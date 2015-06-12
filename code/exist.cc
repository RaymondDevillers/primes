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
bool coverexact(string el2,string el1)
 {int i,j;
  i=0;j=0;
  while(i<el1.length())
  {if(j==el2.length())return false;
   if(el1[i]==el2[j]){i++;j++;continue;}
   if(el1[i]=='{'){while(el2[j]==el1[i+1])j++;i=i+3;continue;}
   return false;
  }
  if(j==el2.length())return true;else return false;
 }

main(int argc, char *argv[])
{string p,pp,ms,pref,prefms;int m,l,i,j;
bool fin;
list<string> foundM,found10;
list<elem>::iterator it,itp;
{ms=argv[1];
pref="kernel"; prefms=pref+ms;
kern.open(prefms.c_str());
while(kern>>p){pp="";l=1;while(p[l]!='"'){pp=pp+p[l];l++;}
               el.mm=pp;found.push_back(el);}
while(cin>>p)
{l=0;
 while(p[l]!='{')l++;
 if(p[l+2]!='}'){cerr<<"ERREUR 0:"<<p<<"\n";break;}l=l+3;
 while(l<p.length())if(p[l]=='{'){cerr<<"ERREUR 1:"<<p<<"\n";break;}else l++;
 for(it=found.begin();it!=found.end();it++)if(coverexact((*it).mm,p))break;
 if(it==found.end())cerr<<p<<"\n"; else cout<<p<<"\n";
}
kern.close();
}} // fin main

