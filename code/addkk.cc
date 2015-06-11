
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
#include <stdlib.h>
using namespace std;

struct elem{string mm, m10;};
list<elem> found; elem el;

ifstream kern; ofstream ckern;
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
int order(string el1,string el2)
 {int i;
  if(el1.length()>el2.length())return 1;
  if(el1.length()<el2.length())return 2;
  i=0;
  while(i<el1.length())
  {if(el1[i]==el2[i])i++;
   else if(el1[i]<el2[i])return 2;
   else return 1;
  }
  return 0;
 }

main(int argc, char *argv[])
{string p,ms,pref,prefms,mm,m10,mM,md;int m,k,nn,l,i,j;
bool fin;
list<string> foundM,found10;
list<elem>::iterator it,itp;
for(k=1;k<argc;k++)
{ms=argv[k];m=atoi(argv[k]);
pref="kernel"; prefms=pref+ms;
kern.open(prefms.c_str());
nn=0;
while(kern>>p)
{l=p.length();
 if(p[0]!='"'){cerr<<"problème de quote à la ligne"<<p; }
 if(p[l-1]!=','){p=p+",";cerr<<"problème de , à la ligne"<<p; }
 for(i=1;i<l;i++)if(p[i]=='>')
                   {p='"'+p.substr(i+1,l-1);l=p.length();break;}
 for(i=1;i<l;i++)if(p[i]=='"')
                   {mm=p.substr(1,i-1);m10=p.substr(i+2,l-i-3);break;}
 el.mm=mm;el.m10=m10;found.push_back(el);
}cerr<<"on demarre avec "<<found.size()<<" membres\n";
while(cin>>p)
{nn++;if((nn%1000)==0)cerr<<ms<<":"<<p<<"("<<found.size()<<")\n";
 l=p.length();
 if(p[0]!='"'){cerr<<"problème de quote à la ligne"<<p; }
 if(p[l-1]!=','){p=p+",";cerr<<"problème de , à la ligne"<<p; }
 for(i=1;i<l;i++)if(p[i]=='>')
                   {p='"'+p.substr(i+1,l-1);l=p.length();break;}
 for(i=1;i<l;i++)if(p[i]=='"')
                   {mm=p.substr(1,i-1);m10=p.substr(i+2,l-i-3);break;}
 for(it=found.begin();it!=found.end();it++)
    {if((*it).mm.size()<mm.size()){if(cover((*it).mm,mm))break;}else break;}
 if(it==found.end()){el.mm=mm;el.m10=m10;found.push_back(el);continue;}
 if((*it).mm.size()<mm.size())continue;
 while((*it).mm.size()==mm.size())
   {k=order(mm,(*it).mm);
    if(k==0)break;
    if(k==2)
      {el.mm=mm;el.m10=m10;found.insert(it,el);
       while((*it).mm.size()==mm.size())it++;break;
      }
    it++;
   }
 if(k==0)continue;
 if(k==1){el.mm=mm;el.m10=m10;found.insert(it,el);}
 while(it!=found.end())
    {if(cover(mm,(*it).mm))it=found.erase(it); else it++;}
}cerr<<"on termine avec "<<found.size()<<" membres\n";
for(it=found.begin();it!=found.end();it++)
    cout<<'"'<<(*it).mm<<'"'<<'='<<(*it).m10<<",\n";
kern.close();
}} // fin main

