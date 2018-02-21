#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define GNAME_LEN_MAX 10

int toupperStr(char *inStr, int inLen, char* outStr, int outLen){
  int i;

  if(inLen < 0 || outLen < 0 || inLen > outLen){
    printf("[error toupperStr] : invalid length\n");
    return -1;
  }

  memset(outStr,0,outLen);

  for(i=0;i<inLen;i++){
    outStr[i] = toupper(inStr[i]);
  }
  return inLen;
}

int main(int argc,char *argv[]){
  printf("Analysis using global section\n");
  if( argc == 2 ){//Input is run# only
    char cmd[100];
    int nRun = atoi(argv[1]);
    memset(cmd,0,sizeof(cmd));

    sprintf(cmd,"./anap4 -g HOGE ./rdf/%04d.rdf\n",nRun,nRun);
    printf("%s",cmd);
    system(cmd);
    printf("\nYou can copipe the line below\nglob hoge \n");
    //    system("ls \n");

    return 0;

  }
  else if(argc == 3){

    if(strlen(argv[2]) > GNAME_LEN_MAX){
      printf("[Error] : The name of global section is too long\n");
      return 1;
    }
    char gname[GNAME_LEN_MAX];
    toupperStr(argv[2],strlen(argv[2]),gname,strlen(gname));
    char cmd[100];
    memset(cmd,0,sizeof(cmd));
    sprintf(cmd,"./anap4 -g %s ./rdf/%04d.rdf\n",
	    gname,atoi(argv[1]),atoi(argv[1]));
    printf("%s",cmd);
    system(cmd);
    printf("\nYou can copipe the line below\nglob %s \n",gname);
    //    system("ls \n");

    return 0;

  }
  else{  //  if (argc > 3 || argc < 2){
    printf("./kaiseki [run#] ([name of global section])\n");
  }


}
