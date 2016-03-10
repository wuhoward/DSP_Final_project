#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

int power(int a,int b);

int main(){
    
    int control_1=1; //控制讀檔結束時機 
    fstream file;
    file.open("output_top30_10000_1.txt",ios::out);//ouput檔名
    fstream file_2;
    file_2.open("output_top30_10000_1_full.txt",ios::out);
    double background[62000];
    int doc_num=0;
    
    int control_2=1;
    while(control_2!=0){
    int bnum=control_2;
    control_2++;
    char btmp[100];
    char abnum[4];
    vector<double> doc;
    for(int i=0;i<4;i++){
            abnum[i]='0'+((bnum/power(10,i))*power(10,i)-(bnum/power(10,i+1))*power(10,i+1))/power(10,i);
            }
    string bname="onebest/T";
    bname=bname+abnum[3]+abnum[2]+abnum[1]+abnum[0];
    const char *bname_c = bname.c_str();
    fstream bfin;
    bfin.open(bname_c,ios::in);
    if(!bfin){
              doc_num=control_2-1;
              control_2=0;
              }
    else{
    double sum=0;
    while(bfin.getline(btmp,sizeof(btmp))){
    char *bcut;
    bcut=strtok(btmp," \n");
    while(bcut!=NULL){
                     doc.push_back(atof(bcut));
                     bcut=strtok(NULL," \n");
                     }
}
    for(int i=0;i<doc.size();i+=2) {
            background[(int)doc[i]]+=doc[i+1];
    }
}
}    
    for(int i=0;i<62000;i++){
            background[i]/=5047;
            }

    while(control_1!=0){
    int qnum=control_1;
    vector<double> point;//存分數 
    vector<int> number;
    control_1++;
    char qtmp[100];
    char aqnum[3];
    for(int i=0;i<3;i++){
            aqnum[i]='0'+((qnum/power(10,i))*power(10,i)-(qnum/power(10,i+1))*power(10,i+1))/power(10,i);
            }
    //未滿四位數的數字前面補零
     
    vector<double> query;
    string qname="newquery/Q";
    qname=qname+aqnum[2]+aqnum[1]+aqnum[0];
    const char *qname_c = qname.c_str();
    fstream qfin;
    qfin.open(qname_c,ios::in);    
    if(!qfin)control_1=0;
    else{
    while(qfin.getline(qtmp,sizeof(qtmp))){
        char *qcut;
        qcut=strtok(qtmp," \n");
        while(qcut!=NULL){
                     query.push_back(atof(qcut));
                     qcut=strtok(NULL," \n");
                     }
    }
    

    int control_3=1;
    while(control_3!=0){
    int dnum=control_3;
    control_3++;
    double tpoint=1;
    char dtmp[100];
    char adnum[4];
    vector<double> doc_2;
    vector<double> mul;
    for(int i=0;i<4;i++){
            adnum[i]='0'+((dnum/power(10,i))*power(10,i)-(dnum/power(10,i+1))*power(10,i+1))/power(10,i);
            }
    string dname="onebest/T";
    dname=dname+adnum[3]+adnum[2]+adnum[1]+adnum[0];
    const char *dname_c = dname.c_str();
    fstream dfin;
    dfin.open(dname_c,ios::in);
    if(!dfin)control_3=0;
    else{
    int key=0;
    while(dfin.getline(dtmp,sizeof(dtmp))){
    char *dcut;
    dcut=strtok(dtmp," \n");
    int even=0;
    int match=0;
    while(dcut!=NULL){
                      if(!even%2&&key<query.size()){
                                  while(atof(dcut)>query[key]&&key<query.size()){
                                                               key+=2;
                                                               mul.push_back(0);             
                                                    }
                                  if(atof(dcut)==query[key]){
                                                             key+=2;
                                                             match=1;
                                                             }
                                  }
                      if(even%2&&match==1){
                                   mul.push_back(atof(dcut));
                                   match=0;
                                   }
                      even++;
                      doc_2.push_back(atof(dcut));
                      dcut=strtok(NULL," \n");
                      }
}
    for(int i=0;i<query.size()/2-mul.size();i++){
            mul.push_back(0);
            }
    for(int i=0;i<query.size();i+=2){
                                     tpoint=tpoint*pow(0.95*mul[i/2]+0.05*background[(int)query[i]],query[i+1]);
    }
    point.push_back(tpoint);
    
}}}
    
    for(int i=0;i<point.size();i++) {
            //if(point[i]>0){
            char filenum[4];
            for(int j=0;j<4;j++){
            filenum[j]='0'+(((i+1)/power(10,j))*power(10,j)-((i+1)/power(10,j+1))*power(10,j+1))/power(10,j);
            }
            string filename="T";
            filename=filename+filenum[3]+filenum[2]+filenum[1]+filenum[0];
            file_2<<qnum<<" 0 "<<filename<<" 0 "<<point[i]<<" EXP"<<endl;
            //}
    }

    for(int i=0;i<30;i++){
            double max=0;
            int pos=0;
            for(int j=0;j<point.size();j++){
                    if(point[j]>max){
                                     max=point[j];
                                     pos=j;
                                     }
                    }
                    char filenum[4];
                    for(int j=0;j<4;j++){
                    filenum[j]='0'+(((pos+1)/power(10,j))*power(10,j)-((pos+1)/power(10,j+1))*power(10,j+1))/power(10,j);
                    }
                    string filename="T";
                    filename=filename+filenum[3]+filenum[2]+filenum[1]+filenum[0];
                    file<<qnum<<" 0 "<<filename<<" 0 "<<max<<" EXP"<<endl;
                    point[pos]=0;
                    }


}
    system("pause");
    return 0;
}

//計算整數次方用 
int power(int a,int b){
    int result=1;
    for(int i=0;i<b;i++){
            result*=a;
            }
    return result;
}
