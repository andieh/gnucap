/*                               -*- C++ -*-
 * Copyright (C) 2001 Albert Davis
 *               2015 Felix Salfelder
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
 * DEV_CPOLY_G
 * number of nodes = 2*n_ports
 * number of val, ov = n_ports+1
 * val[0] is the constant part, val[1] is self admittance,
 *   val[2+] are transadmittances, up to n_ports
 * node[0] and node[1] are the output.
 * node[2] up are inputs.
 * node[2*i] and node[2*i+1] correspond to val[i+1]
 */
#include <vector>
#include "u_parameter.h"
/*--------------------------------------------------------------------------*/
#include "e_elemnt.h"
#include "m_mvpoly.h"
/*--------------------------------------------------------------------------*/
namespace {
/*--------------------------------------------------------------------------*/
class COMMON_G_POLY_K : public EVAL_BM_ACTION_BASE {
public:
  explicit COMMON_G_POLY_K(int x) :
    EVAL_BM_ACTION_BASE(x),
    _poly(NULL),
    _n_ports(0),
    _minnodes(2),
    _maxnodes(4)
  {
    // set_modelname("poly");
  }
  COMMON_G_POLY_K(const COMMON_G_POLY_K& p) :
    EVAL_BM_ACTION_BASE(p),
    _coeffs(p._coeffs),
    _coeff(p._coeff),
    _poly(NULL),
    _n_ports(p._n_ports),
    _minnodes(p._minnodes),
    _maxnodes(p._maxnodes)
  {
    trace1("copy. coeffs", _coeffs);
    trace1("copy. coeff", _coeff);
  }
  COMMON_COMPONENT* clone()const{return new COMMON_G_POLY_K(*this);}
  bool operator==(const COMMON_COMPONENT&x)const {
    const COMMON_G_POLY_K* p = dynamic_cast<const COMMON_G_POLY_K*>(&x);
    bool rv = p
      && _n_ports == p->_n_ports
      && _coeffs == p->_coeffs
      && EVAL_BM_ACTION_BASE::operator==(x);
    return rv;
  }

  int param_count()const {return 1 + EVAL_BM_ACTION_BASE::param_count(); }
  void parse_type_tail(CS&);
  bool use_obsolete_callback_parse()const {return false;}
  bool use_obsolete_callback_print()const {return false;}
  bool has_parse_params_obsolete_callback()const {return false;}
  std::string name()const
  {
    if(_n_ports){
      return "poly(" + to_string(_n_ports-1) + ")";
    }else{
      return "poly";
    }
  }
  bool has_tr_eval()const{return true;}
  bool ac_too()const {untested();return false;}
  void set_param_by_name(std::string Name, std::string Value)
  {
    trace2("", Name, Value);
    if (Umatch(Name, "c{oeffs} ")) {
      _coeffs = Value;
      trace1("coeffs", _coeffs);
    }else{
      EVAL_BM_ACTION_BASE::set_param_by_name(Name, Value);
    }
  }
  std::string param_name(int i, int j)const{return j?"":param_name(i); }
  std::string param_name(int i)const
  {
    switch (COMMON_G_POLY_K::param_count() - 1 - i) {
      case 0: return "coeffs";
      default: return EVAL_BM_ACTION_BASE::param_name(i);
    }
  }
  void set_param_by_index(int i, std::string& s, int)
  {
//    unsigned i = COMMON_G_POLY_K::param_count() - 1 - I;
    if(i < int(_coeff.size())) {
      //ok.
    }else{
      _coeff.resize(i+1);
    }
    _coeff[i] = s;
  }
  bool param_is_printable(int i)const
  {
    switch (COMMON_G_POLY_K::param_count() - 1 - i) {
      case 0: return true;
      default: return EVAL_BM_ACTION_BASE::param_is_printable(i);
    }
  }
  std::string param_value(int i)const
  {
    switch (COMMON_G_POLY_K::param_count() - 1 - i) {
      case 0: return _coeffs.string();
      default: return EVAL_BM_ACTION_BASE::param_value(i);
    }
  }
  void set_nports(unsigned n_ports)
  {
    _n_ports = n_ports;
    _maxnodes = 2*n_ports;
    _minnodes = 2*n_ports;
  }

