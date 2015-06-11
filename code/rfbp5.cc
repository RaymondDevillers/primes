#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "big.h"   /* include MIRACL system */
#define basemax 50
#define deep 5
#define sizek 100
using namespace std;

Miracl precision(20000,128);   /* bigs are 20000 centimal digits long */

char tr[128]; int w[128];

string s10(Big x)
{Big y=x; int r; string s="";
 while (y!=0){r=y%10;y=y/10;s=tr[r]+s;}
 return s;
}

struct elem{vector <short int> t;
           };
struct node{list <short int> xtend; bool sens; // sens true=extension à gauche vers la droite
            vector <int> ptrl, ptrr;
            vector <long int> select;
           };  
ifstream kern;ofstream result,reject,court; 
unsigned short int b;
vector <int> fact; 

void printres(string s)
 {string ss; int i,j;
  ss="";j=0;
  for(i=0;i<s.length();i++)if((s[i]!='{')||(s[i+2]!='}')){ss[j]=s[i];j++;} else
    {while((j>0)&&(ss[j-1]==s[i+1]))j--;ss[j]='{';ss[++j]=s[i+1];ss[++j]='}';j++;i=i+3;
     while((i<s.length())&&(s[i]==ss[j-2]))i++;i--;
    }
  for(i=0;i<j;i++)result<<ss[i];result<<"\n";result.flush();
 }

unsigned int pgcd(unsigned long int i, unsigned long int j)
 {unsigned long int ii,jj,kk; if(i==0)return j;
  if(j>i){ii=j;jj=i;} else {ii=i;jj=j;}
 while(jj!=0){kk=ii%jj;ii=jj;jj=kk;}
  return ii;}
unsigned int min(unsigned int i, unsigned int j)
 {if(i<=j)return i;else return j;}
bool ok(long int n) // is prime?
 {unsigned int kk;
 if (n<2) return false;
 for (kk=2;kk*kk<=n;kk++)
     {if(n % kk==0)return  false;}
 return true;
 }

unsigned long int nn,nt,lt;
unsigned long int nprune[20],ntag[20];
unsigned int testprune[20],testtag[20];
bool test,modif; 
elem el;
vector<elem> found;
long int ite,ite1,ite2,c,rmax,k,chunkl,chunkr,ltmax; 
list<short int>::iterator iti1,iti2,iti0;
node auto1;vector<int>xtend; 
Big n1,n2,bj,pds,sig1,sig2,bi,bs,bm; 
bool (*cexcl)[basemax][basemax],(*cexcl2)[basemax][basemax][basemax];
 
long int petit_facteur(string ss)
 {long int i,i1,i2;Big n1;
  for(ite=0;ite<fact.size();ite++)
      {i=fact[ite];i1=0;n1=0;
       while(i1<ss.length())
        {for(i2=i1;i2<ss.length();i2++)if(ss[i2]=='{')break;else n1=n1*b+w[ss[i2]];
         if(i2== ss.length()){if((n1%i)==0)return i;else break;}
           else{n1=n1%i;for(i2++;ss[i2]!='}';i2++){if(n1!=((n1*b+w[ss[i2]])%i))break;}
                if(ss[i2]!='}')break;}i1=i2+1;
         if(i1==ss.length())if(n1==0)return i;
        }
      }return 0;
 } 
bool newprime(string s)
 {string ss;int i;
  i=0;n1=0;while(i<s.length()){if(s[i]=='{'){while(s[i]!='}')i++;i++;}
                               else{n1=n1*b+w[s[i]];ss=ss+s[i];i++;}}
  if(prime(n1)) {nprune[7]++;
      cerr<<"un nouveau prime ("<<b<<"): "<<s<<":"<<ss<<" = "<<s10(n1)<<",\n";cerr.flush();
      court<<'"'<<ss<<'"'<<"="<<s10(n1)<<",\n";court.flush();return true;}else return false;
 }
bool bp1(string s)
 {long int i,j,n=0,nn=1,ii=0,jj,jl,jl1,jjj,k,kk,nk;vector <short int> bp1l;bp1l.push_back(0);
  while(ii<s.length())
   {if(s[ii]!='{'){n=(w[s[ii]]-n+b+1)%(b+1);nn=-nn;ii++;}else
    if((s[ii]=='{')&&(s[ii+1]=='}'))ii=ii+2;else
     {jjj=bp1l.size();for(jl=0;jl<jjj;jl++)bp1l[jl]=((bp1l[jl]*nn+n+b+1)%(b+1));n=0;nn=1;
      jj=ii+1;while(s[jj]!='}')jj++;
      for(i=ii+1;i<jj;i++)for(j=i+1;j<jj;j++){k=w[s[j]]-w[s[i]];k=pgcd(k,b+1);
          if(k==1)return false;
          for(kk=k;kk<(b+1);kk=kk+k)
              {for(jl=0;jl<jjj;jl++){nk=(kk+bp1l[jl])%(b+1);
                                     for(jl1=0;jl1<bp1l.size();jl1++)
                                                      if(nk==bp1l[jl1]){jl1=-1;break;}
                                     if(jl1>=0)bp1l.push_back(nk);
                                    }
               jjj=bp1l.size();
              }
                                             }
      for(i=ii+1;i<jj;i++)for(jl=0;jl<jjj;jl++)bp1l.push_back((w[s[i]]-bp1l[jl]+b+1)%(b+1));
      ii=jj+1;
     }
   }jjj=bp1l.size();for(jl=0;jl<jjj;jl++)bp1l[jl]=((bp1l[jl]*nn+n+b+1)%(b+1));
  for(jl=0;jl<bp1l.size();jl++)
                 {if(pgcd(b+1,bp1l[jl])==1)return false;}
  return true;
 }
bool bm1(string s)
 {long int i,j,n=0,ii=0,jj,jl,jl1,jjj,k,kk,nk;vector <short int> bm1l;bm1l.push_back(0);
  while(ii<s.length())
   {if(s[ii]!='{'){n=(w[s[ii]]+n)%(b-1);ii++;}else
    if((s[ii]=='{')&&(s[ii+1]=='}'))ii=ii+2;else
     {jjj=bm1l.size();for(jl=0;jl<jjj;jl++)bm1l[jl]=((bm1l[jl]+n)%(b-1));n=0;
      jj=ii+1;while(s[jj]!='}')jj++;
      for(i=ii+1;i<jj;i++)if(s[i]!='0'){k=pgcd(w[s[i]],b-1);
          if(k==1)return false;
          for(kk=k;kk<(b-1);kk=kk+k)
              {for(jl=0;jl<jjj;jl++){nk=(kk+bm1l[jl])%(b-1);
                                     for(jl1=0;jl1<bm1l.size();jl1++)
                                                      if(nk==bm1l[jl1]){jl1=-1;break;}
                                     if(jl1>=0)bm1l.push_back(nk);
                                    }
               jjj=bm1l.size();
                                       }
              }
      ii=jj+1;
     }
   }jjj=bm1l.size();for(jl=0;jl<jjj;jl++){if(pgcd(b-1,bm1l[jl]+n)==1)return false;}
  return true;
 }
