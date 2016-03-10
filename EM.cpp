#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>
#define DOCUMENT 5047
#define MU 10000
#define N 30
#define Q 163

using namespace std;
int power(int a,int b);

int main(){
    int query_num=1;
    char top[N*Q][5];
    int topN[N];
    char buffer[50];
    double alpha[DOCUMENT];
    double wgivenq[62000];
    double wgivenr[62000];
    double wgivenb[62000];
    int **topcount=new int*[N];
    double **rgivenwd=new double*[N];
    
    for(int i=0;i<N;i++){
            topcount[i]=new int[62000];
            rgivenwd[i]=new double[62000];
            }
    
    for(int i=0;i<62000;i++){
            wgivenb[i]=0;
            }
    
    char dtmp[50];
    char adnum[4];
    for(int i=0;i<DOCUMENT;i++){
            vector<double> doc;
            for(int j=0;j<4;j++){
            adnum[j]='0'+(((i+1)/power(10,j))*power(10,j)-((i+1)/power(10,j+1))*power(10,j+1))/power(10,j);
            }
            fstream din;
            string dname="onebest/T";
            dname=dname+adnum[3]+adnum[2]+adnum[1]+adnum[0];
            din.open(dname.c_str(),ios::in);
            while(din.getline(dtmp,sizeof(dtmp))){
            char *dcut;
            dcut=strtok(dtmp," \n");
            while(dcut!=NULL){
                     doc.push_back(atof(dcut));
                     dcut=strtok(NULL," \n");
                     }
            }
            
            for(int j=0;j<doc.size();j+=2){
            wgivenb[(int)doc[j]]+=doc[j+1];
            }
            }
    
    for(int i=0;i<62000;i++){
            wgivenb[i]/=DOCUMENT;
            }
    
    
    while(query_num<=Q){
                        
    for(int i=0;i<62000;i++){
            wgivenq[i]=0;
            wgivenr[i]=0;
            }
            
    for(int i=0;i<N;i++){
            for(int j=0;j<62000;j++){
                    topcount[i][j]=0;
                    rgivenwd[i][j]=0;
                    }
            }

    /*for(int i=0;i<DOCUMENT;i++){
            alpha[i]=0.5;
            }*/

    char atmp[50];
    char anum[4];
    fstream din_2;
    string aname="alpha/alpha";
    char tmp_1[3];
    itoa(query_num,tmp_1,10);
    aname=aname+tmp_1+".txt";
    din_2.open(aname.c_str(),ios::in);
    int n=0;
    while(din_2.getline(atmp,sizeof(atmp))){
    char *acut;
    acut=strtok(atmp," \n");
    while(acut!=NULL){
                     alpha[n]=atof(acut);
                     acut=strtok(NULL," \n");
                     n++;
                     }
            }
    
    
    fstream ftop;
    fstream opfile;
    fstream opfile_2;
    
    char num[3];        
    for(int j=0;j<3;j++){
            num[j]='0'+((query_num/power(10,j))*power(10,j)-(query_num/power(10,j+1))*power(10,j+1))/power(10,j);
            }    
    string newquery="newquery/Q";
    newquery=newquery+num[2]+num[1]+num[0];
    string alphao="alpha/alpha";
    char tmp_2[3];
    itoa(query_num,tmp_2,10);
    alphao=alphao+tmp_2+".txt";
    opfile.open(newquery.c_str(),ios::out);
    opfile_2.open(alphao.c_str(),ios::out);
    ftop.open("output_top30.txt",ios::in);    
    int a=0;
    while(ftop.getline(buffer,sizeof(buffer))){
    char *ctop;
    ctop=strtok(buffer," \n");
    int b=1;
    while(ctop!=NULL){
                     if(b==3)strcpy(top[a],ctop);
                     ctop=strtok(NULL," \n");
                     b++;
                     }
    a++;
    }

    
    char qtmp[50];
    char aqnum[3];
            
    for(int j=0;j<3;j++){
            aqnum[j]='0'+(((query_num)/power(10,j))*power(10,j)-((query_num)/power(10,j+1))*power(10,j+1))/power(10,j);
            }
            
    vector<double> query;
    string qname="query/Q";
    qname=qname+aqnum[2]+aqnum[1]+aqnum[0];
    fstream qin;
    qin.open(qname.c_str(),ios::in);
    while(qin.getline(qtmp,sizeof(qtmp))){
        char *qcut;
        qcut=strtok(qtmp," \n");
        while(qcut!=NULL){
                     query.push_back(atof(qcut));
                     qcut=strtok(NULL," \n");
                     }
    }
    
    for(int i=0;i<query.size();i+=2){
            wgivenq[(int)query[i]]=query[i+1];
            //wgivenq[(int)query[i]]=2/query.size();
            }
    
    query_num--;
    for(int j=0;j<N;j++){
            topN[j]=(top[query_num*N+j][1]-'0')*1000+(top[query_num*N+j][2]-'0')*100+(top[query_num*N+j][3]-'0')*10+(top[query_num*N+j][4]-'0');
            }
    
    char dtmp_2[50];
    vector<double> doc_2;
    for(int j=0;j<N;j++){
            fstream din_2;
            string dname_2="onebest/";
            dname_2=dname_2+top[query_num*N+j][0]+top[query_num*N+j][1]+top[query_num*N+j][2]+top[query_num*N+j][3]+top[query_num*N+j][4];
            din_2.open(dname_2.c_str(),ios::in);
            while(din_2.getline(dtmp_2,sizeof(dtmp_2))){
            char *dcut_2;
            dcut_2=strtok(dtmp_2," \n");
            int even=0;
            while(dcut_2!=NULL){
                     doc_2.push_back(atof(dcut_2));
                     if(!even%2)topcount[j][(int)atof(dcut_2)]=1;
                     dcut_2=strtok(NULL," \n");
                     even++;
                     }
            }

     }
                       
     for(int j=0;j<doc_2.size();j+=2){
                              wgivenr[(int)doc_2[j]]+=doc_2[j+1];
     }
     
     for(int j=0;j<62000;j++){
             wgivenr[j]/=N;
             }
             
     for(int j=0;j<N;j++){
             for(int k=0;k<62000;k++){
                     if(wgivenr[k]!=0)rgivenwd[j][k]=
                     (alpha[topN[j]-1]*wgivenr[k])/(alpha[topN[j]-1]*wgivenr[k]
                     +(1-alpha[topN[j]-1])*wgivenb[k]);
                     }
             }
             
     query_num++;
     double numerator=0;
     double denominator=0;
     
     for(int j=0;j<N;j++){
             numerator=0;
             denominator=0;
             for(int k=0;k<62000;k++){
                     if(wgivenr[k]!=0){
                     numerator+=rgivenwd[j][k]*topcount[j][k];
                     denominator+=topcount[j][k];
                     }
                     }
             alpha[topN[j]-1]=numerator/denominator;
             }
     
     denominator=0;
     for(int j=0;j<N;j++){
     for(int k=0;k<62000;k++){
             if(wgivenr[k]!=0){
             denominator+=rgivenwd[j][k]*topcount[j][k];
             }
                     
     }
     }
     
     for(int j=0;j<62000;j++){
             numerator=0;
             if(wgivenr[j]!=0){
             for(int k=0;k<N;k++){
                     numerator+=rgivenwd[k][j]*topcount[k][j];
                     }
             wgivenr[j]=(numerator+MU*wgivenq[j])/(denominator+MU);
             }
             }

    for(int i=0;i<DOCUMENT;i++){
            opfile_2<<alpha[i]<<endl;
            }
            
    for(int i=0;i<62000;i++){
            if(wgivenr[i]!=0)opfile<<i<<" "<<wgivenr[i]<<endl;
            }
    query_num++;
}

    for(int i=0;i<N;i++){
            delete [] topcount[i];
            delete [] rgivenwd[i];
            }
            
    delete [] topcount;
    delete [] rgivenwd;
    
    system("pause");
    return 0;
}

int power(int a,int b){
    int result=1;
    for(int i=0;i<b;i++){
            result*=a;
            }
    return result;
}

