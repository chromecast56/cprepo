/*
ID: jamesli5
PROG: stamps
LANG: C++11
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
typedef vector<int> vi;
const int maxn = 2000001;

int n,k;
int f[maxn]; //define f as: the min number of coins needed to make value i (knapsack)
int a[50];
int main()
{
    ofstream fout("stamps.out");
    ifstream fin("stamps.in");
    fin>>k>>n;
    for (int i=0;i<n;i++) fin>>a[i];

    sort(a,a+n);
  //  int K = a[n-1]*K+1;
    fill(f,f+maxn,maxn);

    f[0] = 0;
    for (int i=0;i<maxn;i++)
        for (int j=0;j<n;j++)
            if (f[i] < k && f[i+a[j]] > f[i]+1)
                f[i+a[j]] = f[i]+1;

     for (int i=0;i<maxn;i++)
         if (f[i] > k) {
             fout << i-1 << '\n';
             break;
         }


    return 0;
}