bool oddpow(string s)
 {int ii=0;sig1=0;sig2=0;
  if((b==8)||(b==27)){while(ii<s.length())if(s[ii]!='{'){sig1=sig1*b+w[s[ii]];ii++;}else break;
                     if(ii==s.length())return false;if(s[ii+1]!='0' || s[ii+2]!='}')return false;
                     ii=ii+2;bi=1;bs=sig1;   
                     while(ii<s.length()){sig2=sig2*b+w[s[ii]];ii++;}
                     while(bi<=bs){bm=(bi+bs)/2;if(sig1==bm*bm*bm)break;if(sig1>bm*bm*bm)bi=bm+1;else bs=bm-1;}
                     if(bi>bs)return false;bi=1;bs=sig2;
                     while(bi<=bs){bm=(bi+bs)/2;if(sig2==bm*bm*bm)break;if(sig2>bm*bm*bm)bi=bm+1;else bs=bm-1;}
                     if(bi>bs)return false;else return true;
                    }
  if(b==32){while(ii<s.length())if(s[ii]!='{'){sig1=sig1*b+w[s[ii]];ii++;}else break;
            if(ii==s.length())return false;if(s[ii+1]!='0' || s[ii+2]!='}')return false;
            ii=ii+2;bi=1;bs=sig1; 
            while(ii<s.length()){sig2=sig2*b+w[s[ii]];ii++;}
            while(bi<=bs){bm=(bi+bs)/2;if(sig1==bm*bm*bm*bm*bm)break;if(sig1>bm*bm*bm*bm*bm)bi=bm+1;else bs=bm-1;}
            if(bi>bs)return false;bi=1;bs=sig2;
            while(bi<=bs){bm=(bi+bs)/2;if(sig2==bm*bm*bm*bm*bm)break;if(sig2>bm*bm*bm*bm*bm)bi=bm+1;else bs=bm-1;}
            if(bi>bs)return false;else return true;
           }
  return false;
 }
string fam(list <short int> xtend)
 {string res="";list <short int> xti,rest;list<short int>::iterator iti1,iti2;
  if(xtend.empty())return res;if(xtend.size()==1){res=res+'{'+tr[xtend.front()]+'}';return res;}xti.clear();rest.clear();
  for(iti1=xtend.begin();iti1!=xtend.end();iti1++)
     {for(iti2=xtend.begin();iti2!=xtend.end();iti2++)if((iti2!=iti1)&&(*cexcl)[*iti1][*iti2]&&!(*cexcl)[*iti2][*iti1])break;
      if(iti2==xtend.end())xti.push_back(*iti1); else rest.push_back(*iti1);
     } 
   while(true) 
     {if(rest.empty()){res='{';for(iti2=xti.begin();iti2!=xti.end();++iti2)res=res+tr[*iti2];return res+'}';}
      if(xti.empty()){xti.splice(xti.begin(),rest,rest.begin());continue;}
      for(iti2=rest.begin();iti2!=rest.end();++iti2)
         {for(iti1=xti.begin();iti1!=xti.end();++iti1)if((*cexcl)[*iti1][*iti2]||!(*cexcl)[*iti2][*iti1])break;
          if(iti1!=xti.end())break;
         }
       if(iti2==rest.end()){res='{';for(iti1=xti.begin();iti1!=xti.end();++iti1)res=res+tr[*iti1];return res+'}'+fam(rest);}
       xti.splice(xti.end(),rest,rest.begin());
     }
 }
bool test3s3(int i,int j,int k,node& auto0,string& sl,string& sr )
 {string ss; 
  ss=sl+'{'; 
  for(iti0=auto0.xtend.begin();iti0!=auto0.xtend.end();++iti0)
     if(!(*cexcl2)[*iti0][i][j]&&!(*cexcl2)[*iti0][i][k]&&!(*cexcl2)[*iti0][j][k])ss=ss+tr[*iti0];
  ss=ss+'}'+tr[i]+'{';
  for(iti0=auto0.xtend.begin();iti0!=auto0.xtend.end();++iti0)
     if(!(*cexcl2)[i][*iti0][j]&&!(*cexcl2)[i][*iti0][k]&&!(*cexcl2)[*iti0][j][k])ss=ss+tr[*iti0];
   ss=ss+'}'+tr[j]+'{';
   for(iti0=auto0.xtend.begin();iti0!=auto0.xtend.end();++iti0)
      if(!(*cexcl2)[i][j][*iti0]&&!(*cexcl2)[i][*iti0][k]&&!(*cexcl2)[j][*iti0][k])ss=ss+tr[*iti0];
   ss=ss+'}'+tr[k]+'{';
   for(iti0=auto0.xtend.begin();iti0!=auto0.xtend.end();++iti0)
      if(!(*cexcl2)[i][j][*iti0]&&!(*cexcl2)[i][k][*iti0]&&!(*cexcl2)[j][k][*iti0])ss=ss+tr[*iti0];
   ss=ss+'}'+sr;
   return((petit_facteur(ss)>0)||bp1(ss)||bm1(ss));
 }
bool test2s3(int i,int j,int k,node& auto0,string& sl,string& sr )
 {string ss;
  ss=sl+'{';
  for(iti0=auto0.xtend.begin();iti0!=auto0.xtend.end();++iti0)
      if((*iti0!=k)&&!(*cexcl2)[*iti0][i][j])ss=ss+tr[*iti0];
  ss=ss+'}'+tr[i]+'{';
  for(iti0=auto0.xtend.begin();iti0!=auto0.xtend.end();++iti0)
     if((*iti0!=k)&&!(*cexcl2)[i][*iti0][j])ss=ss+tr[*iti0];
  ss=ss+'}'+tr[j]+'{';
  for(iti0=auto0.xtend.begin();iti0!=auto0.xtend.end();++iti0)
     if((*iti0!=k)&&!(*cexcl2)[i][j][*iti0])ss=ss+tr[*iti0];
  ss=ss+'}'+sr;
  return((petit_facteur(ss)>0)||bp1(ss)||bm1(ss));
 }

