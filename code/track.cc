 
#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>

using namespace std;

struct elem{vector <short int> t;
           };
struct node{list <short int> nexti; 
            list <short int> l; 
            vector <int> ptr; vector <short int> mp1;
            unsigned long int modmm1, modlmm1, gcd, gcdll, gcdf, gcdl, dist, nbl;
            bool court,final,loopnpb;
           };
// gcd= gcd des chiffres de tous les arcs menant au noeud
// gcdll= gcd des chiffre des self-loops sur le noeud
// gcdf= dernier sigma menant au noeud
// gcdl= gcd des self-loops et sigmas précédents
// modlmm1= gcd des chiffre des self-loops menant au noeud
// modmm1= somme (modulo m-1) des arcs progressant vers le noeud
// court= pas de boucle avant ni de découpage du premier sigma
// final= noeud peut correspondre à des strings à tester
// loopnpb= la boucle locale n'est pas première avec la base
// nbl= nombre de boucles sur le chemin
//nt= nbre max de boucles sur un chemin
string tr; ifstream kern,R;
void printelem(elem el)
 {int iti; 
  cout<<'"';
  for (iti=0;iti<el.t.size();++iti)cout<<tr[el.t[iti]];
  cout<<'"'<<"\n";cout.flush();}

bool cover(elem el1,elem el2)
 {int iti1,iti2;
  if(el1.t.size()<el2.t.size())
    {cout<<"problème d'ordre:";cout<<"problème d'ordre";cout.flush();
     printelem(el1);printelem(el2);
    }
  if(el1.t.size()==el2.t.size())return(false);
  iti1=0;iti2=0;
  while(iti2<el2.t.size())
       {if(el1.t[iti1]==el2.t[iti2]){iti1++;iti2++;
             if((iti1==el1.t.size())&&(iti2<el2.t.size())){return(false);}}
        else{iti1++;if(iti1==el1.t.size()){return(false);}}}
  cout<<"problème de dominance entre\n";cout<<"problème de dominance\n";
  printelem(el1);printelem(el2);cout.flush();
  return(true);
 }

void printnode(node el)
 {list<short int>::iterator iti; 
  int i;
//  if(el.nexti.empty() && el.l.empty())return;
  cout<<"{";
  for (iti=el.nexti.begin();iti!=el.nexti.end();++iti)
      {cout<<*iti;} cout<<"}[";cout.flush();
  for (iti=el.l.begin();iti!=el.l.end();++iti)
      {cout<<*iti<<",";cout.flush();}
  cout<<"]";cout<<el.gcd<<","<<el.gcdl<<","<<el.gcdf<<","<<el.gcdll
     <<","<<el.modlmm1<<","<<el.modmm1<<";"<<el.court<<el.loopnpb<<el.final<<",[";
  for(i=0;i<el.mp1.size();i++)cout<<el.mp1[i]<<",";cout<<"]\n";
  cout.flush();}

