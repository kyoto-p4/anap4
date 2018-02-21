#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[]){


  if (argc != 2){
    printf("./kaiseki [run#]\n");
    return 1;
  }

  else{
    char cmd[100];
    int nRun = atoi(argv[1]);
    //    if(nRun <= 999){
      sprintf(cmd,"./anap4 -hb ./hb/%04d.hb ./rdf/%04d.rdf\n",nRun,nRun);
      printf("%s",cmd);
      system(cmd);
      printf("\nYou can copipe the line below\nh/file %04d ./hb/%04d.hb \n",nRun,nRun);
      return 0;
      //      //    }
      //      else if(nRun >= 1000){
      //      sprintf(cmd,"./anap4 -hb ./hbook/160110/%04d.hb /work0/data/15p4jan/rdf/160110/%04d.rdf\n",nRun,nRun);
      //      printf("%s",cmd);
      //      system(cmd);
      //      printf("\nYou can copipe the line below\n");
      //      printf("h/file %04d ./hbook/160110/%04d.hb \n",nRun,nRun);
      //      return 0;
      //    }
  }

}
