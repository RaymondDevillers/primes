#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;

main(int argc, char *argv[])
{string ms,pref,prefms,p,ss;int k=0,b;char s[5];
ifstream res;ofstream split; 
ms=argv[1];b=atoi(argv[1]);
pref="x"; prefms=pref+ms;
res.open(prefms.c_str());
while(res>>p){sprintf(s,"%d",k);
              ss="xx"+ms+'-'+s;
              split.open(ss.c_str(),ios::out);
              split<<p<<"\n";split.close();
              k++;}
} // fin main
