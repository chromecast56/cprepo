/*
                                                    NOTE: Here I was like "I have to use the x var modulated and unmodulated how do I fix that"
                                                    Use another variable to satisfy the unmodulated part


                                                    Stuff I could do better:
                                                        - Maybe use while loops instead, and compute for every "batch" of k
                                                        - Substitute delta for a[i]-a[i+1]

                                                    What to do next time:
                                                        Look at the relations, when theres the iteration problem, see how to split it into two vars and minimize the iteration
 */


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;

const ll MOD = 1000000007;
ll exp(int n,ll p) {
    if (p==0) return 1;
    if (p==1) return n;
    ll x = exp(n,p/2);

    if (p%2) return (n*((x*x)%MOD))%MOD;
    else    return (x*x)%MOD;
}

int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t; cin>>t;
    while(t--) {
        int n,p;
        cin>>n>>p;

        vector<ll> a;
        for (int i=0;i<n;i++) {
            ll x; cin>>x;
            a.pb(x);
        }
        a.pb(0); //push back 0 so we can end the rolling sum correctly
        sort(a.rbegin(),a.rend());

        ll x = 0, sum = 0;                  // sum will be the "rolling sum", in that it will continuously update for lower p^k                 x is the modulated version which is the answer, sum will be the unmodulated version which holds for small n
        int cur_k = a[0];       //current k

        bool b = 0;
        for (int i=0;i<n;i++) {
            if (b) x = (x-1+MOD)%MOD;
            else if (x) x--, sum--; //minus until 0
            else x++, sum++; //x is 0, add

            x = (x*exp(p,a[i]-a[i+1]))%MOD; //fast exp x
            if (a[i] > a[i+1] && !b)
                for (int j=0;j<min(20ll,a[i]-a[i+1]);j++) {            //notice that after 20 p multiplications, sum will be over n . My problem was "The fast exp will pass over n while modding". Well, you can use an extra variable and iterate through a little (20)
                    sum *= p;
                    if (sum > n) b=1;
                }

        }

        cout << x <<  '\n';

    }
    return 0;
}