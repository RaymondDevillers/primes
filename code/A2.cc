
#include <list>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>

#define basemin 2
#define basemax 64
#define detail 25
#define wide 25000

using namespace std;

char tr[128]; int w[128];
struct elem{unsigned long int n; 
            list<short int> t;
            list <list<short int>::iterator> ptr;
            list<short int> next;
           };
struct node{list <short int> nexti; 
            list <short int> l; list <list<node>::iterator> nextn;
            list <list<short int>::iterator> ptr;
            unsigned long int nblink, id;
            long int modmm1, modlmm1, gcd, gcdl, gcdf, dist;
            bool infty,final;
           };
ofstream kern,P;

void printelem(elem el)
 {list<short int>::iterator iti; short int si;
  list <list<short int>::iterator>::iterator ititi;
  P<<'"';kern<<'"';
  for (iti=el.t.begin();iti!=el.t.end();++iti)
      {si=*iti ; P<<tr[si];kern<<tr[si];}
  P<<'"'<<"="<<el.n;kern<<'"'<<"="<<el.n;
  P<<",\n";kern<<",\n";P.flush();kern.flush();}

void printelemf(elem el)
 {list<short int>::iterator iti; short int si;
  list <list<short int>::iterator>::iterator ititi;
  P<<'"';
  for (iti=el.t.begin();iti!=el.t.end();++iti)
      {si=*iti ; P<<tr[si];}
  P<<'"'<<"="<<el.n<<" : ";
  for (ititi=el.ptr.begin();ititi!=el.ptr.end();++ititi)
       {P<<tr[*(*ititi)]<<",";} P<<"->";
  for (iti=el.next.begin();iti!=el.next.end();++iti)
      {si=*iti ; P<<tr[si];}
  P<<",\n";P.flush();}

unsigned int pgcd(unsigned int i, unsigned int j)
 {unsigned int ii,jj,kk;if(i==0)return j;
  if(j>i){ii=j;jj=i;} else {ii=i;jj=j;}
 while(jj!=0){kk=ii%jj;ii=jj;jj=kk;}
  return ii;}
unsigned int min(unsigned int i, unsigned int j)
 {if(i<=j)return i;else return j;}
unsigned int max(unsigned int i, unsigned int j)
 {if(i<=j)return j;else return i;}
bool ok(long int n) // is prime?
 {unsigned int kk;
 //   if (n<2) return false;
 for (kk=2;kk*kk<=n;kk++)
     {if(n % kk==0)return  false;}
 return true;
 }

short int si,f,i,j,iinit;
unsigned int m,g,gg,t1,ll,kk;
unsigned long int ni,n,nmax,nn,szm,nn0,fact;
bool test,modif;
int cpustarttime; double cputime;int cpustarttime1; double cputime1;int cpustarttime2; double cputime2;
unsigned int n0,n1,n2,n3,n4,n5;
elem el,el1,el2,elmax;
list<elem> todo, found;
node auto0,auto1,auto2;
list<node>autom; list<list<node>::iterator>nodetodo;
list<elem>::iterator ite,ite1,ite2;
list<node>::iterator itn,itn0,itn1,itn2;
list<node>::reverse_iterator ritn,ritn0,ritn1,ritn2;
list<short int>::iterator iti,iti1,iti2;
list<list<short int>::iterator>::iterator ite3,ite4;
list<list<node>::iterator>::iterator itepn,itepn1;
list<list<node>::iterator>::iterator ittd;

