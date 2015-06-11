#include <cmath>
#include <list>
#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
using namespace std;

bool ok(long int n) // is prime?
 {unsigned int kk;
 if (n<2) return false;
 for (kk=2;kk*kk<=n;kk++)
     {if(n % kk==0)return  false;}
 return true;
 }

int main()
{
int i,j,k;
vector <double> sizem ( 
{0,0, 2, 3, 3, 8, 7, 9, 15, 12, 26, 152, 17, 228, 240, 100, 483, 1278, 50, 3458, 651, 2598, 1242, 6016, 306, 17584, 5662, 17200, 5782, 57252, 220, 79182, 45205, 57676, 56457, 182378, 6295, 314986, 106838, 230317, 37772, 689061, 4551, 900795, 255911, 323436, 399012, 1436289, 29103, 4365265, 189914});
j=0;
for (i=2;i<sizem.size();i++)if(ok(i)){j++;cout<<"i="<<i<<" ==> "<<sizem[i]<<" :log/i: "<<log(sizem[i])/i<<" :log/log(i): "<<log(sizem[i])/log(i)<<" :log*log(i)/i: "<<log(sizem[i])*log(i)/i<<'\n';}
cout<<'\n';
for (i=1;i<6;i++)cout<<"i="<<pow(2,i)<<" ==> "<<sizem[pow(2,i)]<<" :log/i: "<<log(sizem[pow(2,i)])/pow(2,i)<<'\n';
cout<<'\n';
for (i=1;i<4;i++)cout<<"i="<<pow(3,i)<<" ==> "<<sizem[pow(3,i)]<<" :log/i: "<<log(sizem[pow(3,i)])/pow(3,i)<<'\n';
cout<<'\n';
for (i=1;i<3;i++)cout<<"i="<<pow(5,i)<<" ==> "<<sizem[pow(5,i)]<<" :log/i: "<<log(sizem[pow(5,i)])/pow(5,i)<<'\n';
cout<<'\n';
for (i=1;i<3;i++)cout<<"i="<<pow(7,i)<<" ==> "<<sizem[pow(7,i)]<<" :log/i: "<<log(sizem[pow(7,i)])/pow(7,i)<<'\n';
cout<<'\n';
for (i=2;i<51;i++)cout<<"i="<<i<<" ==> "<<sizem[i]<<" :log/i: "<<log(sizem[i])/i<<'\n';
}
