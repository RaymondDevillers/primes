
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "big.h"   /* include MIRACL system */
using namespace std;

Miracl precision(20000,128);   /* bigs are 10000 centimal digits long */

char tr[128]; int w[128];


string s10(Big x)
{Big y=x; int r; string s="";
 while (y!=0){r=y%10;y=y/10;s=tr[r]+s;}
 return s;
}

main(int argc, char *argv[])
{string p,ms,mm,m10;int m,k,nn,l,i,j;
char c; Big nm,n10;
 for(char c='0';c<='9';c++){w[c]=0+c-'0';tr[0+c-'0']=c;}
 for(char c='A';c<='Z';c++){w[c]=10+c-'A';tr[10+c-'A']=c;}
 for(char c='a';c<='z';c++){w[c]=36+c-'a';tr[36+c-'a']=c;}
for(k=1;k<argc;k++)
{ms=argv[k];m=atoi(argv[k]);nn=0;
cerr<<"traitement de la base "<<ms<<"\n";cerr.flush();
while(cin>>p)
{l=p.length();nn++;
 if(p[0]!='"')cerr<<"problème de quote à la ligne"<<nn; 
 if(p[l-1]!=',')cerr<<"problème de , à la ligne"<<nn; 
 for(i=1;i<l;i++)if(p[i]=='"')
                   {mm=p.substr(1,i-1);m10=p.substr(i+2,l-i-3);break;}
  nm=0;for(i=0;i<mm.length();i++){c=mm[i];if((c>='0')&&(c<='9')){j=c-'0';} else if((c>='A')&&(c<='Z')){j=10+c-'A';} else {j=36+c-'a';} nm=nm*m+j;}
  n10=0;for(i=0;i<m10.length();i++){c=m10[i];if((c>='0')&&(c<='9'))j=c-'0'; else {cerr<<"problème 10\n";break;}n10=n10*10+j;}
  if(!prime(nm))cerr<<"problème de primalité :"<<mm<<"%"<<m10<<"|"<<s10(nm)<<"|"<<s10(n10)<<"\n"; else
  {if(nm!=n10)cerr<<"problème d'égalité :"<<mm<<"%"<<m10<<"|"<<s10(nm)<<"|"<<s10(n10)<<"\n"; else
  cout<<p<<"\n";}
}}} // fin main