  void precalc_first(const CARD_LIST* scope)
  {
    trace3("COMMON_G_POLY_K::precfirst", _coeffs, _n_ports, hp(this));
    _coeffs.e_val(vector<PARAMETER<double> >(), scope);
    trace2("COMMON_G_POLY_K::precfirst", _coeffs, _n_ports);
    if(_coeffs.has_hard_value()){
    }else if(_coeff.size()==0){
    }else if(_coeff[0].has_hard_value()){
      _coeffs = _coeff;
      _coeffs.e_val(vector<PARAMETER<double> >(), scope);
    }
    if(_poly){
    }else if(_n_ports<2){
    }else{
      trace2("COMMON_G_POLY_K::new poly", _coeffs, _n_ports);
      _poly = new MV_POLY<double>(vector<PARAMETER<double> >(_coeffs), _n_ports-1);
    }
  }
  void precalc_last(const CARD_LIST* scope)
  { untested();
    _coeffs.e_val(vector<PARAMETER<double> >(), scope);
    if(_poly){ untested();
    }else{untested();
      _poly = new MV_POLY<double>(vector<PARAMETER<double> >(_coeffs), _n_ports-1);
    }
  }
  void tr_eval(ELEMENT* e) const;
private:
  PARAMETER<vector<PARAMETER<double> > > _coeffs;
  vector<PARAMETER<double> > _coeff; // one by one...
  MV_POLY<double>* _poly;
  unsigned _n_ports;
public: // HACK?
  unsigned _minnodes;
  unsigned _maxnodes;
};
/*--------------------------------------------------------------------------*/
void COMMON_G_POLY_K::parse_type_tail(CS& cmd)
{
  assert(0); // unnneeded
// BUG:  must resize _n
  unsigned ret;
  int paren = cmd.skip1b('(');
  cmd >> ret;
  paren -= cmd.skip1b(')');
  if(paren){
    cmd.warn(bWARNING, "need )");
  }

//  set_nports(1+ret);
//  _maxnodes = 2*_n_ports;
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
class DEV_CPOLY_G : public ELEMENT {
  friend class COMMON_G_POLY_K;
protected:
  hp_float_t*  _values;
  hp_float_t*  _old_values;
  uint_t       _n_ports;
  double   _time;
  const double** _inputs;
protected:
  explicit DEV_CPOLY_G(const DEV_CPOLY_G& p);
public:
  explicit DEV_CPOLY_G(COMMON_COMPONENT* c);
  explicit DEV_CPOLY_G();
  ~DEV_CPOLY_G();
protected: // override virtual
  char id_letter()const	{return 'G';}
  bool print_type_in_spice()const {untested(); return false;}
  std::string value_name()const	{return "p0";}
//  std::string dev_type()const; // element
  uint_t	   max_nodes()const;
  uint_t	   min_nodes()const;
  uint_t	   matrix_nodes()const	{return net_nodes();}
  uint_t	   net_nodes()const;
  uint_t	   ext_nodes()const	{return net_nodes();}
  uint_t	   int_nodes()const	{return 0;}
  CARD*	   clone()const		{return new DEV_CPOLY_G(*this);}
  void	   tr_iwant_matrix()	{tr_iwant_matrix_extended();}
  bool	   do_tr();
  void	   tr_load();
  void	   tr_unload();
  hp_float_t   tr_involts()const	{unreachable(); return NOT_VALID;}
  hp_float_t   tr_involts_limited()const {unreachable(); return NOT_VALID;}
  hp_float_t   tr_amps()const;
  void	   ac_iwant_matrix()	{ac_iwant_matrix_extended();}
  void	   ac_load();
  COMPLEX  ac_involts()const	{itested(); return NOT_VALID;}
  COMPLEX  ac_amps()const	{itested(); return NOT_VALID;}

  std::string port_name(uint_t n)const {
    if(n==0){
      return "p";
    }else if(n==1){
      return "n";
    }else if(n%2){
      return "cn" + to_string(n/2-1);
    }else{
      return "cp" + to_string(n/2-1);
    }
  }
public:
  void set_port_by_index(uint_t num, std::string& ext_name);
  void alloc_values();
  void set_parameters(const std::string& Label, CARD* Parent,
		      COMMON_COMPONENT* Common, double Value,
		      uint_t state_count, hp_float_t state[],
		      uint_t node_count, const node_t nodes[]);
  //		      const double* inputs[]=0);
  int param_count()const { return 0 + ELEMENT::param_count(); }
  std::string param_name(int i, int)const{ return param_name(i); }
  std::string param_name(int i)const
  {
    switch (DEV_CPOLY_G::param_count() - 1 - i) {
//      case 0: return "coeffs";
      default: return ELEMENT::param_name(i);
    }
  }
//  std::string param_value(int i)const
//  {
//    COMMON_G_POLY_K const* p = dynamic_cast<COMMON_G_POLY_K const*>(common());
//    assert(p);
//    switch (DEV_CPOLY_G::param_count() - 1 - i) {
//      case 0: return p->_coeffs.string();
//      default: return ELEMENT::param_value(i);
//    }
//  }
  bool param_is_printable(int i)const
  {
    switch (DEV_CPOLY_G::param_count() - 1 - i) {
      case 0: return true;
      default: return ELEMENT::param_is_printable(i);
    }
  }
  void set_param_by_index(int, std::string&, int);
  void set_param_by_name(const std::string, const std::string);
  void expand();
  void precalc_last();
protected:
  bool do_tr_con_chk_and_q();
};
/*--------------------------------------------------------------------------*/
uint_t DEV_CPOLY_G::net_nodes()const
{
  if(!common()){
    return _n_ports*2;
  }else{
    assert(max_nodes()<100);
    return max_nodes();
  }
}
/*--------------------------------------------------------------------------*/
uint_t DEV_CPOLY_G::min_nodes()const
{
  if(!common()){
    return net_nodes();
  }else if (COMMON_G_POLY_K const* p=dynamic_cast<COMMON_G_POLY_K const*>(common())){
    // not necessary...
    return p->_minnodes;
  }else{
    assert(max_nodes()<100);
    return max_nodes();
  }
}
/*--------------------------------------------------------------------------*/
uint_t DEV_CPOLY_G::max_nodes() const
{
  // various cases
  //
  // Gfoo 1 2 poly(k) n1....n2k p0...p
  // need (should use?) max_nodes to find p0 (?)
  //
  // Gfoo ( 1 2 n1 n2k ) poly(k) p0...p
  // need max_nodes >> 1, check later
  //
  // g_poly_k #(.nports(3),.c(0,0,1,0,0)) p3( ... )
  // nports sets max_nodes
  //
  if(!common()){
  // modelgen: no common here, max_nodes() == net_nodes()
    return net_nodes();
  }else if (COMMON_G_POLY_K const* p=dynamic_cast<COMMON_G_POLY_K const*>(common())){
    return p->_maxnodes;
  }else{
    return 4;
  }
}
/*--------------------------------------------------------------------------*/
//std::string DEV_CPOLY_G::dev_type()const
//{
//  if(common()){ untested();
//    return common()->modelname();
//  }else{ untested();
//    return "cpoly_g";
//  }
//}
/*--------------------------------------------------------------------------*/
void DEV_CPOLY_G::set_port_by_index(uint_t num, std::string& ext_name)
{
  trace3("DEV_CPOLY_G::set_port_by_index", num, ext_name, max_nodes());
  if (num < max_nodes()) {
    _n[num].new_node(ext_name, this);
    if (num+1 > _net_nodes) {
      _net_nodes = num+1;
    }else{
      // it's already big enough, probably assigning out of order
    }
  }else{
    throw Exception_Too_Many(num+1, max_nodes(), 0/*offset*/);
  }
}
/*--------------------------------------------------------------------------*/
void COMMON_G_POLY_K::tr_eval(ELEMENT* e) const
{
  DEV_CPOLY_G* d = prechecked_cast<DEV_CPOLY_G*>(e);
  trace3("COMMON_G_POLY_K::tr_eval", e->long_label(), _n_ports, d->net_nodes());
  trace2("b4", d->_values[2], d->_values[3]);
  d->_values[0] = _poly->eval(d->_values+2);
  trace1("evald", d->_values[1]);
  trace2("deriv", d->_values[2], d->_values[3]);

  // bool DEV_FPOLY_G::do_tr()?
  for(unsigned i=2; i<=_n_ports; ++i) {
    d->_values[0] -= dn_diff(d->n_(2*i-2).v0(),d->n_(2*i-1).v0()) * d->_values[i];
  }

  trace3("after", d->_values[0], d->_values[1], d->_values[2]);
}
/*--------------------------------------------------------------------------*/
#if 0
class DEV_FPOLY_G : public DEV_CPOLY_G {
private:
  explicit DEV_FPOLY_G(const DEV_FPOLY_G& p)
    :DEV_CPOLY_G(p) {incomplete(); unreachable();}
public:
  explicit DEV_FPOLY_G() :DEV_CPOLY_G() {untested();}
private: // override virtual
  char	   id_letter()const	{unreachable(); return '\0';}
  std::string dev_type()const	{unreachable(); return "fpoly_g";}
  CARD*	   clone()const		{unreachable(); return new DEV_FPOLY_G(*this);}
  bool	   do_tr();
};
#endif
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
DEV_CPOLY_G::DEV_CPOLY_G(const DEV_CPOLY_G& p)
  :ELEMENT(p),
   _values(NULL),
   _old_values(NULL),
   _n_ports(p._n_ports),
   _time(NOT_VALID),
   _inputs(NULL)
{
  assert(!p._values);
  assert(!p._old_values);
  assert(p._n_ports == 0);
  assert(!p._inputs);

  assert(p.max_nodes() == max_nodes());
  if (max_nodes() > NODES_PER_BRANCH) { untested();
    trace1("DEV_CPOLY_G, copy more nodes", net_nodes());
    _n = new node_t[max_nodes()];

    for (uint_t ii = 0; ii<max_nodes(); ++ii) { untested();
      _n[ii] = p._n[ii];
    }
  }
}
/*--------------------------------------------------------------------------*/
DEV_CPOLY_G::DEV_CPOLY_G()
  :ELEMENT(),
   _values(NULL),
   _old_values(NULL),
   _n_ports(0),
   _time(NOT_VALID),
   _inputs(NULL)
{
}
/*--------------------------------------------------------------------------*/
DEV_CPOLY_G::DEV_CPOLY_G(COMMON_COMPONENT* c)
  :ELEMENT(),
   _values(NULL),
   _old_values(NULL),
   _n_ports(0),
   _time(NOT_VALID),
   _inputs(NULL)
{ untested();
  attach_common(c);
}
/*--------------------------------------------------------------------------*/
DEV_CPOLY_G::~DEV_CPOLY_G()
{
  delete [] _old_values;
  if (max_nodes() > NODES_PER_BRANCH) {
    delete [] _n;
  }else{
    // it is part of a base class
  }
}
/*--------------------------------------------------------------------------*/
bool DEV_CPOLY_G::do_tr_con_chk_and_q()
{
  q_load();

  assert(_old_values);
  set_converged(conchk(_time, _sim->_time0));
  _time = _sim->_time0;
  for (uint_t i=0; converged() && i<=_n_ports; ++i) {
    set_converged(conchk(_old_values[i], _values[i]));
  }
  return converged();
}
/*--------------------------------------------------------------------------*/
bool DEV_CPOLY_G::do_tr()
{
  trace3("DEV_CPOLY_G::do_tr", long_label(), _n_ports, hp(&n_(0)));
  if (using_tr_eval()) {
    for(unsigned i=2; i<=_n_ports; ++i) {
      trace2("", long_label(), i);
      _values[i] = dn_diff(n_(2*i-2).v0(), n_(2*i-1).v0());
    }
    assert(dynamic_cast<COMMON_G_POLY_K const*>(common())); // for now.
    tr_eval();
  }else{
  }
  assert(_values);
  _m0 = CPOLY1(0., _values[0], _values[1]);
  return do_tr_con_chk_and_q();
}
/*--------------------------------------------------------------------------*/
#if 0
bool DEV_FPOLY_G::do_tr()
{untested();
  assert(_values);
  double c0 = _values[0];
  if (_inputs) {untested();
    untested();
    for (int i=1; i<=_n_ports; ++i) {untested();
      c0 -= *(_inputs[i]) * _values[i];
      trace4("", i, *(_inputs[i]), _values[i], *(_inputs[i]) * _values[i]);
    }
  }else{untested();
    for (int i=1; i<=_n_ports; ++i) {untested();
      c0 -= volts_limited(_n[2*i-2],_n[2*i-1]) * _values[i];
      trace4("", i, volts_limited(_n[2*i-2],_n[2*i-1]), _values[i],
	     volts_limited(_n[2*i-2],_n[2*i-1]) * _values[i]);
    }
  }
  trace2("", _values[0], c0);
  _m0 = CPOLY1(0., c0, _values[1]);

  return do_tr_con_chk_and_q();
}
#endif
/*--------------------------------------------------------------------------*/
void DEV_CPOLY_G::tr_load()
{
  trace3("tr_load", long_label(),_values[0], _values[1]);
  tr_load_passive();
  _old_values[0] = _values[0];
  _old_values[1] = _values[1];
  for (uint_t i=2; i<=_n_ports; ++i) {
    trace4("tr_load", i, _values[i], _n[2*i-2].v0(), _n[2*i-1].v0());
    tr_load_extended(_n[OUT1], _n[OUT2], _n[2*i-2], _n[2*i-1], &(_values[i]), &(_old_values[i]));
  }
}
/*--------------------------------------------------------------------------*/
void DEV_CPOLY_G::tr_unload()
{
  std::fill_n(_values, _n_ports+1, 0.);
  _m0.c0 = _m0.c1 = 0.;
  _sim->mark_inc_mode_bad();
  tr_load();
}
/*--------------------------------------------------------------------------*/
hp_float_t DEV_CPOLY_G::tr_amps()const
{
  hp_float_t amps = _m0.c0;
  for (uint_t i=1; i<=_n_ports; ++i) {
    amps += dn_diff(_n[2*i-2].v0(),_n[2*i-1].v0()) * _values[i];
  }
  return amps;
}
/*--------------------------------------------------------------------------*/
void DEV_CPOLY_G::ac_load()
{
  _acg = _values[1];
  ac_load_passive();
  for (uint_t i=2; i<=_n_ports; ++i) {
    ac_load_extended(_n[OUT1], _n[OUT2], _n[2*i-2], _n[2*i-1], _values[i]);
  }
}
/*--------------------------------------------------------------------------*/
/* set: set parameters, used in model building
 */
void DEV_CPOLY_G::set_parameters(const std::string& Label, CARD *Owner,
				 COMMON_COMPONENT *Common, double Value,
				 uint_t n_states, hp_float_t states[],
				 uint_t n_nodes, const node_t nodes[])
  //				 const double* inputs[])
{
  bool first_time = (net_nodes() == 0);

  set_label(Label);
  set_owner(Owner);
  set_value(Value);
  attach_common(Common);

  if (first_time) {
    _n_ports = n_nodes/2; // sets num_nodes() = _n_ports*2
    _net_nodes = n_nodes;
    assert(_n_ports+1 == n_states);

    assert(!_old_values);
    _old_values = new hp_float_t[n_states];

    assert(net_nodes() == max_nodes());
    if (net_nodes() > NODES_PER_BRANCH) {
      trace1("DEV_CPOLY_G::set_parameters, more nodes", net_nodes());
      // allocate a bigger node list
      _n = new node_t[net_nodes()];
    }else{
      // use the default node list, already set
    }      
  }else{
    assert(_n_ports == n_states-1);
    assert(_old_values);
    assert(net_nodes() == n_nodes);
    // assert could fail if changing the number of nodes after a run
  }

  //_inputs = inputs;
  _inputs = 0;
  _values = states;
  std::fill_n(_values, n_states, 0.);
  std::fill_n(_old_values, n_states, 0.);
  notstd::copy_n(nodes, matrix_nodes(), _n); // copy to _n
  assert(matrix_nodes() == _n_ports * 2);
}
/*--------------------------------------------------------------------------*/
void DEV_CPOLY_G::set_param_by_index(int pos, std::string& Value, int slot)
{
  trace2("DEV_CPOLY_G::set_param_by_index", pos, Value);
  if (common()){ untested();
    COMMON_COMPONENT* m = common()->clone();
    try{ untested();
      unsigned count=0; // incomplete;
      m->set_param_by_index(pos+count, Value, slot);
    }catch(...){ untested();
      delete m;
      throw;
    }
    attach_common(m);

  }else{ incomplete();
  }
}
/*--------------------------------------------------------------------------*/
void DEV_CPOLY_G::alloc_values()
{
//  assert(common());
//  COMMON_G_POLY_K const* p = dynamic_cast<COMMON_G_POLY_K const*>(common());
//  assert(p);
//  _n_ports = p->_maxnodes/2;
//  trace3("alloc_values", long_label(), _n_ports, matrix_nodes());
//  assert(matrix_nodes() == _n_ports*2);
  _values = new double[matrix_nodes()];
  _values[0] = 0;
  _values[1] = 0; // self admittance
  _old_values = new double[matrix_nodes()];
}
/*--------------------------------------------------------------------------*/
void DEV_CPOLY_G::set_param_by_name(std::string Name, std::string Value)
{
  bool retry = false;
  if (!common()){ incomplete();
  }else if (Umatch(Name, "p0 ")) {
    incomplete();
  }else if (Umatch(Name, "bmarg|nports")) {
    if(_n_ports){ untested();
      throw Exception("only one nports allowed right now.");
    }
    _n_ports = atoi(Value.c_str()) + 1;

    // HACK
    COMMON_COMPONENT* m = common()->clone();
    assert(m);
    COMMON_G_POLY_K* p = dynamic_cast<COMMON_G_POLY_K*>(m);
    assert(p);
    p->set_nports(_n_ports);
    // m->set_param_by_name("nports",_n_ports);
    attach_common(p);

    if (max_nodes() > NODES_PER_BRANCH) {
      // allocate a bigger node list
      trace3("DEV_CPOLY_G more nodes", long_label(), max_nodes(), Value);
      node_t* oldn = _n;
      _n = new node_t[max_nodes()];
      for (uint_t ii = 0; ii<NODES_PER_BRANCH; ++ii) {
	_n[ii] = oldn[ii];
      }

    }else{
      trace3("DEV_CPOLY_G enough nodes", long_label(), max_nodes(), NODES_PER_BRANCH);
      // use the default node list, already set
    }


    // HACK
    alloc_values();
  }else if (Umatch(Name, "c{oeffs} ")) {
    // HACK. try all names.
    assert(common());
    COMMON_COMPONENT* m = common()->clone();
    try{
      m->set_param_by_name(Name,Value);
    }catch(Exception){untested();
      retry = true;
      delete m;
      m = NULL;
    }
    if(m){
      attach_common(m);
      trace2("coeffs attached", common()->param_value(m->param_count()-1), hp(common()));
    }else{ untested();
    }
  }else{
   retry = true;
  }

  if(retry){
    ELEMENT::set_param_by_name(Name, Value);
  }else{
  }
}
/*--------------------------------------------------------------------------*/
void DEV_CPOLY_G::expand()
{
  if(_values){
    // hack: done by set_parameters
    // move to common somehow
  }else{ untested();
  }
}
/*--------------------------------------------------------------------------*/
void DEV_CPOLY_G::precalc_last()
{
  trace3("DEV_CPOLY_G::precalc_last", long_label(), net_nodes(), matrix_nodes());

  if(_values){
    // hack: done by set_parameters
    // move to common somehow
  }else{ untested();
    alloc_values();
  }
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
// raw device. used by modelgen
DEV_CPOLY_G p4;
DISPATCHER<CARD>::INSTALL d4(&device_dispatcher, "cpoly_g", &p4);

COMMON_G_POLY_K poly(CC_STATIC);
DISPATCHER<COMMON_COMPONENT>::INSTALL d1(&bm_dispatcher, "poly_k", &poly);

// not required, maybe. using bm_wrapper
// DEV_CPOLY_G p5(&poly);
// DISPATCHER<CARD>::INSTALL d5(&device_dispatcher, "g_poly_k", &p5);
}
/*--------------------------------------------------------------------------*/
// hack: put it here, for now.
vector<vector<unsigned> > MV_POLY_BASE::_spn_list=vector<vector<unsigned> >(1,vector<unsigned>(1,1));
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
// vim:ts=8:sw=2:noet:
