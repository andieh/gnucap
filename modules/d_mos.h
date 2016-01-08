/* $Id: d_mos.h,v 1.16 2010-09-07 07:46:20 felix Exp $ -*- C++ -*-
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
 * data structures and defaults for mos model.
 * internal units all mks (meters)
 * but some user input parameters are in cm.
 *
 * netlist syntax:
 * device:  mxxxx d g s b mname <device args> <model card args>
 * model:   .model mname NMOS <args>
 *	or  .model mname PMOS <args>
 */
/* This file is not automatically generated. */

#ifndef D_MOS_H_INCLUDED
#define D_MOS_H_INCLUDED

#define BTI_HACK 
#define RCD_NUMBER 3
#define BTI_RC 1e-4 // tmp

#include "d_diode.h"
#include "u_sdp.h"
#include "e_node.h"
#include "e_subckt.h"
#include "e_model.h"
#include "bm.h"
#include "u_xprobe.h"
namespace UF{
/*--------------------------------------------------------------------------*/
class COMMON_BUILT_IN_MOS
  :public COMMON_COMPONENT{
  friend class DEV_BUILT_IN_MOS;
public:
  explicit COMMON_BUILT_IN_MOS(const COMMON_BUILT_IN_MOS& p);
  explicit COMMON_BUILT_IN_MOS(int c=0);
           ~COMMON_BUILT_IN_MOS();
  bool     operator==(const COMMON_COMPONENT&)const;
  COMMON_COMPONENT* clone()const {return new COMMON_BUILT_IN_MOS(*this);}
  void     set_param_by_index(int, std::string&, int);
  void     set_param_by_name(std::string Name, std::string Value);
  bool     param_is_printable(int)const;
  std::string param_name(int)const;
  std::string param_name(int,int)const;
  std::string param_value(int)const;
  int param_count()const {return (8 + COMMON_COMPONENT::param_count());}
  void     precalc_first(const CARD_LIST*);
  void     expand(const COMPONENT*);
  void     precalc_last(const CARD_LIST*);
  std::string name()const {itested();return "mosfet";}
  const SDP_CARD* sdp()const {return _sdp;}
  bool     has_sdp()const {untested();return _sdp;}
  static int  count() {return _count;}
private: // strictly internal
  static int _count;
public: // input parameters
  PARAMETER<double> l_in;	// drawn (optical) channel length
  PARAMETER<double> w_in;	// channel width (drawn)
  PARAMETER<double> ad_in;	// drain area, drawn
  PARAMETER<double> as_in;	// source area, drawn
  PARAMETER<double> pd;	// drain perimeter
  PARAMETER<double> ps;	// source perimeter
  PARAMETER<double> nrd;	// drain # squares
  PARAMETER<double> nrs;	// source # squares
public: // calculated parameters
  SDP_CARD* _sdp;
public: // attached commons
  COMMON_COMPONENT* _db;
  COMMON_COMPONENT* _sb;
};
/*--------------------------------------------------------------------------*/
#define CAPCOMMON EVAL_BM_ACTION_BASE
class EVAL_BUILT_IN_MOS_Cgb : public CAPCOMMON {
private:
  explicit EVAL_BUILT_IN_MOS_Cgb(const EVAL_BUILT_IN_MOS_Cgb& p)
    :CAPCOMMON(p) {}
public:
  explicit EVAL_BUILT_IN_MOS_Cgb(int c=0) :CAPCOMMON(c) {}
  bool operator==(const COMMON_COMPONENT& x)const {return COMMON_COMPONENT::operator==(x);}
  COMMON_COMPONENT* clone()const {return new EVAL_BUILT_IN_MOS_Cgb(*this);}
  std::string name()const {untested(); return "EVAL_BUILT_IN_MOS_Cgb";}
  void tr_eval(ELEMENT*d)const;
  bool has_tr_eval()const {return true;}
  bool has_ac_eval()const {return false;}
  bool ac_too()const {return 1;}
};
/*--------------------------------------------------------------------------*/
class EVAL_BUILT_IN_MOS_Cgd : public CAPCOMMON {
private:
  explicit EVAL_BUILT_IN_MOS_Cgd(const EVAL_BUILT_IN_MOS_Cgd& p)
    :CAPCOMMON(p) {}
public:
  explicit EVAL_BUILT_IN_MOS_Cgd(int c=0) :CAPCOMMON(c) {}
  bool operator==(const COMMON_COMPONENT& x)const {return COMMON_COMPONENT::operator==(x);}
  COMMON_COMPONENT* clone()const {return new EVAL_BUILT_IN_MOS_Cgd(*this);}
  std::string name()const {untested(); return "EVAL_BUILT_IN_MOS_Cgd";}
  void tr_eval(ELEMENT*d)const;
  bool has_tr_eval()const {return true;}
  bool has_ac_eval()const {return false;}
  bool ac_too()const {return 1;}
};
/*--------------------------------------------------------------------------*/
class EVAL_BUILT_IN_MOS_Cgs : public CAPCOMMON {
private:
  explicit EVAL_BUILT_IN_MOS_Cgs(const EVAL_BUILT_IN_MOS_Cgs& p)
    :CAPCOMMON(p) {}
public:
  explicit EVAL_BUILT_IN_MOS_Cgs(int c=0) :CAPCOMMON(c) {}
  bool operator==(const COMMON_COMPONENT& x)const {return COMMON_COMPONENT::operator==(x);}
  COMMON_COMPONENT* clone()const {return new EVAL_BUILT_IN_MOS_Cgs(*this);}
  std::string name()const {untested(); return "EVAL_BUILT_IN_MOS_Cgs";}
  void tr_eval(ELEMENT*d)const;
  bool has_tr_eval()const {return true;}
  bool has_ac_eval()const {return false;}
  bool ac_too()const {return 1;}
};
/*--------------------------------------------------------------------------*/
class DEV_BUILT_IN_MOS : public BASE_SUBCKT {
private:
  explicit DEV_BUILT_IN_MOS(const DEV_BUILT_IN_MOS& p);
public:
  explicit DEV_BUILT_IN_MOS();
           ~DEV_BUILT_IN_MOS();
private: // override virtual
  char      id_letter()const     {untested();return 'M';}
  bool      print_type_in_spice()const {return true;}
  std::string value_name()const  {return "area";}
  //std::string dev_type()const;   //BASE_SUBCKT
  uint_t       max_nodes()const     {return 4;}
  uint_t       min_nodes()const     {return 4;}
  //int     matrix_nodes()const; //BASE_SUBCKT
  uint_t       net_nodes()const     {return 4;}
  uint_t       int_nodes()const     {return 2;}
  CARD*     clone()const         {return new DEV_BUILT_IN_MOS(*this);}
  void      precalc_first(); // {COMPONENT::precalc_first(); if(subckt()) subckt()->precalc_first();}
  void      expand();
  void      precalc_last();//  {COMPONENT::precalc_last(); assert(subckt()); subckt()->precalc_last();}
  void    map_nodes();         //BASE_SUBCKT
  void    tr_begin();          //BASE_SUBCKT
  void    tr_restore();        //BASE_SUBCKT
  void      dc_advance();// {set_not_converged(); BASE_SUBCKT::dc_advance();}
  void      tr_advance();// {set_not_converged(); BASE_SUBCKT::tr_advance();}
  void      tr_regress();// {set_not_converged(); BASE_SUBCKT::tr_regress();}
  bool      tr_needs_eval()const;
  void      tr_queue_eval()      {if(tr_needs_eval()){q_eval();}}
  bool      do_tr();
  void    tr_load();           
  TIME_PAIR  tr_review();         
  void    tr_accept();         
  void    tr_unload();         
  double    tr_probe_num(const std::string&)const;
  double    tt_probe_num(const std::string&)const;
  void      do_sens();
  XPROBE sens_probe_ext(const std::string&)const;