void handlebase(unsigned int m)
 {
cpustarttime=clock();
nmax=0;nn=m-1;n0=0;
todo.clear(); found.clear();

P<<"\nbase="<<m<<":\n";
el.n=1; el.t.clear();el.t.push_back(1);el.ptr.clear();el.next.clear();
todo.push_back(el);fact=1;
for (i=2;i<m;i++) 
{el.n=i; el.t.clear();el.t.push_back(i); el.ptr.clear();el.next.clear();
if (ok(i)) {found.push_back(el);printelem(el);fact=fact*i;}
else{todo.push_back(el);}}
for (ite1=todo.begin();ite1!=todo.end();++ite1)
 {(*ite1).next.push_back(0);(*ite1).next.push_back(1);
  for (i=2;i<m;i++){if(!ok(i)){(*ite1).next.push_back(i);}}
  for (ite2=found.begin();ite2!=found.end();++ite2)
   {(*ite1).ptr.push_back((*ite2).t.begin());}
 }
// les structures sont initialisées, avec les chiffres de la base
szm=todo.size();
while (!todo.empty()) // tant qu'il y a des todo
  {el=todo.front();ni=el.n;
if(((((ni+1)*m)/m)!=(ni+1))// (ni>over)
   ||(todo.size()>wide)){elmax=el;break;} // si trop long ou trop large: on arrête!
else{todo.pop_front();
ite1=found.end();ite3=el.ptr.end();j=found.size()-el.ptr.size();
for (i=1;i<=j;i++) // s'il y a de nouveaux founds, on ajuste les structures
 {ite1--; iti1=(*ite1).t.begin();iti2=el.t.begin();
  while(iti2!=el.t.end()){if((*iti1)==(*iti2)){iti1++;iti2++;}else{iti2++;}}
  ite3=el.ptr.insert(ite3,iti1);
 }
for (iti=el.next.begin();iti!=el.next.end();iti++) // le préfixe considéré est allongé
   {el1=el;i=*iti;n=ni*m+i;el1.n=n;el1.t.push_back(i);nmax=n;ite1=found.begin(); nn++; 
for (ite3=el1.ptr.begin();ite3!=el1.ptr.end();ite3++)
 {if(i==(*(*ite3))){(*ite3)++;
if((*ite3)==(*ite1).t.end())break;}
ite1++;
 }
if(ite3==el1.ptr.end())
{ // il n'est pas couvert
 if (ok(n)) 
 {found.push_back(el1);printelem(el1);} // il est found
    else // il est todo, mais on ne le considère que si les allongements possibles ne certifient pas qu'ils seront composés
 {el1.next.clear();test=true; g=el1.n; // g est le gcd des allongements possibles
  for(iti1=el.next.begin();iti1!=el.next.end();iti1++) // un allongement est envisagé
   {j=*iti1;ite1=found.begin();
for (ite4=el1.ptr.begin();ite4!=el1.ptr.end();ite4++)
 {if(j==(*(*ite4))){iti2=*ite4;if((++iti2)==(*ite1).t.end()){break;}}
  ite1++;
 }
if(ite4==el1.ptr.end()){el1.next.push_back(j);
       g=pgcd(g,j);test=test && (pgcd(j,m)!=1);}// il n'est pas couvert par la base
   }
if((!test) and (g==1)) {todo.push_back(el1);} else{n0++;}
//cputime1 = clock()-cpustarttime1; cputime1=cputime1/1000000;if(cputime1>0.001)
 }
}
if(todo.size()>szm)szm=todo.size();
  } // fin de la boucle d'allongement
  }} // fin de la boucle sur todo

cputime = clock()-cpustarttime; cputime=cputime/1000000;cpustarttime1=clock();
P<<"\nla taille de la base de nombres premiers est de : "<<found.size();
P<<"\nil a fallu "<<cputime<<" secondes pour les obtenir, considérer "<<nn<<" candidats, dont "<<szm<<" en même temps, et appliquer "<<n0<<" fois la règle d'élagage.";
P<<"\nle plus grand entier traité est  : "<<nmax;
if(!todo.empty()){
P<<"\n_____________________________________________________";
P<<"\nil restait encore "<<todo.size()<<" préfixes à  traiter\n"; 
P.flush();
if(false)
{if(todo.size()<=2*detail){for (ite=todo.begin();ite!=todo.end();++ite)
 {el=*ite;printelemf(el);}}
 else {i=0; for (ite=todo.begin();i++<detail;++ite)
 {el=*ite;printelemf(el);}P<<".....\n";ite=todo.end();
      i=0;for (ite--;i++<detail;ite--)
 {el=*ite;printelemf(el);}}
P<<"\n===============================================\n";P.flush();
 }}
}
int main(int argc, char *argv[])
{string ms,pref,prefms;int m,k;
for(k=1;k<argc;k++)
{ms=argv[k];m=atoi(argv[k]);
pref="P"; prefms=pref+ms;
P.open(prefms.c_str(),ios::out);
pref="kernel"; prefms=pref+ms;
kern.open(prefms.c_str(),ios::out);
 for(char c='0';c<='9';c++){w[c]=0+c-'0';tr[0+c-'0']=c;}
 for(char c='A';c<='Z';c++){w[c]=10+c-'A';tr[10+c-'A']=c;}
 for(char c='a';c<='z';c++){w[c]=36+c-'a';tr[36+c-'a']=c;}
handlebase(m);
P.close();kern.close();}
} // fin main
