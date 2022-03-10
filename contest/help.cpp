#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;
const int MOD = 1000000007;

int p[100100]; //store powers of two

int l[100100], r[100100];
int s[200200]; //the scene; numberline
int main()
{
    ofstream fout("help.out");
    ifstream fin("help.in");
    ios_base::sync_with_stdio(false);
    cin.tie();
    int n;
    fin>>n;

    for (int i=0;i<n;i++) {
        fin>>l[i]>>r[i];
        s[l[i]]++; s[r[i]+1]--;
    }
    //psum
    for (int i=1;i<200200;i++) s[i] += s[i-1];

    p[0] = {1}; //precompute powers of 2
    for (int i=1;i<=n;i++) p[i] = (p[i-1]*2) % MOD;

    int res = {0};
    for (int i=0;i<n;i++) { //for each l, compute 2^(n-s[i])
        res = (res + p[n-s[l[i]]]) % MOD;
    }

    fout << res << '\n';

    return 0;
}