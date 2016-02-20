/*                              -*- C++ -*-
 * Copyright (C) 2001 Albert Davis
 * Author: Albert Davis <aldavis@gnu.org>
 *
 * This file is part of "Gnucap", the Gnu Circuit Analysis Package
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *------------------------------------------------------------------
 * solve one step of a transient or dc analysis
 */
#include "e_cardlist.h"
#include "u_status.h"
#include "e_node.h"
#include "s__.h"
#include "io_matrix.h"
/*--------------------------------------------------------------------------*/
//	bool	SIM::solve(int,int);
//	void	SIM::finish_building_evalq();
//	void	SIM::advance_time();
//	void	SIM::set_flags();
//	void	SIM::clear_arrays();
//	void	SIM::evaluate_models();
//	void	SIM::set_damp();
//	void	SIM::load_matrix();
//	void	SIM::solve_equations();
/*--------------------------------------------------------------------------*/
static bool converged = false;
/*--------------------------------------------------------------------------*/
bool SIM::solve(OPT::ITL itl, TRACE trace)
{
  trace1("SIM::solve", trace);
  converged = false;
  int convergedcount = 0;
  
  _sim->reset_iteration_counter(iSTEP);
  advance_time();

  _sim->_damp = OPT::dampmax; // default 1.0
 
  do{
    if (( trace & (tMATRIX-1) ) >= tITERATION) {
      trace1("SIM::solve results", _sim->sim_mode());
      SIM::print_results(static_cast<double>(-_sim->iteration_number()));
      // Hack: Added SIM:: / print_results has been overloade but puts out the wrong data
    }
    set_flags();
    clear_arrays();
    finish_building_evalq();
    
    _sim->count_iterations(iPRINTSTEP);
    _sim->count_iterations(iSTEP);
    _sim->count_iterations(_sim->_mode);
    _sim->count_iterations(iTOTAL);
    
    evaluate_models();

    if (converged) {
      if (_sim->_limiting) {
	error(bDEBUG, "converged beyond limit, resetting limit\n");
	_sim->set_limit();
	convergedcount = 0;
      }else{
	++convergedcount;
      }
    }else{
      convergedcount = 0;
    }
    if (convergedcount <= OPT::itermin) {
      converged = false;
    }
      
    if (!converged || !OPT::fbbypass || _sim->_damp < .99) {
      set_damp();
      load_matrix();
      assert(_sim->_loadq.empty());
      trace0("solve_equations");
      try{
        solve_equations(trace);
      }catch(Exception e){
       error(bWARNING, "%s\n", e.message().c_str());
       return false;
      }

      trace0("solve_equations done");
    }
  }while (!converged && !_sim->exceeds_iteration_limit(itl));

  //for(unsigned int y=0; y<_sim->_loadq.size(); y++) {
    //untested0( ("after solve loadq " + _sim->_loadq[y]->long_label()).c_str() );
  //}
  return converged;
}
/*--------------------------------------------------------------------------*/
bool SIM::solve_with_homotopy(OPT::ITL itl, TRACE trace)
{
  solve(itl, trace);
  trace3("plain", _sim->_iter[iSTEP], OPT::gmin, converged);
  if (!converged && OPT::itl[OPT::SSTEP] > 0) {
    int save_itermin = OPT::itermin;
    OPT::itermin = 0;
    double save_gmin = OPT::gmin;
    OPT::gmin = .9;
    while (_sim->_iter[iPRINTSTEP] < OPT::itl[OPT::SSTEP] && OPT::gmin > save_gmin) {
      //CARD_LIST::card_list.precalc();
      _sim->set_inc_mode_no();
      trace2("again... ", _sim->_iter[iSTEP], OPT::gmin);
      solve(itl, trace);
      if (!converged) {
	trace2("fail", _sim->_iter[iSTEP], OPT::gmin);
	if (OPT::gmin*OPT::shortckt > 1){
	  error(bDANGER, "ramping failed at gmin=%E\n", OPT::gmin);
	  break;
	}
	OPT::gmin *= 3.5;
      }else{
	trace2("success", _sim->_iter[iSTEP], OPT::gmin);
	OPT::gmin /= 4;
      }
    }
    OPT::itermin = save_itermin;
    OPT::gmin = save_gmin;
    //CARD_LIST::card_list.precalc();
    solve(itl, trace);
    if (!converged) {
      trace2("final fail", _sim->_iter[iSTEP], OPT::gmin);
    }else{
      trace2("final success", _sim->_iter[iSTEP], OPT::gmin);
    }
  }else{
  }
  return converged;
}
/*--------------------------------------------------------------------------*/
/* finish_building_evalq
 * This function scans the circuit to queue for evaluation anything 
 * that is relevant that the devices missed themselves.
 * For now, it scans the whole circuit, but this will change.
 * This is slow, but the result is still faster than not having a queue.
 * The plan is .. every node knows whether it needs eval or not, and
 * only those nodes needing eval will be scanned.
 * Its purpose is to catch nodes that wake up after being dormant
 */
