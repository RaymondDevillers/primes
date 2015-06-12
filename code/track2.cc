 
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
            unsigned long int modmm1, modlmm1, gcd, gcdll, gcdf, gcdl, dist;
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
string tr,p;char c; ifstream kern,R;ofstream result,control;
void printelem(elem el)
 {int iti; 
  control<<'"';
  for (iti=0;iti<el.t.size();++iti)control<<tr[el.t[iti]];
  control<<'"'<<"\n";control.flush();}

bool cover(elem el1,elem el2)
 {int iti1,iti2;
  if(el1.t.size()<el2.t.size())
    {control<<"problème d'ordre:";cout<<"problème d'ordre";cout.flush();
     printelem(el1);printelem(el2);
    }
  if(el1.t.size()==el2.t.size())return(false);
  iti1=0;iti2=0;
  while(iti2<el2.t.size())
       {if(el1.t[iti1]==el2.t[iti2]){iti1++;iti2++;
             if((iti1==el1.t.size())&&(iti2<el2.t.size())){return(false);}}
        else{iti1++;if(iti1==el1.t.size()){return(false);}}}
  control<<"problème de dominance entre\n";cout<<"problème de dominance\n";
  printelem(el1);printelem(el2);result.flush();cout.flush();
  return(true);
 }

void printnode(node el)
 {list<short int>::iterator iti; 
  int i;
//  if(el.nexti.empty() && el.l.empty())return;
  cout<<"{";
  for (iti=el.nexti.begin();iti!=el.nexti.end();++iti)
      {cout<<tr[*iti];} cout<<"}[";cout.flush();
  for (iti=el.l.begin();iti!=el.l.end();++iti)
      {cout<<tr[*iti]<<",";cout.flush();}
  cout<<"]";cout<<el.gcd<<","<<el.gcdl<<","<<el.gcdf<<","<<el.gcdll
     <<","<<el.modlmm1<<","<<el.modmm1<<";"<<el.court<<el.loopnpb<<el.final<<",[";
  for(i=0;i<el.mp1.size();i++)cout<<el.mp1[i]<<",";cout<<"]";
  cout.flush();}

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

short int si,i,i1,j,ii;
unsigned long int m,g,jj,jjj,n,nn, ip,
             nn1p,nn1,nn2,nn2p,nn3,nn42,nn42p,nn43,nn4,nn5,nn6,nn7,nn7p,nn8,nn8p,nn9;
bool test;
long int cpustarttime; double cputime; 
elem el;
vector<elem> found;
int ite,ite1,ite2;
list<short int>::iterator iti1,iti2;
node auto1;vector<int>xtend; 
  
