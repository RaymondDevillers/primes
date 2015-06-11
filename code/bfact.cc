
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
#include "big.h"   /* include MIRACL system */
using namespace std;

Miracl precision(20000,100);   /* bigs are 10000 centimal digits long */

string s10(Big x)
{Big y=x; Big br; int r; string s=""; char c;
 while (y!=0){br=y%10;y=y/10;
 if(br==0)r=0;if(br==1)r=1;if(br==2)r=2;if(br==3)r=3;if(br==4)r=4;if(br==5)r=5;
 if(br==6)r=6;if(br==7)r=7;if(br==8)r=8;if(br==9)r=9;c='0'+r;s=c+s;}return s;
}
ifstream result;int deploy,b;string p;
char tr[128]; int w[128],k;
Big nbd,MM ;
string itos(int i)	// convert int to string
 {stringstream s;s << i;return s.str();}

string cvrt(char c)
  {if((c>='0')&&(c<='9')) return itos(c-'0'); else return itos(10+c-'A');}
string sb(Big x)
{Big y=x; Big br; int r; string s=""; char c;
 while (y!=0){br=y%b;y=y/b;
 for(r=0;r<36;r++)if(br==r)break;
 if(r<10)c='0'+r; else c='A'+r-10; s=c+s;}return s;
}
void printstringM(string s,string sr,int d)
 {int i,j,ki,kj,dd;string ll,ss;char c;
  for(i=0;i<sr.length();i++)if((sr[i]=='{')||(sr[i]=='<')){if((sr[i+1]=='}')||(sr[i+1]=='>'))i=i+2;else break;}  else s=s+sr[i];
  if(i<sr.length())sr=sr.substr(i,sr.length()-i+1);else sr="";
  if(sr.empty()){nbd=0; for(j=0;j<s.length();j++)nbd=nbd*b+w[s[j]];
    cout<<"         "<<'"'<<p<<'"'<<"=>"<<'"'<<s<<'"'<<"= "<<s10(nbd)<<"\n";MM=nbd;
    if(nbd==0)cout<<"is 0\n"; else 
    if(nbd==1)cout<<"is 1\n"; else 
    if(prime(nbd))cout<<"is prime\n"; else 
    {k=2;while(!prime(nbd)){while((nbd%k)!=0)if(k>100000)break; else k++;
       if(k<100000){cout<<sb(k)<<'('<<sb(MM/k)<<')'<<'.';nbd=nbd/k;cout.flush();}
       else break;         }
     if(k<100000)cout<<sb(nbd)<<'('<<sb(MM/nbd)<<')'<<"\n";else cout<<"...\n";cout.flush();
    }
    return;
                }
  ll="";for(i=1;i<sr.length();i++)if((sr[i]=='}')||(sr[i]=='>'))break;else ll=ll+sr[i];
  ss=sr.substr(i+1,sr.length()-i);if(d==0)dd=0;else dd=(d-1)/ll.length();printstringM(s,ss,dd);
  if(d>0){for(ki=0;ki<ll.length();ki++){cerr<<'.';printstringM(s+ll[ki],sr,dd);}}
 }

main(int argc, char *argv[])
{string ms,pref,prefms;
deploy=atoi(argv[2]);
ms=argv[1];b=atoi(argv[1]);
 for(char c='0';c<='9';c++){w[c]=0+c-'0';tr[0+c-'0']=c;}
 for(char c='A';c<='Z';c++){w[c]=10+c-'A';tr[10+c-'A']=c;}
 for(char c='a';c<='z';c++){w[c]=36+c-'a';tr[36+c-'a']=c;}
while(cin>>p)if(p[0]=='%')break; 
      else {cerr<<"\n"<<p;printstringM("",p,deploy);cout<<"\n===================================\n";}
cerr<<"\n===================================\n";
} // fin main