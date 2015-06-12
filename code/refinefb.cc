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

vector<string> found; vector<int> pointl,pointr; vector <int> fact; 
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

void printresr(vector<int>pointl,string pastl,string pat,vector<int>pointr,string pastr);

void printresl(vector<int>pointl,string pastl,string pat,vector<int>pointr,string pastr)
{int ipat=0,l,i,ipatp; bool test=false; char c; string loop,forw; vector<int>pointf;
//cerr<<'?'<<pastl<<'+'<<pat<<'+'<<pastr<<"\n";for(l=0;l<found.size();l++)cerr<<';'<<pointl[l]<<','<<pointr[l]<<"\n";
  pointf.clear();for(l=0;l<found.size();l++)pointf.push_back(pointl[l]);ipatp=0;
  while(ipatp<pat.size())if(pat[ipatp]!='{')
                             {for(l=0;l<found.size();l++)if(found[l][pointf[l]]==pat[ipatp])
                                 {pointf[l]++;if(pointf[l]>pointr[l]){return;}}ipatp++;}
                           else{while(pat[ipatp]!='}')ipatp++;ipatp++;}
  if(petit_facteur(pastl+pat+pastr)>0){cerr<<pastl+pat+pastr<<" a un facteur "<<petit_facteur(pastl+pat+pastr)<<"\n";return;}
  if((pastl.size()+pat.size()+pastr.size())>m){cout<<pastl+pat+pastr<<'\n';return;}
  while(ipat<pat.size())
  {if(pat[ipat]!='{')
     {c=pat[ipat];for(l=0;l<found.size();l++){if(found[l][pointl[l]]==c){pointl[l]++;if(pointl[l]>pointr[l])break;}}
      if(l<found.size())return;pastl=pastl+c;ipat++;
     }
   else
    {for(ipatp=ipat+1;pat[ipatp]!='}';ipatp++)
      {c=pat[ipatp];for(l=0;l<found.size();l++)if((found[l][pointl[l]])==c)break;
       if(l<found.size())forw.push_back(c); else loop.push_back(c);} 
     if(!loop.empty()){pastl=pastl+'{'+loop+'}';}
     printresr(pointl,pastl,pat.substr(ipatp+1,pat.size()),pointr,pastr);
     for(i=0;i<forw.size();i++){ 
        printresr(pointl,pastl,forw[i]+pat.substr(ipat,pat.size()),pointr,pastr);}
     return;
    }
  }checkpat(pastl+pastr);
}

void printresr(vector<int>pointl,string pastl,string pat,vector<int>pointr,string pastr)
{int ipat=pat.size()-1,l,i,ipatp; bool test=false; char c; string loop,forw; vector<int>pointf;
//cerr<<'!'<<pastl<<'+'<<pat<<'+'<<pastr<<"\n";for(l=0;l<found.size();l++)cerr<<';'<<pointl[l]<<','<<pointr[l]<<"\n";
  pointf.clear();for(l=0;l<found.size();l++)pointf.push_back(pointl[l]);ipatp=0;
  while(ipatp<pat.size())if(pat[ipatp]!='{')
                             {for(l=0;l<found.size();l++)if(found[l][pointf[l]]==pat[ipatp])
                                 {pointf[l]++;if(pointf[l]>pointr[l]){return;}}ipatp++;}
                           else{while(pat[ipatp]!='}')ipatp++;ipatp++;}
  if(petit_facteur(pastl+pat+pastr)>0){cerr<<pastl+pat+pastr<<" a un facteur "<<petit_facteur(pastl+pat+pastr)<<"\n";return;}
  if((pastl.size()+pat.size()+pastr.size())>m){cout<<pastl+pat+pastr<<'\n';return;}
  while(ipat>=0)
  {if(pat[ipat]!='}')
     {c=pat[ipat];  
      for(l=0;l<found.size();l++){if(found[l][pointr[l]]==c){pointr[l]--;if(pointl[l]>pointr[l])break;}}
      if(l<found.size())return;pastr=c+pastr;ipat--;
     }
   else
    {for(ipatp=ipat-1;pat[ipatp]!='{';ipatp--)
      {c=pat[ipatp];for(l=0;l<found.size();l++)if((found[l][pointr[l]])==c)break;
       if(l<found.size())forw=c+forw; else loop=c+loop;}
     if(!loop.empty()){pastr='{'+loop+'}'+pastr;} 
     printresl(pointl,pastl,pat.substr(0,ipatp),pointr,pastr);
     for(i=0;i<forw.size();i++){
        printresl(pointl,pastl,pat.substr(0,ipat+1)+forw[i],pointr,pastr);}
     return;
    }
  }checkpat(pastl+pastr);
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
 found.clear();pointl.clear();pointr.clear();
 while(kern>>p)
  {ip=1;ipat=0; 
   while(ipat<pat.size())
     {if(pat[ipat]!='{'){if(p[ip]==pat[ipat]){ip++;ipat++;if(p[ip]=='"')break;}else ipat++;}
      else{ipatp=ipat+1;while(pat[ipatp]!='}') {if(p[ip]==pat[ipatp]) {ip++;break;} else ipatp++;} 
           if(pat[ipatp]=='}')ipat=ipatp+1;
          }
     }
   if(p[ip]=='"'){ pp="";l=0;while(p[l]!='='){pp=pp+p[l];l++;} found.push_back(pp); 
                   pointl.push_back(1); pointr.push_back(l-2); cerr<<pp<<"\n";}
  }
 printresl(pointl,"",pat,pointr,"");
 kern.clear();kern.seekg(0,ios::beg);
}
//kern.close();
} // fin main