void SIM::finish_building_evalq(void)
{
  ::status.queue.start();
  CARD_LIST::card_list.tr_queue_eval();
  ::status.queue.stop();
}
/*--------------------------------------------------------------------------*/
void SIM::advance_time(void)
{
  static double last_iter_time;
  trace2("SIM::advance_time()", _sim->_time0, last_iter_time);
  ::status.advance.start();
  if (_sim->_time0 > 0) {
    _sim->_nstat[0].set_discont(disNONE);
    if (_sim->_time0 > last_iter_time) {	/* moving forward */
      notstd::copy_n(_sim->_v0, _sim->_total_nodes+1, _sim->_vt1);
      CARD_LIST::card_list.tr_advance();
    }else{
      /* moving backward */
      /* don't save voltages.  They're wrong! */
      /* instead, restore a clean start for iteration */
      notstd::copy_n(_sim->_vt1, _sim->_total_nodes+1, _sim->_v0);
      CARD_LIST::card_list.tr_regress();
    }
  }else{
    trace1("SIM::advance_time dc_adv.", _sim->_time0);
    CARD_LIST::card_list.dc_advance();
  }
  last_iter_time = _sim->_time0;
  ::status.advance.stop();
}
/* last_iter_time is initially 0 by C definition.
 * On subsequent runs it will start with an arbitrary positive value.
 * _sim->_time0 starts at either 0 or the ending time of the last run.
 * In either case, (time0 > last_iter_time) is false on the first step.
 * This correctly results in "don't save voltages..."
 */
