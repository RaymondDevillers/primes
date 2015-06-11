//a partir d'un fichier de familles infinies, creer des familles raffinées, en fonction du kernel actuel
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
#include <stdlib.h>
#include "big.h"   /* include MIRACL system */
using namespace std;

Miracl precision(20000,128);   /* bigs are 20000 centimal digits long */

vector<string> found; vector<int> point; vector <int> fact; 
char tr[128]; int w[128];
int b,m;

string s10(Big x)
{Big y=x; int r; string s="";
 while (y!=0){r=y%10;y=y/10;s=tr[r]+s;}
 return s;
}

bool ok(long int n) // is prime?
 {unsigned int kk;
 if (n<2) return false;
 for (kk=2;kk*kk<=n;kk++)
     {if(n % kk==0)return  false;}
 return true;
 }

int petit_facteur(string ss)
 {int i,i1,i2,ite;Big n1;
  for(ite=0;ite<fact.size();ite++)
      {i=fact[ite];i1=0;n1=0;
       while(i1<ss.length())
        {for(i2=i1;i2<ss.length();i2++)if(ss[i2]=='{')break;else n1=n1*b+w[ss[i2]];
         if(i2== ss.length()){if((n1%i)==0)return i;else break;}
           else{n1=n1%i;for(i2++;ss[i2]!='}';i2++){if(n1!=((n1*b+w[ss[i2]])%i))break;}
                if(ss[i2]!='}')break;}i1=i2+1;
         if(i1==ss.length())if(n1==0)return i;
        }
      }return 0;
 } 

void checkpat(string pat)
{int i; bool test; Big n1; string ss;
  i=0;n1=0;test=false;
  while(i<pat.length()){if(pat[i]=='{'){test=true;while(pat[i]!='}')i++;i++;}
                               else{n1=n1*b+w[pat[i]];ss=ss+pat[i];i++;}}
  if(prime(n1)) {cout<<'"'<<ss<<'"'<<'='<<s10(n1)<<",\n";return;}
  if(!test){cerr<<pat<<" n'est pas premier\n";return;}
  if(petit_facteur(pat)>0){cerr<<pat<<" a un facteur "<<petit_facteur(pat)<<"\n";return;}
 cout<<pat<<"\n";
}

void printres(vector<int>point,string past,string pat)
{int ipat=0,l,i,ipatp; bool test=false; char c; string loop,forw; vector<int>pointf;
  pointf.clear();for(l=0;l<found.size();l++)pointf.push_back(point[l]);ipatp=0;
  while(ipatp<pat.size())if(pat[ipatp]!='{')
                             {for(l=0;l<found.size();l++)if(found[l][pointf[l]]==pat[ipatp])
                                 {pointf[l]++;if(found[l][pointf[l]]=='"'){
//cerr<<" #"<<l<<','<<point[l]<<','<<pointf[l]<<'\n';
                                                 return;}}ipatp++;}
                           else{while(pat[ipatp]!='}')ipatp++;ipatp++;}
//cerr<<'?'<<past<<'+'<<pat<<'\n';for(l=0;l<found.size();l++)cerr<<' '<<point[l];cerr<<'\n';
  if(petit_facteur(past+pat)>0){cerr<<past+pat<<" a un facteur "<<petit_facteur(past+pat)<<"\n";return;}
  if((past.size()+pat.size())>m){cout<<past+pat<<'\n';return;}
  while(ipat<pat.size())
  {if(pat[ipat]!='{')
     {c=pat[ipat];for(l=0;l<found.size();l++){if(found[l][point[l]]==c){point[l]++;if(found[l][point[l]]=='"')return;}}
      past=past+pat[ipat];ipat++;
     }
   else
    {for(ipatp=ipat+1;pat[ipatp]!='}';ipatp++)
      {c=pat[ipatp];for(l=0;l<found.size();l++)if((found[l][point[l]])==c)break;
       if(l<found.size())forw.push_back(c); else loop.push_back(c);} 
     if(!loop.empty()){past=past+'{'+loop+'}';}
     printres(point,past,pat.substr(ipatp+1,pat.size()));
     for(i=0;i<forw.size();i++){printres(point,past,forw[i]+pat.substr(ipat,pat.size()));}
     return;
    }
  }checkpat(past);
}

ifstream kern; 

main(int argc, char *argv[])
{string p,pat,pp,ms,pref,prefms;
int ip,ipat,ipatp,l,i;

ms=argv[1];
pref="kernel"; prefms=pref+ms;b=atoi(argv[1]);
kern.open(prefms.c_str());
 for(char c='0';c<='9';c++){w[c]=0+c-'0';tr[0+c-'0']=c;}
 for(char c='A';c<='Z';c++){w[c]=10+c-'A';tr[10+c-'A']=c;}
 for(char c='a';c<='z';c++){w[c]=36+c-'a';tr[36+c-'a']=c;}
 for(i=2;i<b*b;i++)if(ok(i))fact.push_back(i);
if(argc>2)m=atoi(argv[2]); else m=100000;
while(cin>>pat)
{cerr<<pat<<" keeps "<<"\n";
 found.clear();point.clear();
 while(kern>>p)
  {ip=1;ipat=0; 
   while(ipat<pat.size())
     {if(pat[ipat]!='{'){if(p[ip]==pat[ipat]){ip++;ipat++;if(p[ip]=='"')break;}else ipat++;}
      else{ipatp=ipat+1;while(pat[ipatp]!='}') {if(p[ip]==pat[ipatp]) {ip++;break;} else ipatp++;} 
           if(pat[ipatp]=='}')ipat=ipatp+1;
          }
     }
   if(p[ip]=='"'){ pp="";l=0;while(p[l]!='='){pp=pp+p[l];l++;} found.push_back(pp); point.push_back(1); cerr<<pp<<"\n";}
  }
 printres(point,"",pat);
 kern.clear();kern.seekg(0,ios::beg);
}
//kern.close();
} // fin main
