
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
#include "big.h"   /* include MIRACL system */
using namespace std;

Miracl precision(20000,128);   /* bigs are 20000 centimal digits long */

char tr[128]; int w[128];

string s10(Big x)
{Big y=x; int r; string s="";
 while (y!=0){r=y%10;y=y/10;s=tr[r]+s;}
 return s;
}

ifstream result;int deploy,b,start,d,j;string ms,p,s,ss;char cc;
Big nbd,n1,n2,pds;

main(int argc, char *argv[])
{
deploy=atoi(argv[2]);
ms=argv[1];b=atoi(argv[1]);
if(argc>3)start=atoi(argv[3]);else start=0;cerr<<b<<','<<start<<','<<deploy<<"\n";
for(char c='0';c<='9';c++){w[c]=0+c-'0';tr[0+c-'0']=c;}
for(char c='A';c<='Z';c++){w[c]=10+c-'A';tr[10+c-'A']=c;}
for(char c='a';c<='z';c++){w[c]=36+c-'a';tr[36+c-'a']=c;}
while(cin>>p)if(p[0]=='%')break; 
      else {cerr<<"\n"<<p<<"\n";n1=0;n2=0;pds=1;s="";ss="";
            for(j=0;j<p.size();j++)if(p[j]=='{')break; 
                                   else {n1=n1*b+w[p[j]];s=s+p[j];}
            if(j==p.size()){cerr<<" : pas de repetition";continue;}
            cc=p[j+1];d=w[cc];
            for(j=j+3;j<p.size();j++)if(p[j]=='{')break; 
                                     else {n2=n2*b+w[p[j]];ss=ss+p[j];pds=pds*b;}
            if(j!=p.size()){cerr<<" : plus d'une repetition";continue;}
            for(j=0;j<start;j++){n1=n1*b+d;s=s+cc;}
            for(j=start;j<=deploy;j++)
               {nbd=n1*pds+n2;
                if(prime(nbd))
                  {cout<<'"'<<s+ss<<'"'<<'='<<s10(nbd)<<",\n";cerr<<'+';cout.flush();break;}
                  else if((j%1000)==0)cerr<<'-';else cerr<<'.';
                n1=n1*b+d;s=s+cc;
               }
           }
cerr<<"\n===================================\n";
} // fin main
