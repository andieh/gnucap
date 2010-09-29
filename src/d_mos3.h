/* $Id: d_mos3.model,v 22.1 2002/04/28 05:19:52 al Exp $ -*- C++ -*-
 * Copyright (C) 2001 Albert Davis
 * Author: Albert Davis <aldavis@ieee.org>
 *
 * This file is part of "Gnucap", the Gnu Circuit Analysis Package
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *------------------------------------------------------------------
 * mos model equations: spice level 3 equivalent
 */
/* This file is automatically generated. DO NOT EDIT */
#ifndef D_MOS3_H_INCLUDED
#define D_MOS3_H_INCLUDED

#include "d_mos123.h"
/*--------------------------------------------------------------------------*/
class SDP_MOS3
  :public SDP_MOS123{
public:
  explicit SDP_MOS3(const COMMON_COMPONENT*);
public:
};
/*--------------------------------------------------------------------------*/
class TDP_MOS3
  :public TDP_MOS123{
public:
  explicit TDP_MOS3(const DEV_MOS*);
public:
  double vt;	// 
  double phi;	// 
  double sqrt_phi;	// 
  double beta;	// 
  double uo;	// 
  double vbi;	// 
};
/*--------------------------------------------------------------------------*/
class MODEL_MOS3
  :public MODEL_MOS123{
public:
  // using generated copy constructor, should be unreachable
  explicit MODEL_MOS3();
  ~MODEL_MOS3() {--_count;}
public: // override virtual
  bool      parse_front(CS&);
  bool      parse_params(CS&);
  void      parse_finish();
  SDP_CARD* new_sdp(const COMMON_COMPONENT* c)const;
  void      print_front(OMSTREAM&)const;
  void      print_params(OMSTREAM&)const;
  void      print_calculated(OMSTREAM&)const;
  bool      is_valid(const COMMON_COMPONENT*)const;
  void      tr_eval(COMPONENT*)const;
public: // not virtual
  static int count() {return _count;}
private: // strictly internal
  enum {LEVEL=3};
  static int _count;
public: // input parameters
  double kp;	// transconductance parameter
  double nfs;	// fast surface state density
  double vmax;	// max drift velocity of carriers
  double theta;	// mobility modulation
  double eta;	// static feedback
  double kappa;	// saturation field vector
  double delta;	// width effect on threshold voltage
public: // calculated parameters
  bool calc_kp;	// 
  double alpha;	// 
  double xd;	// coeffDepLayWidth
  double cfsox;	// 
  double delta3;	// narrow factor
};
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
#endif