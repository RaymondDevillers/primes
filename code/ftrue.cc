
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
using namespace std;

main(int argc, char *argv[])
{string p,ms,pref,prefms,mm,m10,mM,md;int m,k,nn,l,i,j;
list<string> foundM,found10;
while(cin>>p)if(p=="true,")
{cin>>p;i=0; 
while (p[i]!='>')if(i==p.length()){cin>>p;i=0;}
                  else i++;
mm="";m10="";i++;
while (p[i]!='=')if(i==p.length()){cin>>p;i=0;}
                  else if(p[i]==' '){i++;}
                  else if(p[i]=='\\'){i++;}
                  else {mm=mm+p[i];i++;}i++;
while (p[i]!=',')if(i==p.length()){cin>>p;i=0;}
                  else i++;i++;
while (true)if(i==p.length()){cin>>p;i=0;}
                  else if(p[i]==' '){i++;}
                  else if(p[i]=='\\'){i++;}
                  else if((p[i]<'0')||(p[i]>'9'))break;
                  else {m10=m10+p[i];i++;}
cout<<'"'<<mm<<'"'<<'='<<m10<<",\n";
}} // fin main

