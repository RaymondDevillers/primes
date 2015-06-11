
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
#include <stdlib.h>
using namespace std;

ifstream result;int deploy;string p;

string itos(int i)	// convert int to string
 {stringstream s;s << i;return s.str();}

string cvrt(char c)
  {if((c>='0')&&(c<='9')) return itos(c-'0'); else return itos(10+c-'A');}

void printstringM(string sM,string s,string sr)
 {int i,ki;char c;
  for(i=0;i<sr.length();i++)if(sr[i]=='{')break; 
         else{sM="("+sM+")*M+"+cvrt(sr[i]);s=s+sr[i];}
  if(i<sr.length())sr=sr.substr(i+1,sr.length()-i);else sr="";
  if(sr.empty()){cout<<"x:="<<sM<<":\n";
         cout<<"isprime(x),ifactor(x),"<<'"'<<p<<"->"<<s<<"="<<'"'<<",x;\n";
                cout.flush();return;}
  c=sr[0];for(i=1;i<sr.length();i++)if(sr[i]=='}')break;
  sr=sr.substr(i+1,sr.length()-i);
  for(ki=0;ki<=deploy;ki++)
     {printstringM(sM,s,sr);
      s=s+c;
      sM="("+sM+")*M+"+cvrt(c);
     }
 }

main(int argc, char *argv[])
{string ms,pref,prefms;int m,k,l,n;char c;
for(k=1;k<argc-1;k++)
{ms=argv[k];m=atoi(argv[k]);deploy=atoi(argv[argc-1]);
pref="res"; prefms=pref+ms;
result.open(prefms.c_str());
pref="resM"; prefms=pref+ms;
cout<<"M:="<<m<<":\n";
while(result>>p)if(p[0]=='%')break;
while(result>>p)if(p[0]=='%')break; else 
{n=0;for(l=p.length()-1;l>=0;l--)if(p[l]=='{'){n++;c=p[l+1];while(c==p[l-1]){p.erase(l-1,1);l--;}}
if(n>0){printstringM("0","",p);}
}
result.close();}
} // fin main