bool printstring(node auto0, string sl, string sr, int xplor)
 {list<short int>::iterator iti,iti0,iti1,iti2,iti3; string ss,ss1,ss2,sso,sd;vector<int>loop,nl;
  list <short int> xti; bool testl,final; int i,j,jl,ii,i1,i2,jj,kk; 
  bool excl[basemax][basemax],excl2[basemax][basemax][basemax];
  for(iti=auto0.xtend.begin();iti!=auto0.xtend.end();iti++)
     {i=*iti;   // on allonge virtuellemnt pour detecter les extensions permises
  for (ite=0;ite!=auto0.select.size();ite++)
          {
           if((auto0.ptrl[ite]==auto0.ptrr[ite])&&(i==found[auto0.select[ite]].t[auto0.ptrl[ite]]))break;}
      if(ite!=auto0.select.size()){iti=auto0.xtend.erase(iti);iti--;} // couvert
     } // fin de l'allongement virtuel
// relations entre les extensions permises
  for (iti=auto0.xtend.begin();iti!=auto0.xtend.end();++iti)
     {i=*iti;
      for (iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();++iti1)
          {j=*iti1;excl[i][j]=false;
           for (iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)excl2[i][j][*iti2]=false;
          }
     }
  for (ite=0;ite<auto0.select.size();ite++)
    if(auto0.ptrr[ite]==(1+auto0.ptrl[ite]))
      {excl[found[auto0.select[ite]].t[auto0.ptrl[ite]]][found[auto0.select[ite]].t[auto0.ptrr[ite]]]=true;
       for(k=0;k<basemax;k++)
          {excl2[found[auto0.select[ite]].t[auto0.ptrl[ite]]][found[auto0.select[ite]].t[auto0.ptrr[ite]]][k]=true;        
           excl2[found[auto0.select[ite]].t[auto0.ptrl[ite]]][k][found[auto0.select[ite]].t[auto0.ptrr[ite]]]=true;
           excl2[k][found[auto0.select[ite]].t[auto0.ptrl[ite]]][found[auto0.select[ite]].t[auto0.ptrr[ite]]]=true;
          }
      }
    else if(auto0.ptrr[ite]==(2+auto0.ptrl[ite]))   
           excl2[found[auto0.select[ite]].t[auto0.ptrl[ite]]][found[auto0.select[ite]].t[1+auto0.ptrl[ite]]][found[auto0.select[ite]].t[auto0.ptrr[ite]]]=true;
// trace
  sso=sl+"{";for (iti=auto0.xtend.begin();iti!=auto0.xtend.end();++iti)sso=sso+tr[*iti];
  sso=sso+"}"+sr+": ";
    for (iti=auto0.xtend.begin();iti!=auto0.xtend.end();++iti)
    for (iti1=iti;iti1!=auto0.xtend.end();++iti1)
       {i=*iti;j=*iti1;if((excl[i][j])&&(excl[j][i]))sso=sso+tr[i]+"<>"+tr[j]+",";
        if((excl[i][j])&&(!excl[j][i]))sso=sso+tr[j]+"<"+tr[i]+",";
        if((!excl[i][j])&&(excl[j][i]))sso=sso+tr[i]+"<"+tr[j]+",";
       }
    for (iti=auto0.xtend.begin();iti!=auto0.xtend.end();++iti)
    for (iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();++iti1)if(!excl[*iti][*iti1])
    for (iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)if((!excl[*iti][*iti2])&&(!excl[*iti1][*iti2]))
       if(excl2[*iti][*iti1][*iti2])sso=sso+"-"+tr[*iti]+"<"+tr[*iti1]+'<'+tr[*iti2]+",";
  if(xplor>=0)nn++;
  if((nn%1)==0){cerr<<nn;if(xplor<0)cerr<<'.'<<-xplor;cerr<<" ("<<b<<"):"<<sso<<" ["<<auto0.select.size()<<"]\n";cerr.flush();}  //if((nn%10000)==0)
// pruning rules
//on peut d'abord tester si, en supprimant les extensions, on n'a pas trouvé un nouveau premier
  if(newprime(sl+sr))return true;  
// certaines règles réduisent l'ensemble des extensions, et donc peuvent permettre d'appliquer des règles qui ont échoué la première fois
  modif=true;while(modif)
  {modif=false;cexcl=&excl;cexcl2=&excl2;
// on peut tester les petits facteurs pour sl{alpha}sr où alpha sont les digits qui peuvent servir pour les extensions 
   ss=sl+fam(auto0.xtend)+sr;//cerr<<"\n?"<<ss<<"\n";
   i=petit_facteur(ss);
   if(i>0){nprune[0]++;if(nprune[0]<testprune[0])cerr<<"P0:"<<ss<<"/"<<i<<"\n";return true;} 
// règle b+1
   if(bp1(ss)){nprune[1]++;if(nprune[1]<testprune[1])cerr<<"P1:"<<ss<<"\n";return true;}
// règle b-1
   if(bm1(ss)){nprune[2]++;if(nprune[2]<testprune[2]!=0)cerr<<"P2:"<<ss<<"\n";return true;}
// si un chiffre ne peut apparaitre que seul, ou en répétition immédiate, ou est incompatible avec un ou plusieurs autres, ou s'il ne peut apparaitre que seul en présence d'un autre, et si, en le conservant et en ne conservant que les configurations compatibles, on contrevient aux règles précédentes, on peut supprimer ce chiffre pour la suite! 
//   for(iti=auto0.xtend.begin();(auto0.xtend.size()>1)&&(iti!=auto0.xtend.end());iti++)
   for(iti=auto0.xtend.begin();(iti!=auto0.xtend.end());iti++)
       {i=*iti;
        if(excl[i][i])
          {xti.clear();
           for(iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();++iti1)
                  {i1=*iti1;if(!excl[i1][i])xti.push_back(i1);}  ss=sl+fam(xti)+tr[i];xti.clear();
           for(iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();++iti1)
                  {i1=*iti1;if(!excl[i][i1])xti.push_back(i1);}  ss=ss+fam(xti)+sr;
           if((petit_facteur(ss)>0)||bp1(ss)||bm1(ss))
              {nprune[3]++;if(nprune[3]<testprune[3])cerr<<"P3:"<<ss<<"\\"<<tr[i]<<"\n";
               iti=auto0.xtend.erase(iti);iti--;modif=true;continue;
              }
          }     
        for(iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();iti1++)
           {i1=*iti1;if((i!=i1)&&!excl2[i][i1][i])break;}
        if(iti1==auto0.xtend.end())
           {xti.clear();
            for(iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();++iti1)
               {i1=*iti1;if((i1!=i)&&!excl[i1][i])xti.push_back(i1);} 
            ss=sl+fam(xti)+tr[i]+'{'+tr[i]+'}';xti.clear();
            for(iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();++iti1)
               {i1=*iti1;if((i1!=i)&&!excl[i][i1])xti.push_back(i1);}  
            ss=ss+fam(xti)+sr; 
            if((petit_facteur(ss)>0)||bp1(ss)||bm1(ss))
               {nprune[4]++;if(nprune[4]<testprune[4])cerr<<"P4:"<<ss<<"\\"<<tr[i]<<"\n";
                iti=auto0.xtend.erase(iti);iti--;modif=true;continue;
               }
           }
        test=false;xti.clear();
        for(iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();iti1++)
           {i1=*iti1;if((i==i1)||(!excl[i][i1])||(!excl[i1][i]))xti.push_back(i1);else test=true;}
        if(test){ss=sl+fam(xti)+sr;
                 if((petit_facteur(ss)>0)||bp1(ss)||bm1(ss))
                    {nprune[5]++;if(nprune[5]<testprune[5])cerr<<"P5:"<<ss<<"\\"<<tr[i]<<"\n";
                     iti=auto0.xtend.erase(iti);iti--;modif=true;continue;}
                }
       } 
  if(modif)continue; 
// si un digit ne peut apparaitre qu'une fois ou en répétition immédiate et que, en sa présence, un autre ne peut apparaître qu'une fois, on peut raffiner le cas précédent
  for(iti=auto0.xtend.begin();(auto0.xtend.size()>1)&&(iti!=auto0.xtend.end());iti++)
     {i=*iti;if(excl[i][i])sd=tr[i];
             else {for(iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();iti1++)
                      {i1=*iti1;if((i!=i1)&&!excl2[i][i1][i])break;}
                   if(iti1==auto0.xtend.end()){sd=tr[i];sd=sd+"{"+tr[i]+"}";}else continue;
                  } 
      for(iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();iti1++)
         {i1=*iti1; 
          if((i1!=i)&&excl2[i1][i1][i]&&excl2[i1][i][i1]&&excl2[i][i1][i1])
            {if(!excl[i1][i])
               {xti.clear();
                for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                   {i2=*iti2;if((i2!=i)&&!excl2[i2][i1][i])xti.push_back(i2);}
                ss=sl+fam(xti)+tr[i1];xti.clear();
                for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                   {i2=*iti2;if((i2!=i)&&!excl2[i1][i2][i])xti.push_back(i2);}
                ss=ss+fam(xti)+sd;xti.clear();
                for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                   {i2=*iti2;if((i2!=i)&&!excl2[i1][i][i2])xti.push_back(i2);}
                ss=ss+fam(xti)+sr;
                if(!((petit_facteur(ss)>0)||bp1(ss)||bm1(ss)))continue;
              } 
            if(!excl[i][i1])
              {xti.clear();
               for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                  {i2=*iti2;if((i2!=i)&&!excl2[i2][i][i1])xti.push_back(i2);}
               ss=sl+fam(xti)+sd;xti.clear();
               for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                  {i2=*iti2;if((i2!=i)&&!excl2[i][i2][i1])xti.push_back(i2);}
               ss=ss+fam(xti)+tr[i1];xti.clear();
               for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                  {i2=*iti2;if((i2!=i)&&!excl2[i][i1][i2])xti.push_back(i2);}
               ss=ss+fam(xti)+sr;
               if(!((petit_facteur(ss)>0)||bp1(ss)||bm1(ss)))continue;
              }  
            xti.clear();
            for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
               {i2=*iti2;if((i2!=i)&&(i2!=i1)&&!excl[i2][i])xti.push_back(i2);}
            ss=sl+fam(xti)+sd;xti.clear();
            for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
               {i2=*iti2;if((i2!=i)&&(i2!=i1)&&!excl[i][i2])xti.push_back(i2);}
            ss=ss+fam(xti)+sr;
            if((petit_facteur(ss)>0)||bp1(ss)||bm1(ss))
               {nprune[6]++;modif=true;if(nprune[6]<testprune[6])cerr<<"P6:"<<ss<<'\\'<<tr[i]<<tr[i1]<<"\n";
                iti=auto0.xtend.erase(iti);iti--;break;
               }
            }
         } 
     }
  if(modif)continue; 
// si deux digits ne peuvent apparaitre ensemble qu'une fois, sans pour autant être limité seuls, on peut adapter le cas précédent
  for(iti=auto0.xtend.begin();(auto0.xtend.size()>2)&&(iti!=auto0.xtend.end());iti++)
     {i=*iti;if(excl[i][i])continue;
      for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();iti2++){i2=*iti2;if((i!=i2)&&!excl2[i][i2][i])break;}
      if(iti2==auto0.xtend.end())continue;iti1=iti;
      for(iti1++;iti1!=auto0.xtend.end();iti1++)
         {i1=*iti1;if(excl[i1][i1])continue;
          for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();iti2++){i2=*iti2;if((i1!=i2)&&!excl2[i1][i2][i1])break;}
          if(iti2==auto0.xtend.end())continue;
          if(excl2[i1][i1][i]&&excl2[i1][i][i1]&&excl2[i][i1][i1]&&excl2[i][i1][i]&&excl2[i1][i][i]&&excl2[i][i][i1])
            {if(!excl[i1][i])
               {xti.clear();
                for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                   {i2=*iti2;if((i2!=i)&&!excl2[i2][i1][i])xti.push_back(i2);}
                ss=sl+fam(xti)+tr[i1];xti.clear();
                for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                   {i2=*iti2;if((i2!=i)&&!excl2[i1][i2][i])xti.push_back(i2);}
                ss=ss+fam(xti)+tr[i];xti.clear();
                for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                   {i2=*iti2;if((i2!=i)&&!excl2[i1][i][i2])xti.push_back(i2);}
                ss=ss+fam(xti)+sr;
                if(!((petit_facteur(ss)>0)||bp1(ss)||bm1(ss)))continue;
               }
             if(!excl[i][i1])
               {xti.clear();
                for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                   {i2=*iti2;if((i2!=i)&&!excl2[i2][i][i1])xti.push_back(i2);}
                ss=sl+fam(xti)+tr[i];xti.clear();
                for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                   {i2=*iti2;if((i2!=i)&&!excl2[i][i2][i1])xti.push_back(i2);}
                ss=ss+fam(xti)+tr[i1];xti.clear();
                for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                   {i2=*iti2;if((i2!=i)&&!excl2[i][i1][i2])xti.push_back(i2);}
                ss=ss+fam(xti)+sr;
                if(!((petit_facteur(ss)>0)||bp1(ss)||bm1(ss)))continue;
               }  
              xti.clear();
              for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                 {i2=*iti2;if((i2!=i)&&!excl[i2][i1])xti.push_back(i2);}
              ss=sl+fam(xti)+tr[i1];xti.clear();
              for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                 {i2=*iti2;if((i2!=i)&&!excl[i1][i2])xti.push_back(i2);}
              ss=ss+fam(xti)+sr;
              if((petit_facteur(ss)>0)||bp1(ss)||bm1(ss))
                {nprune[7]++;modif=true;if(nprune[7]<testprune[7])cerr<<"P7:"<<ss<<'\\'<<tr[i1]<<tr[i]<<"\n";
                 iti1=auto0.xtend.erase(iti1);iti1--;}
              xti.clear();
              for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                 {i2=*iti2;if((i2!=i1)&&!excl[i2][i])xti.push_back(i2);}
              ss=sl+fam(xti)+tr[i];xti.clear();
              for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                 {i2=*iti2;if((i2!=i1)&&!excl[i][i2])xti.push_back(i2);}
              ss=ss+fam(xti)+sr;
              if((petit_facteur(ss)>0)||bp1(ss)||bm1(ss))
                {nprune[7]++;modif=true;if(nprune[7]<testprune[7])cerr<<"P7:"<<ss<<'\\'<<tr[i]<<tr[i1]<<"\n";
                 iti=auto0.xtend.erase(iti);iti--;break;}
             }
         }
     }
  if(modif)continue; 
