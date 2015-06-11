#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
using namespace std;

main(int argc, char *argv[])
{string ms,pref,prefms,ss,p; bool test;
 ifstream old;
 int i;
 vector <string> oldv;
 ms=argv[1]; pref="oldleft"; prefms=pref+ms;
 old.open(prefms.c_str());
 while(old>>p)
  {ss="";i=0;
   while(i<p.length())
    {if(p[i]!='$'){ss.push_back(p[i]);i++;}
       else{ while(p[++i]!='$')true;i++; }
    }oldv.push_back(ss);
  }
 while(cin>>p)
  {test=false;
   for(i=0;i<oldv.size();i++)if(oldv[i]==p){test=true;break;}
   if(!test)cout<<p<<'\n'; else cerr<<p<<'\n';
  }
} // fin main
