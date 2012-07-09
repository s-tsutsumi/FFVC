// #################################################################
//
// FFV : Frontflow / violet Cartesian
//
// Copyright (c) All right reserved. 2012
//
// Institute of Industrial Science, The University of Tokyo, Japan. 
//
// #################################################################

/** 
 * @file   ffv_Ffunc.h
 * @brief  FFV Fortran function Header
 * @author kero
 */

#include "FB_Define.h"

#ifndef _FFV_F_FUNC_H_
#define _FFV_F_FUNC_H_

#ifdef _WIN32

// ffv_forcing.f90
#define hex_dir_            HEX_DIR
#define force_keep_vec_     FORCE_KEEP_VEC
#define hex_psrc_           HEX_PSRC
#define hex_force_pvec_     HEX_FORCE_PVEC
#define hex_force_vec_      HEX_FORCE_VEC


// ffv_pbc.f90
#define pobc_drchlt_        POBC_DRCHLT
#define pobc_neumann_       POBC_NEUMANN


// ffv_poisson.f90
#define div_cnst_           DIV_CNST
#define psor_               PSOR
#define psor2sma_core_      PSOR2SMA_CORE
#define sma_comm_           SMA_COMM
#define sma_comm_wait_      SMA_COMM_WAIT
#define cds_psor_           CDS_PSOR


// ffv_pscalar.f90
#define ps_muscl_           PS_MUSCL
#define ps_buoyancy_        PS_BUOYANCY
#define ps_diff_ee_         PS_DIFF_EE
#define hbc_drchlt_         HBC_DRCHLT

// ffv_vbc_inner.f90
#define vibc_drchlt_        VIBC_DRCHLT
#define vibc_outflow_       VIBC_OUTFLOW
#define pvec_vibc_specv_    PVEC_VIBC_SPECV
#define pvec_vibc_oflow_    PVEC_VIBC_OFLOW
#define div_ibc_drchlt_     DIV_IBC_DRCHLT
#define div_ibc_oflow_pvec_ DIV_IBC_OFLOW_PVEC
#define div_ibc_oflow_vec_  DIV_IBC_OFLOW_VEC

// ffv_vbc_outer.f90
#define pvec_vobc_specv_    PVEC_VOBC_SPECV
#define pvec_vobc_oflow_    PVEC_VOBC_OFLOW
#define pvec_vobc_wall_     PVEC_VOBC_WALL
#define pvec_vobc_symtrc_   PVEC_VOBC_SYMTRC
#define vobc_drchlt_        VOBC_DRCHLT
#define vobc_outflow_       VOBC_OUTFLOW
#define vobc_tfree_         VOBC_TFREE
#define vobc_update_        VOBC_UPDATE
#define div_obc_drchlt_     DIV_OBC_DRCHLT
#define div_obc_oflow_pvec_ DIV_OBC_OFLOW_PVEC
#define div_obc_oflow_vec_  DIV_OBC_OFLOW_VEC

// ffv_velocity_binary.f90
#define ab2_                AB2
#define divergence_         DIVERGENCE
#define eddy_viscosity_     EDDY_VISCOSITY
#define euler_explicit_     EULER_EXPLICIT
#define friction_velocity_  FRICTION_VELOCITY
#define pvec_muscl_         PVEC_MUSCL
#define pvec_les_           PVEC_LES
#define update_vec_         UPDATE_VEC
#define vis_cn_jcb_         VIS_CN_JCB
#define vis_cn_mod_jcb_     VIS_CN_MOD_JCB
#define vis_cn_mod_sor_     VIS_CN_MOD_SOR
#define vis_cn_sor_         VIS_CN_SOR
#define vis_ee_             VIS_EE
#define vis_ee_vbc_         VIS_EE_VBC

// ffv_utility.f90
#define norm_v_div_dbg_     NORM_V_DIV_DBG
#define norm_v_div_l2_      NORM_V_DIV_L2
#define norm_v_div_max_     NORM_V_DIV_MAX
#define helicity_           HELICITY
#define i2vgt_              I2VGT
#define rot_v_              ROT_V
#define find_vmax_          FIND_VMAX


#define cds_pvec_vibc_specv_    CDS_PVEC_VIBC_SPECV