// si un digit ne peut apparaitre 2 fois, et que 2 autres ne peuvent apparaître qu'une fois avec lui, on peut encore généraliser
  for(iti=auto0.xtend.begin();(auto0.xtend.size()>3)&&(iti!=auto0.xtend.end());iti++)
     if(excl[*iti][*iti])
       for(iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();iti1++)
          if((iti!=iti1)&&excl2[*iti1][*iti1][*iti]&&excl2[*iti1][*iti][*iti1]&&excl2[*iti][*iti1][*iti1])
            {iti2=iti1;iti2++;
             for(iti2=iti2;iti2!=auto0.xtend.end();iti2++)
               if((iti!=iti2)&&excl2[*iti2][*iti][*iti2]&&excl2[*iti][*iti2][*iti2]&&excl2[*iti2][*iti2][*iti])
                 {i=*iti;j=*iti1;k=*iti2;
                  if(!excl2[i][j][k])if(!test3s3(i,j,k,auto0,sl,sr))continue;
                  if(!excl2[i][k][j])if(!test3s3(i,k,j,auto0,sl,sr))continue;
                  if(!excl2[j][i][k])if(!test3s3(j,i,k,auto0,sl,sr))continue;
                  if(!excl2[j][k][i])if(!test3s3(j,k,i,auto0,sl,sr))continue;
                  if(!excl2[k][i][j])if(!test3s3(k,i,j,auto0,sl,sr))continue;
                  if(!excl2[k][j][i])if(!test3s3(k,j,i,auto0,sl,sr))continue;
                  if(!excl[i][j])if(!test2s3(i,j,k,auto0,sl,sr))continue;
                  if(!excl[i][k])if(!test2s3(i,k,j,auto0,sl,sr))continue;
                  if(!excl[j][i])if(!test2s3(j,i,k,auto0,sl,sr))continue;
                  if(!excl[k][i])if(!test2s3(k,i,j,auto0,sl,sr))continue;
                  ss=sl+'{';
                  for(iti0=auto0.xtend.begin();iti0!=auto0.xtend.end();++iti0)
                     if((*iti0!=j)&&(*iti0!=k)&&!excl[*iti0][i])ss=ss+tr[*iti0];
                  ss=ss+'}'+tr[i]+'{';
                  for(iti0=auto0.xtend.begin();iti0!=auto0.xtend.end();++iti0)
                     if((*iti0!=j)&&(*iti0!=k)&&!excl[i][*iti0])ss=ss+tr[*iti0];
                  ss=ss+'}'+sr;
                  if((petit_facteur(ss)>0)||bp1(ss)||bm1(ss))
                    {nprune[8]++;modif=true;if(nprune[8]<testprune[8])cerr<<"P8:"<<ss<<'\\'<<tr[i]<<tr[j]<<tr[k]<<"\n";
                     iti=auto0.xtend.erase(iti);iti--;iti1=auto0.xtend.end();iti1--;break;}
                 }
            }
  if(modif)continue; 
