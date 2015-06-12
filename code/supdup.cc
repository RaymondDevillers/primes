#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

main(int argc, char *argv[])
{string oldl="";string newl; bool dup;
 while(cin>>newl)
  {if(oldl.length()!=newl.length()) dup=false; else
     {dup=true;
      for(int i=0;i<oldl.length();i++)if(oldl[i]!=newl[i]){dup=false;break;}
     }
   if(dup){cerr<<newl<<"\n";}else{cout<<newl<<"\n";oldl=newl;}
  }
} // fin main

