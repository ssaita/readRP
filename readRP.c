#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#define N 256
int readBuf(int n,FILE *fp);
int day_of_year(int a, int b, int c);

int main(int argc,char *argv[])
{
  FILE *fp1,*fp2,*fp_list;
  DIR *dp;
  struct dirent *p;
  struct stat    s;
  int retval;
  //char *oname;
//  char *fname1 = "/Users/saita/Dropbox/data/TEW/2018/09/01/2018-09-01_00_01.txt";
  char fname1[12];
  char fname3[128]={'\0'};
  char fname4[128]={'\0'};
  char *fname2 = "./TEW_20180901.csv";
  char *dname1 = "/Users/saita/Documentation/Researches/readRP/";
  //char *dname2 = "/Users/saita/Dropbox/data/TEW/";
  char *dname2 = "/Users/saita/Dropbox/data/TEW/";
  char *dname3;
  char buf[100],input[128],order[128];
  char c='A';
  int index,year,month,day;
  int i=0,j,file_num=0;
  int YY,MM,DD,hh,mm,ss,HHH,DDD,ZZZ,GPS,LAT,LONG;
	double H,D,Z,F;

  if(argc > 3){
    //oname = argv[1];
    year = atoi(argv[1]);
    month = atoi(argv[2]);
    day = atoi(argv[3]);
  }
  printf("Y:%04d, M:%02d, D:%02d\n",year,month,day);
  /*
  fp1 = fopen(fname1, "r");
  fp2 = fopen(fname2, "w");
  */
  //sprintf(fname1, "%s%04d/%02d/%02d/",dname2,year,month,day);
  printf("%s%04d/%02d/%02d/\n",dname2,year,month,day);
  snprintf(fname1,12,"%04d/%02d/%02d/",year,month,day);
  printf("%s\n",fname1);
  strcat(fname3,dname2);
  strcat(fname3,fname1);
  printf("%s\n",fname3);
  //dp = opendir(fname3);
  /*
  if( fp1 == NULL ){
    printf( "%s元データファイルが開けません\n", fname1 );
    return -1;
  }
  if( fp2 == NULL ){
    printf( "%s変換後データファイルが開けません\n", fname2 );
    return -1;
  }
  */
  if ((dp = opendir(fname3)) == NULL) {
      fprintf(stderr, "Can't open directory %s\n", fname3);
      return -1;
  }
  for(p=readdir(dp);p!=NULL;p=readdir(dp)){
    printf("%s\n",p->d_name);
  }
  /*
  while ((p = readdir(dp)) != NULL) {
      retval = stat(p->d_name, &s);
      if (retval != 0) {
          fprintf(stderr, "Can't stat %s\n", p->d_name);
          return -1;
      }
      if ((s.st_mode & S_IFMT) == S_IFREG) {
          printf("Filename %10s Size %10ld\n", p->d_name, s.st_size);
      }
  }
  */
  if (closedir(dp) != 0) {
      fprintf(stderr, "Can't close directory %s\n", fname3);
      return -1;
  }

    // データのあるフォルダの中を調べる
    /*
  chdir(dname2);
  sprintf(order,"dir /B > %s/tmp.txt",dname1);
  system(order);
  chdir(dname1);
  fp_list=fopen("./tmp.txt","r");
    while(fgets(input,64,fp_list)!=NULL){
        file_num++;
    }
    */
  fprintf(fp2,"\"DateTime\", \"DOY\", \"TEWX\", \"TEWY\", \"TEWZ\", \"TEWF\"\n");
  printf( "\n-- start : readRP --\n" );

  /* find a punctuation symbol.*/
  while((c =fgetc(fp1))!= EOF){
    while(c != '$' && c != EOF){
      c=fgetc(fp1);
    }
    if(c==EOF) break;

    /* if first character is 1, the magnetic field data is in this line skip 1 character */
	 index=readBuf(1,fp1);
		if(index == 1)
    {
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
      F = sqrt(pow(H,2.0)+pow(D,2.0)+pow(Z,2));

      //printf("%c:%d-%02d-%02d %02d:%02d:%02d,%d, H: %10.2f, D: %10.2f, Z:%10.2f F:%10.2f\n",c,YY,MM,DD,hh,mm,ss,day_of_year(MM,DD,YY),H,D,Z,F);
      fprintf(fp2,"\"%d/%02d/%02d %02d:%02d:%02d\",%d, %10.2f %10.2f %10.2f %10.2f\n",YY,MM,DD,hh,mm,ss,day_of_year(MM,DD,YY),H,D,Z,F);
		}
		else
    {
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

int day_of_year(int a, int b, int c)
{
    int i=0, daymon=0, dayday=0;
    int mth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ( (c % 4) || (c % 100) && (c % 400) )
        mth[3] = mth[3] + 1;

    for (i = 0; i < a; i++)
    {
        daymon += mth[i];
    }

    dayday = b;


return (daymon + dayday);
}
