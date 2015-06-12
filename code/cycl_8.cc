#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
#include <stdlib.h>

#include "big.h"   /* include MIRACL system */

#define cyclemax 8 
#define bound 1000000

using namespace std;

Miracl precision(20000,128);   /* bigs are 20000 decimal digits long */

int b,ite,n1,n2,i,j,k,h,l,m,r,i1,i2,d,dd,jj,ddd,decal; char c; string s,ss,sss;
vector <int> fact;vector <int> prm; 
int f[128];
string divfound[cyclemax+1][cyclemax+1];
Big polyn[100], polfact1[100], polfact2[100];
Big NN,Nd,Ni,Fi,Ib,Nf,Ff,N1,MM,Fb,Fc,Ma,Mb,Mc,Maa,Mbb,Faa,Fbb,X,Y,Z,FZ,L2,Ndd;
vector <Big> factors;

char tr[128]; int w[128];

string sb(Big x)
{Big y=x; int r; string s=""; char c;
 while (y!=0){r=y%b;y=y/b;s=tr[r]+s;}return s;
}
string sb0(Big x)
{Big y=x; int r; string s=""; char c;
 if(x==0)return "0";
 while (y!=0){r=y%b;y=y/b;s=tr[r]+s;}return s;
}
string s10(Big x)
{Big y=x; int r; string s=""; char c;
 if(x==0)return "0";
 while (y!=0){r=y%10;y=y/10;s=tr[r]+s;}return s;
}
string check0()
{Ndd=Nd;
for(decal=0;decal<5;decal++) 
{
{for(ite=0;ite<fact.size();ite++)
             {i=fact[ite];n1=Ndd%i;n2=(n1*Ff+Nf)%i;
              if((n2==0)&&(((n1*Fi+Ni)%i)==n1))break;
             }
  if(ite!=fact.size()){return sb(i);}
  N1=Ndd*Ff+Nf;if(N1==0)continue;
  if(prime(N1)){cerr<<"\nnouveau premier trouvé:"<<sb(N1);return sb(N1);}
  j=0;MM=N1;factors.clear();factors.push_back(1);
  while((j<prm.size())&&(MM!=1))if((MM%prm[j])==0)
     {k=factors.size();
      for(i=0;i<k;i++)
        {for(h=0;h<factors.size();h++)if(factors[h]==(factors[i]*prm[j]))break;
         if(h==factors.size())factors.push_back(factors[i]*prm[j]);
        }
      MM=MM/prm[j];
     }
    else j++;
  for(i=0;i<factors.size();i++)
    {s=sb(factors[i]);ss=sb(N1/factors[i]);
     for(j=0;j<=s.length();j++)
      {Ma=0;for(k=0;k<j;k++)Ma=Ma*b+w[s[k]];
       Mc=0;Fc=1;
       for(k=j;k<s.length();k++){Fc=Fc*b;Mc=Mc*b+w[s[k]];}
       for(dd=0;dd<b;dd++)
          {Mb=0;Fb=1;if((dd==0)&&(j==0))continue;
           for(h=1;h<m;h++)
            {Mb=Mb*b+dd;Fb=Fb*b;X=Ndd;Y=Ma;
             for(l=0;l<20;l++)
                {X=X*Fi+Ni;Y=Y*Fb+Mb;if(((X*Ff+Nf)%(Y*Fc+Mc))!=0)break;
                }
             if(l==20){s=sb((X*Ff+Nf)/(Y*Fc+Mc));ss="";
                       cerr<<"\n"<<sb(Y*Fc+Mc)<<"*"<<s<<" = "<<sb(X*Ff+Nf);
                       for(i=0;i<=m;i++){polyn[i]=0;polfact1[i]=0;polfact2[i]=0;}
                       polyn[m]=Ndd*Ff*(b-1)*(b-1)+d*Ff*(b-1);
                       polyn[0]=Nf*(b-1)*(b-1)-d*Ff*(b-1);
                       polfact1[h]=Ma*Fc*(b-1)+dd*Fc;
                       polfact1[0]=Mc*(b-1)-dd*Fc;L2=1;j=0;
                       for(i=s.length()-1;i>=0;i--)
                          {for(k=1;(k<=19)&&(i>=k);k++)if(s[i-k]!=s[i])break;
                           if(k<=19){if(k>=15){polfact2[j]=polfact2[j]-w[s[i]]*L2;
                                               sss=s[i];sss="{"+sss+"}";i=i-k+1;
                                               for(k=k;k<=19;k++){sss=sss+'-';L2=L2/b;}
                                               for(k=0;k<decal;k++)sss=sss+'-';
                                               ss=sss+ss;
                                               j++;polfact2[j]=w[s[i]]*L2;
                                              }
                                       else {ss=s[i]+ss;
                                             polfact2[j]=polfact2[j]+w[s[i]]*(b-1)*L2;L2=L2*b;
                                            }
                                    }
                             else{sss=s[i];sss="{"+sss;sss=sss+'}';
                                  for(k=0;k<decal;k++)sss=sss+'-';
                                  ss=sss+ss;
                                  polfact2[j]=polfact2[j]-w[s[i]]*L2;
                                  j++;polfact2[j]=w[s[i]]*L2;i=i-19;
                                 }
                          }
                       for(k=i;k>=0;k--){ss=s[k]+ss;
                                         polfact2[j]=polfact2[j]+w[s[k]]*(b-1)*L2;
                                         L2=L2*b;
                                        }
                       for(i=0;i<=m;i++){X=polyn[i];for(j=0;j<=i;j++)
                                                       X=X-polfact1[j]*polfact2[i-j];
                                         if(X!=0){cerr<<"\n%%% : ";
                                                  for(j=0;j<=m;j++)cerr<<polyn[m-j]<<',';
                                                  cerr<<"\n    : ";
                                                  for(j=0;j<=m;j++)cerr<<polfact1[m-j]<<',';
                                                  cerr<<"\n    : ";
                                                  for(j=0;j<=m;j++)cerr<<polfact2[m-j]<<',';
                                                  break;
                                                 }
                                        }
                       ss=sb(Mc)+"]*["+ss+']';for(decal=decal;decal>0;decal--)ss='-'+ss;
                       return ('['+sb(Ma)+'{'+sb0(Mb)+'}'+ss);
                   }
            }
        }
      }
    }
  N1=Ndd*Ff+Nf;if(m>=4)
  for(i=0;i<factors.size();i++)
    {s=sb(factors[i]);ss=sb(N1/factors[i]);
     for(j=0;j<=s.length();j++)
      {Ma=0;for(k=0;k<j;k++)Ma=Ma*b+w[s[k]];
       for(jj=j;jj<=s.length();jj++)
          {Maa=0;Faa=1;for(k=j;k<jj;k++){Maa=Maa*b+w[s[k]];Faa=Faa*b;}
           Mc=0;Fc=1;
           for(k=jj;k<s.length();k++){Fc=Fc*b;Mc=Mc*b+w[s[k]];}
           for(dd=0;dd<b;dd++){if((dd==0)&&(j==0))continue;for(ddd=0;ddd<b;ddd++)
              {Mb=0;Fb=1;Mbb=0;Fbb=1;
               //for(h=1;h<m;h++)
                {Mb=Mb*b+dd;Fb=Fb*b;Mbb=Mbb*b+ddd;Fbb=Fbb*b;X=Ndd;Y=Ma;Z=Maa;FZ=Faa;
                 for(l=0;l<20;l++)
                    {X=X*Fi+Ni;Y=Y*Fb+Mb;Z=Z*Fbb+Mbb;FZ=FZ*Fbb;
                     if(((X*Ff+Nf)%((Y*FZ+Z)*Fc+Mc))!=0)break;}
                 if(l==20){s=sb((X*Ff+Nf)/((Y*FZ+Z)*Fc+Mc));ss="";cerr<<"\n$ : "<<sb(Fi);
                       cerr<<"\n"<<sb((Y*FZ+Z)*Fc+Mc)<<"*"<<s<<" = "<<sb(X*Ff+Nf);
                       for(i=0;i<=m;i++){polyn[i]=0;polfact1[i]=0;polfact2[i]=0;}
                       polyn[m]=Ndd*Ff*(b-1)*(b-1)+d*Ff*(b-1);
                       polyn[0]=Nf*(b-1)*(b-1)-d*Ff*(b-1);
                       polfact1[h]=Ma*Fc*(b-1)+dd*Fc;  //à adapter
                       polfact1[0]=Mc*(b-1)-dd*Fc;L2=1;j=0;
                       for(i=s.length()-1;i>=19;i--)
                          {for(k=1;k<=19;k++)if(s[i-k]!=s[i])break;
                           if(k<=19){if(k>=15){polfact2[j]=polfact2[j]-w[s[i]]*L2;
                                               sss=s[i];sss="{"+sss+"}";i=i-k+1;
                                               for(k=k;k<=19;k++){sss=sss+'-';L2=L2/b;}
                                               ss=sss+ss;
                                               j++;polfact2[j]=w[s[i]]*L2;
                                              }
                                       else {ss=s[i]+ss;
                                             polfact2[j]=polfact2[j]+w[s[i]]*(b-1)*L2;L2=L2*b;
                                            }
                                    }
                             else{sss=s[i];sss="{"+sss;ss=sss+'}'+ss;
                                  polfact2[j]=polfact2[j]-w[s[i]]*L2;
                                  j++;polfact2[j]=w[s[i]]*L2;i=i-19;
                                 }
                          }
                       for(k=i;k>=0;k--){ss=s[k]+ss;
                                         polfact2[j]=polfact2[j]+w[s[k]]*(b-1)*L2;
                                         L2=L2*b;
                                        }
                       for(i=0;i<=m;i++){X=polyn[i];for(j=0;j<=i;j++)
                                                       X=X-polfact1[j]*polfact2[i-j];
                                         if(X!=0){cerr<<"\n%%% : ";
                                                  for(j=0;j<=m;j++)cerr<<polyn[m-j]<<',';
                                                  cerr<<"\n    : ";
                                                  for(j=0;j<=m;j++)cerr<<polfact1[m-j]<<',';
                                                  cerr<<"\n    : ";
                                                  for(j=0;j<=m;j++)cerr<<polfact2[m-j]<<',';
                                                  break;
                                                 }
                                        }
                       return ('['+sb(Ma)+'{'+sb0(Mb)+'}'+sb(Maa)+'{'+sb0(Mbb)+'}'+sb(Mc)+"]*["+ss+']');
                   }
                }
              }}
          }
      }
    }
 }
Ndd=Ndd*Fi+Ni;
}
return "";
}
bool ok(long int n) // is prime?
 {unsigned int kk;
 if (n<2) return false;
 for (kk=2;kk*kk<=n;kk++)
     {if(n % kk==0)return  false;}
 return true;
 }

