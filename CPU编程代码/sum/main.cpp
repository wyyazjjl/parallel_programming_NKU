#include <iostream>
#include <chrono>
#include <fstream>
#include<cstdlib>
using namespace std;
int a[1000005];
int b[1000005];
int num[19]={1,2,3,4,5,6,8,10,15,20,25,30,40,50,60,70,80,90,100};
struct data
{
    int time;
    double timep;
};
data sum_0(int n,int t)
{
    int sum=0,ot=t;
    auto start = chrono::steady_clock::now();
    while(t--)
    {
        sum=0;
        for(int i=0;i<n;i++)
            sum+=a[i];
    }

    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    double timeper=duration.count()*1.0/ot;
    cout<<"平凡算法"<<endl;
    cout<<"sum="<<sum<<endl;
    cout<<"time="<<duration.count() << "ms"<<endl;
    cout<<"timep="<<timeper<<endl;
    return data{duration.count(),timeper};
}
data sum_2(int n,int t)
{
    int sum=0,ot=t;
    int sum1=0,sum2=0;
    auto start = chrono::steady_clock::now();
    while(t--)
    {
        sum=0;sum1=0,sum2=0;
        for(int i=0;i<n;i+=2)
            {sum1+=a[i];sum2+=a[i+1];}
        sum=sum1+sum2;
    }
    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    double timeper=duration.count()*1.0/ot;
    cout<<"2路优化算法"<<endl;
    cout<<"sum="<<sum<<endl;
    cout<<"time="<<duration.count() << "ms"<<endl;
    cout<<"timep="<<timeper<<endl;
    return data{duration.count(),timeper};
}
data sum_8(int n,int t)
{
    int sum=0,ot=t;
    int sum1=0,sum2=0,sum3=0,sum4=0,sum5=0,sum6=0,sum7=0,sum8=0;
    auto start = chrono::steady_clock::now();
    while(t--)
    {
        sum=0;sum1=0,sum2=0;sum3=0,sum4=0;sum5=0,sum6=0;sum7=0,sum8=0;
        for(int i=0;i<n;i+=8)
            {sum1+=a[i];sum2+=a[i+1];sum3+=a[i+2];sum4+=a[i+3];sum5+=a[i+4];sum6+=a[i+5];sum7+=a[i+6];sum8+=a[i+7];}
        sum=sum1+sum2+sum3+sum4+sum5+sum6+sum7+sum8;
    }
    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    double timeper=duration.count()*1.0/ot;
    cout<<"8路优化算法"<<endl;
    cout<<"sum="<<sum<<endl;
    cout<<"time="<<duration.count() << "ms"<<endl;
    cout<<"timep="<<timeper<<endl;
    return data{duration.count(),timeper};
}
inline void digui(int n){
    if(n==1) return;
    for(int i=0;i<n/2;i++) b[i]+=b[n-i-1];
    n=n/2+n%2;
    digui(n);
}
data sum_log(int n,int t){
    int sum=0,ot=t;
    auto start = chrono::steady_clock::now();
    while(t--){
        sum=0;
       for(int i=0;i<n;i++)b[i]=a[i];
        digui(n);
        sum=b[0];//
    }
    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    t=ot;
    auto start2 = chrono::steady_clock::now();
    while(t--){
       for(int i=0;i<n;i++)b[i]=a[i];
    }
    auto end2 = chrono::steady_clock::now();
    auto duration2 = chrono::duration_cast<chrono::milliseconds>(end2 - start2);
    double timeper=(duration.count()-duration2.count())*1.0/ot;
    cout<<"归并算法"<<endl;
    cout<<"sum="<<sum<<endl;
    cout<<"time="<<duration.count()-duration2.count() << "ms"<<endl;
    cout<<"timep="<<timeper<<endl;
    return data{duration.count()-duration2.count(),timeper};
}
void putintocsv()
{
    ofstream csvout("sum.csv");
    csvout<<"sum0_time,sum0_timep,sum2_time,sum2_timep,sum8_time,sum8_timep,sum_log_time,sum_log_timep,"<<endl;
    data tmp;int n,t;
    for(int i=0;i<19;i++)
    {
        n=10000*num[i];t=1000;
        cout<<"n="<<n<<" t="<<t<<'\n';
        tmp=sum_0(n,t);
        csvout<<tmp.time<<","<<tmp.timep<<",";
        tmp=sum_2(n,t);
        csvout<<tmp.time<<","<<tmp.timep<<",";
        tmp=sum_8(n,t);
        csvout<<tmp.time<<","<<tmp.timep<<",";
        tmp=sum_log(n,t);
        csvout<<tmp.time<<","<<tmp.timep<<endl;
    }
    csvout.close();
    return;
}
int main()
{
    for(int i=0;i<=1000005;i++)
    {
        a[i]=rand()%10;
        b[i]=a[i];
    }


    //1 2 3 4 5 6 8 10 15 20 25 30 40 50 60 70 80 90 100


    putintocsv();

    cout << "Hello world!" << endl;
    return 0;
}