void printstring(node auto0,string s,int m)
 {list<short int>::iterator iti;
   if((auto0.court)&&ok(auto0.gcdf))
        {nn8p++;
      cerr<<"un prime court: "<<s<<" = "<<auto1.gcdf<<",\n";cerr.flush();
      result<<s<<"\n";result.flush();return;}
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
  if((nn%1)==0)
   {cout<<nn<<":"<<s<<"[";
    for (iti=auto0.nexti.begin();iti!=auto0.nexti.end();++iti)
        cout<<tr[*iti];
    cout<<".";
    for (iti=auto0.l.begin();iti!=auto0.l.end();++iti)
        cout<<tr[*iti];
    cout<<"]\n";}
  if((!auto0.l.empty())||(!auto0.l.empty()))
    {test=true;  
     for (iti=auto0.nexti.begin();iti!=auto0.nexti.end();++iti) 
         if(pgcd(m,*iti)==1)test=false;
     for (iti=auto0.l.begin();iti!=auto0.l.end();++iti) if(pgcd(m,*iti)==1)test=false;
            // test= tous les arcs ont un facteur avec la base
     if(test) // on peut supprimer les successeurs car ils ont tous un diviseur avec m
       {//control<<"\n(1)";printnode(auto0); 
        auto0.nexti.clear(); auto0.l.clear(); 
        auto0.gcdll=0;auto0.loopnpb=true;nn1++;}
    }
   iti=auto0.l.begin();
   while(iti!=auto0.l.end())
   if(pgcd(m,*iti)!=1) // *iti ne peut être un chiffre final
   {auto1=auto0;
    for (ite=0;ite<found.size();ite++)
      {if((*iti)==found[ite].t[auto1.ptr[ite]])auto1.ptr[ite]++;}
    test=false;
    for (iti1=auto1.nexti.begin();iti1!=auto1.nexti.end();++iti1)
    if(pgcd(m,*iti1)==1) // on teste si un chiffre final peut suivre
      {for (ite=0;ite<found.size();ite++)
       {if((*iti1)==found[ite].t[auto1.ptr[ite]])
           if(auto1.ptr[ite]==(found[ite].t.size()-1))break;}
       if(ite==found.size())test=true;
      }
    if(!test)for (iti1=auto1.l.begin();iti1!=auto1.l.end();++iti1)
    if(pgcd(m,*iti1)==1)
      {for (ite=0;ite<found.size();ite++)
       {if((*iti1)==found[ite].t[auto1.ptr[ite]])
           if(auto1.ptr[ite]==(found[ite].t.size()-1))break;}
       if(ite==found.size())test=true;
      }
    if(!test){nn1p++;iti=auto0.nexti.erase(iti);}else{iti++;}
   } //suppression des chiffres non-terminaux qui ne peuvent être suivis d'un terminal
   else{iti++;}
  test=true;j=0;  
  for (iti=auto0.nexti.begin();iti!=auto0.nexti.end();++iti) 
   {if(pgcd(m,*iti)==1)test=false;j=pgcd(j,*iti);} auto0.loopnpb=test;
  auto0.gcdll=j; // gcdll = gcd de la boucle locale
  j=0; for (iti=auto0.l.begin();iti!=auto0.l.end();++iti)j=pgcd(j,*iti);
       //j=gcd des arcs forward
  if((!auto0.l.empty())||(!auto0.l.empty()))
  {
  if (pgcd(pgcd(auto0.gcd,auto0.gcdll),j)!=1) // tous les digits ont un diviseur
    {//control<<"\n(2)";printnode(auto0); 
     auto0.nexti.clear();auto0.l.clear();
     auto0.gcdll=0;auto0.loopnpb=true;nn2++;}
  else if (pgcd(pgcd(pgcd(auto0.gcdl,auto0.gcdll),j),auto0.gcdf)!=1) 
           // sigma et loop ont un diviseur
    {//control<<"\n(2')";printnode(auto0); 
     auto0.nexti.clear();auto0.l.clear();
     auto0.gcdll=0;auto0.loopnpb=true;nn2p++;}
  else if
   (pgcd(m-1,pgcd(auto0.modlmm1,pgcd(auto0.modmm1,pgcd(auto0.gcdll,j))))!=1)
     {//control<<"\n(3)";printnode(auto0); 
       auto0.nexti.clear();auto0.l.clear();
       auto0.gcdll=0;auto0.loopnpb=true;nn3++;}
// si un arc forward est incompatible avec un ou plusieurs autres et si, en le conservant et en supprimant les arcs incompatibles, on contrevient aux règles 2, 2' ou 3, on peut supprimer cet arc forward pour la suite! 
  else{iti=auto0.l.begin();
       while(iti!=auto0.l.end())
       {i=*iti;j=i;
        for(iti1=auto0.l.begin();iti1!=auto0.l.end();iti1++)if(iti!=iti1)
        {i1=*iti1;test=false;
         for(ii=0;ii<found.size();ii++)
          if(found[ii].t.size()==(2+auto0.ptr[ii]))
          if(i==found[ii].t[auto0.ptr[ii]])
          if(i1==found[ii].t[auto0.ptr[ii]+1])break;
         if(ii<found.size()){
         for(ii=0;ii<found.size();ii++)
          if(found[ii].t.size()==(2+auto0.ptr[ii]))
          if(i1==found[ii].t[auto0.ptr[ii]])
          if(i==found[ii].t[auto0.ptr[ii]+1])break;
         if(ii<found.size())test=true;
                            }
         if(!test)j=pgcd(j,i1);
         } // j=pgcd des compatibles avec i
        if (pgcd(pgcd(auto0.gcd,auto0.gcdll),j)!=1) // tous les digits ont un diviseur
    {//control<<"\n(4+2)";printnode(auto0); 
     iti=auto0.l.erase(iti);nn42++;}
  else if (pgcd(pgcd(pgcd(auto0.gcdl,auto0.gcdll),j),auto0.gcdf)!=1) 
           // sigma et loop ont un diviseur
    {//control<<"\n(4+2')";printnode(auto0); 
     iti=auto0.l.erase(iti);nn42p++;}
  else if
   (pgcd(m-1,pgcd(auto0.modlmm1,pgcd(auto0.modmm1,pgcd(auto0.gcdll,j))))!=1)
     {//control<<"\n(4+3)";printnode(auto0); 
       iti=auto0.l.erase(iti);nn43++;}
  else iti++;
       }
      }
  }  
//
   if(auto0.nexti.size()>1)auto1.mp1.clear();
   else if(auto0.nexti.size()==1)
          {jjj=auto0.mp1.size();
           for(jj=0;jj<jjj;jj++)
        auto0.mp1.push_back((auto0.nexti.front()-auto0.mp1[jj]+m+1)%(m+1));}
  if((auto0.loopnpb)&&(pgcd(m,auto0.gcdf)>1))
        {auto0.final=false;nn4++;}
      else if((auto0.nexti.empty())&&(auto0.court)
              &&(!ok(auto0.gcdf)))
        {auto0.final=false;nn8++;}
      else if(1!=pgcd(m-1,pgcd(auto0.modlmm1,
                      pgcd(auto0.modmm1,auto0.gcdll))))
        {auto0.final=false;nn5++;}
      else if(pgcd(auto0.gcd,auto0.gcdll)!=1)
        {auto0.final=false;nn7++;}
      else if(pgcd(pgcd(auto0.gcdf,auto0.gcdl),auto0.gcdll)!=1)
        {auto0.final=false;nn7p++;}
      else if(!auto0.mp1.empty())
           {test=true;
            for(jj=0;jj<auto0.mp1.size();jj++)
               if(pgcd(m+1,auto0.mp1[jj])==1){test=false;break;}
            if(test){auto0.final=false;nn9++;}
           }
  if(auto0.final&&auto0.loopnpb){result<<s<<"\n";result.flush();}
  if(!auto0.nexti.empty())    
    {s=s+"{";
     for(iti=auto0.nexti.begin();iti!=auto0.nexti.end();++iti)
     s=s+tr[*iti];s=s+"}";
    }
  if(auto0.final&&(!auto0.loopnpb)){result<<s<<"\n";result.flush();}
if(p[ip]!='[')
  {if(p[ip]=='{'){while(p[ip]!='}')ip++;ip++;}c=p[ip];ip++;
   auto1=auto0;ite=0;if(c>='A')i=10+c-'A';else i=c-'0';
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
   if(auto1.court && ok(auto1.gcdf))
     {cout<<"un prime court: "<<(s+tr[i])<<" = "<<auto1.gcdf<<"\n";cout.flush();
      result<<"un prime court: "<<(s+tr[i])<<" = "<<auto1.gcdf<<"\n";result.flush();}
   printstring(auto1,s+tr[i],m);
  }
else for (iti=auto0.l.begin();iti!=auto0.l.end();++iti) 
  {auto1=auto0;ite=0;
   for (ite=0;ite<found.size();ite++)
      {if((*iti)==found[ite].t[auto1.ptr[ite]])auto1.ptr[ite]++;} 
   auto1.final=true;auto1.gcd=pgcd(pgcd(auto0.gcd,auto0.gcdll),*iti);
   auto1.modlmm1=pgcd(auto0.modlmm1,auto0.gcdll);
   auto1.modmm1=(auto0.modmm1+*iti)%(m-1);
   for(jj=0;jj<auto1.mp1.size();jj++)
              auto1.mp1[jj]=(*iti-auto1.mp1[jj]+m+1)%(m+1);
   if(!auto0.nexti.empty())
     {auto1.gcdl=pgcd(pgcd(auto1.gcdl,auto1.gcdf),auto0.gcdll);
      auto1.gcdf=*iti;auto1.court=false;}
   else{jj=(auto1.gcdf)*m+(*iti);
        if(((jj-(*iti))/m)!=auto1.gcdf)
    {auto1.gcdl=pgcd(auto1.gcdl,auto1.gcdf);
     auto1.gcdf=(*iti);auto1.court=false;}
        else auto1.gcdf=jj;}
   if(auto1.court && ok(auto1.gcdf))
     {cout<<"un prime court: "<<(s+tr[*iti])<<" = "<<auto1.gcdf<<"\n";cout.flush();
      result<<"un prime court: "<<(s+tr[*iti])<<" = "<<auto1.gcdf<<"\n";result.flush();}
   printstring(auto1,s+tr[*iti],m);
  }
}

