/* $Id: d_mos8.cc,v 1.12 2010-09-07 07:46:20 felix Exp $ -*- C++ -*-
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
 * Berkeley BSIM3v3.3 model
 **********  derived from.........
 * Copyright 2004 Regents of the University of California. All rights reserved.
 * File: b3ld.c of BSIM3v3.3.0
 * Author: 1991 JianHui Huang and Min-Chie Jeng.
 * Modified by Mansun Chan (1995).
 * Author: 1997-1999 Weidong Liu.
 * Author: 2001 Xuemei Xi
 * Modified by Xuemei Xi, 10/05, 12/21, 2001.
 * Modified by Xuemei Xi, 07/29/2005.
 **********
 * Recoded for Gnucap model compiler, Al Davis, 2006
 */
/* This file is not automatically generated. */

#include "l_compar.h"
#include "l_denoise.h"
#include "globals.h"
#include "e_elemnt.h"
#include "d_mos8.h"
#include "d_bti.h"
#include "e_adp.h"
#include "e_adplist.h"
#include "u_nodemap.h" // fixme

/*--------------------------------------------------------------------------*/
const double NA(NOT_INPUT);
const double INF(BIGBIG);
/*--------------------------------------------------------------------------*/
int MODEL_BUILT_IN_MOS8::_count = 0;
/*--------------------------------------------------------------------------*/
const int LEVEL(8);
/*--------------------------------------------------------------------------*/
namespace MODEL_BUILT_IN_MOS8_DISPATCHER { 
  static DEV_BUILT_IN_MOS p1d;
  static MODEL_BUILT_IN_MOS8 p1(&p1d);
  static DISPATCHER<MODEL_CARD>::INSTALL
    d1(&model_dispatcher, "nmos8|pmos8|nmos49|pmos49", &p1);
}
/*--------------------------------------------------------------------------*/
void SDP_BUILT_IN_MOS8::init(const COMMON_COMPONENT* cc)
{
  assert(cc);
  SDP_BUILT_IN_MOS_BASE::init(cc);
  const COMMON_BUILT_IN_MOS* c = prechecked_cast<const COMMON_BUILT_IN_MOS*>(cc);
  assert(c);
  const MODEL_BUILT_IN_MOS8* m = prechecked_cast<const MODEL_BUILT_IN_MOS8*>(c->model());
  assert(m);
  const CARD_LIST* par_scope = m->scope();
  assert(par_scope);

      {
	double T0 = pow(c->l_in, m->Lln);
	double T1 = pow(c->w_in, m->Lwn);
	double tmp1 = m->Ll / T0 + m->Lw / T1 + m->Lwl / (T0 * T1);
	dl = m->Lint + tmp1;
	dlc = m->dlc + tmp1;
      }
      {
	double T2 = pow(c->l_in, m->Wln);
	double T3 = pow(c->w_in, m->Wwn);
	double tmp2 = m->Wl / T2 + m->Ww / T3 + m->Wwl / (T2 * T3);
	dw = m->Wint + tmp2;
	dwc = m->dwc + tmp2;
      }

      leff = c->l_in - 2.0 * dl;
      weff = c->w_in - 2.0 * dw;
      leffCV = c->l_in - 2.0 * dlc;
      weffCV = c->w_in - 2.0 * dwc;
      cgate = m->cox * w_eff * l_eff; /* BUG:: not adjusted values?? */
      double L = leff;
      double W = weff;
      if (m->binUnit == 1) {
	L /= MICRON2METER;
	W /= MICRON2METER;
      }
  // adjust: override
  // adjust: raw
  cdsc = m->cdsc(L, W, 2.4e-4, par_scope);
  cdscb = m->cdscb(L, W, 0.0, par_scope);
  cdscd = m->cdscd(L, W, 0.0, par_scope);
  cit = m->cit(L, W, 0.0, par_scope);
  nfactor = m->nfactor(L, W, 1, par_scope);
  xj = m->xj(L, W, .15e-6, par_scope);
  vsat = m->vsat(L, W, 8.0e4, par_scope);
  at = m->at(L, W, 3.3e4, par_scope);
  a0 = m->a0(L, W, 1.0, par_scope);
  ags = m->ags(L, W, 0.0, par_scope);
  a1 = m->a1(L, W, 0.0, par_scope);
  a2 = m->a2(L, W, 1.0, par_scope);
  keta = m->keta(L, W, -0.047, par_scope);
  nsub = m->nsub(L, W, 6.0e16, par_scope);
  npeak = m->npeak(L, W, NA, par_scope);
  ngate = m->ngate(L, W, 0.0, par_scope);
  gamma1 = m->gamma1(L, W, NA, par_scope);
  gamma2 = m->gamma2(L, W, NA, par_scope);
  vbx = m->vbx(L, W, NA, par_scope);
  vbm = m->vbm(L, W, -3.0, par_scope);
  xt = m->xt(L, W, 1.55e-7, par_scope);
  k1 = m->k1(L, W, NA, par_scope);
  kt1 = m->kt1(L, W, -0.11, par_scope);
  kt1l = m->kt1l(L, W, 0.0, par_scope);
  kt2 = m->kt2(L, W, 0.022, par_scope);
  k2 = m->k2(L, W, NA, par_scope);
  k3 = m->k3(L, W, 80.0, par_scope);
  k3b = m->k3b(L, W, 0.0, par_scope);
  w0 = m->w0(L, W, 2.5e-6, par_scope);
  nlx = m->nlx(L, W, 1.74e-7, par_scope);
  dvt0 = m->dvt0(L, W, 2.2, par_scope);
  dvt1 = m->dvt1(L, W, 0.53, par_scope);
  dvt2 = m->dvt2(L, W, -0.032, par_scope);
  dvt0w = m->dvt0w(L, W, 0.0, par_scope);
  dvt1w = m->dvt1w(L, W, 5.3e6, par_scope);
  dvt2w = m->dvt2w(L, W, -0.032, par_scope);
  drout = m->drout(L, W, 0.56, par_scope);
  dsub = m->dsub(L, W, drout, par_scope);
    if (dsub == NA) {
      dsub = drout;
    }else{
    }
  vth0 = m->vth0(L, W, NA, par_scope);
    if (vth0 == NA) {
      vth0 = NA;
    }else{
    }
  ua1 = m->ua1(L, W, 4.31e-9, par_scope);
  ua = m->ua(L, W, 2.25e-9, par_scope);
  ub1 = m->ub1(L, W, -7.61e-18, par_scope);
  ub = m->ub(L, W, 5.87e-19, par_scope);
  uc1 = m->uc1(L, W, ((m->mobMod==3) ? -0.056 : -0.056e-9), par_scope);
    if (uc1 == NA) {
      uc1 = ((m->mobMod==3) ? -0.056 : -0.056e-9);
    }else{
    }
  uc = m->uc(L, W, ((m->mobMod==3) ? -0.0465 : -0.0465e-9), par_scope);
    if (uc == NA) {
      uc = ((m->mobMod==3) ? -0.0465 : -0.0465e-9);
    }else{
    }
  u0 = m->u0(L, W, ((m->polarity == pN) ? 0.067 : 0.025), par_scope);
    if (u0 == NA) {
      u0 = ((m->polarity == pN) ? 0.067 : 0.025);
    }else{
    }
  ute = m->ute(L, W, -1.5, par_scope);
  voff = m->voff(L, W, -0.08, par_scope);
  delta = m->delta(L, W, 0.01, par_scope);
  rdsw = m->rdsw(L, W, 0.0, par_scope);
  prwg = m->prwg(L, W, 0.0, par_scope);
  prwb = m->prwb(L, W, 0.0, par_scope);
  prt = m->prt(L, W, 0.0, par_scope);
  eta0 = m->eta0(L, W, 0.08, par_scope);
  etab = m->etab(L, W, -0.07, par_scope);
  pclm = m->pclm(L, W, 1.3, par_scope);
  pdibl1 = m->pdibl1(L, W, .39, par_scope);
  pdibl2 = m->pdibl2(L, W, 0.0086, par_scope);
  pdiblb = m->pdiblb(L, W, 0.0, par_scope);
  pscbe1 = m->pscbe1(L, W, 4.24e8, par_scope);
  pscbe2 = m->pscbe2(L, W, 1.0e-5, par_scope);
  pvag = m->pvag(L, W, 0.0, par_scope);
  wr = m->wr(L, W, 1.0, par_scope);
  dwg = m->dwg(L, W, 0.0, par_scope);
  dwb = m->dwb(L, W, 0.0, par_scope);
  b0 = m->b0(L, W, 0.0, par_scope);
  b1 = m->b1(L, W, 0.0, par_scope);
  alpha0 = m->alpha0(L, W, 0.0, par_scope);
  trace1("SDP_BUILT_IN_MOS_BASE::init", alpha0);
  beta0 = m->beta0(L, W, 30.0, par_scope);
  elm = m->elm(L, W, 5.0, par_scope);
  vfbcv = m->vfbcv(L, W, -1.0, par_scope);
  cgsl = m->cgsl(L, W, 0.0, par_scope);
  cgdl = m->cgdl(L, W, 0.0, par_scope);
  ckappa = m->ckappa(L, W, 0.6, par_scope);
  cf = m->cf(L, W, 2.0 * P_EPS_OX / M_PI * log(1.0 + 0.4e-6 / m->tox), par_scope);
    if (cf == NA) {
      cf = 2.0 * P_EPS_OX / M_PI * log(1.0 + 0.4e-6 / m->tox);
    }else{
    }
  clc = m->clc(L, W, 0.1e-6, par_scope);
  cle = m->cle(L, W, 0.6, par_scope);
  vfb = m->vfb(L, W, NA, par_scope);
  acde = m->acde(L, W, 1.0, par_scope);
    //acde = std::max(acde, 0.4);
    //acde = std::min(acde, 1.6);
  moin = m->moin(L, W, 15.0, par_scope);
    //moin = std::max(moin, 5.0);
    //moin = std::min(moin, 25.0);
  noff = m->noff(L, W, 1.0, par_scope);
    //noff = std::max(noff, 0.1);
    //noff = std::min(noff, 4.0);
  voffcv = m->voffcv(L, W, 0.0, par_scope);
    //voffcv = std::max(voffcv, -0.5);
    //voffcv = std::min(voffcv, 0.5);
  alpha1 = m->alpha1(L, W, 0.0, par_scope);
  // adjust: calculated
    abulkCVfactor = 1.0 + pow((clc / leff), cle);
    litl = sqrt(3.0 * xj * m->tox);
  // code_post

      cgso = (m->cgso + cf) * weffCV;
      cgdo = (m->cgdo + cf) * weffCV;
      cgbo = m->cgbo * leffCV;

      if (u0 > 1.0) {
	u0 /= 1.0e4;
      }
      if (m->npeak.nom() == NA) {
	if (m->gamma1.nom() != NA) {
	  double T0 = gamma1 * m->cox;
	  npeak = 3.021E22 * T0 * T0;
	}else{
	  npeak = 1.7e17;
	}
      }
      if (m->k1.nom() != NA && m->k2.nom() != NA) {
	if (m->k1.nom() == NA) {
	  k1 = 0.53;
	}
	if (m->k2.nom() == NA) {
	  k2 = -0.0186;
	}
      }else{
	vbm = -std::abs(vbm);
	if (m->gamma1.nom() == NA) {
	  gamma1 = 5.753e-12 * sqrt(npeak) / m->cox;
	}
	if (m->gamma2.nom() == NA) {
	  gamma2 = 5.753e-12 * sqrt(nsub) / m->cox;
	}
      }

      // version 3.3
      acde *= pow((npeak / 2.0e16), -0.25);
      ldeb = sqrt(P_EPS_SI * m->vt_at_tnom / (P_Q * npeak * 1.0e6)) / 3.0;
}
/*--------------------------------------------------------------------------*/
TDP_BUILT_IN_MOS8::TDP_BUILT_IN_MOS8(const DEV_BUILT_IN_MOS* d)
  :TDP_BUILT_IN_MOS_BASE(d)
{
  assert(d);
  const COMMON_BUILT_IN_MOS* c = prechecked_cast<const COMMON_BUILT_IN_MOS*>(d->common());
  assert(c);
  const SDP_BUILT_IN_MOS8* s = prechecked_cast<const SDP_BUILT_IN_MOS8*>(c->sdp());
  assert(s);
  const ADP_BUILT_IN_MOS8* a = (const ADP_BUILT_IN_MOS8*)(d->adp());
  assert(a); USE(a);
  const MODEL_BUILT_IN_MOS8* m = prechecked_cast<const MODEL_BUILT_IN_MOS8*>(c->model());
  assert(m);
  const CARD_LIST* par_scope = d->scope();
  assert(par_scope); USE(par_scope);

  double L = s->leff;
  double W = s->weff;
    // final adjust: code_pre

      temp = d->_sim->_temp_c + P_CELSIUS0;
      double egap = 1.16 - 7.02e-4 * temp * temp / (temp + 1108.0);
    // final adjust: override
    // final adjust: raw
    // final adjust: mid
    // final adjust: calculated
    tempratio = temp / m->tnom_k;
    tempratio_1 = tempratio - 1;
    vtm = temp * P_K_Q;
    // final adjust: post

      const double EXP_THRESHOLD = 34.0;
      const double MIN_EXP = 1.713908431e-15;

      double jctTempSatCurDensity;
      double jctSidewallTempSatCurDensity;
      if (temp != m->tnom_k) {
	double T0 = m->egap / m->vt_at_tnom - egap / vtm + m->jctTempExponent
	  * log(temp / m->tnom_k);
	double T1 = exp(T0 / m->jctEmissionCoeff);
	jctTempSatCurDensity = m->js * T1;
	jctSidewallTempSatCurDensity = m->jctSidewallSatCurDensity * T1;
      }else{
	jctTempSatCurDensity = m->js;
	jctSidewallTempSatCurDensity = m->jctSidewallSatCurDensity;
      }
      if (jctTempSatCurDensity < 0.0) {
	jctTempSatCurDensity = 0.0;
      }
      if (jctSidewallTempSatCurDensity < 0.0) {
	jctSidewallTempSatCurDensity = 0.0;
      }
      {
	double T0 = (tempratio - 1.0);
	ua = s->ua + s->ua1 * T0;
	dua_dW = m->ua.dW(L,W,par_scope) + m->ua1.dW(L,W,par_scope) * T0;
	dua_dL = m->ua.dL(L,W,par_scope) + m->ua1.dL(L,W,par_scope) * T0;
	ub = s->ub + s->ub1 * T0;
	dub_dW = m->ub.dW(L,W,par_scope) + m->ub1.dW(L,W,par_scope) * T0;
	dub_dL = m->ub.dL(L,W,par_scope) + m->ub1.dL(L,W,par_scope) * T0;
	uc = s->uc + s->uc1 * T0;
	duc_dW = m->uc.dW(L,W,par_scope) + m->uc1.dW(L,W,par_scope) * T0;
	duc_dL = m->uc.dL(L,W,par_scope) + m->uc1.dL(L,W,par_scope) * T0;
	u0temp = s->u0 * pow(tempratio, s->ute); 
	vsattemp = s->vsat - s->at * T0;
	rds0 = (s->rdsw + s->prt * T0) / pow(s->weff * 1E6, s->wr);
	drds0_dW = (m->rdsw.dW(L,W,par_scope) + m->prt.dW(L, W, par_scope) * T0) / pow(s->weff * 1E6, s->wr)
	         + (s->rdsw + s->prt * T0) / pow(s->weff * 1E6, 2.*s->wr) * s->wr * pow(s->weff * 1E6, s->wr-1.);
	         // assuming wr is constant.
	drds0_dL = (m->rdsw.dL(L,W,par_scope) + m->prt.dL(L, W, par_scope) * T0) / pow(s->weff * 1E6, s->wr);
	         // assuming wr is constant.
	if(rds0 < 0){ rds0 = drds0_dW = drds0_dL = 0.; }
      }
      double dnpeak_dW = 0; // SDP. set 0 anyway (BUG?)
      double dnpeak_dL = 0; // SDP. set 0 anyway (BUG?)
      phi = 2.0 * m->vt_at_tnom * log(s->npeak / m->ni);
      double dphi_dW = 2.0 * m->vt_at_tnom * 1./(s->npeak / m->ni) * dnpeak_dW;// 0, for now
      double dphi_dL = 2.0 * m->vt_at_tnom * 1./(s->npeak / m->ni) * dnpeak_dL;// 0, for now
      sqrtPhi = sqrt(phi);
      double dsqrtPhi_dL = 0; // SDP. set 0 anyway (BUG?)
      double dsqrtPhi_dW = 0; // SDP. set 0 anyway (BUG?)
      phis3 = sqrtPhi * phi;
      Xdep0 = sqrt(2.0 * P_EPS_SI / (P_Q * s->npeak * 1.0e6)) * sqrtPhi;
      vbi = m->vt_at_tnom * log(1.0e20 * s->npeak / (m->ni * m->ni));
      cdep0 = sqrt(P_Q * P_EPS_SI * s->npeak * 1.0e6 / 2.0 / phi);

      if (m->k1.nom() != NA && m->k2.nom() != NA) {
	k2 = s->k2;
	k1 = s->k1;
      }else{
	double vbx = (m->vbx.nom() == NA)
	  ? -std::abs(phi - 7.7348e-4 * s->npeak * s->xt * s->xt)
	  : -std::abs(s->vbx);
	double T0 = s->gamma1 - s->gamma2;
	double T1 = sqrt(phi - vbx) - sqrtPhi;
	double T2 = sqrt(phi * (phi - s->vbm)) - phi;
	k2 = T0 * T1 / (2.0 * T2 + s->vbm);
	k1 = s->gamma2 - 2.0 * k2 * sqrt(phi - s->vbm);
      }
      double dk1_dW = 0; // for now.
      double dk1_dL = 0; // for now.
      k1ox = k1 * m->tox / m->toxm;
      k2ox = k2 * m->tox / m->toxm;

      if (k2 < 0.) {
	double T0 = 0.5 * k1 / k2;
	vbsc = to_range(-30.0, (0.9 * (phi - T0 * T0)), -3.0);
      }else{
	vbsc = -30.0;
      }
      vbsc = std::min(vbsc, s->vbm);
      if (s->vfb == NA) {
	if (s->vth0 == NA) {
	  vfb = -1.0;
	  dvfb_dW = 0;
	  dvfb_dL = 0;
	}else{
	  vfb = m->polarity * s->vth0 - phi - k1 * sqrtPhi;
	  double L=s->leff;
	  double W=s->weff;
	  dvfb_dW = m->polarity * m->vth0.dW(L, W, par_scope) - dphi_dW - k1 * dsqrtPhi_dW - dk1_dW * sqrtPhi;
	  dvfb_dL = m->polarity * m->vth0.dL(L, W, par_scope) - dphi_dL - k1 * dsqrtPhi_dL - dk1_dL * sqrtPhi;
	}
      }else{
	vfb = s->vfb;
	dvfb_dW = m->vfb.dW(L, W, par_scope);
	dvfb_dL = m->vfb.dL(L, W, par_scope);
	trace1("", s->vfb);
      }
      if (s->vth0 == NA) {
	vth0 = m->polarity * (vfb + phi + k1 * sqrtPhi);
	dvth0_dW = m->polarity * (dvfb_dW + dphi_dW + dk1_dW * sqrtPhi + k1 * dsqrtPhi_dW);
	dvth0_dL = m->polarity * (dvfb_dL + dphi_dL + dk1_dL * sqrtPhi + k1 * dsqrtPhi_dL);
      }else{
	vth0 = s->vth0;
	dvth0_dW = m->vth0.dW(L, W, par_scope);
	dvth0_dL = m->vth0.dL(L, W, par_scope);
      }

//       vth0 *= ( exp( a-> ));
      trace3("", s->vth0, vth0, vfb);
      {
	double T1 = sqrt(P_EPS_SI / P_EPS_OX * m->tox * Xdep0);
	double dT1_dW = 0.; // constant npeak
	double dT1_dL = 0.; // constant npeak
	double T0 = exp(-0.5 * s->dsub * s->leff / T1);
	double dT0_dW, dT0_dL;

	double test = m->dsub(L, W, s->drout, par_scope);
	if (test == NA) { // weird hack from SDP
	  dT0_dW = - T0 * 0.5 * ( m->drout.dW(L,W,par_scope) * s->leff ) / T1;
	  dT0_dL = - T0 * 0.5 * ( m->drout.dL(L,W,par_scope) * s->leff + s->drout ) / T1;
	}else{
	  dT0_dW = - T0 * 0.5 * ( m->dsub.dW(L,W,par_scope) * s->leff ) / T1;
	  dT0_dL = - T0 * 0.5 * ( m->dsub.dL(L,W,par_scope) * s->leff + s->dsub ) / T1;
	}
	theta0vb0 = (T0 + 2.0 * T0 * T0);
	dtheta0vb0_dW = dT0_dW * (1. + 4.0 * T0);
	dtheta0vb0_dL = dT0_dL * (1. + 4.0 * T0);

	T0 = exp(-0.5 * s->drout * s->leff / T1);
	dT0_dW = - T0 * .5 * ( m->drout.dW(L,W,par_scope) * s->leff / T1 - s->drout * s->leff / T1 / T1 * dT1_dW );
	dT0_dL = - exp(-0.5 * s->drout * s->leff / T1)
	                * 0.5 * ( m->drout.dL(L,W,par_scope) * s->leff / T1
			        + s->drout/T1 - s->drout * s->leff / T1 / T1 * dT1_dL );
	double T2 = T0 * (1. + 2. * T0);
	double dT2_dW = dT0_dW * ( 1. + 4.0 * T0);
	double dT2_dL = dT0_dL + 4.0 * T0 * dT0_dL;
	thetaRout = s->pdibl1 * T2 + s->pdibl2;
	dthetaRout_dW = m->pdibl1.dW(L,W,par_scope) * T2 + s->pdibl1 * dT2_dW + m->pdibl2.dW(L,W,par_scope);
	dthetaRout_dL = m->pdibl1.dL(L,W,par_scope) * T2 + s->pdibl1 * dT2_dL + m->pdibl2.dL(L,W,par_scope);
      }

      { // vfbzb
	double tmp1 = vbi - phi;
	double tmp2 = m->factor1 * sqrt(Xdep0);
	
	double T2;
	{
	  double T0 = -0.5 * s->dvt1w * s->weff * s->leff / tmp2;
	  double T1 = (T0 > -EXP_THRESHOLD) ? exp(T0) : MIN_EXP;
	  T2 = T1 * (1.0 + 2.0 * T1);
	  T0 = s->dvt0w * T2;
	  T2 = T0 * tmp1;
	}
	double T3;
	{
	  double T0 = -0.5 * s->dvt1 * s->leff / tmp2;
	  double T1 = (T0 > -EXP_THRESHOLD) ? exp(T0) : MIN_EXP;
	  double t2 = T1 * (1.0 + 2.0 * T1);
	  T3 = s->dvt0 * t2 * tmp1;
	}
	double T4 = m->tox * phi / (s->weff + s->w0);
	double T5;
	{
	  double T0 = sqrt(1.0 + s->nlx / s->leff);
	  T5 = k1ox * (T0 - 1.0) * sqrtPhi
	    + (s->kt1 + s->kt1l / s->leff) * (tempratio - 1.0);
	}
	{
	  double tmp3 = m->polarity * vth0 - T2 - T3 + s->k3 * T4 + T5;
	  vfbzb = tmp3 - phi - k1 * sqrtPhi;
	}
      }
    // final adjust: done
}
/*--------------------------------------------------------------------------*/
MODEL_BUILT_IN_MOS8::MODEL_BUILT_IN_MOS8(const BASE_SUBCKT* p)
  :MODEL_BUILT_IN_MOS_BASE(p),
   cdsc(2.4e-4),
   cdscb(0.0),
   cdscd(0.0),
   cit(0.0),
   nfactor(1),
   xj(.15e-6),
   vsat(8.0e4),
   at(3.3e4),
   a0(1.0),
   ags(0.0),
   a1(0.0),
   a2(1.0),
   keta(-0.047),
   nsub(6.0e16),
   npeak(NA),
   ngate(0.0),
   gamma1(NA),
   gamma2(NA),
   vbx(NA),
   vbm(-3.0),
   xt(1.55e-7),
   k1(NA),
   kt1(-0.11),
   kt1l(0.0),
   kt2(0.022),
   k2(NA),
   k3(80.0),
   k3b(0.0),
   w0(2.5e-6),
   nlx(1.74e-7),
   dvt0(2.2),
   dvt1(0.53),
   dvt2(-0.032),
   dvt0w(0.0),
   dvt1w(5.3e6),
   dvt2w(-0.032),
   drout(0.56),
   dsub(NA),
   vth0(NA),
   ua1(4.31e-9),
   ua(2.25e-9),
   ub1(-7.61e-18),
   ub(5.87e-19),
   uc1(NA),
   uc(NA),
   u0(NA),
   ute(-1.5),
   voff(-0.08),
   delta(0.01),
   rdsw(0.0),
   prwg(0.0),
   prwb(0.0),
   prt(0.0),
   eta0(0.08),
   etab(-0.07),
   pclm(1.3),
   pdibl1(.39),
   pdibl2(0.0086),
   pdiblb(0.0),
   pscbe1(4.24e8),
   pscbe2(1.0e-5),
   pvag(0.0),
   wr(1.0),
   dwg(0.0),
   dwb(0.0),
   b0(0.0),
   b1(0.0),
   alpha0(0.0), // aging important 
   beta0(30.0),
   elm(5.0),
   vfbcv(-1.0),
   cgsl(0.0),
   cgdl(0.0),
   ckappa(0.6),
   cf(NA),
   clc(0.1e-6),
   cle(0.6),
   vfb(NA),
   acde(1.0),
   moin(15.0),
   noff(1.0),
   voffcv(0.0),
   alpha1(0.0),
   capMod(3),
   nqsMod(0),
   mobMod(1),
   noiMod(1),
   paramChk(0),
   binUnit(1),
   version(3.3),
   tox(150.0e-10),
   xpart(0.0),
   jctSidewallSatCurDensity(0.0),
   mjswg(NA),
   pbswg(NA),
   unitLengthGateSidewallJctCap(NA),
   jctEmissionCoeff(1.0),
   jctTempExponent(3.0),
   Lint(0.0),
   Ll(0.0),
   Lln(1.0),
   Lw(0.0),
   Lwn(1.0),
   Lwl(0.0),
   Wint(0.0),
   Wl(0.0),
   Wln(1.0),
   Ww(0.0),
   Wwn(1.0),
   Wwl(0.0),
   dwc(NA),
   dlc(NA),
   noia(NA),
   noib(NA),
   noic(NA),
   em(4.1e7),
   ef(1.0),
   acnqsMod(0),
   toxm(tox),
   lintnoi(0.0),
   ijth(0.1),
   tpb(0.0),
   tcj(0.0),
   tpbsw(0.0),
   tcjsw(0.0),
   tpbswg(0.0),
   tcjswg(0.0),
   Llc(Ll),
   Lwc(Lw),
   Lwlc(Lwl),
   Wlc(Wl),
   Wwc(Ww),
   Wwlc(Wwl),
   acm(10),
   h0(NA),
   hci_m(3),
   hci_n(.3),
   cox(NA),
   factor1(NA),
   ni(NA)
   //vt_at_nom(NA)
{
  if (ENV::run_mode != rPRE_MAIN) {
    ++_count;
  }else{
  }
  set_default(&mjsw, NA);
  set_default(&pb, NA);
  set_default(&pbsw, NA);
  set_default(&cjo, 5.0E-4);
  set_default(&cgdo, NA);
  set_default(&cgso, NA);
  set_default(&cgbo, NA);
  set_default(&mos_level, LEVEL);
}
/*--------------------------------------------------------------------------*/
MODEL_BUILT_IN_MOS8::MODEL_BUILT_IN_MOS8(const MODEL_BUILT_IN_MOS8& p)
  :MODEL_BUILT_IN_MOS_BASE(p),
   cdsc(p.cdsc),
   cdscb(p.cdscb),
   cdscd(p.cdscd),
   cit(p.cit),
   nfactor(p.nfactor),
   xj(p.xj),
   vsat(p.vsat),
   at(p.at),
   a0(p.a0),
   ags(p.ags),
   a1(p.a1),
   a2(p.a2),
   keta(p.keta),
   nsub(p.nsub),
   npeak(p.npeak),
   ngate(p.ngate),
   gamma1(p.gamma1),
   gamma2(p.gamma2),
   vbx(p.vbx),
   vbm(p.vbm),
   xt(p.xt),
   k1(p.k1),
   kt1(p.kt1),
   kt1l(p.kt1l),
   kt2(p.kt2),
   k2(p.k2),
   k3(p.k3),
   k3b(p.k3b),
   w0(p.w0),
   nlx(p.nlx),
   dvt0(p.dvt0),
   dvt1(p.dvt1),
   dvt2(p.dvt2),
   dvt0w(p.dvt0w),
   dvt1w(p.dvt1w),
   dvt2w(p.dvt2w),
   drout(p.drout),
   dsub(p.dsub),
   vth0(p.vth0),
   ua1(p.ua1),
   ua(p.ua),
   ub1(p.ub1),
   ub(p.ub),
   uc1(p.uc1),
   uc(p.uc),
   u0(p.u0),
   ute(p.ute),
   voff(p.voff),
   delta(p.delta),
   rdsw(p.rdsw),
   prwg(p.prwg),
   prwb(p.prwb),
   prt(p.prt),
   eta0(p.eta0),
   etab(p.etab),
   pclm(p.pclm),
   pdibl1(p.pdibl1),
   pdibl2(p.pdibl2),
   pdiblb(p.pdiblb),
   pscbe1(p.pscbe1),
   pscbe2(p.pscbe2),
   pvag(p.pvag),
   wr(p.wr),
   dwg(p.dwg),
   dwb(p.dwb),
   b0(p.b0),
   b1(p.b1),
   alpha0(p.alpha0),
   beta0(p.beta0),
   elm(p.elm),
   vfbcv(p.vfbcv),
   cgsl(p.cgsl),
   cgdl(p.cgdl),
   ckappa(p.ckappa),
   cf(p.cf),
   clc(p.clc),
   cle(p.cle),
   vfb(p.vfb),
   acde(p.acde),
   moin(p.moin),
   noff(p.noff),
   voffcv(p.voffcv),
   alpha1(p.alpha1),
   capMod(p.capMod),
   nqsMod(p.nqsMod),
   mobMod(p.mobMod),
   noiMod(p.noiMod),
   paramChk(p.paramChk),
   binUnit(p.binUnit),
   version(p.version),
   tox(p.tox),
   xpart(p.xpart),
   jctSidewallSatCurDensity(p.jctSidewallSatCurDensity),
   mjswg(p.mjswg),
   pbswg(p.pbswg),
   unitLengthGateSidewallJctCap(p.unitLengthGateSidewallJctCap),
   jctEmissionCoeff(p.jctEmissionCoeff),
   jctTempExponent(p.jctTempExponent),
   Lint(p.Lint),
   Ll(p.Ll),
   Lln(p.Lln),
   Lw(p.Lw),
   Lwn(p.Lwn),
   Lwl(p.Lwl),
   Wint(p.Wint),
   Wl(p.Wl),
   Wln(p.Wln),
   Ww(p.Ww),
   Wwn(p.Wwn),
   Wwl(p.Wwl),
   dwc(p.dwc),
   dlc(p.dlc),
   noia(p.noia),
   noib(p.noib),
   noic(p.noic),
   em(p.em),
   ef(p.ef),
   acnqsMod(p.acnqsMod),
   toxm(p.toxm),
   lintnoi(p.lintnoi),
   ijth(p.ijth),
   tpb(p.tpb),
   tcj(p.tcj),
   tpbsw(p.tpbsw),
   tcjsw(p.tcjsw),
   tpbswg(p.tpbswg),
   tcjswg(p.tcjswg),
   Llc(p.Llc),
   Lwc(p.Lwc),
   Lwlc(p.Lwlc),
   Wlc(p.Wlc),
   Wwc(p.Wwc),
   Wwlc(p.Wwlc),
   acm(p.acm),
   h0(p.h0),
   hci_m(p.hci_m),
   hci_n(p.hci_n),
   cox(p.cox),
   factor1(p.factor1),
   vt_at_tnom(p.vt_at_tnom),
   ni(p.ni)
{
  if (ENV::run_mode != rPRE_MAIN) {
    ++_count;
  }else{untested();//194
  }
}
/*--------------------------------------------------------------------------*/
std::string MODEL_BUILT_IN_MOS8::dev_type()const
{
  if (polarity == pN) {
    return "nmos8";
  }else if (polarity == pP) {
    return "pmos8";
  }else if (polarity == pN) {
    return "nmos49";
  }else if (polarity == pP) {
    return "pmos49";
  }else{untested();//235
    return MODEL_BUILT_IN_MOS_BASE::dev_type();
  }
}
/*--------------------------------------------------------------------------*/
void MODEL_BUILT_IN_MOS8::set_dev_type(const std::string& new_type)
{
  if (Umatch(new_type, "nmos8 ")) {
    polarity = pN;
  }else if (Umatch(new_type, "pmos8 ")) {
    polarity = pP;
  }else if (Umatch(new_type, "nmos49 ")) {
    polarity = pN;
  }else if (Umatch(new_type, "pmos49 ")) {
    polarity = pP;
  }else{
    MODEL_BUILT_IN_MOS_BASE::set_dev_type(new_type);
  }
}
/*--------------------------------------------------------------------------*/
void MODEL_BUILT_IN_MOS8::precalc_first()
{
    const CARD_LIST* par_scope = scope();
    assert(par_scope);
    MODEL_BUILT_IN_MOS_BASE::precalc_first();
    e_val(&(this->capMod), 3, par_scope);
    e_val(&(this->nqsMod), 0, par_scope);
    e_val(&(this->mobMod), 1, par_scope);
    e_val(&(this->noiMod), 1, par_scope);
    e_val(&(this->paramChk), 0, par_scope);
    e_val(&(this->binUnit), 1, par_scope);
    e_val(&(this->version), 3.3, par_scope);
    e_val(&(this->tox), 150.0e-10, par_scope);
    e_val(&(this->xpart), 0.0, par_scope);
    e_val(&(this->h0), NA, par_scope);
    e_val(&(this->hci_m), 3., par_scope);
    e_val(&(this->hci_n), .3, par_scope);
    e_val(&(this->jctSidewallSatCurDensity), 0.0, par_scope);
    e_val(&(this->mjswg), NA, par_scope);
    e_val(&(this->pbswg), NA, par_scope);
    e_val(&(this->unitLengthGateSidewallJctCap), NA, par_scope);
    e_val(&(this->jctEmissionCoeff), 1.0, par_scope);
    e_val(&(this->jctTempExponent), 3.0, par_scope);
    e_val(&(this->Lint), 0.0, par_scope);
    e_val(&(this->Ll), 0.0, par_scope);
    e_val(&(this->Lln), 1.0, par_scope);
    e_val(&(this->Lw), 0.0, par_scope);
    e_val(&(this->Lwn), 1.0, par_scope);
    e_val(&(this->Lwl), 0.0, par_scope);
    e_val(&(this->Wint), 0.0, par_scope);
    e_val(&(this->Wl), 0.0, par_scope);
    e_val(&(this->Wln), 1.0, par_scope);
    e_val(&(this->Ww), 0.0, par_scope);
    e_val(&(this->Wwn), 1.0, par_scope);
    e_val(&(this->Wwl), 0.0, par_scope);
    e_val(&(this->dwc), NA, par_scope);
    e_val(&(this->dlc), NA, par_scope);
    e_val(&(this->noia), NA, par_scope);
    e_val(&(this->noib), NA, par_scope);
    e_val(&(this->noic), NA, par_scope);
    e_val(&(this->em), 4.1e7, par_scope);
    e_val(&(this->ef), 1.0, par_scope);
    e_val(&(this->acnqsMod), 0, par_scope);
    e_val(&(this->toxm), tox, par_scope);
    e_val(&(this->lintnoi), 0.0, par_scope);
    e_val(&(this->ijth), 0.1, par_scope);
    e_val(&(this->tpb), 0.0, par_scope);
    e_val(&(this->tcj), 0.0, par_scope);
    e_val(&(this->tpbsw), 0.0, par_scope);
    e_val(&(this->tcjsw), 0.0, par_scope);
    e_val(&(this->tpbswg), 0.0, par_scope);
    e_val(&(this->tcjswg), 0.0, par_scope);
    e_val(&(this->Llc), Ll, par_scope);
    e_val(&(this->Lwc), Lw, par_scope);
    e_val(&(this->Lwlc), Lwl, par_scope);
    e_val(&(this->Wlc), Wl, par_scope);
    e_val(&(this->Wwc), Ww, par_scope);
    e_val(&(this->Wwlc), Wwl, par_scope);
    e_val(&(this->acm), 10, par_scope);
    // final adjust: code_pre

      //tox = std::max(tox, 1e-20);
      cox = 3.453133e-11 / tox;
    // final adjust: override
    if (mjsw == NA) {
      mjsw = .33;
    }else{
    }
    if (pb == NA) {
      pb = 1.0;
    }else{
    }
    //pb = std::max(pb, 0.1);
    if (pbsw == NA) {
      pbsw = pb;
    }else{
    }
    //pbsw = std::max(pbsw, 0.1);
    if (cgdo == NA) {
      cgdo = (((dlc != NA) && (dlc > 0.0))
	  ? dlc * cox - cgdl.nom()
	  : 0.6 * xj.nom() * cox);
    }else{
    }
    if (cgso == NA) {
      cgso = (((dlc != NA) && (dlc > 0.0))
	  ? dlc * cox - cgsl.nom()
	  : 0.6 * xj.nom() * cox);
    }else{
    }
    if (cgbo == NA) {
      cgbo = ((dwc != NA)
	  ? 2.0 * dwc  * cox
	  : 2.0 * Wint * cox);
    }else{
    }
    cmodel = ((!cmodel)?0:cmodel);
    needs_isub = (alpha0.nom()!=0.);
    // final adjust: raw
    e_val(&(this->capMod), 3, par_scope);
    e_val(&(this->nqsMod), 0, par_scope);
    e_val(&(this->mobMod), 1, par_scope);
    e_val(&(this->noiMod), 1, par_scope);
    e_val(&(this->paramChk), 0, par_scope);
    e_val(&(this->binUnit), 1, par_scope);
    e_val(&(this->version), 3.3, par_scope);
    e_val(&(this->tox), 150.0e-10, par_scope);
    e_val(&(this->xpart), 0.0, par_scope);
    e_val(&(this->h0), NA, par_scope);
    e_val(&(this->hci_m), 3., par_scope);
    e_val(&(this->hci_n), .3, par_scope);
    e_val(&(this->jctSidewallSatCurDensity), 0.0, par_scope);
    e_val(&(this->mjswg), mjsw, par_scope);
    e_val(&(this->pbswg), pbsw, par_scope);
    //this->pbswg = std::max(pbswg, 0.1);
    e_val(&(this->unitLengthGateSidewallJctCap), cjsw, par_scope);
    e_val(&(this->jctEmissionCoeff), 1.0, par_scope);
    e_val(&(this->jctTempExponent), 3.0, par_scope);
    e_val(&(this->Lint), 0.0, par_scope);
    e_val(&(this->Ll), 0.0, par_scope);
    e_val(&(this->Lln), 1.0, par_scope);
    e_val(&(this->Lw), 0.0, par_scope);
    e_val(&(this->Lwn), 1.0, par_scope);
    e_val(&(this->Lwl), 0.0, par_scope);
    e_val(&(this->Wint), 0.0, par_scope);
    e_val(&(this->Wl), 0.0, par_scope);
    e_val(&(this->Wln), 1.0, par_scope);
    e_val(&(this->Ww), 0.0, par_scope);
    e_val(&(this->Wwn), 1.0, par_scope);
    e_val(&(this->Wwl), 0.0, par_scope);
    e_val(&(this->dwc), Wint, par_scope);
    e_val(&(this->dlc), Lint, par_scope);
    e_val(&(this->noia), (polarity==pN) ? 1e20 : 9.9e18, par_scope);
    e_val(&(this->noib), (polarity==pN) ? 5e4 : 2.4e3, par_scope);
    e_val(&(this->noic), (polarity==pN) ?-1.4e-12 :1.4e-12, par_scope);
    e_val(&(this->em), 4.1e7, par_scope);
    e_val(&(this->ef), 1.0, par_scope);
    e_val(&(this->acnqsMod), 0, par_scope);
    //this->acnqsMod = std::min(acnqsMod, 1);
    e_val(&(this->toxm), tox, par_scope);
    e_val(&(this->lintnoi), 0.0, par_scope);
    e_val(&(this->ijth), 0.1, par_scope);
    e_val(&(this->tpb), 0.0, par_scope);
    e_val(&(this->tcj), 0.0, par_scope);
    e_val(&(this->tpbsw), 0.0, par_scope);
    e_val(&(this->tcjsw), 0.0, par_scope);
    e_val(&(this->tpbswg), 0.0, par_scope);
    e_val(&(this->tcjswg), 0.0, par_scope);
    e_val(&(this->Llc), Ll, par_scope);
    e_val(&(this->Lwc), Lw, par_scope);
    e_val(&(this->Lwlc), Lwl, par_scope);
    e_val(&(this->Wlc), Wl, par_scope);
    e_val(&(this->Wwc), Ww, par_scope);
    e_val(&(this->Wwlc), Wwl, par_scope);
    e_val(&(this->acm), 10, par_scope);
    // final adjust: mid
    // final adjust: calculated
    factor1 = sqrt(tox * P_EPS_SI / P_EPS_OX);
    vt_at_tnom = tnom_k * P_K_Q;
    ni = (1.45e10 * (tnom_k / 300.15)
	 * sqrt(tnom_k / 300.15)
	 * exp(21.5565981 - egap / (2.0 * vt_at_tnom)));
    // final adjust: post

      if (npeak.nom() > 1.0e20) {
	npeak.set_nom(npeak.nom() * 1.0e-6);
      }
      if (ngate.nom() > 1.0e23) {
	ngate.set_nom(ngate.nom() * 1.0e-6);
      }
    // final adjust: done
}
/*--------------------------------------------------------------------------*/
void MODEL_BUILT_IN_MOS8::precalc_last()
{
    MODEL_BUILT_IN_MOS_BASE::precalc_last();
}
/*--------------------------------------------------------------------------*/
SDP_CARD* MODEL_BUILT_IN_MOS8::new_sdp(COMMON_COMPONENT* c)const
{
  assert(c);
  if (COMMON_BUILT_IN_MOS* cc = dynamic_cast<COMMON_BUILT_IN_MOS*>(c)) {
    if (cc->_sdp) {
      cc->_sdp->init(cc);
      return cc->_sdp;
    }else{
      delete cc->_sdp;
      return new SDP_BUILT_IN_MOS8(c);
    }
  }else{
    return MODEL_BUILT_IN_MOS_BASE::new_sdp(c);
  }
}
/*--------------------------------------------------------------------------*/
void MODEL_BUILT_IN_MOS8::set_param_by_index(int i, std::string& value, int offset)
{
  switch (MODEL_BUILT_IN_MOS8::param_count() - 1 - i) {
  case 0: level = value; break; //8
  case 1: unreachable(); break;
  case 2: unreachable(); break;
  case 3: unreachable(); break;
  case 4: unreachable(); break;
  case 5: unreachable(); break;
  case 6: unreachable(); break;
  case 7: unreachable(); break;
  case 8: unreachable(); break;
  case 9: unreachable(); break;
  case 10: mos_level = value; break;
  case 11: cdsc.set_nom(value); break;
  case 12: cdsc.set_w(value); break;
  case 13: cdsc.set_l(value); break;
  case 14: cdsc.set_p(value); break;
  case 15: cdscb.set_nom(value); break;
  case 16: cdscb.set_w(value); break;
  case 17: cdscb.set_l(value); break;
  case 18: cdscb.set_p(value); break;
  case 19: cdscd.set_nom(value); break;
  case 20: cdscd.set_w(value); break;
  case 21: cdscd.set_l(value); break;
  case 22: cdscd.set_p(value); break;
  case 23: cit.set_nom(value); break;
  case 24: cit.set_w(value); break;
  case 25: cit.set_l(value); break;
  case 26: cit.set_p(value); break;
  case 27: nfactor.set_nom(value); break;
  case 28: nfactor.set_w(value); break;
  case 29: nfactor.set_l(value); break;
  case 30: nfactor.set_p(value); break;
  case 31: xj.set_nom(value); break;
  case 32: xj.set_w(value); break;
  case 33: xj.set_l(value); break;
  case 34: xj.set_p(value); break;
  case 35: vsat.set_nom(value); break;
  case 36: vsat.set_w(value); break;
  case 37: vsat.set_l(value); break;
  case 38: vsat.set_p(value); break;
  case 39: at.set_nom(value); break;
  case 40: at.set_w(value); break;
  case 41: at.set_l(value); break;
  case 42: at.set_p(value); break;
  case 43: a0.set_nom(value); break;
  case 44: a0.set_w(value); break;
  case 45: a0.set_l(value); break;
  case 46: a0.set_p(value); break;
  case 47: ags.set_nom(value); break;
  case 48: ags.set_w(value); break;
  case 49: ags.set_l(value); break;
  case 50: ags.set_p(value); break;
  case 51: a1.set_nom(value); break;
  case 52: a1.set_w(value); break;
  case 53: a1.set_l(value); break;
  case 54: a1.set_p(value); break;
  case 55: a2.set_nom(value); break;
  case 56: a2.set_w(value); break;
  case 57: a2.set_l(value); break;
  case 58: a2.set_p(value); break;
  case 59: keta.set_nom(value); break;
  case 60: keta.set_w(value); break;
  case 61: keta.set_l(value); break;
  case 62: keta.set_p(value); break;
  case 63: nsub.set_nom(value); break;
  case 64: nsub.set_w(value); break;
  case 65: nsub.set_l(value); break;
  case 66: nsub.set_p(value); break;
  case 67: npeak.set_nom(value); break;
  case 68: npeak.set_w(value); break;
  case 69: npeak.set_l(value); break;
  case 70: npeak.set_p(value); break;
  case 71: ngate.set_nom(value); break;
  case 72: ngate.set_w(value); break;
  case 73: ngate.set_l(value); break;
  case 74: ngate.set_p(value); break;
  case 75: gamma1.set_nom(value); break;
  case 76: gamma1.set_w(value); break;
  case 77: gamma1.set_l(value); break;
  case 78: gamma1.set_p(value); break;
  case 79: gamma2.set_nom(value); break;
  case 80: gamma2.set_w(value); break;
  case 81: gamma2.set_l(value); break;
  case 82: gamma2.set_p(value); break;
  case 83: vbx.set_nom(value); break;
  case 84: vbx.set_w(value); break;
  case 85: vbx.set_l(value); break;
  case 86: vbx.set_p(value); break;
  case 87: vbm.set_nom(value); break;
  case 88: vbm.set_w(value); break;
  case 89: vbm.set_l(value); break;
  case 90: vbm.set_p(value); break;
  case 91: xt.set_nom(value); break;
  case 92: xt.set_w(value); break;
  case 93: xt.set_l(value); break;
  case 94: xt.set_p(value); break;
  case 95: k1.set_nom(value); break;
  case 96: k1.set_w(value); break;
  case 97: k1.set_l(value); break;
  case 98: k1.set_p(value); break;
  case 99: kt1.set_nom(value); break;
  case 100: kt1.set_w(value); break;
  case 101: kt1.set_l(value); break;
  case 102: kt1.set_p(value); break;
  case 103: kt1l.set_nom(value); break;
  case 104: kt1l.set_w(value); break;
  case 105: kt1l.set_l(value); break;
  case 106: kt1l.set_p(value); break;
  case 107: kt2.set_nom(value); break;
  case 108: kt2.set_w(value); break;
  case 109: kt2.set_l(value); break;
  case 110: kt2.set_p(value); break;
  case 111: k2.set_nom(value); break;
  case 112: k2.set_w(value); break;
  case 113: k2.set_l(value); break;
  case 114: k2.set_p(value); break;
  case 115: k3.set_nom(value); break;
  case 116: k3.set_w(value); break;
  case 117: k3.set_l(value); break;
  case 118: k3.set_p(value); break;
  case 119: k3b.set_nom(value); break;
  case 120: k3b.set_w(value); break;
  case 121: k3b.set_l(value); break;
  case 122: k3b.set_p(value); break;
  case 123: w0.set_nom(value); break;
  case 124: w0.set_w(value); break;
  case 125: w0.set_l(value); break;
  case 126: w0.set_p(value); break;
  case 127: nlx.set_nom(value); break;
  case 128: nlx.set_w(value); break;
  case 129: nlx.set_l(value); break;
  case 130: nlx.set_p(value); break;
  case 131: dvt0.set_nom(value); break;
  case 132: dvt0.set_w(value); break;
  case 133: dvt0.set_l(value); break;
  case 134: dvt0.set_p(value); break;
  case 135: dvt1.set_nom(value); break;
  case 136: dvt1.set_w(value); break;
  case 137: dvt1.set_l(value); break;
  case 138: dvt1.set_p(value); break;
  case 139: dvt2.set_nom(value); break;
  case 140: dvt2.set_w(value); break;
  case 141: dvt2.set_l(value); break;
  case 142: dvt2.set_p(value); break;
  case 143: dvt0w.set_nom(value); break;
  case 144: dvt0w.set_w(value); break;
  case 145: dvt0w.set_l(value); break;
  case 146: dvt0w.set_p(value); break;
  case 147: dvt1w.set_nom(value); break;
  case 148: dvt1w.set_w(value); break;
  case 149: dvt1w.set_l(value); break;
  case 150: dvt1w.set_p(value); break;
  case 151: dvt2w.set_nom(value); break;
  case 152: dvt2w.set_w(value); break;
  case 153: dvt2w.set_l(value); break;
  case 154: dvt2w.set_p(value); break;
  case 155: drout.set_nom(value); break;
  case 156: drout.set_w(value); break;
  case 157: drout.set_l(value); break;
  case 158: drout.set_p(value); break;
  case 159: dsub.set_nom(value); break;
  case 160: dsub.set_w(value); break;
  case 161: dsub.set_l(value); break;
  case 162: dsub.set_p(value); break;
  case 163: vth0.set_nom(value); break;
  case 164: vth0.set_w(value); break;
  case 165: vth0.set_l(value); break;
  case 166: vth0.set_p(value); break;
  case 167: ua1.set_nom(value); break;
  case 168: ua1.set_w(value); break;
  case 169: ua1.set_l(value); break;
  case 170: ua1.set_p(value); break;
  case 171: ua.set_nom(value); break;
  case 172: ua.set_w(value); break;
  case 173: ua.set_l(value); break;
  case 174: ua.set_p(value); break;
  case 175: ub1.set_nom(value); break;
  case 176: ub1.set_w(value); break;
  case 177: ub1.set_l(value); break;
  case 178: ub1.set_p(value); break;
  case 179: ub.set_nom(value); break;
  case 180: ub.set_w(value); break;
  case 181: ub.set_l(value); break;
  case 182: ub.set_p(value); break;
  case 183: uc1.set_nom(value); break;
  case 184: uc1.set_w(value); break;
  case 185: uc1.set_l(value); break;
  case 186: uc1.set_p(value); break;
  case 187: uc.set_nom(value); break;
  case 188: uc.set_w(value); break;
  case 189: uc.set_l(value); break;
  case 190: uc.set_p(value); break;
  case 191: u0.set_nom(value); break;
  case 192: u0.set_w(value); break;
  case 193: u0.set_l(value); break;
  case 194: u0.set_p(value); break;
  case 195: ute.set_nom(value); break;
  case 196: ute.set_w(value); break;
  case 197: ute.set_l(value); break;
  case 198: ute.set_p(value); break;
  case 199: voff.set_nom(value); break;
  case 200: voff.set_w(value); break;
  case 201: voff.set_l(value); break;
  case 202: voff.set_p(value); break;
  case 203: delta.set_nom(value); break;
  case 204: delta.set_w(value); break;
  case 205: delta.set_l(value); break;
  case 206: delta.set_p(value); break;
  case 207: rdsw.set_nom(value); break;
  case 208: rdsw.set_w(value); break;
  case 209: rdsw.set_l(value); break;
  case 210: rdsw.set_p(value); break;
  case 211: prwg.set_nom(value); break;
  case 212: prwg.set_w(value); break;
  case 213: prwg.set_l(value); break;
  case 214: prwg.set_p(value); break;
  case 215: prwb.set_nom(value); break;
  case 216: prwb.set_w(value); break;
  case 217: prwb.set_l(value); break;
  case 218: prwb.set_p(value); break;
  case 219: prt.set_nom(value); break;
  case 220: prt.set_w(value); break;
  case 221: prt.set_l(value); break;
  case 222: prt.set_p(value); break;
  case 223: eta0.set_nom(value); break;
  case 224: eta0.set_w(value); break;
  case 225: eta0.set_l(value); break;
  case 226: eta0.set_p(value); break;
  case 227: etab.set_nom(value); break;
  case 228: etab.set_w(value); break;
  case 229: etab.set_l(value); break;
  case 230: etab.set_p(value); break;
  case 231: pclm.set_nom(value); break;
  case 232: pclm.set_w(value); break;
  case 233: pclm.set_l(value); break;
  case 234: pclm.set_p(value); break;
  case 235: pdibl1.set_nom(value); break;
  case 236: pdibl1.set_w(value); break;
  case 237: pdibl1.set_l(value); break;
  case 238: pdibl1.set_p(value); break;
  case 239: pdibl2.set_nom(value); break;
  case 240: pdibl2.set_w(value); break;
  case 241: pdibl2.set_l(value); break;
  case 242: pdibl2.set_p(value); break;
  case 243: pdiblb.set_nom(value); break;
  case 244: pdiblb.set_w(value); break;
  case 245: pdiblb.set_l(value); break;
  case 246: pdiblb.set_p(value); break;
  case 247: pscbe1.set_nom(value); break;
  case 248: pscbe1.set_w(value); break;
  case 249: pscbe1.set_l(value); break;
  case 250: pscbe1.set_p(value); break;
  case 251: pscbe2.set_nom(value); break;
  case 252: pscbe2.set_w(value); break;
  case 253: pscbe2.set_l(value); break;
  case 254: pscbe2.set_p(value); break;
  case 255: pvag.set_nom(value); break;
  case 256: pvag.set_w(value); break;
  case 257: pvag.set_l(value); break;
  case 258: pvag.set_p(value); break;
  case 259: wr.set_nom(value); break;
  case 260: wr.set_w(value); break;
  case 261: wr.set_l(value); break;
  case 262: wr.set_p(value); break;
  case 263: dwg.set_nom(value); break;
  case 264: dwg.set_w(value); break;
  case 265: dwg.set_l(value); break;
  case 266: dwg.set_p(value); break;
  case 267: dwb.set_nom(value); break;
  case 268: dwb.set_w(value); break;
  case 269: dwb.set_l(value); break;
  case 270: dwb.set_p(value); break;
  case 271: b0.set_nom(value); break;
  case 272: b0.set_w(value); break;
  case 273: b0.set_l(value); break;
  case 274: b0.set_p(value); break;
  case 275: b1.set_nom(value); break;
  case 276: b1.set_w(value); break;
  case 277: b1.set_l(value); break;
  case 278: b1.set_p(value); break;
  case 279: alpha0.set_nom(value); break;
  case 280: alpha0.set_w(value); break;
  case 281: alpha0.set_l(value); break;
  case 282: alpha0.set_p(value); break;
  case 283: beta0.set_nom(value); break;
  case 284: beta0.set_w(value); break;
  case 285: beta0.set_l(value); break;
  case 286: beta0.set_p(value); break;
  case 287: elm.set_nom(value); break;
  case 288: elm.set_w(value); break;
  case 289: elm.set_l(value); break;
  case 290: elm.set_p(value); break;
  case 291: vfbcv.set_nom(value); break;
  case 292: vfbcv.set_w(value); break;
  case 293: vfbcv.set_l(value); break;
  case 294: vfbcv.set_p(value); break;
  case 295: cgsl.set_nom(value); break;
  case 296: cgsl.set_w(value); break;
  case 297: cgsl.set_l(value); break;
  case 298: cgsl.set_p(value); break;
  case 299: cgdl.set_nom(value); break;
  case 300: cgdl.set_w(value); break;
  case 301: cgdl.set_l(value); break;
  case 302: cgdl.set_p(value); break;
  case 303: ckappa.set_nom(value); break;
  case 304: ckappa.set_w(value); break;
  case 305: ckappa.set_l(value); break;
  case 306: ckappa.set_p(value); break;
  case 307: cf.set_nom(value); break;
  case 308: cf.set_w(value); break;
  case 309: cf.set_l(value); break;
  case 310: cf.set_p(value); break;
  case 311: clc.set_nom(value); break;
  case 312: clc.set_w(value); break;
  case 313: clc.set_l(value); break;
  case 314: clc.set_p(value); break;
  case 315: cle.set_nom(value); break;
  case 316: cle.set_w(value); break;
  case 317: cle.set_l(value); break;
  case 318: cle.set_p(value); break;
  case 319: vfb.set_nom(value); break;
  case 320: vfb.set_w(value); break;
  case 321: vfb.set_l(value); break;
  case 322: vfb.set_p(value); break;
  case 323: acde.set_nom(value); break;
  case 324: acde.set_w(value); break;
  case 325: acde.set_l(value); break;
  case 326: acde.set_p(value); break;
  case 327: moin.set_nom(value); break;
  case 328: moin.set_w(value); break;
  case 329: moin.set_l(value); break;
  case 330: moin.set_p(value); break;
  case 331: noff.set_nom(value); break;
  case 332: noff.set_w(value); break;
  case 333: noff.set_l(value); break;
  case 334: noff.set_p(value); break;
  case 335: voffcv.set_nom(value); break;
  case 336: voffcv.set_w(value); break;
  case 337: voffcv.set_l(value); break;
  case 338: voffcv.set_p(value); break;
  case 339: alpha1.set_nom(value); break;
  case 340: alpha1.set_w(value); break;
  case 341: alpha1.set_l(value); break;
  case 342: alpha1.set_p(value); break;
  case 343: capMod = value; break;
  case 344: nqsMod = value; break;
  case 345: mobMod = value; break;
  case 346: noiMod = value; break;
  case 347: paramChk = value; break;
  case 348: binUnit = value; break;
  case 349: version = value; break;
  case 350: tox = value; break;
  case 351: xpart = value; break;
  case 352: jctSidewallSatCurDensity = value; break;
  case 353: mjswg = value; break;
  case 354: pbswg = value; break;
  case 355: unitLengthGateSidewallJctCap = value; break;
  case 356: jctEmissionCoeff = value; break;
  case 357: jctTempExponent = value; break;
  case 358: Lint = value; break;
  case 359: Ll = value; break;
  case 360: Lln = value; break;
  case 361: Lw = value; break;
  case 362: Lwn = value; break;
  case 363: Lwl = value; break;
  case 364: Wint = value; break;
  case 365: Wl = value; break;
  case 366: Wln = value; break;
  case 367: Ww = value; break;
  case 368: Wwn = value; break;
  case 369: Wwl = value; break;
  case 370: dwc = value; break;
  case 371: dlc = value; break;
  case 372: noia = value; break;
  case 373: noib = value; break;
  case 374: noic = value; break;
  case 375: em = value; break;
  case 376: ef = value; break;
  case 377: acnqsMod = value; break;
  case 378: toxm = value; break;
  case 379: lintnoi = value; break;
  case 380: ijth = value; break;
  case 381: tpb = value; break;
  case 382: tcj = value; break;
  case 383: tpbsw = value; break;
  case 384: tcjsw = value; break;
  case 385: tpbswg = value; break;
  case 386: tcjswg = value; break;
  case 387: Llc = value; break;
  case 388: Lwc = value; break;
  case 389: Lwlc = value; break;
  case 390: Wlc = value; break;
  case 391: Wwc = value; break;
  case 392: Wwlc = value; break;
  case 393: acm = value; break;
  case 394: h0 = value; break;
//  case 395: hci_m = value; break;
//  case 396: hci_n = value; break;
  default: MODEL_BUILT_IN_MOS_BASE::set_param_by_index(i, value, offset); break;
  }
}
/*--------------------------------------------------------------------------*/
bool MODEL_BUILT_IN_MOS8::param_is_printable(int i)const
{
  switch (MODEL_BUILT_IN_MOS8::param_count() - 1 - i) {
  case 0:  return (true);
  case 1:  return (false);
  case 2:  return (false);
  case 3:  return (false);
  case 4:  return (false);
  case 5:  return (false);
  case 6:  return (false);
  case 7:  return (false);
  case 8:  return (false);
  case 9:  return (false);
  case 10:  return (mos_level != LEVEL);
  case 11:  return (true);
  case 12:  return (cdsc.w_has_value());
  case 13:  return (cdsc.l_has_value());
  case 14:  return (cdsc.p_has_value());
  case 15:  return (true);
  case 16:  return (cdscb.w_has_value());
  case 17:  return (cdscb.l_has_value());
  case 18:  return (cdscb.p_has_value());
  case 19:  return (true);
  case 20:  return (cdscd.w_has_value());
  case 21:  return (cdscd.l_has_value());
  case 22:  return (cdscd.p_has_value());
  case 23:  return (true);
  case 24:  return (cit.w_has_value());
  case 25:  return (cit.l_has_value());
  case 26:  return (cit.p_has_value());
  case 27:  return (true);
  case 28:  return (nfactor.w_has_value());
  case 29:  return (nfactor.l_has_value());
  case 30:  return (nfactor.p_has_value());
  case 31:  return (true);
  case 32:  return (xj.w_has_value());
  case 33:  return (xj.l_has_value());
  case 34:  return (xj.p_has_value());
  case 35:  return (true);
  case 36:  return (vsat.w_has_value());
  case 37:  return (vsat.l_has_value());
  case 38:  return (vsat.p_has_value());
  case 39:  return (true);
  case 40:  return (at.w_has_value());
  case 41:  return (at.l_has_value());
  case 42:  return (at.p_has_value());
  case 43:  return (true);
  case 44:  return (a0.w_has_value());
  case 45:  return (a0.l_has_value());
  case 46:  return (a0.p_has_value());
  case 47:  return (true);
  case 48:  return (ags.w_has_value());
  case 49:  return (ags.l_has_value());
  case 50:  return (ags.p_has_value());
  case 51:  return (true);
  case 52:  return (a1.w_has_value());
  case 53:  return (a1.l_has_value());
  case 54:  return (a1.p_has_value());
  case 55:  return (true);
  case 56:  return (a2.w_has_value());
  case 57:  return (a2.l_has_value());
  case 58:  return (a2.p_has_value());
  case 59:  return (true);
  case 60:  return (keta.w_has_value());
  case 61:  return (keta.l_has_value());
  case 62:  return (keta.p_has_value());
  case 63:  return (true);
  case 64:  return (nsub.w_has_value());
  case 65:  return (nsub.l_has_value());
  case 66:  return (nsub.p_has_value());
  case 67:  return (npeak.has_value());
  case 68:  return (npeak.w_has_value());
  case 69:  return (npeak.l_has_value());
  case 70:  return (npeak.p_has_value());
  case 71:  return (true);
  case 72:  return (ngate.w_has_value());
  case 73:  return (ngate.l_has_value());
  case 74:  return (ngate.p_has_value());
  case 75:  return (gamma1.has_value());
  case 76:  return (gamma1.w_has_value());
  case 77:  return (gamma1.l_has_value());
  case 78:  return (gamma1.p_has_value());
  case 79:  return (gamma2.has_value());
  case 80:  return (gamma2.w_has_value());
  case 81:  return (gamma2.l_has_value());
  case 82:  return (gamma2.p_has_value());
  case 83:  return (vbx.has_value());
  case 84:  return (vbx.w_has_value());
  case 85:  return (vbx.l_has_value());
  case 86:  return (vbx.p_has_value());
  case 87:  return (true);
  case 88:  return (vbm.w_has_value());
  case 89:  return (vbm.l_has_value());
  case 90:  return (vbm.p_has_value());
  case 91:  return (true);
  case 92:  return (xt.w_has_value());
  case 93:  return (xt.l_has_value());
  case 94:  return (xt.p_has_value());
  case 95:  return (k1.has_value());
  case 96:  return (k1.w_has_value());
  case 97:  return (k1.l_has_value());
  case 98:  return (k1.p_has_value());
  case 99:  return (true);
  case 100:  return (kt1.w_has_value());
  case 101:  return (kt1.l_has_value());
  case 102:  return (kt1.p_has_value());
  case 103:  return (true);
  case 104:  return (kt1l.w_has_value());
  case 105:  return (kt1l.l_has_value());
  case 106:  return (kt1l.p_has_value());
  case 107:  return (true);
  case 108:  return (kt2.w_has_value());
  case 109:  return (kt2.l_has_value());
  case 110:  return (kt2.p_has_value());
  case 111:  return (k2.has_value());
  case 112:  return (k2.w_has_value());
  case 113:  return (k2.l_has_value());
  case 114:  return (k2.p_has_value());
  case 115:  return (true);
  case 116:  return (k3.w_has_value());
  case 117:  return (k3.l_has_value());
  case 118:  return (k3.p_has_value());
  case 119:  return (true);
  case 120:  return (k3b.w_has_value());
  case 121:  return (k3b.l_has_value());
  case 122:  return (k3b.p_has_value());
  case 123:  return (true);
  case 124:  return (w0.w_has_value());
  case 125:  return (w0.l_has_value());
  case 126:  return (w0.p_has_value());
  case 127:  return (true);
  case 128:  return (nlx.w_has_value());
  case 129:  return (nlx.l_has_value());
  case 130:  return (nlx.p_has_value());
  case 131:  return (true);
  case 132:  return (dvt0.w_has_value());
  case 133:  return (dvt0.l_has_value());
  case 134:  return (dvt0.p_has_value());
  case 135:  return (true);
  case 136:  return (dvt1.w_has_value());
  case 137:  return (dvt1.l_has_value());
  case 138:  return (dvt1.p_has_value());
  case 139:  return (true);
  case 140:  return (dvt2.w_has_value());
  case 141:  return (dvt2.l_has_value());
  case 142:  return (dvt2.p_has_value());
  case 143:  return (true);
  case 144:  return (dvt0w.w_has_value());
  case 145:  return (dvt0w.l_has_value());
  case 146:  return (dvt0w.p_has_value());
  case 147:  return (true);
  case 148:  return (dvt1w.w_has_value());
  case 149:  return (dvt1w.l_has_value());
  case 150:  return (dvt1w.p_has_value());
  case 151:  return (true);
  case 152:  return (dvt2w.w_has_value());
  case 153:  return (dvt2w.l_has_value());
  case 154:  return (dvt2w.p_has_value());
  case 155:  return (true);
  case 156:  return (drout.w_has_value());
  case 157:  return (drout.l_has_value());
  case 158:  return (drout.p_has_value());
  case 159:  return (dsub.has_value());
  case 160:  return (dsub.w_has_value());
  case 161:  return (dsub.l_has_value());
  case 162:  return (dsub.p_has_value());
  case 163:  return (vth0.has_value());
  case 164:  return (vth0.w_has_value());
  case 165:  return (vth0.l_has_value());
  case 166:  return (vth0.p_has_value());
  case 167:  return (true);
  case 168:  return (ua1.w_has_value());
  case 169:  return (ua1.l_has_value());
  case 170:  return (ua1.p_has_value());
  case 171:  return (true);
  case 172:  return (ua.w_has_value());
  case 173:  return (ua.l_has_value());
  case 174:  return (ua.p_has_value());
  case 175:  return (true);
  case 176:  return (ub1.w_has_value());
  case 177:  return (ub1.l_has_value());
  case 178:  return (ub1.p_has_value());
  case 179:  return (true);
  case 180:  return (ub.w_has_value());
  case 181:  return (ub.l_has_value());
  case 182:  return (ub.p_has_value());
  case 183:  return (uc1.has_value());
  case 184:  return (uc1.w_has_value());
  case 185:  return (uc1.l_has_value());
  case 186:  return (uc1.p_has_value());
  case 187:  return (uc.has_value());
  case 188:  return (uc.w_has_value());
  case 189:  return (uc.l_has_value());
  case 190:  return (uc.p_has_value());
  case 191:  return (u0.has_value());
  case 192:  return (u0.w_has_value());
  case 193:  return (u0.l_has_value());
  case 194:  return (u0.p_has_value());
  case 195:  return (true);
  case 196:  return (ute.w_has_value());
  case 197:  return (ute.l_has_value());
  case 198:  return (ute.p_has_value());
  case 199:  return (true);
  case 200:  return (voff.w_has_value());
  case 201:  return (voff.l_has_value());
  case 202:  return (voff.p_has_value());
  case 203:  return (true);
  case 204:  return (delta.w_has_value());
  case 205:  return (delta.l_has_value());
  case 206:  return (delta.p_has_value());
  case 207:  return (true);
  case 208:  return (rdsw.w_has_value());
  case 209:  return (rdsw.l_has_value());
  case 210:  return (rdsw.p_has_value());
  case 211:  return (true);
  case 212:  return (prwg.w_has_value());
  case 213:  return (prwg.l_has_value());
  case 214:  return (prwg.p_has_value());
  case 215:  return (true);
  case 216:  return (prwb.w_has_value());
  case 217:  return (prwb.l_has_value());
  case 218:  return (prwb.p_has_value());
  case 219:  return (true);
  case 220:  return (prt.w_has_value());
  case 221:  return (prt.l_has_value());
  case 222:  return (prt.p_has_value());
  case 223:  return (true);
  case 224:  return (eta0.w_has_value());
  case 225:  return (eta0.l_has_value());
  case 226:  return (eta0.p_has_value());
  case 227:  return (true);
  case 228:  return (etab.w_has_value());
  case 229:  return (etab.l_has_value());
  case 230:  return (etab.p_has_value());
  case 231:  return (true);
  case 232:  return (pclm.w_has_value());
  case 233:  return (pclm.l_has_value());
  case 234:  return (pclm.p_has_value());
  case 235:  return (true);
  case 236:  return (pdibl1.w_has_value());
  case 237:  return (pdibl1.l_has_value());
  case 238:  return (pdibl1.p_has_value());
  case 239:  return (true);
  case 240:  return (pdibl2.w_has_value());
  case 241:  return (pdibl2.l_has_value());
  case 242:  return (pdibl2.p_has_value());
  case 243:  return (true);
  case 244:  return (pdiblb.w_has_value());
  case 245:  return (pdiblb.l_has_value());
  case 246:  return (pdiblb.p_has_value());
  case 247:  return (true);
  case 248:  return (pscbe1.w_has_value());
  case 249:  return (pscbe1.l_has_value());
  case 250:  return (pscbe1.p_has_value());
  case 251:  return (true);
  case 252:  return (pscbe2.w_has_value());
  case 253:  return (pscbe2.l_has_value());
  case 254:  return (pscbe2.p_has_value());
  case 255:  return (true);
  case 256:  return (pvag.w_has_value());
  case 257:  return (pvag.l_has_value());
  case 258:  return (pvag.p_has_value());
  case 259:  return (true);
  case 260:  return (wr.w_has_value());
  case 261:  return (wr.l_has_value());
  case 262:  return (wr.p_has_value());
  case 263:  return (true);
  case 264:  return (dwg.w_has_value());
  case 265:  return (dwg.l_has_value());
  case 266:  return (dwg.p_has_value());
  case 267:  return (true);
  case 268:  return (dwb.w_has_value());
  case 269:  return (dwb.l_has_value());
  case 270:  return (dwb.p_has_value());
  case 271:  return (true);
  case 272:  return (b0.w_has_value());
  case 273:  return (b0.l_has_value());
  case 274:  return (b0.p_has_value());
  case 275:  return (true);
  case 276:  return (b1.w_has_value());
  case 277:  return (b1.l_has_value());
  case 278:  return (b1.p_has_value());
  case 279:  return (true);
  case 280:  return (alpha0.w_has_value());
  case 281:  return (alpha0.l_has_value());
  case 282:  return (alpha0.p_has_value());
  case 283:  return (true);
  case 284:  return (beta0.w_has_value());
  case 285:  return (beta0.l_has_value());
  case 286:  return (beta0.p_has_value());
  case 287:  return (true);
  case 288:  return (elm.w_has_value());
  case 289:  return (elm.l_has_value());
  case 290:  return (elm.p_has_value());
  case 291:  return (true);
  case 292:  return (vfbcv.w_has_value());
  case 293:  return (vfbcv.l_has_value());
  case 294:  return (vfbcv.p_has_value());
  case 295:  return (true);
  case 296:  return (cgsl.w_has_value());
  case 297:  return (cgsl.l_has_value());
  case 298:  return (cgsl.p_has_value());
  case 299:  return (true);
  case 300:  return (cgdl.w_has_value());
  case 301:  return (cgdl.l_has_value());
  case 302:  return (cgdl.p_has_value());
  case 303:  return (true);
  case 304:  return (ckappa.w_has_value());
  case 305:  return (ckappa.l_has_value());
  case 306:  return (ckappa.p_has_value());
  case 307:  return (cf.has_value());
  case 308:  return (cf.w_has_value());
  case 309:  return (cf.l_has_value());
  case 310:  return (cf.p_has_value());
  case 311:  return (true);
  case 312:  return (clc.w_has_value());
  case 313:  return (clc.l_has_value());
  case 314:  return (clc.p_has_value());
  case 315:  return (true);
  case 316:  return (cle.w_has_value());
  case 317:  return (cle.l_has_value());
  case 318:  return (cle.p_has_value());
  case 319:  return (vfb.has_value());
  case 320:  return (vfb.w_has_value());
  case 321:  return (vfb.l_has_value());
  case 322:  return (vfb.p_has_value());
  case 323:  return (true);
  case 324:  return (acde.w_has_value());
  case 325:  return (acde.l_has_value());
  case 326:  return (acde.p_has_value());
  case 327:  return (true);
  case 328:  return (moin.w_has_value());
  case 329:  return (moin.l_has_value());
  case 330:  return (moin.p_has_value());
  case 331:  return (true);
  case 332:  return (noff.w_has_value());
  case 333:  return (noff.l_has_value());
  case 334:  return (noff.p_has_value());
  case 335:  return (true);
  case 336:  return (voffcv.w_has_value());
  case 337:  return (voffcv.l_has_value());
  case 338:  return (voffcv.p_has_value());
  case 339:  return (true);
  case 340:  return (alpha1.w_has_value());
  case 341:  return (alpha1.l_has_value());
  case 342:  return (alpha1.p_has_value());
  case 343:  return (true);
  case 344:  return (true);
  case 345:  return (true);
  case 346:  return (true);
  case 347:  return (true);
  case 348:  return (true);
  case 349:  return (true);
  case 350:  return (true);
  case 351:  return (true);
  case 352:  return (true);
  case 353:  return (mjswg.has_hard_value());
  case 354:  return (pbswg.has_hard_value());
  case 355:  return (unitLengthGateSidewallJctCap.has_hard_value());
  case 356:  return (true);
  case 357:  return (true);
  case 358:  return (true);
  case 359:  return (true);
  case 360:  return (true);
  case 361:  return (true);
  case 362:  return (true);
  case 363:  return (true);
  case 364:  return (true);
  case 365:  return (true);
  case 366:  return (true);
  case 367:  return (true);
  case 368:  return (true);
  case 369:  return (true);
  case 370:  return (dwc.has_hard_value());
  case 371:  return (dlc.has_hard_value());
  case 372:  return (noia.has_hard_value());
  case 373:  return (noib.has_hard_value());
  case 374:  return (noic.has_hard_value());
  case 375:  return (true);
  case 376:  return (true);
  case 377:  return (true);
  case 378:  return (true);
  case 379:  return (true);
  case 380:  return (true);
  case 381:  return (true);
  case 382:  return (true);
  case 383:  return (true);
  case 384:  return (true);
  case 385:  return (true);
  case 386:  return (true);
  case 387:  return (true);
  case 388:  return (true);
  case 389:  return (true);
  case 390:  return (true);
  case 391:  return (true);
  case 392:  return (true);
  case 393:  return (true);
  case 394:  return (true);
  default: return MODEL_BUILT_IN_MOS_BASE::param_is_printable(i);
  }
}
/*--------------------------------------------------------------------------*/
std::string MODEL_BUILT_IN_MOS8::param_name(int i)const
{
  switch (MODEL_BUILT_IN_MOS8::param_count() - 1 - i) {
  case 0:  return "level";
  case 1:  return "=====";
  case 2:  return "=====";
  case 3:  return "=====";
  case 4:  return "=====";
  case 5:  return "=====";
  case 6:  return "=====";
  case 7:  return "=====";
  case 8:  return "=====";
  case 9:  return "=====";
  case 10:  return "diodelevel";
  case 11:  return "cdsc";
  case 12:  return "wcdsc";
  case 13:  return "lcdsc";
  case 14:  return "pcdsc";
  case 15:  return "cdscb";
  case 16:  return "wcdscb";
  case 17:  return "lcdscb";
  case 18:  return "pcdscb";
  case 19:  return "cdscd";
  case 20:  return "wcdscd";
  case 21:  return "lcdscd";
  case 22:  return "pcdscd";
  case 23:  return "cit";
  case 24:  return "wcit";
  case 25:  return "lcit";
  case 26:  return "pcit";
  case 27:  return "nfactor";
  case 28:  return "wnfactor";
  case 29:  return "lnfactor";
  case 30:  return "pnfactor";
  case 31:  return "xj";
  case 32:  return "wxj";
  case 33:  return "lxj";
  case 34:  return "pxj";
  case 35:  return "vsat";
  case 36:  return "wvsat";
  case 37:  return "lvsat";
  case 38:  return "pvsat";
  case 39:  return "at";
  case 40:  return "wat";
  case 41:  return "lat";
  case 42:  return "pat";
  case 43:  return "a0";
  case 44:  return "wa0";
  case 45:  return "la0";
  case 46:  return "pa0";
  case 47:  return "ags";
  case 48:  return "wags";
  case 49:  return "lags";
  case 50:  return "pags";
  case 51:  return "a1";
  case 52:  return "wa1";
  case 53:  return "la1";
  case 54:  return "pa1";
  case 55:  return "a2";
  case 56:  return "wa2";
  case 57:  return "la2";
  case 58:  return "pa2";
  case 59:  return "keta";
  case 60:  return "wketa";
  case 61:  return "lketa";
  case 62:  return "pketa";
  case 63:  return "nsub";
  case 64:  return "wnsub";
  case 65:  return "lnsub";
  case 66:  return "pnsub";
  case 67:  return "nch";
  case 68:  return "wnch";
  case 69:  return "lnch";
  case 70:  return "pnch";
  case 71:  return "ngate";
  case 72:  return "wngate";
  case 73:  return "lngate";
  case 74:  return "pngate";
  case 75:  return "gamma1";
  case 76:  return "wgamma1";
  case 77:  return "lgamma1";
  case 78:  return "pgamma1";
  case 79:  return "gamma2";
  case 80:  return "wgamma2";
  case 81:  return "lgamma2";
  case 82:  return "pgamma2";
  case 83:  return "vbx";
  case 84:  return "wvbx";
  case 85:  return "lvbx";
  case 86:  return "pvbx";
  case 87:  return "vbm";
  case 88:  return "wvbm";
  case 89:  return "lvbm";
  case 90:  return "pvbm";
  case 91:  return "xt";
  case 92:  return "wxt";
  case 93:  return "lxt";
  case 94:  return "pxt";
  case 95:  return "k1";
  case 96:  return "wk1";
  case 97:  return "lk1";
  case 98:  return "pk1";
  case 99:  return "kt1";
  case 100:  return "wkt1";
  case 101:  return "lkt1";
  case 102:  return "pkt1";
  case 103:  return "kt1l";
  case 104:  return "wkt1l";
  case 105:  return "lkt1l";
  case 106:  return "pkt1l";
  case 107:  return "kt2";
  case 108:  return "wkt2";
  case 109:  return "lkt2";
  case 110:  return "pkt2";
  case 111:  return "k2";
  case 112:  return "wk2";
  case 113:  return "lk2";
  case 114:  return "pk2";
  case 115:  return "k3";
  case 116:  return "wk3";
  case 117:  return "lk3";
  case 118:  return "pk3";
  case 119:  return "k3b";
  case 120:  return "wk3b";
  case 121:  return "lk3b";
  case 122:  return "pk3b";
  case 123:  return "w0";
  case 124:  return "ww0";
  case 125:  return "lw0";
  case 126:  return "pw0";
  case 127:  return "nlx";
  case 128:  return "wnlx";
  case 129:  return "lnlx";
  case 130:  return "pnlx";
  case 131:  return "dvt0";
  case 132:  return "wdvt0";
  case 133:  return "ldvt0";
  case 134:  return "pdvt0";
  case 135:  return "dvt1";
  case 136:  return "wdvt1";
  case 137:  return "ldvt1";
  case 138:  return "pdvt1";
  case 139:  return "dvt2";
  case 140:  return "wdvt2";
  case 141:  return "ldvt2";
  case 142:  return "pdvt2";
  case 143:  return "dvt0w";
  case 144:  return "wdvt0w";
  case 145:  return "ldvt0w";
  case 146:  return "pdvt0w";
  case 147:  return "dvt1w";
  case 148:  return "wdvt1w";
  case 149:  return "ldvt1w";
  case 150:  return "pdvt1w";
  case 151:  return "dvt2w";
  case 152:  return "wdvt2w";
  case 153:  return "ldvt2w";
  case 154:  return "pdvt2w";
  case 155:  return "drout";
  case 156:  return "wdrout";
  case 157:  return "ldrout";
  case 158:  return "pdrout";
  case 159:  return "dsub";
  case 160:  return "wdsub";
  case 161:  return "ldsub";
  case 162:  return "pdsub";
  case 163:  return "vth0";
  case 164:  return "wvth0";
  case 165:  return "lvth0";
  case 166:  return "pvth0";
  case 167:  return "ua1";
  case 168:  return "wua1";
  case 169:  return "lua1";
  case 170:  return "pua1";
  case 171:  return "ua";
  case 172:  return "wua";
  case 173:  return "lua";
  case 174:  return "pua";
  case 175:  return "ub1";
  case 176:  return "wub1";
  case 177:  return "lub1";
  case 178:  return "pub1";
  case 179:  return "ub";
  case 180:  return "wub";
  case 181:  return "lub";
  case 182:  return "pub";
  case 183:  return "uc1";
  case 184:  return "wuc1";
  case 185:  return "luc1";
  case 186:  return "puc1";
  case 187:  return "uc";
  case 188:  return "wuc";
  case 189:  return "luc";
  case 190:  return "puc";
  case 191:  return "u0";
  case 192:  return "wu0";
  case 193:  return "lu0";
  case 194:  return "pu0";
  case 195:  return "ute";
  case 196:  return "wute";
  case 197:  return "lute";
  case 198:  return "pute";
  case 199:  return "voff";
  case 200:  return "wvoff";
  case 201:  return "lvoff";
  case 202:  return "pvoff";
  case 203:  return "delta";
  case 204:  return "wdelta";
  case 205:  return "ldelta";
  case 206:  return "pdelta";
  case 207:  return "rdsw";
  case 208:  return "wrdsw";
  case 209:  return "lrdsw";
  case 210:  return "prdsw";
  case 211:  return "prwg";
  case 212:  return "wprwg";
  case 213:  return "lprwg";
  case 214:  return "pprwg";
  case 215:  return "prwb";
  case 216:  return "wprwb";
  case 217:  return "lprwb";
  case 218:  return "pprwb";
  case 219:  return "prt";
  case 220:  return "wprt";
  case 221:  return "lprt";
  case 222:  return "pprt";
  case 223:  return "eta0";
  case 224:  return "weta0";
  case 225:  return "leta0";
  case 226:  return "peta0";
  case 227:  return "etab";
  case 228:  return "wetab";
  case 229:  return "letab";
  case 230:  return "petab";
  case 231:  return "pclm";
  case 232:  return "wpclm";
  case 233:  return "lpclm";
  case 234:  return "ppclm";
  case 235:  return "pdiblc1";
  case 236:  return "wpdiblc1";
  case 237:  return "lpdiblc1";
  case 238:  return "ppdiblc1";
  case 239:  return "pdiblc2";
  case 240:  return "wpdiblc2";
  case 241:  return "lpdiblc2";
  case 242:  return "ppdiblc2";
  case 243:  return "pdiblcb";
  case 244:  return "wpdiblcb";
  case 245:  return "lpdiblcb";
  case 246:  return "ppdiblcb";
  case 247:  return "pscbe1";
  case 248:  return "wpscbe1";
  case 249:  return "lpscbe1";
  case 250:  return "ppscbe1";
  case 251:  return "pscbe2";
  case 252:  return "wpscbe2";
  case 253:  return "lpscbe2";
  case 254:  return "ppscbe2";
  case 255:  return "pvag";
  case 256:  return "wpvag";
  case 257:  return "lpvag";
  case 258:  return "ppvag";
  case 259:  return "wr";
  case 260:  return "wwr";
  case 261:  return "lwr";
  case 262:  return "pwr";
  case 263:  return "dwg";
  case 264:  return "wdwg";
  case 265:  return "ldwg";
  case 266:  return "pdwg";
  case 267:  return "dwb";
  case 268:  return "wdwb";
  case 269:  return "ldwb";
  case 270:  return "pdwb";
  case 271:  return "b0";
  case 272:  return "wb0";
  case 273:  return "lb0";
  case 274:  return "pb0";
  case 275:  return "b1";
  case 276:  return "wb1";
  case 277:  return "lb1";
  case 278:  return "pb1";
  case 279:  return "alpha0";
  case 280:  return "walpha0";
  case 281:  return "lalpha0";
  case 282:  return "palpha0";
  case 283:  return "beta0";
  case 284:  return "wbeta0";
  case 285:  return "lbeta0";
  case 286:  return "pbeta0";
  case 287:  return "elm";
  case 288:  return "welm";
  case 289:  return "lelm";
  case 290:  return "pelm";
  case 291:  return "vfbcv";
  case 292:  return "wvfbcv";
  case 293:  return "lvfbcv";
  case 294:  return "pvfbcv";
  case 295:  return "cgsl";
  case 296:  return "wcgsl";
  case 297:  return "lcgsl";
  case 298:  return "pcgsl";
  case 299:  return "cgdl";
  case 300:  return "wcgdl";
  case 301:  return "lcgdl";
  case 302:  return "pcgdl";
  case 303:  return "ckappa";
  case 304:  return "wckappa";
  case 305:  return "lckappa";
  case 306:  return "pckappa";
  case 307:  return "cf";
  case 308:  return "wcf";
  case 309:  return "lcf";
  case 310:  return "pcf";
  case 311:  return "clc";
  case 312:  return "wclc";
  case 313:  return "lclc";
  case 314:  return "pclc";
  case 315:  return "cle";
  case 316:  return "wcle";
  case 317:  return "lcle";
  case 318:  return "pcle";
  case 319:  return "vfb";
  case 320:  return "wvfb";
  case 321:  return "lvfb";
  case 322:  return "pvfb";
  case 323:  return "acde";
  case 324:  return "wacde";
  case 325:  return "lacde";
  case 326:  return "pacde";
  case 327:  return "moin";
  case 328:  return "wmoin";
  case 329:  return "lmoin";
  case 330:  return "pmoin";
  case 331:  return "noff";
  case 332:  return "wnoff";
  case 333:  return "lnoff";
  case 334:  return "pnoff";
  case 335:  return "voffcv";
  case 336:  return "wvoffcv";
  case 337:  return "lvoffcv";
  case 338:  return "pvoffcv";
  case 339:  return "alpha1";
  case 340:  return "walpha1";
  case 341:  return "lalpha1";
  case 342:  return "palpha1";
  case 343:  return "capmod";
  case 344:  return "nqsmod";
  case 345:  return "mobmod";
  case 346:  return "noimod";
  case 347:  return "paramchk";
  case 348:  return "binunit";
  case 349:  return "version";
  case 350:  return "tox";
  case 351:  return "xpart";
  case 352:  return "jsw";
  case 353:  return "mjswg";
  case 354:  return "pbswg";
  case 355:  return "cjswg";
  case 356:  return "nj";
  case 357:  return "xti";
  case 358:  return "lint";
  case 359:  return "ll";
  case 360:  return "lln";
  case 361:  return "lw";
  case 362:  return "lwn";
  case 363:  return "lwl";
  case 364:  return "wint";
  case 365:  return "wl";
  case 366:  return "wln";
  case 367:  return "ww";
  case 368:  return "wwn";
  case 369:  return "wwl";
  case 370:  return "dwc";
  case 371:  return "dlc";
  case 372:  return "noia";
  case 373:  return "noib";
  case 374:  return "noic";
  case 375:  return "em";
  case 376:  return "ef";
  case 377:  return "acnqsmod";
  case 378:  return "toxm";
  case 379:  return "lintnoi";
  case 380:  return "ijth";
  case 381:  return "tpb";
  case 382:  return "tcj";
  case 383:  return "tpbsw";
  case 384:  return "tcjsw";
  case 385:  return "tpbswg";
  case 386:  return "tcjswg";
  case 387:  return "llc";
  case 388:  return "lwc";
  case 389:  return "lwlc";
  case 390:  return "wlc";
  case 391:  return "wwc";
  case 392:  return "wwlc";
  case 393:  return "acm";
  case 394:  return "h0";
  default: return MODEL_BUILT_IN_MOS_BASE::param_name(i);
  }
}
/*--------------------------------------------------------------------------*/
std::string MODEL_BUILT_IN_MOS8::param_name(int i, int j)const
{
  if (j == 0) {
    return param_name(i);
  }else if (j == 1) {
    switch (MODEL_BUILT_IN_MOS8::param_count() - 1 - i) {
    case 0:  return "";
    case 1:  return "";
    case 2:  return "";
    case 3:  return "";
    case 4:  return "";
    case 5:  return "";
    case 6:  return "";
    case 7:  return "";
    case 8:  return "";
    case 9:  return "";
    case 10:  return "";
    case 11:  return "";
    case 12:  return "";
    case 13:  return "";
    case 14:  return "";
    case 15:  return "";
    case 16:  return "";
    case 17:  return "";
    case 18:  return "";
    case 19:  return "";
    case 20:  return "";
    case 21:  return "";
    case 22:  return "";
    case 23:  return "";
    case 24:  return "";
    case 25:  return "";
    case 26:  return "";
    case 27:  return "";
    case 28:  return "";
    case 29:  return "";
    case 30:  return "";
    case 31:  return "";
    case 32:  return "";
    case 33:  return "";
    case 34:  return "";
    case 35:  return "";
    case 36:  return "";
    case 37:  return "";
    case 38:  return "";
    case 39:  return "";
    case 40:  return "";
    case 41:  return "";
    case 42:  return "";
    case 43:  return "";
    case 44:  return "";
    case 45:  return "";
    case 46:  return "";
    case 47:  return "";
    case 48:  return "";
    case 49:  return "";
    case 50:  return "";
    case 51:  return "";
    case 52:  return "";
    case 53:  return "";
    case 54:  return "";
    case 55:  return "";
    case 56:  return "";
    case 57:  return "";
    case 58:  return "";
    case 59:  return "";
    case 60:  return "";
    case 61:  return "";
    case 62:  return "";
    case 63:  return "";
    case 64:  return "";
    case 65:  return "";
    case 66:  return "";
    case 67:  return "";
    case 68:  return "";
    case 69:  return "";
    case 70:  return "";
    case 71:  return "";
    case 72:  return "";
    case 73:  return "";
    case 74:  return "";
    case 75:  return "";
    case 76:  return "";
    case 77:  return "";
    case 78:  return "";
    case 79:  return "";
    case 80:  return "";
    case 81:  return "";
    case 82:  return "";
    case 83:  return "";
    case 84:  return "";
    case 85:  return "";
    case 86:  return "";
    case 87:  return "";
    case 88:  return "";
    case 89:  return "";
    case 90:  return "";
    case 91:  return "";
    case 92:  return "";
    case 93:  return "";
    case 94:  return "";
    case 95:  return "";
    case 96:  return "";
    case 97:  return "";
    case 98:  return "";
    case 99:  return "";
    case 100:  return "";
    case 101:  return "";
    case 102:  return "";
    case 103:  return "";
    case 104:  return "";
    case 105:  return "";
    case 106:  return "";
    case 107:  return "";
    case 108:  return "";
    case 109:  return "";
    case 110:  return "";
    case 111:  return "";
    case 112:  return "";
    case 113:  return "";
    case 114:  return "";
    case 115:  return "";
    case 116:  return "";
    case 117:  return "";
    case 118:  return "";
    case 119:  return "";
    case 120:  return "";
    case 121:  return "";
    case 122:  return "";
    case 123:  return "";
    case 124:  return "";
    case 125:  return "";
    case 126:  return "";
    case 127:  return "";
    case 128:  return "";
    case 129:  return "";
    case 130:  return "";
    case 131:  return "";
    case 132:  return "";
    case 133:  return "";
    case 134:  return "";
    case 135:  return "";
    case 136:  return "";
    case 137:  return "";
    case 138:  return "";
    case 139:  return "";
    case 140:  return "";
    case 141:  return "";
    case 142:  return "";
    case 143:  return "";
    case 144:  return "";
    case 145:  return "";
    case 146:  return "";
    case 147:  return "";
    case 148:  return "";
    case 149:  return "";
    case 150:  return "";
    case 151:  return "";
    case 152:  return "";
    case 153:  return "";
    case 154:  return "";
    case 155:  return "";
    case 156:  return "";
    case 157:  return "";
    case 158:  return "";
    case 159:  return "";
    case 160:  return "";
    case 161:  return "";
    case 162:  return "";
    case 163:  return "";
    case 164:  return "";
    case 165:  return "";
    case 166:  return "";
    case 167:  return "";
    case 168:  return "";
    case 169:  return "";
    case 170:  return "";
    case 171:  return "";
    case 172:  return "";
    case 173:  return "";
    case 174:  return "";
    case 175:  return "";
    case 176:  return "";
    case 177:  return "";
    case 178:  return "";
    case 179:  return "";
    case 180:  return "";
    case 181:  return "";
    case 182:  return "";
    case 183:  return "";
    case 184:  return "";
    case 185:  return "";
    case 186:  return "";
    case 187:  return "";
    case 188:  return "";
    case 189:  return "";
    case 190:  return "";
    case 191:  return "";
    case 192:  return "";
    case 193:  return "";
    case 194:  return "";
    case 195:  return "";
    case 196:  return "";
    case 197:  return "";
    case 198:  return "";
    case 199:  return "";
    case 200:  return "";
    case 201:  return "";
    case 202:  return "";
    case 203:  return "";
    case 204:  return "";
    case 205:  return "";
    case 206:  return "";
    case 207:  return "";
    case 208:  return "";
    case 209:  return "";
    case 210:  return "";
    case 211:  return "";
    case 212:  return "";
    case 213:  return "";
    case 214:  return "";
    case 215:  return "";
    case 216:  return "";
    case 217:  return "";
    case 218:  return "";
    case 219:  return "";
    case 220:  return "";
    case 221:  return "";
    case 222:  return "";
    case 223:  return "";
    case 224:  return "";
    case 225:  return "";
    case 226:  return "";
    case 227:  return "";
    case 228:  return "";
    case 229:  return "";
    case 230:  return "";
    case 231:  return "";
    case 232:  return "";
    case 233:  return "";
    case 234:  return "";
    case 235:  return "";
    case 236:  return "";
    case 237:  return "";
    case 238:  return "";
    case 239:  return "";
    case 240:  return "";
    case 241:  return "";
    case 242:  return "";
    case 243:  return "";
    case 244:  return "";
    case 245:  return "";
    case 246:  return "";
    case 247:  return "";
    case 248:  return "";
    case 249:  return "";
    case 250:  return "";
    case 251:  return "";
    case 252:  return "";
    case 253:  return "";
    case 254:  return "";
    case 255:  return "";
    case 256:  return "";
    case 257:  return "";
    case 258:  return "";
    case 259:  return "";
    case 260:  return "";
    case 261:  return "";
    case 262:  return "";
    case 263:  return "";
    case 264:  return "";
    case 265:  return "";
    case 266:  return "";
    case 267:  return "";
    case 268:  return "";
    case 269:  return "";
    case 270:  return "";
    case 271:  return "";
    case 272:  return "";
    case 273:  return "";
    case 274:  return "";
    case 275:  return "";
    case 276:  return "";
    case 277:  return "";
    case 278:  return "";
    case 279:  return "";
    case 280:  return "";
    case 281:  return "";
    case 282:  return "";
    case 283:  return "";
    case 284:  return "";
    case 285:  return "";
    case 286:  return "";
    case 287:  return "";
    case 288:  return "";
    case 289:  return "";
    case 290:  return "";
    case 291:  return "";
    case 292:  return "";
    case 293:  return "";
    case 294:  return "";
    case 295:  return "";
    case 296:  return "";
    case 297:  return "";
    case 298:  return "";
    case 299:  return "";
    case 300:  return "";
    case 301:  return "";
    case 302:  return "";
    case 303:  return "";
    case 304:  return "";
    case 305:  return "";
    case 306:  return "";
    case 307:  return "";
    case 308:  return "";
    case 309:  return "";
    case 310:  return "";
    case 311:  return "";
    case 312:  return "";
    case 313:  return "";
    case 314:  return "";
    case 315:  return "";
    case 316:  return "";
    case 317:  return "";
    case 318:  return "";
    case 319:  return "";
    case 320:  return "";
    case 321:  return "";
    case 322:  return "";
    case 323:  return "";
    case 324:  return "";
    case 325:  return "";
    case 326:  return "";
    case 327:  return "";
    case 328:  return "";
    case 329:  return "";
    case 330:  return "";
    case 331:  return "";
    case 332:  return "";
    case 333:  return "";
    case 334:  return "";
    case 335:  return "";
    case 336:  return "";
    case 337:  return "";
    case 338:  return "";
    case 339:  return "";
    case 340:  return "";
    case 341:  return "";
    case 342:  return "";
    case 343:  return "";
    case 344:  return "";
    case 345:  return "";
    case 346:  return "";
    case 347:  return "";
    case 348:  return "";
    case 349:  return "";
    case 350:  return "";
    case 351:  return "";
    case 352:  return "";
    case 353:  return "";
    case 354:  return "";
    case 355:  return "";
    case 356:  return "";
    case 357:  return "";
    case 358:  return "";
    case 359:  return "";
    case 360:  return "";
    case 361:  return "";
    case 362:  return "";
    case 363:  return "";
    case 364:  return "";
    case 365:  return "";
    case 366:  return "";
    case 367:  return "";
    case 368:  return "";
    case 369:  return "";
    case 370:  return "";
    case 371:  return "";
    case 372:  return "";
    case 373:  return "";
    case 374:  return "";
    case 375:  return "";
    case 376:  return "";
    case 377:  return "";
    case 378:  return "";
    case 379:  return "";
    case 380:  return "";
    case 381:  return "";
    case 382:  return "";
    case 383:  return "";
    case 384:  return "";
    case 385:  return "";
    case 386:  return "";
    case 387:  return "";
    case 388:  return "";
    case 389:  return "";
    case 390:  return "";
    case 391:  return "";
    case 392:  return "";
    case 393:  return "";
    case 394:  return "";
    default: return MODEL_BUILT_IN_MOS_BASE::param_name(i, j);
    }
  }else if (i < 395) {
    return "";
  }else{
    return MODEL_BUILT_IN_MOS_BASE::param_name(i, j);
  }
}
/*--------------------------------------------------------------------------*/
std::string MODEL_BUILT_IN_MOS8::param_value(int i)const
{
  switch (MODEL_BUILT_IN_MOS8::param_count() - 1 - i) {
  case 0:  return "8";
  case 1:  unreachable(); return "";
  case 2:  unreachable(); return "";
  case 3:  unreachable(); return "";
  case 4:  unreachable(); return "";
  case 5:  unreachable(); return "";
  case 6:  unreachable(); return "";
  case 7:  unreachable(); return "";
  case 8:  unreachable(); return "";
  case 9:  unreachable(); return "";
  case 10:  return mos_level.string();
  case 11:  return cdsc.string();
  case 12:  return cdsc.w_string();
  case 13:  return cdsc.l_string();
  case 14:  return cdsc.p_string();
  case 15:  return cdscb.string();
  case 16:  return cdscb.w_string();
  case 17:  return cdscb.l_string();
  case 18:  return cdscb.p_string();
  case 19:  return cdscd.string();
  case 20:  return cdscd.w_string();
  case 21:  return cdscd.l_string();
  case 22:  return cdscd.p_string();
  case 23:  return cit.string();
  case 24:  return cit.w_string();
  case 25:  return cit.l_string();
  case 26:  return cit.p_string();
  case 27:  return nfactor.string();
  case 28:  return nfactor.w_string();
  case 29:  return nfactor.l_string();
  case 30:  return nfactor.p_string();
  case 31:  return xj.string();
  case 32:  return xj.w_string();
  case 33:  return xj.l_string();
  case 34:  return xj.p_string();
  case 35:  return vsat.string();
  case 36:  return vsat.w_string();
  case 37:  return vsat.l_string();
  case 38:  return vsat.p_string();
  case 39:  return at.string();
  case 40:  return at.w_string();
  case 41:  return at.l_string();
  case 42:  return at.p_string();
  case 43:  return a0.string();
  case 44:  return a0.w_string();
  case 45:  return a0.l_string();
  case 46:  return a0.p_string();
  case 47:  return ags.string();
  case 48:  return ags.w_string();
  case 49:  return ags.l_string();
  case 50:  return ags.p_string();
  case 51:  return a1.string();
  case 52:  return a1.w_string();
  case 53:  return a1.l_string();
  case 54:  return a1.p_string();
  case 55:  return a2.string();
  case 56:  return a2.w_string();
  case 57:  return a2.l_string();
  case 58:  return a2.p_string();
  case 59:  return keta.string();
  case 60:  return keta.w_string();
  case 61:  return keta.l_string();
  case 62:  return keta.p_string();
  case 63:  return nsub.string();
  case 64:  return nsub.w_string();
  case 65:  return nsub.l_string();
  case 66:  return nsub.p_string();
  case 67:  return npeak.string();
  case 68:  return npeak.w_string();
  case 69:  return npeak.l_string();
  case 70:  return npeak.p_string();
  case 71:  return ngate.string();
  case 72:  return ngate.w_string();
  case 73:  return ngate.l_string();
  case 74:  return ngate.p_string();
  case 75:  return gamma1.string();
  case 76:  return gamma1.w_string();
  case 77:  return gamma1.l_string();
  case 78:  return gamma1.p_string();
  case 79:  return gamma2.string();
  case 80:  return gamma2.w_string();
  case 81:  return gamma2.l_string();
  case 82:  return gamma2.p_string();
  case 83:  return vbx.string();
  case 84:  return vbx.w_string();
  case 85:  return vbx.l_string();
  case 86:  return vbx.p_string();
  case 87:  return vbm.string();
  case 88:  return vbm.w_string();
  case 89:  return vbm.l_string();
  case 90:  return vbm.p_string();
  case 91:  return xt.string();
  case 92:  return xt.w_string();
  case 93:  return xt.l_string();
  case 94:  return xt.p_string();
  case 95:  return k1.string();
  case 96:  return k1.w_string();
  case 97:  return k1.l_string();
  case 98:  return k1.p_string();
  case 99:  return kt1.string();
  case 100:  return kt1.w_string();
  case 101:  return kt1.l_string();
  case 102:  return kt1.p_string();
  case 103:  return kt1l.string();
  case 104:  return kt1l.w_string();
  case 105:  return kt1l.l_string();
  case 106:  return kt1l.p_string();
  case 107:  return kt2.string();
  case 108:  return kt2.w_string();
  case 109:  return kt2.l_string();
  case 110:  return kt2.p_string();
  case 111:  return k2.string();
  case 112:  return k2.w_string();
  case 113:  return k2.l_string();
  case 114:  return k2.p_string();
  case 115:  return k3.string();
  case 116:  return k3.w_string();
  case 117:  return k3.l_string();
  case 118:  return k3.p_string();
  case 119:  return k3b.string();
  case 120:  return k3b.w_string();
  case 121:  return k3b.l_string();
  case 122:  return k3b.p_string();
  case 123:  return w0.string();
  case 124:  return w0.w_string();
  case 125:  return w0.l_string();
  case 126:  return w0.p_string();
  case 127:  return nlx.string();
  case 128:  return nlx.w_string();
  case 129:  return nlx.l_string();
  case 130:  return nlx.p_string();
  case 131:  return dvt0.string();
  case 132:  return dvt0.w_string();
  case 133:  return dvt0.l_string();
  case 134:  return dvt0.p_string();
  case 135:  return dvt1.string();
  case 136:  return dvt1.w_string();
  case 137:  return dvt1.l_string();
  case 138:  return dvt1.p_string();
  case 139:  return dvt2.string();
  case 140:  return dvt2.w_string();
  case 141:  return dvt2.l_string();
  case 142:  return dvt2.p_string();
  case 143:  return dvt0w.string();
  case 144:  return dvt0w.w_string();
  case 145:  return dvt0w.l_string();
  case 146:  return dvt0w.p_string();
  case 147:  return dvt1w.string();
  case 148:  return dvt1w.w_string();
  case 149:  return dvt1w.l_string();
  case 150:  return dvt1w.p_string();
  case 151:  return dvt2w.string();
  case 152:  return dvt2w.w_string();
  case 153:  return dvt2w.l_string();
  case 154:  return dvt2w.p_string();
  case 155:  return drout.string();
  case 156:  return drout.w_string();
  case 157:  return drout.l_string();
  case 158:  return drout.p_string();
  case 159:  return dsub.string();
  case 160:  return dsub.w_string();
  case 161:  return dsub.l_string();
  case 162:  return dsub.p_string();
  case 163:  return vth0.string();
  case 164:  return vth0.w_string();
  case 165:  return vth0.l_string();
  case 166:  return vth0.p_string();
  case 167:  return ua1.string();
  case 168:  return ua1.w_string();
  case 169:  return ua1.l_string();
  case 170:  return ua1.p_string();
  case 171:  return ua.string();
  case 172:  return ua.w_string();
  case 173:  return ua.l_string();
  case 174:  return ua.p_string();
  case 175:  return ub1.string();
  case 176:  return ub1.w_string();
  case 177:  return ub1.l_string();
  case 178:  return ub1.p_string();
  case 179:  return ub.string();
  case 180:  return ub.w_string();
  case 181:  return ub.l_string();
  case 182:  return ub.p_string();
  case 183:  return uc1.string();
  case 184:  return uc1.w_string();
  case 185:  return uc1.l_string();
  case 186:  return uc1.p_string();
  case 187:  return uc.string();
  case 188:  return uc.w_string();
  case 189:  return uc.l_string();
  case 190:  return uc.p_string();
  case 191:  return u0.string();
  case 192:  return u0.w_string();
  case 193:  return u0.l_string();
  case 194:  return u0.p_string();
  case 195:  return ute.string();
  case 196:  return ute.w_string();
  case 197:  return ute.l_string();
  case 198:  return ute.p_string();
  case 199:  return voff.string();
  case 200:  return voff.w_string();
  case 201:  return voff.l_string();
  case 202:  return voff.p_string();
  case 203:  return delta.string();
  case 204:  return delta.w_string();
  case 205:  return delta.l_string();
  case 206:  return delta.p_string();
  case 207:  return rdsw.string();
  case 208:  return rdsw.w_string();
  case 209:  return rdsw.l_string();
  case 210:  return rdsw.p_string();
  case 211:  return prwg.string();
  case 212:  return prwg.w_string();
  case 213:  return prwg.l_string();
  case 214:  return prwg.p_string();
  case 215:  return prwb.string();
  case 216:  return prwb.w_string();
  case 217:  return prwb.l_string();
  case 218:  return prwb.p_string();
  case 219:  return prt.string();
  case 220:  return prt.w_string();
  case 221:  return prt.l_string();
  case 222:  return prt.p_string();
  case 223:  return eta0.string();
  case 224:  return eta0.w_string();
  case 225:  return eta0.l_string();
  case 226:  return eta0.p_string();
  case 227:  return etab.string();
  case 228:  return etab.w_string();
  case 229:  return etab.l_string();
  case 230:  return etab.p_string();
  case 231:  return pclm.string();
  case 232:  return pclm.w_string();
  case 233:  return pclm.l_string();
  case 234:  return pclm.p_string();
  case 235:  return pdibl1.string();
  case 236:  return pdibl1.w_string();
  case 237:  return pdibl1.l_string();
  case 238:  return pdibl1.p_string();
  case 239:  return pdibl2.string();
  case 240:  return pdibl2.w_string();
  case 241:  return pdibl2.l_string();
  case 242:  return pdibl2.p_string();
  case 243:  return pdiblb.string();
  case 244:  return pdiblb.w_string();
  case 245:  return pdiblb.l_string();
  case 246:  return pdiblb.p_string();
  case 247:  return pscbe1.string();
  case 248:  return pscbe1.w_string();
  case 249:  return pscbe1.l_string();
  case 250:  return pscbe1.p_string();
  case 251:  return pscbe2.string();
  case 252:  return pscbe2.w_string();
  case 253:  return pscbe2.l_string();
  case 254:  return pscbe2.p_string();
  case 255:  return pvag.string();
  case 256:  return pvag.w_string();
  case 257:  return pvag.l_string();
  case 258:  return pvag.p_string();
  case 259:  return wr.string();
  case 260:  return wr.w_string();
  case 261:  return wr.l_string();
  case 262:  return wr.p_string();
  case 263:  return dwg.string();
  case 264:  return dwg.w_string();
  case 265:  return dwg.l_string();
  case 266:  return dwg.p_string();
  case 267:  return dwb.string();
  case 268:  return dwb.w_string();
  case 269:  return dwb.l_string();
  case 270:  return dwb.p_string();
  case 271:  return b0.string();
  case 272:  return b0.w_string();
  case 273:  return b0.l_string();
  case 274:  return b0.p_string();
  case 275:  return b1.string();
  case 276:  return b1.w_string();
  case 277:  return b1.l_string();
  case 278:  return b1.p_string();
  case 279:  return alpha0.string();
  case 280:  return alpha0.w_string();
  case 281:  return alpha0.l_string();
  case 282:  return alpha0.p_string();
  case 283:  return beta0.string();
  case 284:  return beta0.w_string();
  case 285:  return beta0.l_string();
  case 286:  return beta0.p_string();
  case 287:  return elm.string();
  case 288:  return elm.w_string();
  case 289:  return elm.l_string();
  case 290:  return elm.p_string();
  case 291:  return vfbcv.string();
  case 292:  return vfbcv.w_string();
  case 293:  return vfbcv.l_string();
  case 294:  return vfbcv.p_string();
  case 295:  return cgsl.string();
  case 296:  return cgsl.w_string();
  case 297:  return cgsl.l_string();
  case 298:  return cgsl.p_string();
  case 299:  return cgdl.string();
  case 300:  return cgdl.w_string();
  case 301:  return cgdl.l_string();
  case 302:  return cgdl.p_string();
  case 303:  return ckappa.string();
  case 304:  return ckappa.w_string();
  case 305:  return ckappa.l_string();
  case 306:  return ckappa.p_string();
  case 307:  return cf.string();
  case 308:  return cf.w_string();
  case 309:  return cf.l_string();
  case 310:  return cf.p_string();
  case 311:  return clc.string();
  case 312:  return clc.w_string();
  case 313:  return clc.l_string();
  case 314:  return clc.p_string();
  case 315:  return cle.string();
  case 316:  return cle.w_string();
  case 317:  return cle.l_string();
  case 318:  return cle.p_string();
  case 319:  return vfb.string();
  case 320:  return vfb.w_string();
  case 321:  return vfb.l_string();
  case 322:  return vfb.p_string();
  case 323:  return acde.string();
  case 324:  return acde.w_string();
  case 325:  return acde.l_string();
  case 326:  return acde.p_string();
  case 327:  return moin.string();
  case 328:  return moin.w_string();
  case 329:  return moin.l_string();
  case 330:  return moin.p_string();
  case 331:  return noff.string();
  case 332:  return noff.w_string();
  case 333:  return noff.l_string();
  case 334:  return noff.p_string();
  case 335:  return voffcv.string();
  case 336:  return voffcv.w_string();
  case 337:  return voffcv.l_string();
  case 338:  return voffcv.p_string();
  case 339:  return alpha1.string();
  case 340:  return alpha1.w_string();
  case 341:  return alpha1.l_string();
  case 342:  return alpha1.p_string();
  case 343:  return capMod.string();
  case 344:  return nqsMod.string();
  case 345:  return mobMod.string();
  case 346:  return noiMod.string();
  case 347:  return paramChk.string();
  case 348:  return binUnit.string();
  case 349:  return version.string();
  case 350:  return tox.string();
  case 351:  return xpart.string();
  case 352:  return jctSidewallSatCurDensity.string();
  case 353:  return mjswg.string();
  case 354:  return pbswg.string();
  case 355:  return unitLengthGateSidewallJctCap.string();
  case 356:  return jctEmissionCoeff.string();
  case 357:  return jctTempExponent.string();
  case 358:  return Lint.string();
  case 359:  return Ll.string();
  case 360:  return Lln.string();
  case 361:  return Lw.string();
  case 362:  return Lwn.string();
  case 363:  return Lwl.string();
  case 364:  return Wint.string();
  case 365:  return Wl.string();
  case 366:  return Wln.string();
  case 367:  return Ww.string();
  case 368:  return Wwn.string();
  case 369:  return Wwl.string();
  case 370:  return dwc.string();
  case 371:  return dlc.string();
  case 372:  return noia.string();
  case 373:  return noib.string();
  case 374:  return noic.string();
  case 375:  return em.string();
  case 376:  return ef.string();
  case 377:  return acnqsMod.string();
  case 378:  return toxm.string();
  case 379:  return lintnoi.string();
  case 380:  return ijth.string();
  case 381:  return tpb.string();
  case 382:  return tcj.string();
  case 383:  return tpbsw.string();
  case 384:  return tcjsw.string();
  case 385:  return tpbswg.string();
  case 386:  return tcjswg.string();
  case 387:  return Llc.string();
  case 388:  return Lwc.string();
  case 389:  return Lwlc.string();
  case 390:  return Wlc.string();
  case 391:  return Wwc.string();
  case 392:  return Wwlc.string();
  case 393:  return acm.string();
  case 394:  return h0.string();
  default: return MODEL_BUILT_IN_MOS_BASE::param_value(i);
  }
}
/*--------------------------------------------------------------------------*/
bool MODEL_BUILT_IN_MOS8::is_valid(const COMPONENT* d)const
{
  assert(d);
  return MODEL_BUILT_IN_MOS_BASE::is_valid(d);
}
/*--------------------------------------------------------------------------*/
void MODEL_BUILT_IN_MOS8::tr_eval(COMPONENT* brh)const
{
  DEV_BUILT_IN_MOS* d = prechecked_cast<DEV_BUILT_IN_MOS*>(brh);
  assert(d);
  const ADP_BUILT_IN_MOS* a = asserted_cast<const ADP_BUILT_IN_MOS*>(d->adp());
  const COMMON_BUILT_IN_MOS* c = prechecked_cast<const COMMON_BUILT_IN_MOS*>(d->common());
  assert(c);
  const SDP_BUILT_IN_MOS8* s = prechecked_cast<const SDP_BUILT_IN_MOS8*>(c->sdp());
  assert(s);
  const MODEL_BUILT_IN_MOS8* m = this;
  const TDP_BUILT_IN_MOS8 T(d);
  const TDP_BUILT_IN_MOS8* t = &T;

  if (0 && polarity == -1){
    d->qgs *= -1;
    d->qbd *= -1;
    d->qbs *= -1;
    d->qgd *= -1;
    d->qdrn *= -1;
  }

    trace3("", d->vds, d->vgs, d->vbs);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    const double EXP_THRESHOLD = 34.0;
    const double MIN_EXP = 1.713908431e-15;
    const double MAX_EXP = 5.834617425e14;
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    d->reverse_if_needed();
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    double Vbseff, dVbseff_dVb;
    {
      double T0 = d->vbs - t->vbsc - 0.001;
      double T1 = sqrt(T0 * T0 - 0.004 * t->vbsc);
      trace3("", t->vbsc, T0, T1);
      Vbseff = t->vbsc + 0.5 * (T0 + T1);
      dVbseff_dVb = 0.5 * (1.0 + T0 / T1);
      trace2("raw", Vbseff, dVbseff_dVb);

      fixzero(&Vbseff, t->vbsc);
      if (Vbseff < d->vbs) {	// From Spice, to fix numeric problems
	//untested();		// inadequately.  Above fixzero should do a 
	Vbseff = d->vbs;	// better job, but I left this in case.
      }
    }
    trace2("fixed", Vbseff, dVbseff_dVb);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    double Phis, dPhis_dVb, sqrtPhis, dsqrtPhis_dVb;
    if (Vbseff > 0.0) {
	//untested();
      d->sbfwd = true;
      double T0 = t->phi / (t->phi + Vbseff);
      Phis = t->phi * T0;
      dPhis_dVb = -T0 * T0;
      sqrtPhis = t->phis3 / (t->phi + 0.5 * Vbseff);
      dsqrtPhis_dVb = -0.5 * sqrtPhis * sqrtPhis / t->phis3;
      trace0("bs-fwd-bias");
    }else{
      d->sbfwd = false;
      Phis = t->phi - Vbseff;
      dPhis_dVb = -1.0;
      sqrtPhis = sqrt(Phis);
      dsqrtPhis_dVb = -0.5 / sqrtPhis;
      trace0("bs-normal");
    }
    trace4("", Phis, dPhis_dVb, sqrtPhis, dsqrtPhis_dVb);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    double Xdep = t->Xdep0 * sqrtPhis / t->sqrtPhi;
    double dXdep_dVb = (t->Xdep0 / t->sqrtPhi) * dsqrtPhis_dVb;
    trace2("", Xdep, dXdep_dVb);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    double Theta0, dTheta0_dVb;
    {
      double lt1, dlt1_dVb;
      {
	double T3 = sqrt(Xdep);
	double T0 = s->dvt2 * Vbseff;
	double T1, T2;
	if (T0 >= - 0.5) {
	  T1 = 1.0 + T0;
	  T2 = s->dvt2;
	  trace4("", T0, T1, T2, T3);
	}else{
	  //untested();
	  /* Added to avoid any discontinuity problems caused by dvt2 */ 
	  double T4 = 1.0 / (3.0 + 8.0 * T0);
	  T1 = (1.0 + 3.0 * T0) * T4; 
	  T2 = s->dvt2 * T4 * T4;
	  trace4("dvd2 fix", T0, T1, T2, T3);
	}
	lt1 = m->factor1 * T3 * T1;
	dlt1_dVb = m->factor1 * (0.5 / T3 * T1 * dXdep_dVb + T3 * T2);
      }
      trace2("", lt1, dlt1_dVb);

      double T0 = -0.5 * s->dvt1 * s->leff / lt1;
      if (T0 > -EXP_THRESHOLD) {
	double T1 = exp(T0);
	Theta0 = T1 * (1.0 + 2.0 * T1);
	double dT1_dVb = -T0 / lt1 * T1 * dlt1_dVb;
	dTheta0_dVb = (1.0 + 4.0 * T1) * dT1_dVb;
	trace2("T0 > -ET", Theta0, dTheta0_dVb);
      }else{
	double T1 = MIN_EXP;
	Theta0 = T1 * (1.0 + 2.0 * T1);
	dTheta0_dVb = 0.0;
	trace2("T0 < -ET", Theta0, dTheta0_dVb);
      }
    }
    trace2("", Theta0, dTheta0_dVb);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    double dVth_dVb, dVth_dVd; // d->von
    {
      double V0 = t->vbi - t->phi;
      double T2, dT2_dVb;
      {
	double ltw, dltw_dVb;
	{
	  double T3 = sqrt(Xdep);
	  double T0 = s->dvt2w * Vbseff;
	  double T1, t2;
	  if (T0 >= - 0.5) {
	    T1 = 1.0 + T0;
	    t2 = s->dvt2w;
	  }else{
	   // untested();
	    /* Added to avoid any discontinuity problems caused by dvt2w */ 
	    double T4 = 1.0 / (3.0 + 8.0 * T0);
	    T1 = (1.0 + 3.0 * T0) * T4; 
	    t2 = s->dvt2w * T4 * T4;
	  }
	  trace4("", T0, T1, t2, T3);
	  ltw = m->factor1 * T3 * T1;
	  dltw_dVb = m->factor1 * (0.5 / T3 * T1 * dXdep_dVb + T3 * t2);
	}
	trace2("", ltw, dltw_dVb);
	double T0 = -0.5 * s->dvt1w * s->weff * s->leff / ltw;
	if (T0 > -EXP_THRESHOLD) {
	  double T1 = exp(T0);
	  T2 = T1 * (1.0 + 2.0 * T1);
	  double dT1_dVb = -T0 / ltw * T1 * dltw_dVb;
	  dT2_dVb = (1.0 + 4.0 * T1) * dT1_dVb;
	}else{
	  double T1 = MIN_EXP;
	  T2 = T1 * (1.0 + 2.0 * T1);
	  dT2_dVb = 0.0;
	}
	T0 = s->dvt0w * T2;
	T2 = T0 * V0;
	dT2_dVb = s->dvt0w * dT2_dVb * V0;
      }
      trace3("", V0, T2, dT2_dVb);
      double T0 = sqrt(1.0 + s->nlx / s->leff);
      double T1 = t->k1ox * (T0 - 1.0) * t->sqrtPhi
	+ (s->kt1 + s->kt1l / s->leff + s->kt2 * Vbseff) * t->tempratio_1;
      double tmp2 = m->tox * t->phi / (s->weff + s->w0);
      
      double T3 = s->eta0 + s->etab * Vbseff;
      trace4("", T0, T1, tmp2, T3);
      double T4;
      if (T3 < 1.0e-4) {
	itested(); // not really.
	/* avoid  discontinuity problems caused by etab */ 
	double T9 = 1.0 / (3.0 - 2.0e4 * T3);
	T3 = (2.0e-4 - T3) * T9;
	T4 = T9 * T9;
	trace3("", T9, T3, T4);
      }else{
	T4 = 1.0;
	trace1("", T4);
      }
      double thetavth = s->dvt0 * Theta0;
      double Delt_vth = thetavth * V0;
      double dDelt_vth_dVb = s->dvt0 * dTheta0_dVb * V0;
      trace4("", thetavth, t->theta0vb0, Delt_vth, dDelt_vth_dVb);
      double dDIBL_Sft_dVd = T3 * t->theta0vb0;
      double DIBL_Sft = dDIBL_Sft_dVd * d->vds;
      trace2("", dDIBL_Sft_dVd, DIBL_Sft);
      
      trace4("", t->vth0, t->k1, sqrtPhis, t->sqrtPhi);
      trace4("", t->k2, Vbseff, Delt_vth, T2);
      trace4("", s->k3, s->k3b, Vbseff, tmp2);
      trace2("", T1, DIBL_Sft);
      double Vth = m->polarity * t->vth0
                 + t->k1ox * sqrtPhis
                 - t->k1 *  t->sqrtPhi
                 - t->k2ox * Vbseff
                 - Delt_vth
                 - T2
                 + (s->k3 + s->k3b * Vbseff) * tmp2
                 + T1
                 - DIBL_Sft;

      trace5("DEV_BUILT_IN_MOS::tr_eval", Vth, polarity,
          _sim->tt_iteration_number(), _sim->iteration_number(), a->delta_vth);
      // assert(polarity*Vth>0);

      trace1("MOS8 delta", a->delta_vth);
      if ( !(Vth<0 || a->delta_vth>=-1e-10)
         ||!(Vth>0 || a->delta_vth<= 1e-10) ){
        error(bDANGER,"mos8: dvth went wrong %E, %E\n", Vth, a->delta_vth);
      }
      assert(fabs(a->delta_vth)<10);
      Vth += a->delta_vth;
      d->von = Vth;
      
      dVth_dVb = t->k1ox * dsqrtPhis_dVb - t->k2ox  - dDelt_vth_dVb - dT2_dVb
	+ s->k3b * tmp2 - s->etab * d->vds * t->theta0vb0 * T4
	+ s->kt2 * t->tempratio_1;
      dVth_dVd = -dDIBL_Sft_dVd; 
    }
    trace1("", d->von);
    trace1("", dVth_dVb);
    trace1("", dVth_dVd);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    /* Calculate n */
    double n, dn_dVb, dn_dVd;
    {
      double tmp2 = s->nfactor * P_EPS_SI / Xdep;
      double tmp3 = s->cdsc + s->cdscb * Vbseff + s->cdscd * d->vds;
      double tmp4 = (tmp2 + tmp3 * Theta0 + s->cit) / m->cox;
      trace3("", tmp2, tmp3, tmp4);
      if (tmp4 >= -0.5) {
	n = 1.0 + tmp4;
	dn_dVb = (-tmp2 / Xdep * dXdep_dVb + tmp3 * dTheta0_dVb 
		  + s->cdscb * Theta0) / m->cox;
	dn_dVd = s->cdscd * Theta0 / m->cox;
	trace3("n", n, dn_dVb, dn_dVd);
      }else{
	/* avoid  discontinuity problems caused by tmp4 */ 
	double T0 = 1.0 / (3.0 + 8.0 * tmp4);
	n = (1.0 + 3.0 * tmp4) * T0;
	T0 *= T0;
	dn_dVb = (-tmp2 / Xdep * dXdep_dVb + tmp3 * dTheta0_dVb
		  + s->cdscb * Theta0) / m->cox * T0;
	dn_dVd = s->cdscd * Theta0 / m->cox * T0;
	trace3("n disc", n, dn_dVb, dn_dVd);
      }
    }
    trace3("", n, dn_dVb, dn_dVd);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    /* Poly Gate Si Depletion Effect */
    double Vgs_eff, dVgs_eff_dVg;
    {
      double T0 = t->vfb + t->phi;
      trace2("Poly", t->vfb, t->phi);
      trace3("", s->ngate, d->vgs, T0);
      if ((s->ngate > 1.e18) && (s->ngate < 1.e25) && (d->vgs > T0)) {
	/* added to avoid the problem caused by ngate */
	double T1 = 1.0e6 * P_Q * P_EPS_SI * s->ngate / (m->cox * m->cox);
	double T4 = sqrt(1.0 + 2.0 * (d->vgs - T0) / T1);
	double T2 = T1 * (T4 - 1.0);
	double T3 = 0.5 * T2 * T2 / T1; /* T3 = Vpoly */
	double T7 = 1.12 - T3 - 0.05;
	double T6 = sqrt(T7 * T7 + 0.224);
	double T5 = 1.12 - 0.5 * (T7 + T6);
	Vgs_eff = d->vgs - T5;
	dVgs_eff_dVg = 1.0 - (0.5 - 0.5 / T4) * (1.0 + T7 / T6);
	trace2("><", Vgs_eff, dVgs_eff_dVg);
      }else{
	Vgs_eff = d->vgs;
	dVgs_eff_dVg = 1.0;
	trace2("const", Vgs_eff, dVgs_eff_dVg);
      }
    }
    trace2("", Vgs_eff, dVgs_eff_dVg);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    /* Effective Vgst (Vgsteff) Calculation */
    double /*Vgsteff,*/ dVgsteff_dVg, dVgsteff_dVd, dVgsteff_dVb, Vgst2Vtm;
    // d->vgst
    {
      double Vgst = Vgs_eff - d->von;
      double T10 = 2.0 * n * t->vtm;
      double VgstNVt = Vgst / T10;
      double ExpArg = (2.0 * s->voff - Vgst) / T10;
      trace4("", Vgst, T10, VgstNVt, ExpArg);

      /* MCJ: Very small Vgst */
      if (VgstNVt > EXP_THRESHOLD) {
	d->vgst = Vgst;
	dVgsteff_dVg = dVgs_eff_dVg;
	dVgsteff_dVd = -dVth_dVd;
	dVgsteff_dVb = -dVth_dVb;
	trace4(">>", d->vgst, dVgsteff_dVg, dVgsteff_dVd, dVgsteff_dVb);
      }else if (ExpArg > EXP_THRESHOLD) {
	double T0 = (Vgst - s->voff) / (n * t->vtm);
	double ExpVgst = exp(T0);
	d->vgst = t->vtm * t->cdep0 / m->cox * ExpVgst;
	dVgsteff_dVg = d->vgst / (n * t->vtm);
	dVgsteff_dVd = -dVgsteff_dVg * (dVth_dVd + T0 * t->vtm * dn_dVd);
	dVgsteff_dVb = -dVgsteff_dVg * (dVth_dVb + T0 * t->vtm * dn_dVb);
	dVgsteff_dVg *= dVgs_eff_dVg;
	trace4(">", d->vgst, dVgsteff_dVg, dVgsteff_dVd, dVgsteff_dVb);
      }else{
	double ExpVgst = exp(VgstNVt);
	double T1 = T10 * log(1.0 + ExpVgst);
	double dT1_dVg = ExpVgst / (1.0 + ExpVgst);
	double dT1_dVb = -dT1_dVg * (dVth_dVb + Vgst / n * dn_dVb)
		      + T1 / n * dn_dVb; 
	double dT1_dVd = -dT1_dVg * (dVth_dVd + Vgst / n * dn_dVd)
		      + T1 / n * dn_dVd;

	double dT2_dVg = -m->cox / (t->vtm * t->cdep0)
		      * exp(ExpArg);
	double T2 = 1.0 - T10 * dT2_dVg;
	double dT2_dVd = -dT2_dVg * (dVth_dVd - 2.0 * t->vtm * ExpArg * dn_dVd)
		      + (T2 - 1.0) / n * dn_dVd;
	double dT2_dVb = -dT2_dVg * (dVth_dVb - 2.0 * t->vtm * ExpArg * dn_dVb)
		      + (T2 - 1.0) / n * dn_dVb;

	d->vgst = T1 / T2;
	double T3 = T2 * T2;
	dVgsteff_dVg = (T2 * dT1_dVg - T1 * dT2_dVg) / T3 * dVgs_eff_dVg;
	dVgsteff_dVd = (T2 * dT1_dVd - T1 * dT2_dVd) / T3;
	dVgsteff_dVb = (T2 * dT1_dVb - T1 * dT2_dVb) / T3;
	trace4("<", d->vgst, dVgsteff_dVg, dVgsteff_dVd, dVgsteff_dVb);
      }
      Vgst2Vtm = d->vgst + 2.0 * t->vtm;
      trace3("", d->vgst, t->vtm, Vgst2Vtm);
    }
    trace1("", d->vgst);
    trace4("", dVgsteff_dVg, dVgsteff_dVd, dVgsteff_dVb, Vgst2Vtm);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    /* Calculate Effective Channel Geometry */
    double Weff, dWeff_dVg, dWeff_dVb;
    {
      double T9 = sqrtPhis - t->sqrtPhi;
      Weff = s->weff - 2.0 * (s->dwg * d->vgst + s->dwb * T9); 
      dWeff_dVg = -2.0 * s->dwg;
      dWeff_dVb = -2.0 * s->dwb * dsqrtPhis_dVb;

      if (Weff < 2.0e-8) {
	/* to avoid the discontinuity problem due to Weff*/
	double T0 = 1.0 / (6.0e-8 - 2.0 * Weff);
	Weff = 2.0e-8 * (4.0e-8 - Weff) * T0;
	T0 *= T0 * 4.0e-16;
	dWeff_dVg *= T0;
	dWeff_dVb *= T0;
	trace3("Weff fix", Weff, dWeff_dVg, dWeff_dVb);
      }
    }
    trace3("", Weff, dWeff_dVg, dWeff_dVb);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    double Rds, dRds_dVg, dRds_dVb;
    {
      double T9 = sqrtPhis - t->sqrtPhi;
      double T0 = s->prwg * d->vgst + s->prwb * T9;
      if (T0 >= -0.9) {
	Rds = t->rds0 * (1.0 + T0);
	dRds_dVg = t->rds0 * s->prwg;
	dRds_dVb = t->rds0 * s->prwb * dsqrtPhis_dVb;
      }else{
	/* to avoid the discontinuity problem due to prwg and prwb*/
	double T1 = 1.0 / (17.0 + 20.0 * T0);
	Rds = t->rds0 * (0.8 + T0) * T1;
	T1 *= T1;
	dRds_dVg = t->rds0 * s->prwg * T1;
	dRds_dVb = t->rds0 * s->prwb * dsqrtPhis_dVb * T1;
	trace3("Rds fix", T9, T0, T1);
	trace3("Rds fix", Rds, dRds_dVg, dRds_dVb);
      }
      ////////// d->rds = Rds /* Noise Bugfix */
    }
    trace3("", Rds, dRds_dVg, dRds_dVb);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    /* Calculate Abulk */
    double Abulk0, dAbulk0_dVb, dAbulk_dVg, Abulk, dAbulk_dVb;
    {
      double T1 = 0.5 * t->k1ox / sqrtPhis;
      double dT1_dVb = -T1 / sqrtPhis * dsqrtPhis_dVb;

      double T9 = sqrt(s->xj * Xdep);
      double tmp1 = s->leff + 2.0 * T9;
      double T5 = s->leff / tmp1; 
      double tmp2 = s->a0 * T5;
      double tmp3 = s->weff + s->b1; 
      double tmp4 = s->b0 / tmp3;
      double T2 = tmp2 + tmp4;
      double dT2_dVb = -T9 / tmp1 / Xdep * dXdep_dVb;
      double T6 = T5 * T5;
      double T7 = T5 * T6;

      Abulk0 = 1.0 + T1 * T2; 
      dAbulk0_dVb = T1 * tmp2 * dT2_dVb + T2 * dT1_dVb;

      double T8 = s->ags * s->a0 * T7;
      dAbulk_dVg = -T1 * T8;
      Abulk = Abulk0 + dAbulk_dVg * d->vgst; 
      dAbulk_dVb = dAbulk0_dVb - T8 * d->vgst * (dT1_dVb + 3.0 * T1 * dT2_dVb);

      trace2("1", Abulk0, dAbulk0_dVb);
      trace3("1", dAbulk_dVg, Abulk, dAbulk_dVb);

      if (Abulk0 < 0.1) {
	/* added to avoid the problems caused by Abulk0 */
	double t9 = 1.0 / (3.0 - 20.0 * Abulk0);
	Abulk0 = (0.2 - Abulk0) * t9;
	dAbulk0_dVb *= t9 * t9;
	trace2("2", Abulk0, dAbulk0_dVb);
      }
      if (Abulk < 0.1) {
	/* added to avoid the problems caused by Abulk */
	double t9 = 1.0 / (3.0 - 20.0 * Abulk);
	Abulk = (0.2 - Abulk) * t9;
	double T10 = t9 * t9;
	dAbulk_dVb *= T10;
	dAbulk_dVg *= T10;
	trace3("2", dAbulk_dVg, Abulk, dAbulk_dVb);
      }
      ////////// d->Abulk = Abulk

      double T0, dT0_dVb;
      {
	double t2 = s->keta * Vbseff;
	if (t2 >= -0.9) {
	  T0 = 1.0 / (1.0 + t2);
	  dT0_dVb = -s->keta * T0 * T0;
	  trace3("", t2, T0, dT0_dVb);
	}else{
	  /* added to avoid the problems caused by Keta */
	  double t1 = 1.0 / (0.8 + t2);
	  T0 = (17.0 + 20.0 * t2) * t1;
	  dT0_dVb = -s->keta * t1 * t1;
	  trace3("keta fix", t2, T0, dT0_dVb);
	}
      }
      dAbulk_dVg *= T0;
      dAbulk_dVb = dAbulk_dVb * T0 + Abulk * dT0_dVb;
      dAbulk0_dVb = dAbulk0_dVb * T0 + Abulk0 * dT0_dVb;
      Abulk *= T0;
      Abulk0 *= T0;
      ////////// d->AbovVgst2Vtm = Abulk / Vgst2Vtm
    }
    trace2("", Abulk0, dAbulk0_dVb);
    trace3("", dAbulk_dVg, Abulk, dAbulk_dVb);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    /* Mobility calculation */
    double ueff, dueff_dVg, dueff_dVd, dueff_dVb;
    {
      double Denomi, dDenomi_dVg, dDenomi_dVd, dDenomi_dVb;
      {
	double T5;
	if (m->mobMod == 1) {
	  double T0 = d->vgst + d->von + d->von;
	  double T2 = t->ua + t->uc * Vbseff;
	  double T3 = T0 / m->tox;
	  T5 = T3 * (T2 + t->ub * T3);
	  dDenomi_dVg = (T2 + 2.0 * t->ub * T3) / m->tox;
	  dDenomi_dVd = dDenomi_dVg * 2.0 * dVth_dVd;
	  dDenomi_dVb = dDenomi_dVg * 2.0 * dVth_dVb + t->uc * T3;
	}else if (m->mobMod == 2) {
	  T5 = d->vgst / m->tox 
	    * (t->ua + t->uc * Vbseff + t->ub * d->vgst / m->tox);
	  dDenomi_dVg = (t->ua + t->uc * Vbseff + 2.0 * t->ub * d->vgst / m->tox)
	    / m->tox;
	  dDenomi_dVd = 0.0;
	  dDenomi_dVb = d->vgst * t->uc / m->tox; 
	}else{
	  double T0 = d->vgst + d->von + d->von;
	  double T2 = 1.0 + t->uc * Vbseff;
	  double T3 = T0 / m->tox;
	  double T4 = T3 * (t->ua + t->ub * T3);
	  T5 = T4 * T2;
	  dDenomi_dVg = (t->ua + 2.0 * t->ub * T3) * T2 / m->tox;
	  dDenomi_dVd = dDenomi_dVg * 2.0 * dVth_dVd;
	  dDenomi_dVb = dDenomi_dVg * 2.0 * dVth_dVb + t->uc * T4;
	}
	if (T5 >= -0.8) {
	  Denomi = 1.0 + T5;
	}else{
	  /* Added to avoid the discontinuity problem caused by ua and ub*/ 
	  double T9 = 1.0 / (7.0 + 10.0 * T5);
	  Denomi = (0.6 + T5) * T9;
	  T9 *= T9;
	  dDenomi_dVg *= T9;
	  dDenomi_dVd *= T9;
	  dDenomi_dVb *= T9;
	}
      }
      ueff = t->u0temp / Denomi;
      double T9 = -ueff / Denomi;
      dueff_dVg = T9 * dDenomi_dVg;
      dueff_dVd = T9 * dDenomi_dVd;
      dueff_dVb = T9 * dDenomi_dVb;
    }
    trace4("", ueff, dueff_dVg, dueff_dVd, dueff_dVb);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    double Esat, EsatL, dEsatL_dVg, dEsatL_dVd, dEsatL_dVb;
    {
      Esat = 2.0 * t->vsattemp / ueff;
      EsatL = Esat * s->leff;
      double T0 = -EsatL /ueff;
      dEsatL_dVg = T0 * dueff_dVg;
      dEsatL_dVd = T0 * dueff_dVd;
      dEsatL_dVb = T0 * dueff_dVb;
    }
    trace2("", Esat, EsatL);
    trace3("", dEsatL_dVg, dEsatL_dVd, dEsatL_dVb);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    /* Saturation Drain Voltage Vdsat */
    double Vdsat, dVdsat_dVg, dVdsat_dVd, dVdsat_dVb; // d->vdsat
    double Vasat, dVasat_dVg, dVasat_dVb, dVasat_dVd;
    {
      double WVCoxRds;
      {
	double WVCox = Weff * t->vsattemp * m->cox;
	WVCoxRds = WVCox * Rds;
      }
      trace1("", WVCoxRds);

      double Lambda, dLambda_dVg;
      {
	if (s->a1 == 0.0) {
	  Lambda = s->a2;
	  dLambda_dVg = 0.0;
	}else if (s->a1 > 0.0) {
	  /* avoid discontinuity problem caused by s->a1 and s->a2 (Lambda) */
	  double T0 = 1.0 - s->a2;
	  double T1 = T0 - s->a1 * d->vgst - 0.0001;
	  double T2 = sqrt(T1 * T1 + 0.0004 * T0);
	  Lambda = s->a2 + T0 - 0.5 * (T1 + T2);
	  dLambda_dVg = 0.5 * s->a1 * (1.0 + T1 / T2);
	}else{
	  double T1 = s->a2 + s->a1 * d->vgst - 0.0001;
	  double T2 = sqrt(T1 * T1 + 0.0004 * s->a2);
	  Lambda = 0.5 * (T1 + T2);
	  dLambda_dVg = 0.5 * s->a1 * (1.0 + T1 / T2);
	}
      }
      trace2("", Lambda, dLambda_dVg);

      double tmp2, tmp3;
      if (Rds > 0) {
	tmp2 = dRds_dVg / Rds + dWeff_dVg / Weff;
	tmp3 = dRds_dVb / Rds + dWeff_dVb / Weff;
      }else{
	tmp2 = dWeff_dVg / Weff;
	tmp3 = dWeff_dVb / Weff;
      }
      trace2("", tmp2, tmp3);

      //double Vdsat, dVdsat_dVg, dVdsat_dVd, dVdsat_dVb; // d->vdsat
      double tmp1;
      {
	if ((Rds == 0.0) && (Lambda == 1.0)) {
	  double T0 = 1.0 / (Abulk * EsatL + Vgst2Vtm);
	  tmp1 = 0.0;
	  double T1 = T0 * T0;
	  double T2 = Vgst2Vtm * T0;
	  double T3 = EsatL * Vgst2Vtm;
	  Vdsat = T3 * T0;
	  double dT0_dVg = -(Abulk * dEsatL_dVg + EsatL * dAbulk_dVg + 1.0)*T1;
	  double dT0_dVd = -(Abulk * dEsatL_dVd) * T1; 
	  double dT0_dVb = -(Abulk * dEsatL_dVb + dAbulk_dVb * EsatL) * T1;   
	  dVdsat_dVg = T3 * dT0_dVg + T2 * dEsatL_dVg + EsatL * T0;
	  dVdsat_dVd = T3 * dT0_dVd + T2 * dEsatL_dVd;
	  dVdsat_dVb = T3 * dT0_dVb + T2 * dEsatL_dVb;   
	}else{
	  tmp1 = dLambda_dVg / (Lambda * Lambda);
	  double T9 = Abulk * WVCoxRds;
	  double T8 = Abulk * T9;
	  double T7 = Vgst2Vtm * T9;
	  double T6 = Vgst2Vtm * WVCoxRds;
	  double T0 = 2.0 * Abulk * (T9 - 1.0 + 1.0 / Lambda);  // 2.0 * Abulk * T9
	  double dT0_dVg = 2.0 * (T8 * tmp2 - Abulk * tmp1
			+ (2.0 * T9 + 1.0 / Lambda - 1.0) * dAbulk_dVg);
	  double dT0_dVb = 2.0 * (T8 * (2.0 / Abulk * dAbulk_dVb + tmp3)
				  + (1.0 / Lambda - 1.0) * dAbulk_dVb);
	  //double dT0_dVd = 0.0;
	  
	  double T1 = Vgst2Vtm * (2.0 / Lambda - 1.0) + Abulk * EsatL + 3.0*T7;
	  double dT1_dVg = (2.0 / Lambda - 1.0) - 2.0 * Vgst2Vtm * tmp1
	    + Abulk * dEsatL_dVg + EsatL * dAbulk_dVg 
	    + 3.0 * (T9 + T7 * tmp2 + T6 * dAbulk_dVg);
	  double dT1_dVb = Abulk * dEsatL_dVb + EsatL * dAbulk_dVb
	    + 3.0 * (T6 * dAbulk_dVb + T7 * tmp3);
	  double dT1_dVd = Abulk * dEsatL_dVd;
	  
	  double T2 = Vgst2Vtm * (EsatL + 2.0 * T6);
	  double dT2_dVg = EsatL + Vgst2Vtm * dEsatL_dVg
	    + T6 * (4.0 + 2.0 * Vgst2Vtm * tmp2);
	  double dT2_dVb = Vgst2Vtm * (dEsatL_dVb + 2.0 * T6 * tmp3);
	  double dT2_dVd = Vgst2Vtm * dEsatL_dVd;
	  
	  double T3 = sqrt(T1 * T1 - 2.0 * T0 * T2);
	  Vdsat = (T1 - T3) / T0;
	  dVdsat_dVg = (dT1_dVg - (T1 * dT1_dVg - dT0_dVg * T2
				- T0 * dT2_dVg) / T3 - Vdsat * dT0_dVg) / T0;
	  dVdsat_dVb = (dT1_dVb - (T1 * dT1_dVb - dT0_dVb * T2
				- T0 * dT2_dVb) / T3 - Vdsat * dT0_dVb) / T0;
	  dVdsat_dVd = (dT1_dVd - (T1 * dT1_dVd - T0 * dT2_dVd) / T3) / T0;
	}
	d->vdsat = Vdsat;
	d->saturated = (d->vds >= d->vdsat);
      }
      trace1("", tmp1);
      trace4("d->vdsat", Vdsat, dVdsat_dVg, dVdsat_dVd, dVdsat_dVb);

      /* Calculate VAsat */
      // double Vasat, dVasat_dVg, dVasat_dVb, dVasat_dVd;
      {
	double tmp4 = 1.0 - 0.5 * Abulk * Vdsat / Vgst2Vtm;
	double T9 = WVCoxRds * d->vgst;
	double T8 = T9 / Vgst2Vtm;
	double T0 = EsatL + Vdsat + 2.0 * T9 * tmp4;
	double T7 = 2.0 * WVCoxRds * tmp4;
	double dT0_dVg = dEsatL_dVg + dVdsat_dVg + T7 * (1.0 + tmp2 * d->vgst)
	  - T8 * (Abulk * dVdsat_dVg - Abulk * Vdsat / Vgst2Vtm
		  + Vdsat * dAbulk_dVg);   
	double dT0_dVb = dEsatL_dVb + dVdsat_dVb + T7 * tmp3 * d->vgst
	  - T8 * (dAbulk_dVb * Vdsat + Abulk * dVdsat_dVb);
	double dT0_dVd = dEsatL_dVd + dVdsat_dVd - T8 * Abulk * dVdsat_dVd;
	T9 = WVCoxRds * Abulk; 
	double T1 = 2.0 / Lambda - 1.0 + T9; 
	double dT1_dVg = -2.0 * tmp1 +  WVCoxRds * (Abulk * tmp2 + dAbulk_dVg);
	double dT1_dVb = dAbulk_dVb * WVCoxRds + T9 * tmp3;
	Vasat = T0 / T1;
	dVasat_dVg = (dT0_dVg - Vasat * dT1_dVg) / T1;
	dVasat_dVb = (dT0_dVb - Vasat * dT1_dVb) / T1;
	dVasat_dVd = dT0_dVd / T1;
      }
      trace4("", Vasat, dVasat_dVg, dVasat_dVb, dVasat_dVd);
    }
    trace1("", d->vdsat);
    trace4("", Vdsat, dVdsat_dVg, dVdsat_dVd, dVdsat_dVb);
    trace4("", Vasat, dVasat_dVg, dVasat_dVb, dVasat_dVd);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    /* Effective Vds (Vdseff) Calculation */
    double Vdseff, diffVds, dVdseff_dVg, dVdseff_dVd, dVdseff_dVb;
    {
      double T1 = Vdsat - d->vds - s->delta;
      double dT1_dVg = dVdsat_dVg;
      double dT1_dVd = dVdsat_dVd - 1.0;
      double dT1_dVb = dVdsat_dVb;
      trace4("", T1, dT1_dVg, dT1_dVd, dT1_dVb);
      
      double T2 = sqrt(T1 * T1 + 4.0 * s->delta * Vdsat);
      double T0 = T1 / T2;
      double T3 = 2.0 * s->delta / T2;
      trace3("", T2, T0, T3);
      double dT2_dVg = T0 * dT1_dVg + T3 * dVdsat_dVg;
      double dT2_dVd = T0 * dT1_dVd + T3 * dVdsat_dVd;
      double dT2_dVb = T0 * dT1_dVb + T3 * dVdsat_dVb;
      trace3("", dT2_dVg, dT2_dVd, dT2_dVb);
      
      Vdseff      = Vdsat - 0.5 * (T1 + T2);
      dVdseff_dVg = dVdsat_dVg - 0.5 * (dT1_dVg + dT2_dVg); 
      dVdseff_dVd = dVdsat_dVd - 0.5 * (dT1_dVd + dT2_dVd); 
      dVdseff_dVb = dVdsat_dVb - 0.5 * (dT1_dVb + dT2_dVb); 
      trace4("raw", Vdseff, dVdseff_dVg, dVdseff_dVd, dVdseff_dVb);

      fixzero(&Vdseff,      Vdsat);
      fixzero(&dVdseff_dVg, dVdsat_dVg);
      fixzero(&dVdseff_dVd, dVdsat_dVd);
      fixzero(&dVdseff_dVb, dVdsat_dVb);
      /* Added to eliminate non-zero Vdseff at Vds=0.0 */
      if (d->vds == 0.0) {
	assert(Vdseff == 0.0);
	assert(dVdseff_dVg == 0.0);
	assert(dVdseff_dVb == 0.0);
      }
      if (Vdseff > d->vds) { untested();
	// From Spice, to fix numeric problems.
	trace2("numeric problems", Vdseff, d->vds);
	Vdseff = d->vds;
      }
      trace4("fixed", Vdseff, dVdseff_dVg, dVdseff_dVd, dVdseff_dVb);

      diffVds = d->vds - Vdseff;
      trace2("", Vdseff, diffVds);
      ////////// d->Vdseff = Vdseff;
    }
    trace2("", Vdseff, diffVds);
    trace3("", dVdseff_dVg, dVdseff_dVd, dVdseff_dVb);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    /* Calculate Ids */
    double Idsa, dIdsa_dVg, dIdsa_dVd, dIdsa_dVb;
    {
      double Va, dVa_dVg, dVa_dVd, dVa_dVb;
      {
	/* Calculate VACLM */
	double VACLM, dVACLM_dVg, dVACLM_dVb, dVACLM_dVd;
	if ((s->pclm > 0.0) && (diffVds > 1.0e-10)) {
	  double T0 = 1.0 / (s->pclm * Abulk * s->litl);
	  double dT0_dVb = -T0 / Abulk * dAbulk_dVb;
	  double dT0_dVg = -T0 / Abulk * dAbulk_dVg; 
	  double T2 = d->vgst / EsatL;
	  double T1 = s->leff * (Abulk + T2); 
	  double dT1_dVg = s->leff * ((1.0-T2*dEsatL_dVg)/EsatL + dAbulk_dVg);
	  double dT1_dVb = s->leff * (dAbulk_dVb - T2 * dEsatL_dVb / EsatL);
	  double dT1_dVd = -T2 * dEsatL_dVd / Esat;
	  double T9 = T0 * T1;
	  VACLM = T9 * diffVds;
	  dVACLM_dVg = T0 * dT1_dVg * diffVds - T9 * dVdseff_dVg
	    + T1 * diffVds * dT0_dVg;
	  dVACLM_dVb = (dT0_dVb*T1 + T0*dT1_dVb) * diffVds - T9 * dVdseff_dVb;
	  dVACLM_dVd = T0 * dT1_dVd * diffVds + T9 * (1.0 - dVdseff_dVd);
	}else{
	  VACLM = MAX_EXP;
	  dVACLM_dVd = dVACLM_dVg = dVACLM_dVb = 0.0;
	}
	trace4("", VACLM, dVACLM_dVg, dVACLM_dVb, dVACLM_dVd);

	/* Calculate VADIBL */
	double VADIBL, dVADIBL_dVg, dVADIBL_dVb, dVADIBL_dVd;
	if (t->thetaRout > 0.0) {
	  double T8 = Abulk * Vdsat;
	  double T0 = Vgst2Vtm * T8;
	  double dT0_dVg = Vgst2Vtm * Abulk * dVdsat_dVg + T8
	    + Vgst2Vtm * Vdsat * dAbulk_dVg;
	  double dT0_dVb = Vgst2Vtm * (dAbulk_dVb*Vdsat + Abulk*dVdsat_dVb);
	  double dT0_dVd = Vgst2Vtm * Abulk * dVdsat_dVd;
	  double T1 = Vgst2Vtm + T8;
	  double dT1_dVg = 1.0 + Abulk * dVdsat_dVg + Vdsat * dAbulk_dVg;
	  double dT1_dVb = Abulk * dVdsat_dVb + dAbulk_dVb * Vdsat;
	  double dT1_dVd = Abulk * dVdsat_dVd;
	  double T9 = T1 * T1;
	  double T2 = t->thetaRout;
	  VADIBL = (Vgst2Vtm - T0 / T1) / T2;
	  dVADIBL_dVg = (1.0 - dT0_dVg / T1 + T0 * dT1_dVg / T9) / T2;
	  dVADIBL_dVb = (-dT0_dVb / T1 + T0 * dT1_dVb / T9) / T2;
	  dVADIBL_dVd = (-dT0_dVd / T1 + T0 * dT1_dVd / T9) / T2;
	  
	  double T7 = s->pdiblb * Vbseff;
	  if (T7 >= -0.9) {
	    double T3 = 1.0 / (1.0 + T7);
	    VADIBL *= T3;
	    dVADIBL_dVg *= T3;
	    dVADIBL_dVb = (dVADIBL_dVb - VADIBL * s->pdiblb) * T3;
	    dVADIBL_dVd *= T3;
	  }else{
	    /* Added to avoid the discontinuity problem caused by pdiblcb */
	    double T4 = 1.0 / (0.8 + T7);
	    double T3 = (17.0 + 20.0 * T7) * T4;
	    dVADIBL_dVg *= T3;
	    dVADIBL_dVb = dVADIBL_dVb * T3 - VADIBL * s->pdiblb * T4 * T4;
	    dVADIBL_dVd *= T3;
	    VADIBL *= T3;
	  }
	}else{
	  VADIBL = MAX_EXP;
	  dVADIBL_dVd = dVADIBL_dVg = dVADIBL_dVb = 0.0;
	}
	trace4("", VADIBL, dVADIBL_dVg, dVADIBL_dVb, dVADIBL_dVd);

	/* Calculate VA */
	double T8 = s->pvag / EsatL;
	double T9 = T8 * d->vgst;
	double T0, dT0_dVg, dT0_dVb, dT0_dVd;
	if (T9 > -0.9) {
	  T0 = 1.0 + T9;
	  dT0_dVg = T8 * (1.0 - d->vgst * dEsatL_dVg / EsatL);
	  dT0_dVb = -T9 * dEsatL_dVb / EsatL;
	  dT0_dVd = -T9 * dEsatL_dVd / EsatL;
	}else{
	  /* Added to avoid the discontinuity problems caused by pvag */
	  double T1 = 1.0 / (17.0 + 20.0 * T9);
	  T0 = (0.8 + T9) * T1;
	  T1 *= T1;
	  dT0_dVg = T8 * (1.0 - d->vgst * dEsatL_dVg / EsatL) * T1;
	  T9 *= T1 / EsatL;
	  dT0_dVb = -T9 * dEsatL_dVb;
	  dT0_dVd = -T9 * dEsatL_dVd;
	}
	double tmp1 = VACLM * VACLM;
	double tmp2 = VADIBL * VADIBL;
	double tmp3 = VACLM + VADIBL;
	
	double T1 = VACLM * VADIBL / tmp3;
	tmp3 *= tmp3;
	double dT1_dVg = (tmp1 * dVADIBL_dVg + tmp2 * dVACLM_dVg) / tmp3;
	double dT1_dVd = (tmp1 * dVADIBL_dVd + tmp2 * dVACLM_dVd) / tmp3;
	double dT1_dVb = (tmp1 * dVADIBL_dVb + tmp2 * dVACLM_dVb) / tmp3;
	
	Va = Vasat + T0 * T1;
	dVa_dVg = dVasat_dVg + T1 * dT0_dVg + T0 * dT1_dVg;
	dVa_dVd = dVasat_dVd + T1 * dT0_dVd + T0 * dT1_dVd;
	dVa_dVb = dVasat_dVb + T1 * dT0_dVb + T0 * dT1_dVb;
      }
      trace4("", Va, dVa_dVg, dVa_dVd, dVa_dVb);

      double Idl, dIdl_dVg, dIdl_dVd, dIdl_dVb;
      {
	double gche, dgche_dVg, dgche_dVd, dgche_dVb;
	{
	  double beta, dbeta_dVg, dbeta_dVd, dbeta_dVb;
	  {
	    double CoxWovL = m->cox * Weff / s->leff;
	    beta = ueff * CoxWovL;
	    dbeta_dVg = CoxWovL * dueff_dVg + beta * dWeff_dVg / Weff;
	    dbeta_dVd = CoxWovL * dueff_dVd;
	    dbeta_dVb = CoxWovL * dueff_dVb + beta * dWeff_dVb / Weff;
	  }
	  trace4("", beta, dbeta_dVg, dbeta_dVd, dbeta_dVb);

	  double fgche1, dfgche1_dVg, dfgche1_dVd, dfgche1_dVb;
	  {
	    double T0 = 1.0 - 0.5 * Abulk * Vdseff / Vgst2Vtm;
	    double dT0_dVg = -0.5 * (Abulk * dVdseff_dVg 
		- Abulk * Vdseff / Vgst2Vtm + Vdseff * dAbulk_dVg) / Vgst2Vtm;
	    double dT0_dVd = -0.5 * Abulk * dVdseff_dVd / Vgst2Vtm;
	    double dT0_dVb = -0.5 * (Abulk*dVdseff_dVb + dAbulk_dVb*Vdseff) 
	      / Vgst2Vtm;
	    fgche1 = d->vgst * T0;
	    dfgche1_dVg = d->vgst * dT0_dVg + T0; 
	    dfgche1_dVd = d->vgst * dT0_dVd; 
	    dfgche1_dVb = d->vgst * dT0_dVb; 
	  }
	  trace4("", fgche1, dfgche1_dVg, dfgche1_dVd, dfgche1_dVb);

	  double fgche2, dfgche2_dVg, dfgche2_dVd, dfgche2_dVb;
	  {
	    double T9 = Vdseff / EsatL;
	    fgche2 = 1.0 + T9;
	    dfgche2_dVg = (dVdseff_dVg - T9 * dEsatL_dVg) / EsatL;
	    dfgche2_dVd = (dVdseff_dVd - T9 * dEsatL_dVd) / EsatL;
	    dfgche2_dVb = (dVdseff_dVb - T9 * dEsatL_dVb) / EsatL;
	  }
	  trace4("", fgche2, dfgche2_dVg, dfgche2_dVd, dfgche2_dVb);

	  gche = beta * fgche1 / fgche2;
	  dgche_dVg = (beta * dfgche1_dVg + fgche1 * dbeta_dVg
		       - gche * dfgche2_dVg) / fgche2;
	  dgche_dVd = (beta * dfgche1_dVd + fgche1 * dbeta_dVd
		       - gche * dfgche2_dVd) / fgche2;
	  dgche_dVb = (beta * dfgche1_dVb + fgche1 * dbeta_dVb
		       - gche * dfgche2_dVb) / fgche2;
	}
	trace4("", gche, dgche_dVg, dgche_dVd, dgche_dVb);

	double T0 = 1.0 + gche * Rds;
	double T9 = Vdseff / T0;
	Idl = gche * T9;
	dIdl_dVg = (gche * dVdseff_dVg + T9 * dgche_dVg) / T0
	  - Idl * gche / T0 * dRds_dVg; 
	dIdl_dVd = (gche * dVdseff_dVd + T9 * dgche_dVd) / T0; 
	dIdl_dVb = (gche*dVdseff_dVb + T9*dgche_dVb - Idl*dRds_dVb*gche) / T0; 
      }
      trace4("", Idl, dIdl_dVg, dIdl_dVd, dIdl_dVb);

      double T9 = diffVds / Va;
      double T0 = 1.0 + T9;
      Idsa = Idl * T0;
      dIdsa_dVg = T0 * dIdl_dVg - Idl * (dVdseff_dVg + T9 * dVa_dVg) / Va;
      dIdsa_dVd = T0 * dIdl_dVd + Idl * (1.0 - dVdseff_dVd - T9*dVa_dVd) / Va;
      dIdsa_dVb = T0 * dIdl_dVb - Idl * (dVdseff_dVb + T9 * dVa_dVb) / Va;
    }
    trace4("", Idsa, dIdsa_dVg, dIdsa_dVd, dIdsa_dVb);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // d->ids, d->gds, d->gmf, d->gmbf
    {
      double VASCBE, dVASCBE_dVg, dVASCBE_dVd, dVASCBE_dVb;
      if (s->pscbe2 > 0.0) {
	if (diffVds > s->pscbe1 * s->litl / EXP_THRESHOLD) {
	  double T0 =  s->pscbe1 * s->litl / diffVds;
	  VASCBE = s->leff * exp(T0) / s->pscbe2;
	  double T1 = T0 * VASCBE / diffVds;
	  dVASCBE_dVg = T1 * dVdseff_dVg;
	  dVASCBE_dVd = -T1 * (1.0 - dVdseff_dVd);
	  dVASCBE_dVb = T1 * dVdseff_dVb;
	}else{
	  VASCBE = MAX_EXP * s->leff/s->pscbe2;
	  dVASCBE_dVg = dVASCBE_dVd = dVASCBE_dVb = 0.0;
	}
      }else{
	VASCBE = MAX_EXP;
	dVASCBE_dVg = dVASCBE_dVd = dVASCBE_dVb = 0.0;
      }
      double T9 = diffVds / VASCBE;
      double T0 = 1.0 + T9;
      double Ids = Idsa * T0;
      double Gm = T0*dIdsa_dVg - Idsa*(dVdseff_dVg + T9*dVASCBE_dVg) / VASCBE;
      double Gds = T0 * dIdsa_dVd 
	+ Idsa * (1.0 - dVdseff_dVd - T9 * dVASCBE_dVd) / VASCBE;
      double Gmb = T0 * dIdsa_dVb
	- Idsa * (dVdseff_dVb + T9 * dVASCBE_dVb) / VASCBE;
      trace3("", T0, dIdsa_dVb, (T0 * dIdsa_dVb));
      trace4("", dVdseff_dVb, T9, dVASCBE_dVb, (dVdseff_dVb + T9*dVASCBE_dVb));
      trace3("", Idsa, VASCBE, (Idsa*(dVdseff_dVb+T9*dVASCBE_dVb)/VASCBE));

      Gds += Gm * dVgsteff_dVd;
      Gmb += Gm * dVgsteff_dVb;
      Gm *= dVgsteff_dVg;
      Gmb *= dVbseff_dVb;
      trace4("", Ids, Gm, Gds, Gmb);
      trace0("=========================");

      d->gds = Gds;
      if (d->reversed) {
	d->ids  = -Ids;
	d->gmr  = Gm;
	d->gmbr = Gmb;
	d->gmf = d->gmbf = 0;
      }else{
	d->ids  = Ids;
	d->gmf  = Gm;
	d->gmbf = Gmb;
	d->gmr = d->gmbr = 0.;
      }
    }
    trace4("", d->ids, d->gds, d->gmf, d->gmbf);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // d->isub, d->gbbs, d->gbgs, d->gbds
    {
      /* calculate substrate current Isub */
      double Isub, Gbd, Gbb, Gbg;
      double tmp = s->alpha0 + s->alpha1 * s->leff;

      if ((tmp <= 0.0) || (s->beta0 <= 0.0)) {
	Isub = Gbd = Gbb = Gbg = 0.0;
	trace7("no-isub", Isub, Gbd, Gbb, Gbg, tmp, s->beta0, s->alpha0);
      }else{
	double T2 = tmp / s->leff;
	double T1, dT1_dVg, dT1_dVd, dT1_dVb;
	if (diffVds > s->beta0 / EXP_THRESHOLD) {
	  double T0 = -s->beta0 / diffVds;
	  T1 = T2 * diffVds * exp(T0);
	  double T3 = T1 / diffVds * (T0 - 1.0);
	  trace3("", T0, T2, T3);
	  dT1_dVg = T3 * dVdseff_dVg;
	  dT1_dVd = T3 * (dVdseff_dVd - 1.0);
	  dT1_dVb = T3 * dVdseff_dVb;
	  trace4("vds > ?", T1, dT1_dVg, dT1_dVd, dT1_dVb);
	}else{
	  double T3 = T2 * MIN_EXP;
	  trace2("", T2, T3);
	  T1 = T3 * diffVds;
	  dT1_dVg = -T3 * dVdseff_dVg;
	  dT1_dVd = T3 * (1.0 - dVdseff_dVd);
	  dT1_dVb = -T3 * dVdseff_dVb;
	  trace4("vds < ?", T1, dT1_dVg, dT1_dVd, dT1_dVb);
	}
	Isub = T1 * Idsa;
//        std::cerr << "DBG " << T1 << Idsa <<  "\n";
	Gbg = T1 * dIdsa_dVg + Idsa * dT1_dVg;
	Gbd = T1 * dIdsa_dVd + Idsa * dT1_dVd;
	Gbb = T1 * dIdsa_dVb + Idsa * dT1_dVb;
	trace4("raw", Isub, Gbd, Gbb, Gbg);
	
	Gbd += Gbg * dVgsteff_dVd;
	Gbb += Gbg * dVgsteff_dVb;
	Gbg *= dVgsteff_dVg;
	Gbb *= dVbseff_dVb; /* bug fixing */
      }
      trace4("", Isub, Gbd, Gbb, Gbg);
      if (!(d->reversed)) {
	d->idb   = Isub;
//        std::cerr << "ALFADBG " << s->alpha0  << " " << s->alpha1 << " " << s->leff << " " << Isub  << "\n";
	d->gdbds = Gbd;
	d->gdbgs = Gbg;
	d->gdbbs = Gbb;
	d->isb = d->gsbsd = d->gsbgd = d->gsbbd = 0.;
      }else{
	d->idb = d->gdbds = d->gdbgs = d->gdbbs = 0.;
	d->isb   = Isub;
	d->gsbsd = Gbd;
	d->gsbgd = Gbg;
	d->gsbbd = Gbb;
      }
      //double d__csub = Isub - (Gbb * Vbseff + Gbd * d->vds + Gbg * d->vgs);
    }
    //trace4("", d->isub, d->gbbs, d->gbgs, d->gbds);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    /* Calculate Qinv for Noise analysis */
    {
      // from 3.1
      //double T1 = d->vgst * (1.0 - 0.5 * Abulk * Vdseff / Vgst2Vtm);
      //double d__qinv = -m->cox * Weff * s->leff * T1;

      // from 3.3
      // /* BSIM3 thermal noise Qinv calculated from all capMod 
      // 0, 1, 2 & 3 stored in here->BSIM3qinv 1/1998 */
    }
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // ends line 2020 (finished)
    // d->qgate, d->qdrn, d->qbulk
    // d->cggb, d->cgsb, d->cgdb
    // d->cdgb, d->cdsb, d->cddb
    // d->cbgb, d->cbsb, d->cbdb
    assert(d->qbulk == d->qbulk);
    assert(d->qdrn == d->qdrn);
    assert(d->qgate == d->qgate);
    {
      const bool ChargeComputationNeeded = true;
      trace2("", m->xpart, m->capMod);
      if ((m->xpart < 0) || (!ChargeComputationNeeded)) {
	d->qgate = d->qdrn = d->qbulk = 0.0;
	d->cggb = d->cgsb = d->cgdb = 0.0;
	d->cdgb = d->cdsb = d->cddb = 0.0;
	d->cbgb = d->cbsb = d->cbdb = 0.0;
        ////////// d->cqdb = d->cqsb = d->cqgb = d->cqbb = 0.0;
        ////////// d->gtau = 0.0;
	trace0("xpart < 0 || no charge computation");
	untested();
	assert(d->qbulk == d->qbulk);
	assert(d->qdrn == d->qdrn);
	assert(d->qgate == d->qgate);
	untested();
      }else if (m->capMod == 0) {
	untested();
	// block ends 1876 this 1599
	trace0("begin capMod == 0 (mos8)");
	if (Vbseff < 0.0) {  // redefinition
	  Vbseff = d->vbs;
	  dVbseff_dVb = 1.0;
	}else{
	  Vbseff = t->phi - Phis;
	  dVbseff_dVb = -dPhis_dVb;
	}
	trace1("old value replaced", dVth_dVb);
	double Vfb = s->vfbcv; // possible improper redefinition later
        double Vth = Vfb + t->phi + t->k1ox * sqrtPhis; 
        assert(Vth>0);

//        std::cout << "*% \n";
        Vth += a->delta_vth;

        // mos1
        // d->von += a->delta_vth;   

	dVth_dVb = t->k1ox * dsqrtPhis_dVb; // redefinition
	double Vgst = Vgs_eff - Vth;
	//double dVgst_dVb = -dVth_dVb;
	//double dVgst_dVg = dVgs_eff_dVg; 
	double CoxWL = m->cox * s->weffCV * s->leffCV;
	double Arg1 = Vgs_eff - Vbseff - Vfb; // Vbseff2!
	trace3("", Vfb, Vth, dVth_dVb);
	trace3("", Vgst, CoxWL, Arg1);

	// ends 1618 this 1328
	if (Arg1 <= 0.0) {
	  trace0("Arg1 <= 0.0");
	  
	  d->qgate = CoxWL * Arg1;
	  d->cggb = CoxWL * dVgs_eff_dVg;
	  d->cgdb = 0.0;
	  d->cgsb = CoxWL * (dVbseff_dVb - dVgs_eff_dVg);
	  
	  d->qbulk = -d->qgate;
	  d->cbgb = -CoxWL * dVgs_eff_dVg;
	  d->cbdb = 0.0;
	  d->cbsb = -d->cgsb;
	  
	  d->qdrn = 0.0;
	  d->cdgb = 0.0;
	  d->cddb = 0.0;
	  d->cdsb = 0.0;
	  
	  ////////// d->qinv = 0.0;
	}else if (Vgst <= 0.0) {
	  trace0("Vgst <= 0.0");
	  double T1 = 0.5 * t->k1ox;
	  double T2 = sqrt(T1 * T1 + Arg1);
	  double T0 = CoxWL * T1 / T2;

	  d->qgate = CoxWL * t->k1 * (T2 - T1);
	  d->cggb = T0 * dVgs_eff_dVg;
	  d->cgdb = 0.0;
	  d->cgsb = T0 * (dVbseff_dVb - dVgs_eff_dVg);
	  
	  d->qbulk = -d->qgate;
	  d->cbgb = -d->cggb;
	  d->cbdb = 0.0;
	  d->cbsb = -d->cgsb;
   
	  d->qdrn = 0.0;
	  d->cdgb = 0.0;
	  d->cddb = 0.0;
	  d->cdsb = 0.0;
	}else{
	  trace0("!(Arg1 <= 0.0 || Vgst <= 0.0)");
	  double One_Third_CoxWL = CoxWL / 3.0;
	  double Two_Third_CoxWL = 2.0 * One_Third_CoxWL;
	  // redefine Vdsat, dVdsat_dVg, dVdsat_dVb
	  {
	    double AbulkCV = Abulk0 * s->abulkCVfactor;
	    double dAbulkCV_dVb = s->abulkCVfactor * dAbulk0_dVb;
	    Vdsat = Vgst / AbulkCV;
	    dVdsat_dVg = dVgs_eff_dVg / AbulkCV;
            assert( m->capMod == 0 );
	    dVdsat_dVb = - (Vdsat * dAbulkCV_dVb + dVth_dVb)/ AbulkCV; 
	  }
	  if (m->xpart > 0.5) {
	    /* 0/100 Charge partition model */
	    if (d->vds >= Vdsat) {
	      /* saturation region */
	      double T1 = Vdsat / 3.0;
	      double T2 = -One_Third_CoxWL * dVdsat_dVb;
	      d->qgate = CoxWL * (Vgs_eff - Vfb - t->phi - T1);
	      d->cggb = One_Third_CoxWL * (3.0 - dVdsat_dVg) * dVgs_eff_dVg;
	      d->cgsb = -(d->cggb + T2);
	      d->cgdb = 0.0;
	      
	      double T2a = -Two_Third_CoxWL * Vgst;
	      double T3 = -(T2 + Two_Third_CoxWL * dVth_dVb);
	      d->qbulk = -(d->qgate + T2a);
	      d->cbgb = -(d->cggb - Two_Third_CoxWL * dVgs_eff_dVg);
	      d->cbsb = -(d->cbgb + T3);
	      d->cbdb = 0.0;

	      d->qdrn = 0.0;
	      d->cdgb = 0.0;
	      d->cddb = 0.0;
	      d->cdsb = 0.0;
	      ////////// d->qinv =  -(d->qgate + d->qbulk);
	    }else{
	      /* linear region */
	      double Alphaz = Vgst / Vdsat;
	      double T1 = 2.0 * Vdsat - d->vds;
	      double T2 = d->vds / (3.0 * T1);
	      double T3 = T2 * d->vds;
	      double T9 = 0.25 * CoxWL;
	      double T4 = T9 * Alphaz;
	      double T7 = 2.0 * d->vds - T1 - 3.0 * T3;
	      double T8 = T3 - T1 - 2.0 * d->vds;
	      d->qgate = CoxWL * (Vgs_eff - Vfb - t->phi - 0.5 * (d->vds-T3));
	      double T10 = T4 * T8;
	      d->qdrn = T4 * T7;
	      d->qbulk = -(d->qgate + d->qdrn + T10);
	      ////////// d->qinv =  -(d->qgate + d->qbulk);
	      
	      double T5 = T3 / T1;
	      d->cggb = CoxWL * (1.0 - T5 * dVdsat_dVg) * dVgs_eff_dVg;
	      double T11 = -CoxWL * T5 * dVdsat_dVb;
	      d->cgdb = CoxWL * (T2 - 0.5 + 0.5 * T5);
	      d->cgsb = -(d->cggb + T11 + d->cgdb);

	      double T6 = 1.0 / Vdsat;
	      double dAlphaz_dVg = T6 * (1.0 - Alphaz * dVdsat_dVg);
	      double dAlphaz_dVb = -T6 * (dVth_dVb + Alphaz * dVdsat_dVb);
	      T7 = T9 * T7;
	      T8 = T9 * T8;
	      T9 = 2.0 * T4 * (1.0 - 3.0 * T5);
	      d->cdgb = (T7 * dAlphaz_dVg - T9 * dVdsat_dVg) * dVgs_eff_dVg;
	      double T12 = T7 * dAlphaz_dVb - T9 * dVdsat_dVb;
	      d->cddb = T4 * (3.0 - 6.0 * T2 - 3.0 * T5);
	      d->cdsb = -(d->cdgb + T12 + d->cddb);

	      T9 = 2.0 * T4 * (1.0 + T5);
	      T10 = (T8 * dAlphaz_dVg - T9 * dVdsat_dVg) * dVgs_eff_dVg;
	      T11 = T8 * dAlphaz_dVb - T9 * dVdsat_dVb;
	      T12 = T4 * (2.0 * T2 + T5 - 1.0); 
	      double T0 = -(T10 + T11 + T12);
	      d->cbgb = -(d->cggb + d->cdgb + T10);
	      d->cbdb = -(d->cgdb + d->cddb + T12);
	      d->cbsb = -(d->cgsb + d->cdsb + T0);
	    }
	  }else if (m->xpart < 0.5) {
	    /* 40/60 Charge partition model */
	    if (d->vds >= Vdsat) {
	      /* saturation region */
	      double T1 = Vdsat / 3.0;
	      d->qgate = CoxWL * (Vgs_eff - Vfb - t->phi - T1);
	      double T2 = -Two_Third_CoxWL * Vgst;
	      d->qbulk = -(d->qgate + T2);
	      d->qdrn = 0.4 * T2;
	      ////////// d->qinv =  -(d->qgate + d->qbulk);

	      d->cggb = One_Third_CoxWL * (3.0 - dVdsat_dVg) * dVgs_eff_dVg;
	      T2 = -One_Third_CoxWL * dVdsat_dVb;
	      d->cgsb = -(d->cggb + T2);
	      d->cgdb = 0.0;
       
	      double T3 = 0.4 * Two_Third_CoxWL;
	      d->cdgb = -T3 * dVgs_eff_dVg;
	      d->cddb = 0.0;
	      double T4 = T3 * dVth_dVb;
	      d->cdsb = -(T4 + d->cdgb);
	      
	      d->cbgb = -(d->cggb - Two_Third_CoxWL * dVgs_eff_dVg);
	      T3 = -(T2 + Two_Third_CoxWL * dVth_dVb);
	      d->cbsb = -(d->cbgb + T3);
	      d->cbdb = 0.0;
	    }else{
	      /* linear region  */
	      double T1 = 2.0 * Vdsat - d->vds;
	      double T2 = d->vds / (3.0 * T1);
	      double T3 = T2 * d->vds;
	      d->qgate = CoxWL * (Vgs_eff - Vfb - t->phi - 0.5 * (d->vds - T3));
	      double T5 = T3 / T1;
	      d->cggb = CoxWL * (1.0 - T5 * dVdsat_dVg) * dVgs_eff_dVg;
	      double tmp = -CoxWL * T5 * dVdsat_dVb;
	      d->cgdb = CoxWL * (T2 - 0.5 + 0.5 * T5);
	      d->cgsb = -(d->cggb + d->cgdb + tmp);

	      double T6 = 1.0 / Vdsat;
	      double Alphaz      =  T6 * Vgst;
	      double dAlphaz_dVg =  T6 * (1.0 - Alphaz * dVdsat_dVg);
	      double dAlphaz_dVb = -T6 * (dVth_dVb + Alphaz * dVdsat_dVb);
	      T6 = 8.0 * Vdsat * Vdsat - 6.0 * Vdsat * d->vds 
		+ 1.2 * d->vds * d->vds;
	      double T8 = T2 / T1;
	      double T7 = d->vds - T1 - T8 * T6;
	      double T9 = 0.25 * CoxWL;
	      double T4 = T9 * Alphaz;
	      d->qdrn = T4 * T7;
	      T7 *= T9;
	      tmp = T8 / T1;
	      double tmp1 = T4 * (2.0 - 4.0 * tmp * T6
			   + T8 * (16.0 * Vdsat - 6.0 * d->vds));
	      d->cdgb = (T7 * dAlphaz_dVg - tmp1 * dVdsat_dVg) * dVgs_eff_dVg;
	      double T10 = T7 * dAlphaz_dVb - tmp1 * dVdsat_dVb;
	      d->cddb = T4 * (2.0 - (1.0 / (3.0 * T1 * T1) + 2.0 * tmp) * T6 
			      + T8 * (6.0 * Vdsat - 2.4 * d->vds));
	      d->cdsb = -(d->cdgb + T10 + d->cddb);

	      T7 = 2.0 * (T1 + T3);
	      d->qbulk = -(d->qgate - T4 * T7);
	      T7 *= T9;
	      double T0 = 4.0 * T4 * (1.0 - T5);
	      double T12 = (-T7 * dAlphaz_dVg - d->cdgb - T0 * dVdsat_dVg)
		* dVgs_eff_dVg;
	      double T11 = -T7 * dAlphaz_dVb - T10 - T0 * dVdsat_dVb;
	      T10 = -4.0 * T4 * (T2 - 0.5 + 0.5 * T5) - d->cddb;
	      tmp = -(T10 + T11 + T12);
	      d->cbgb = -(d->cggb + d->cdgb + T12);
	      d->cbdb = -(d->cgdb + d->cddb + T10); /* bug fix 3.3 */
	      d->cbsb = -(d->cgsb + d->cdsb + tmp);
	      trace3("0,40/60,lin", T10, T11, T12);
	      trace3("0,40/60,lin", d->cbgb, d->cbdb, d->cbsb); 
	      ////////// d->qinv =  -(d->qgate + d->qbulk);
	    }
	  }else{
	    /* 50/50 partitioning */
	    if (d->vds >= Vdsat) {
	      /* saturation region */
	      double T1 = Vdsat / 3.0;
	      d->qgate = CoxWL * (Vgs_eff - Vfb - t->phi - T1);
	      double T2 = -Two_Third_CoxWL * Vgst;
	      d->qbulk = -(d->qgate + T2);
	      ////////// d->qinv =  -(d->qgate + d->qbulk);
	      d->qdrn = 0.5 * T2;
	      
	      T2 = -One_Third_CoxWL * dVdsat_dVb;
	      d->cggb = One_Third_CoxWL * (3.0 - dVdsat_dVg) * dVgs_eff_dVg;
	      d->cgsb = -(d->cggb + T2);
	      d->cgdb = 0.0;
	      
	      double T4 = One_Third_CoxWL * dVth_dVb;
	      d->cdgb = -One_Third_CoxWL * dVgs_eff_dVg;
	      d->cddb = 0.0;
	      d->cdsb = -(T4 + d->cdgb);
	      
	      double T3 = -(T2 + Two_Third_CoxWL * dVth_dVb);
	      d->cbgb = -(d->cggb - Two_Third_CoxWL * dVgs_eff_dVg);
	      d->cbsb = -(d->cbgb + T3);
	      d->cbdb = 0.0;
	    }else{
	      /* linear region */
	      double T1 = 2.0 * Vdsat - d->vds;
	      double T2 = d->vds / (3.0 * T1);
	      double T3 = T2 * d->vds;
	      double T5 = T3 / T1;
	      double tmp = -CoxWL * T5 * dVdsat_dVb;
	      d->qgate = CoxWL * (Vgs_eff - Vfb - t->phi - 0.5 * (d->vds-T3));
	      d->cggb = CoxWL * (1.0 - T5 * dVdsat_dVg) * dVgs_eff_dVg;
	      d->cgdb = CoxWL * (T2 - 0.5 + 0.5 * T5);
	      d->cgsb = -(d->cggb + d->cgdb + tmp);
	      
	      double T6 = 1.0 / Vdsat;
	      double Alphaz =       T6 * Vgst;
	      double dAlphaz_dVg =  T6 * (1.0 - Alphaz * dVdsat_dVg);
	      double dAlphaz_dVb = -T6 * (dVth_dVb + Alphaz * dVdsat_dVb);
	      
	      double T9 = 0.25 * CoxWL;
	      double T4 = T9 * Alphaz;
	      double T7 = T1 + T3;
	      d->qdrn = -T4 * T7;
	      d->qbulk = - (d->qgate + d->qdrn + d->qdrn);
	      ////////// d->qinv =  -(d->qgate + d->qbulk);

	      T7 *= T9;
	      double T0 = T4 * (2.0 * T5 - 2.0);	      
	      double T12 = T0 * dVdsat_dVb - T7 * dAlphaz_dVb;
	      d->cdgb = (T0 * dVdsat_dVg - T7 * dAlphaz_dVg) * dVgs_eff_dVg;
	      d->cddb = T4 * (1.0 - 2.0 * T2 - T5);
	      d->cdsb = -(d->cdgb + T12 + d->cddb);
	      
	      d->cbgb = -(d->cggb + 2.0 * d->cdgb);
	      d->cbdb = -(d->cgdb + 2.0 * d->cddb);
	      d->cbsb = -(d->cgsb + 2.0 * d->cdsb);
	    }
	  }
	} // begins 1328 this 1618
	trace0("end capMod == 0");
	// end of else if (m->capMod == 0) line 1598 this 1875
	assert(d->qbulk == d->qbulk);
	assert(d->qdrn == d->qdrn);
	assert(d->qgate == d->qgate);
      }else{
	trace0("begin capMod != 0 (mos8)");	
	assert(m->capMod != 0);
	double qsrc;
	double VbseffCV, dVbseffCV_dVb;
	if (Vbseff < 0.0) {
	  VbseffCV = Vbseff;  // Vbseff2?!
	  dVbseffCV_dVb = 1.0;
	}else{
	  VbseffCV = t->phi - Phis;
	  dVbseffCV_dVb = -dPhis_dVb;
	}
	trace2("", VbseffCV, dVbseffCV_dVb);

	//////////-----------moved???
	//double Vth = d->von; // possibly wrong value -- scope problem
	//double Vfb = Vth - t->phi - t->k1 * sqrtPhis;
	//double dVfb_dVb = dVth_dVb - t->k1 * dsqrtPhis_dVb;
	//double dVfb_dVd = dVth_dVd;
	//////////-------------end moved?

	double Vgsteff;
	{
	  /* Seperate VgsteffCV with noff and voffcv */
	  double nnoff = n * s->noff;
	  double dnoff_dVd = s->noff * dn_dVd;
	  double dnoff_dVb = s->noff * dn_dVb;

	  double T0 = t->vtm * nnoff;
	  double Vgst = Vgs_eff - d->von;
	  double VgstNVt = (Vgst - s->voffcv) / T0; // was /(2*T0) in d_mos8.model;
	  
	  trace3("", d->vgst, Vgst, VgstNVt);
	  trace2("", n, t->vtm);
	  
	  if (VgstNVt > EXP_THRESHOLD) {
	    trace0("VgstNVt above");
	    Vgsteff = Vgst - s->voffcv;
	    dVgsteff_dVg = dVgs_eff_dVg;
	    dVgsteff_dVd = -dVth_dVd;
	    dVgsteff_dVb = -dVth_dVb;
	  }else if (VgstNVt < -EXP_THRESHOLD) {
	    trace0("VgstNVt below");
	    Vgsteff = T0 * log(1.0 + MIN_EXP);
	    dVgsteff_dVg = 0.0;
	    dVgsteff_dVd = Vgsteff / nnoff;
	    dVgsteff_dVb = dVgsteff_dVd * dnoff_dVb;
	    dVgsteff_dVd *= dnoff_dVd;
	  }else{
	    trace0("VgstNVt in range");
	    double ExpVgst = exp(VgstNVt);
	    trace1("", ExpVgst);
	    Vgsteff = T0 * log(1.0 + ExpVgst);
	    dVgsteff_dVg = ExpVgst / (1.0 + ExpVgst);
	    dVgsteff_dVd = -dVgsteff_dVg
	      * (dVth_dVd + (Vgst - s->voffcv) / nnoff * dnoff_dVd)
	      + Vgsteff / nnoff * dnoff_dVd;
	    dVgsteff_dVb = -dVgsteff_dVg
	      * (dVth_dVb + (Vgst - s->voffcv) / nnoff * dnoff_dVb)
	      + Vgsteff / nnoff * dnoff_dVb;
	    dVgsteff_dVg *= dVgs_eff_dVg;
	  } /* End of VgsteffCV */
	}
	trace4("", Vgsteff, dVgsteff_dVg, dVgsteff_dVd, dVgsteff_dVb);
	  
	/* old code
	if ((VgstNVt > -EXP_THRESHOLD) && (VgstNVt < EXP_THRESHOLD)) {
	  assert(ExpVgst != NOT_VALID);
	  ExpVgst *= ExpVgst;
	  Vgsteff = n * t->vtm * log(1.0 + ExpVgst);
	  dVgsteff_dVg = ExpVgst / (1.0 + ExpVgst);
	  dVgsteff_dVd = -dVgsteff_dVg * (dVth_dVd + (Vgs_eff-Vth)/n * dn_dVd)
	    + Vgsteff/n * dn_dVd;
	  dVgsteff_dVb = -dVgsteff_dVg * (dVth_dVb + (Vgs_eff-Vth)/n * dn_dVb)
	    + Vgsteff/n * dn_dVb;
	  dVgsteff_dVg *= dVgs_eff_dVg;
	}else{
	  Vgsteff = d->vgst;
	}
	*/

	double CoxWL = m->cox * s->weffCV * s->leffCV;
	// redundant??

	if (m->capMod == 1) {
	  untested();
	  double Cgg, Cgd, Cgb;
	  {
	    double Vfb = t->vfbzb;
	    double Arg1 = Vgs_eff - VbseffCV - Vfb - Vgsteff;
	    if (Arg1 <= 0.0) {
	      d->qgate = CoxWL * Arg1;
	      Cgg = CoxWL * (dVgs_eff_dVg - dVgsteff_dVg);
	      //Cgd = -CoxWL * (dVfb_dVd + dVgsteff_dVd);
	      //Cgb = -CoxWL * (dVfb_dVb + dVbseffCV_dVb + dVgsteff_dVb);
	      Cgd = -CoxWL * dVgsteff_dVd;
	      Cgb = -CoxWL * (dVbseffCV_dVb + dVgsteff_dVb);
	    }else{
	      double T0 = 0.5 * t->k1ox;
	      double T1 = sqrt(T0 * T0 + Arg1);
	      double T2 = CoxWL * T0 / T1;
	      d->qgate = CoxWL * t->k1ox * (T1 - T0);
	      Cgg = T2 * (dVgs_eff_dVg - dVgsteff_dVg);
	      //Cgd = -T2 * (dVfb_dVd + dVgsteff_dVd);
	      //Cgb = -T2 * (dVfb_dVb + dVbseffCV_dVb + dVgsteff_dVb);
	      Cgd = -T2 * dVgsteff_dVd;
	      Cgb = -T2 * (dVbseffCV_dVb + dVgsteff_dVb);
	    }
	  }
	  d->qbulk = -d->qgate;
	  double Cbg = -Cgg;
	  double Cbd = -Cgd;
	  double Cbb = -Cgb;
	  
	  double AbulkCV = Abulk0 * s->abulkCVfactor;
	  double dAbulkCV_dVb = s->abulkCVfactor * dAbulk0_dVb;

	  double Csg, Csb, Csd;
	  {
	    double VdsatCV = Vgsteff / AbulkCV;
	    if (VdsatCV < d->vds) {
	      double One_Third_CoxWL = CoxWL / 3.0;
	      double Two_Third_CoxWL = 2.0 * One_Third_CoxWL;
	      double dVdsatCV_dVg = 1.0 / AbulkCV;
	      double dVdsatCV_dVb = -VdsatCV * dAbulkCV_dVb / AbulkCV;
	      {
		double T0 = Vgsteff - VdsatCV / 3.0;
		double dT0_dVg = 1.0 - dVdsatCV_dVg / 3.0;
		double dT0_dVb = -dVdsatCV_dVb / 3.0;
		d->qgate += CoxWL * T0;
		double Cgg1 = CoxWL * dT0_dVg; 
		double Cgb1 = CoxWL * dT0_dVb + Cgg1 * dVgsteff_dVb;
		double Cgd1 = Cgg1 * dVgsteff_dVd;
		Cgg1 *= dVgsteff_dVg;
		Cgg += Cgg1;
		Cgb += Cgb1;
		Cgd += Cgd1;
	      }
	      {
		double T0 = VdsatCV - Vgsteff;
		double dT0_dVg = dVdsatCV_dVg - 1.0;
		double dT0_dVb = dVdsatCV_dVb;
		d->qbulk += One_Third_CoxWL * T0;
		double Cbg1 = One_Third_CoxWL * dT0_dVg;
		double Cbb1 = One_Third_CoxWL * dT0_dVb + Cbg1 * dVgsteff_dVb;
		double Cbd1 = Cbg1 * dVgsteff_dVd;
		Cbg1 *= dVgsteff_dVg;
		Cbg += Cbg1;
		Cbb += Cbb1;
		Cbd += Cbd1;
	      }
	      double T0;
	      if (m->xpart > 0.5) {
		T0 = -Two_Third_CoxWL;
	      }else if (m->xpart < 0.5) {
		T0 = -0.4 * CoxWL;
	      }else{
		T0 = -One_Third_CoxWL;
	      }
	      qsrc = T0 * Vgsteff;
	      Csg = T0 * dVgsteff_dVg;
	      Csb = T0 * dVgsteff_dVb;
	      Csd = T0 * dVgsteff_dVd;
	      Cgb *= dVbseff_dVb;
	      Cbb *= dVbseff_dVb;
	      Csb *= dVbseff_dVb;
	    }else{
	      double T0 = AbulkCV * d->vds;
	      double T1 = 12.0 * (Vgsteff - 0.5 * T0 + 1.e-20);
	      double Cgg1, Cgb1, Cgd1, Cbg1, Cbb1, Cbd1;
	      {
		double T2 = d->vds / T1;
		double T3 = T0 * T2;
		double dT3_dVg = -12.0 * T2 * T2 * AbulkCV;
		double dT3_dVd = 6.0 * T0 * (4.0*Vgsteff - T0) / T1 / T1 - 0.5;
		double dT3_dVb = 12.0 * T2 * T2 * dAbulkCV_dVb * Vgsteff;
		
		d->qgate += CoxWL * (Vgsteff - 0.5 * d->vds + T3);
		Cgg1 = CoxWL * (1.0 + dT3_dVg);
		Cgb1 = CoxWL * dT3_dVb + Cgg1 * dVgsteff_dVb;
		Cgd1 = CoxWL * dT3_dVd + Cgg1 * dVgsteff_dVd;
		Cgg1 *= dVgsteff_dVg;
		Cgg += Cgg1;
		Cgb += Cgb1;
		Cgd += Cgd1;
		
		d->qbulk += CoxWL * (1.0 - AbulkCV) * (0.5 * d->vds - T3);
		Cbg1 = -CoxWL * ((1.0 - AbulkCV) * dT3_dVg);
		Cbb1 = -CoxWL * ((1.0 - AbulkCV) * dT3_dVb
				 + (0.5 * d->vds - T3) * dAbulkCV_dVb)
		  + Cbg1 * dVgsteff_dVb;
		Cbd1 = -CoxWL * (1.0 - AbulkCV) * dT3_dVd
		  + Cbg1 * dVgsteff_dVd;
		Cbg1 *= dVgsteff_dVg;
		Cbg += Cbg1;
		Cbb += Cbb1;
		Cbd += Cbd1;
	      }
	      if (m->xpart > 0.5) {
		/* 0/100 Charge petition model */
		T1 = T1 + T1;
		qsrc = -CoxWL * (0.5 * Vgsteff + 0.25 * T0 - T0 * T0 / T1);
		Csg = -CoxWL * (0.5 + 24.0 * T0 * d->vds / T1 / T1 * AbulkCV);
		Csb = -CoxWL * (0.25 * d->vds * dAbulkCV_dVb
			  - 12.0 * T0 * d->vds / T1 / T1 * (4.0 * Vgsteff - T0)
				* dAbulkCV_dVb) + Csg * dVgsteff_dVb;
		Csd = -CoxWL * (0.25 * AbulkCV - 12.0 * AbulkCV * T0
				/ T1 / T1 * (4.0 * Vgsteff - T0))
		  + Csg * dVgsteff_dVd;
		Csg *= dVgsteff_dVg;
	      }else if (m->xpart < 0.5) {
		/* 40/60 Charge petition model */
		T1 = T1 / 12.0;
		double T2 = 0.5 * CoxWL / (T1 * T1);
		double T3 = Vgsteff * (2.0 * T0 * T0 / 3.0 
				       + Vgsteff * (Vgsteff - 4.0 * T0 / 3.0))
		  - 2.0 * T0 * T0 * T0 / 15.0;
		qsrc = -T2 * T3;
		double T4 = 4.0 / 3.0 * Vgsteff * (Vgsteff-T0) + 0.4 * T0 * T0;
		Csg = -2.0 * qsrc / T1 
		  - T2 * (Vgsteff * (3.0 * Vgsteff - 8.0 * T0 / 3.0)
			  + 2.0 * T0 * T0 / 3.0);
		Csb = (qsrc / T1 * d->vds + T2 * T4 * d->vds) * dAbulkCV_dVb
		  + Csg * dVgsteff_dVb;
		Csd = (qsrc / T1 + T2 * T4) * AbulkCV + Csg * dVgsteff_dVd;
		Csg *= dVgsteff_dVg;
	      }else{
		/* 50/50 Charge petition model */
		qsrc = -0.5 * (d->qgate + d->qbulk);
		Csg = -0.5 * (Cgg1 + Cbg1);
		Csb = -0.5 * (Cgb1 + Cbb1); 
		Csd = -0.5 * (Cgd1 + Cbd1); 
	      }
	      Cgb *= dVbseff_dVb;
	      Cbb *= dVbseff_dVb;
	      Csb *= dVbseff_dVb;
	    }
	  }
	  d->qdrn = -(d->qgate + d->qbulk + qsrc);
	  d->cggb = Cgg;
	  d->cgsb = -(Cgg + Cgd + Cgb);
	  d->cgdb = Cgd;
	  d->cdgb = -(Cgg + Cbg + Csg);
	  d->cdsb = (Cgg + Cgd + Cgb + Cbg + Cbd + Cbb + Csg + Csd + Csb);
	  d->cddb = -(Cgd + Cbd + Csd);
	  d->cbgb = Cbg;
	  d->cbsb = -(Cbg + Cbd + Cbb);
	  d->cbdb = Cbd;

	  ////////// d->qinv =  -(d->qgate + d->qbulk);
	  trace0("end capMod == 1");
	  untested();
	  assert(d->qbulk == d->qbulk);
	  assert(d->qdrn == d->qdrn);
	  assert(d->qgate == d->qgate);
	  untested();
	}else if (m->capMod == 2) {
	  trace0("begin capMod == 2");
	  double Qac0, dQac0_dVg, dQac0_dVb;
	  double Qsub0, dQsub0_dVg, dQsub0_dVd, dQsub0_dVb;
	  {
	    double Vfb = t->vfbzb;
	    double Vfbeff, dVfbeff_dVg, dVfbeff_dVb;
	    {
	      const double DELTA_3 = 0.02;
	      double V3 = Vfb - Vgs_eff + VbseffCV - DELTA_3;
	      double T0; //, T2;
	      if (Vfb <= 0.0) {
		T0 = sqrt(V3 * V3 - 4.0 * DELTA_3 * Vfb);
		//T2 = -DELTA_3 / T0;
	      }else{
		T0 = sqrt(V3 * V3 + 4.0 * DELTA_3 * Vfb);
		//T2 = DELTA_3 / T0;
	      }
	      double T1 = 0.5 * (1.0 + V3 / T0);
	      Vfbeff = Vfb - 0.5 * (V3 + T0);
	      //dVfbeff_dVd = (1.0 - T1 - T2) * dVfb_dVd;
	      dVfbeff_dVg = T1 * dVgs_eff_dVg;
	      //dVfbeff_dVb = (1.0 - T1 - T2) * dVfb_dVb - T1 * dVbseffCV_dVb;
	      dVfbeff_dVb = -T1 * dVbseffCV_dVb;
	    }
	    trace3("", Vfbeff, dVfbeff_dVg, dVfbeff_dVb);

	    //double Qac0, dQac0_dVg, dQac0_dVd, dQac0_dVb;
	    {
	      Qac0 = CoxWL * (Vfbeff - Vfb);
	      dQac0_dVg = CoxWL * dVfbeff_dVg;
	      //dQac0_dVd = CoxWL * (dVfbeff_dVd - dVfb_dVd);
	      //dQac0_dVb = CoxWL * (dVfbeff_dVb - dVfb_dVb);
	      dQac0_dVb = CoxWL * dVfbeff_dVb;
	    }

	    //double Qsub0, dQsub0_dVg, dQsub0_dVd, dQsub0_dVb;
	    {
	      double T0 = 0.5 * t->k1ox;
	      double T3 = Vgs_eff - Vfbeff - VbseffCV - Vgsteff;
	      double T1, T2;
	      if (t->k1ox == 0.0) {
		T1 = 0.0;
		T2 = 0.0;
	      }else if (T3 < 0.0) {
		T1 = T0 + T3 / t->k1ox;
		T2 = CoxWL;
	      }else{
		T1 = sqrt(T0 * T0 + T3);
		T2 = CoxWL * T0 / T1;
	      }
	      Qsub0 = CoxWL * t->k1ox * (T1 - T0);
	      dQsub0_dVg = T2 * (dVgs_eff_dVg - dVfbeff_dVg - dVgsteff_dVg);
	      //dQsub0_dVd = -T2 * (dVfbeff_dVd + dVgsteff_dVd);
	      dQsub0_dVd = -T2 * dVgsteff_dVd;
	      dQsub0_dVb = -T2 * (dVfbeff_dVb +dVbseffCV_dVb +dVgsteff_dVb);
	    }
	  }
	  trace3("", Qac0, dQac0_dVg, dQac0_dVb);
	  trace4("", Qsub0, dQsub0_dVg, dQsub0_dVd, dQsub0_dVb);

	  double AbulkCV = Abulk0 * s->abulkCVfactor;
	  double dAbulkCV_dVb = s->abulkCVfactor * dAbulk0_dVb;
	  trace2("", AbulkCV, dAbulkCV_dVb);

	  double VdseffCV, dVdseffCV_dVg, dVdseffCV_dVd, dVdseffCV_dVb;
	  {
	    const double DELTA_4 = 0.02;
	    double VdsatCV = Vgsteff / AbulkCV;
	    double V4 = VdsatCV - d->vds - DELTA_4;
	    double T0 = sqrt(V4 * V4 + 4.0 * DELTA_4 * VdsatCV);
	    VdseffCV = VdsatCV - 0.5 * (V4 + T0);
	    double T1 = 0.5 * (1.0 + V4 / T0);
	    double T2 = DELTA_4 / T0;
	    double T3 = (1.0 - T1 - T2) / AbulkCV;
	    dVdseffCV_dVg = T3;
	    dVdseffCV_dVd = T1;
	    dVdseffCV_dVb = -T3 * VdsatCV * dAbulkCV_dVb;
	    /* Added to eliminate non-zero VdseffCV at Vds=0.0 */
	    if (d->vds == 0.0) {
	      //////VdseffCV = 0.0;
	      //////dVdseffCV_dVg = 0.0;
	      //////dVdseffCV_dVb = 0.0;
	    }
	  }
	  trace4("", VdseffCV, dVdseffCV_dVg, dVdseffCV_dVd, dVdseffCV_dVb);

	  double T0 = AbulkCV * VdseffCV;
	  double T1 = 12.0 * (Vgsteff - 0.5 * T0 + 1e-20);
	  trace2("", T0, T1);
	  
	  double Cgg1, Cgd1, Cgb1, Cbg1, Cbd1, Cbb1;
	  // also 1st estimate of d->qgate, d->qbulk
	  {
	    double T2 = VdseffCV / T1;
	    double T3 = T0 * T2;
	    double T4 = (1.0 - 12.0 * T2 * T2 * AbulkCV);
	    double T5 = (6.0 * T0 * (4.0 * Vgsteff - T0) / (T1 * T1) - 0.5);
	    double T6 = 12.0 * T2 * T2 * Vgsteff;

	    ////////// double qinoi = -CoxWL * (Vgsteff - 0.5 * T0 + AbulkCV * T3);
	    ////////// d->qinv = qinoi;
	    d->qgate = CoxWL * (Vgsteff - 0.5 * VdseffCV + T3);
	    Cgg1 = CoxWL * (T4 + T5 * dVdseffCV_dVg);
	    Cgd1 = CoxWL * T5 * dVdseffCV_dVd + Cgg1 * dVgsteff_dVd;
	    Cgb1 = CoxWL * (T5 * dVdseffCV_dVb + T6 * dAbulkCV_dVb) 
	      + Cgg1 * dVgsteff_dVb;
	    Cgg1 *= dVgsteff_dVg;
	    
	    double T7 = 1.0 - AbulkCV;
	    d->qbulk = CoxWL * T7 * (0.5 * VdseffCV - T3);
	    T4 = -T7 * (T4 - 1.0);
	    T5 = -T7 * T5;
	    T6 = -(T7 * T6 + (0.5 * VdseffCV - T3));
	    Cbg1 = CoxWL * (T4 + T5 * dVdseffCV_dVg);
	    Cbd1 = CoxWL * T5 * dVdseffCV_dVd + Cbg1 * dVgsteff_dVd;
	    Cbb1 = CoxWL * (T5 * dVdseffCV_dVb + T6 * dAbulkCV_dVb)
	      + Cbg1 * dVgsteff_dVb;
	    Cbg1 *= dVgsteff_dVg;
	  }
	  trace3("", Cgg1, Cgd1, Cgb1);
	  trace3("", Cbg1, Cbd1, Cbb1);
	  trace2("2-1", d->qgate, d->qbulk);
	  
	  double Csg, Csd, Csb;
	  trace1("", m->xpart);
	  if (m->xpart > 0.5) {
	    trace0("0/100 Charge petition model");
	    T1 = T1 + T1;
	    qsrc = -CoxWL * (0.5 * Vgsteff + 0.25 * T0 - T0 * T0 / T1);
	    double T7 = (4.0 * Vgsteff - T0) / (T1 * T1);
	    double T4 = -(0.5 + 24.0 * T0 * T0 / (T1 * T1));
	    double T5 = -(0.25 * AbulkCV - 12.0 * AbulkCV * T0 * T7);
	    double T6 = -(0.25 * VdseffCV - 12.0 * T0 * VdseffCV * T7);
	    Csg = CoxWL * (T4 + T5 * dVdseffCV_dVg);
	    Csd = CoxWL * T5 * dVdseffCV_dVd + Csg * dVgsteff_dVd;
	    Csb = CoxWL * (T5 * dVdseffCV_dVb + T6 * dAbulkCV_dVb) 
	      + Csg * dVgsteff_dVb;
	    Csg *= dVgsteff_dVg;
	  }else if (m->xpart < 0.5) {
	    trace0("40/60 Charge petition model");
	    T1 = T1 / 12.0;
	    double T2 = 0.5 * CoxWL / (T1 * T1);
	    double T3 = Vgsteff * (2.0 * T0 * T0 / 3.0 + Vgsteff
				   * (Vgsteff - 4.0 * T0 / 3.0))
	      - 2.0 * T0 * T0 * T0 / 15.0;
	    qsrc = -T2 * T3;
	    double T7 = 4.0 / 3.0 * Vgsteff * (Vgsteff - T0) + 0.4 * T0 * T0;
	    double T4 = -2.0 * qsrc / T1 
	      - T2 * (Vgsteff * (3.0 * Vgsteff - 8.0 * T0 / 3.0)
		      + 2.0 * T0 * T0 / 3.0);
	    double T5 = (qsrc / T1 + T2 * T7) * AbulkCV;
	    double T6 = (qsrc / T1 * VdseffCV + T2 * T7 * VdseffCV);
	    Csg = (T4 + T5 * dVdseffCV_dVg);
	    Csd = T5 * dVdseffCV_dVd + Csg * dVgsteff_dVd;
	    Csb = (T5 * dVdseffCV_dVb + T6 * dAbulkCV_dVb) 
	      + Csg * dVgsteff_dVb;
	    Csg *= dVgsteff_dVg;
	  }else{
	    trace0("50/50 Charge petition model");
	    qsrc = -0.5 * (d->qgate + d->qbulk);
	    Csg = -0.5 * (Cgg1 + Cbg1);
	    Csb = -0.5 * (Cgb1 + Cbb1); 
	    Csd = -0.5 * (Cgd1 + Cbd1); 
	  }
	  trace4("", Csg, Csd, Csb, qsrc);

	  d->qgate += Qac0 + Qsub0;
	  d->qbulk -= (Qac0 + Qsub0);
	  d->qdrn = -(d->qgate + d->qbulk + qsrc);
	  trace3("2-2", d->qgate, d->qbulk, d->qdrn);
	  
	  double Cgg = dQac0_dVg + dQsub0_dVg + Cgg1;
	  //double Cgd = dQac0_dVd + dQsub0_dVd + Cgd1;
	  double Cgd = dQsub0_dVd + Cgd1;
	  double Cgb = dQac0_dVb + dQsub0_dVb + Cgb1;
	  trace3("", Cgg, Cgd, Cgb);
	  
	  double Cbg = Cbg1 - dQac0_dVg - dQsub0_dVg;
	  //double Cbd = Cbd1 - dQac0_dVd - dQsub0_dVd;
	  double Cbd = Cbd1 - dQsub0_dVd;
	  double Cbb = Cbb1 - dQac0_dVb - dQsub0_dVb;
	  trace3("", Cbg, Cbd, Cbb);

	  Cgb *= dVbseff_dVb;
	  Cbb *= dVbseff_dVb;
	  Csb *= dVbseff_dVb;
	  trace3("adjusted", Cgb, Cbb, Csb);
	  
	  d->cggb = Cgg;
	  d->cgsb = -(Cgg + Cgd + Cgb);
	  d->cgdb = Cgd;
	  d->cdgb = -(Cgg + Cbg + Csg);
	  d->cdsb = (Cgg + Cgd + Cgb + Cbg + Cbd + Cbb + Csg + Csd + Csb);
	  d->cddb = -(Cgd + Cbd + Csd);
	  d->cbgb = Cbg;
	  d->cbsb = -(Cbg + Cbd + Cbb);
	  d->cbdb = Cbd;
	  trace0("end capMod == 2");
	  assert(d->qbulk == d->qbulk);
	  assert(d->qdrn == d->qdrn);
	  assert(d->qgate == d->qgate);
	}else if (m->capMod == 3) {
	  trace0("begin capMod == 3");
	  double Vfbeff, dVfbeff_dVg, dVfbeff_dVb;
	  {
	    const double DELTA_3 = 0.02;
	    double V3 = t->vfbzb - Vgs_eff + VbseffCV - DELTA_3;
	    double T0;
	    if (t->vfbzb <= 0.0) {
	      T0 = sqrt(V3 * V3 - 4.0 * DELTA_3 * t->vfbzb);
	      //T2 = -DELTA_3 / T0;
	    }else{
	      T0 = sqrt(V3 * V3 + 4.0 * DELTA_3 * t->vfbzb);
	      //T2 = DELTA_3 / T0;
	    }
	    double T1 = 0.5 * (1.0 + V3 / T0);
	    Vfbeff = t->vfbzb - 0.5 * (V3 + T0);
	    dVfbeff_dVg = T1 * dVgs_eff_dVg;
	    dVfbeff_dVb = -T1 * dVbseffCV_dVb;
	  }
	  double Cox = m->cox;
	  double Tox = 1.0e8 * m->tox;
	  trace2("", Cox, Tox);

	  double Qac0, dQac0_dVg, dQac0_dVb;
	  double Qsub0, dQsub0_dVg, dQsub0_dVd, dQsub0_dVb;
	  {
	    double Coxeff, dCoxeff_dVg, dCoxeff_dVb, CoxWLcen;
	    {
	      double Tcen, dTcen_dVg, dTcen_dVb;
	      {
		double T0 = (Vgs_eff - VbseffCV - t->vfbzb) / Tox;
		double tmp = T0 * s->acde;
		trace2("", T0, tmp);
		if ((-EXP_THRESHOLD < tmp) && (tmp < EXP_THRESHOLD)) {
		  double dT0_dVg = dVgs_eff_dVg / Tox;
		  double dT0_dVb = -dVbseffCV_dVb / Tox;
		  trace4("", dT0_dVg, dT0_dVb, s->ldeb, exp(tmp));
		  Tcen = s->ldeb * exp(tmp);
		  dTcen_dVg = s->acde * Tcen;
		  dTcen_dVb = dTcen_dVg * dT0_dVb;
		  dTcen_dVg *= dT0_dVg;
		}else if (tmp <= -EXP_THRESHOLD) {
		  Tcen = s->ldeb * MIN_EXP;
		  dTcen_dVg = dTcen_dVb = 0.0;
		}else{
		  Tcen = s->ldeb * MAX_EXP;
		  dTcen_dVg = dTcen_dVb = 0.0;
		}
		trace3("1", Tcen, dTcen_dVg, dTcen_dVb);
		double LINK = 1.0e-3 * m->tox;
		double V3 = s->ldeb - Tcen - LINK;
		double V4 = sqrt(V3 * V3 + 4.0 * LINK * s->ldeb);
		double T1 = 0.5 * (1.0 + V3 / V4);
		trace4("", LINK, V3, V4, T1);
		Tcen = s->ldeb - 0.5 * (V3 + V4);
		dTcen_dVg *= T1;
		dTcen_dVb *= T1;
	      }
	      trace3("2", Tcen, dTcen_dVg, dTcen_dVb);
	      {
		double Ccen = P_EPS_SI / Tcen;
		double T2 = Cox / (Cox + Ccen);
		double T3 = -Ccen / Tcen;
		trace3("Coxeff", Ccen, T2, T3);
		Coxeff = T2 * Ccen;
		dCoxeff_dVg = T2 * T2 * T3;
		dCoxeff_dVb = dCoxeff_dVg * dTcen_dVb;
		dCoxeff_dVg *= dTcen_dVg;
		CoxWLcen = CoxWL * Coxeff / Cox;
	      }
	    }
	    trace4("", Coxeff, dCoxeff_dVg, dCoxeff_dVb, CoxWLcen);
	    //double Qac0, dQac0_dVg, dQac0_dVb;
	    {
	      trace4("Qac0", CoxWLcen, Vfbeff, t->vfbzb, Coxeff);
	      Qac0 = CoxWLcen * (Vfbeff - t->vfbzb);
	      double QovCox = Qac0 / Coxeff;
	      dQac0_dVg = CoxWLcen * dVfbeff_dVg + QovCox * dCoxeff_dVg;
	      dQac0_dVb = CoxWLcen * dVfbeff_dVb + QovCox * dCoxeff_dVb;
	    }
	    trace3("", Qac0, dQac0_dVg, dQac0_dVb);
	    
	    //double Qsub0, dQsub0_dVg, dQsub0_dVd, dQsub0_dVb;
	    {
	      double T0 = 0.5 * t->k1ox;
	      double T3 = Vgs_eff - Vfbeff - VbseffCV - Vgsteff;
	      double T1, T2;
	      if (t->k1ox == 0.0) {
		T1 = 0.0;
		T2 = 0.0;
	      }else if (T3 < 0.0) {
		T1 = T0 + T3 / t->k1ox;
		T2 = CoxWLcen;
	      }else{
		T1 = sqrt(T0 * T0 + T3);
		T2 = CoxWLcen * T0 / T1;
	      }
	      
	      Qsub0 = CoxWLcen * t->k1ox * (T1 - T0);
	      double QovCox = Qsub0 / Coxeff;
	      dQsub0_dVg = T2 * (dVgs_eff_dVg - dVfbeff_dVg - dVgsteff_dVg)
		+ QovCox * dCoxeff_dVg;
	      dQsub0_dVd = -T2 * dVgsteff_dVd;
	      dQsub0_dVb = -T2 * (dVfbeff_dVb + dVbseffCV_dVb + dVgsteff_dVb)
		+ QovCox * dCoxeff_dVb;
	    }
	    trace4("", Qsub0, dQsub0_dVg, dQsub0_dVd, dQsub0_dVb);
	  } // end scope Coxeff, CoxWLcen
	  assert(Qac0 == Qac0);
	  assert(Qsub0 == Qsub0);
	  
	  double VgDP, dVgDP_dVg;
	  {
	    double DeltaPhi, dDeltaPhi_dVg;
	    { /* Gate-bias dependent delta Phis begins */
	      double Denomi, T0;
	      if (t->k1ox <= 0.0) {
		Denomi = 0.25 * s->moin * t->vtm;
		T0 = 0.5 * t->sqrtPhi;
	      }else{
		Denomi = s->moin * t->vtm * t->k1ox * t->k1ox;
		T0 = t->k1ox * t->sqrtPhi;
	      }
	      double T1 = 2.0 * T0 + Vgsteff;
	      DeltaPhi = t->vtm * log(1.0 + T1 * Vgsteff / Denomi);
	      dDeltaPhi_dVg = 2.0 * t->vtm * (T1-T0) / (Denomi + T1 * Vgsteff);
	    }
	    
	    /* VgDP = Vgsteff - DeltaPhi */
	    double T0 = Vgsteff - DeltaPhi - 0.001;
	    double dT0_dVg = 1.0 - dDeltaPhi_dVg;
	    double T1 = sqrt(T0 * T0 + Vgsteff * 0.004);
	    VgDP = 0.5 * (T0 + T1);
	    dVgDP_dVg = 0.5 * (dT0_dVg + (T0 * dT0_dVg + 0.002) / T1);
	  }

	  double Coxeff, dCoxeff_dVg, dCoxeff_dVd, dCoxeff_dVb;
	  {
	    double Tcen, dTcen_dVg, dTcen_dVd, dTcen_dVb;
	    {
	      double T3 = 4.0 * (d->von - t->vfbzb - t->phi);
	      Tox += Tox;
	      double T0, dT0_dVd, dT0_dVb;
	      if (T3 >= 0.0) {
		T0 = (Vgsteff + T3) / Tox;
		dT0_dVd = (dVgsteff_dVd + 4.0 * dVth_dVd) / Tox;
		dT0_dVb = (dVgsteff_dVb + 4.0 * dVth_dVb) / Tox;
	      }else{
		T0 = (Vgsteff + 1.0e-20) / Tox;
		dT0_dVd = dVgsteff_dVd / Tox;
		dT0_dVb = dVgsteff_dVb / Tox;
	      }
	      double tmp = exp(0.7 * log(T0));
	      double T1 = 1.0 + tmp;
	      double T2 = 0.7 * tmp / (T0 * Tox);
	      Tcen = 1.9e-9 / T1;
	      dTcen_dVg = -1.9e-9 * T2 / T1 /T1;
	      dTcen_dVd = Tox * dTcen_dVg;
	      dTcen_dVb = dTcen_dVd * dT0_dVb;
	      dTcen_dVd *= dT0_dVd;
	      dTcen_dVg *= dVgsteff_dVg;
	    }
	    double Ccen = P_EPS_SI / Tcen;
	    double T0 = Cox / (Cox + Ccen);
	    Coxeff = T0 * Ccen;
	    double T1 = -Ccen / Tcen;
	    dCoxeff_dVg = T0 * T0 * T1;
	    dCoxeff_dVd = dCoxeff_dVg * dTcen_dVd;
	    dCoxeff_dVb = dCoxeff_dVg * dTcen_dVb;
	    dCoxeff_dVg *= dTcen_dVg;
	  }
	  double CoxWLcen = CoxWL * Coxeff / Cox;
	  double AbulkCV = Abulk0 * s->abulkCVfactor;
	  double dAbulkCV_dVb = s->abulkCVfactor * dAbulk0_dVb;

	  double VdseffCV, dVdseffCV_dVg, dVdseffCV_dVd, dVdseffCV_dVb;
	  {
	    const double DELTA_4 = 0.02;
	    double VdsatCV =  VgDP / AbulkCV;
	    double T0 = VdsatCV - d->vds - DELTA_4;
	    double dT0_dVg = dVgDP_dVg / AbulkCV;
	    double dT0_dVb = -VdsatCV * dAbulkCV_dVb / AbulkCV;
	    double T1 = sqrt(T0 * T0 + 4.0 * DELTA_4 * VdsatCV);
	    double dT1_dVg = (T0 + DELTA_4 + DELTA_4) / T1;
	    double dT1_dVd = -T0 / T1;
	    double dT1_dVb = dT1_dVg * dT0_dVb;
	    dT1_dVg *= dT0_dVg;
	    if (T0 >= 0.0) {
	      VdseffCV = VdsatCV - 0.5 * (T0 + T1);
	      dVdseffCV_dVg = 0.5 * (dT0_dVg - dT1_dVg);
	      dVdseffCV_dVd = 0.5 * (1.0 - dT1_dVd);
	      dVdseffCV_dVb = 0.5 * (dT0_dVb - dT1_dVb);
	    }else{
	      double T3 = (DELTA_4 + DELTA_4) / (T1 - T0);
	      double T4 = 1.0 - T3;
	      double T5 = VdsatCV * T3 / (T1 - T0);
	      VdseffCV = VdsatCV * T4;
	      dVdseffCV_dVg = dT0_dVg * T4 + T5 * (dT1_dVg - dT0_dVg);
	      dVdseffCV_dVd = T5 * (dT1_dVd + 1.0);
	      dVdseffCV_dVb = dT0_dVb * (1.0 - T5) + T5 * dT1_dVb;
	    }
	    /* Added to eliminate non-zero VdseffCV at Vds=0.0 */
	    if (d->vds == 0.0) {
	      VdseffCV = 0.0;
	      dVdseffCV_dVg = 0.0;
	      dVdseffCV_dVb = 0.0;
	    }
	  }
	  
	  double T0 = AbulkCV * VdseffCV;
	  double T1 = VgDP;
	  double T2 = 12.0 * (T1 - 0.5 * T0 + 1.0e-20);
	  double T3 = T0 / T2;
	  double T4 = 1.0 - 12.0 * T3 * T3;
	  double T5 = AbulkCV * (6.0 * T0 * (4.0 * T1 - T0) / (T2*T2) - 0.5);
	  double T6 = T5 * VdseffCV / AbulkCV;
	  d->qgate = CoxWLcen * (T1 - T0 * (0.5 - T3));
	  //////////double qinoi = qgate;
	  
	  double Cgg1, Cgd1, Cgb1;
	  {
	    double QovCox = d->qgate / Coxeff;
	    Cgg1 = CoxWLcen * (T4 * dVgDP_dVg + T5 * dVdseffCV_dVg);
	    Cgd1 = CoxWLcen * T5 * dVdseffCV_dVd + Cgg1 
	      * dVgsteff_dVd + QovCox * dCoxeff_dVd;
	    Cgb1 = CoxWLcen * (T5 * dVdseffCV_dVb + T6 * dAbulkCV_dVb) 
	      + Cgg1 * dVgsteff_dVb + QovCox * dCoxeff_dVb;
	    Cgg1 = Cgg1 * dVgsteff_dVg + QovCox * dCoxeff_dVg;
	  }
	  
	  double T7 = 1.0 - AbulkCV;
	  double T8 = T2 * T2;
	  double T9 = 12.0 * T7 * T0 * T0 / (T8 * AbulkCV);
	  double T10 = T9 * dVgDP_dVg;
	  double T11 = -T7 * T5 / AbulkCV;
	  double T12 = -(T9 * T1 / AbulkCV + VdseffCV * (0.5 - T0 / T2));
	  d->qbulk = CoxWLcen * T7 * (0.5 * VdseffCV - T0 * VdseffCV / T2);

	  assert(d->qbulk == d->qbulk);
	  assert(d->qdrn == d->qdrn);
	  assert(d->qgate == d->qgate);
	  
	  double Cbg1, Cbd1, Cbb1;
	  {
	    double QovCox = d->qbulk / Coxeff;
	    Cbg1 = CoxWLcen * (T10 + T11 * dVdseffCV_dVg);
	    Cbd1 = CoxWLcen * T11 * dVdseffCV_dVd + Cbg1
	      * dVgsteff_dVd + QovCox * dCoxeff_dVd; 
	    Cbb1 = CoxWLcen * (T11 * dVdseffCV_dVb + T12 * dAbulkCV_dVb)
	      + Cbg1 * dVgsteff_dVb + QovCox * dCoxeff_dVb;
	    Cbg1 = Cbg1 * dVgsteff_dVg + QovCox * dCoxeff_dVg;
	  }
	  //////////qsrc -- scope too wide??
	  double Csg, Csd, Csb;
	  if (m->xpart > 0.5) {
	    /* 0/100 partition */
	    qsrc = -CoxWLcen * (T1 / 2.0 + T0 / 4.0 - 0.5 * T0 * T0 / T2);
	    double QovCox = qsrc / Coxeff;
	    T2 += T2;
	    T3 = T2 * T2;
	    T7 = -(0.25 - 12.0 * T0 * (4.0 * T1 - T0) / T3);
	    T4 = -(0.5 + 24.0 * T0 * T0 / T3) * dVgDP_dVg;
	    T5 = T7 * AbulkCV;
	    T6 = T7 * VdseffCV;
	    
	    Csg = CoxWLcen * (T4 + T5 * dVdseffCV_dVg);
	    Csd = CoxWLcen * T5 * dVdseffCV_dVd + Csg * dVgsteff_dVd
	      + QovCox * dCoxeff_dVd;
	    Csb = CoxWLcen * (T5 * dVdseffCV_dVb + T6 * dAbulkCV_dVb)
	      + Csg * dVgsteff_dVb + QovCox * dCoxeff_dVb;
	    Csg = Csg * dVgsteff_dVg + QovCox * dCoxeff_dVg;
	  }else if (m->xpart < 0.5) {
	    /* 40/60 partition */
	    T2 = T2 / 12.0;
	    T3 = 0.5 * CoxWLcen / (T2 * T2);
	    T4 = T1 * (2.0 * T0 * T0 / 3.0 + T1 * (T1 - 4.0 * T0 / 3.0))
	      - 2.0 * T0 * T0 * T0 / 15.0;
	    qsrc = -T3 * T4;
	    double QovCox = qsrc / Coxeff;
	    T8 = 4.0 / 3.0 * T1 * (T1 - T0) + 0.4 * T0 * T0;
	    T5 = -2.0 * qsrc / T2 
	      - T3 * (T1 * (3.0 * T1 - 8.0 * T0 / 3.0) + 2.0 * T0 * T0 / 3.0);
	    T6 = AbulkCV * (qsrc / T2 + T3 * T8);
	    T7 = T6 * VdseffCV / AbulkCV; 
	    
	    Csg = T5 * dVgDP_dVg + T6 * dVdseffCV_dVg; 
	    Csd = Csg * dVgsteff_dVd + T6 * dVdseffCV_dVd 
	      + QovCox * dCoxeff_dVd;
	    Csb = Csg * dVgsteff_dVb + T6 * dVdseffCV_dVb 
	      + T7 * dAbulkCV_dVb + QovCox * dCoxeff_dVb; 
	    Csg = Csg * dVgsteff_dVg + QovCox * dCoxeff_dVg;
	  }else{
	    /* 50/50 partition */
	    qsrc = -0.5 * d->qgate;
	    Csg = -0.5 * Cgg1;
	    Csd = -0.5 * Cgd1; 
	    Csb = -0.5 * Cgb1; 
	  }
	  //////////
	  assert(Qsub0 == Qsub0);
	  assert(Qac0 == Qac0);

	  d->qgate += Qac0 + Qsub0 - d->qbulk;
	  d->qbulk -= (Qac0 + Qsub0);
	  d->qdrn = -(d->qgate + d->qbulk + qsrc);

	  assert(d->qbulk == d->qbulk);
	  assert(d->qdrn == d->qdrn);
	  assert(d->qgate == d->qgate);
	  
	  {
	    double Cbg = Cbg1 - dQac0_dVg - dQsub0_dVg;
	    double Cbd = Cbd1 - dQsub0_dVd;
	    double Cbb = Cbb1 - dQac0_dVb - dQsub0_dVb;
	    
	    double Cgg = Cgg1 - Cbg;
	    double Cgd = Cgd1 - Cbd;
	    double Cgb = Cgb1 - Cbb;
	    
	    Cgb *= dVbseff_dVb;
	    Cbb *= dVbseff_dVb;
	    Csb *= dVbseff_dVb;
	    
	    d->cggb = Cgg;
	    d->cgsb = -(Cgg + Cgd + Cgb);
	    d->cgdb = Cgd;

	    d->cdgb = -(Cgg + Cbg + Csg);
	    d->cdsb = (Cgg + Cgd + Cgb + Cbg + Cbd + Cbb + Csg + Csd + Csb);
	    d->cddb = -(Cgd + Cbd + Csd);

	    d->cbgb = Cbg;
	    d->cbsb = -(Cbg + Cbd + Cbb);
	    d->cbdb = Cbd;
	  }
	  ////////// d->qinv = -qinoi;
	  assert(d->qbulk == d->qbulk);
	  assert(d->qdrn == d->qdrn);
	  assert(d->qgate == d->qgate);
	}else{
	  error(bDANGER, "illegal capmod = %d\n", int(m->capMod));
	  d->qgate = d->qdrn = d->qbulk = 0.0;
	  d->cggb = d->cgsb = d->cgdb = 0.0;
	  d->cdgb = d->cdsb = d->cddb = 0.0;
	  d->cbgb = d->cbsb = d->cbdb = 0.0;
	  ////////// d->cqdb = d->cqsb = d->cqgb = d->cqbb = 0.0;
	  ////////// d->gtau = 0.0;
	  trace0("xpart < 0 || no charge computation");
	  untested();
	  assert(d->qbulk == d->qbulk);
	  assert(d->qdrn == d->qdrn);
	  assert(d->qgate == d->qgate);
	  untested();
	}
	assert(d->qbulk == d->qbulk);
	assert(d->qdrn == d->qdrn);
	assert(d->qgate == d->qgate);

	/* Non-quasi-static Model */
	double tconst;
	if (m->nqsMod) {
	  //  d->gtau
	  double qcheq = -d->qbulk - d->qgate;
	  double T0 = s->leffCV * s->leffCV;
	  tconst = t->u0temp * s->elm / CoxWL / T0;
	  if (qcheq == 0.0) {
	    tconst = 0.0;
	  }else if (qcheq < 0.0) {
	    tconst = -tconst;
	  }else{
	  }
	  double gtau_drift = std::abs(tconst * qcheq);
	  double gtau_diff = 16.0 * t->u0temp * t->vtm / T0;
	  d->gtau =  gtau_drift + gtau_diff;
	  d->cqgb = -(d->cggb + d->cbgb);
	  d->cqdb = -(d->cgdb + d->cbdb);
	  d->cqsb = -(d->cgsb + d->cbsb);
	  d->cqbb = d->cggb +d->cgdb +d->cgsb +d->cbgb +d->cbdb +d->cbsb;
	  
	  d->qbulk = d->qgate = d->qdrn = qsrc = 0.0;
	  d->cggb = d->cgsb = d->cgdb = 0.0;
	  d->cdgb = d->cdsb = d->cddb = 0.0;
	  d->cbgb = d->cbsb = d->cbdb = 0.0;
#if 0
	  *(ckt->CKTstate0 + d->qcheq) = qcheq;
	  if (ckt->CKTmode & MODEINITTRAN)
	    *(ckt->CKTstate1 + d->qcheq) = *(ckt->CKTstate0 + d->qcheq);
	  error = NIintegrate(ckt, &geq, &ceq, 0.0, d->qcheq);
	  if (error) return (error);
#endif
	}else{
	  d->gtau = 0.0;
	  d->cqgb = d->cqdb = d->cqsb = d->cqbb = 0.0;
	}
      }
    }
    if (d->reversed) {
      d->qdrn = -d->qdrn;
      d->cdgb = -d->cdgb;
      {
	double t1 = d->cdsb;
	d->cdsb = -d->cddb;
	d->cddb = -t1;
      }

      d->qgd   = d->qgate;
      d->cgdgb = d->cggb;
      d->cgdsb = d->cgsb;
      d->cgddb = d->cgdb;
      d->qgs   = 0.;
      d->cgsgb = 0.;
      d->cgssb = 0.;
      d->cgsdb = 0.;

      d->qbd   = d->qbulk;
      d->cbdgb = d->cbgb;
      d->cbdsb = d->cbsb;
      d->cbddb = d->cbdb;
      d->qbs   = 0.;
      d->cbsgb = 0.;
      d->cbssb = 0.;
      d->cbsdb = 0.;
    }else{
      d->qgs   = d->qgate;
      d->cgsgb = d->cggb;
      d->cgssb = d->cgsb;
      d->cgsdb = d->cgdb;
      d->qgd   = 0.;
      d->cgdgb = 0.;
      d->cgdsb = 0.;
      d->cgddb = 0.;

      d->qbs   = d->qbulk;
      d->cbsgb = d->cbgb;
      d->cbssb = d->cbsb;
      d->cbsdb = d->cbdb;
      d->qbd   = 0.;
      d->cbdgb = 0.;
      d->cbdsb = 0.;
      d->cbddb = 0.;
    }
    if (polarity == -1){
      d->qgs *= -1;
      d->qbd *= -1;
      d->qbs *= -1;
      d->qgd *= -1;
      d->qdrn *= -1;
      // d->qbulk *= -1;
    }
    
    assert(d->qbulk == d->qbulk);
    assert(d->qdrn == d->qdrn);
    assert(d->qgate == d->qgate);
    
    trace0("mos8");
    trace4("", d->qgate, d->cggb, d->cgsb, d->cgdb);
    trace4("", d->qdrn,  d->cdgb, d->cdsb, d->cddb);
    trace4("", d->qbulk, d->cbgb, d->cbsb, d->cbdb);

    trace2("", d->ids, d->gds);
    trace4("", d->gmf, d->gmr, d->gmbf, d->gmbr);
    //trace4("", d->isub, d->gbbs, d->gbgs, d->gbds);
    //trace4("", d->qgate, d->cggb, d->cgsb, d->cgdb);
    trace4("", d->qdrn, d->cdgb, d->cdsb, d->cddb);
    trace4("", d->qbulk, d->cbgb, d->cbsb, d->cbdb);
    trace1("", d->gtau);
    trace4("", d->cqgb, d->cqsb, d->cqdb, d->cqbb);
    //trace1("", d->tconst);
    //trace2("", d->cgb, d->qgb);
    //trace2("", d->qgd, d->cgd);
    trace2("", d->qgs, d->cgs);
    trace3("", d->vgs, d->vds, d->vbs);
    trace3("", d->vdsat, d->vgst, d->von);
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
void MODEL_BUILT_IN_MOS8::do_tr_stress( const COMPONENT* ) const
{
  assert(false);
}
/*--------------------------------------------------------------------------*/
ADP_CARD* MODEL_BUILT_IN_MOS8::new_adp( COMPONENT* c)const
{
  assert(c);
  //const MODEL_BUILT_IN_MOS8* m = this;
  trace0(( "MODEL_BUILT_IN_MOS8::new_adp for " + c->short_label() ).c_str() );

  //attach a generic adp for MOS8 effects
  if (!use_hci()){
    return new ADP_BUILT_IN_MOS(c,"dummy");
  }
  ADP_BUILT_IN_MOS8* a = new ADP_BUILT_IN_MOS8(c,"adp");

  assert( c->adp() == NULL );
  assert(a);
  return a;
}
/*--------------------------------------------------------------------------*/
void MODEL_BUILT_IN_MOS8::do_stress_apply(COMPONENT*) const
{
  return; // obsolete
}
/*--------------------------------------------------------------------------*/
ADP_BUILT_IN_MOS8::ADP_BUILT_IN_MOS8(const ADP_BUILT_IN_MOS8& a):
    ADP_BUILT_IN_MOS(a)
   //  vthscale_hci(a.vthscale_hci),
   //  vthdelta_hci(a.vthdelta_hci),
   //  _raw_hci_node(0)
{
}
/*--------------------------------------------------------------------------*/

  //void ADP_BUILT_IN_MOS8::init(const COMPONENT* c)
//{
//  const COMMON_COMPONENT* cc = c->common();
//  const MODEL_BUILT_IN_MOS_BASE* m = prechecked_cast<const MODEL_BUILT_IN_MOS_BASE*>(cc->model());
//  assert(m);
//
//  std::cerr << "ADP_BUILT_IN_MOS8::init( " <<c<< " ) " << c->short_label() << "\n" ;
////  ids_stress = new ADP(this,c, "ids" );
////  igd_stress = new ADP(this,c, "igs" );
////
////  ADP_NODE_LIST::adp_list.push_back( ids_stress );
////  ADP_NODE_LIST::adp_list.push_back( igd_stress );
////
//
//}
/*------------------------------------------------------------------*/
const COMPONENT* MODEL_BUILT_IN_MOS8::hci_device()const
{
  if (((double)h0 == 0) || (h0==NA)) {
    return 0;
  }
  const COMPONENT* c = dynamic_cast<const COMPONENT*>(device_dispatcher["hci"]);
  return c;
}
/*--------------------------------------------------------------------------*/
void MODEL_BUILT_IN_MOS8::sens_eval(COMPONENT* brh) const
{
  DEV_BUILT_IN_MOS* d = prechecked_cast<DEV_BUILT_IN_MOS*>(brh);
  assert(d);
  const COMMON_BUILT_IN_MOS* c = prechecked_cast<const COMMON_BUILT_IN_MOS*>(d->common());
  assert(c);
  const MODEL_BUILT_IN_MOS8* m = this;
  const TDP_BUILT_IN_MOS8 T(d);
  const TDP_BUILT_IN_MOS8* t = &T;
  const SDP_BUILT_IN_MOS8* s = prechecked_cast<const SDP_BUILT_IN_MOS8*>(c->sdp());
  assert(s);

  const double EXP_THRESHOLD = 34.0;
  const double MIN_EXP = 1.713908431e-15;
  const double MAX_EXP = 5.834617425e14;

  double L = s->leff;
  double W = s->weff;
  const CARD_LIST* par_scope = m->scope(); // BUG: slow

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  double Vbseff, dVbseff_dVb;
  double dVbseff_dW, dVbseff_dL;
  {
    double T0 = d->vbs - t->vbsc - 0.001;
    double T1 = sqrt(T0 * T0 - 0.004 * t->vbsc);
    trace4("", t->vbsc, T0, T1, d->vbs);
    Vbseff = t->vbsc + 0.5 * (T0 + T1);
    // dvbsc_dW = 0; hmmm, BUG?
    // dvbsc_dL = 0; hmmm, BUG?
    dVbseff_dW = 0;
    dVbseff_dL = 0;
    dVbseff_dVb = 0.5 * (1.0 + T0 / T1);
    trace2("raw", Vbseff, dVbseff_dVb);

  //  fixzero(&Vbseff, t->vbsc);
  }

  // SENS:
  double Phis, dPhis_dVb, sqrtPhis, dsqrtPhis_dVb;
  double dsqrtPhis_dW, dsqrtPhis_dL;
  if (Vbseff > 0.0) {
    //untested();
    assert(d->sbfwd);
    double T0 = t->phi / (t->phi + Vbseff);
//    double dT0_dW = - T0 / (t->phi + Vbseff) * dVbseff_dW;
//    double dT0_dL = - T0 / (t->phi + Vbseff) * dVbseff_dL;
    Phis = t->phi * T0;
//    double dPhis_dW = t->phi * dT0_dW;
//    double dPhis_dL = t->phi * dT0_dL;
    dPhis_dVb = -T0 * T0; USE(dPhis_dVb);
    sqrtPhis = t->phis3 / (t->phi + 0.5 * Vbseff);
    dsqrtPhis_dW = /*t->dphis3_dW / (t->phi + 0.5 * Vbseff) */
                 - sqrtPhis / (t->phi + 0.5 * Vbseff) * .5 * dVbseff_dW;
    dsqrtPhis_dL = /*t->dphis3_dL / (t->phi + 0.5 * Vbseff) */
                 - sqrtPhis / (t->phi + 0.5 * Vbseff) * .5 * dVbseff_dL;
    dsqrtPhis_dVb = -0.5 * sqrtPhis * sqrtPhis / t->phis3;
    trace0("bs-fwd-bias");
  }else{
    assert(!d->sbfwd);
    Phis = t->phi - Vbseff;
    double dPhis_dW = - dVbseff_dW;
    double dPhis_dL = - dVbseff_dL;
    dPhis_dVb = -1.0; USE(dPhis_dVb);
    sqrtPhis = sqrt(Phis);
    dsqrtPhis_dW = .5 / sqrt(Phis) * dPhis_dW;
    dsqrtPhis_dL = .5 / sqrt(Phis) * dPhis_dL;
    dsqrtPhis_dVb = -0.5 / sqrtPhis;
    trace0("bs-normal");
  }
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  double Xdep = t->Xdep0 * sqrtPhis / t->sqrtPhi;
  double dXdep_dW = t->Xdep0 * dsqrtPhis_dW / t->sqrtPhi; // assuming npeak is const
  double dXdep_dL = t->Xdep0 * dsqrtPhis_dL / t->sqrtPhi; // assuming npeak is const
  double dXdep_dVb = (t->Xdep0 / t->sqrtPhi) * dsqrtPhis_dVb;

  // - - - - - - - - - - - - - - - - - - - -
  double Theta0, dTheta0_dVb;
  double dTheta0_dW, dTheta0_dL;
  {
    double lt1, dlt1_dVb;
    double dlt1_dW, dlt1_dL;
    {
      double T3 = sqrt(Xdep);
      double dT3_dW = .5 / T3 * dXdep_dW;
      double dT3_dL = .5 / T3 * dXdep_dL;
      double T0 = s->dvt2 * Vbseff;
      double dT0_dW = m->dvt2.dW(L,W,par_scope) * Vbseff
	            + s->dvt2 * dVbseff_dW;
      double dT0_dL = m->dvt2.dL(L,W,par_scope) * Vbseff
	            + s->dvt2 * dVbseff_dL;
      double T1, T2;
      double dT1_dW, dT1_dL;
      if (T0 >= - 0.5) {
        T1 = 1.0 + T0;
	dT1_dW = dT0_dW;
	dT1_dL = dT0_dL;
        T2 = s->dvt2;
        trace4("", T0, T1, T2, T3);
      }else{
        //untested();
        /* Added to avoid any discontinuity problems caused by dvt2 */ 
        double T4 = 1.0 / (3.0 + 8.0 * T0);
	double dT4_dW = - T4 /  (3.0 + 8.0 * T0) * 8. * dT0_dW;
	double dT4_dL = - T4 /  (3.0 + 8.0 * T0) * 8. * dT0_dL;
        T1 = (1.0 + 3.0 * T0) * T4;
	dT1_dW = (3. * dT0_dW ) * T4 + (1.0 + 3.0 * T0) * dT4_dW;
	dT1_dL = (3. * dT0_dL ) * T4 + (1.0 + 3.0 * T0) * dT4_dL;
        T2 = s->dvt2 * T4 * T4;
        trace4("dvd2 fix", T0, T1, T2, T3);
      }
      lt1 = m->factor1 * T3 * T1;
      dlt1_dW = m->factor1 * T3 * dT1_dW +  m->factor1 * dT3_dW * T1;
      dlt1_dL = m->factor1 * T3 * dT1_dL +  m->factor1 * dT3_dL * T1;
      dlt1_dVb = m->factor1 * (0.5 / T3 * T1 * dXdep_dVb + T3 * T2);
    }
    trace2("", lt1, dlt1_dVb);

    double T0 = -0.5 * s->dvt1 * s->leff / lt1;
    double dT0_dW = -0.5 * m->dvt1.dW(L,W,par_scope) * s->leff / lt1
	            - T0 / lt1 * dlt1_dW;
    double dT0_dL = -0.5 * ( m->dvt1.dL(L,W,par_scope) * s->leff / lt1
	                   + s->dvt1 / lt1 )
	            - T0 / lt1 * dlt1_dL;
    if (T0 > -EXP_THRESHOLD) {
      double T1 = exp(T0);
      double dT1_dW = T1 * dT0_dW;
      double dT1_dL = T1 * dT0_dL;
      Theta0 = T1 * (1.0 + 2.0 * T1);
      dTheta0_dW = dT1_dW * (1.0 + 4.0 * T1);
      dTheta0_dL = dT1_dL * (1.0 + 4.0 * T1);
      double dT1_dVb = -T0 / lt1 * T1 * dlt1_dVb;
      dTheta0_dVb = (1.0 + 4.0 * T1) * dT1_dVb;
      trace2("T0 > -ET", Theta0, dTheta0_dVb);
    }else{
      const double MIN_EXP = 1.713908431e-15;
      double T1 = MIN_EXP;
      Theta0 = T1 * (1.0 + 2.0 * T1);
      dTheta0_dW = 0.;
      dTheta0_dL = 0.;
      dTheta0_dVb = 0.0;
      trace2("T0 < -ET", Theta0, dTheta0_dVb);
    }
  }
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  //  SENS:
  double dVth_dVb, dVth_dVd; // d->von
  double dVth_dW, dVth_dL;
  {
    double V0 = t->vbi - t->phi;
    double dV0_dW = 0; // npeak etc. const
    double dV0_dL = 0; // npeak etc. const
    double T2, dT2_dVb;
    double dT2_dW, dT2_dL;
    {
      double ltw, dltw_dVb;
      double dltw_dW, dltw_dL;
      {
        double T3 = sqrt(Xdep);
        double dT3_dW = .5 / T3 * dXdep_dW;
        double dT3_dL = .5 / T3 * dXdep_dL;
        double T0 = s->dvt2w * Vbseff;
	double dT0_dW = m->dvt2w.dW(L,W,par_scope) * Vbseff
	              + s->dvt2w * dVbseff_dW;
	double dT0_dL = m->dvt2w.dL(L,W,par_scope) * Vbseff
	              + s->dvt2w * dVbseff_dL;
        double T1, t2;
	double dT1_dW, dT1_dL;
        if (T0 >= - 0.5) {
          T1 = 1.0 + T0;
	  dT1_dW = dT0_dW;
	  dT1_dL = dT0_dL;
          t2 = s->dvt2w;
        }else{
          // untested();
          /* Added to avoid any discontinuity problems caused by dvt2w */ 
          double T4 = 1.0 / (3.0 + 8.0 * T0);
	  double dT4_dW = 8. * T4 / (3.0 + 8.0 * T0) * dT0_dW;
	  double dT4_dL = 8. * T4 / (3.0 + 8.0 * T0) * dT0_dL;
          T1 = (1.0 + 3.0 * T0) * T4;
	  dT1_dW = 3. * dT0_dW * T4 + (1.0 + 3.0 * T0) * dT4_dW;
	  dT1_dL = 3. * dT0_dL * T4 + (1.0 + 3.0 * T0) * dT4_dL;
          t2 = s->dvt2w * T4 * T4;
        }
        trace4("", T0, T1, t2, T3);
        ltw = m->factor1 * T3 * T1;
	dltw_dW = m->factor1 * ( dT3_dW * T1 + T3 * dT1_dW );
	dltw_dL = m->factor1 * ( dT3_dL * T1 + T3 * dT1_dL );
        dltw_dVb = m->factor1 * (0.5 / T3 * T1 * dXdep_dVb + T3 * t2);
      }
      trace2("", ltw, dltw_dVb);
      double T0 = -0.5 * s->dvt1w * s->weff * s->leff / ltw;
      double dT0_dW = -.5 *( -m->dvt1w.dW(L,W,par_scope) * s->weff * s->leff / ltw
	                     -s->dvt1w * s->leff / ltw
	                     +s->dvt1w * s->weff * s->leff / ltw / ltw * dltw_dW);
      double dT0_dL = -.5 *( -m->dvt1w.dL(L,W,par_scope) * s->weff * s->leff / ltw
	                     -s->dvt1w * s->weff / ltw
	                     +s->dvt1w * s->weff * s->leff / ltw / ltw * dltw_dL);
      if (T0 > -EXP_THRESHOLD) {
        double T1 = exp(T0);
	double dT1_dW = T1 * dT0_dW;
	double dT1_dL = T1 * dT0_dL;
        T2 = T1 * (1.0 + 2.0 * T1);
	dT2_dW = dT1_dW * (1. + 4. * T1);
	dT2_dL = dT1_dL * (1. + 4. * T1);
        double dT1_dVb = -T0 / ltw * T1 * dltw_dVb;
        dT2_dVb = (1.0 + 4.0 * T1) * dT1_dVb;
      }else{
        double T1 = MIN_EXP;
        T2 = T1 * (1.0 + 2.0 * T1);
	dT2_dW = 0.;
	dT2_dL = 0.;
        dT2_dVb = 0.0;
        dT2_dVb = 0.0;
      }
      T0 = s->dvt0w * T2;
      T2 = T0 * V0;
      dT2_dVb = s->dvt0w * dT2_dVb * V0;
    }
    trace3("", V0, T2, dT2_dVb);
    double T0 = sqrt(1.0 + s->nlx / s->leff);
    double dT0_dW = .5 / T0
                  * m->nlx.dW(L,W,par_scope) / s->leff;
    double dT0_dL = .5 / T0
                  * ( m->nlx.dL(L,W,par_scope) / s->leff - s->nlx / s->leff / s->leff );
//    double T1 = t->k1ox * (T0 - 1.0) * t->sqrtPhi
//      + (s->kt1 + s->kt1l / s->leff + s->kt2 * Vbseff) * t->tempratio_1; unused
    double dT1_dW = t->k1ox * dT0_dW * t->sqrtPhi
      + ( m->kt1.dW(L,W,par_scope) + m->kt1l.dW(L,W,par_scope) / s->leff
	  + m->kt2.dW(L,W,par_scope) * Vbseff +  s->kt2 * dVbseff_dW )
      * t->tempratio_1;
    double dT1_dL = t->k1ox * dT0_dL * t->sqrtPhi
      + ( m->kt1.dL(L,W,par_scope)
	+ m->kt1l.dL(L,W,par_scope) / s->leff - s->kt1l / s->leff / s->leff
	+ m->kt2.dL(L,W,par_scope) * Vbseff + s->kt2 * dVbseff_dL )
      * t->tempratio_1;
    double tmp2 = m->tox * t->phi / (s->weff + s->w0);
    double dtmp2_dW = - m->tox * t->phi / (s->weff + s->w0) / (s->weff + s->w0)
                      * (1. + m->w0.dW(L,W,par_scope));
    double dtmp2_dL = - m->tox * t->phi / (s->weff + s->w0) / (s->weff + s->w0)
                      * m->w0.dL(L,W,par_scope);

    double T3 = s->eta0 + s->etab * Vbseff;
    double dT3_dW = m->eta0.dW(L,W,par_scope)
                  + m->etab.dW(L,W,par_scope) * Vbseff
                  + s->etab * dVbseff_dW;
    double dT3_dL = m->eta0.dL(L,W,par_scope)
                  + m->etab.dL(L,W,par_scope) * Vbseff
                  + s->etab * dVbseff_dL;
    double T4;
    if (T3 < 1.0e-4) {
      /* avoid  discontinuity problems caused by etab */ 
      double T9 = 1.0 / (3.0 - 2.0e4 * T3);
      double dT9_dW = T9 / (3.0 - 2.0e4 * T3) * 2.0e4 * dT3_dW;
      double dT9_dL = T9 / (3.0 - 2.0e4 * T3) * 2.0e4 * dT3_dL;
      dT3_dW = - dT3_dW * T9 - T3 * dT9_dW;
      dT3_dL = - dT3_dL * T9 - T3 * dT9_dL;
      T3 = (2.0e-4 - T3) * T9;
      T4 = T9 * T9;
    }else{
      T4 = 1.0;
    }
    double thetavth = s->dvt0 * Theta0;
    double dthetavth_dW = m->dvt0.dW(L,W,par_scope) * Theta0
                        + s->dvt0 * dTheta0_dW;
    double dthetavth_dL = m->dvt0.dL(L,W,par_scope) * Theta0
                        + s->dvt0 * dTheta0_dL;
//    double Delt_vth = thetavth * V0;
    double dDelt_vth_dW = dthetavth_dW * V0
                        + thetavth * dV0_dW;
    double dDelt_vth_dL = dthetavth_dL * V0
                        + thetavth * dV0_dL;

    double dDelt_vth_dVb = s->dvt0 * dTheta0_dVb * V0;
    trace3("", thetavth, t->theta0vb0, dDelt_vth_dVb);
    double dDIBL_Sft_dVd = T3 * t->theta0vb0;
    double ddDIBL_Sft_dVd_dW = dT3_dW * t->theta0vb0
                             + T3 *  t->dtheta0vb0_dW;
    double ddDIBL_Sft_dVd_dL = dT3_dL * t->theta0vb0
                             + T3 *  t->dtheta0vb0_dL;
//    double DIBL_Sft = dDIBL_Sft_dVd * d->vds;
    double dDIBL_Sft_dW = ddDIBL_Sft_dVd_dW * d->vds;
    double dDIBL_Sft_dL = ddDIBL_Sft_dVd_dL * d->vds;

#if 0
    double Vth = m->polarity * t->vth0
               + t->k1ox * sqrtPhis
               - t->k1 *  t->sqrtPhi
               - t->k2ox * Vbseff
               - Delt_vth
               - T2
               + (s->k3 + s->k3b * Vbseff) * tmp2 
               + T1
               - DIBL_Sft;
#endif
    dVth_dW = m->polarity * t->dvth0_dW
            + t->k1ox * dsqrtPhis_dW
            - t->k2ox * dVbseff_dW
            - dDelt_vth_dW
            - dT2_dW
            + (m->k3.dW(L,W,par_scope)
		+ m->k3b.dW(L,W,par_scope) * Vbseff
		+ s->k3b * dVbseff_dW) * tmp2
            + (s->k3 + s->k3b * Vbseff) * dtmp2_dW
            + dT1_dW
            - dDIBL_Sft_dW;

    dVth_dL = m->polarity * t->dvth0_dL
            + t->k1ox * dsqrtPhis_dL
            - t->k2ox * dVbseff_dL
            - dDelt_vth_dL
            - dT2_dL
            + (m->k3.dL(L,W,par_scope)
		+ m->k3b.dL(L,W,par_scope) * Vbseff
		+ s->k3b * dVbseff_dW) * tmp2
            + (s->k3 + s->k3b * Vbseff) * dtmp2_dL
            + dT1_dL
            - dDIBL_Sft_dL;

    // assert(polarity*Vth>0);

    double Vth = d->von; USE(Vth);

    dVth_dVb = t->k1ox * dsqrtPhis_dVb - t->k2ox  - dDelt_vth_dVb - dT2_dVb
      + s->k3b * tmp2 - s->etab * d->vds * t->theta0vb0 * T4
      + s->kt2 * t->tempratio_1;
    dVth_dVd = -dDIBL_Sft_dVd; 
  }
  double dVon_dW = dVth_dW; // alias
  double dVon_dL = dVth_dL; // alias
  // - - - - - - - - - - - - - - - - - - 
  double dphi_dW = 0; // for now. see TDP
  double dphi_dL = 0; // for now. see TDP
  /* SENS: Poly Gate Si Depletion Effect */
  double Vgs_eff, dVgs_eff_dVg;
  double dVgs_eff_dW, dVgs_eff_dL;
  double ddVgs_eff_dVg_dW, ddVgs_eff_dVg_dL;
  {
    double T0 = t->vfb + t->phi;
    double dT0_dW = t->dvfb_dW + dphi_dW;
    double dT0_dL = t->dvfb_dL + dphi_dL;
    trace2("Poly", t->vfb, t->phi);
    trace3("", s->ngate, d->vgs, T0);
    if ((s->ngate > 1.e18) && (s->ngate < 1.e25) && (d->vgs > T0)) {
      /* added to avoid the problem caused by ngate */
      double T1 = 1.0e6 * P_Q * P_EPS_SI * s->ngate / (m->cox * m->cox);
      // double dngate_dW = 0; // SDP. set 0 anyway (BUG?)
      // double dngate_dL = 0; // SDP. set 0 anyway (BUG?)
      // double dT1_dW = 0; // *
      // double dT1_dL = 0; // *
      double T4 = sqrt(1.0 + 2.0 * (d->vgs - T0) / T1);
      double dT4_dW = .5 / sqrt(1.0 + 2.0 * (d->vgs - T0) / T1) * ( -2. * dT0_dW / T1 );
      double dT4_dL = .5 / sqrt(1.0 + 2.0 * (d->vgs - T0) / T1) * ( -2. * dT0_dL / T1 );
      double T2 = T1 * (T4 - 1.0);
      double dT2_dW = T1 * dT4_dW; // *
      double dT2_dL = T1 * dT4_dL; // *
      double T3 = 0.5 * T2 * T2 / T1; /* T3 = Vpoly */
      double dT3_dW = T2 / T1 * dT2_dW; // *, T1
      double dT3_dL = T2 / T1 * dT2_dL; // *, T1
      double T7 = 1.12 - T3 - 0.05;
      double dT7_dW = - dT3_dW;
      double dT7_dL = - dT3_dL;
      double T6 = sqrt(T7 * T7 + 0.224);
      double dT6_dW = 1. / T6 * T7 * dT7_dW;
      double dT6_dL = 1. / T6 * T7 * dT7_dL;
      double T5 = 1.12 - 0.5 * (T7 + T6);
      double dT5_dW = - 0.5 * (dT7_dW + dT6_dW);
      double dT5_dL = - 0.5 * (dT7_dL + dT6_dL);
      Vgs_eff = d->vgs - T5;
      dVgs_eff_dVg = 1.0 - (0.5 - 0.5 / T4) * (1.0 + T7 / T6);
      ddVgs_eff_dVg_dW = -( .5 / T4 /T4 * dT4_dW ) * (1.0 + T7 / T6)
	                 -(0.5 - 0.5 / T4) * ( dT7_dW / T6 - T7/T6/T6/dT6_dW );
      ddVgs_eff_dVg_dL = -( .5 / T4 /T4 * dT4_dL ) * (1.0 + T7 / T6)
	                 -(0.5 - 0.5 / T4) * ( dT7_dL / T6 - T7/T6/T6/dT6_dL );
      dVgs_eff_dW = - dT5_dW;
      dVgs_eff_dL = - dT5_dL;
      trace2("><", Vgs_eff, dVgs_eff_dVg);
    }else{
      Vgs_eff = d->vgs;
      dVgs_eff_dVg = 1.0;
      ddVgs_eff_dVg_dW = 0;
      ddVgs_eff_dVg_dL = 0;
      dVgs_eff_dW = 0; // weird.
      dVgs_eff_dL = 0; // weird.
      trace2("const", Vgs_eff, dVgs_eff_dVg);
    }
  }
  // - - - - - - - - - - - - - - - - - - 
  /* SENS: Calculate n */
  double n, dn_dVb, dn_dVd;
  double dn_dW, dn_dL;
  {
    double tmp2 = s->nfactor * P_EPS_SI / Xdep;
    double dtmp2_dW = - tmp2 / Xdep * dXdep_dW;
    double dtmp2_dL = - tmp2 / Xdep * dXdep_dL;
    double tmp3 = s->cdsc + s->cdscb * Vbseff + s->cdscd * d->vds;
    double dtmp3_dW = m->cdsc.dW(L,W,par_scope)
                    + m->cdscb.dW(L,W,par_scope) * Vbseff
                    + s->cdscb * dVbseff_dW
		    + m->cdscd.dW(L,W,par_scope) * d->vds;
    double dtmp3_dL = m->cdsc.dL(L,W,par_scope)
                    + m->cdscb.dL(L,W,par_scope) * Vbseff
                    + s->cdscb * dVbseff_dL
		    + m->cdscd.dL(L,W,par_scope) * d->vds;
    double tmp4 = (tmp2 + tmp3 * Theta0 + s->cit) / m->cox;
    double dtmp4_dW = (dtmp2_dW + dtmp3_dW * Theta0 + tmp3 * dTheta0_dW
	+ m->cit.dW(L,W,par_scope))/ m->cox;
    double dtmp4_dL = (dtmp2_dL + dtmp3_dL * Theta0 + tmp3 * dTheta0_dL
	+ m->cit.dL(L,W,par_scope))/ m->cox;
    trace3("", tmp2, tmp3, tmp4);
    if (tmp4 >= -0.5) {
      n = 1.0 + tmp4;
      dn_dW = dtmp4_dW;
      dn_dL = dtmp4_dL;
      dn_dVb = (-tmp2 / Xdep * dXdep_dVb + tmp3 * dTheta0_dVb 
          + s->cdscb * Theta0) / m->cox;
      dn_dVd = s->cdscd * Theta0 / m->cox;
      trace3("n", n, dn_dVb, dn_dVd);
    }else{
      /* avoid  discontinuity problems caused by tmp4 */ 
      double T0 = 1.0 / (3.0 + 8.0 * tmp4);
      double dT0_dW = - 1.0 / (3.0 + 8.0 * tmp4) / (3.0 + 8.0 * tmp4)
	            * 8 * dtmp4_dW;
      double dT0_dL = - 1.0 / (3.0 + 8.0 * tmp4) / (3.0 + 8.0 * tmp4)
	            * 8 * dtmp4_dL;
      n = (1.0 + 3.0 * tmp4) * T0;
      dn_dW = 3. * dtmp4_dW * T0 + (1.0 + 3.0 * tmp4) * dT0_dW;
      dn_dL = 3. * dtmp4_dL * T0 + (1.0 + 3.0 * tmp4) * dT0_dL;
      T0 *= T0;
      dn_dVb = (-tmp2 / Xdep * dXdep_dVb + tmp3 * dTheta0_dVb
          + s->cdscb * Theta0) / m->cox * T0;
      dn_dVd = s->cdscd * Theta0 / m->cox * T0;
      trace3("n disc", n, dn_dVb, dn_dVd);
    }
  }
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  /* SENS: Effective Vgst (Vgsteff) Calculation */
  double /*Vgsteff,*/ dVgsteff_dVg, dVgsteff_dVd, dVgsteff_dVb, Vgst2Vtm;
  double dVgst2Vtm_dW;
  double dVgst2Vtm_dL;
  double dVgst_dW, dVgst_dL;
  double ddVgsteff_dVg_dW, ddVgsteff_dVg_dL;
  // d->vgst
  {
    double Vgst = Vgs_eff - d->von;
    //double Vgst = d->vgst;
    dVgst_dW = dVgs_eff_dW - dVon_dW;
    dVgst_dL = dVgs_eff_dL - dVon_dL;
    double T10 = 2.0 * n * t->vtm;
    double dT10_dW = 2. * dn_dW;
    double dT10_dL = 2. * dn_dL;
    double VgstNVt = Vgst / T10;
    double dVgstNVt_dW = dVgst_dW / T10 - Vgst / T10 / T10 * dT10_dW;
    double dVgstNVt_dL = dVgst_dL / T10 - Vgst / T10 / T10 * dT10_dL;
    double ExpArg = (2.0 * s->voff - Vgst) / T10;
    double dExpArg_dW = (2. * m->voff.dW(L,W,par_scope) - dVgst_dW) / T10
                      - (2. * s->voff - Vgst) / T10 / T10 * dT10_dW;
    double dExpArg_dL = (2. * m->voff.dL(L,W,par_scope) - dVgst_dL) / T10
                      - (2. * s->voff - Vgst) / T10 / T10 * dT10_dL;
    trace4("", Vgst, T10, VgstNVt, ExpArg);

    /* MCJ: Very small Vgst */
    if (VgstNVt > EXP_THRESHOLD) { incomplete();
      // unrechable?
      // d->vgst = Vgst;
      dVgsteff_dVg = dVgs_eff_dVg;
      ddVgsteff_dVg_dW = ddVgs_eff_dVg_dW;
      ddVgsteff_dVg_dL = ddVgs_eff_dVg_dL;
      dVgsteff_dVd = -dVth_dVd;
      dVgsteff_dVb = -dVth_dVb;
      trace4(">>", d->vgst, dVgsteff_dVg, dVgsteff_dVd, dVgsteff_dVb);
    }else if (ExpArg > EXP_THRESHOLD) { incomplete();
      double T0 = (Vgst - s->voff) / (n * t->vtm);
      // double ExpVgst = exp(T0);
      // d->vgst = t->vtm * t->cdep0 / m->cox * ExpVgst;
      dVgsteff_dVg = d->vgst / (n * t->vtm);
      ddVgsteff_dVg_dW = dVgst_dW / (n * t->vtm)
	               +  d->vgst / t->vtm / n / n * dn_dW;
      ddVgsteff_dVg_dL = dVgst_dL / (n * t->vtm)
	               +  d->vgst / t->vtm / n / n * dn_dL;
      dVgsteff_dVd = -dVgsteff_dVg * (dVth_dVd + T0 * t->vtm * dn_dVd);
      dVgsteff_dVb = -dVgsteff_dVg * (dVth_dVb + T0 * t->vtm * dn_dVb);
      ddVgsteff_dVg_dW = ddVgsteff_dVg_dW * dVgs_eff_dVg
	               + dVgsteff_dVg * ddVgs_eff_dVg_dW;
      ddVgsteff_dVg_dL = ddVgsteff_dVg_dL * dVgs_eff_dVg
	               + dVgsteff_dVg * ddVgs_eff_dVg_dL;
      dVgsteff_dVg *= dVgs_eff_dVg;
      trace4(">", d->vgst, dVgsteff_dVg, dVgsteff_dVd, dVgsteff_dVb);
    }else{
      double ExpVgst = exp(VgstNVt);
      double dExpVgst_dW = exp(VgstNVt) * dVgstNVt_dW;
      double dExpVgst_dL = exp(VgstNVt) * dVgstNVt_dL;
      double T1 = T10 * log(1.0 + ExpVgst);
      double dT1_dW = dT10_dW * log(1.0 + ExpVgst)
	            + T10 * 1./(1.+ExpVgst) * dExpVgst_dW;
      double dT1_dL = dT10_dL * log(1.0 + ExpVgst)
	            + T10 * 1./(1.+ExpVgst) * dExpVgst_dL;
      double dT1_dVg = ExpVgst / (1.0 + ExpVgst);
      double ddT1_dVg_dW = dExpVgst_dW / (1.0 + ExpVgst)
	                 - ExpVgst / (1.0 + ExpVgst)/ (1.0 + ExpVgst) * dExpVgst_dW;
      double ddT1_dVg_dL = dExpVgst_dL / (1.0 + ExpVgst)
	                 - ExpVgst / (1.0 + ExpVgst)/ (1.0 + ExpVgst) * dExpVgst_dL;
      double dT1_dVb = -dT1_dVg * (dVth_dVb + Vgst / n * dn_dVb)
	+ T1 / n * dn_dVb;
      double dT1_dVd = -dT1_dVg * (dVth_dVd + Vgst / n * dn_dVd)
	+ T1 / n * dn_dVd;

      double dT2_dVg = -m->cox / (t->vtm * t->cdep0) * exp(ExpArg);
      double ddT2_dVg_dW = dT2_dVg * dExpArg_dW;
      double ddT2_dVg_dL = dT2_dVg * dExpArg_dL;
      double T2 = 1.0 - T10 * dT2_dVg;
      double dT2_dW = - dT10_dW * dT2_dVg - T10 * ddT2_dVg_dW;
      double dT2_dL = - dT10_dL * dT2_dVg - T10 * ddT2_dVg_dL;
      double dT2_dVd = -dT2_dVg * (dVth_dVd - 2.0 * t->vtm * ExpArg * dn_dVd)
	+ (T2 - 1.0) / n * dn_dVd;
      double dT2_dVb = -dT2_dVg * (dVth_dVb - 2.0 * t->vtm * ExpArg * dn_dVb)
	+ (T2 - 1.0) / n * dn_dVb;

      // d->vgst = T1 / T2;
      double T3 = T2 * T2;
      double dT3_dW = 2. * T2 * dT2_dW;
      double dT3_dL = 2. * T2 * dT2_dL;
      dVgsteff_dVg = (T2 * dT1_dVg - T1 * dT2_dVg) / T3 * dVgs_eff_dVg;
      ddVgsteff_dVg_dW = ( dT2_dW * dT1_dVg + T2 * ddT1_dVg_dW
	                  - dT1_dW * dT2_dVg - T1 * ddT2_dVg_dW )
	                 / T3 * dVgs_eff_dVg
	- (T2 * dT1_dVg - T1 * dT2_dVg) / T3 / T3 * dT3_dW * dVgs_eff_dVg
	+  (T2 * dT1_dVg - T1 * dT2_dVg) / T3 * ddVgs_eff_dVg_dW;
      ddVgsteff_dVg_dL = ( dT2_dL * dT1_dVg + T2 * ddT1_dVg_dL 
	                  - dT1_dL * dT2_dVg - T1 * ddT2_dVg_dL )
	                 / T3 * dVgs_eff_dVg
	- (T2 * dT1_dVg - T1 * dT2_dVg) / T3 / T3 * dT3_dL * dVgs_eff_dVg
	+  (T2 * dT1_dVg - T1 * dT2_dVg) / T3 * ddVgs_eff_dVg_dL;
      dVgsteff_dVd = (T2 * dT1_dVd - T1 * dT2_dVd) / T3;
      dVgsteff_dVb = (T2 * dT1_dVb - T1 * dT2_dVb) / T3;
      trace4("<", d->vgst, dVgsteff_dVg, dVgsteff_dVd, dVgsteff_dVb);
    }
    Vgst2Vtm = d->vgst + 2.0 * t->vtm;
    dVgst2Vtm_dW = dVgst_dW; // t->vtm is const
    dVgst2Vtm_dL = dVgst_dL; // t->vtm is const
    trace3("", d->vgst, t->vtm, Vgst2Vtm);
  }
  double Rds, dRds_dVg, dRds_dVb;
  double dRds_dW, dRds_dL;
  double ddRds_dVg_dW, ddRds_dVg_dL;
  {
    double T9 = sqrtPhis - t->sqrtPhi;
    double dT9_dW = dsqrtPhis_dW;
    double dT9_dL = dsqrtPhis_dL;
    double T0 = s->prwg * d->vgst + s->prwb * T9;
    double dT0_dW = m->prwg.dW(L, W, par_scope) * d->vgst
                  + s->prwg * dVgst_dW
                  + m->prwb.dW(L, W, par_scope) * T9
		  + s->prwb * dT9_dW;
    double dT0_dL = m->prwg.dL(L, W, par_scope) * d->vgst
                  + s->prwg * dVgst_dL
                  + m->prwb.dL(L, W, par_scope) * T9
		  + s->prwb * dT9_dL;
    if (T0 >= -0.9) {
      Rds = t->rds0 * (1.0 + T0);
      dRds_dW = t->drds0_dW * (1.0 + T0) + t->rds0 * dT0_dW;
      dRds_dL = t->drds0_dL * (1.0 + T0) + t->rds0 * dT0_dL;
      dRds_dVg = t->rds0 * s->prwg;
      ddRds_dVg_dW = t->drds0_dW * s->prwg + t->rds0 * m->prwg.dW(L,W,par_scope);
      ddRds_dVg_dL = t->drds0_dL * s->prwg + t->rds0 * m->prwg.dL(L,W,par_scope);
      dRds_dVb = t->rds0 * s->prwb * dsqrtPhis_dVb;
    }else{
      /* to avoid the discontinuity problem due to prwg and prwb*/
      double T1 = 1.0 / (17.0 + 20.0 * T0);
      double dT1_dW = - 1./(17.0 + 20.0 * T0) / (17.0 + 20.0 * T0) * dT0_dW;
      double dT1_dL = - 1./(17.0 + 20.0 * T0) / (17.0 + 20.0 * T0) * dT0_dL;
      Rds = t->rds0 * (0.8 + T0) * T1;
      dRds_dW = ( t->drds0_dW * (1.0 + T0) + t->rds0 * dT0_dW ) * T1
	      + t->rds0 * (0.8 + T0) * dT1_dW;
      dRds_dL = ( t->drds0_dL * (1.0 + T0) + t->rds0 * dT0_dL ) * T1
	      + t->rds0 * (0.8 + T0) * dT1_dL;
      dT1_dW = 2.*T1 * dT1_dW;
      dT1_dL = 2.*T1 * dT1_dL;
      T1 *= T1;
      dRds_dVg = t->rds0 * s->prwg * T1;
      ddRds_dVg_dW = t->drds0_dW * s->prwg * T1
	           + t->rds0 * m->prwg.dW(L,W,par_scope)* T1
		   + t->rds0 * s->prwg * dT1_dW;
      ddRds_dVg_dL = t->drds0_dL * s->prwg * T1
	           + t->rds0 * m->prwg.dL(L,W,par_scope)* T1
		   + t->rds0 * s->prwg * dT1_dL;
      dRds_dVb = t->rds0 * s->prwb * dsqrtPhis_dVb * T1;
      trace3("Rds fix", T9, T0, T1);
      trace3("Rds fix", Rds, dRds_dVg, dRds_dVb);
    }
    ////////// d->rds = Rds /* Noise Bugfix */
  }
  // - - - - - - - - - - - - - - - - - - - - - - - - -
  /* SENS: Calculate Abulk */
  double Abulk0, dAbulk0_dVb, dAbulk_dVg, Abulk, dAbulk_dVb;
  double dAbulk_dW, dAbulk_dL;
  double ddAbulk_dVg_dW, ddAbulk_dVg_dL;
  {
    double T1 = 0.5 * t->k1ox / sqrtPhis;
    double dT1_dW = 0; // BUG: k1ox is SDP (why?)
    double dT1_dL = 0; // BUG: k1ox is SDP (why?)
    double dT1_dVb = -T1 / sqrtPhis * dsqrtPhis_dVb;

    double T9 = sqrt(s->xj * Xdep);
    double dT9_dW = .5 / T9 * ( m->xj.dW(L, W, par_scope) * Xdep + s->xj * dXdep_dW );
    double dT9_dL = .5 / T9 * ( m->xj.dL(L, W, par_scope) * Xdep + s->xj * dXdep_dL );
    double tmp1 = s->leff + 2.0 * T9;
    double dtmp1_dW = 2. * dT9_dW;
    double dtmp1_dL = 1. + 2. * dT9_dL;
    double T5 = s->leff / tmp1; 
    double dT5_dW = - s->leff / tmp1 / tmp1 * dtmp1_dW;
    double dT5_dL = - s->leff / tmp1 / tmp1 * dtmp1_dL + 1. / tmp1;
    double tmp2 = s->a0 * T5;
    double dtmp2_dW =  m->a0.dW(L, W, par_scope) * T5 + s->a0 + dT5_dW;
    double dtmp2_dL =  m->a0.dL(L, W, par_scope) * T5 + s->a0 + dT5_dL;
    double tmp3 = s->weff + s->b1; 
    double dtmp3_dW = 1. + m->b1.dW(L, W, par_scope);
    double dtmp3_dL = m->b1.dL(L, W, par_scope);
    double tmp4 = s->b0 / tmp3;
    double dtmp4_dW = m->b0.dW(L, W, par_scope) / tmp3 + s->b0 / tmp3 / tmp3 * dtmp3_dW;
    double dtmp4_dL = m->b0.dL(L, W, par_scope) / tmp3 + s->b0 / tmp3 / tmp3 * dtmp3_dL;
    double T2 = tmp2 + tmp4;
    double dT2_dW = dtmp2_dW + dtmp4_dW;
    double dT2_dL = dtmp2_dL + dtmp4_dL;
    double dT2_dVb = -T9 / tmp1 / Xdep * dXdep_dVb;
    double T6 = T5 * T5;
    double dT6_dW = 2. * T5 * dT5_dW;
    double dT6_dL = 2. * T5 * dT5_dL;
    double T7 = T5 * T6;
    double dT7_dW = dT5_dW * T6 + T5 * dT6_dW;
    double dT7_dL = dT5_dL * T6 + T5 * dT6_dL;

    Abulk0 = 1.0 + T1 * T2; 
    double dAbulk0_dW = dT1_dW * T2 + T1 * dT2_dW;
    double dAbulk0_dL = dT1_dL * T2 + T1 * dT2_dL;
    dAbulk0_dVb = T1 * tmp2 * dT2_dVb + T2 * dT1_dVb;

    double T8 = s->ags * s->a0 * T7;
    double dT8_dW = m->ags.dW(L, W, par_scope) * s->a0 * T7
                  + s->ags * m->a0.dW(L, W, par_scope) * T7
                  + s->ags * s->a0 * dT7_dW;
    double dT8_dL = m->ags.dL(L, W, par_scope) * s->a0 * T7
                  + s->ags * m->a0.dL(L, W, par_scope) * T7
                  + s->ags * s->a0 * dT7_dL;
    dAbulk_dVg = -T1 * T8;
    ddAbulk_dVg_dW = -T1 * dT8_dW; // assuming const k1ox
    ddAbulk_dVg_dL = -T1 * dT8_dL; // assuming const k1ox
    Abulk = Abulk0 + dAbulk_dVg * d->vgst; 
    dAbulk_dW = dAbulk0_dW + ddAbulk_dVg_dW * d->vgst + dAbulk_dVg * dVgst_dW; 
    dAbulk_dL = dAbulk0_dL + ddAbulk_dVg_dL * d->vgst + dAbulk_dVg * dVgst_dL;
    dAbulk_dVb = dAbulk0_dVb - T8 * d->vgst * (dT1_dVb + 3.0 * T1 * dT2_dVb);

    trace2("1", Abulk0, dAbulk0_dVb);
    trace3("1", dAbulk_dVg, Abulk, dAbulk_dVb);

    if (Abulk0 < 0.1) {
      /* added to avoid the problems caused by Abulk0 */
      double t9 = 1.0 / (3.0 - 20.0 * Abulk0);
      Abulk0 = (0.2 - Abulk0) * t9;
      dAbulk0_dVb *= t9 * t9;
      trace2("2", Abulk0, dAbulk0_dVb);
    }
    if (Abulk < 0.1) {
      /* added to avoid the problems caused by Abulk */
      double t9 = 1.0 / (3.0 - 20.0 * Abulk);
      Abulk = (0.2 - Abulk) * t9;
      double T10 = t9 * t9;
      dAbulk_dVb *= T10;
      dAbulk_dVg *= T10;
      trace3("2", dAbulk_dVg, Abulk, dAbulk_dVb);
    }
    ////////// d->Abulk = Abulk

    double T0, dT0_dVb;
    {
      double t2 = s->keta * Vbseff;
      if (t2 >= -0.9) {
        T0 = 1.0 / (1.0 + t2);
        dT0_dVb = -s->keta * T0 * T0;
        trace3("", t2, T0, dT0_dVb);
      }else{
        /* added to avoid the problems caused by Keta */
        double t1 = 1.0 / (0.8 + t2);
        T0 = (17.0 + 20.0 * t2) * t1;
        dT0_dVb = -s->keta * t1 * t1;
        trace3("keta fix", t2, T0, dT0_dVb);
      }
    }
    dAbulk_dVg *= T0;
    dAbulk_dVb = dAbulk_dVb * T0 + Abulk * dT0_dVb;
    dAbulk0_dVb = dAbulk0_dVb * T0 + Abulk0 * dT0_dVb;
    Abulk *= T0;
    Abulk0 *= T0;
    ////////// d->AbovVgst2Vtm = Abulk / Vgst2Vtm
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  /* SENS: Mobility calculation */
  double ueff, dueff_dVg, dueff_dVd, dueff_dVb;
  double dueff_dW, dueff_dL;
  double ddueff_dVg_dW, ddueff_dVg_dL;
  {
    double Denomi, dDenomi_dVg;
    double dDenomi_dW, dDenomi_dL;
    double ddDenomi_dVg_dW, ddDenomi_dVg_dL;
    double dDenomi_dVd, dDenomi_dVb;
    {
      double T5;
      double dT5_dW, dT5_dL;
      if (m->mobMod == 1) {
        double T0 = d->vgst + d->von + d->von;
	double dT0_dW = dVgst_dW + 2. * dVon_dW;
	double dT0_dL = dVgst_dL + 2. * dVon_dL;
        double T2 = t->ua + t->uc * Vbseff;
        double dT2_dW = t->dua_dW + t->duc_dW * Vbseff + t->uc * dVbseff_dW;
        double dT2_dL = t->dua_dL + t->duc_dL * Vbseff + t->uc * dVbseff_dL;
        double T3 = T0 / m->tox;
        double dT3_dW = dT0_dW / m->tox;
        double dT3_dL = dT0_dL / m->tox;
        T5 = T3 * (T2 + t->ub * T3);
	dT5_dW = dT3_dW * (T2 + t->ub * T3) + T3 * (dT2_dW + t->dub_dW * T3 + t->ub * dT3_dW);
	dT5_dL = dT3_dL * (T2 + t->ub * T3) + T3 * (dT2_dL + t->dub_dL * T3 + t->ub * dT3_dL);
        dDenomi_dVg = (T2 + 2.0 * t->ub * T3) / m->tox;
	ddDenomi_dVg_dW = (dT2_dW + 2. * ( t->dub_dW * T3 + t->ub * dT3_dW ) )/m->tox;
	ddDenomi_dVg_dL = (dT2_dL + 2. * ( t->dub_dL * T3 + t->ub * dT3_dL ) )/m->tox;
        dDenomi_dVd = dDenomi_dVg * 2.0 * dVth_dVd;
        dDenomi_dVb = dDenomi_dVg * 2.0 * dVth_dVb + t->uc * T3;
      }else if (m->mobMod == 2) { incomplete();
        T5 = d->vgst / m->tox 
          * (t->ua + t->uc * Vbseff + t->ub * d->vgst / m->tox);
	dT5_dW = 0; incomplete();
	dT5_dL = 0; incomplete();
        dDenomi_dVg = (t->ua + t->uc * Vbseff + 2.0 * t->ub * d->vgst / m->tox)
          / m->tox;
        dDenomi_dVd = 0.0; incomplete();
        dDenomi_dVb = d->vgst * t->uc / m->tox; 
	ddDenomi_dVg_dW = ddDenomi_dVg_dL = 0; incomplete();
      }else{ incomplete();
        double T0 = d->vgst + d->von + d->von;
        double T2 = 1.0 + t->uc * Vbseff;
        double T3 = T0 / m->tox;
        double T4 = T3 * (t->ua + t->ub * T3);
        T5 = T4 * T2;
	dT5_dW = 0; incomplete();
	dT5_dL = 0; incomplete();
        dDenomi_dVg = (t->ua + 2.0 * t->ub * T3) * T2 / m->tox;
        dDenomi_dVd = dDenomi_dVg * 2.0 * dVth_dVd;
        dDenomi_dVb = dDenomi_dVg * 2.0 * dVth_dVb + t->uc * T4;
	ddDenomi_dVg_dW = ddDenomi_dVg_dL = 0; incomplete();
      }
      if (T5 >= -0.8) {
        Denomi = 1.0 + T5;
	dDenomi_dW = dT5_dW;
	dDenomi_dL = dT5_dL;
      }else{
        /* Added to avoid the discontinuity problem caused by ua and ub*/ 
        double T9 = 1.0 / (7.0 + 10.0 * T5);
        double dT9_dW = - .1 / (7.0 + 10.0 * T5) / (7.0 + 10.0 * T5) / dT5_dW;
        double dT9_dL = - .1 / (7.0 + 10.0 * T5) / (7.0 + 10.0 * T5) / dT5_dL;
        Denomi = (0.6 + T5) * T9;
	dDenomi_dW = dT5_dW * T9 + (0.6 + dT5_dW) * dT9_dW;
	dDenomi_dL = dT5_dL * T9 + (0.6 + dT5_dL) * dT9_dL;
        T9 *= T9;
        dDenomi_dVg *= T9;
 //       dDenomi_dVd *= T9;
 //       dDenomi_dVb *= T9;
      }
    }
    ueff = t->u0temp / Denomi;
    // constant t->u0temp (BUG?)
    dueff_dW = -ueff / Denomi * dDenomi_dW;
    dueff_dL = -ueff / Denomi * dDenomi_dL;
    double T9 = -ueff / Denomi;
    double dT9_dW = -dueff_dW / Denomi + ueff / Denomi / Denomi * dDenomi_dW;
    double dT9_dL = -dueff_dL / Denomi + ueff / Denomi / Denomi * dDenomi_dL;
    dueff_dVg = T9 * dDenomi_dVg;
    ddueff_dVg_dW = dT9_dW * dDenomi_dVg + T9 * ddDenomi_dVg_dW;
    ddueff_dVg_dL = dT9_dL * dDenomi_dVg + T9 * ddDenomi_dVg_dL;
    dueff_dVd = T9 * dDenomi_dVd;
    dueff_dVb = T9 * dDenomi_dVb;
  }
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  /* SENS: Calculate Effective Channel Geometry */
  double Weff, dWeff_dVg, dWeff_dVb;
  double dWeff_dW, dWeff_dL;
  double ddWeff_dVg_dW, ddWeff_dVg_dL;
  {
    double T9 = sqrtPhis - t->sqrtPhi;
    Weff = s->weff - 2.0 * (s->dwg * d->vgst + s->dwb * T9);
    dWeff_dW = 1. - 2. * ( m->dwg.dW(L,W,par_scope) * d->vgst
	                 + s->dwg * dVgst_dW
			 + m->dwb.dW(L,W,par_scope) * T9 );
    dWeff_dL = 1. - 2. * ( m->dwg.dL(L,W,par_scope) * d->vgst
	                 + s->dwg * dVgst_dL
			 + m->dwb.dL(L,W,par_scope) * T9 );
    dWeff_dVg = -2.0 * s->dwg;
    ddWeff_dVg_dW = -2.0 * m->dwg.dW(L,W,par_scope);
    ddWeff_dVg_dL = -2.0 * m->dwg.dL(L,W,par_scope);
    dWeff_dVb = -2.0 * s->dwb * dsqrtPhis_dVb;

    if (Weff < 2.0e-8) { incomplete();
      /* to avoid the discontinuity problem due to Weff*/
      double T0 = 1.0 / (6.0e-8 - 2.0 * Weff);
      Weff = 2.0e-8 * (4.0e-8 - Weff) * T0;
      T0 *= T0 * 4.0e-16;
      dWeff_dVg *= T0;
      dWeff_dVb *= T0;
      trace3("Weff fix", Weff, dWeff_dVg, dWeff_dVb);
    }
  }

  double Esat, EsatL, dEsatL_dVg, dEsatL_dVd, dEsatL_dVb;
  double dEsatL_dW = 0; // (formally incorrect, BUG?)
  double dEsatL_dL;
  double ddEsatL_dVg_dW, ddEsatL_dVg_dL;
  {
    Esat = 2.0 * t->vsattemp / ueff;
    EsatL = Esat * s->leff;
    dEsatL_dL = Esat;

    double T0 = -EsatL / ueff;
    double dT0_dW = - dEsatL_dW / ueff + EsatL / ueff / ueff * dueff_dW;
    double dT0_dL = - dEsatL_dL / ueff + EsatL / ueff / ueff * dueff_dL;
    dEsatL_dVg = T0 * dueff_dVg;
    ddEsatL_dVg_dW = dT0_dW * dueff_dVg + T0 * ddueff_dVg_dW;
    ddEsatL_dVg_dL = dT0_dL * dueff_dVg + T0 * ddueff_dVg_dL;
    dEsatL_dVd = T0 * dueff_dVd;
    dEsatL_dVb = T0 * dueff_dVb;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  /* SENS: Saturation Drain Voltage Vdsat */
  double Vdsat, dVdsat_dVg, dVdsat_dVd, dVdsat_dVb;
  double dVdsat_dW, dVdsat_dL;
  double ddVdsat_dVg_dW, ddVdsat_dVg_dL;
  double Vasat, dVasat_dVg, dVasat_dVb, dVasat_dVd;
  double dVasat_dW, dVasat_dL;
  double ddVasat_dVg_dW, ddVasat_dVg_dL;
  {
    double WVCoxRds;
    double dWVCoxRds_dW, dWVCoxRds_dL;
    {
      double dvsattemp_dW = 0; // BUG
      double dvsattemp_dL = 0; // BUG
      double WVCox = Weff * t->vsattemp * m->cox;
      double dWVCox_dW = dWeff_dW * t->vsattemp * m->cox
	               + Weff * dvsattemp_dW * m->cox;
      double dWVCox_dL = dWeff_dL * t->vsattemp * m->cox
	               + Weff * dvsattemp_dL * m->cox;
      WVCoxRds = WVCox * Rds;
      dWVCoxRds_dW = dWVCox_dW * Rds + WVCox * dRds_dW;
      dWVCoxRds_dL = dWVCox_dL * Rds + WVCox * dRds_dL;
    }
    trace1("", WVCoxRds);

    double Lambda, dLambda_dVg;
    double dLambda_dW, dLambda_dL;
    double ddLambda_dVg_dW, ddLambda_dVg_dL;
    {
      if (s->a1 == 0.0) {
	Lambda = s->a2;
	dLambda_dW = m->a2.dW(L,W,par_scope);
	dLambda_dL = m->a2.dL(L,W,par_scope);
	dLambda_dVg = 0.0;
	ddLambda_dVg_dW = ddLambda_dVg_dL = 0;
      }else if (s->a1 > 0.0) {
	/* avoid discontinuity problem caused by s->a1 and s->a2 (Lambda) */
	double T0 = 1.0 - s->a2;
	double dT0_dW = - m->a2.dW(L,W,par_scope);
	double dT0_dL = - m->a2.dL(L,W,par_scope);
	double T1 = T0 - s->a1 * d->vgst - 0.0001;
	double dT1_dW = dT0_dW - m->a1.dW(L,W,par_scope) * d->vgst - s->a1 * dVgst_dW;
	double dT1_dL = dT0_dL - m->a1.dL(L,W,par_scope) * d->vgst - s->a1 * dVgst_dL;
	double T2 = sqrt(T1 * T1 + 0.0004 * T0);
	double dT2_dW = .5 / T2 * ( 2. * T1 * dT1_dW + 0.0004 * dT0_dW );
	double dT2_dL = .5 / T2 * ( 2. * T1 * dT1_dL + 0.0004 * dT0_dL );
	Lambda = 1. - .5 * (T1 + T2);
	dLambda_dW = - 0.5 * ( dT1_dW + dT2_dW );
	dLambda_dL = - 0.5 * ( dT1_dL + dT2_dL );
	dLambda_dVg = 0.5 * s->a1 * (1.0 + T1 / T2);
	ddLambda_dVg_dW = 0.5 * ( m->a1.dW(L,W,par_scope) *  (1.0 + T1 / T2)
	                       + s->a1 * (dT1_dW / T2 - T1 / T2 /T2 * dT2_dW ) );
	ddLambda_dVg_dL = 0.5 * ( m->a1.dL(L,W,par_scope) *  (1.0 + T1 / T2)
	                       + s->a1 * (dT1_dL / T2 - T1 / T2 /T2 * dT2_dL ) );
      }else{
	double T1 = s->a2 + s->a1 * d->vgst - 0.0001;
	double dT1_dW = m->a2.dW(L,W,par_scope) + m->a1.dW(L,W,par_scope) * d->vgst - s->a1 * dVgst_dW;
	double dT1_dL = m->a2.dL(L,W,par_scope) + m->a1.dL(L,W,par_scope) * d->vgst - s->a1 * dVgst_dL;
	double T2 = sqrt(T1 * T1 + 0.0004 * s->a2);
	double dT2_dW = .5 / sqrt(T1 * T1 + 0.0004 * s->a2)
	  * ( 2. * T1 * dT1_dW + 0.0004 * m->a2.dW(L,W,par_scope) );
	double dT2_dL = .5 / sqrt(T1 * T1 + 0.0004 * s->a2)
	  * ( 2. * T1 * dT1_dL + 0.0004 * m->a2.dL(L,W,par_scope) );
	Lambda = 0.5 * (T1 + T2);
	dLambda_dW = .5 * ( dT1_dW + dT2_dW );
	dLambda_dL = .5 * ( dT1_dL + dT2_dL );
	dLambda_dVg = 0.5 * s->a1 * (1.0 + T1 / T2);
	ddLambda_dVg_dW = 0.5 * ( m->a1.dW(L,W,par_scope) *  (1.0 + T1 / T2)
	                       + s->a1 * (dT1_dW / T2 - T1 / T2 /T2 * dT2_dW ) );
	ddLambda_dVg_dL = 0.5 * ( m->a1.dL(L,W,par_scope) *  (1.0 + T1 / T2)
	                       + s->a1 * (dT1_dL / T2 - T1 / T2 /T2 * dT2_dL ) );
      }
    }
    trace2("", Lambda, dLambda_dVg);

    double tmp2, tmp3;
    double dtmp2_dW, dtmp2_dL;
    if (Rds > 0) {
      tmp2 = dRds_dVg / Rds + dWeff_dVg / Weff;
      dtmp2_dW = ddRds_dVg_dW / Rds - dRds_dVg / Rds / Rds * dRds_dW
	       + ddWeff_dVg_dW / Weff - dWeff_dVg / Weff / Weff * dWeff_dW;
      dtmp2_dL = ddRds_dVg_dL / Rds - dRds_dVg / Rds / Rds * dRds_dL
	       + ddWeff_dVg_dL / Weff - dWeff_dVg / Weff / Weff * dWeff_dL;
      tmp3 = dRds_dVb / Rds + dWeff_dVb / Weff;
    }else{
      tmp2 = dWeff_dVg / Weff;
      dtmp2_dW = ddWeff_dVg_dW / Weff - dWeff_dVg / Weff / Weff * dWeff_dW;
      dtmp2_dL = ddWeff_dVg_dL / Weff - dWeff_dVg / Weff / Weff * dWeff_dL;
      tmp3 = dWeff_dVb / Weff;
    }
    trace2("", tmp2, tmp3);
    // SENS
    //double Vdsat, dVdsat_dVg, dVdsat_dVd, dVdsat_dVb; // d->vdsat
    double tmp1;
    double dtmp1_dW, dtmp1_dL;
    {
      if ((Rds == 0.0) && (Lambda == 1.0)) {
	double T0 = 1.0 / (Abulk * EsatL + Vgst2Vtm);
	double dT0_dL = - 1.0 / (Abulk * EsatL + Vgst2Vtm) / (Abulk * EsatL + Vgst2Vtm) * ( dAbulk_dL * EsatL + Abulk * dEsatL_dL + dVgst2Vtm_dL );
	double dT0_dW = - 1.0 / (Abulk * EsatL + Vgst2Vtm) / (Abulk * EsatL + Vgst2Vtm) * ( dAbulk_dW * EsatL + Abulk * dEsatL_dW + dVgst2Vtm_dW );
	tmp1 = 0.0;
	dtmp1_dW = dtmp1_dL = 0.;
	double T1 = T0 * T0;
	double dT1_dW = 2.*T0 * dT0_dW;
	double dT1_dL = 2.*T0 * dT0_dL;
	double T2 = Vgst2Vtm * T0;
	double dT2_dW = dVgst2Vtm_dW * T0 + Vgst2Vtm * dT0_dW;
	double dT2_dL = dVgst2Vtm_dL * T0 + Vgst2Vtm * dT0_dL;
	double T3 = EsatL * Vgst2Vtm;
	double dT3_dW = dEsatL_dW * Vgst2Vtm + EsatL * dVgst2Vtm_dW;
	double dT3_dL = dEsatL_dL * Vgst2Vtm + EsatL * dVgst2Vtm_dL;
	Vdsat = T3 * T0;
	// Vdsat = d->vdsat; ?
	dVdsat_dW = dT3_dW * T0 + T3 * dT0_dW;
	dVdsat_dL = dT3_dL * T0 + T3 * dT0_dL;
	double dT0_dVg = -(Abulk * dEsatL_dVg + EsatL * dAbulk_dVg + 1.0)*T1;
	double ddT0_dVg_dW = - ( dAbulk_dW * dEsatL_dVg + Abulk * ddEsatL_dVg_dW
	                       + dEsatL_dW * dAbulk_dVg + EsatL * ddAbulk_dVg_dW)*T1
                             -(Abulk * dEsatL_dVg + EsatL * dAbulk_dVg + 1.0)*dT1_dW;
	double ddT0_dVg_dL = - ( dAbulk_dL * dEsatL_dVg + Abulk * ddEsatL_dVg_dL
	                       + dEsatL_dL * dAbulk_dVg + EsatL * ddAbulk_dVg_dL)*T1
                             -(Abulk * dEsatL_dVg + EsatL * dAbulk_dVg + 1.0)*dT1_dL;
	double dT0_dVd = -(Abulk * dEsatL_dVd) * T1;
	double dT0_dVb = -(Abulk * dEsatL_dVb + dAbulk_dVb * EsatL) * T1;
	dVdsat_dVg = T3 * dT0_dVg + T2 * dEsatL_dVg + EsatL * T0;
	ddVdsat_dVg_dW = dT3_dW * dT0_dVg + T3 * ddT0_dVg_dW
		       + dT2_dW * dEsatL_dVg + T2 * ddEsatL_dVg_dW
		       + dEsatL_dW * T0 + EsatL * dT0_dW;
	ddVdsat_dVg_dL = dT3_dL * dT0_dVg + T3 * ddT0_dVg_dL
		       + dT2_dL * dEsatL_dVg + T2 * ddEsatL_dVg_dL
		       + dEsatL_dL * T0 + EsatL * dT0_dL;
	dVdsat_dVd = T3 * dT0_dVd + T2 * dEsatL_dVd;
	dVdsat_dVb = T3 * dT0_dVb + T2 * dEsatL_dVb;
      }else{
	tmp1 = dLambda_dVg / (Lambda * Lambda);
	dtmp1_dW = ddLambda_dVg_dW / (Lambda * Lambda)
	         - dLambda_dVg / (Lambda * Lambda) / (Lambda * Lambda) * 2.*Lambda * dLambda_dW;
	dtmp1_dL = ddLambda_dVg_dL / (Lambda * Lambda)
	         - dLambda_dVg / (Lambda * Lambda) / (Lambda * Lambda) * 2.*Lambda * dLambda_dL;
	double T9 = Abulk * WVCoxRds;
	double dT9_dW = dAbulk_dW * WVCoxRds + Abulk * dWVCoxRds_dW;
	double dT9_dL = dAbulk_dL * WVCoxRds + Abulk * dWVCoxRds_dL;
	double T8 = Abulk * T9;
	double dT8_dW = dAbulk_dW * T9 + Abulk * dT9_dW;
	double dT8_dL = dAbulk_dL * T9 + Abulk * dT9_dL;
	double T7 = Vgst2Vtm * T9;
	double dT7_dW = dVgst2Vtm_dW * T9 + Vgst2Vtm * dT9_dW;
	double dT7_dL = dVgst2Vtm_dL * T9 + Vgst2Vtm * dT9_dL;
	double T6 = Vgst2Vtm * WVCoxRds;
	double dT6_dW = dVgst2Vtm_dW * WVCoxRds + Vgst2Vtm * dWVCoxRds_dW;
	double dT6_dL = dVgst2Vtm_dL * WVCoxRds + Vgst2Vtm * dWVCoxRds_dL;
	double T0 = 2.0 * Abulk * (T9 - 1.0 + 1.0 / Lambda);  // 2.0 * Abulk * T9
	double dT0_dW = 2. * ( dAbulk_dW * (T9 - 1.0 + 1.0 / Lambda)
	                     + Abulk * (dT9_dW - 1.0 / Lambda / Lambda * dLambda_dW) );
	double dT0_dL = 2. * ( dAbulk_dL * (T9 - 1.0 + 1.0 / Lambda)
	                     + Abulk * (dT9_dL - 1.0 / Lambda / Lambda * dLambda_dL) );
	double dT0_dVg = 2.0 * (T8 * tmp2 - Abulk * tmp1
	    + (2.0 * T9 + 1.0 / Lambda - 1.0) * dAbulk_dVg);
	double ddT0_dVg_dW = 2.0 * ( dT8_dW * tmp2 + T8 * dtmp2_dW
	                           - dAbulk_dW * tmp1 - Abulk * dtmp1_dW
	    + (2.0 * dT9_dW - 1.0 / Lambda / Lambda * dLambda_dW) * dAbulk_dVg
	    + (2.0 * T9 + 1.0 / Lambda - 1.0) * ddAbulk_dVg_dW);
	double ddT0_dVg_dL = 2.0 * ( dT8_dL * tmp2 + T8 * dtmp2_dL
	                           - dAbulk_dL * tmp1 - Abulk * dtmp1_dL
	    + (2.0 * dT9_dL - 1.0 / Lambda / Lambda * dLambda_dL) * dAbulk_dVg
	    + (2.0 * T9 + 1.0 / Lambda - 1.0) * ddAbulk_dVg_dL);
	double dT0_dVb = 2.0 * (T8 * (2.0 / Abulk * dAbulk_dVb + tmp3)
	    + (1.0 / Lambda - 1.0) * dAbulk_dVb);
	//double dT0_dVd = 0.0;

	double T1 = Vgst2Vtm * (2.0 / Lambda - 1.0) + Abulk * EsatL + 3.0*T7;
	double dT1_dW = dVgst2Vtm_dW * (2.0 / Lambda - 1.0)
                      - Vgst2Vtm * 2.0 / Lambda / Lambda * dLambda_dW
	              + dAbulk_dW * EsatL + Abulk * dEsatL_dW
		      + 3.0 * dT7_dW;
	double dT1_dL = dVgst2Vtm_dL * (2.0 / Lambda - 1.0)
                      - Vgst2Vtm * 2.0 / Lambda / Lambda * dLambda_dL
	              + dAbulk_dL * EsatL + Abulk * dEsatL_dL
		      + 3.0 * dT7_dW;
	double dT1_dVg = (2.0 / Lambda - 1.0) - 2.0 * Vgst2Vtm * tmp1
	  + Abulk * dEsatL_dVg + EsatL * dAbulk_dVg
	  + 3.0 * (T9 + T7 * tmp2 + T6 * dAbulk_dVg);
	double ddT1_dVg_dW = 2.0 / Lambda / Lambda * dLambda_dW
	                   - dVgst2Vtm_dW * tmp1 - Vgst2Vtm * dtmp1_dW
	                   + dAbulk_dW * dEsatL_dVg + Abulk * ddEsatL_dVg_dW
	                   + dEsatL_dW * dAbulk_dVg + EsatL * ddAbulk_dVg_dW
	                   + 3.0 * (dT9_dW + dT7_dW * tmp2 + T7 * dtmp2_dW
	                         + dT6_dW * dAbulk_dVg + T6 * ddAbulk_dVg_dW);
	double ddT1_dVg_dL = 2.0 / Lambda / Lambda * dLambda_dL
	                   - dVgst2Vtm_dL * tmp1 - Vgst2Vtm * dtmp1_dL
	                   + dAbulk_dL * dEsatL_dVg + Abulk * ddEsatL_dVg_dL
	                   + dEsatL_dL * dAbulk_dVg + EsatL * ddAbulk_dVg_dL
	                   + 3.0 * (dT9_dL + dT7_dL * tmp2 + T7 * dtmp2_dL
	                         + dT6_dL * dAbulk_dVg + T6 * ddAbulk_dVg_dL);

	double dT1_dVb = Abulk * dEsatL_dVb + EsatL * dAbulk_dVb
	  + 3.0 * (T6 * dAbulk_dVb + T7 * tmp3);
	double dT1_dVd = Abulk * dEsatL_dVd;

	double T2 = Vgst2Vtm * (EsatL + 2.0 * T6);
	double dT2_dW = dVgst2Vtm_dW * (EsatL + 2.0 * T6)
	              + Vgst2Vtm * (dEsatL_dW + 2.0 * dT6_dW);
	double dT2_dL = dVgst2Vtm_dL * (EsatL + 2.0 * T6)
	              + Vgst2Vtm * (dEsatL_dL + 2.0 * dT6_dL);
	double dT2_dVg = EsatL + Vgst2Vtm * dEsatL_dVg
	               + T6 * (4.0 + 2.0 * Vgst2Vtm * tmp2);
	double ddT2_dVg_dW = dEsatL_dW + dVgst2Vtm_dW * dEsatL_dVg + Vgst2Vtm * ddEsatL_dVg_dW
			   + dT6_dW * (4.0 + 2.0 * Vgst2Vtm * tmp2)
			   + T6 * 2.0 * ( dVgst2Vtm_dW * tmp2 + Vgst2Vtm * dtmp2_dW );
	double ddT2_dVg_dL = dEsatL_dL + dVgst2Vtm_dL * dEsatL_dVg + Vgst2Vtm * ddEsatL_dVg_dL
			   + dT6_dL * (4.0 + 2.0 * Vgst2Vtm * tmp2)
			   + T6 * 2.0 * ( dVgst2Vtm_dL * tmp2 + Vgst2Vtm * dtmp2_dL );
	double dT2_dVb = Vgst2Vtm * (dEsatL_dVb + 2.0 * T6 * tmp3);
	double dT2_dVd = Vgst2Vtm * dEsatL_dVd;

	double T3 = sqrt(T1 * T1 - 2.0 * T0 * T2);
	double dT3_dW = .5 / sqrt(T1 * T1 - 2.0 * T0 * T2)
	              * ( 2.0 * T1 * dT1_dW - 2. * ( dT0_dW * T2 + T0 * dT2_dW) );
	double dT3_dL = .5 / sqrt(T1 * T1 - 2.0 * T0 * T2)
	              * ( 2.0 * T1 * dT1_dL - 2. * ( dT0_dL * T2 + T0 * dT2_dL) );
	Vdsat = (T1 - T3) / T0;
	dVdsat_dW = (dT1_dW - dT3_dW) / T0 - Vdsat / T0 * dT0_dW;
	dVdsat_dL = (dT1_dL - dT3_dL) / T0 - Vdsat / T0 * dT0_dL;
	dVdsat_dVg = (dT1_dVg - (T1 * dT1_dVg - dT0_dVg * T2
	      - T0 * dT2_dVg) / T3 - Vdsat * dT0_dVg) / T0;
	ddVdsat_dVg_dW = ( ddT1_dVg_dW
	    - ( dT1_dW * dT1_dVg + T1 * ddT1_dVg_dW
	      - ddT0_dVg_dW * T2 - dT0_dVg * dT2_dW
	      - dT0_dW * dT2_dVg - T0 * ddT2_dVg_dW) / T3
	    + (T1 * dT1_dVg - dT0_dVg * T2 - T0 * dT2_dVg) / T3 / T3 * dT3_dW
	    - dVdsat_dW * dT0_dVg
	    - Vdsat * ddT0_dVg_dW) / T0
	      - dVdsat_dVg / T0 * dT0_dW;
	ddVdsat_dVg_dL = ( ddT1_dVg_dL
	    - ( dT1_dL * dT1_dVg + T1 * ddT1_dVg_dL
	      - ddT0_dVg_dL * T2 - dT0_dVg * dT2_dL
	      - dT0_dL * dT2_dVg - T0 * ddT2_dVg_dL) / T3
	    + (T1 * dT1_dVg - dT0_dVg * T2 - T0 * dT2_dVg) / T3 / T3 * dT3_dL
	    - dVdsat_dL * dT0_dVg
	    - Vdsat * ddT0_dVg_dL) / T0
	      - dVdsat_dVg / T0 * dT0_dL;
	dVdsat_dVb = (dT1_dVb - (T1 * dT1_dVb - dT0_dVb * T2
	      - T0 * dT2_dVb) / T3 - Vdsat * dT0_dVb) / T0;
	dVdsat_dVd = (dT1_dVd - (T1 * dT1_dVd - T0 * dT2_dVd) / T3) / T0;
      }
//      d->vdsat = Vdsat;
      assert( d->saturated == (d->vds >= d->vdsat) );
    }
    trace1("", tmp1);
    trace4("d->vdsat", Vdsat, dVdsat_dVg, dVdsat_dVd, dVdsat_dVb);

    /* Calculate VAsat */
    // double Vasat, dVasat_dVg, dVasat_dVb, dVasat_dVd;
    {
      double tmp4 = 1.0 - 0.5 * Abulk * Vdsat / Vgst2Vtm;
      double dtmp4_dW = - 0.5 * dAbulk_dW * Vdsat / Vgst2Vtm
                        - 0.5 * Abulk * dVdsat_dW / Vgst2Vtm
                        + 0.25 * Abulk * Vdsat / Vgst2Vtm / Vgst2Vtm * dVgst2Vtm_dW;
      double dtmp4_dL = - 0.5 * dAbulk_dL * Vdsat / Vgst2Vtm
                        - 0.5 * Abulk * dVdsat_dL / Vgst2Vtm
                        + 0.25 * Abulk * Vdsat / Vgst2Vtm / Vgst2Vtm * dVgst2Vtm_dL;
      double T9 = WVCoxRds * d->vgst;
      double dT9_dW = dWVCoxRds_dW * d->vgst + WVCoxRds * dVgst_dW;
      double dT9_dL = dWVCoxRds_dL * d->vgst + WVCoxRds * dVgst_dL;
      double T8 = T9 / Vgst2Vtm;
      double dT8_dW = dT9_dW / Vgst2Vtm - T9 / Vgst2Vtm / Vgst2Vtm * dVgst2Vtm_dW;
      double dT8_dL = dT9_dL / Vgst2Vtm - T9 / Vgst2Vtm / Vgst2Vtm * dVgst2Vtm_dL;
      double T0 = EsatL + Vdsat + 2.0 * T9 * tmp4;
      double dT0_dW = dEsatL_dW + dVdsat_dW + 2. * (dT9_dW * tmp4 + T9 * dtmp4_dW);
      double dT0_dL = dEsatL_dL + dVdsat_dL + 2. * (dT9_dL * tmp4 + T9 * dtmp4_dL);
      double T7 = 2.0 * WVCoxRds * tmp4;
      double dT7_dW = 2.0 * ( dWVCoxRds_dW * tmp4 + WVCoxRds * dtmp4_dW );
      double dT7_dL = 2.0 * ( dWVCoxRds_dL * tmp4 + WVCoxRds * dtmp4_dL );
      double dT0_dVg = dEsatL_dVg + dVdsat_dVg + T7 * (1.0 + tmp2 * d->vgst)
	- T8 * (Abulk * dVdsat_dVg - Abulk * Vdsat / Vgst2Vtm
	    + Vdsat * dAbulk_dVg);
      double ddT0_dVg_dW = ddEsatL_dVg_dW + ddVdsat_dVg_dW
	                 + dT7_dW * (1.0 + tmp2 * d->vgst)
			 + T7 * ( dtmp2_dW * d->vgst + tmp2 * dVgst_dW )
	- dT8_dW * (Abulk * dVdsat_dVg - Abulk * Vdsat / Vgst2Vtm
	    + Vdsat * dAbulk_dVg)
	- T8 * (dAbulk_dW * dVdsat_dVg + Abulk * ddVdsat_dVg_dW
	    - dAbulk_dW * Vdsat / Vgst2Vtm - Abulk * dVdsat_dW / Vgst2Vtm
	     + Abulk * Vdsat / Vgst2Vtm / Vgst2Vtm * dVgst2Vtm_dW
	    + dVdsat_dW * dAbulk_dVg + Vdsat * ddAbulk_dVg_dW);
      double ddT0_dVg_dL = ddEsatL_dVg_dL + ddVdsat_dVg_dL
	                 + dT7_dL * (1.0 + tmp2 * d->vgst)
			 + T7 * ( dtmp2_dL * d->vgst + tmp2 * dVgst_dL )
	- dT8_dL * (Abulk * dVdsat_dVg - Abulk * Vdsat / Vgst2Vtm
	    + Vdsat * dAbulk_dVg)
	- T8 * (dAbulk_dL * dVdsat_dVg + Abulk * ddVdsat_dVg_dL
	    - dAbulk_dL * Vdsat / Vgst2Vtm - Abulk * dVdsat_dL / Vgst2Vtm
	     + Abulk * Vdsat / Vgst2Vtm / Vgst2Vtm * dVgst2Vtm_dL
	    + dVdsat_dL * dAbulk_dVg + Vdsat * ddAbulk_dVg_dL);

      double dT0_dVb = dEsatL_dVb + dVdsat_dVb + T7 * tmp3 * d->vgst
	- T8 * (dAbulk_dVb * Vdsat + Abulk * dVdsat_dVb);
      double dT0_dVd = dEsatL_dVd + dVdsat_dVd - T8 * Abulk * dVdsat_dVd;
      T9 = WVCoxRds * Abulk;
      double T1 = 2.0 / Lambda - 1.0 + T9;
      double dT1_dW = - 2.0 / Lambda / Lambda * dLambda_dW + dT9_dW;
      double dT1_dL = - 2.0 / Lambda / Lambda * dLambda_dL + dT9_dL;
      double dT1_dVg = -2.0 * tmp1 +  WVCoxRds * (Abulk * tmp2 + dAbulk_dVg);
      double ddT1_dVg_dW = -2.0 * dtmp1_dW
	+ dWVCoxRds_dW * (Abulk * tmp2 + dAbulk_dVg)
	+ WVCoxRds * (dAbulk_dW * tmp2 + Abulk * dtmp2_dW + ddAbulk_dVg_dW);
      double ddT1_dVg_dL = -2.0 * dtmp1_dL
	+ dWVCoxRds_dL * (Abulk * tmp2 + dAbulk_dVg)
	+ WVCoxRds * (dAbulk_dL * tmp2 + Abulk * dtmp2_dL + ddAbulk_dVg_dL);
      double dT1_dVb = dAbulk_dVb * WVCoxRds + T9 * tmp3;
      Vasat = T0 / T1;
      assert(is_number(Vasat));
      dVasat_dW = dT0_dW / T1 - Vasat / T1 * dT1_dW;
      assert(is_number(dVasat_dW));
      dVasat_dL = dT0_dL / T1 - T0 / T1 / T1 * dT1_dL;
      dVasat_dVg = (dT0_dVg - Vasat * dT1_dVg) / T1;
      ddVasat_dVg_dW = (ddT0_dVg_dW - dVasat_dW * dT1_dVg - Vasat * ddT1_dVg_dW) / T1
	             - (dT0_dVg - Vasat * dT1_dVg) / T1 / T1 * dT1_dW;
      ddVasat_dVg_dL = (ddT0_dVg_dL - dVasat_dL * dT1_dVg - Vasat * ddT1_dVg_dL) / T1
	             - (dT0_dVg - Vasat * dT1_dVg) / T1 / T1 * dT1_dL;
      dVasat_dVb = (dT0_dVb - Vasat * dT1_dVb) / T1;
      dVasat_dVd = dT0_dVd / T1;
    }
    trace4("", Vasat, dVasat_dVg, dVasat_dVb, dVasat_dVd);
  }
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  /* SENS -- Effective Vds (Vdseff) Calculation */
  double Vdseff, diffVds, dVdseff_dVg, dVdseff_dVd, dVdseff_dVb;
  double ddiffVds_dW, ddiffVds_dL;
  double dVdseff_dW, dVdseff_dL;
  double ddVdseff_dVg_dW, ddVdseff_dVg_dL;
  {
    double T1 = Vdsat - d->vds - s->delta;
    double dT1_dW = dVdsat_dW - m->delta.dW( L, W, par_scope);
    double dT1_dL = dVdsat_dL - m->delta.dL( L, W, par_scope);
    double dT1_dVg = dVdsat_dVg;
    double ddT1_dVg_dW = ddVdsat_dVg_dW;
    double ddT1_dVg_dL = ddVdsat_dVg_dL;
    double dT1_dVd = dVdsat_dVd - 1.0;
    double dT1_dVb = dVdsat_dVb;
    trace4("", T1, dT1_dVg, dT1_dVd, dT1_dVb);

    double Arg = T1 * T1 + 4.0 * s->delta * d->vdsat;
    double dArg_dW = 2.*T1 * dT1_dW + 4.0 * ( m->delta.dW(L, W, par_scope) * Vdsat + s->delta * dVdsat_dW );
    double dArg_dL = 2.*T1 * dT1_dL + 4.0 * ( m->delta.dL(L, W, par_scope) * Vdsat + s->delta * dVdsat_dL );
    double T2 = sqrt(Arg);
    double dT2_dW = .5 / T2 * dArg_dW;
    double dT2_dL = .5 / T2 * dArg_dL;
    double T0 = T1 / T2;
    double dT0_dW = dT1_dW / T2 - T1 / T2 / T2 * dT2_dW;
    double dT0_dL = dT1_dL / T2 - T1 / T2 / T2 * dT2_dL;
    double T3 = 2.0 * s->delta / T2;
    double dT3_dW = 2.0 * ( m->delta.dW(L,W,par_scope) / T2 - s->delta / T2 / T2 * dT2_dW );
    double dT3_dL = 2.0 * ( m->delta.dL(L,W,par_scope) / T2 - s->delta / T2 / T2 * dT2_dL );
    trace3("", T2, T0, T3);
    double dT2_dVg = T0 * dT1_dVg + T3 * dVdsat_dVg;
    double ddT2_dVg_dW = dT0_dW * dT1_dVg + T0 * ddT1_dVg_dW
                       + dT3_dW * dVdsat_dVg + T3 * ddVdsat_dVg_dW;
    double ddT2_dVg_dL = dT0_dL * dT1_dVg + T0 * ddT1_dVg_dL
                       + dT3_dL * dVdsat_dVg + T3 * ddVdsat_dVg_dL;
    double dT2_dVd = T0 * dT1_dVd + T3 * dVdsat_dVd;
    double dT2_dVb = T0 * dT1_dVb + T3 * dVdsat_dVb;
    trace3("", dT2_dVg, dT2_dVd, dT2_dVb);

    Vdseff      = Vdsat - 0.5 * (T1 + T2);
    dVdseff_dVg = dVdsat_dVg - 0.5 * (dT1_dVg + dT2_dVg);
    ddVdseff_dVg_dW = ddVdsat_dVg_dW - 0.5 * (ddT1_dVg_dW + ddT2_dVg_dW);
    ddVdseff_dVg_dL = ddVdsat_dVg_dL - 0.5 * (ddT1_dVg_dL + ddT2_dVg_dL);
    dVdseff_dVd = dVdsat_dVd - 0.5 * (dT1_dVd + dT2_dVd);
    dVdseff_dVb = dVdsat_dVb - 0.5 * (dT1_dVb + dT2_dVb);
    trace4("raw", Vdseff, dVdseff_dVg, dVdseff_dVd, dVdseff_dVb);

    // hmmm, recheck...
    dVdseff_dW = dVdsat_dW - 0.5 * (dT1_dW + dT2_dW);
    dVdseff_dL = dVdsat_dL - 0.5 * (dT1_dL + dT2_dL);

    fixzero(&Vdseff,      Vdsat);
    fixzero(&dVdseff_dVg, dVdsat_dVg);
    fixzero(&dVdseff_dVd, dVdsat_dVd);
    fixzero(&dVdseff_dVb, dVdsat_dVb);
    /* Added to eliminate non-zero Vdseff at Vds=0.0 */
    if (d->vds == 0.0) {
      assert(Vdseff == 0.0);
      assert(dVdseff_dVg == 0.0);
      assert(dVdseff_dVb == 0.0);
    }
    if (Vdseff > d->vds) {	// From Spice, to fix numeric problems.
      trace2("numeric problems", Vdseff, d->vds);
      Vdseff = d->vds;
      dVdseff_dW = 0;
      dVdseff_dL = 0;
      untested(); // weird
    }
    trace4("fixed", Vdseff, dVdseff_dVg, dVdseff_dVd, dVdseff_dVb);

    diffVds = d->vds - Vdseff;
    ddiffVds_dW = - dVdseff_dW;
    ddiffVds_dL = - dVdseff_dL;
    trace2("", Vdseff, diffVds);
    ////////// d->Vdseff = Vdseff;
  }

  double T0 = t->vfb + t->phi;
  if ((s->ngate > 1.e18) && (s->ngate < 1.e25) && (d->vgs > T0)) {
    incomplete();
  }

  trace3("", n, dn_dVb, dn_dVd);

  double dlitl_dW = 0; // ... xj (BUG?)
  double dlitl_dL = 0; // ... xj (BUG?)

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  /* SENS: Calculate Ids */
  double Idsa, dIdsa_dVg, dIdsa_dVd, dIdsa_dVb;
  double dIdsa_dW, dIdsa_dL;
  double ddIdsa_dVg_dW, ddIdsa_dVg_dL;
  {
    double Va, dVa_dVg, dVa_dVd, dVa_dVb;
    double dVa_dW, dVa_dL;
    double ddVa_dVg_dW, ddVa_dVg_dL;
    {
      /* SENS: Calculate VACLM */
      double VACLM, dVACLM_dVg, dVACLM_dVb, dVACLM_dVd;
      double dVACLM_dW, dVACLM_dL;
      double ddVACLM_dVg_dW, ddVACLM_dVg_dL;
      if ((s->pclm > 0.0) && (diffVds > 1.0e-10)) {
	double T0 = 1.0 / (s->pclm * Abulk * s->litl);
	double dT0_dW = - 1.0 / (s->pclm * Abulk * s->litl) / (s->pclm * Abulk * s->litl)
	              * ( m->pclm.dW(L,W,par_scope) * Abulk * s->litl
			+ s->pclm * dAbulk_dW * s->litl
			+ s->pclm * Abulk * dlitl_dW );
	double dT0_dL = - 1.0 / (s->pclm * Abulk * s->litl) / (s->pclm * Abulk * s->litl)
	              * ( m->pclm.dL(L,W,par_scope) * Abulk * s->litl
			+ s->pclm * dAbulk_dL * s->litl
			+ s->pclm * Abulk * dlitl_dL );
	double dT0_dVb = -T0 / Abulk * dAbulk_dVb;
	double dT0_dVg = -T0 / Abulk * dAbulk_dVg;
	double ddT0_dVg_dW = - dT0_dW / Abulk * dAbulk_dVg
	                   + T0 / Abulk  / Abulk * dAbulk_dW * dAbulk_dVg
			    -T0 / Abulk * ddAbulk_dVg_dW;
	double ddT0_dVg_dL = - dT0_dL / Abulk * dAbulk_dVg
	                   + T0 / Abulk  / Abulk * dAbulk_dL * dAbulk_dVg
			    -T0 / Abulk * ddAbulk_dVg_dL;
	double T2 = d->vgst / EsatL;
	double dT2_dW = dVgst_dW / EsatL - d->vgst / EsatL / EsatL * dEsatL_dW;
	double dT2_dL = dVgst_dL / EsatL - d->vgst / EsatL / EsatL * dEsatL_dL;
	double T1 = s->leff * (Abulk + T2);
	double dT1_dW = s->leff * (dAbulk_dW + dT2_dW);
	double dT1_dL = s->leff * (dAbulk_dL + dT2_dL) + (Abulk + T2);
	double dT1_dVg = s->leff * ((1.0-T2*dEsatL_dVg)/EsatL + dAbulk_dVg);
	double ddT1_dVg_dW = s->leff * (
	    ( dT2_dW*dEsatL_dVg + T2 * ddEsatL_dVg_dW)/EsatL
	    - (1.0-T2*dEsatL_dVg)/EsatL/EsatL * dEsatL_dW
	    + ddAbulk_dVg_dW);
	double ddT1_dVg_dL = ((1.0-T2*dEsatL_dVg)/EsatL + dAbulk_dVg)
	                   + s->leff * (
	    ( dT2_dL*dEsatL_dVg + T2 * ddEsatL_dVg_dL)/EsatL
	    - (1.0-T2*dEsatL_dVg)/EsatL/EsatL * dEsatL_dL
	    + ddAbulk_dVg_dL);
	double dT1_dVb = s->leff * (dAbulk_dVb - T2 * dEsatL_dVb / EsatL);
	double dT1_dVd = -T2 * dEsatL_dVd / Esat;
	double T9 = T0 * T1;
	double dT9_dW = dT0_dW * T1 + T0 * dT1_dW;
	double dT9_dL = dT0_dL * T1 + T0 * dT1_dL;
	VACLM = T9 * diffVds;
	dVACLM_dW = dT9_dW * diffVds + T9 * ddiffVds_dW;
	assert(is_number(dVACLM_dW));
	dVACLM_dL = dT9_dL * diffVds + T9 * ddiffVds_dL;
	dVACLM_dVg = T0 * dT1_dVg * diffVds - T9 * dVdseff_dVg
	  + T1 * diffVds * dT0_dVg;
	ddVACLM_dVg_dW = dT0_dW * dT1_dVg * diffVds
	               + T0 * ddT1_dVg_dW * diffVds
		       + T0 * dT1_dVg * ddiffVds_dW
		       - dT9_dW * dVdseff_dVg
		       - T9 * ddVdseff_dVg_dW
		       + dT1_dW * diffVds * dT0_dVg
		       + T1 * ddiffVds_dW * dT0_dVg
		       + T1 * diffVds * ddT0_dVg_dW;
	ddVACLM_dVg_dL = dT0_dL * dT1_dVg * diffVds
	               + T0 * ddT1_dVg_dL * diffVds
		       + T0 * dT1_dVg * ddiffVds_dL
		       - dT9_dL * dVdseff_dVg
		       - T9 * ddVdseff_dVg_dL
		       + dT1_dL * diffVds * dT0_dVg
		       + T1 * ddiffVds_dL * dT0_dVg
		       + T1 * diffVds * ddT0_dVg_dL;
	dVACLM_dVb = (dT0_dVb*T1 + T0*dT1_dVb) * diffVds - T9 * dVdseff_dVb;
	dVACLM_dVd = T0 * dT1_dVd * diffVds + T9 * (1.0 - dVdseff_dVd);
      }else{
	VACLM = MAX_EXP;
	dVACLM_dW = dVACLM_dL = 0.;
	dVACLM_dVd = dVACLM_dVg = dVACLM_dVb = 0.0;
	ddVACLM_dVg_dW = ddVACLM_dVg_dL = 0.;
      }
      trace4("", VACLM, dVACLM_dVg, dVACLM_dVb, dVACLM_dVd);

      /* Calculate VADIBL */
      double VADIBL, dVADIBL_dVg, dVADIBL_dVb, dVADIBL_dVd;
      double dVADIBL_dW, dVADIBL_dL;
      double ddVADIBL_dVg_dW, ddVADIBL_dVg_dL;
      if (t->thetaRout > 0.0) {
	double T8 = Abulk * Vdsat;
	double dT8_dW = dAbulk_dW * Vdsat + Abulk * dVdsat_dW;
	double dT8_dL = dAbulk_dL * Vdsat + Abulk * dVdsat_dL;
	double T0 = Vgst2Vtm * T8;
	double dT0_dW = dVgst2Vtm_dW * T8 + Vgst2Vtm * dT8_dW;
	double dT0_dL = dVgst2Vtm_dL * T8 + Vgst2Vtm * dT8_dL;
	double dT0_dVg = Vgst2Vtm * Abulk * dVdsat_dVg + T8
	  + Vgst2Vtm * Vdsat * dAbulk_dVg;
	double ddT0_dVg_dW = dVgst2Vtm_dW * Abulk * dVdsat_dVg
	                   + Vgst2Vtm * dAbulk_dW * dVdsat_dVg
	                   + Vgst2Vtm * Abulk * ddVdsat_dVg_dW
                           + dT8_dW
                           + dVgst2Vtm_dW * Vdsat * dAbulk_dVg
                           + Vgst2Vtm * dVdsat_dW * dAbulk_dVg
                           + Vgst2Vtm * Vdsat * ddAbulk_dVg_dW;
	double ddT0_dVg_dL = dVgst2Vtm_dL * Abulk * dVdsat_dVg
	                   + Vgst2Vtm * dAbulk_dL * dVdsat_dVg
	                   + Vgst2Vtm * Abulk * ddVdsat_dVg_dL
                           + dT8_dL
                           + dVgst2Vtm_dL * Vdsat * dAbulk_dVg
                           + Vgst2Vtm * dVdsat_dL * dAbulk_dVg
                           + Vgst2Vtm * Vdsat * ddAbulk_dVg_dL;
	double dT0_dVb = Vgst2Vtm * (dAbulk_dVb*Vdsat + Abulk*dVdsat_dVb);
	double dT0_dVd = Vgst2Vtm * Abulk * dVdsat_dVd;
	double T1 = Vgst2Vtm + T8;
	double dT1_dW = dVgst2Vtm_dW + dT8_dW;
	double dT1_dL = dVgst2Vtm_dL + dT8_dL;
	double dT1_dVg = 1.0 + Abulk * dVdsat_dVg + Vdsat * dAbulk_dVg;
	double ddT1_dVg_dW = dAbulk_dW * dVdsat_dVg + Abulk * ddVdsat_dVg_dW
	                   + dVdsat_dW * dAbulk_dVg + Vdsat * ddAbulk_dVg_dW;
	double ddT1_dVg_dL = dAbulk_dL * dVdsat_dVg + Abulk * ddVdsat_dVg_dL
	                   + dVdsat_dL * dAbulk_dVg + Vdsat * ddAbulk_dVg_dL;
	double dT1_dVb = Abulk * dVdsat_dVb + dAbulk_dVb * Vdsat;
	double dT1_dVd = Abulk * dVdsat_dVd;
	double T9 = T1 * T1;
	double dT9_dW = 2.*T1*dT1_dW;
	double dT9_dL = 2.*T1*dT1_dL;
	double T2 = t->thetaRout;
	double dT2_dW = t->dthetaRout_dW;
	double dT2_dL = t->dthetaRout_dL;
	VADIBL = (Vgst2Vtm - T0 / T1) / T2;
	dVADIBL_dW = ( (dVgst2Vtm_dW - dT0_dW / T1 + T0 / T1 / T1 * dT1_dW )
		     - VADIBL * dT2_dW ) / T2;
	assert(is_number(dVADIBL_dW));
	dVADIBL_dL = ( (dVgst2Vtm_dL - dT0_dL / T1 + T0 / T1 / T1 * dT1_dL )
		     - VADIBL * dT2_dL ) / T2;
	dVADIBL_dVg = (1.0 - dT0_dVg / T1 + T0 * dT1_dVg / T9) / T2;
	ddVADIBL_dVg_dW = ( - ddT0_dVg_dW / T1 + dT0_dVg / T1  / T1 * dT1_dW
	                      + dT0_dW * dT1_dVg / T9  + T0 * ddT1_dVg_dW / T9
	                     -  T0 * dT1_dVg / T9 / T9 * dT9_dW ) /T2
	                - (1.0 - dT0_dVg / T1 + T0 * dT1_dVg / T9) / T2 / T2 * dT2_dW;
	ddVADIBL_dVg_dL = ( - ddT0_dVg_dL / T1 + dT0_dVg / T1  / T1 * dT1_dL
	                      + dT0_dL * dT1_dVg / T9  + T0 * ddT1_dVg_dL / T9
	                     -  T0 * dT1_dVg / T9 / T9 * dT9_dL ) /T2
	                - (1.0 - dT0_dVg / T1 + T0 * dT1_dVg / T9) / T2 / T2 * dT2_dL;
	dVADIBL_dVb = (-dT0_dVb / T1 + T0 * dT1_dVb / T9) / T2;
	dVADIBL_dVd = (-dT0_dVd / T1 + T0 * dT1_dVd / T9) / T2;

	double T7 = s->pdiblb * Vbseff;
	double dT7_dW = m->pdiblb.dW(L,W,par_scope) * Vbseff + s->pdiblb * dVbseff_dW;
	double dT7_dL = m->pdiblb.dL(L,W,par_scope) * Vbseff + s->pdiblb * dVbseff_dL;
	double T3;
	double dT3_dW, dT3_dL;
	if (T7 >= -0.9) {
	  T3 = 1.0 / (1.0 + T7);
	  dT3_dW = - 1. / (1.0 + T7) / (1.0 + T7) * dT7_dW;
	  dT3_dL = - 1. / (1.0 + T7) / (1.0 + T7) * dT7_dL;
	  dVADIBL_dW = dVADIBL_dW * T3 + VADIBL * dT3_dW;
	  dVADIBL_dL = dVADIBL_dL * T3 + VADIBL * dT3_dL;
	  VADIBL *= T3;
	  ddVADIBL_dVg_dW = ddVADIBL_dVg_dW * T3 + dVADIBL_dVg * dT3_dW;
	  ddVADIBL_dVg_dL = ddVADIBL_dVg_dL * T3 + dVADIBL_dVg * dT3_dL;
	  dVADIBL_dVg *= T3;
	  dVADIBL_dVb = (dVADIBL_dVb - VADIBL * s->pdiblb) * T3;
	  dVADIBL_dVd *= T3;
	}else{
	  /* Added to avoid the discontinuity problem caused by pdiblcb */
	  double T4 = 1.0 / (0.8 + T7);
	  double dT4_dW = - 1.0 / (0.8 + T7) / (0.8 + T7) * dT7_dW;
	  double dT4_dL = - 1.0 / (0.8 + T7) / (0.8 + T7) * dT7_dL;
	  T3 = (17.0 + 20.0 * T7) * T4;
	  dT3_dW = 20. * dT7_dW + (17.0 + 20.0 * T7) * dT4_dW;
	  dT3_dL = 20. * dT7_dL + (17.0 + 20.0 * T7) * dT4_dL;
	  ddVADIBL_dVg_dW = ddVADIBL_dVg_dW * T3 + dVADIBL_dVg * dT3_dW;
	  ddVADIBL_dVg_dL = ddVADIBL_dVg_dL * T3 + dVADIBL_dVg * dT3_dL;
	  dVADIBL_dVg *= T3;
	  dVADIBL_dVb = dVADIBL_dVb * T3 - VADIBL * s->pdiblb * T4 * T4;
	  dVADIBL_dVd *= T3;
	  dVADIBL_dW = dVADIBL_dW * T3 + VADIBL * dT3_dW;
	  dVADIBL_dL = dVADIBL_dL * T3 + VADIBL * dT3_dL;
	  VADIBL *= T3;
	}
      }else{
	VADIBL = MAX_EXP;
	dVADIBL_dW = dVADIBL_dL = 0.;
	dVADIBL_dVd = dVADIBL_dVg = dVADIBL_dVb = 0.0;
	ddVADIBL_dVg_dW = ddVADIBL_dVg_dL = 0.;
      }
      trace4("", VADIBL, dVADIBL_dVg, dVADIBL_dVb, dVADIBL_dVd);

      /* Calculate VA */
      double T8 = s->pvag / EsatL;
      double dT8_dW = m->pvag.dW(L,W,par_scope) / EsatL - T8 / EsatL * dEsatL_dW;
      double dT8_dL = m->pvag.dL(L,W,par_scope) / EsatL - T8 / EsatL * dEsatL_dL;
      double T9 = T8 * d->vgst;
      double dT9_dW = dT8_dW * d->vgst + T8 * dVgst_dW;
      double dT9_dL = dT8_dL * d->vgst + T8 * dVgst_dL;
      double T0, dT0_dVg, dT0_dVb, dT0_dVd;
      double dT0_dW, dT0_dL;
      double ddT0_dVg_dW, ddT0_dVg_dL;
      if (T9 > -0.9) {
	T0 = 1.0 + T9;
	dT0_dW = dT9_dW;
	dT0_dL = dT9_dL;
	dT0_dVg = T8 * (1.0 - d->vgst * dEsatL_dVg / EsatL);
	ddT0_dVg_dW = dT8_dW * (1.0 - d->vgst * dEsatL_dVg / EsatL)
	  + T8 * ( - dVgst_dW * dEsatL_dVg / EsatL - d->vgst * ddEsatL_dVg_dW / EsatL
	       + d->vgst * dEsatL_dVg / EsatL / EsatL * dEsatL_dW );
	ddT0_dVg_dL = dT8_dL * (1.0 - d->vgst * dEsatL_dVg / EsatL)
	  + T8 * ( - dVgst_dL * dEsatL_dVg / EsatL - d->vgst * ddEsatL_dVg_dL / EsatL
	       + d->vgst * dEsatL_dVg / EsatL / EsatL * dEsatL_dL );
	dT0_dVb = -T9 * dEsatL_dVb / EsatL;
	dT0_dVd = -T9 * dEsatL_dVd / EsatL;
      }else{
	/* Added to avoid the discontinuity problems caused by pvag */
	double T1 = 1.0 / (17.0 + 20.0 * T9);
	double dT1_dW = - T1 * (17.0 + 20.0 * T9) * 20 * dT9_dW;
	double dT1_dL = - T1 * (17.0 + 20.0 * T9) * 20 * dT9_dL;
	T0 = (0.8 + T9) * T1;
	dT0_dW = dT9_dW * T1 + (0.8 + T9) * dT1_dW;
	dT0_dL = dT9_dL * T1 + (0.8 + T9) * dT1_dL;
	dT1_dW *= 2. * T1;
	dT1_dL *= 2. * T1;
	T1 *= T1;
	dT0_dVg = T8 * (1.0 - d->vgst * dEsatL_dVg / EsatL) * T1;
	ddT0_dVg_dW = dT8_dW * (1.0 - d->vgst * dEsatL_dVg / EsatL) * T1
	            + T8 * ( - dVgst_dW * dEsatL_dVg / EsatL
			   - d->vgst * ddEsatL_dVg_dW / EsatL
	                   + d->vgst * dEsatL_dVg / EsatL / EsatL * dEsatL_dW ) * T1
	            + T8 * (1.0 - d->vgst * dEsatL_dVg / EsatL) * dT1_dW;
	ddT0_dVg_dL = dT8_dL * (1.0 - d->vgst * dEsatL_dVg / EsatL) * T1
	  + T8 * ( - dVgst_dL * dEsatL_dVg / EsatL - d->vgst * ddEsatL_dVg_dL / EsatL
	       + d->vgst * dEsatL_dVg / EsatL / EsatL * dEsatL_dL ) * T1
	  + T8 * (1.0 - d->vgst * dEsatL_dVg / EsatL) * dT1_dL;
	T9 *= T1 / EsatL;
	dT0_dVb = -T9 * dEsatL_dVb;
	dT0_dVd = -T9 * dEsatL_dVd;
      }
      double tmp1 = VACLM * VACLM;
      double dtmp1_dW = 2. * VACLM * dVACLM_dW;
      double dtmp1_dL = 2. * VACLM * dVACLM_dL;
      double tmp2 = VADIBL * VADIBL;
      double dtmp2_dW = 2. * VADIBL * dVADIBL_dW;
      double dtmp2_dL = 2. * VADIBL * dVADIBL_dL;
      double tmp3 = VACLM + VADIBL;
      double dtmp3_dW = dVACLM_dW + dVADIBL_dW;
      assert(is_number(dtmp3_dW));
      double dtmp3_dL = dVACLM_dL + dVADIBL_dL;

      double T1 = VACLM * VADIBL / tmp3;
      assert(is_number(T1));
      double dT1_dW = ( dVACLM_dW * VADIBL
	              + VACLM * dVADIBL_dW
		      - T1 * dtmp3_dW ) / tmp3;
      assert(is_number(dT1_dW));
      double dT1_dL = dVACLM_dL * VADIBL / tmp3
	            + VACLM * dVADIBL_dL / tmp3
		    - T1 / tmp3 * dtmp3_dL;
      dtmp3_dW = 2. * tmp3 * dtmp3_dW;
      dtmp3_dL = 2. * tmp3 * dtmp3_dL;
      tmp3 *= tmp3;
      double dT1_dVg = (tmp1 * dVADIBL_dVg + tmp2 * dVACLM_dVg) / tmp3;
      double ddT1_dVg_dW = (dtmp1_dW * dVADIBL_dVg + tmp1 * ddVADIBL_dVg_dW
	                    + dtmp2_dW * dVACLM_dVg + tmp2 * ddVACLM_dVg_dW ) / tmp3
	                 - dT1_dVg / tmp3 * dtmp3_dW;
      double ddT1_dVg_dL = (dtmp1_dL * dVADIBL_dVg + tmp1 * ddVADIBL_dVg_dL
	                    + dtmp2_dL * dVACLM_dVg + tmp2 * ddVACLM_dVg_dL ) / tmp3
	                 - dT1_dVg / tmp3 * dtmp3_dL;
      double dT1_dVd = (tmp1 * dVADIBL_dVd + tmp2 * dVACLM_dVd) / tmp3;
      double dT1_dVb = (tmp1 * dVADIBL_dVb + tmp2 * dVACLM_dVb) / tmp3;

      Va = Vasat + T0 * T1;
      assert(is_number(Va));
      dVa_dW = dVasat_dW + dT0_dW * T1 + T0 * dT1_dW;
      assert(is_number(dVa_dW));
      dVa_dL = dVasat_dL + dT0_dL * T1 + T0 * dT1_dL;
      assert(is_number(dVa_dL));
      dVa_dVg = dVasat_dVg + T1 * dT0_dVg + T0 * dT1_dVg;
      ddVa_dVg_dW = ddVasat_dVg_dW + dT1_dW * dT0_dVg + T1 * ddT0_dVg_dW
	          + dT0_dW * dT1_dVg + T0 * ddT1_dVg_dW;
      ddVa_dVg_dL = ddVasat_dVg_dL + dT1_dL * dT0_dVg + T1 * ddT0_dVg_dL
	          + dT0_dL * dT1_dVg + T0 * ddT1_dVg_dL;
      dVa_dVd = dVasat_dVd + T1 * dT0_dVd + T0 * dT1_dVd;
      dVa_dVb = dVasat_dVb + T1 * dT0_dVb + T0 * dT1_dVb;
    }
    trace4("", Va, dVa_dVg, dVa_dVd, dVa_dVb);

    double Idl, dIdl_dVg, dIdl_dVd, dIdl_dVb;
    double dIdl_dW, dIdl_dL;
    double ddIdl_dVg_dW, ddIdl_dVg_dL;
    {
      double gche, dgche_dVg, dgche_dVd, dgche_dVb;
      double dgche_dW, dgche_dL;
      double ddgche_dVg_dW, ddgche_dVg_dL;
      {
	double beta, dbeta_dVg, dbeta_dVd, dbeta_dVb;
	double dbeta_dW, dbeta_dL;
	double ddbeta_dVg_dW, ddbeta_dVg_dL;
	{
	  double CoxWovL = m->cox * Weff / s->leff;
	  double dCoxWovL_dW = m->cox * dWeff_dW / s->leff;
	  double dCoxWovL_dL = m->cox * dWeff_dL / s->leff
	                     - CoxWovL / s->leff;
	  beta = ueff * CoxWovL;
	  dbeta_dW = dueff_dW * CoxWovL + ueff * dCoxWovL_dW;
	  dbeta_dL = dueff_dL * CoxWovL + ueff * dCoxWovL_dL;
	  dbeta_dVg = CoxWovL * dueff_dVg + beta * dWeff_dVg / Weff;
	  ddbeta_dVg_dW = dCoxWovL_dW * dueff_dVg
	                + CoxWovL * ddueff_dVg_dW
			+ dbeta_dW * dWeff_dVg / Weff
			+ beta * ddWeff_dVg_dW / Weff
			- beta * dWeff_dVg / Weff / Weff * dWeff_dW;
	  ddbeta_dVg_dL = dCoxWovL_dL * dueff_dVg
	                + CoxWovL * ddueff_dVg_dL
			+ dbeta_dL * dWeff_dVg / Weff
			+ beta * ddWeff_dVg_dL / Weff
			- beta * dWeff_dVg / Weff / Weff * dWeff_dL;
	  dbeta_dVd = CoxWovL * dueff_dVd;
	  dbeta_dVb = CoxWovL * dueff_dVb + beta * dWeff_dVb / Weff;
	}
	trace4("", beta, dbeta_dVg, dbeta_dVd, dbeta_dVb);

	double fgche1, dfgche1_dVg, dfgche1_dVd, dfgche1_dVb;
	double dfgche1_dW, dfgche1_dL;
	double ddfgche1_dVg_dW, ddfgche1_dVg_dL;
	{
	  double T0 = 1.0 - 0.5 * Abulk * Vdseff / Vgst2Vtm;
	  double dT0_dW = - .5 * dAbulk_dW * Vdseff / Vgst2Vtm
	                  - .5 * Abulk * dVdseff_dW / Vgst2Vtm
			  + .5 * Abulk * Vdseff / Vgst2Vtm / Vgst2Vtm * dVgst2Vtm_dW;
	  double dT0_dL = - .5 * dAbulk_dL * Vdseff / Vgst2Vtm
	                  - .5 * Abulk * dVdseff_dL / Vgst2Vtm
			  + .5 * Abulk * Vdseff / Vgst2Vtm / Vgst2Vtm * dVgst2Vtm_dL;
	  double dT0_dVg = -0.5 * (Abulk * dVdseff_dVg
	      - Abulk * Vdseff / Vgst2Vtm + Vdseff * dAbulk_dVg) / Vgst2Vtm;
	  double dT0_dVd = -0.5 * Abulk * dVdseff_dVd / Vgst2Vtm;
	  double dT0_dVb = -0.5 * (Abulk*dVdseff_dVb + dAbulk_dVb*Vdseff)
	    / Vgst2Vtm;
	  fgche1 = d->vgst * T0;
	  dfgche1_dW = dVgst_dW * T0 + d->vgst * dT0_dW;
	  dfgche1_dL = dVgst_dL * T0 + d->vgst * dT0_dL;
	  dfgche1_dVg = d->vgst * dT0_dVg + T0;
	  ddfgche1_dVg_dW = dVgst_dW * dT0_dVg + dVgst_dW * dT0_dVg + dT0_dW;
	  ddfgche1_dVg_dL = dVgst_dL * dT0_dVg + dVgst_dL * dT0_dVg + dT0_dL;
	  dfgche1_dVd = d->vgst * dT0_dVd;
	  dfgche1_dVb = d->vgst * dT0_dVb;
	}
	trace4("", fgche1, dfgche1_dVg, dfgche1_dVd, dfgche1_dVb);

	double fgche2, dfgche2_dVg, dfgche2_dVd, dfgche2_dVb;
	double dfgche2_dW, dfgche2_dL;
	double ddfgche2_dVg_dW, ddfgche2_dVg_dL;
	{
	  double T9 = Vdseff / EsatL;
	  double dT9_dW = dVdseff_dW / EsatL - T9 / EsatL * dEsatL_dW;
	  double dT9_dL = dVdseff_dL / EsatL - T9 / EsatL * dEsatL_dL;
	  fgche2 = 1.0 + T9;
	  dfgche2_dW = dT9_dW;
	  dfgche2_dL = dT9_dL;
	  dfgche2_dVg = (dVdseff_dVg - T9 * dEsatL_dVg) / EsatL;
	  ddfgche2_dVg_dW = ( ddVdseff_dVg_dW
	                    - dT9_dW * dEsatL_dVg
			    - T9 * ddEsatL_dVg_dW ) / EsatL
	                  - dfgche2_dVg / EsatL * dEsatL_dW;
	  ddfgche2_dVg_dL = ( ddVdseff_dVg_dL
	                    - dT9_dL * dEsatL_dVg
			    - T9 * ddEsatL_dVg_dL ) / EsatL
	                  - dfgche2_dVg / EsatL * dEsatL_dL;
	  dfgche2_dVd = (dVdseff_dVd - T9 * dEsatL_dVd) / EsatL;
	  dfgche2_dVb = (dVdseff_dVb - T9 * dEsatL_dVb) / EsatL;
	}
	trace4("", fgche2, dfgche2_dVg, dfgche2_dVd, dfgche2_dVb);

	gche = beta * fgche1 / fgche2;
	dgche_dW = dbeta_dW * fgche1 / fgche2
	         + beta * dfgche1_dW / fgche2
		 - gche / fgche2 * dfgche2_dW;
	dgche_dL = dbeta_dL * fgche1 / fgche2
	         + beta * dfgche1_dL / fgche2
		 - gche / fgche2 * dfgche2_dL;
	dgche_dVg = (beta * dfgche1_dVg + fgche1 * dbeta_dVg
	    - gche * dfgche2_dVg) / fgche2;
	ddgche_dVg_dW = ( dbeta_dW * dfgche1_dVg + beta * ddfgche1_dVg_dW
	                + dfgche1_dW * dbeta_dVg
	                + fgche1 * ddbeta_dVg_dW
	                - dgche_dW * dfgche2_dVg
	                - gche * ddfgche2_dVg_dW ) / fgche2
	              - dgche_dVg / fgche2 * dfgche2_dW;
	ddgche_dVg_dL = ( dbeta_dL * dfgche1_dVg + beta * ddfgche1_dVg_dL
	                + dfgche1_dL * dbeta_dVg
	                + fgche1 * ddbeta_dVg_dL
	                - dgche_dL * dfgche2_dVg
	                - gche * ddfgche2_dVg_dL ) / fgche2
	              - dgche_dVg / fgche2 * dfgche2_dL;
	dgche_dVd = (beta * dfgche1_dVd + fgche1 * dbeta_dVd
	    - gche * dfgche2_dVd) / fgche2;
	dgche_dVb = (beta * dfgche1_dVb + fgche1 * dbeta_dVb
	    - gche * dfgche2_dVb) / fgche2;
      }
      trace4("", gche, dgche_dVg, dgche_dVd, dgche_dVb);

      double T0 = 1.0 + gche * Rds;
      double dT0_dW = dgche_dW * Rds + gche * dRds_dW;
      double dT0_dL = dgche_dL * Rds + gche * dRds_dL;
      double T9 = Vdseff / T0;
      double dT9_dW = dVdseff_dW / T0 - T9 / T0 * dT0_dW;
      double dT9_dL = dVdseff_dL / T0 - T9 / T0 * dT0_dL;
      Idl = gche * T9;
      assert(is_number(Idl));
      dIdl_dW = dgche_dW * T9 + gche * dT9_dW;
      dIdl_dL = dgche_dL * T9 + gche * dT9_dL;
      assert(is_number(dIdl_dW));
      assert(is_number(dIdl_dL));
      dIdl_dVg = (gche * dVdseff_dVg + T9 * dgche_dVg) / T0
	- Idl * gche / T0 * dRds_dVg;
      ddIdl_dVg_dW = ( dgche_dW * dVdseff_dVg + gche * ddVdseff_dVg_dW
	             + dT9_dW * dgche_dVg + T9 * ddgche_dVg_dW
		     -  dIdl_dW * gche * dRds_dVg
		     -  Idl * dgche_dW * dRds_dVg
		     -  Idl * gche * ddRds_dVg_dW) / T0
	- dIdl_dVg / T0 *dT0_dW;
      ddIdl_dVg_dL = ( dgche_dL * dVdseff_dVg + gche * ddVdseff_dVg_dL
	             + dT9_dL * dgche_dVg + T9 * ddgche_dVg_dL
		     -  dIdl_dL * gche * dRds_dVg
		     -  Idl * dgche_dL * dRds_dVg
		     -  Idl * gche * ddRds_dVg_dL) / T0
	- dIdl_dVg / T0 * dT0_dL;

      dIdl_dVd = (gche * dVdseff_dVd + T9 * dgche_dVd) / T0;
      dIdl_dVb = (gche*dVdseff_dVb + T9*dgche_dVb - Idl*dRds_dVb*gche) / T0;
    }
    trace4("", Idl, dIdl_dVg, dIdl_dVd, dIdl_dVb);

    assert(Va);
    double T9 = diffVds / Va;
    assert(is_number(T9));
    double dT9_dW = ddiffVds_dW / Va - T9 / Va * dVa_dW;
    assert(is_number(dT9_dW));
    double dT9_dL = ddiffVds_dL / Va - T9 / Va * dVa_dL;
    double T0 = 1.0 + T9;
    double dT0_dW = dT9_dW;
    double dT0_dL = dT9_dL;
    Idsa = Idl * T0;
    assert(is_number(Idsa));
    dIdsa_dW = dIdl_dW * T0 + Idl * dT0_dW;
    dIdsa_dL = dIdl_dL * T0 + Idl * dT0_dL;
    dIdsa_dVg = T0 * dIdl_dVg - Idl * (dVdseff_dVg + T9 * dVa_dVg) / Va;
    ddIdsa_dVg_dW = dT0_dW * dIdl_dVg + T0 * ddIdl_dVg_dW
		  - dIdl_dW * (dVdseff_dVg + T9 * dVa_dVg) / Va
		  - Idl * (ddVdseff_dVg_dW + dT9_dW * dVa_dVg + T9 * ddVa_dVg_dW ) / Va
		  + Idl * (dVdseff_dVg + T9 * dVa_dVg) / Va / Va * dVa_dW;
    ddIdsa_dVg_dL = dT0_dL * dIdl_dVg + T0 * ddIdl_dVg_dL
		  - dIdl_dL * (dVdseff_dVg + T9 * dVa_dVg) / Va
		  - Idl * (ddVdseff_dVg_dL + dT9_dL * dVa_dVg + T9 * ddVa_dVg_dL ) / Va
		  + Idl * (dVdseff_dVg + T9 * dVa_dVg) / Va / Va * dVa_dL;
    dIdsa_dVd = T0 * dIdl_dVd + Idl * (1.0 - dVdseff_dVd - T9*dVa_dVd) / Va;
    dIdsa_dVb = T0 * dIdl_dVb - Idl * (dVdseff_dVb + T9 * dVa_dVb) / Va;
  }
  assert(is_number(dIdsa_dW));
  assert(is_number(dIdsa_dL));
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // SENS: d->ids, d->gds, d->gmf, d->gmbf
  {
    double VASCBE, dVASCBE_dVg, dVASCBE_dVd, dVASCBE_dVb;
    double dVASCBE_dW, dVASCBE_dL;
    {
      if (s->pscbe2 > 0.0) {
	if (diffVds > s->pscbe1 * s->litl / EXP_THRESHOLD) {
	  double T0 = s->pscbe1 * s->litl / diffVds;
	  double dT0_dW = m->pscbe1.dW(L,W, par_scope) * s->litl / diffVds
	                - T0 / diffVds * ddiffVds_dW;
	                // assuming constant litl (constant xj);
	  double dT0_dL = m->pscbe1.dL(L,W, par_scope) * s->litl / diffVds
	                - T0 / diffVds * ddiffVds_dL;
	                // assuming constant litl (constant xj);
	  VASCBE = s->leff * exp(T0) / s->pscbe2;
	  dVASCBE_dW = s->leff * exp(T0) * (
	               - 1. / s->pscbe2 / s->pscbe2 * m->pscbe2.dW(L, W, par_scope)
	               + dT0_dW / s->pscbe2 );
	  dVASCBE_dL = s->leff * exp(T0) * (
	               - 1. / s->pscbe2 / s->pscbe2 * m->pscbe2.dL(L,W, par_scope)
	               + dT0_dL / s->pscbe2 )
		       + exp(T0) / s->pscbe2;
	  double T1 = T0 * VASCBE / diffVds;
	  dVASCBE_dVg = T1 * dVdseff_dVg;
	  dVASCBE_dVd = -T1 * (1.0 - dVdseff_dVd);
	  dVASCBE_dVb = T1 * dVdseff_dVb;
	}else{
	  VASCBE = MAX_EXP * s->leff/s->pscbe2;
	  dVASCBE_dVg = dVASCBE_dVd = dVASCBE_dVb = 0.0;
	  dVASCBE_dW = - VASCBE / s->pscbe2 * m->pscbe2.dW(L,W, par_scope);
	  dVASCBE_dL = - VASCBE / s->pscbe2 * m->pscbe2.dL(L,W, par_scope)
	               + MAX_EXP / s->pscbe2;
	}
      }else{
	VASCBE = MAX_EXP;
	dVASCBE_dVg = dVASCBE_dVd = dVASCBE_dVb = 0.0;
	dVASCBE_dW = dVASCBE_dL = 0;
      }
    }
    double T9 = diffVds / VASCBE;
    double dT9_dW = (ddiffVds_dW - T9  * dVASCBE_dW ) / VASCBE;
    double dT9_dL = (ddiffVds_dL - T9  * dVASCBE_dL ) / VASCBE;
    double T0 = 1.0 + T9;
    double dT0_dW = dT9_dW;
    double dT0_dL = dT9_dL;

    double Gm = T0 * dIdsa_dVg - Idsa*(dVdseff_dVg + T9 * dVASCBE_dVg) / VASCBE;
    double dGm_dW = dT0_dW * dIdsa_dVg + T0 * ddIdsa_dVg_dW
		  - ( dIdsa_dW*(dVdseff_dVg + T9 * dVASCBE_dVg) 
		    + Idsa*(ddVdseff_dVg_dW + dT9_dW * dVASCBE_dVg + T9 * dVASCBE_dVg)
		    - Idsa*(dVdseff_dVg + T9*dVASCBE_dVg) / VASCBE * dVASCBE_dW ) / VASCBE;
    double dGm_dL = dT0_dL * dIdsa_dVg + T0 * ddIdsa_dVg_dL
		  - ( dIdsa_dL*(dVdseff_dVg + T9 * dVASCBE_dVg)
		    + Idsa*(ddVdseff_dVg_dL + dT9_dL*dVASCBE_dVg+T9*dVASCBE_dVg)
		    -  Idsa*(dVdseff_dVg + T9*dVASCBE_dVg) / VASCBE * dVASCBE_dL ) / VASCBE;
    double Gds = T0 * dIdsa_dVd
      + Idsa * (1.0 - dVdseff_dVd - T9 * dVASCBE_dVd) / VASCBE;
    double Gmb = T0 * dIdsa_dVb
      - Idsa * (dVdseff_dVb + T9 * dVASCBE_dVb) / VASCBE;
    trace3("", T0, dIdsa_dVb, (T0 * dIdsa_dVb));
    trace4("", dVdseff_dVb, T9, dVASCBE_dVb, (dVdseff_dVb + T9*dVASCBE_dVb));
    trace3("", Idsa, VASCBE, (Idsa*(dVdseff_dVb+T9*dVASCBE_dVb)/VASCBE));

    Gds += Gm * dVgsteff_dVd;
    Gmb += Gm * dVgsteff_dVb;
    dGm_dW = dGm_dW * dVgsteff_dVg + Gm * ddVgsteff_dVg_dW;
    dGm_dL = dGm_dL * dVgsteff_dVg + Gm * ddVgsteff_dVg_dL;
    assert(is_number(dGm_dW));
    assert(is_number(dGm_dL));
    Gm *= dVgsteff_dVg;
    Gmb *= dVbseff_dVb;
    d->dgmdw = dGm_dW;
    d->dgmdl = dGm_dL;

    trace0("=========================");

    assert(d->gds = Gds);
    if (d->reversed) {
//      assert(d->ids == -Ids);
      assert(is_almost(d->gmr, Gm));
      assert(is_almost(d->gmbr, Gmb));
      assert(d->gmf == 0 && d->gmbf == 0);
    }else{
//      assert(d->ids == Ids);
      assert(is_almost(d->gmf, Gm));
      assert(is_almost(d->gmbf, Gmb));
      assert(d->gmr == 0 && d->gmbr == 0);
    }
  }
}
/*--------------------------------------------------------------------------*/
double MODEL_BUILT_IN_MOS8::dgmdw_eff(const DEV_BUILT_IN_MOS* brh) const
{
  const DEV_BUILT_IN_MOS* d = prechecked_cast<const DEV_BUILT_IN_MOS*>(brh);
  assert(d);
  return d->dgmdw;
}
/*--------------------------------------------------------------------------*/
double MODEL_BUILT_IN_MOS8::dgmdl_eff(const DEV_BUILT_IN_MOS* brh) const
{
  const DEV_BUILT_IN_MOS* d = prechecked_cast<const DEV_BUILT_IN_MOS*>(brh);
  assert(d);
  return d->dgmdl;
}
// vim:ts=8:sw=2:
