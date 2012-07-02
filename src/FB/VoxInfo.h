#ifndef _FB_BINVOX_H_
#define _FB_BINVOX_H_

// #################################################################
//
// CAERU Library
//
// Copyright (c) All right reserved. 2012
//
// Institute of Industrial Science, The University of Tokyo, Japan. 
//
// #################################################################

/** 
 * @file   VoxInfo.h
 * @brief  FlowBase VoxInfo class Header
 * @author kero
 */

#include <math.h>
#include <cstdlib>

#include "cpm_Define.h"
#include "cpm_ParaManager.h"

#include "DomainInfo.h"
#include "FBUtility.h"
#include "Component.h"
#include "Medium.h"
#include "SetBC.h"
#include "BndOuter.h"
#include "vec3.h"
#include "CompoFraction.h"

#include "Polylib.h"
#include "MPIPolylib.h"

#include "mpi.h"
#include "limits.h"

class VoxInfo : public DomainInfo {
  
private:
  int NoBC;                      ///< 境界条件数
  int NoCompo;                   ///< コンポーネントの総数
  int NoVoxID;                   ///< 含まれるIDの数(Local/Global)
  int colorList[MODEL_ID_MAX+1]; ///< ボクセルモデルに含まれるIDのリスト(Global)

public:
  /** コンストラクタ */
  VoxInfo() {
    NoVoxID = 0;
    NoBC = 0;
    NoCompo = 0;
    
    for (int i=0; i<MODEL_ID_MAX+1; i++) colorList[i]=0;
  }
  
  /**　デストラクタ */
  ~VoxInfo() {}
  
private:
  
  
  int* allocTable(int size);
  
  void checkColorTable       (FILE* fp, int size, int* table);
  
  
  /**
   * @brief 指定されたIDが計算領域内部にあるかどうかを判定する
   * @param [in] id サーチ対象ID
   * @param [in] mid ID配列
   * @retval IDがあればtrue
   */
  bool chkIDinside(const int id, const int* mid);
  
  /**
   * @brief 外部境界に接するガイドセルのmid[]にIDを内部周期境界からコピーする
   * @param [in/out] mid   ID配列のデータクラス
   * @param [in]     m_st  コンポーネントのbbox始点
   * @param [in]     m_ed  コンポーネントのbbox終点
   * @param [in]     m_id  対象のID
   * @param [in]     m_dir ドライバの方向
   */
  void copyID_Prdc_Inner(int* mid, const int* m_st, const int* m_ed, const int m_id, const int m_dir);
  
  
  unsigned long countState(int id, int* mid);
  
  unsigned long count_ValidCell_OBC (const int face, const int* bv);
  
  unsigned long encodeOrder(const int order,
                            const int id, 
                            const int* mid, 
                            int* bx);
  
  unsigned long encPbit_D_IBC(const int order, 
                              const int id, 
                              const int* mid, 
                              int* bcd, 
                              int* bcp, 
                              const int deface);
  
  unsigned long encPbit_N_Binary(int* bx);
  
  unsigned long encPbit_N_Cut(int* bx, const float* cut, const bool convergence);
  
  unsigned long encPbit_N_IBC(const int order, 
                              const int id, 
                              const int* mid, 
                              int* bcd, 
                              int* bcp, 
                              const int deface);
  
  unsigned long encQface(const int order, 
                         const int id, 
                         const int* mid, 
                         int* bcd, 
                         int* bh1, 
                         int* bh2, 
                         const int deface, 
                         const bool flag);
  
  unsigned long encQfaceHT_B(const int order, 
                             const int id, 
                             const int* mid, 
                             int* bcd, 
                             int* bh1, 
                             int* bh2, 
                             const int deface);
  
  unsigned long encQfaceHT_S(const int order, 
                             const int id, 
                             const int* mid, 
                             int* bcd, 
                             int* bh1, 
                             int* bh2, 
                             const int deface);
  
  unsigned long encQfaceISO_SF(const int order, 
                               const int id, 
                               const int* mid, 
                               int* bcd, 
                               int* bh1, 
                               int* bh2, 
                               const int deface);
  
  unsigned long encQfaceISO_SS(const int order, 
                               const int id, 
                               const int* mid, 
                               int* bcd, 
                               int* bh1, 
                               int* bh2, 
                               const int deface);
  
  unsigned long encVbit_IBC(const int order, 
                            const int id, 
                            const int* mid, 
                            int* bv, 
                            const int deface, 
                            int* bp);
  
  unsigned long encVbit_IBC_Cut(const int order, 
                                const int id, 
                                int* bv, 
                                int* bp, 
                                const float* cut, 
                                const int* cut_id, 
                                const float* vec, 
                                const int bc_dir);
  void encActive             (unsigned long& Lcell, unsigned long& Gcell, int* bx, const int KOS);
  void encAmask_SymtrcBC     (int face, int* bh2);
  void encHbit               (int* bh1, int* bh2);
  void encPbit               (int* bx);
  void encPbit_OBC           (int face, int* bx, string key, bool dir);
  void encQfaceSVO           (int order, int id, int* mid, int* bcd, int* bh1, int* bh2, int deface);
  void encVbit_OBC           (int face, int* bv, string key, const bool enc_sw, string chk, int* bp, const bool enc_uwd);
  
  
  void find_isolated_Fcell   (int order, int* mid, int* bx);
  
  
  /**
   * @brief cmp[]にエンコードされた媒質IDの中から対象となるIDのエントリを探す
   * @param [in] mat_id 対象とする媒質ID
   */
  int find_mat_odr(const int mat_id, CompoList* cmp);
  
  
  void getOffset             (int* st, int* ofst);
  
  
  bool isInTable             (int MaxSize, int* cList, int target);
  
  
  
  //@fn inline int offBit(int idx, const int shift)
  //@brief idxの第shiftビットをOFFにする
  inline int offBit(int idx, const int shift) {
    return ( idx & (~(0x1<<shift)) );
  }
  
  //@fn inline int onBit(int idx, const int shift)
  //@brief idxの第shiftビットをONにする
  inline int onBit(int idx, const int shift) {
    return ( idx | (0x1<<shift) );
  }
  
  
  
  
  void resizeBVcell          (const int* st, const int* ed, int n, int* bx, int* gcbv);
  void resizeBVface          (const int* st, const int* ed, int n, int* bx, int* gcbv);
  void setInactive_Compo     (int id, int def, int* mid, int* bh1, int* bh2);
  void setAmask_InActive     (int id, int* mid, int* bh);
  void setAmask_Solid        (int* bh);
  void setAmask_Thermal      (int* bh);
  void updateGlobalIndex     (const int* st, const int* ed, int n, int* gcbv);
  


  
  
public:
  
  /**
   * @brief 外部境界に接するガイドセルのmid[]に媒質インデクスをエンコードする
   * @param [in]     face      外部境界面番号
   * @param [in/out] mid       ID配列のデータクラス
   * @param [in]     BCtype    外部境界面の境界条件の種類
   * @param [in]     c_id      媒質インデクス
   * @param [in]     prdc_mode 周期境界条件のモード
   */
  void adjMedium_on_GC(const int face, int* mid, const int BCtype, const int c_id, const int prdc_mode);
  
  
  /**
   * @brief 外部境界に接するガイドセルのmid[]にIDをエンコードする（内部周期境界の場合）
   * @param [in/out] mid       ID配列のデータ
   * @param [in]     cmp        CompoList
   */
  void adjMediumPrdc_Inner(int* mid, CompoList* cmp);
  
  
  /**
   * @brief ペイント済みかどうかをチェックする
   * @param [in] mid ID配列
   * @note 未ペイントセルがあれば1を返す
   */
  int check_fill(const int* mid);
  
  /**
   * @brief パラメータファイルとスキャンしたIDの同一性をチェック
   * @param [in] m_NoMedium  Medium_Tableに記述されたIDの個数
   */
  bool chkIDconsistency      (const int m_NoMedium);
  
  
  void copyBCIbase           (int* dst, int* src);
  void countCellState        (unsigned long& Lcell, unsigned long& Gcell, int* bx, const int state);
  void countOpenAreaOfDomain (int* bx, REAL_TYPE* OpenArea);
  
  
  unsigned fill_cell_edge    (int* bid, int* mid, float* cut, const int tgt_id, const int solid_id);
  unsigned fill_inside       (int* mid, const int solid_id);
  
  unsigned test_opposite_cut (int* bid, int* mid, const int solid_id);
  
  unsigned long flip_InActive(unsigned long& L, 
                              unsigned long& G, 
                              const int id, 
                              const int* mid, 
                              int* bx);
  
  

  
  
  
  void fill_isolated_cells   (const int* bid, int* mid, const int isolated, const int solid_id);
  void findVIBCbbox          (const int id, const int* bv, int* st, int* ed);
  
  //@fn const int* getColorList() const
  //@retval colorListのポインタ
	const int* getColorList() const { return colorList; }
	
  
  //@brief CutBid5のBoundrary IDを計算
  //@note dir = (w/X_MINUS=0, e/X_PLUS=1, s/2, n/3, b/4, t/5)
  inline int get_BID5(const int dir, const int bid) {
    return ( (bid >> dir*5) & MASK_5 );
  }
  
  /**
   * @brief コンポーネントの断面積を求める
   * @param [in]     n   エントリ番号
   * @param [in/out] cmp CompoList
   * @param [int]    PL  MPIPolylibクラス
   */
  void get_Compo_Area_Cut(const int n, CompoList* cmp, const PolylibNS::MPIPolylib* PL);
  
  
  bool paint_first_seed      (int* mid, const int* idx, const int target);
  void printScanedCell       (FILE* fp);
  void resizeCompoBV         (int* bd, int* bv, int* bh1, int* bh2, int kos, bool isHeat, int* gcbv);
  
  

  /**
   * @brief cellで保持されるボクセルid配列をスキャンし，coloList[]に登録する
   * @return 含まれるセルIDの種類数
   * @param [in/out] cell       ボクセルIDを保持する配列
   * @param [in]     cid        セルIDリスト 
   * @param [in]     ID_replace ID=0を置換するID
   */ 
  int scanCell(int *cell, const int* cid, const int ID_replace);
  
  
  //@brief CutBid5のBoundrary ID設定
  //@note dir = (w/X_MINUS=0, e/X_PLUS=1, s/2, n/3, b/4, t/5)
  inline void set_BID5(int& bid, const int dir, const int s_id) {
    bid |= (s_id << (dir*5));
  }
  
  /**
   * @brief bx[]に各境界条件の共通のビット情報をエンコードする（その1）
   * @param [in/out] bx   BCindex ID
   * @param [in/out] mid  ID配列
   * @param [in]     cvf  コンポーネントの体積率
   * @param [in]     mat  MediumList
   * @param [in/out] cmp  CompoList
   * @note 事前に，cmp[]へMediumListへのエントリ番号をエンコードしておく -> cmp[].setMatOdr()
   */
  void setBCIndex_base1(int* bd, int* mid, const float* cvf, const MediumList* mat, CompoList* cmp);
  
  
  /**
   * @brief bx[]に各境界条件の共通のビット情報をエンコードする（その2）
   * @param [out]    bx    BCindex ID
   * @param [in/out] mid   ID配列
   * @param [in/out] Lcell ノードローカルの有効セル数
   * @param [in/out] Gcell グローバルの有効セル数
   * @param [in]     KOS   解くべき方程式の種類 KIND_OF_SOLVER
   * @param [in/out] cmp   CompoList
   */
  void setBCIndex_base2(int* bx, int* mid, unsigned long& Lcell, unsigned long& Gcell, const int KOS, CompoList* cmp);
  
  
  /**
   @brief 境界条件のビット情報をエンコードする
   @param [in/out] bcd BCindex ID
   @param [in/out] bh1 BCindex H1
   @param [in/out] bh1 BCindex H2
   @param [in/out] mid ID配列
   @param [in]     BC  SetBCクラスのポインタ
   @param [in]     kos KindOfSolver
   @param [in/out] cmp CompoList
   */
  void setBCIndexH(int* bcd, int* bh1, int* bh2, int* mid, SetBC* BC, const int kos, CompoList* cmp);
  
  
  /**
   @brief 圧力境界条件のビット情報をエンコードする
   @param [in/out] bcd   BCindex ID
   @param [in/out] bcp   BCindex P
   @param [in/out] mid   ID配列
   @param [in]     BC    SetBCクラスのポインタ
   @param [in]     isCDS CDS->true
   @param [in]     cut   距離情報
   @param [in/out] cmp   CompoList
   @retval 表面セル数
   */
  unsigned long setBCIndexP(int* bcd, int* bcp, int* mid, SetBC* BC, const bool isCDS, const float* cut, CompoList* cmp);
  
  
  void setBCIndexV(int* bv, int* mid, SetBC* BC, int* bp, CompoList* cmp, bool isCDS=false, float* cut=NULL, int* cut_id=NULL);
  
  void setCmpFraction        (CompoList* compo, int* bx, float* vf);
  
  void setAdiabatic4SF       (int* bh);
  
  
  void setNoCompo_BC         (int m_NoBC, int m_NoCompo);
  void setOBC_Cut            (SetBC* BC, float* cut);
  
  
  /**
   * @brief Cell_Monitorで指定するIDでモニタ部分を指定するためのしかけ
   * @param [in] mid  ID配列
   * @param [in] SM   ShapeMonitorクラス
   * @param [in] cmp  CompoListクラス
   * @param [in] RefL 代表長さ
   */
  void setShapeMonitor(int* mid, ShapeMonitor* SM, CompoList* cmp, const REAL_TYPE RefL);
  
  
  /**
   @brief ボクセルモデルにカット情報から得られた固体情報を転写する
   @param [in/out] mid セルID
   @param [in]     cut 距離情報
   @param [in]     id  固体ID 
   @retval 固体セル数
   */
  unsigned long Solid_from_Cut(int* mid, const float* cut, const int id);
  
  
  // ----> debug function
  
  /**
   * @brief BCindexを表示する（デバッグ用）
   * @param [in] bcd   BCindex D
   * @param [in] fname 出力用ファイル名
   */
  void dbg_chkBCIndexD  (const int* bcd, const char* fname);
  
  /**
   * @brief BCindexを表示する（デバッグ用）
   * @param [in] bcd   BCindex ID
   * @param [in] bcp   BCindex P
   * @param [in] fname 出力用ファイル名
   * @param [in] cmp CompoListクラス
   */
  void dbg_chkBCIndexP  (const int* bcd, const int* bcp, const char* fname, CompoList* cmp);
  
  void dbg_chkBCIndexV  (int* bcv, const char* fname);
};

#endif // _FB_BINVOX_H_
