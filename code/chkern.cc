
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
using namespace std;

ifstream kern,Q; ofstream resultchk,resultchkM,controlchk;
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
list<string>::iterator itM,it10,fitM,fit10;
for(k=1;k<argc;k++)
{ms=argv[k];m=atoi(argv[k]);
pref="controlchk"; prefms=pref+ms;
controlchk.open(prefms.c_str(),ios::out);
pref="reschk"; prefms=pref+ms;
resultchk.open(prefms.c_str(),ios::out);
pref="kernel"; prefms=pref+ms;
kern.open(prefms.c_str());
pref="Q"; prefms=pref+ms;
Q.open(prefms.c_str());
pref="resultchkM"; prefms=pref+ms;
resultchkM.open(prefms.c_str(),ios::out);
resultchkM<<"M:="<<m<<":A:=10:C:=12:E:=14:F:=15:\n";
nn=0;
while(kern>>p)
{nn++;l=p.length();
 if(p[0]!='"'){controlchk<<"problème de quote à la ligne"<<nn; }
 if(p[l-1]!=','){controlchk<<"problème de , à la ligne"<<nn; }
 for(i=1;i<l;i++)if(p[i]=='"')
                   {mm=p.substr(1,i-1);m10=p.substr(i+2,l-i-3);break;}
 if((nn>1)&&(order(found10.back(),m10)!=2))
   {controlchk<<"problème d'ordre à la ligne"<<nn;
    itM=foundM.begin();it10=found10.begin();
    while(order(*it10,m10)==2){it10++;itM++;}
    if(order(*it10,m10)==1){foundM.insert(itM,mm);found10.insert(it10,m10);}
   }
  else{foundM.push_back(mm);found10.push_back(m10);}
}
nn==0;controlchk<<"taille des listes 1: "<<foundM.size()<<","<<found10.size()<<"\n";
fin=(Q>>p);
while(fin)
{nn++;
 while(p[0]!='t'){controlchk<<"problème de true à la ligne "<<nn<<" de Q\n";
                  fin=(Q>>p);if(!fin)break; }if(!fin)break;
 if(!(Q>>p))break;l=p.length();
 if(p[0]!='"'){controlchk<<"problème de quote à la ligne "<<nn<<" de Q\n"; }
   else{for(i=1;i<l;i++){if(p[i]=='>')break;}
        for(j=i+1;j<l;j++)
           {if(p[j]=='='){mm=p.substr(i+1,j-i-1);
                          fin=(Q>>p);m10=p;break;} }
              
       }
 if((m10[0]=='t')||(m10[0]=='"'))
                {controlchk<<"problème de m10 à la ligne "<<nn<<" de Q\n";}
 else {fin=(Q>>p);controlchk<<"???????"<<m10<<"\n";
   if(order(found10.back(),m10)!=2)
   {itM=foundM.begin();it10=found10.begin();
    while(order(*it10,m10)==2){it10++;itM++;}
    controlchk<<"inserer? "<<*it10<<"_"<<m10<<":"<<order(*it10,m10)<<"\n";
    if(order(*it10,m10)==1){foundM.insert(itM,mm);found10.insert(it10,m10);
                            cout<<*it10<<"<"<<m10<<"\n";}
    else controlchk<<"======="<<*it10<<"_"<<m10<<"\n";
   }
   else{foundM.push_back(mm);found10.push_back(m10); 
       controlchk<<'"'<<mm<<'"'<<'='<<m10<<"\n";}
      }
}
controlchk<<"taille des listes 2: "<<foundM.size()<<","<<found10.size()<<"\n";
it10=found10.begin();itM=foundM.begin();
while(itM!=foundM.end())
 {fitM=itM;fit10=it10;fitM++;fit10++;
  while(fitM!=foundM.end())
       {if(cover(*itM,*fitM))
          {controlchk<<*itM<<" domine "<<*fitM<<"\n";controlchk.flush();
           fitM=foundM.erase(fitM);fit10=found10.erase(fit10);}
        else{fitM++;fit10++;}
       }
  itM++;it10++;
 }
itM=foundM.begin();it10=found10.begin();
controlchk<<"taille des listes: "<<foundM.size()<<","<<found10.size()<<"\n";
it10=found10.begin();itM=foundM.begin();
while(itM!=foundM.end())
 {resultchk<<'"'<<*itM<<'"'<<'='<<*it10<<",\n";
  mM="0";for(i=0;i<(*itM).length();i++){mM="("+mM+")*M+"+cvrt((*itM)[i]);} md=*it10; 
  resultchkM<<"[testeq("<<mM<<","<<md<<"),isprime("<<mM<<"),"<<mM<<","<<md<<"];\n";
  itM++;it10++;
 }
//for(itM=foundM.begin();itM!=foundM.end();itM++)controlchk<<*itM<<",";

controlchk.close();resultchk.close();kern.close();resultchkM.close();
}} // fin main

