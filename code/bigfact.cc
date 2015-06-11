#include <list>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <sstream>

#include <cmath>
#include "big.h"   /* include MIRACL system */

using namespace std;

Miracl precision(5000,100);   /* bigs are 5000 decimal digits long */

int deploy,b; string ms,p,s; Big NN,MM;
char tr[128]; int w[128];

string s10(Big x)
{Big y=x; int r; string s="";
 while (y!=0){r=y%10;y=y/10;s=tr[r]+s;}
 return s;
}
string sb(Big x)
{Big y=x; int r; string s="";
 while (y!=0){r=y%b;y=y/b;s=tr[r]+s;}
 return s;
}

void printstringM(string s,string sr)
 {int i,j,ki,kj;char c; unsigned long int k;
  for(i=0;i<sr.length();i++)if(sr[i]=='{')break; 
         else s=s+sr[i];
  if(i<sr.length())sr=sr.substr(i+1,sr.length()-i);else sr="";
  if(sr.empty())
   {NN=0; for(j=0;j<s.length();j++)
                  {c=s[j];kj=w[c];NN=NN*b+kj;}
    cout<<"         "<<'"'<<p<<'"'<<"=>"<<'"'<<s<<'"'<<"= "<<s10(NN)<<"\n";MM=NN;
    if(NN==0)cout<<"is 0\n"; else 
    if(NN==1)cout<<"is 1\n"; else 
    if(prime(NN))cout<<"is prime\n"; else 
    {k=2;while(!prime(NN)){while((NN%k)!=0){if(k>100000)break; else k++;}
       if(k<100000){cout<<sb(k)<<'('<<sb(MM/k)<<')'<<'.';NN=NN/k;cout.flush();}else break;}
     if(k<100000)cout<<sb(NN)<<'('<<sb(MM/NN)<<')'<<"\n";else cout<<"...\n";cout.flush();}
    return;}
  c=sr[0];for(i=1;i<sr.length();i++)if(sr[i]=='}')break;
  sr=sr.substr(i+1,sr.length()-i);
  for(ki=0;ki<=deploy;ki++)
     {printstringM(s,sr);
      s=s+c;
     }
 }

main(int argc, char *argv[])
{ int k; char c;
deploy=atoi(argv[argc-1]);
ms=argv[1];b=atoi(argv[1]);
 for(char c='0';c<='9';c++){w[c]=0+c-'0';tr[0+c-'0']=c;}
 for(char c='A';c<='Z';c++){w[c]=10+c-'A';tr[10+c-'A']=c;}
 for(char c='a';c<='z';c++){w[c]=36+c-'a';tr[36+c-'a']=c;}
while(cin>>p)if(p[0]=='%')break; 
else {s="";for(k=p.length()-1;k>=0;k--)if(p[k]=='}')if(p[k-2]!='{'){cerr<<p;break;}
                                                    else {c=p[k-1];s='}'+s;s=c+s;s='{'+s;k=k-2;while(c==p[k-1])k--;}
                                       else s=p[k]+s;p=s;
      cout<<"===============================================\n";cerr<<s<<"\n";printstringM("",s);}
} // fin main
