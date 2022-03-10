#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;


int v[10100];
vi gen_primes() {
    for (int i=2;i<10000;i++)
        if (!v[i])
            for (int j=i<<1; j<10000; j+=i)
                v[j] = 1;

    vi res;
    for (int i=2;i<10000;i++)
        if (!v[i])
           res.pb(i);
    return res;
}
int main()
{
    ofstream fout("exercise.out");
    ifstream fin("exercise.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n,MOD;
    fin>>n>>MOD;

    vi primes = gen_primes();
    vi cycount;
    for (auto pm: primes)
        if (n >= pm)
            cycount.pb(pm), n -= pm;
        else break;

    while(1) {
        bool change = 0;
        pii m = {1000000000,-1}; //multiply, index
        for (int i=0;i<cycount.size();i++)
            m = min(m, {cycount[i]*(primes[i]-1),i});
        if (n < m.F) break;
        n -= m.F; cycount[m.S] *= primes[m.S];
            /*if (n >= cycount[i]*(primes[i]-1))
                n -= cycount[i]*(primes[i]-1), cycount[i] *= primes[i], change = 1;*/

    //    if (!change) break;
    }

    ll res = 0;
    for (auto val: cycount) {
        if (!res) res = val;
        else res = (res*val) % MOD;
    }

    res = ((res*res+res)/2) % MOD;
    fout << res << '\n';
    return 0;
}