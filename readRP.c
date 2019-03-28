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
void joinpath(char *path, const char *path1, const char *path2);
void listfiles(char *path);

int main(int argc,char *argv[])
{
  FILE *fp1,*fp2,*fp_list;
  DIR *dir;
  struct dirent *dp;
  struct dirent *p;
  struct stat    s;
  struct stat fi;
  int retval;

  char *fname[100];
  char fname1[20];
  char fname2[18];
  char fname3[128]={'\0'};
  char fname4[128]={'\0'};

  char *dname1 = "/Users/saita/Documentation/Researches/readRP/";
  char *dname2 = "/Users/saita/Dropbox/data/";
  char *dname3;
  char *stname;
  char buf[100],input[128],order[128];
  char c='A';
  int index,year,month,day;
  int i=0,j,file_num=0;
  int YY,MM,DD,hh,mm,ss,HHH,DDD,ZZZ,GPS,LAT,LONG;
	double H,D,Z,F;

  if(argc > 4){
    stname = (argv[1]);
    year = atoi(argv[2]);
    month = atoi(argv[3]);
    day = atoi(argv[4]);
  }
  printf("Y:%04d, M:%02d, D:%02d\n",year,month,day);
  snprintf(fname2,18,"%s_%04d%02d%02d.csv",stname,year,month,day);
  printf("%s\n",fname2);
  fp2 = fopen(fname2, "w");

  snprintf(fname1,12,"%04d/%02d/%02d/\n",year,month,day);
  printf("%s\n",fname1);
  printf("STES01\n");
  strcat(fname3,dname2);
  strcat(fname3,stname);
  strcat(fname3,"/");
  strcat(fname3,fname1);
  printf("%s\n",fname3);
  printf("STES02\n");

  fprintf(fp2,"\"DateTime\", \"DOY\", \"X\", \"Y\", \"Z\", \"F\"\n");
  printf( "\n-- start : readRP --\n" );

  /* find a punctuation symbol.*/
  i=0;
  printf("STES10\n");
  dir = opendir(fname3);
  for (dp = readdir(dir); dp != NULL; dp = readdir(dir)) {
      if (dp->d_name[0] != '.') {
          joinpath(fname4, fname3, dp->d_name);
          stat(fname4, &fi);
          if (!S_ISDIR(fi.st_mode)) {
              fname[i]= fname4;
              printf("%s\n", fname[i]);
              i++;
          }
      }
  }
  closedir(dir);
  printf("STEP11\n");
  i=0;
  printf("STEP12\n");
  while(fname[i]!=NULL){
    printf("これからファイル：%sを開きます\n",fname[i]);
    fp1 = fopen(fname[i], "r");
    if(fp1==NULL)printf("%sのデータファイルが開けません。\n",fname[i]);
    c =fgetc(fp1);
    while(c != EOF){
      index=readBuf(1,fp1);
      if(index == 1){
        printf("%c%d ",c,index);
        YY=2000+readBuf(2,fp1);
        MM=readBuf(2,fp1);
        DD=readBuf(2,fp1);
        hh=readBuf(2,fp1);
        mm=readBuf(2,fp1);
        ss=readBuf(2,fp1);
        HHH=readBuf(5,fp1);
        H = (HHH-(2^15))/(2^15)*10.24/10*600;
        DDD=readBuf(5,fp1);
        D = (DDD-(2^15))/(2^15)*10.24/10*600;
        ZZZ=readBuf(5,fp1);
        Z = (ZZZ-(2^15))/(2^15)*10.24/10*600;
        F = sqrt(pow(H,2.0)+pow(D,2.0)+pow(Z,2));
        printf("%d-%02d-%02d %02d:%02d:%02d,%03d, H: %10.2f, D: %10.2f, Z:%10.2f F:%10.2f\n",YY,MM,DD,hh,mm,ss,day_of_year(MM,DD,YY),H,D,Z,F);
        fprintf(fp2,"\"%d/%02d/%02d %02d:%02d:%02d\",%03d, %10.2f, %10.2f, %10.2f, %10.2f\n",YY,MM,DD,hh,mm,ss,day_of_year(MM,DD,YY),H,D,Z,F);
      }
        // else
        // {
        //   GPS=readBuf(15,fp1);
        //   c=fgetc(fp1);
        //   LAT=readBuf(6,fp1);
        //   c=fgetc(fp1);
        //   LONG=readBuf(6,fp1);
        //   printf("LAT: %d, LONG: %d\n",LAT,LONG);
        // }
        c =fgetc(fp1);
        while(c != '$' && c != EOF){
          c=fgetc(fp1);
          //if(c=='$') break;
        }

        if(c==EOF) break;
        // printf("STEP19\n");
      }
      fclose(fp1);
      i++;
      printf("STEP20\n");
    }

  /*  while( (c = fgetc( fp1 )) != EOF ){
    printf( "%c", c );
  }
  */

//  fclose( fp2 );
  printf( "\n-- end : readRP --\n" );
  fclose(fp2);
  return 0;
}

int readBuf(int n, FILE *fp){
  /* read buffer */
  char c,buff[10];
  int i=0,ibuff;
  while(i!=n){
    c=fgetc(fp);
    buff[i]=c;
    i++;
  }
  ibuff=atoi(buff);
  return ibuff;

}

int day_of_year(int a, int b, int c)
{
    int i=0, daymon=0, dayday=0;
    int mth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ( (c % 4) || (c % 100) && (c % 400) ) mth[3] = mth[3] + 1;
    for (i = 0; i < a; i++){
        daymon += mth[i];
    }
    dayday = b;
return (daymon + dayday);
}

// void listfiles(char *path)
// {
//     DIR *dir;
//     struct dirent *dp;
//     struct stat fi;
//     char path2[256];
//     int i=0;
//
//     dir = opendir(path);
//     for (dp = readdir(dir); dp != NULL; dp = readdir(dir)) {
//         if (dp->d_name[0] != '.') {
//             joinpath(path2, path, dp->d_name);
//             stat(path2, &fi);
//             if (!S_ISDIR(fi.st_mode)) {
//                 // printf("%s\n",path2);
//                 // printf("STES(listfiles 00)\n");
//                 fname[i]= path2;
//                 //printf("%s\n", path2);
//                 printf("%s\n", fname[i]);
//                 i++;
//             }
//         }
//     }
//     closedir(dir);
//
//     return;
// }

void joinpath(char *path, const char *path1, const char *path2)
{
    strcpy(path, path1);
//    strcat(path, "/");
    strcat(path, path2);

    return;
}
