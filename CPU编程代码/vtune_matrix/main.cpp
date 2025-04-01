#include <iostream>
#include<chrono>
#include<fstream>
#include<cstdlib>
#include <cmath>
using namespace std;
int *sum,*a,**b;
struct data
{
    int time;
    double timep;
};
void pre(int n){
    a=new int[n];
    b=new int*[n];
    for(int i=0;i<n;i++){
        a[i]=rand()%5;
        b[i]=new int[n];
        for(int j=0;j<n;j++)b[i][j]=rand()%5;
    }
    sum=new int[n];
}
data matrix_0(int n,int t)
{
    while(t--)
    {
       for(int i=0; i<n;i++){
           sum[i]= 0;
           for(int j=0;j<n;j++)sum[i]+=b[j][i]*a[j];
       }
    }
    return data{0,0.0};
}
data matrix_cache(int n,int t)
{
    int ot=t;
    auto start = chrono::steady_clock::now();
    while(t--)
    {
        for(int i = 0; i < n; i++)sum[i] = 0;
        for(int j = 0; j < n; j++)
            for(int i = 0; i < n; i++)sum[i] += b[j][i]*a[j];

    }
    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    double timeper=duration.count()*1.0/ot;
    int sumsum=0;
    for(int i=0;i<n;i++)
        sumsum+=sum[i];
    cout<<"cache"<<endl;
    cout<<"sumsum="<<sumsum<<endl;
    cout<<"time="<<duration.count() << "ms"<<endl;
    cout<<"timep="<<timeper<<endl;
    return data{duration.count(),timeper};
}
void del(int n){
    delete[] sum;
    delete[] a;
    for(int i=0;i<n;i++)delete[] b[i];
    delete[] b;
}
void putintocsv()
{
    //ofstream csvout("matrix.csv");
    //csvout<<"n,matrix_0_time,matrix_0_timep,matrix_cache_time,matrix_cache_timep"<<endl;
    data tmp;int n=4,t;


        n=8192;t=1;
        pre(n);
        tmp=matrix_0(n,t);

        //tmp=matrix_cache(n,t);

        del(n);

    return;
}
int main()
{

    putintocsv();

    return 0;
}
