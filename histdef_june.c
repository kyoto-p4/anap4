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
    HBOOK1(10+i,hnam,256,0.,4096.,0);
    sprintf(hnam,"ENERGY %02d",i);
    HBOOK1(10+N_QDC+i,hnam,1000,0.,40.,0);
  }
  for(i=0;i<N_TDC;i++){
    sprintf(hnam,"TDC %02d",i);
    HBOOK1(30+i,hnam,2048,0.,2048.,0);
  }
  for(i=0;i<N_TDC;i++){ 
    sprintf(hnam,"TPOSITION %02d",i);
    HBOOK1(40+i,hnam,300,-150.,150.,0);
  }
  HBOOK1(50,"lnL/R",160,-2.,2.,0);
  HBOOK2(51,"lnL/R vs TPOSITION",256,-2.,2.,256,-150.,150.,0);
  HBOOK2(60,"TPOSITION vs QDC0",256,-150.,150.,256,0.,1024.,0);
  HBOOK2(61,"TPOSITION vs QDC1",256,-150.,150.,256,0.,1024.,0);
  HBOOK2(62,"QDC3 vs QDC4",256,0.,1024.,256,0.,1024.,0);
  HBOOK1(63,"TPOSITION ver liqsin",256,-128.,128,0);
  HBOOK2(64,"QDC2off vs QDC3off",256,0.,2048.,256,0.,2048.,0);
  HBOOK1(65,"QDC3off/QDC2off",200,0.,2,0);
  HBOOK2(66,"QDC2off vs QDC3off TH200 ch",256,0.,2048.,256,0.,2048.,0);

  //  HBOOK2(70,"QDC0 vs TDC0",256,0.,4096.,256,0.,4096.,0);

  for(i=0;i < N_USE;i++){
    sprintf(hnam,"QDC%d vs TDC%d",i,i+1);
    HBOOK2(70+i,hnam,256,0.,4096.,256,0.,2048.,0);
  } 


  return(1);
}
