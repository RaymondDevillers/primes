
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

ifstream kern; 
bool cover(string el1,string el2)
 {int i,j,k;
  if(el1.length()==el2.length())return false;
  if(el1.length()>el2.length())return(false);
  i=0;j=0;
  while(i<el1.length())
  {if(el1[i]==el2[j])
     {i++;j++;if(i==el1.length())return true;if(j>=el2.length())return false;}
   else{j++;if(j>=el2.length())return false;}
  }
  return true;
 }
main(int argc, char *argv[])
{string p,ms,pref,prefms,mm,m10;
int m,k,nn,l,i,j;
int w[128];
char c; 
Big nm,n10,on;
list<string> foundM;
list<string>::iterator itM;
for(i=0;i<128;i++)w[i]=-1;
 for(char c='0';c<='9';c++){w[c]=0+c-'0';tr[0+c-'0']=c;}
 for(char c='A';c<='Z';c++){w[c]=10+c-'A';tr[10+c-'A']=c;}
 for(char c='a';c<='z';c++){w[c]=36+c-'a';tr[36+c-'a']=c;}
for(k=1;k<argc;k++)
{ms=argv[k];m=atoi(argv[k]);
pref="kernel"; prefms=pref+ms;
kern.open(prefms.c_str());
nn=0;
cerr<<"\nTraitement de la base "<<m<<"\n";
while(kern>>p)
{nn++;l=p.length();if((nn%1000)==0)cerr<<nn<<':'<<p<<"\n";
 if(p[0]!='"'){cerr<<"problème de quote à la ligne "<<nn<<" = "+p;break; }
 if(p[l-1]!=','){cerr<<"problème de , à la ligne "<<nn<<" = "+p;break; }
 for(i=1;i<l;i++)if(p[i]=='"')
                   {mm=p.substr(1,i-1);m10=p.substr(i+2,l-i-3);break;}
 if(i==l){cerr<<"problème de quote à la ligne "<<nn<<" = "+p;break; }
 if(p[i+1]!='='){cerr<<"problème de = à la ligne "<<nn<<" = "+p;break; }
 l=mm.length();nm=0;
 for(i=0;i<l;i++)if((w[mm[i]]==-1)||(w[mm[i]]>=m))
    {cerr<<"problème de base à la ligne "<<nn<<" = "+p;break; }
    else{nm=nm*m+w[mm[i]];}
 l=m10.length();n10=0;
 for(i=0;i<l;i++)if((w[m10[i]]==-1)||(w[m10[i]]>=10))
    {cerr<<"problème de base 10 à la ligne "<<nn<<" = "+p;break; }
    else{n10=n10*10+w[m10[i]];}
 if(!prime(nm)){cerr<<"problème de primalité à la ligne "<<nn<<" = "+p;break; }
 if(nm!=n10){cerr<<"problème d'égalité à la ligne "<<nn<<" = "+p;break; }
 if((nn>1)&&(on>nm))
   {cerr<<"problème d'ordre à la ligne "<<nn<<" = "+p;break; }
 itM=foundM.begin();on=nm;
 while(itM!=foundM.end())
  {if(cover(*itM,mm)){cerr<<"problème de dominance à la ligne "<<nn<<" = "+p<<" parrapport à "+*itM;break; } else itM++;
  }if(itM!=foundM.end())break;
 foundM.push_back(mm);
}
cerr<<"on s'arrête à la ligne "<<nn;foundM.clear();kern.close();
}} // fin main

