
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
using namespace std;


main(int argc, char *argv[])
{int m,k,deploy,pp,ss,cc,l,i,j;string p,s,ms,fam,famms,prefms; char c;
 ifstream families;
for(k=1;k<argc-1;k++)
{ms=argv[k];m=atoi(argv[k]);deploy=atoi(argv[argc-1]);
fam="fam"; famms=fam+ms;
families.open(famms.c_str());
while(families>>p>>c>>s)
{cout<<'"'<<"m="+ms+": "+p+"{"+c+"}"+s+'"'+";\n";
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
for(i=0;i<=deploy;i++)
 {cout<<"xx:=x*"<<m<<"^"<<s.length()<<"+"<<ss<<
        ":x:=x*"<<m<<"+"<<cc<<":\n";
  cout<<"["<<i<<",isprime(xx)";
  if(i<20)cout<<",ifactor(xx)];"; else cout<<"];";
 }
// cout<<"xx;\n";
}
families.close();}
} // fin main

