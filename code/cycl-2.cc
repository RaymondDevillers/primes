#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
#include <stdlib.h>

#include "big.h"   /* include MIRACL system */

#define cyclemax 12
#define bound 1000000

using namespace std;

Miracl precision(20000,128);   /* bigs are 20000 decimal digits long */

int b,i,j,ki,kj,r,rr,k,kk,i1,h,pp; string p;
vector <int> prm; 
int fact[cyclemax][cyclemax];
Big NN;

char tr[128]; int w[128];

main(int argc, char *argv[])
{string ms,pref,prefms,p;
ms=argv[1];b=atoi(argv[1]);
prm.push_back(2);k=3;while(k<bound){NN=k;if(prime(NN))prm.push_back(k);k=k+2;}
 for(char c='0';c<='9';c++){w[c]=0+c-'0';tr[0+c-'0']=c;}
 for(char c='A';c<='Z';c++){w[c]=10+c-'A';tr[10+c-'A']=c;}
 for(char c='a';c<='z';c++){w[c]=36+c-'a';tr[36+c-'a']=c;}
while(cin>>p)
{cerr<<"\n"<<p;
 for(i=1;i<=cyclemax;i++)
  {for (j=1;j<=cyclemax;j++)
    {for(ki=0;ki<i;ki++)for(kj=0;kj<j;kj++)fact[ki][kj]=0;
     for(ki=0;ki<i;ki++)
      {for(kj=0;kj<j;kj++)
        {for(k=0;k<prm.size();k++)
          {kk=prm[k];r=0;
           for(i1=0;p[i1]!='{';i1++)r=(r*b+w[p[i1]])%kk;pp=w[p[i1+1]];
           for(h=0;h<ki;h++)r=(r*b+pp)%kk;rr=r;
           for(h=1;h<=i;h++)rr=(rr*b+pp)%kk;if(rr!=r)continue;
           for(i1=i1+3;p[i1]!='{';i1++)r=(r*b+w[p[i1]])%kk;pp=w[p[i1+1]];
           for(h=0;h<kj;h++)r=(r*b+pp)%kk;rr=r;
           for(h=1;h<=j;h++)rr=(rr*b+pp)%kk;if(rr!=r)continue;
           for(i1=i1+3;i1<p.length();i1++)r=(r*b+w[p[i1]])%kk;if(r!=0)continue;
           fact[ki][kj]=kk;break;
          }
         if(k==prm.size())break;
        }
       if(k==prm.size())break;
      }
     if(k==prm.size())continue;
     cerr<<"\ncycle double:\n";for(ki=0;ki<i;ki++){for(kj=0;kj<j;kj++)cerr<<fact[ki][kj]<<',';cerr<<'\n';}break;
    }
   if(k<prm.size())break;
  }
 if(k==prm.size())cout<<p<<'\n';
 cerr<<"\n===================================\n";
}
} // fin main

