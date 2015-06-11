
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
#include <stdlib.h>
using namespace std;

struct elem{string mm;};
list<elem> found;elem el;

ifstream kern; ofstream ckern;
bool cover(string el1,string el2)
 {int i,j;
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
{string p,pp,ms,pref,prefms;int m,l,i,j;
bool fin;
list<string> foundM,found10;
list<elem>::iterator it,itp;
{ms=argv[1];
pref="kernel"; prefms=pref+ms;
kern.open(prefms.c_str());
m=atoi(argv[2]);
while(kern>>p){pp="";l=1;while(p[l]!='"'){pp=pp+p[l];l++;}
               el.mm=pp;found.push_back(el);}
while(cin>>p)
{l=0;pp="";
 while(p[l]!='{'){pp=pp+p[l];l++;}
 if(p[l+2]!='}'){cerr<<"ERREUR 0:"<<p<<"\n";break;}
 for(i=1;i<=m;i++){pp=pp+p[l+1];}l=l+3;
 while(l<p.length()){pp=pp+p[l];l++;}
 for(it=found.begin();it!=found.end();it++)if(cover((*it).mm,pp))break;
 if(it==found.end())cerr<<p<<"\n"; else cout<<p<<"\n";
}
kern.close();
}} // fin main

