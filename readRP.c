#include <stdio.h>
#include <stdlib.h>

int readBuf(int n,FILE *fp);

int main(void){
  FILE *fp1,*fp2;
  char *fname1 = "/Users/saita/Dropbox/data/TEW/2018/09/01/2018-09-01_00_01.txt";
  char *fname2 = "./TEW_20180901_0001.txt";
  char buf[100];
  char c='A';
  int index;
  int i=0,j;
  int YY,MM,DD,hh,mm,ss,HHH,DDD,ZZZ,GPS,LAT,LONG;
	double H,D,Z;
  fp1 = fopen( fname1, "r" );
  fp2 = fopen( fname2, "w" );
  if( fp1 == NULL ){
    printf( "%s元データファイルが開けません¥n", fname1 );
    return -1;
  }
  if( fp2 == NULL ){
    printf( "%s変換後データファイルが開けません¥n", fname2 );
    return -1;
  }

  printf( "\n-- start : readRP --\n" );

  /* find a punctuation symbol.*/
  while((c =fgetc(fp1))!= EOF){
    while(c != '$' && c != EOF){
      c=fgetc(fp1);
    }
    if(c==EOF) break;

	/* if first character is 1, the magnetic field data is in this line skip 1 character */
	index=readBuf(1,fp1);
		if(index == 1){
//    printf("c:%c\n",c);
    
    YY=2000+readBuf(2,fp1);
//    printf("YY:%d\n",YY);
  
    MM=readBuf(2,fp1);
//    printf("MM:%d\n",MM);

    DD=readBuf(2,fp1);
//    printf("DD:%d\n",DD);

    hh=readBuf(2,fp1);
//    printf("hh:%d\n",hh);
    
    mm=readBuf(2,fp1);
//    printf("mm:%d\n",mm);
    
    ss=readBuf(2,fp1);
//	printf("ss:%d\n",ss);
	

  
	HHH=readBuf(5,fp1);
	H = (HHH-(2^15))/(2^15)*10.24/10*600;
	DDD=readBuf(5,fp1);
	D = (DDD-(2^15))/(2^15)*10.24/10*600;
	ZZZ=readBuf(5,fp1);
	Z = (ZZZ-(2^15))/(2^15)*10.24/10*600;
/*    printf("HHH:%d\n",HHH);
    printf("DDD:%d\n",DDD);
    printf("ZZZ:%d\n",ZZZ);
*/		
	printf("%c:%d-%02d-%02d %02d:%02d:%02d H: %f, D: %f, Z:%f\n",c,YY,MM,DD,hh,mm,ss,H,D,Z);
		
    fprintf(fp2,"%d/%02d/%02d %02d:%02d:%02d %f %f %f\n",YY,MM,DD,hh,mm,ss,H,D,Z);
		}
		else{
			GPS=readBuf(15,fp1);
			c=fgetc(fp1);
			LAT=readBuf(6,fp1);
			c=fgetc(fp1);
			LONG=readBuf(6,fp1);
			printf("LAT: %d, LONG: %d\n",LAT,LONG);
		}
  }

  /*  while( (c = fgetc( fp1 )) != EOF ){
    printf( "%c", c );
  }
  */
  fclose( fp1 );
//  fclose( fp2 );
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
