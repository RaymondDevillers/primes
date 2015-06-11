//a partir d'un fichier de familles infinies, creer des familles lineaires
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
struct li{int lst[5];};

ifstream kern; ofstream ckern;

main(int argc, char *argv[])
{string p,pp,ms,pref,prefms;int i,ii,j,jj,l,m,n,k;
bool fin;
list<string> foundM,found10;
list<elem>::iterator it,itp;
string sig[5];char d[5];li rp;
list<li> listrep; list<li>::iterator itl,itm;
{ms=argv[1];
pref="kernel"; prefms=pref+ms;
kern.open(prefms.c_str());
m=atoi(argv[2]);
while(kern>>p){pp="";l=1;while(p[l]!='"'){pp=pp+p[l];l++;}
               el.mm=pp;found.push_back(el);}
while(cin>>p)
{n=0;sig[0]="";listrep.clear();//cerr<<p<<"=>\n";
 for(i=0;i<p.length();i++)
    {if(p[i]!='{'){sig[n]=sig[n]+p[i]; } else
        {if(p[i+2]!='}'){cerr<<p<<"\n";break;} else
            {n++;sig[n]="";d[n]=p[i+1];i=i+2;}
        }
    }
 if(n<=1){cout<<p<<"\n";continue;}
 for(it=found.begin();it!=found.end();it++)
    {ii=0;for(i=0;i<sig[0].length();i++)if((*it).mm[ii]==sig[0][i])ii++; 
     for(j=1;j<=n;j++)
        {rp.lst[j]=0;while((*it).mm[ii]==d[j]){rp.lst[j]++;ii++;}
         if(rp.lst[j]>m)break;
         for(i=0;i<sig[j].length();i++)if((*it).mm[ii]==sig[j][i])ii++; 
        }if(ii<(*it).mm.length())continue; 
         else {listrep.push_back(rp);//cerr<<(*it).mm<<"\n";
              }
    }
 if(listrep.empty()){cerr<<p<<"\n";continue;}
 for(i=1;i<=n;i++)
    {itm=listrep.begin();itl=itm;
     for(itl++; itl!=listrep.end(); itl++) if((*itl).lst[i]<(*itm).lst[i])itm=itl;
     for(j=0;j<=(*itm).lst[i];j++)
        {cout<<sig[0];for(ii=1;ii<i;ii++)cout<<"{"<<d[ii]<<"}"<<sig[ii];
         for(k=0;k<j;k++)cout<<d[i];cout<<sig[i];
         for(ii=i+1;ii<=n;ii++)cout<<"{"<<d[ii]<<"}"<<sig[ii];cout<<"\n";
        }
    }
}
kern.close();
}} // fin main

