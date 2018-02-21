
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
  }
  for(i=0;i<N_TDC;i++){
    sprintf(hnam,"TDC %02d",i);
    HBOOK1(20+i,hnam,4096,0.,4096.,0);
  }
  
  for(i=0;i<N_ADC;i++){
    sprintf(hnam,"ADC %02d",i);
    HBOOK1(30+i,hnam,4096,0.,4096.,0);
  }

  HBOOK2(40,"slow vs fast",512,0.,1536.,512,0.,512.,0);
  HBOOK2(41,"slow vs fast(kevee)",128,0.,4096.,256,0.,2048.,0);
  HBOOK1(500,"PID 1800V 30cm(0.15MeV)",512,-100.,100.,0);
  HBOOK1(501,"PID 1800V 30cm(0.31MeV)",512,-100.,100.,0);
  HBOOK1(502,"PID 1800V 30cm(0.4MeV)",512,-100.,100.,0);
  HBOOK1(503,"PID 1800V 30cm(0.5MeV)",512,-100.,100.,0);
  HBOOK1(504,"PID 1800V 30cm(0.7MeV)",512,-100.,100.,0);
  HBOOK1(510,"PID 1800V 45cm(0.15MeV)",512,-100.,100.,0);
  HBOOK1(511,"PID 1800V 45cm(0.31MeV)",512,-100.,100.,0);
  HBOOK1(512,"PID 1800V 45cm(0.4MeV)",512,-100.,100.,0);
  HBOOK1(513,"PID 1800V 45cm(0.5MeV)",512,-100.,100.,0);
  HBOOK1(514,"PID 1800V 45cm(0.7MeV)",512,-100.,100.,0);
  HBOOK1(520,"PID 1800V 60cm(0.15MeV)",512,-100.,100.,0);
  HBOOK1(521,"PID 1800V 60cm(0.31MeV)",512,-100.,100.,0);
  HBOOK1(522,"PID 1800V 60cm(0.4MeV)",512,-100.,100.,0);
  HBOOK1(523,"PID 1800V 60cm(0.5MeV)",512,-100.,100.,0);
  HBOOK1(524,"PID 1800V 60cm(0.7MeV)",512,-100.,100.,0);
  HBOOK1(530,"PID 1600V 30cm(0.15MeV)",512,-100.,100.,0);
  HBOOK1(531,"PID 1600V 30cm(0.31MeV)",512,-100.,100.,0);
  HBOOK1(532,"PID 1600V 30cm(0.4MeV)",512,-100.,100.,0);
  HBOOK1(533,"PID 1600V 30cm(0.5MeV)",512,-100.,100.,0);
  HBOOK1(534,"PID 1600V 30cm(0.7MeV)",512,-100.,100.,0);
  HBOOK1(540,"PID 1600V 45cm(0.15MeV)",512,-100.,100.,0);
  HBOOK1(541,"PID 1600V 45cm(0.31MeV)",512,-100.,100.,0);
  HBOOK1(542,"PID 1600V 45cm(0.4MeV)",512,-100.,100.,0);
  HBOOK1(543,"PID 1600V 45cm(0.5MeV)",512,-100.,100.,0);
  HBOOK1(544,"PID 1600V 45cm(0.7MeV)",512,-100.,100.,0);
  HBOOK1(550,"PID 1600V 60cm(0.15MeV)",512,-100.,100.,0);
  HBOOK1(551,"PID 1600V 60cm(0.31MeV)",512,-100.,100.,0);
  HBOOK1(552,"PID 1600V 60cm(0.4MeV)",512,-100.,100.,0);
  HBOOK1(553,"PID 1600V 60cm(0.5MeV)",512,-100.,100.,0);
  HBOOK1(554,"PID 1600V 60cm(0.7MeV)",512,-100.,100.,0);
  HBOOK1(60,"1600V Compton Edge keVee",128,0.,4096.,0);
  HBOOK1(70,"1800V Compton Edge keVee",128,0.,4096.,0);
  HBOOK2(83,"PID曲線 1800V 30cm",128,0.,4096.,256,0.,2048.,0);
  HBOOK2(90,"slow vs fast",512,0.,512.,512,0.,1536.,0);
  HBOOK1(100,"PID2 1800V 30cm(0.15MeV)",64,-128.,128.,0);
  HBOOK1(101,"PID2 1800V 30cm(0.31MeV)",64,-128.,128.,0);
  HBOOK1(102,"PID2 1800V 30cm(0.4MeV)",64,-128.,128.,0);
  HBOOK1(103,"PID2 1800V 30cm(0.5MeV)",64,-128.,128.,0);
  HBOOK1(104,"PID2 1800V 30cm(0.7MeV)",64,-128.,128.,0);
  HBOOK2(120,"slow vs fast(neutron)",512,0.,1536.,512,0.,512.,0);

  
  

  return(1);
}
