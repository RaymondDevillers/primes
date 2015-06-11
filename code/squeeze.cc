#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

main(int argc, char *argv[])
{string p; int i,j,jj,k,kk;
 while(cin>>p)
  {//              cout<<p<<"\n";
   for(i=0;i<p.length();i++)
      {if(p[i]=='{')
         {if(p[i-1]!='}'){for(j=i+1;p[j]!='}';j++)
                           if(p[j]==p[i-1]){p.erase(i-1,1);i=i-2;j--;break;}
                          if(p[j]!='}')continue;
                         }
                    else {for(k=i-2;p[k]!='{';k--)
                             {for(j=i+1;p[j]!='}';j++)if(p[k]==p[j])break;
                              if(p[j]=='}')break;
                             }
                          if(p[k]=='{'){while(p[k]!='}')p.erase(k,1);p.erase(k,1);i=k-1;continue;}
                         }
          for(j=i+1;p[j]!='}';j++)jj=j+1;
          if(p[jj+1]!='{'){for(j=i+1;p[j]!='}';j++)
                             if(p[j]==p[jj+1]){p.erase(jj+1,1);i--;break;}
                           if(p[j]!='}')continue;i=jj;
                          }
                     else {for(k=jj+2;p[k]!='}';k++)
                             {for(j=i+1;p[j]!='}';j++)if(p[k]==p[j])break;
                              if(p[j]=='}')break;
                             }
                            if(p[k]=='}'){while(p[jj+1]!='}')p.erase(jj+1,1);
                                          p.erase(jj+1,1);i=i-1;continue;
                                         }

                          }
         }
      }
   cout<<p<<"\n";
  }
} // fin main

