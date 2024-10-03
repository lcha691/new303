/*
 * Automatically generated C code by
 * KIELER SCCharts - The Key to Efficient Modeling
 *
 * http://rtsys.informatik.uni-kiel.de/kieler
 */

#include "timing.h"
#include <stdio.h>
#include "sccharts.h"

void logic(TickData* d) {
  d->VRP_ACTIVE = 0;
  d->URI_ACTIVE = 0;
  d->PVARP_ACTIVE = 0;
  d->LRI_ACTIVE = 0;
  d->AP = 0;
  d->VP = 0;
  d->_g83 = d->_pg69;
  if (d->_g83) {
    d->VRP_ACTIVE |= 1;
  }
  d->_pre_VP = d->_reg_VP;
  d->_g15 = d->_pg12;
  d->_g9 = d->_pg24;
  d->_g10_e1 = !(d->_g15 || d->_g9);
  d->_cg9 = d->VS || d->_pre_VP && !d->VRP_ACTIVE;
  d->_g142 = d->_pg107;
  d->_g143 = d->_g142 && d->VS;
  if (d->_g143) {
    d->_pacemaker_local__Atrig4 = 1;
  }
  d->_g112 = d->_pg144_e3;
  d->_cg112 = d->_pacemaker_local__Atrig4;
  d->_g114 = d->_g112 && !d->_cg112;
  if (d->_g114) {
    d->URI_ACTIVE |= 1;
  }
  d->_g198 = d->_pg150;
  if (d->_g198) {
    d->_region0_null_x += d->deltaT;
  }
  d->_g19 = d->_pg7;
  d->_cg19 = d->VS || d->_pre_VP && !d->VRP_ACTIVE;
  d->_g21 = d->_g19 && !d->_cg19;
  d->_cg21 = d->_region0_null_x >= AVI_VALUE && !d->URI_ACTIVE;
  d->_g22 = d->_g21 && d->_cg21;
  if (d->_g22) {
    d->_pacemaker_local__Atrig = 1;
  }
  d->sleepT = 1000.0;
  d->_cg15 = d->VS || d->_pre_VP && !d->VRP_ACTIVE;
  d->_g11 = d->_g9 && !d->_cg9 || d->_g15 && !d->_cg15;
  d->_cg11 = d->_region0_null_x < AVI_VALUE;
  d->_g12 = d->_g11 && d->_cg11;
  if (d->_g12) {
    d->sleepT = (d->sleepT < (AVI_VALUE - d->_region0_null_x)) ? d->sleepT : (AVI_VALUE - d->_region0_null_x);
  }
  d->_cg12 = d->_pacemaker_local__Atrig;
  d->_g11 = d->_g11 && !d->_cg11;
  d->_cg13 = d->_pacemaker_local__Atrig;
  d->_g15 = d->_g9 && d->_cg9 || d->_g12 && d->_cg12 || d->_g11 && d->_cg13 || d->_g15 && d->_cg15;
  d->_g9 = !d->_g19;
  d->_g22 = d->_g19 && d->_cg19 || d->_g22;
  d->_g19 = (d->_g10_e1 || d->_g15) && (d->_g9 || d->_g22) && (d->_g15 || d->_g22);
  d->_cg23 = d->VS || d->_pre_VP && !d->VRP_ACTIVE;
  d->_g10_e1 = d->_g19 && !d->_cg23;
  if (d->_g10_e1) {
    d->VP |= 1;
  }
  d->_g20 = d->_pg181_e2;
  if (d->_g20) {
    d->PVARP_ACTIVE |= 1;
  }
  d->_g10 = d->_pg28;
  d->_g20_e2 = d->_pg47;
  d->_g58_e1 = !(d->_g10 || d->_g20_e2);
  d->_cg57 = d->AS && !d->PVARP_ACTIVE;
  d->_g206 = d->_pg164;
  if (d->_g206) {
    d->_region2_null_x += d->deltaT;
  }
  d->_g67 = d->_pg71;
  d->_cg67 = d->AS && !d->PVARP_ACTIVE;
  d->_g69 = d->_g67 && !d->_cg67;
  d->_cg69 = d->_region2_null_x >= AEI_VALUE;
  d->_g70 = d->_g69 && d->_cg69;
  if (d->_g70) {
    d->_pacemaker_local__Atrig2 = 1;
  }
  d->_cg63 = d->AS && !d->PVARP_ACTIVE;
  d->_g59 = d->_g20_e2 && !d->_cg57 || d->_g10 && !d->_cg63;
  d->_cg59 = d->_region2_null_x < AEI_VALUE;
  d->_g60 = d->_g59 && d->_cg59;
  if (d->_g60) {
    d->sleepT = (d->sleepT < (AEI_VALUE - d->_region2_null_x)) ? d->sleepT : (AEI_VALUE - d->_region2_null_x);
  }
  d->_cg60 = d->_pacemaker_local__Atrig2;
  d->_g59 = d->_g59 && !d->_cg59;
  d->_cg61 = d->_pacemaker_local__Atrig2;
  d->_g63 = d->_g20_e2 && d->_cg57 || d->_g60 && d->_cg60 || d->_g59 && d->_cg61 || d->_g10 && d->_cg63;
  d->_g57 = !d->_g67;
  d->_g67 = d->_g67 && d->_cg67 || d->_g70;
  d->_g70 = (d->_g58_e1 || d->_g63) && (d->_g57 || d->_g67) && (d->_g63 || d->_g67);
  d->_cg71 = d->AS && !d->PVARP_ACTIVE;
  d->_g58_e1 = d->_g70 && !d->_cg71;
  if (d->_g58_e1) {
    d->AP |= 1;
  }
  d->_g68_e2 = d->_pg68;
  d->_cg4 = d->AS || d->AP;
  d->_g68 = d->_GO || d->_g19 && d->_cg23 || d->_g10_e1 || d->_g68_e2 && !d->_cg4;
  d->_g58 = d->_g68_e2 && d->_cg4;
  if (d->_g58) {
    d->_region0_null_x = 0;
    d->_pacemaker_local__Atrig = 0;
  }
  d->_cg6 = d->_region0_null_x < AVI_VALUE;
  d->_g23 = d->_g58 && d->_cg6;
  if (d->_g23) {
    d->sleepT = (d->sleepT < (AVI_VALUE - d->_region0_null_x)) ? d->sleepT : (AVI_VALUE - d->_region0_null_x);
  }
  d->_cg7 = d->_pacemaker_local__Atrig;
  d->_g24 = d->_g23 && !d->_cg7 || d->_g12 && !d->_cg12;
  d->_g4 = d->_g58 && !d->_cg6;
  d->_cg16 = d->_pacemaker_local__Atrig;
  d->_g12 = d->_g11 && !d->_cg13 || d->_g4 && !d->_cg16;
  d->_g7 = d->_g58 || d->_g21 && !d->_cg21;
  d->_g16 = d->_pg157;
  if (d->_g16) {
    d->_region1_null_x += d->deltaT;
  }
  d->_g13 = d->_pg41;
  d->_cg46 = d->_region1_null_x >= PVARP_VALUE;
  d->_g5 = d->_g13 && d->_cg46;
  if (d->_g5) {
    d->_pacemaker_local__Atrig1 = 1;
  }
  d->_g21 = d->_pg108;
  d->_g155 = d->_pg125;
  d->_g167 = d->_pg145;
  d->_g161 = d->_pg130;
  d->_g176_e1 = !(d->_g21 || d->_g155 || d->_g167 || d->_g161);
  d->_g185 = d->_pg190;
  d->_cg185 = d->VP || d->VS;
  d->_g186 = d->_g185 && d->_cg185;
  if (d->_g186) {
    d->_pacemaker_local__Atrig6 = 1;
  }
  d->_g156_e1 = !d->_g155;
  d->_cg155 = d->_pacemaker_local__Atrig6;
  d->_g180 = d->_pg189;
  d->_cg180 = d->_pacemaker_local__Atrig6;
  d->_g182 = d->_g180 && !d->_cg180;
  if (d->_g182) {
    d->_pacemaker_local_x2 += d->deltaT;
  }
  d->_cg171 = d->_pacemaker_local__Atrig6;
  d->_g173 = d->_g21 && !d->_cg171;
  d->_cg173 = d->_pacemaker_local_x2 >= LRI_VALUE;
  d->_g174 = d->_g173 && d->_cg173;
  if (d->_g174) {
    d->_pacemaker_local__Atrig7 = 1;
  }
  d->_g157 = d->_g155 && !d->_cg155;
  if (d->_g157) {
    d->LRI_ACTIVE |= 1;
  }
  d->_cg157 = d->_pacemaker_local__Atrig7;
  d->_g155 = d->_g155 && d->_cg155 || d->_g157 && d->_cg157;
  d->_g162_e2 = !(d->_g167 || d->_g161);
  d->_cg161 = d->_pacemaker_local__Atrig6;
  d->_cg167 = d->_pacemaker_local__Atrig6;
  d->_g163 = d->_g161 && !d->_cg161 || d->_g167 && !d->_cg167;
  d->_cg163 = d->_pacemaker_local_x2 < LRI_VALUE;
  d->_g164 = d->_g163 && d->_cg163;
  if (d->_g164) {
    d->sleepT = (d->sleepT < (LRI_VALUE - d->_pacemaker_local_x2)) ? d->sleepT : (LRI_VALUE - d->_pacemaker_local_x2);
  }
  d->_cg164 = d->_pacemaker_local__Atrig7;
  d->_g163 = d->_g163 && !d->_cg163;
  d->_cg165 = d->_pacemaker_local__Atrig7;
  d->_g167 = d->_g161 && d->_cg161 || d->_g164 && d->_cg164 || d->_g163 && d->_cg165 || d->_g167 && d->_cg167;
  d->_g161 = !d->_g21;
  d->_g174 = d->_g21 && d->_cg171 || d->_g174;
  d->_g171 = (d->_g156_e1 || d->_g155) && (d->_g162_e2 || d->_g167) && (d->_g161 || d->_g174) && (d->_g155 || d->_g167 || d->_g174);
  d->_cg175 = d->_pacemaker_local__Atrig6;
  d->_g156 = d->_g171 && !d->_cg175;
  if (d->_g156) {
    d->_pacemaker_local__CFSterm2 = 1;
  }
  d->_g156_e1 = d->_g171 && d->_cg175 || d->_g156;
  d->_g172 = !d->_g180;
  d->_cg182 = d->_pacemaker_local__CFSterm2;
  d->_g172_e3 = d->_g180 && d->_cg180 || d->_g182 && d->_cg182;
  d->_g162 = !d->_g185;
  d->_g162_e2 = d->_g185 && !d->_cg185;
  d->_cg188 = d->_pacemaker_local__CFSterm2;
  d->_g175 = d->_g186 || d->_g162_e2 && d->_cg188;
  d->_g177 = (d->_g176_e1 || d->_g156_e1) && (d->_g172 || d->_g172_e3) && (d->_g162 || d->_g175) && (d->_g156_e1 || d->_g172_e3 || d->_g175);
  d->_cg189 = d->_pacemaker_local__Atrig6;
  d->_g180 = d->_g177 && !d->_cg189;
  if (d->_g180) {
    d->VP |= 1;
  }
  d->_g185 = d->_pg47_e3;
  d->_cg28 = d->VS || d->VP;
  d->_g186 = d->_g185 && d->_cg28;
  if (d->_g186) {
    d->_region1_null_x = 0;
    d->_pacemaker_local__Atrig1 = 0;
  }
  d->_g181 = d->_g186 || d->_g20;
  d->_cg31 = d->_pacemaker_local__Atrig1;
  d->_g181_e2 = d->_g181 && !d->_cg31;
  d->_g187 = !d->_g181_e2;
  d->_g176 = d->_g181 && d->_cg31;
  d->_g187_e3 = d->_pg36;
  d->_g176_e1 = d->_pg40;
  d->_g34 = d->_g186 || d->_g187_e3 || d->_g176_e1;
  d->_cg36 = d->_region1_null_x < PVARP_VALUE;
  d->_g31 = d->_g34 && !d->_cg36;
  d->_cg41 = d->_pacemaker_local__Atrig1;
  d->_g40 = d->_g31 && !d->_cg41;
  d->_g43 = d->_g34 && d->_cg36;
  if (d->_g43) {
    d->sleepT = (d->sleepT < (PVARP_VALUE - d->_region1_null_x)) ? d->sleepT : (PVARP_VALUE - d->_region1_null_x);
  }
  d->_cg37 = d->_pacemaker_local__Atrig1;
  d->_g36 = d->_g43 && !d->_cg37;
  d->_g38_e2 = !(d->_g40 || d->_g36);
  d->_g37 = d->_g43 && d->_cg37 || d->_g31 && d->_cg41;
  d->_g41 = d->_g186 || d->_g13 && !d->_cg46;
  d->_g46 = !d->_g41;
  d->_g29 = (d->_g187 || d->_g176) && (d->_g38_e2 || d->_g37) && (d->_g46 || d->_g5) && (d->_g176 || d->_g37 || d->_g5);
  d->_g47_e3 = d->_GO || d->_g29 || d->_g185 && !d->_cg28;
  d->_g38 = d->_pg32;
  d->_cg52 = d->VS || d->VP;
  d->_g32 = d->_GO || d->_g70 && d->_cg71 || d->_g58_e1 || d->_g38 && !d->_cg52;
  d->_g38_e2 = d->_g38 && d->_cg52;
  if (d->_g38_e2) {
    d->_region2_null_x = 0;
    d->_pacemaker_local__Atrig2 = 0;
  }
  d->_cg54 = d->_region2_null_x < AEI_VALUE;
  d->_g32_e1 = d->_g38_e2 && d->_cg54;
  if (d->_g32_e1) {
    d->sleepT = (d->sleepT < (AEI_VALUE - d->_region2_null_x)) ? d->sleepT : (AEI_VALUE - d->_region2_null_x);
  }
  d->_cg55 = d->_pacemaker_local__Atrig2;
  d->_g47 = d->_g32_e1 && !d->_cg55 || d->_g60 && !d->_cg60;
  d->_g48 = d->_g38_e2 && !d->_cg54;
  d->_cg64 = d->_pacemaker_local__Atrig2;
  d->_g28 = d->_g59 && !d->_cg61 || d->_g48 && !d->_cg64;
  d->_g71 = d->_g38_e2 || d->_g69 && !d->_cg69;
  d->_g72 = d->_pg77;
  d->_cg76 = d->VS || d->VP;
  d->_g52 = d->_g72 && d->_cg76;
  if (d->_g52) {
    d->_pacemaker_local_x = 0;
    d->_pacemaker_local__CFSterm = 0;
    d->_pacemaker_local__Atrig3 = 0;
  }
  d->_g55 = d->_pg81_e1;
  if (d->_g55) {
    d->_pacemaker_local_x += d->deltaT;
  }
  d->_g60 = d->_pg64;
  d->_cg95 = d->_pacemaker_local_x >= VRP_VALUE;
  d->_g64 = d->_g52 || d->_g60 && !d->_cg95;
  d->_g61 = d->_g60 && d->_cg95;
  if (d->_g61) {
    d->_pacemaker_local__Atrig3 = 1;
  }
  d->_g53 = d->_g52 || d->_g83;
  d->_cg80 = d->_pacemaker_local__Atrig3;
  d->_g69 = d->_g53 && !d->_cg80;
  d->_g95 = d->_pg88;
  d->_g83 = d->_pg91;
  d->_g92 = d->_g52 || d->_g95 || d->_g83;
  d->_cg85 = d->_pacemaker_local_x < VRP_VALUE;
  d->_g89 = d->_g92 && !d->_cg85;
  d->_cg90 = d->_pacemaker_local__Atrig3;
  d->_g91 = d->_g89 && !d->_cg90;
  d->_g85 = d->_g92 && d->_cg85;
  if (d->_g85) {
    d->sleepT = (d->sleepT < (VRP_VALUE - d->_pacemaker_local_x)) ? d->sleepT : (VRP_VALUE - d->_pacemaker_local_x);
  }
  d->_cg86 = d->_pacemaker_local__Atrig3;
  d->_g88 = d->_g85 && !d->_cg86;
  d->_g97_e1 = !(d->_g64 || d->_g69 || d->_g91 || d->_g88);
  d->_g81_e1 = !d->_g69;
  d->_g80 = d->_g53 && d->_cg80;
  d->_g87_e2 = !(d->_g91 || d->_g88);
  d->_g86 = d->_g85 && d->_cg86 || d->_g89 && d->_cg90;
  d->_g90 = !d->_g64;
  d->_g96_e3 = (d->_g81_e1 || d->_g80) && (d->_g87_e2 || d->_g86) && (d->_g90 || d->_g61) && (d->_g80 || d->_g86 || d->_g61);
  if (d->_g96_e3) {
    d->_pacemaker_local__CFSterm = 1;
  }
  d->_g96 = d->_g52 || d->_g55;
  d->_cg99 = d->_pacemaker_local__CFSterm;
  d->_g81_e1 = d->_g96 && !d->_cg99;
  d->_g87 = !d->_g81_e1;
  d->_g81 = d->_g96 && d->_cg99;
  d->_g87_e2 = (d->_g97_e1 || d->_g96_e3) && (d->_g87 || d->_g81) && (d->_g96_e3 || d->_g81);
  d->_g77 = d->_GO || d->_g87_e2 || d->_g72 && !d->_cg76;
  d->_g102 = d->_pg138_e2;
  d->_g99 = d->_pg133_e1;
  d->_g100_e2 = d->_pg144;
  d->_g97 = !(d->_g102 || d->_g112 || d->_g99 || d->_g100_e2);
  d->_g100 = !d->_g112;
  d->_g97_e1 = d->_pg146;
  d->_cg137 = d->_pacemaker_local__Atrig4;
  d->_g103 = d->_g97_e1 && !d->_cg137;
  if (d->_g103) {
    d->_pacemaker_local_x1 += d->deltaT;
  }
  d->_cg128 = d->_pacemaker_local__Atrig4;
  d->_g76 = d->_g102 && !d->_cg128;
  d->_cg130 = d->_pacemaker_local_x1 >= URI_VALUE;
  d->_g131 = d->_g76 && d->_cg130;
  if (d->_g131) {
    d->_pacemaker_local__Atrig5 = 1;
  }
  d->_cg114 = d->_pacemaker_local__Atrig5;
  d->_g112 = d->_g112 && d->_cg112 || d->_g114 && d->_cg114;
  d->_g119_e2 = !(d->_g99 || d->_g100_e2);
  d->_cg118 = d->_pacemaker_local__Atrig4;
  d->_cg124 = d->_pacemaker_local__Atrig4;
  d->_g120 = d->_g100_e2 && !d->_cg118 || d->_g99 && !d->_cg124;
  d->_cg120 = d->_pacemaker_local_x1 < URI_VALUE;
  d->_g121 = d->_g120 && d->_cg120;
  if (d->_g121) {
    d->sleepT = (d->sleepT < (URI_VALUE - d->_pacemaker_local_x1)) ? d->sleepT : (URI_VALUE - d->_pacemaker_local_x1);
  }
  d->_cg121 = d->_pacemaker_local__Atrig5;
  d->_g120 = d->_g120 && !d->_cg120;
  d->_cg122 = d->_pacemaker_local__Atrig5;
  d->_g124 = d->_g100_e2 && d->_cg118 || d->_g121 && d->_cg121 || d->_g120 && d->_cg122 || d->_g99 && d->_cg124;
  d->_g118 = !d->_g102;
  d->_g131 = d->_g102 && d->_cg128 || d->_g131;
  d->_g128 = (d->_g100 || d->_g112) && (d->_g119_e2 || d->_g124) && (d->_g118 || d->_g131) && (d->_g112 || d->_g124 || d->_g131);
  d->_cg132 = d->_pacemaker_local__Atrig4;
  d->_g113 = d->_g128 && !d->_cg132;
  if (d->_g113) {
    d->_pacemaker_local__CFSterm1 = 1;
  }
  d->_g129 = d->_g128 && d->_cg132 || d->_g113;
  d->_g113_e1 = !d->_g97_e1;
  d->_cg139 = d->_pacemaker_local__CFSterm1;
  d->_g119 = d->_g97_e1 && d->_cg137 || d->_g103 && d->_cg139;
  d->_g129_e3 = !d->_g142;
  d->_g119_e2 = d->_g142 && !d->VS;
  d->_cg145 = d->_pacemaker_local__CFSterm1;
  d->_g134 = d->_g143 || d->_g119_e2 && d->_cg145;
  d->_g132 = (d->_g97 || d->_g129) && (d->_g113_e1 || d->_g119) && (d->_g129_e3 || d->_g134) && (d->_g129 || d->_g119 || d->_g134);
  d->_cg146 = d->_pacemaker_local__Atrig4;
  d->_g137 = d->_pg142;
  d->_cg107 = d->VP || d->VS;
  d->_g142 = d->_GO || d->_g132 && !d->_cg146 || d->_g137 && !d->_cg107;
  d->_g143 = d->_g137 && d->_cg107 || d->_g132 && d->_cg146;
  if (d->_g143) {
    d->_pacemaker_local_x1 = 0;
    d->_pacemaker_local__CFSterm1 = 0;
    d->_pacemaker_local__Atrig4 = 0;
    d->_pacemaker_local__Atrig5 = 0;
  }
  d->_cg110 = d->_pacemaker_local__Atrig5;
  d->_g144_e3 = d->_g143 && !d->_cg110 || d->_g114 && !d->_cg114;
  d->_cg115 = d->_pacemaker_local_x1 < URI_VALUE;
  d->_g133 = d->_g143 && d->_cg115;
  if (d->_g133) {
    d->sleepT = (d->sleepT < (URI_VALUE - d->_pacemaker_local_x1)) ? d->sleepT : (URI_VALUE - d->_pacemaker_local_x1);
  }
  d->_cg116 = d->_pacemaker_local__Atrig5;
  d->_g144 = d->_g133 && !d->_cg116 || d->_g121 && !d->_cg121;
  d->_g138 = d->_g143 && !d->_cg115;
  d->_cg125 = d->_pacemaker_local__Atrig5;
  d->_g133_e1 = d->_g120 && !d->_cg122 || d->_g138 && !d->_cg125;
  d->_g138_e2 = d->_g143 || d->_g76 && !d->_cg130;
  d->_cg135 = d->_pacemaker_local__CFSterm1;
  d->_g146 = d->_g143 && !d->_cg135 || d->_g103 && !d->_cg139;
  d->_g107 = d->_g143 || d->_g119_e2 && !d->_cg145;
  d->_g114 = d->_pg116;
  d->_cg150 = d->VP || d->VS;
  d->_g116 = d->_GO || d->_g114 && !d->_cg150;
  d->_g121 = d->_g114 && d->_cg150 || d->_g177 && d->_cg189 || d->_g180;
  if (d->_g121) {
    d->_pacemaker_local_x2 = 0;
    d->_pacemaker_local__CFSterm2 = 0;
    d->_pacemaker_local__Atrig6 = 0;
    d->_pacemaker_local__Atrig7 = 0;
  }
  d->_cg153 = d->_pacemaker_local__Atrig7;
  d->_g125 = d->_g121 && !d->_cg153 || d->_g157 && !d->_cg157;
  d->_cg158 = d->_pacemaker_local_x2 < LRI_VALUE;
  d->_g122 = d->_g121 && d->_cg158;
  if (d->_g122) {
    d->sleepT = (d->sleepT < (LRI_VALUE - d->_pacemaker_local_x2)) ? d->sleepT : (LRI_VALUE - d->_pacemaker_local_x2);
  }
  d->_cg159 = d->_pacemaker_local__Atrig7;
  d->_g130 = d->_g122 && !d->_cg159 || d->_g164 && !d->_cg164;
  d->_g139 = d->_g121 && !d->_cg158;
  d->_cg168 = d->_pacemaker_local__Atrig7;
  d->_g145 = d->_g163 && !d->_cg165 || d->_g139 && !d->_cg168;
  d->_g108 = d->_g121 || d->_g173 && !d->_cg173;
  d->_cg178 = d->_pacemaker_local__CFSterm2;
  d->_g189 = d->_g121 && !d->_cg178 || d->_g182 && !d->_cg182;
  d->_g190 = d->_g121 || d->_g162_e2 && !d->_cg188;
  d->_g150 = d->_GO || d->_g198;
  d->_g157 = d->_GO || d->_g16;
  d->_g164 = d->_GO || d->_g206;
  d->_reg_VP = d->VP;
}