unsigned int pgcd(unsigned long int i, unsigned long int j)
 {unsigned long int ii,jj,kk; if(i==0)return j;if(j==0)return i;
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

short int si,i,i1,j,ii;
unsigned long int m,g,jj,jjj,n,nn,ip, 
             nn1p,nn1,nn2,nn2p,nn3,nn42,nn42p,nn43,nn4,nn5,nn6,nn7,nn7p,nn8,nn8p,nn9,nt;
bool test; string p; char c;
long int cpustarttime; double cputime; 
elem el;
vector<elem> found;
int ite,ite1,ite2;
list<short int>::iterator iti1,iti2;
node auto1;vector<int>xtend; 
  
void printstring(node auto0,string s,int m)
 {list<short int>::iterator iti;
  xtend.clear();nn++;
  for (iti=auto0.nexti.begin();iti!=auto0.nexti.end();++iti)
      xtend.push_back(*iti);
  for (iti=auto0.l.begin();iti!=auto0.l.end();++iti)
      xtend.push_back(*iti);
  auto0.nexti.clear();auto0.l.clear();
  for (ii=0;ii<xtend.size();++ii)
    {i=xtend[ii];   // on allonge
      test=false;
      for (ite=0;ite<found.size();ite++)
      if(i==found[ite].t[auto0.ptr[ite]]){test=true;
        if(auto0.ptr[ite]==(found[ite].t.size()-1))break;}
     if(ite==found.size())
      // il n'est pas couvert; test indique si c'est une self-loop
      {if(test){auto0.l.push_back(i);}else {auto0.nexti.push_back(i);}}
    } // fin de l'allongement
   test=true;j=0; for (iti=auto0.nexti.begin();iti!=auto0.nexti.end();++iti) 
   {if(pgcd(m,*iti)==1)test=false;j=pgcd(j,*iti);} auto0.loopnpb=test;
   auto0.gcdll=j; // gcdll = gcd de la boucle locale
   if(auto0.nexti.size()>1)auto1.mp1.clear();
   else if(auto0.nexti.size()==1)
          {jjj=auto0.mp1.size();
           for(jj=0;jj<jjj;jj++)
        auto0.mp1.push_back((auto0.nexti.front()-auto0.mp1[jj]+m+1)%(m+1));}
//
   iti=auto0.l.begin();
   while(iti!=auto0.l.end())
   if(pgcd(m,*iti)==1) iti++; else // *iti ne peut être un chiffre final
   {test=false;i=*iti;
    for (iti1=auto0.nexti.begin();iti1!=auto0.l.end();++iti1)
    {if(iti1==auto0.nexti.end())iti1=auto0.l.begin();
    if(pgcd(m,*iti1)==1) // on teste si un chiffre final peut suivre
      {i1=*iti1;for (ite=0;ite<found.size();ite++)
          if(found[ite].t.size()==(2+auto0.ptr[ite]))
          if(i==found[ite].t[auto0.ptr[ite]])
          if(i1==found[ite].t[auto0.ptr[ite]+1])break;
       if(ite==found.size()){test=true;break;}
      }}
    if(!test){cout<<"<<"<<*iti<<">>";iti=auto0.nexti.erase(iti);}else{iti++;}
//suppression des chiffres non-terminaux qui ne peuvent être suivis d'un terminal
  } 
   {cout<<"\n"<<nn<<":"<<s<<"[";
    for (iti=auto0.nexti.begin();iti!=auto0.nexti.end();++iti)
        cout<<tr[*iti];
    cout<<".";
    for (iti=auto0.l.begin();iti!=auto0.l.end();++iti)
        cout<<tr[*iti];
    cout<<"]\n";printnode(auto0);}
        for(iti=auto0.nexti.begin();iti!=auto0.nexti.end();iti++)
        for(iti1=auto0.l.begin();iti1!=auto0.l.end();iti1++)
        {i=*iti;i1=*iti1;
         for(ii=0;ii<found.size();ii++)
          if(found[ii].t.size()==(2+auto0.ptr[ii]))
          if(i==found[ii].t[auto0.ptr[ii]])
          if(i1==found[ii].t[auto0.ptr[ii]+1])break;
         if(ii<found.size())cout<<"<"<<*iti<<","<<*iti1<<"> ";}
        for(iti=auto0.l.begin();iti!=auto0.l.end();iti++)
        for(iti1=auto0.l.begin();iti1!=auto0.l.end();iti1++)
        {i=*iti;i1=*iti1;
         for(ii=0;ii<found.size();ii++)
          if(found[ii].t.size()==(2+auto0.ptr[ii]))
          if(i==found[ii].t[auto0.ptr[ii]])
          if(i1==found[ii].t[auto0.ptr[ii]+1])break;
         if(ii<found.size())cout<<"<"<<*iti<<","<<*iti1<<"> ";}cout<<"\n";cout.flush();
  ip++;if(p[ip]=='[')return;if(p[ip]=='{')ip=ip+3;c=p[ip];if(c>='A')i=10+c-'A';else i=c-'0';
  {auto1=auto0;ite=0;
   for (ite=0;ite<found.size();ite++)
      {if((i)==found[ite].t[auto1.ptr[ite]])auto1.ptr[ite]++;} 
   auto1.final=true;auto1.gcd=pgcd(pgcd(auto0.gcd,auto0.gcdll),i);
   auto1.modlmm1=pgcd(auto0.modlmm1,auto0.gcdll);
   auto1.modmm1=(auto0.modmm1+i)%(m-1);
   for(jj=0;jj<auto1.mp1.size();jj++)
              auto1.mp1[jj]=(i-auto1.mp1[jj]+m+1)%(m+1);
   if(!auto0.nexti.empty())
     {auto1.gcdl=pgcd(pgcd(auto1.gcdl,auto1.gcdf),auto0.gcdll);
      auto1.gcdf=i;auto1.court=false;}
   else{jj=(auto1.gcdf)*m+(i);
        if(((jj-(i))/m)!=auto1.gcdf)
    {auto1.gcdl=pgcd(auto1.gcdl,auto1.gcdf);
     auto1.gcdf=(i);auto1.court=false;}
        else auto1.gcdf=jj;}
   printstring(auto1,s+c,m);
  }
}

void handlebase(unsigned int m)
 {string s;long int k,kkk;node auto0,auto1;short int i;int ii;
found.clear();
for (i=0;i<min(m,10);i++)tr.push_back('0'+i);
for (i=10;i<m;i++)tr.push_back('A'+i-10);
while(kern>>p)
{el.t.clear();//cout<<p<<"\n";
 for(i=1;p[i]!='"';i++){if(p[i]<'A'){el.t.push_back(p[i]-'0');}
                        else{el.t.push_back(10+p[i]-'A');}}
 found.push_back(el);
}
R>>p;ip=0;cout<<p<<"\n";
for (ite1=0;ite1!=found.size();++ite1)
    for (ite2=0;ite2!=ite1;++ite2)cover(found[ite1],found[ite2]);
nn=0;
// initialisation
c=p[ip];if(c>='A')i=10+c-'A'; else i=c-'0';
 auto0.nexti.clear(); auto0.l.clear(); auto0.ptr.clear();
 for(j=0;j<m;j++)if(!ok(j))auto0.l.push_back(j);
  for (ite2=0;ite2!=found.size();++ite2)
   {if(i==found[ite2].t[0])ii=1; else ii=0;auto0.ptr.push_back(ii);}
 auto0.modmm1=i%(m-1); auto0.modlmm1=0; auto0.nbl=0;
 auto0.mp1.clear(); auto0.mp1.push_back(i);
 auto0.final=false;auto0.loopnpb=false;auto0.court=true;
 auto0.gcd=i; auto0.gcdl=0;auto0.gcdll=0;auto0.gcdf=i;s=c;
  printstring(auto0,s,m);
} // fin du traitement de la base

main(int argc, char *argv[])
{string ms,pref,prefms;int m,k;
k=1;//for(k=1;k<argc;k++)
{ms=argv[k];m=atoi(argv[k]);
pref="kernel"; prefms=pref+ms;
kern.open(prefms.c_str());
pref="R"; prefms=pref+ms;
R.open(prefms.c_str());
handlebase(m);}
} // fin main