/*--------------------------------------------------------------------------*/
void SIM::set_flags()
{
  _sim->_limiting = false;
  _sim->_fulldamp = false;
  
  if (OPT::incmode == false) {
    _sim->set_inc_mode_no();
  }else if (_sim->inc_mode_is_bad()) {
    _sim->set_inc_mode_no();
  }else if (_sim->is_iteration_number(OPT::itl[OPT::TRLOW])) {
    _sim->set_inc_mode_no();
  }else if (_sim->is_iteration_number(0)) {
    // leave it as is
  }else{
    _sim->set_inc_mode_yes();
  }

  _sim->_bypass_ok = 
    (is_step_rejected()  ||  _sim->_damp < OPT::dampmax*OPT::dampmax)
    ? false : bool(OPT::bypass);
}
/*--------------------------------------------------------------------------*/
void SIM::clear_arrays(void)
{
  trace0("SIM::clear_arrays");
  if (!_sim->is_inc_mode()) {			/* Clear working array */
    _sim->_aa.zero();
    _sim->_aa.dezero(OPT::gmin);		/* gmin fudge */
    trace2("SIM::clear_arrays ", _sim->_aa.size(), hp(_sim->_i) );
    assert(_sim->_i);
    assert(_sim->_aa.size()<=_sim->_total_nodes);
    std::fill_n(_sim->_i, _sim->_aa.size()+1, 0);
  }
  trace0("loadq clear");
  _sim->_loadq.clear();
}
/*--------------------------------------------------------------------------*/
void SIM::evaluate_models()
{
  ::status.evaluate.start();
  _sim->_nstat[0].set_discont(disNONE);
  if (OPT::bypass) {
    converged = true;
    std::swap(_sim->_evalq, _sim->_evalq_uc);
    while (!_sim->_evalq->empty()) {
      converged &= _sim->_evalq->front()->do_tr();
      _sim->_evalq->pop_front();
    }
  }else{
    _sim->_evalq_uc->clear();
    converged = CARD_LIST::card_list.do_tr();
  }
  while (!_sim->_late_evalq.empty()) { //BUG// encapsulation violation
    converged &= _sim->_late_evalq.front()->do_tr_last();
    _sim->_late_evalq.pop_front();
  }
  ::status.evaluate.stop();
}
/*--------------------------------------------------------------------------*/
void SIM::set_damp()
{
  if (_sim->is_second_iteration() && !converged && OPT::dampstrategy&dsINIT) {
    _sim->_damp = OPT::dampmin;
  }else if (_sim->is_first_iteration()  ||  converged) {
    _sim->_damp = OPT::dampmax;
  }else if (_sim->_fulldamp) {
    _sim->_damp = OPT::dampmin;
  }else{
    _sim->_damp = OPT::dampmax;
  }
  trace1("SIM::set_damp", _sim->_damp);
}
/*--------------------------------------------------------------------------*/
void SIM::load_matrix()
{
  ::status.load.start();
  if (OPT::traceload && _sim->is_inc_mode()) {
    trace0("SIM::load_matrix loading some");
    while (!_sim->_loadq.empty()) {
      _sim->_loadq.back()->tr_load();
      _sim->_loadq.pop_back();
    }
  }else{
    trace0("SIM::load_matrix loading all :( ");
    _sim->_loadq.clear();
    CARD_LIST::card_list.tr_load();
  }
  ::status.load.stop();
}
/*--------------------------------------------------------------------------*/
#ifndef NDEBUG
static double* v0;
unsigned init_vectors;
#endif
void SIM::solve_equations(TRACE trace)
{
#ifndef NDEBUG
  if (init_vectors!=_sim->_total_nodes+1) {
    delete[] v0;
    v0 = new double[_sim->_total_nodes+1];
    init_vectors = _sim->_total_nodes+1;
  }
#endif

  trace1("SIM::solve_equations", trace);
  if(trace & tMATRIX /* && printhere */) {
    _out << "\n--- aa -------\n" <<  _sim->_aa << "\n--- i ----\n";
    for (unsigned i=0; i<_sim->_total_nodes; ++i){
      _out << _sim->_i[i+1] << ", ";
    }
    _out << "\n-----\n";
  }

  ::status.lud.start();
  _sim->_lu.lu_decomp(_sim->_aa, bool(OPT::lubypass && _sim->is_inc_mode()));
  ::status.lud.stop();

#ifndef NDEBUG
  notstd::copy_n(_sim->_v0, _sim->_total_nodes+1, v0);
  std::string exnumbers("");
#endif
  ::status.back.start();
  _sim->_lu.fbsub(_sim->_v0, _sim->_i, _sim->_v0);
  ::status.back.stop();

  _sim->_dxm = 0;
  for(unsigned i=0;i<=_sim->_total_nodes; ++i){
    if (!is_number(_sim->_v0[i])) {
      assert(i); // cannot happen in gnd
#ifdef NDEBUG
      unreachable();
#else
      _sim->_v0[i] = 0;
      exnumbers += " " + to_string(i);
    }
    _sim->_dxm = std::max(_sim->_dxm, fabs(_sim->_v0[i] - v0[i]));
  }
  {
    if(exnumbers!=""){
      throw(Exception("cannot solve linear equation, nan in positions" + exnumbers));
#endif
    }
  }

  if (_sim->_nstat) {
    // mixed mode
    for (unsigned ii = _sim->_lu.size(); ii >= 1; --ii) {
//      _sim->_nstat[ii].set_discont(disNONE);
      _sim->_nstat[ii].set_a_iter();
//      assert(!_sim->_nstat[ii].discont());
    }
  }else{ untested();
    // pure analog
  }
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
// vim:ts=8:sw=2:noet:
