#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;

main(int argc, char *argv[])
{string ms,pref,prefms,p,ss;int k=0,n,i;bool pasfin;char s[5];
ifstream res;ofstream split; 
ms=argv[1];n=atoi(argv[2]);
pref="r"; prefms=pref+ms;
res.open(ms.c_str());
while(true){sprintf(s,"%d",k);k++;i=0;
              ss=prefms+'-'+s;
              split.open(ss.c_str(),ios::out);
              while(i<n){pasfin=(res>>p);if(pasfin){split<<p<<"\n";i++;}else break;}
              if(pasfin) split.close();else break;}
} // fin main
