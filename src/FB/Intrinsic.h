#ifndef _SKL_FB_INTRNSC_H_
#define _SKL_FB_INTRNSC_H_

/*
 * SPHERE - Skeleton for PHysical and Engineering REsearch
 *
 * Copyright (c) RIKEN, Japan. All right reserved. 2004-2012
 *
 */

//@file Intrinsic.h
//@brief FlowBase Intrinsic class Header
//@author keno, FSI Team, VCAD, RIKEN

#include "Skl.h"
#include "SklSolverBase.h"
#include "FBDefine.h"
#include "BndOuter.h"
#include "Control.h"
#include "Component.h"
#include "FBUtility.h"
#include <math.h>
#include <fstream>
#include "Parallel_node.h"
#include "SklUtil.h"
#include "vec3.h"
extern SklParaComponent* ParaCmpo;

enum Intrinsic_class {
  id_Users = 0,
  id_Duct,
  id_PPLT2D,
  id_SHC1D,
  id_PMT,
  id_Rect,
  id_Cylinder,
  id_Step,
  id_Polygon,
  id_Sphere
};

class Intrinsic : public Parallel_Node {

public:
  unsigned size[3];
  unsigned imax, jmax, kmax, guide;
  REAL_TYPE RefL;
  
  enum dim_mode {
    dim_2d = 1,
    dim_3d
  };
  
  Intrinsic() { 
    for (unsigned i=0; i<3; i++) size[i]=0.0;
    imax = jmax = kmax = guide = 0;
    RefL = 0.0;
  }
  virtual ~Intrinsic() {}
    
public:
  virtual bool getXML(SklSolverConfig* CF, Control* R) { return true; };
  
  virtual const char* getExampleName(void) { return NULL; };
  
  virtual void genVFfromBcx(REAL_TYPE* VF, unsigned* bx);
  virtual void initCond(REAL_TYPE* v, REAL_TYPE* p) {};
  virtual void PostInit(REAL_TYPE &checkTime, Control* R) {};
  virtual void printExample(FILE* fp, const char* str);
  virtual void printParaInfo(FILE* mp, FILE* fp, Control* R);
  virtual void printPara(FILE* fp, Control* R);
  virtual void setDomain(Control* R, unsigned sz[3], REAL_TYPE org[3], REAL_TYPE wth[3], REAL_TYPE pch[3]) {};
  virtual void setup(int* mid, Control* R, REAL_TYPE* G_org) {};
  virtual void setup_cut(int* mid, Control* R, REAL_TYPE* G_org, float* cut) {};
  virtual void writeSVX(REAL_TYPE *vf, int *id, Control* R);
  virtual void writeSVX(int *id, Control* R);
  
  void setControlVars(Control* R);
};
#endif // _SKL_FB_INTRNSC_H_
