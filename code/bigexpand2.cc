#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
#include "big.h"   /* include MIRACL system */
using namespace std;

Miracl precision(20000,128);   /* bigs are 10000 centimal digits long */

char tr[128]; int w[128];

string s10(Big x)
{Big y=x; int r; string s="";
 while (y!=0){r=y%10;y=y/10;s=tr[r]+s;}
 return s;
}

ifstream result;int deploy,m;string p;
Big nbd ;

string strip0(string s)
  {int i;i=0;while(s[i]=='0')i++;return s.substr(i);}

void printstringM(string s,string sr,int n)
 {int i,j,ki,kj;char c;string ssr;
cerr<<s<<'+'<<sr<<": "<<n<<"\n";
  for(i=0;i<sr.length();i++)if(sr[i]=='{')break; 
         else s=s+sr[i];
  if(i<sr.length())sr=sr.substr(i+1,sr.length()-i);else sr="";
  if(sr.empty()){nbd=0; for(j=0;j<s.length();j++)
                            {c=s[j];nbd=nbd*m+w[c];}
                 if(prime(nbd))
                    {cout<<'"'<<strip0(s)<<'"'<<'='<<s10(nbd)<<",\n";
                     cout.flush();}return;
                }
  if(sr[1]=='}')
     {c=sr[0];for(i=1;i<sr.length();i++)if(sr[i]=='}')break;
      sr=sr.substr(i+1,sr.length()-i);
      for(ki=0;ki<=deploy;ki++)
         {if((ki%1000)==0)cerr<<'-';else cerr<<'.';
          printstringM(s,sr,deploy);
          s=s+c;
         }return;
     } else
     {for(i=1;i<sr.length();i++)if(sr[i]=='}')break;
      ssr=sr.substr(i+1,sr.length()-i);
      printstringM(s,ssr,deploy);
      if(n>0)
         for(i=0;sr[i]!='}';i++) printstringM(s+sr[i],'{'+sr,n-1);
     }
 }

main(int argc, char *argv[])
{string ms,pref,prefms;
deploy=atoi(argv[argc-1]);
ms=argv[1];m=atoi(argv[1]);
 for(char c='0';c<='9';c++){w[c]=0+c-'0';tr[0+c-'0']=c;}
 for(char c='A';c<='Z';c++){w[c]=10+c-'A';tr[10+c-'A']=c;}
 for(char c='a';c<='z';c++){w[c]=36+c-'a';tr[36+c-'a']=c;}
while(cin>>p)if(p[0]=='%')break; 
      else {cerr<<"\n"<<p<<"\n";printstringM("",p,deploy);}
cerr<<"\n===================================\n";
} // fin main