void reset(TickData* d) {
  d->_GO = 1;
  d->_TERM = 0;
  d->_region0_null_x = 0;
  d->_region1_null_x = 0;
  d->_region2_null_x = 0;
  d->deltaT = 0.0;
  d->sleepT = 0.0;
  d->_reg_VP = 0;
  d->_pg69 = 0;
  d->_pg12 = 0;
  d->_pg24 = 0;
  d->_pg107 = 0;
  d->_pg144_e3 = 0;
  d->_pg150 = 0;
  d->_pg7 = 0;
  d->_pg181_e2 = 0;
  d->_pg28 = 0;
  d->_pg47 = 0;
  d->_pg164 = 0;
  d->_pg71 = 0;
  d->_pg68 = 0;
  d->_pg157 = 0;
  d->_pg41 = 0;
  d->_pg108 = 0;
  d->_pg125 = 0;
  d->_pg145 = 0;
  d->_pg130 = 0;
  d->_pg190 = 0;
  d->_pg189 = 0;
  d->_pg47_e3 = 0;
  d->_pg36 = 0;
  d->_pg40 = 0;
  d->_pg32 = 0;
  d->_pg77 = 0;
  d->_pg81_e1 = 0;
  d->_pg64 = 0;
  d->_pg88 = 0;
  d->_pg91 = 0;
  d->_pg138_e2 = 0;
  d->_pg133_e1 = 0;
  d->_pg144 = 0;
  d->_pg146 = 0;
  d->_pg142 = 0;
  d->_pg116 = 0;
}