// si un digit d peut apparaitre 2 fois mais pas 3, qu'un autre ne peut apparaître plus d'une fois avec lui et que les familles correspondantes sont divisibles, on peut supprimer d pour la suite
  for(iti=auto0.xtend.begin();(auto0.xtend.size()>2)&&(iti!=auto0.xtend.end());iti++)
     if(!excl[*iti][*iti]&& excl2[*iti][*iti][*iti])
       {for(iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();iti1++)
           if((iti!=iti1)&&excl2[*iti1][*iti1][*iti]&&excl2[*iti1][*iti][*iti1]&&excl2[*iti][*iti1][*iti1])
             {i=*iti;j=*iti1;
              if(!excl2[i][i][j])if(!test3s3(i,i,j,auto0,sl,sr))continue;
              if(!excl2[i][j][i])if(!test3s3(i,j,i,auto0,sl,sr))continue;
              if(!excl2[j][i][i])if(!test3s3(j,i,i,auto0,sl,sr))continue;
              if(!excl[i][i])if(!test2s3(i,i,j,auto0,sl,sr))continue;
              if(!excl[i][j])if(!test2s3(i,j,j,auto0,sl,sr))continue;
              if(!excl[j][i])if(!test2s3(j,i,j,auto0,sl,sr))continue;
              ss=sl+'{';
              for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                 if((iti2!=iti)&&(iti2!=iti1))if(!excl[*iti2][*iti])ss=ss+tr[*iti2];
              ss=ss+'}'+tr[*iti]+'{';
              for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
                 if((iti2!=iti)&&(iti2!=iti1))if(!excl[*iti][*iti2])ss=ss+tr[*iti2];
              ss=ss+'}'+sr;
              if((petit_facteur(ss)>0)||bp1(ss)||bm1(ss))
                {nprune[9]++;modif=true;if(nprune[9]<testprune[9])cerr<<"P9:"<<ss<<'\\'<<tr[*iti]<<tr[*iti1]<<"\n";
                 iti=auto0.xtend.erase(iti);iti--;break;}
             }
       }
  if(modif)continue; 
// si un des digits d ne peut apparaître plus de k fois (k>1, sinon on est dans un cas précédent, et pas trop grand sinon la règle des petits facteurs risque de ne pas donner grand chose) et si, pour chaque répétition possible, il y a des petits facteurs, on peut supprimer d
  for(iti=auto0.xtend.begin();(auto0.xtend.size()>1)&&(iti!=auto0.xtend.end());iti++)if(!excl[*iti][*iti])
     {rmax=100;i=*iti;
      for(ite=0;ite<auto0.select.size();ite++)
         {for(j=auto0.ptrl[ite];j<=auto0.ptrr[ite];j++)if(i!=found[auto0.select[ite]].t[j])break;
          if(j>auto0.ptrr[ite])if((1+auto0.ptrr[ite]-auto0.ptrl[ite])<rmax)
              rmax=1+auto0.ptrr[ite]-auto0.ptrl[ite];
         }
      if(rmax<(b-1))
        {ss=sl+'{';for(iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();++iti1)
            if(i!=(*iti1))if(!excl[*iti1][i])ss=ss+tr[*iti1];ss=ss+'}'+tr[i];
         ss1='{'; for(iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();++iti1)
            if(i!=(*iti1))if(!excl[i][*iti1])ss1=ss1+tr[*iti1];ss1=ss1+'}'+sr;
         if(!((petit_facteur(ss+ss1)>1)||bp1(ss+ss1)||bm1(ss+ss1)))continue;
         ss=sl+'{';for(iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();++iti1)
            if(i!=(*iti1))if(!excl2[*iti1][i][i])ss=ss+tr[*iti1];ss=ss+'}'+tr[i];
         ss1='{'; for(iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();++iti1)
            if(i!=(*iti1))if(!excl2[i][i][*iti1])ss1=ss1+tr[*iti1];ss1=ss1+'}'+sr;
         ss2='{';for(iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();++iti1)
            if(i!=(*iti1))if(!excl2[i][*iti1][i])ss2=ss2+tr[*iti1];
         ss2 =ss2+'}'+tr[i];ss=ss+ss2; 
         for(k=2;k<rmax;k++)if((petit_facteur(ss+ss1)>1)||bp1(ss+ss1)||bm1(ss+ss1))ss=ss+ss2; else break;
         if(k==rmax){iti=auto0.xtend.erase(iti);iti--;nprune[10]++;modif=true; 
                       if(nprune[10]<testprune[10])cerr<<"P10:"<<ss<<'('<<ss2<<')'+ss1<<'\\'<<tr[i]<<"!"<<rmax<<"\n";
                    }
        }
     }
// si un digit d ne peut apparaître qu'une fois en présence de l'un des autres et si toutes les configurations compatibles sont divisibles, on peut supprimer d
  for(iti=auto0.xtend.begin();(auto0.xtend.size()>2)&&(iti!=auto0.xtend.end());iti++)
     for(iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();iti1++)if((iti1!=iti)&&excl2[*iti][*iti][*iti1]&&excl2[*iti][*iti1][*iti]&&excl2[*iti1][*iti][*iti])
        {i=*iti;j=*iti1;xti.clear();
         for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)if((iti1!=iti2)&&!excl[*iti2][i])xti.push_back(*iti2);ss=sl+fam(xti)+tr[i];xti.clear();
         for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)if((iti1!=iti2)&&!excl[i][*iti2])xti.push_back(*iti2);ss=ss+fam(xti)+sr;
         if(!((petit_facteur(ss)>0)||bp1(ss)||bm1(ss)))continue;xti.clear();
         for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)if((iti!=iti2)&&!excl2[*iti2][j][i])xti.push_back(*iti2);ss=sl+fam(xti)+tr[j];xti.clear();
         for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)if((iti!=iti2)&&!excl2[j][*iti2][i])xti.push_back(*iti2);ss=ss+fam(xti)+tr[i];xti.clear();
         for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)if((iti!=iti2)&&!excl2[j][i][*iti2])xti.push_back(*iti2);ss=ss+fam(xti)+sr;
         if(!((petit_facteur(ss)>0)||bp1(ss)||bm1(ss)))continue;xti.clear();
         for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)if((iti!=iti2)&&!excl2[*iti2][i][j])xti.push_back(*iti2);ss=sl+fam(xti)+tr[i];xti.clear();
         for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)if((iti!=iti2)&&!excl2[i][*iti2][j])xti.push_back(*iti2);ss=ss+fam(xti)+tr[j];xti.clear();
         for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)if((iti!=iti2)&&!excl2[i][j][*iti2])xti.push_back(*iti2);ss=ss+fam(xti)+sr;
         if((petit_facteur(ss)>0)||bp1(ss)||bm1(ss))
                {nprune[11]++;modif=true;if(nprune[11]<testprune[11])cerr<<"P11:"<<ss<<'\\'<<tr[i]<<tr[j]<<"\n";
                 iti=auto0.xtend.erase(iti);iti--;break;}
        }
 } // fin de la boucle modif  
//petite exploration avec une surapproximation des extrémités
  if(xplor==-deep)return false;
  if(auto0.sens)
    {sd="";xti.clear();test=false;
     for(iti0=auto0.xtend.begin();iti0!=auto0.xtend.end();++iti0)
        {for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
            {for(iti3=auto0.xtend.begin();iti3!=auto0.xtend.end();++iti3)
                if(excl2[*iti0][*iti2][*iti3]&&!excl[*iti2][*iti3])break;
             if(iti3!=auto0.xtend.end())break;
            }
         if(iti2==auto0.xtend.end()){test=true;sd=sd+tr[*iti0];}else xti.push_back(*iti0);
        }if(test)sd='{'+sd+'}';
     if(test||(xplor<0))
       {for(iti2=xti.begin();iti2!=xti.end();++iti2)
           {auto1=auto0;auto1.sens=false;
            for (ite=0;ite!=auto0.select.size();ite++)if((*iti2)==found[auto0.select[ite]].t[auto1.ptrl[ite]])auto1.ptrl[ite]++;
            for(iti3=auto1.xtend.begin();iti3!=auto1.xtend.end();++iti3)
               if(excl[*iti2][*iti3]){iti3=auto1.xtend.erase(iti3);iti3--;}
            if(xplor<0)
              {if(!printstring(auto1,sl+sd+tr[*iti2],sr,xplor-1))return false;}
            else
               if(!printstring(auto1,sl+sd+tr[*iti2],sr,-1))break;
           }
        if((iti2==xti.end())&&((petit_facteur(sl+sd+sr)>0)||bp1(sl+sd+sr)||bm1(sl+sd+sr)))
           {nprune[12]++;if(nprune[12]<testprune[12])cerr<<"P12:"<<sl+sd<<"{F}"<<sr<<"\n";return true;} 
       }
    }else
    {sd="";test=false;xti.clear();
     for(iti0=auto0.xtend.begin();iti0!=auto0.xtend.end();++iti0)
        {for(iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)
            {for(iti3=auto0.xtend.begin();iti3!=auto0.xtend.end();++iti3)
                if(excl2[*iti2][*iti3][*iti0]&&!excl[*iti2][*iti3])break;
             if(iti3!=auto0.xtend.end())break;
            }
          if(iti2==auto0.xtend.end()){test=true;sd=sd+tr[*iti0];}else xti.push_back(*iti0);
        }if(test)sd='{'+sd+'}';
     if(test||(xplor<0))
       {for(iti2=xti.begin();iti2!=xti.end();++iti2)
           {auto1=auto0;auto1.sens=true;
            for (ite=0;ite!=auto0.select.size();ite++)if((*iti2)==found[auto0.select[ite]].t[auto1.ptrr[ite]])auto1.ptrr[ite]--;
            for(iti3=auto1.xtend.begin();iti3!=auto1.xtend.end();++iti3)
               if(excl[*iti3][*iti2]){iti3=auto1.xtend.erase(iti3);iti3--;}
            if(xplor<0)
              {if(!printstring(auto1,sl,tr[*iti2]+sd+sr,xplor-1))return false;}
            else
               if(!printstring(auto1,sl,tr[*iti2]+sd+sr,-1))break;
           }
        if((iti2==xti.end())&&((petit_facteur(sl+sd+sr)>0)||bp1(sl+sd+sr)||bm1(sl+sd+sr)))
           {nprune[12]++;if(nprune[12]<testprune[12])cerr<<"P12:"<<sl<<"{B}"<<sd+sr<<"\n";return true;} 
       }
    }
// end of pruning<<"\n"
  if(xplor<0)return false;
// tagging rules
//  cas des extensions uniques
  if(auto0.xtend.size()==1)
    {rmax=20000;i=auto0.xtend.front();ss=sl+'{'+tr[i]+'}'+sr; 
    // règle odd power
     if(oddpow(ss)){ntag[4]++;if(ntag[4]<testtag[4])cerr<<"T4:"<<ss<<"\n";return true;}
    // sinon
     for(ite=0;ite<auto0.select.size();ite++)
        {for(j=auto0.ptrl[ite];j<=auto0.ptrr[ite];j++)if(i!=found[auto0.select[ite]].t[j])break;
         if(j>auto0.ptrr[ite])if((1+auto0.ptrr[ite]-auto0.ptrl[ite])<rmax)
           rmax=1+auto0.ptrr[ite]-auto0.ptrl[ite];
        }
     if(rmax==20000){printres(ss);return false;}
     n1=0;n2=0;pds=1;test=true; ss1=sl+'{'+tr[i]+'}'+sr;
     for(j=0;j<sl.size();j++)if(sl[j]=='{')test=false; else n1=n1*b+w[sl[j]];
     for(j=0;j<sr.size();j++)if(sr[j]=='{')test=false; else{n2=n2*b+w[sr[j]];pds=pds*b;}
     if(test)
        { ntag[5]++;if(ntag[5]<testtag[5])cerr<<"T5:"<<ss1<<'\\'<<rmax<<"\n";cerr.flush();
          for(j=1;j<rmax;j++){n1=n1*b+i;sl=sl+tr[i];if(prime(n1*pds+n2))
                               {nprune[11]++;
                                cerr<<"un nouveau prime ("<<b<<"): "<<sl+sr<<" = "<<s10(n1*pds+n2)<<",\n";
                                court<<'"'<<sl+sr<<'"'<<"="<<s10(n1*pds+n2)<<",\n";return true;
                               } 
                            } 
        return true;
        }
    }
  loop.clear();nl.clear(); 
  if(auto0.sens)for(iti=auto0.xtend.begin();iti!=auto0.xtend.end();iti++)
                    {i=*iti;for (ite=0;ite<auto0.select.size();ite++)
                     if(i==found[auto0.select[ite]].t[auto0.ptrl[ite]])break;
                     if(ite==auto0.select.size())loop.push_back(i);else nl.push_back(i);
                    }

           else for(iti=auto0.xtend.begin();iti!=auto0.xtend.end();iti++)
                   {i=*iti;for (ite=0;ite<auto0.select.size();ite++)
                    if(i==found[auto0.select[ite]].t[auto0.ptrr[ite]])break;
                    if(ite==auto0.select.size())loop.push_back(i);else nl.push_back(i);
                   }
  if(loop.empty())ss=sl+sr; else
    {ss=sl+'{';for(i=0;i<loop.size();i++)ss=ss+tr[loop[i]];ss=ss+'}'+sr;}
  switch(true)
    {default:
// règle prime
     j=0;for(i=0;i<ss.size();i++)if(ss[i]=='{')j++;
     if(j==0)if(!newprime(ss)){ntag[2]++;if(ntag[2]<testtag[2])cerr<<"T2:"<<ss<<"\n";break;}
// règle petit facteur
     if(petit_facteur(ss)>1){ntag[0]++;
                             if(ntag[0]<testtag[0])cerr<<"T0:"<<ss<<'/'<<petit_facteur(ss)<<"\n";break;
                            }
// règle b+1
     if(bp1(ss)){ntag[1]++;if(ntag[1]<testtag[1])cerr<<"T1:"<<ss<<"\n";break;}
// règle b-1
     if(bm1(ss)){ntag[3]++;if(ntag[3]<testtag[3])cerr<<"T3:"<<ss<<"\n";break;}
// règle odd power
     if(oddpow(ss)){ntag[4]++;if(ntag[4]<testtag[4])cerr<<"T4:"<<ss<<"\n";break;}
//  famille encore à considérer       
  if(xplor>=0)printres(ss);    else return false;
                   }
  if(nl.empty())return true;
// rejet car trop long
  if(auto0.xtend.size()>1)if(xplor==0){nt++;ss=sl+'<';
    for (iti=auto0.xtend.begin();iti!=auto0.xtend.end();++iti)ss=ss+tr[*iti];
    ss=ss+'>'+sr;reject<<ss<<":";
    for (iti=auto0.xtend.begin();iti!=auto0.xtend.end();++iti)
    for (iti1=iti;iti1!=auto0.xtend.end();++iti1)
       {i=*iti;j=*iti1;if((excl[i][j])&&(excl[j][i]))reject<<tr[i]<<"<>"<<tr[j]<<",";
        if((excl[i][j])&&(!excl[j][i]))reject<<tr[j]<<"<"<<tr[i]<<",";
        if((!excl[i][j])&&(excl[j][i]))reject<<tr[i]<<"<"<<tr[j]<<",";
       }
    for (iti=auto0.xtend.begin();iti!=auto0.xtend.end();++iti)
    for (iti1=auto0.xtend.begin();iti1!=auto0.xtend.end();++iti1)if(!excl[*iti][*iti1])
    for (iti2=auto0.xtend.begin();iti2!=auto0.xtend.end();++iti2)if((!excl[*iti][*iti2])&&(!excl[*iti1][*iti2]))
       if(excl2[*iti][*iti1][*iti2])reject<<"-"<<tr[*iti]<<"<"<<tr[*iti1]<<'<'<<tr[*iti2]<<",";
    reject<<"\n";reject.flush();return false;} 
  else if(xplor>=0)if(ltmax<(lt-xplor))ltmax=lt-xplor;