  //void    ac_begin(){}          //BASE_SUBCKT
  //void    do_ac(){}             //BASE_SUBCKT
  //void    ac_load(){}           //BASE_SUBCKT
  XPROBE  ac_probe_ext(const std::string&)const;//debugging
public:
  static int  count() {return _count;}
public: // may be used by models
  void reverse_if_needed();
private: // not available even to models
  static int _count;
public: // input parameters
public: // calculated parameters
  double ids;	// 
  double idsxxx;	// 
  double gds;	// dids/dvds
  double gmf;	// dids/dvgs
  double gmr;	// dids/dvgd
  double gmbf;	// dids/dvbs
  double gmbr;	// dids/dvbd
  double idb;	// 
  double idbxxx;	// 
  double gdbdb;	// placeholder
  double gdbds;	// disub/dvds
  double gdbgs;	// disub/dvgs
  double gdbbs;	// disub/dvbs
  double isb;	// 
  double isbxxx;	// 
  double gsbsb;	// placeholder
  double gsbsd;	// disub/dvds
  double gsbgd;	// disub/dvgs
  double gsbbd;	// disub/dvbs
  double qgate;	// raw
  double cgs;	// dqgate_vgs placeholder
  double cggb;	// dqgate_vgb
  double cgsb;	// dqgate_vsb
  double cgdb;	// dqgate_vdb
  double qgs;	// forward mode
  double cgsgs;	// dqgs_vgs placeholder
  double cgsgb;	// dqgs_vgb
  double cgssb;	// dqgs_vsb
  double cgsdb;	// dqgs_vdb
  double qgd;	// reverse mode
  double cgdgd;	// dqgd_vgs placeholder
  double cgdgb;	// dqgd_vgb
  double cgdsb;	// dqgd_vsb
  double cgddb;	// dqgd_vdb
  double qdrn;	// Qds
  double cdsds;	// dqds_vds placeholder
  double cdgb;	// dqds_vgb
  double cdsb;	// dqds_vsb
  double cddb;	// dqds_vdb
  double qbulk;	// raw
  double cbs;	// dqbs_vbs placeholder
  double cbgb;	// dqbs_vbg
  double cbsb;	// dqbs_vsb
  double cbdb;	// dqbs_vdb
  double qbs;	// Qbs forward
  double cbsbs;	// dqbs_vbs placeholder
  double cbsgb;	// dqbs_vbg
  double cbssb;	// dqbs_vsb
  double cbsdb;	// dqbs_vdb
  double qbd;	// Qbd reverse
  double cbdbd;	// dqbd_vbd placeholder
  double cbdgb;	// dqbd_vbg
  double cbdsb;	// dqbd_vsb
  double cbddb;	// dqbd_vdb
  double gtau;	// 
  double cqgb;	// 
  double cqsb;	// 
  double cqdb;	// 
  double cqbb;	// 
  double vgs;	// terminal voltages
  double vds;	// 
  double vbs;	// 
  double vdsat;	// saturation voltage
  double vgst;	// vgs - von.
  double von;	// actual threshold voltage
  double dgmdw; // dgm/dSDP::weff
  double dgmdl;
  bool reversed;	// flag: Vgs < 0, reverse s & d
  bool cutoff;	// flag: in cut off region
  bool subthreshold;	// flag: subthreshold region
  bool saturated;	// flag: in saturation region
  bool sbfwd;	// flag: sb diode fwd biased
  bool punchthru;	// flag: punch thru region
public: // netlist
  COMPONENT* _Rs;
  COMPONENT* _Rd;
  COMPONENT* _Ddb;
  COMPONENT* _Dsb;
  COMPONENT* _Cgs;
  COMPONENT* _Cgd;
  COMPONENT* _Cgb;
  COMPONENT* _Cqgs;
  COMPONENT* _Cqgd;
  COMPONENT* _Cqds;
  COMPONENT* _Cqbs;
  COMPONENT* _Cqbd;
  COMPONENT* _BTI;
  COMPONENT* _HCI;
  COMPONENT* _Ids;
  COMPONENT* _Idb;
  COMPONENT* _Isb;
private: // node list
  enum {n_d, n_g, n_s, n_b, n_id, n_is};
  node_t _nodes[6];
  std::string port_name(uint_t i)const {
    assert(i != INVALID_NODE);
    assert(i < 4);
    static std::string names[] = {"d", "g", "s", "b", ""};
    return names[i];
  }
private:
  void tt_begin();
  void do_tt();
  void tt_advance();
  void tt_accept();
protected:
  virtual  void tr_save_amps(int trstep); //
public:
  COMPONENT* BTI() const { return(_BTI); } // HACK.
  COMPONENT* bti_device() const { return(_BTI); } // HACK.
  COMPONENT* hci_device() const { return(_HCI); } // HACK.
  void tr_stress_last( );
};
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
}
#endif