void tick(TickData* d) {
  logic(d);

  d->_pg69 = d->_g69;
  d->_pg12 = d->_g12;
  d->_pg24 = d->_g24;
  d->_pg107 = d->_g107;
  d->_pg144_e3 = d->_g144_e3;
  d->_pg150 = d->_g150;
  d->_pg7 = d->_g7;
  d->_pg181_e2 = d->_g181_e2;
  d->_pg28 = d->_g28;
  d->_pg47 = d->_g47;
  d->_pg164 = d->_g164;
  d->_pg71 = d->_g71;
  d->_pg68 = d->_g68;
  d->_pg157 = d->_g157;
  d->_pg41 = d->_g41;
  d->_pg108 = d->_g108;
  d->_pg125 = d->_g125;
  d->_pg145 = d->_g145;
  d->_pg130 = d->_g130;
  d->_pg190 = d->_g190;
  d->_pg189 = d->_g189;
  d->_pg47_e3 = d->_g47_e3;
  d->_pg36 = d->_g36;
  d->_pg40 = d->_g40;
  d->_pg32 = d->_g32;
  d->_pg77 = d->_g77;
  d->_pg81_e1 = d->_g81_e1;
  d->_pg64 = d->_g64;
  d->_pg88 = d->_g88;
  d->_pg91 = d->_g91;
  d->_pg138_e2 = d->_g138_e2;
  d->_pg133_e1 = d->_g133_e1;
  d->_pg144 = d->_g144;
  d->_pg146 = d->_g146;
  d->_pg142 = d->_g142;
  d->_pg116 = d->_g116;
  d->_GO = 0;
}