void handlebase(unsigned int m)
 {string s;long int k,kkk;node auto0,auto1;short int i;int ii;
cpustarttime=clock();cout<<"traitement de la base "<<m<<"\n";
nn1p=0;nn1=0;nn2=0;nn2p=0;nn3=0;nn4=0;nn5=0;
nn6=0;nn7=0;nn7p=0;nn8=0;nn8p=0;nn9=0;
found.clear();
for (i=0;i<min(m,10);i++)tr.push_back('0'+i);
for (i=10;i<m;i++)tr.push_back('A'+i-10);
while(kern>>p)
{el.t.clear();
 for(i=1;p[i]!='"';i++){if(p[i]<'A'){el.t.push_back(p[i]-'0');}
                        else{el.t.push_back(10+p[i]-'A');}}
 found.push_back(el);
}

R>>p;ip=0;cout<<p<<"\n";
for (ite1=0;ite1!=found.size();++ite1)
    for (ite2=0;ite2!=ite1;++ite2)cover(found[ite1],found[ite2]);

nn=0;
// initialisation
result<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
c=p[ip];ip++;if(c>='A')i=10+c-'A';else i=c-'0';
{auto0.nexti.clear(); auto0.l.clear(); auto0.ptr.clear();
 for(j=0;j<m;j++)if(!ok(j))auto0.l.push_back(j);
  for (ite2=0;ite2!=found.size();++ite2)
   {if(i==found[ite2].t[0])ii=1; else ii=0;auto0.ptr.push_back(ii);}
 auto0.modmm1=i%(m-1); auto0.modlmm1=0;
 auto0.mp1.clear(); auto0.mp1.push_back(i);
 auto0.final=false;auto0.loopnpb=false;auto0.court=true;
 auto0.gcd=i; auto0.gcdl=0;auto0.gcdll=0;auto0.gcdf=i;s=tr[i];
//construction des familles à explorer à  partir du premier chiffre
  printstring(auto0,s,m);
}
cputime = clock()-cpustarttime; cputime=cputime/1000000;
result<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
result<<"\nA la fin, on a exploré "
<<nn<<" familles de nombres, et on a pu appliquer "
<<nn1<<" règles 1, "<<nn1p<<" règles 1', "
<<nn2<<" règles 2, "<<nn2p<<" règles 2', "
<<nn3<<" règles 3, "
<<nn42<<" règles 42, "<<nn42p<<" règles 42', "<<nn43<<" règles 43, "
<<nn4<<" règles 4, "
<<nn5<<" règles 5, "<<nn6<<" règles 6, "<<nn7<<" règles 7, "
<<nn7p<<" règles 7', "<<nn8<<" règles 8, "<<nn8p<<" règles 8' et "
<<nn9<<" règles 9, en "
<<cputime<<" secondes\n"; result.flush();
} // fin du traitement de la base

main(int argc, char *argv[])
{string ms,pref,prefms;int m,k;
k=1;//for(k=1;k<argc;k++)
{ms=argv[k];m=atoi(argv[k]);
pref="control"; prefms=pref+ms;
control.open(prefms.c_str(),ios::out);
pref="res"; prefms=pref+ms;
result.open(prefms.c_str(),ios::out);
pref="kernel"; prefms=pref+ms;
kern.open(prefms.c_str());
pref="R"; prefms=pref+ms;
R.open(prefms.c_str());
handlebase(m);
control.close();result.close();kern.close();}
} // fin main
