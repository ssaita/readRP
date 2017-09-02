#include <stdio.h>
#include <stdlib.h>

int readBuf(int n,FILE *fp);

int main(void){
  FILE *fp1,*fp2;
  char *fname1 = "/Users/sato/Downloads/2017-08-29_16_08.txt";
  char *fname2 = "/Users/sato/Downloads/20170829_1608.txt";
  char buf[100];
  char c='A';
  int i=0,j;
  int YY,MM,DD,hh,mm,ss,HHH,DDD,ZZZ;
  
  fp1 = fopen( fname1, "r" );
  fp2 = fopen( fname2, "w" );
  if( fp1 == NULL ){
    printf( "%sファイルが開けません¥n", fname1 );
    return -1;
  }

  printf( "\n-- start : readRP --\n" );

  /* find a punctuation symbol.*/
  while((c =fgetc(fp1))!= EOF){
    while(c != '$' && c != EOF){
      c=fgetc(fp1);
    }
    if(c==EOF) break;

    /* skip 1 character */
    c=fgetc(fp1);
    printf("c:%c\n",c);
    
    YY=2000+readBuf(2,fp1);
    printf("YY:%d\n",YY);
  
    MM=readBuf(2,fp1);
    printf("MM:%d\n",MM);

    DD=readBuf(2,fp1);
    printf("DD:%d\n",DD);

    hh=readBuf(2,fp1);
    printf("hh:%d\n",hh);
    
    mm=readBuf(2,fp1);
    printf("mm:%d\n",mm);
    
    ss=readBuf(2,fp1);
    printf("ss:%d\n",ss);
  
    HHH=readBuf(5,fp1);
    DDD=readBuf(5,fp1);
    ZZZ=readBuf(5,fp1);
    printf("HHH:%d\n",HHH);
    printf("DDD:%d\n",DDD);
    printf("ZZZ:%d\n",ZZZ);

    fprintf(fp2,"%d/%d/%d %d:%d:%d %d %d %d\n",YY,MM,DD,hh,mm,ss,HHH,DDD,ZZZ);

  }

  /*  while( (c = fgetc( fp1 )) != EOF ){
    printf( "%c", c );
  }
  */
  fclose( fp1 );
  fclose( fp2 );
  printf( "\n-- end : readRP --\n" );

  return 0;
}

int readBuf(int n, FILE *fp){
  /* read buffer */
  char c,buff[10];
  int i=0,ibuff;
  while(i!=n){
    c=fgetc(fp);
    //    printf("c;%c\n",c);
    buff[i]=c;
    i++;
  }
  ibuff=atoi(buff);
  //  printf("MM;%d\n",j);
  //  month=atoi(buf);
  return ibuff; 

}
