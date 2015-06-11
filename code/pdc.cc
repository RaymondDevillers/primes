 
#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "big.h"   /* include MIRACL system */

using namespace std;

Miracl precision(5000,100);   /* bigs are 5000 centimal digits long */

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

short int si,i,il,ir,j,ii,b,ilb,ilh,irb,irh; 
main(int argc, char *argv[])
{string ms,pref,prefms;
ms=argv[1];b=atoi(argv[1]);
ilb=1;ilh=b;irb=1;irh=b;
cout<<"pour la base "<<b<<", les premiers chiffres sont: ";
for(il=ilb;il<ilh;il++)if(!ok(il))cout<<il<<", ";
cout<<"\net les derniers  chiffres sont: ";
for(ir=irb;ir<irh;ir++)if(!ok(ir))if(pgcd(ir,b)==1)cout<<ir<<", ";cout<<"\n";

} // fin main
