#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cfortran.h>
#include <hbook.h>
#include <kernlib.h>

#include "kinema.h"
#include "anap4.h"

int anaevt(int evtlen,unsigned short *rawbuf,struct p4dat *dat){
  int i,ip,j;
  int segsize,ids,ips,ipsn,count;
  unsigned short qdc[N_QDC];
  unsigned short qdcoff[N_QDC];
  unsigned short tdc[N_TDC];
  unsigned short adc[N_ADC];
  double qdcc[N_QDC];
  double tdcc[N_TDC];
  double adcc[N_ADC];
  //const double qpar[N_QDC][2]={{0.0, 0.01}, {0.0, 0.01}};
  const double tpar[N_TDC][2];
  //unsigned short qdcp0[N_QDC]={0,30};
  char tmpbuf[200];
  double pede=0.;
  double kevee1600,kevee1800;
  double gamma83,gamma84,gamma86,gamma63,gamma64,gamma66,gamma1;

  /************* Clear Event Buffer *****************/
  for(i=0;i<N_QDC;i++) {
    qdc[i]=0;
    qdcc[i]=0.;
  }
  for(i=0;i<N_TDC;i++){
    tdc[i]=0;
    tdcc[i]=0.;
  }
  for(i=0;i<N_ADC;i++){
    adc[i]=0;
    adcc[i]=0.;
  }
  count=0;

  /************* Clear Event Buffer *****************/

  /************* Decode Event Data Here *****************/
  ip=0;
  while(ip<evtlen){  
    int tmpdat,tmpch;

    /** Segment Header ************/
    segsize=rawbuf[ip++];
    ipsn=ip+segsize-1;
    ids=rawbuf[ip++];

#if _DEBUG
    ips=0;
    printf(" New Seg %d\n",ids);
#endif

    while(ip<ipsn){ /*** Segment loop ***/
      /*** 7166 ****/
#if _DEBUG
      printf("  7166\n");
#endif
      for(i=0;i<N_QDC;i++) {
	tmpdat=rawbuf[ip++];
	tmpch=(tmpdat>>12)&0xf;
	qdc[i]=(tmpdat&0xfff);
#if _DEBUG
	sprintf(tmpbuf,"QDC:   %2d: %04x  ch:%02d  adc:%4d\n",i,tmpdat,tmpch,
		qdc[i]);
	dumpmsg(tmpbuf);
#endif
      }
      for(i=0;i<N_TDC;i++) {
	tmpdat=rawbuf[ip++];
	tmpch=(tmpdat>>12)&0xf;
	tdc[i]=(tmpdat&0xfff);
#if _DEBUG
	sprintf(tmpbuf,"TDC:   %2d: %04x  ch:%02d  adc:%4d\n",i,tmpdat,tmpch,
		tdc[i]);
	dumpmsg(tmpbuf);
#endif
      }
      for(i=0;i<N_ADC;i++) {
	tmpdat=rawbuf[ip++];
	tmpch=(tmpdat>>12)&0xf;
	adc[i]=(tmpdat&0xfff);
#if _DEBUG
	sprintf(tmpbuf,"ADC:   %2d: %04x  ch:%02d  adc:%4d\n",i,tmpdat,tmpch,
		adc[i]);
	dumpmsg(tmpbuf);
#endif
      }
    }
  }
  /**** Decode Event Data Above***************/


  /**** Data Analysis Here ***************/

/* energy calibration */
  /*
    for(i=0;i<N_QDC;i++) {
    qdcc[i]=(qdc[i]-qpar[i][0])*qpar[i][1];
    qdcoff[i]=qdc[i]-qdcp0[i];
    }
  */
  for(i=0;i<N_ADC;i++){
    adcc[i]=(double)adc[i];
  }
  for(i=0;i<N_QDC;i++){
    qdcc[i]=1.*qdc[i];
  }

  for(i=0;i<N_TDC;i++){
    tdcc[i]=1.*tdc[i];
  }
  kevee1600 = qdcc[0]*5.3876-38.4728; // 1600V
  kevee1800 = qdcc[0]*2.7073-27.3554; // 1800V
  /*******ガンマで識別********/
  /*  gamma83 = (qdcc[0])*(qdcc[0])*0.93560e-5+qdcc[0]*0.12169+37.276; //1800V 30cm
  gamma84 = (qdcc[0])*(qdcc[0])*0.68547e-5+qdcc[0]*0.13412+28.718; //1800V 45cm
  gamma86 = (qdcc[0])*(qdcc[0])*0.78683e-5+qdcc[0]*0.13200+31.817; //1800V 60cm
  gamma63 = (qdcc[0])*(qdcc[0])*0.89516e-5+qdcc[0]*0.13056+33.992; //1600V 30cm
  gamma64 = (qdcc[0])*(qdcc[0])*0.12385e-5+qdcc[0]*0.11622+43.062; //1600V 45cm
  gamma66 = (qdcc[0])*(qdcc[0])*0.97612e-5+qdcc[0]*0.12488+40.070; //1600V 60cm
  */
  /*******中性子で識別***********/
  //  gamma83 = (qdcc[0])*(qdcc[0])*(qdcc[0])*(0.27914e-7)+(qdcc[0])*(qdcc[0])*(-0.81844e-4)+qdcc[0]*0.25007+43.956; //1800V 30cm
   gamma83 = 91.12+18.996*pow(qdcc[0],0.5)-47.305*pow(qdcc[0],0.33); //1800V 30cm 任意関数でfitting
   // gamma83 = 79.269+17.735*pow(qdcc[0],0.5)-42.138*pow(qdcc[0],0.33); //1800V 30cm
   //  gamma84 = (qdcc[0])*(qdcc[0])*(qdcc[0])*(0.31947e-7)+(qdcc[0])*(qdcc[0])*(-0.84243e-4)+qdcc[0]*0.24734+42.228; //1800V 45cm
   gamma84 = 40.856+12.485*pow(qdcc[0],0.5)-22.304*pow(qdcc[0],0.33); //1800V 45cm 任意関数でfitting
   gamma86 = 29.291+10.766*pow(qdcc[0],0.5)-15.884*pow(qdcc[0],0.33); //1800V 60cm 任意関数でfitting
   // gamma86 = (qdcc[0])*(qdcc[0])*(qdcc[0])*(0.49453e-7)+(qdcc[0])*(qdcc[0])*(-0.11024e-3)+qdcc[0]*0.25519+42.772; //1800V 60cm
   gamma63 = 36.674+10.104*pow(qdcc[0],0.5)-16.662*pow(qdcc[0],0.33); //1600V 30cm 任意関数でfitting
   //  gamma63 = (qdcc[0])*(qdcc[0])*(qdcc[0])*(0.5207e-6)+(qdcc[0])*(qdcc[0])*(-0.69968e-3)+qdcc[0]*0.46369+16.875; //1600V 30cm
   gamma64 = -15.003+1.9572*pow(qdcc[0],0.5)+12.518*pow(qdcc[0],0.33); //1600V 45cm 任意関数でfitting
   //  gamma64 = (qdcc[0])*(qdcc[0])*(qdcc[0])*(0.43162e-6)+(qdcc[0])*(qdcc[0])*(-0.46313e-3)+qdcc[0]*0.33144+30.248; //1600V 45cm
   gamma66 = -28.764-0.82967*pow(qdcc[0],0.5)+21.651*pow(qdcc[0],0.33); //1600V 60cm 任意関数でfitting
   // gamma66 = (qdcc[0])*(qdcc[0])*(qdcc[0])*(0.30087e-6)+(qdcc[0])*(qdcc[0])*(-0.35934e-3)+qdcc[0]*0.31114+32.095; //1600V 60cm
 
 /*********qdc[1]とqdc[0]を入れ替えて識別*********/
 gamma1 =qdcc[1]*qdcc[1]*qdcc[1]*qdcc[1]*0.30259e-6+(qdcc[1])*(qdcc[1])*(qdcc[1])*(-0.25685e-3)+(qdcc[1])*(qdcc[1])*(0.74459e-1)-qdcc[1]*3.3564+76.145; //1800V 30cm
 /*******:*中性子だけを切り取る********/

  /**** Data Analysis Above ***************/
  
  /*********** Booking here **********/
  
  for(i=0;i<N_QDC;i++){
    HF1(10+i,qdc[i],1.0);
  }
  for(i=0;i<N_TDC;i++){
    HF1(20+i,tdc[i],1.0);
  }

  for(i=0;i<N_ADC;i++){
    HF1(30+i,adc[i],1.0);
  }
  if(qdcc[0]<4000&&qdc[1]<4000&&kevee1800>150){//電圧によって1800or1600//
    HF2(40,qdc[0],qdc[1],1.0);
    HF2(41,kevee1800,qdc[1],1.0);
    HF2(83,qdcc[0],gamma83,1.0);
    HF2(90,qdc[1],qdc[0],1.0);
    // HF1(50,qdcc[1]/qdcc[0],1.0);//
    pede = 20.449;//RUN35
    /*
      pede = 19.511;//RUN23
      pede = 5.1631;//RUN24
      pede = 14.804;//RUN25
      pede = 31.712;//RUN26
      pede = 29.4;//RUN27
      pede = 28.069;//RUN28
      pede = 20.026;//RUN29
      pede = 18.989;//RUN30
      pede = 17.51;//RUN31
      pede = 24.282;//RUN32
      pede = 21.065;//RUN33
      pede = 23.24;//RUN34
      pede = 19.909;//RUN36
      pede = 20.698;//RUN37
      pede = 19.288;//RUN38
    */
    HF1(100,(qdcc[0]-gamma1),1.0);
    HF1(500,(qdcc[1]-gamma83),1.0);
    HF1(510,(qdcc[1]-gamma84),1.0);
    HF1(520,(qdcc[1]-gamma86),1.0);
    HF1(530,(qdcc[1]-gamma63),1.0);
    HF1(540,(qdcc[1]-gamma64),1.0);
    HF1(550,(qdcc[1]-gamma66),1.0);

    

    HF1(60,qdcc[0]*5.3876-38.4728,1.0); // 1600V
    HF1(70,qdcc[0]*2.7073-27.3554,1.0); // 1800V
  }
  /* if(qdcc[0]<4000&&qdc[1]<4000&&kevee1800>200){
    HF1(501,(qdcc[1]-gamma83),1.0);
    HF1(511,(qdcc[1]-gamma84),1.0);
    HF1(521,(qdcc[1]-gamma86),1.0);
    HF1(531,(qdcc[1]-gamma63),1.0);
    HF1(541,(qdcc[1]-gamma64),1.0);
    HF1(551,(qdcc[1]-gamma66),1.0);
    HF1(101,(qdcc[0]-gamma1),1.0);
    }*/
     if(qdcc[0]<4000&&qdc[1]<4000&&kevee1800>310){
    HF1(501,(qdcc[1]-gamma83),1.0);
    HF1(511,(qdcc[1]-gamma84),1.0);
    HF1(521,(qdcc[1]-gamma86),1.0);
    HF1(531,(qdcc[1]-gamma63),1.0);
    HF1(541,(qdcc[1]-gamma64),1.0);
    HF1(551,(qdcc[1]-gamma66),1.0);
    HF1(101,(qdcc[0]-gamma1),1.0);
    }
  if(qdcc[0]<4000&&qdc[1]<4000&&kevee1800>400){
    HF1(502,(qdcc[1]-gamma83),1.0);
    HF1(512,(qdcc[1]-gamma84),1.0);
    HF1(522,(qdcc[1]-gamma86),1.0);
    HF1(532,(qdcc[1]-gamma63),1.0);
    HF1(542,(qdcc[1]-gamma64),1.0);
    HF1(552,(qdcc[1]-gamma66),1.0);
    HF1(102,(qdcc[0]-gamma1),1.0);
  }
  if(qdcc[0]<4000&&qdc[1]<4000&&kevee1800>500){
    HF1(503,(qdcc[1]-gamma83),1.0);
    HF1(513,(qdcc[1]-gamma84),1.0);
    HF1(523,(qdcc[1]-gamma86),1.0);
    HF1(533,(qdcc[1]-gamma63),1.0);
    HF1(543,(qdcc[1]-gamma64),1.0);
    HF1(553,(qdcc[1]-gamma66),1.0);
    HF1(103,(qdcc[0]-gamma1),1.0);
  }
  if(qdcc[0]<4000&&qdc[1]<4000&&kevee1800>700){
    HF1(504,(qdcc[1]-gamma83),1.0);
    HF1(514,(qdcc[1]-gamma84),1.0);
    HF1(524,(qdcc[1]-gamma86),1.0);
    HF1(534,(qdcc[1]-gamma63),1.0);
    HF1(544,(qdcc[1]-gamma64),1.0);
    HF1(554,(qdcc[1]-gamma66),1.0);
    HF1(104,(qdcc[0]-gamma1),1.0);
  }

  if(qdcc[0]<gamma1+50&&qdcc[0]>gamma1-50){
    HF2(120,qdcc[0],qdcc[1],1.0);
  }
  //  if(qdcc[1]<gamma83+30&&qdcc[1]>gamma83-30){//

  
  /*********** Booking Above **********/
  return(ip);
}

