
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

string itos(int i)	// convert int to string
 {stringstream s;s << i;return s.str();}

string cvrt(char c)
  {if((c>='0')&&(c<='9')) return itos(c-'0'); else return itos(10+c-'A');}

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
{nn++;if((nn%10000)==0)cerr<<ms<<":"<<p<<"\n";
 l=p.length();
 if(p[0]!='"'){cout<<"problème de quote à la ligne"<<p; }
 if(p[l-1]!=','){p=p+",";cout<<"problème de , à la ligne"<<p; }
 for(i=1;i<l;i++)if(p[i]=='>')
                   {p='"'+p.substr(i+1,l-1);l=p.length();break;}
 for(i=1;i<l;i++)if(p[i]=='"')
                   {mm=p.substr(1,i-1);m10=p.substr(i+2,l-i-3);break;}
 for(it=found.begin();it!=found.end();it++)if(cover((*it).mm,mm))break;
 if(it==found.end())
 {it=found.begin();while(it!=found.end())
    {if(cover(mm,(*it).mm))it=found.erase(it); else it++;}
  for(it=found.begin();it!=found.end();it++)
   {if(order(mm,(*it).mm)==0)break;
    if(order(mm,(*it).mm)==2)
      {el.mm=mm;el.m10=m10;found.insert(it,el);break;}
   }
  if(it==found.end()){el.mm=mm;el.m10=m10;found.push_back(el);}
 }
}
while(cin>>p)
{nn++;if((nn%10000)==0)cerr<<ms<<":"<<p<<"("<<found.size()<<")\n";
 l=p.length();
 if(p[0]!='"'){cout<<"problème de quote à la ligne"<<p; }
 if(p[l-1]!=','){p=p+",";cout<<"problème de , à la ligne"<<p; }
 for(i=1;i<l;i++)if(p[i]=='>')
                   {p='"'+p.substr(i+1,l-1);l=p.length();break;}
 for(i=1;i<l;i++)if(p[i]=='"')
                   {mm=p.substr(1,i-1);m10=p.substr(i+2,l-i-3);break;}
 for(it=found.begin();it!=found.end();it++)if(cover((*it).mm,mm))break;
 if(it==found.end())
 {it=found.begin();while(it!=found.end())
    {if(cover(mm,(*it).mm))it=found.erase(it); else it++;}
  for(it=found.begin();it!=found.end();it++)
   {if(order(mm,(*it).mm)==0)break;
    if(order(mm,(*it).mm)==2)
      {el.mm=mm;el.m10=m10;found.insert(it,el);break;}
   }
  if(it==found.end()){el.mm=mm;el.m10=m10;found.push_back(el);}
 }
}
for(it=found.begin();it!=found.end();it++)
    cout<<'"'<<(*it).mm<<'"'<<'='<<(*it).m10<<",\n";
kern.close();
}} // fin main