// c3d_vof.f90
#define vof_uwd_                VOF_UWD
#define vof_muscl_              VOF_MUSCL

// cds_vector.f90
#define cds_pvec_muscl_         CDS_PVEC_MUSCL
#define cds_update_vec_         CDS_UPDATE_VEC
#define cds_div_                CDS_DIV
#define cds_force_              CDS_FORCE


#endif // _WIN32


extern "C" {
  //***********************************************************************************************
  // ffv_forcing.f90
  void hex_dir_           (REAL_TYPE* v, int* sz, int* g, int* st, int* ed, int* bd, REAL_TYPE* vf, int* odr, REAL_TYPE* v00, REAL_TYPE* nv, double* flop);
  void force_keep_vec_    (REAL_TYPE* wk, int* c_sz, int* st, int* ed, REAL_TYPE* v, int* sz, int* g);
  void hex_psrc_          (REAL_TYPE* src, int* sz, int* g, int* st, int* ed, int* bd, float* vf, REAL_TYPE* wk, int* c_sz, int* odr, 
                           REAL_TYPE* v00, REAL_TYPE* dh, REAL_TYPE* nv, REAL_TYPE* c, double* flop);
  void hex_force_pvec_    (REAL_TYPE* vc,  int* sz, int* g, int* st, int* ed, int* bd, REAL_TYPE* vf, REAL_TYPE* v, int* odr, 
                           REAL_TYPE* v00, REAL_TYPE* dt, REAL_TYPE* nv, REAL_TYPE* c, double* flop);
  void hex_force_vec_     (REAL_TYPE* v, REAL_TYPE* div, int* sz, int* g, int* st, int* ed, int* bd, REAL_TYPE* vf, REAL_TYPE* wk, int* c_sz, int* odr, 
                           REAL_TYPE* v00, REAL_TYPE* dt, REAL_TYPE* dh, REAL_TYPE* nv, REAL_TYPE* c, REAL_TYPE* am, double* flop);
  
  
  
  
  
  //***********************************************************************************************
  // ffv_pbc.f90
  void pobc_drchlt_(REAL_TYPE* p, int* sz, int* g, int* face, REAL_TYPE* pv);
  
  void pobc_neumann_(REAL_TYPE* p, int* sz, int* g, int* face);
  
  
  
  //***********************************************************************************************
  // ffv_poisson.f90
  void div_cnst_(REAL_TYPE* dv, int* sz, int* g, REAL_TYPE* b2, int* bp, double* flop);
  void psor_(REAL_TYPE* p,  int* sz, int* g, REAL_TYPE* omg, REAL_TYPE* res, REAL_TYPE* s0, REAL_TYPE* s1, 
                         int* bp, double* flop);
  void psor2sma_core_(REAL_TYPE* p,  int* sz, int* g, int* ip, int* color, REAL_TYPE* omg, REAL_TYPE* res, REAL_TYPE* s0, 
                         REAL_TYPE* s1, int* bp, double* flop);
  void sma_comm_(REAL_TYPE* p, int* sz, int* g, int* col, int* ip, int* cf_sz, REAL_TYPE* cf_x, REAL_TYPE* cf_y, 
                         REAL_TYPE* cf_z, int* key, int* para_key);
  void sma_comm_wait_(REAL_TYPE* p, int* sz, int* g, int* col, int* ip, int* cf_sz, REAL_TYPE* cf_x, REAL_TYPE* cf_y, 
                         REAL_TYPE* cf_z, int* key);
  
  
  //***********************************************************************************************
  // ffv_pscalar.f90
  void ps_muscl_      (REAL_TYPE* ws, int* sz, int* g, REAL_TYPE* dh, int* c_scheme, REAL_TYPE* v00, REAL_TYPE* v, REAL_TYPE* t, int* bv, 
                       int* bh1, int* bh2, int* swt, double* flop);
  void ps_buoyancy_   (REAL_TYPE* v, int* sz, int* g, REAL_TYPE* dt, REAL_TYPE* gr, REAL_TYPE* rei, REAL_TYPE* t, int* bd, double* flop);
  void ps_diff_ee_    (REAL_TYPE* t, int* sz, int* g, REAL_TYPE* res, REAL_TYPE* dh, REAL_TYPE* dt, REAL_TYPE* pei, REAL_TYPE* qbc, 
                       int* bh, REAL_TYPE* ws, double* flop);
  void hbc_drchlt_    (REAL_TYPE* t,  int* sz, int* g, int* st, int* ed, int* bh, int* odr, REAL_TYPE* tc);
  
  
  
  //***********************************************************************************************
  // ffv_vbc_inner.f90
  void pvec_vibc_oflow_   (REAL_TYPE* wv, int* sz, int* g, int* st, int* ed, REAL_TYPE* dh, REAL_TYPE* rei, REAL_TYPE* v, 
                           int* bv, int* odr, REAL_TYPE* vec, double* flop);
  void pvec_vibc_specv_   (REAL_TYPE* wv, int* sz, int* g, int* st, int* ed, REAL_TYPE* dh, REAL_TYPE* v00, REAL_TYPE* rei, REAL_TYPE* v, 
                           int* bv, int* odr, REAL_TYPE* vec, double* flop);
  void vibc_drchlt_       (REAL_TYPE* v, int* sz, int* g, int* st, int* ed, REAL_TYPE* v00, int* bv, int* odr, REAL_TYPE* vec);
  void vibc_outflow_      (REAL_TYPE* vc,int* sz, int* g, int* st, int* ed, int* bv, int* odr);
  void div_ibc_drchlt_    (REAL_TYPE* div, int* sz, int* g, int* st, int* ed, REAL_TYPE* v00, REAL_TYPE* coef, int* bv, int* odr, 
                           REAL_TYPE* vec, double* flop);
  void div_ibc_oflow_pvec_(REAL_TYPE* div, int* sz, int* g, int* st, int* ed, REAL_TYPE* v00, REAL_TYPE* v_cnv, REAL_TYPE* coef, 
                           int* bv, int* odr, REAL_TYPE* v0, double* flop);
  void div_ibc_oflow_vec_ (REAL_TYPE* div, int* sz, int* g, int* st, int* ed, REAL_TYPE* v00, REAL_TYPE* coef, int* bv, int* odr, 
                           REAL_TYPE* av, double* flop);
  
  
  //***********************************************************************************************
  // ffv_vbc_outer.f90
  void pvec_vobc_oflow_   (REAL_TYPE* wv, int* sz, int* g, REAL_TYPE* dh, REAL_TYPE* v00, REAL_TYPE* rei, REAL_TYPE* v,
                           int* bv, REAL_TYPE* vec, int* face, double* flop);
  void pvec_vobc_specv_   (REAL_TYPE* wv, int* sz, int* g, REAL_TYPE* dh, REAL_TYPE* v00, REAL_TYPE* rei, REAL_TYPE* v,
                           int* bv, REAL_TYPE* vec, int* face, double* flop);
  void pvec_vobc_symtrc_  (REAL_TYPE* wv, int* sz, int* g, REAL_TYPE* dh, REAL_TYPE* rei, REAL_TYPE* v, int* bv, int* face, double* flop);
  void pvec_vobc_wall_    (REAL_TYPE* wv, int* sz, int* g, REAL_TYPE* dh, REAL_TYPE* v00, REAL_TYPE* rei, REAL_TYPE* v,
                           int* bv, REAL_TYPE* vec, int* face, double* flop);
  void vobc_drchlt_       (REAL_TYPE* v, int* sz, int* g, REAL_TYPE* v00, int* bv, int* face, REAL_TYPE* vec);
  void vobc_neumann_      (REAL_TYPE* v, int* sz, int* g, int* face);
  void vobc_outflow_      (REAL_TYPE* v, int* sz, int* g, REAL_TYPE* c, int* bv, int* face, REAL_TYPE* v0, double* flop);
  void vobc_tfree_        (REAL_TYPE* v, int* sz, int* g, int* face, double* flop);
  void vobc_update_       (REAL_TYPE* v, int* sz, int* g, REAL_TYPE*vc, int* face);
  void div_obc_drchlt_    (REAL_TYPE* div, int* sz, int* g, int* face, REAL_TYPE* v00, REAL_TYPE* coef, int* bv, REAL_TYPE* vec, double* flop);
  void div_obc_oflow_pvec_(REAL_TYPE* div, int* sz, int* g, int* face, REAL_TYPE* v00, REAL_TYPE* v_out, REAL_TYPE* coef, int* bv, 
                           REAL_TYPE* v0, double* flop);
  void div_obc_oflow_vec_ (REAL_TYPE* div, int* sz, int* g, int* face, REAL_TYPE* v00, REAL_TYPE* coef, int* bv, REAL_TYPE* aa, double* flop);

  
  //***********************************************************************************************
  // ffv_velocity_binary.f90
  void ab2_               (REAL_TYPE* vc, int* sz, int* g, REAL_TYPE* dt, REAL_TYPE* v, REAL_TYPE* ab, int* bd, REAL_TYPE* v00, double* flop);
  void divergence_        (REAL_TYPE* dv, int* sz, int* g, REAL_TYPE* coef, REAL_TYPE* vc, int* bv, REAL_TYPE* v00, double* flop);
  void eddy_viscosity_    (REAL_TYPE* vt, int* sz, int* g, REAL_TYPE* dh, REAL_TYPE* re, REAL_TYPE* cs, REAL_TYPE* v, int* bx, 
                           REAL_TYPE* vt_range, REAL_TYPE* yp_range, REAL_TYPE* v00);
  void euler_explicit_    (REAL_TYPE* vc, int* sz, int* g, REAL_TYPE* dt, REAL_TYPE* v, int* bd, double* flop);
  void friction_velocity_ (REAL_TYPE* ut, int* sz, int* g, REAL_TYPE* dh, REAL_TYPE* re, REAL_TYPE* v, int* bp, 
                           REAL_TYPE* range_Yp, REAL_TYPE* range_Ut, REAL_TYPE* v00, double* flop);
  void pvec_muscl_        (REAL_TYPE* wv, int* sz, int* g, REAL_TYPE* dh, int* c_scheme, REAL_TYPE* v00, REAL_TYPE* rei, REAL_TYPE* v, 
                           int* bv, int* bp, int* v_mode, REAL_TYPE* ut, int* wall_type, int* bd, float* cvf, double* flop);
  void update_vec_        (REAL_TYPE* v, REAL_TYPE* div, int* sz, int* g, REAL_TYPE* dt, REAL_TYPE* dh, REAL_TYPE* vc, REAL_TYPE* p, int* bp, int* bv, 
                           REAL_TYPE* v00, double* flop);
  void vis_cn_jcb_        (REAL_TYPE* vc, int* sz, int* g, REAL_TYPE* dh, REAL_TYPE* dt, REAL_TYPE* v00, REAL_TYPE* rei, 
                           REAL_TYPE* omg, REAL_TYPE* wv, int* bx, REAL_TYPE* wk, REAL_TYPE* coef, REAL_TYPE* res, double* flop);
  void vis_cn_mod_jcb_    (REAL_TYPE* vc, int* sz, int* g, int* st, int* ed, REAL_TYPE* dh, REAL_TYPE* dt, REAL_TYPE* v00, REAL_TYPE* rei, 
                           REAL_TYPE* omg, REAL_TYPE* wv, int* bx, REAL_TYPE* wk, REAL_TYPE* coef, REAL_TYPE* res, REAL_TYPE* vec, double* flop);
  void vis_cn_mod_sor_    (REAL_TYPE* vc, int* sz, int* g, int* st, int* ed, REAL_TYPE* dh, REAL_TYPE* dt, REAL_TYPE* v00, REAL_TYPE* rei, 
                           REAL_TYPE* omg, REAL_TYPE* wv, int* bx, REAL_TYPE* coef, REAL_TYPE* res, REAL_TYPE* vec, double* flop);
  void vis_cn_sor_        (REAL_TYPE* vc, int* sz, int* g, REAL_TYPE* dh, REAL_TYPE* dt, REAL_TYPE* v00, REAL_TYPE* rei, 
                           REAL_TYPE* omg, REAL_TYPE* wv, int* bx, REAL_TYPE* coef, REAL_TYPE* res, double* flop);
  void vis_ee_            (REAL_TYPE* vc, int* sz, int* g, REAL_TYPE* dh, REAL_TYPE* dt, REAL_TYPE* v00, REAL_TYPE* rei, REAL_TYPE* wv, 
                           REAL_TYPE* v, int* bx, REAL_TYPE* coef, double* flop);
  void vis_ee_vbc_        (REAL_TYPE* vc, int* sz, int* g, int* st, int* ed, REAL_TYPE* dh, REAL_TYPE* dt, REAL_TYPE* v00, REAL_TYPE* rei, 
                           REAL_TYPE* v0, int* bx, int* odr, REAL_TYPE* coef, REAL_TYPE* vec, double* flop);
  
  


  
  //***********************************************************************************************
  // ffv_utility.f90
  void norm_v_div_dbg_    (REAL_TYPE* ds, REAL_TYPE* rm, int* index, int* sz, int* g, REAL_TYPE* div, REAL_TYPE* coef, int* bp, double* flop);
  void norm_v_div_l2_     (REAL_TYPE* rms,   int* sz, int* g, REAL_TYPE* div, REAL_TYPE* coef, int* bp, double* flop);
  void norm_v_div_max_    (REAL_TYPE* ds,    int* sz, int* g, REAL_TYPE* div, REAL_TYPE* coef, int* bp, double* flop);
  void helicity_          (REAL_TYPE* ht,    int* sz, int* g, REAL_TYPE* dh, REAL_TYPE* v, int* bv, REAL_TYPE* v00, double* flop);
  void i2vgt_             (REAL_TYPE* q,     int* sz, int* g, REAL_TYPE* dh, REAL_TYPE* v, int* bv, REAL_TYPE* v00, double* flop);
  void rot_v_             (REAL_TYPE* rot,   int* sz, int* g, REAL_TYPE* dh, REAL_TYPE* v, int* bv, REAL_TYPE* v00, double* flop);
  void find_vmax_         (REAL_TYPE* v_max, int* sz, int* g, REAL_TYPE* v00, REAL_TYPE* v, double* flop);
  void face_avr_sampling_ (REAL_TYPE* p, int* sz, int* g, int* face, REAL_TYPE* avr);
  void shift_pressure_    (REAL_TYPE* p, int* sz, int* g, REAL_TYPE* avr);
  void force_             (REAL_TYPE* force, int* sz, int* g, REAL_TYPE* p, int* bp, REAL_TYPE* dh, double* flop);
  


  
  // cds_poisson.f90
  void cds_psor_          (REAL_TYPE* p,   int* sz, int* g, REAL_TYPE* omg, REAL_TYPE* res, REAL_TYPE* div, REAL_TYPE* bnd, REAL_TYPE* cut, 
                          REAL_TYPE* epsilon, int* para_key);
  
  // c3d_vof.f90
  void vof_uwd_    (REAL_TYPE* f, int* sz, int* g, REAL_TYPE* v00, REAL_TYPE* dt, REAL_TYPE* dh, REAL_TYPE* v, REAL_TYPE* q, int* bx, double* flop);
  void vof_muscl_  (REAL_TYPE* f, int* sz, int* g, REAL_TYPE* v00, REAL_TYPE* dt, REAL_TYPE* dh, REAL_TYPE* v, REAL_TYPE* q, int* bx, double* flop);
  
  // cds_vector.f90
  void cds_pvec_muscl_    (REAL_TYPE* wv, int* sz, int* g, REAL_TYPE* dh, int* c_scheme, REAL_TYPE* v00, REAL_TYPE* rei, REAL_TYPE* v, 
                           int* bv, int* bp, int* v_mode, float* cut, double* flop);
  void cds_update_vec_    (REAL_TYPE* v, REAL_TYPE* div, int* sz, int* g, REAL_TYPE* dt, REAL_TYPE* dh, REAL_TYPE* vc, REAL_TYPE* p, 
                           int* bp, int* bv, float* cut, REAL_TYPE* v00, double* flop);
  void cds_div_           (REAL_TYPE* div, int* sz, int* g, REAL_TYPE* coef, REAL_TYPE* v, int* bv, float* cut, REAL_TYPE* v00, double* flop);
  void cds_force_         (REAL_TYPE* force, int* sz, int* g, REAL_TYPE* p, int* bp, int* bid, int* id, REAL_TYPE* dh, double* flop);
}

#endif // _FFV_F_FUNC_H_