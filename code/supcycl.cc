#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
using namespace std;

main(int argc, char *argv[])
{string ss,p,pp;
 ifstream all,part;
 all.open(argv[1]);
 part.open(argv[2]);
// int i;
// vector <string> oldv;
// ms=argv[1]; pref="oldleft"; prefms=pref+ms;
// old.open(prefms.c_str());
 part>>p;all>>pp;
 while(true)
{if(pp==p){if(!(all>>pp)){while(part>>p)cerr<<p<<'\n';break;}if(!(part>>p)){cout<<pp<<'\n';while(all>>pp)cout<<pp<<'\n';break;};continue;}
 cout<<pp<<'\n';if(!(all>>pp)){cerr<<p<<'\n';while(part>>p)cerr<<p<<'\n';break;}
}
} // fin main