main(int argc, char *argv[])
{string ms,pref,prefms,p;
ms=argv[1];b=atoi(argv[1]);
for(i=2;i<b*b*b*b;i++)if(ok(i))fact.push_back(i);
k=2;while(k<bound){NN=k;if(prime(NN))prm.push_back(k);k++;}
 for(char c='0';c<='9';c++){w[c]=0+c-'0';tr[0+c-'0']=c;}
 for(char c='A';c<='Z';c++){w[c]=10+c-'A';tr[10+c-'A']=c;}
 for(char c='a';c<='z';c++){w[c]=36+c-'a';tr[36+c-'a']=c;}
while(cin>>p)
{//if(p[0]=='{')p=p[1]+p;if(p[p.length()-1]=='}')p=p+p[p.length()-2];
 cerr<<"\n"<<p;
 NN=0;for(i1=0;p[i1]!='{';i1++)NN=NN*b+w[p[i1]];d=w[p[i1+1]];
 Nf=0;Ff=1;for(i1=i1+3;i1<p.length();i1++){Ff=Ff*b;Nf=Nf*b+w[p[i1]];}
 Ni=0;Fi=1;
 for(i=0;i<=cyclemax;i++)for(j=0;j<cyclemax;j++)divfound[i][j]="";
 for(m=1;m<=cyclemax;m++)
     {Ni=Ni*b+d;Fi=Fi*b;Nd=NN;
      for(r=0;r<m;r++)
         {if(divfound[m][r]=="")
           {divfound[m][r]=check0();
            if(divfound[m][r]!="")
              {cerr<<"\ndiv "<<divfound[m][r]<<" pour i="<<r<<" mod("<<m<<")";
               for(j=2;(j*m)<=cyclemax;j++)
                 for(k=0;k<j;k++)
                  if(divfound[j*m][r+k*m]=="")divfound[j*m][r+k*m]=divfound[m][r];
               for(i=0;i<m;i++)if(divfound[m][i]=="")break;
               if(i==m){cerr<<"\n"<<p<<" => cycle de taille "<<m<<" : ";
                        for(i=0;i<m;i++)cerr<<divfound[m][i]<<',';break;
                       }
              }
           }
          Nd=Nd*b+d; 
         }
      if(r!=m)break;
     }
 if(m>cyclemax)cout<<p<<"\n";
 cerr<<"\n===================================\n";
}
} // fin main

