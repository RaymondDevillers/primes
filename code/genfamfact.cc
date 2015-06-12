
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
using namespace std;


main(int argc, char *argv[])
{int m,k,pp,ss,cc,l,i,j;string p,s; char c;
m=atoi(argv[1]);k=atoi(argv[2]);
p=argv[3];c=argv[4][0];s=argv[5];
pp=0;
for(i=0;i<p.length();i++)
 {if((p[i]>='0')&&(p[i]<='9')) j=p[i]-'0'; else j=10+p[i]-'A';
  pp=pp*m+j;}
ss=0;
for(i=0;i<s.length();i++)
 {if((s[i]>='0')&&(s[i]<='9')) j=s[i]-'0'; else j=10+s[i]-'A';
  ss=ss*m+j;}
if((c>='0')&&(c<='9')) cc=c-'0'; else cc=10+c-'A';
 cout<<"x:="<<pp<<":\n";
for(i=0;i<=k;i++)
 {cout<<"xx:=x*"<<m<<"^"<<s.length()<<"+"<<ss<<
        ";x:=x*"<<m<<"+"<<cc<<":\n";
  cout<<i<<";ifactor(xx);\n";
 }
// cout<<"xx;\n";
} // fin main

