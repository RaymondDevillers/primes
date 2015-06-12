#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <time.h>
#define wide 25000

using namespace std;
unsigned int m;
struct elem{unsigned long int n; 
            list<short int> t;
            list <list<short int>::iterator> ptr;
            list<short int> next;
           };
string tr; 
ofstream kern,P;

void printelem(elem el)
 {list<short int>::iterator iti; short int si;
  list <list<short int>::iterator>::iterator ititi;
  kern<<'"';
  for (iti=el.t.begin();iti!=el.t.end();++iti)
      {si=*iti ; if(m<=36){kern<<tr[si];}
                 else{kern<<si<<",";}
      }
  kern<<'"'<<"="<<el.n;
  kern<<",\n";kern.flush();}

unsigned int min(unsigned int i, unsigned int j)
 {if(i<=j)return i;else return j;}

bool ok(long int n) // is composite?
 {unsigned int kk;
 if (n<4) return false;
 for (kk=2;kk*kk<=n;kk++)
     {if(n % kk==0)return  true;}
 return false;
 }

short int si,f,i,j,iinit;
unsigned int g,gg,t1,ll,kk;
unsigned long int ni,n,nmax,nn,szm,nn0;
int cpustart; double cptime;
elem el,el1;
list<elem> todo, found;
list<elem>::iterator ite,ite1,ite2;
list<short int>::iterator iti,iti1,iti2;
list<list<short int>::iterator>::iterator ite3,ite4;

void handlebase(unsigned int m)
 {
cpustart=clock();
nmax=0;nn=m-1;
todo.clear(); found.clear(); tr="";
for (i=0;i<min(m,10);i++)tr.push_back('0'+i);
for (i=10;i<m;i++)tr.push_back('A'+i-10);

P<<"\nbase="<<m<<":\n";
kern<<"\nbase="<<m<<":\n";
for (i=1;i<m;i++) 
{el.n=i; el.t.clear();el.t.push_back(i); el.ptr.clear();el.next.clear();
if (ok(i)) {found.push_back(el);printelem(el);}
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
   ||(todo.size()>wide))break; // si trop long ou trop large: on arr\^ete!
else{todo.pop_front();
ite1=found.end();ite3=el.ptr.end();j=found.size()-el.ptr.size();
for (i=1;i<=j;i++) // s'il y a de nouveaux founds, on ajuste les structures
 {ite1--; iti1=(*ite1).t.begin();iti2=el.t.begin();
  while(iti2!=el.t.end()){if((*iti1)==(*iti2)){iti1++;iti2++;}else{iti2++;}}
  ite3=el.ptr.insert(ite3,iti1);
 }
for (iti=el.next.begin();iti!=el.next.end();iti++) // le préfixe considéré est allongé
   {el1=el;i=*iti;n=ni*m+i;el1.n=n;el1.t.push_back(i);nmax=n;
    ite1=found.begin(); nn++; 
for (ite3=el1.ptr.begin();ite3!=el1.ptr.end();ite3++)
 {if(i==(*(*ite3))){(*ite3)++;
if((*ite3)==(*ite1).t.end())break;}
ite1++;
 }
if(ite3==el1.ptr.end())
{ // il n'est pas couvert
 if (ok(n)) 
         {found.push_back(el1);printelem(el1);} // il est found
    else todo.push_back(el1); 
}
if(todo.size()>szm)szm=todo.size();
  } // fin de la boucle d'allongement
  }} // fin de la boucle sur todo
//
cptime = (clock()-cpustart)/1000000.0;
P<<"\nla taille de la base de composites est de : "<<found.size();
P<<"\nil a fallu "<<cptime<<" secondes pour les obtenir, considerer "<<nn<<" candidats, dont "<<szm<<" en meme temps.";
P<<"\nle plus grand entier traite est  : "<<nmax;
if(!todo.empty()){
P<<"\n_____________________________________________________";
P<<"\nil restait encore "<<todo.size()<<" prefixes à  traiter\n";
P<<"\n===============================================\n";
 }
P<<"\n\\put("<<3*m<<",0){\\line(0,1){"<<found.size()/6.0<<"}} %"<<m<<"\n";
P<<"\n\n\n";P.flush();
}
int main(int argc, char *argv[])
{
kern.open("l-composites",ios::out);
P.open("o-composites",ios::out);
for(m=2;m<=100;m++)
handlebase(m);
P.close();kern.close();
} // fin main