// itération suivante
  if(auto0.sens)
    {if(!loop.empty()){sl=sl+'{';for(i=0;i<loop.size();i++)sl=sl+tr[loop[i]];sl=sl+'}';}
     for(i=0;i<nl.size();i++)
        {auto1.sens=false;auto1.xtend=auto0.xtend;auto1.select.clear();auto1.ptrl.clear();auto1.ptrr.clear();
         for(ite=0;ite<auto0.select.size();ite++)
            {if((nl[i])==found[auto0.select[ite]].t[auto0.ptrl[ite]])j=auto0.ptrl[ite]+1; else j=auto0.ptrl[ite];
             k=auto0.ptrr[ite];
             for(jj=j;jj<=k;jj++){kk=found[auto0.select[ite]].t[jj];
                                  for (iti=auto0.xtend.begin();iti!=auto0.xtend.end();++iti)if(kk==(*iti))break;
                                  if(iti==auto0.xtend.end())break;
                                 }
             if(jj>k){auto1.select.push_back(auto0.select[ite]);
                      auto1.ptrl.push_back(j);auto1.ptrr.push_back(k);
                     }
            }
         printstring(auto1,sl+tr[nl[i]],sr,xplor-1);
        }
    }else
    {if(!loop.empty()){sr='}'+sr;for(i=0;i<loop.size();i++)sr=tr[loop[i]]+sr;sr='{'+sr;}
     for(i=0;i<nl.size();i++)
        {auto1.sens=true;auto1.xtend=auto0.xtend;auto1.select.clear();auto1.ptrl.clear();auto1.ptrr.clear();
         for(ite=0;ite<auto0.select.size();ite++)
            {if((nl[i])==found[auto0.select[ite]].t[auto0.ptrr[ite]])k=auto0.ptrr[ite]-1; else k=auto0.ptrr[ite];
             j=auto0.ptrl[ite];
             for(jj=j;jj<=k;jj++){kk=found[auto0.select[ite]].t[jj];
                                  for (iti=auto0.xtend.begin();iti!=auto0.xtend.end();++iti)if(kk==(*iti))break;
                                  if(iti==auto0.xtend.end())break;
                                 }
             if(jj>k){auto1.select.push_back(auto0.select[ite]);
                      auto1.ptrl.push_back(j);auto1.ptrr.push_back(k);
                     }
            }
         printstring(auto1,sl,tr[nl[i]]+sr,xplor-1);
        }
    }
 return true;
}
  
void handlebase()
{string p,sr,sl;long int k,kkk;node auto0,auto1;
 short int ir,il,i,j;int ii,kk,ilb,ilh,irb,irh;
 clock_t cpustarttime,cputime; 

 cpustarttime=clock();cerr<<"traitement de la base "<<b;
 ltmax=1;
 if(chunkl!=0)cerr<<" pour le chiffre initial "<<chunkl;
 if(chunkr!=0)cerr<<" et pour le chiffre terminal "<<chunkr;
 cerr<<"\n";
 for (i=0;i<20;i++){nprune[i]=0;ntag[i]=0;}
 found.clear();nt=0;
 while(kern>>p)
      {el.t.clear();
       for(i=1;p[i]!='"';i++){el.t.push_back(w[p[i]]);}
       if(i>sizek)break;
       found.push_back(el);
      }
 for(i=2;i<b*b;i++)if(ok(i))fact.push_back(i);
// initialisation
 if(chunkl==0){ilb=1;ilh=b;} else {ilb=chunkl;ilh=chunkl+1;}
 if(chunkr==0){irb=1;irh=b;} else {irb=chunkr;irh=chunkr+1;}
 for(il=ilb;il<ilh;il++)
    {if(!ok(il))
       {for(ir=irb;ir<irh;ir++)
           {if(!ok(ir))
              {if(pgcd(ir,b)==1)
                 {auto0.xtend.clear(); auto0.ptrl.clear(); auto0.ptrr.clear(); auto0.select.clear();auto0.sens=true;
                  for(j=0;j<b;j++)if(!ok(j))auto0.xtend.push_back(j);
                  for (ite2=0;ite2!=found.size();++ite2)
                      {ii=found[ite2].t.size()-1;if(ir==found[ite2].t[ii])ii--;
                       kk=0;if(il==found[ite2].t[0])kk=1;if(kk>ii)break;
                       auto0.ptrr.push_back(ii);auto0.ptrl.push_back(kk);auto0.select.push_back(ite2);
                      }
                  if(ite2==found.size()) // on n'a pas un premier à 2 chiffres
                    {sr=tr[ir];sl=tr[il]; printstring(auto0,sl,sr,lt);}
//construction des familles à explorer à  partir du premier et du dernier chiffre
                 }
              }
          }
      }
   }
 cputime = clock()-cpustarttime; cputime=cputime/1000000;
 result<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
 result<<"\nA la fin, on a exploré "<<nn<<" familles de nombres pour la base "<<b;
 if(chunkl!=0)result<<" et le chiffre initial "<<chunkl;
 if(chunkr!=0)result<<" et le chiffre terminal "<<chunkr;
 result<<"\n on a pu appliquer en pruning ";
 for (i=0;i<20;i++)if(nprune[i]!=0)result<<nprune[i]<< " règles "<<i<<" , ";
 result<<"\n on a pu appliquer en tagging ";
 for (i=0;i<20;i++)if(ntag[i]!=0)result<<ntag[i]<< " règles "<<i<<" , ";
 result<<"\n en "<<cputime<<" secondes\n"; 
 cerr<<"\nla taille maximum considérée a été de "<<ltmax<<"\n";
 result<<"la taille maximum considérée a été de "<<ltmax<<"\n";
 result.flush();
 if(nt>0){cerr<<"on a effectué "<<nt<<" troncatures "<<"à la taille "<<lt<<" pour la base "<<b;
          if(chunkl!=0)cerr<<" et le chiffre initial "<<chunkl;
          if(chunkr!=0)cerr<<" et le chiffre terminal "<<chunkr;cerr<<"\n";
          result<<"on a effectué "<<nt<<" troncatures\n";
         }
} // fin du traitement de la base

main(int argc, char *argv[])
// call base rejectsize [firstdigit [lastdigit]]
{string ms,pref,prefms;
 ms=argv[1];b=atoi(argv[1]);lt=atoi(argv[2]);
 pref="kernel"; prefms=pref+ms;
 kern.open(prefms.c_str());
 if(argc>3){chunkl=atoi(argv[3]);ms=ms+'-'+argv[3];}else{chunkl=0;}
 if(argc>4){chunkr=atoi(argv[4]);ms=ms+'-'+argv[4];}else{chunkr=0;}
 pref="resfb"; prefms=pref+ms; 
 result.open(prefms.c_str(),ios::out);
 pref="xfb"; prefms=pref+ms;
 court.open(prefms.c_str(),ios::out);
 pref="rejfb"; prefms=pref+ms;
 reject.open(prefms.c_str(),ios::out);
 for(char c='0';c<='9';c++){w[c]=0+c-'0';tr[0+c-'0']=c;}
 for(char c='A';c<='Z';c++){w[c]=10+c-'A';tr[10+c-'A']=c;}
 for(char c='a';c<='z';c++){w[c]=36+c-'a';tr[36+c-'a']=c;}
 for(int i=0;i<20;i++){testprune[i]=1000;testtag[i]=1000;}
 handlebase();
} // fin main
