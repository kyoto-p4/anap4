#include <stdio.h>
#include <cfortran.h>
#include <kernlib.h>
#include <hbook.h>
#include "anap4.h"


int histdef(){
  int i;
  char hnam[100];

  for(i=0;i<N_QDC;i++){
    sprintf(hnam,"QDC %02d",i);
    HBOOK1(10+i,hnam,4096,0.,4096.,0);
    sprintf(hnam,"ENERGY %02d",i);
    HBOOK1(10+N_QDC+i,hnam,1000,0.,40.,0);
  }
  for(i=0;i<N_TDC;i++){
    sprintf(hnam,"TDC %02d",i);
    HBOOK1(20+i,hnam,4096,0.,4096.,0);
  }
  for(i=0;i<N_ADC;i++){
    sprintf(hnam,"ADC %02d",i);
    HBOOK1(30+i,hnam,4096,0.,4096.,0);
    //sprintf(hnam,"ADC %02d_coincident",i);
    // HBOOK1(30+N_ADC+i,hnam,4096,0.,4096.,0);
  }
  HBOOK1(40,"ssdhitpattern",N_ADC,0,N_ADC,0);
  //  HBOOK2(40,"ADC1 vs ADC2",4096,0.,4096.,4096,0.,4096.,0);
  // HBOOK1(41,"count",4096,-1.,3.,0);
  //  HBOOK1(25,"TDCdiff",4096,0.,8192.,0);
  //HBOOK1(50,"60Co 1.33MeV",4096,0.,4096.,0);
  //HBOOK1(51,"60Co 1.17MeV",4096,0.,4096.,0);
  //HBOOK2(61,"tdc00 vs tdc01",128,0.,4096.,128,0.,4096.,0);
  //  HBOOK1(30,"times",256,0.,1024.,0);
  //  HBOOK1(31,"devide",256,0.,1024.,0);
  //  HBOOK2(32,"v_l/v_r vs v_l",256,0.,1024.,256,0.,1024.,0);
  //  HBOOK2(33,"v_l/v_r vs v_r",256,0.,1024.,256,0.,1024.,0);
  //  HBOOK2(35,"qx vs tx",256,-64.,64.,256,-64.,64.,0);
  //  HBOOK1(36,"qx",256,-64.,64.,0);
  //  HBOOK1(37,"tx",256,-64.,64.,0);
  //  HBOOK2(38,"TDCdiff vs QDC3",4096,4096.,8192.,4096,0.,4096.,0);
  // HBOOK2(40,"adc1 vs adc2",256,0.,4096.,256,0.,4096.,0);
  
  //HBOOK2(60,"thr",256,0.,4096,256,-4000.,2500.,0);
  return(1);
}
