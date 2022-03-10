#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
typedef vector<pii> vpii; typedef vector<pll> vpll;
#define F first
#define S second
#define sz(x) (int) (x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define pb push_back
#define lb lower_bound
const int MOD = 1e9+7; //998244353
const int MX = 2e5+100;
const ll INF = 1e18;

#include <ext/pb_ds/tree_policy.hpp> //set but with more operations: Tree<T>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;                                 //order_of_key(x) - find # elements less than x, index Set greater<> for comparator if needed
template <class T> using Tree = tree<T, null_type, less<T>,               //find_by_order(x) - return iterator to x lowest value (0 based), value
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
void sort(vector<t> &a) {return sort(a.begin(),a.end());}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void setIO(string name = "") { // empty if stdin/out
    ios_base::sync_with_stdio(0); cin.tie(0); // make IO faster
    if (sz(name)) {
        freopen((name+".in").c_str(), "r", stdin);
        freopen((name+".out").c_str(), "w", stdout);
    }
}
int sieve[11000];
vi primes;
ll f[1300][11000];
void gen_primes(int n) {
    primes.pb(1);
    for (int i=2;i<=n;i++)
        if (!sieve[i]) {
            primes.pb(i);
            for (int j=2*i;j<=n;j+=i)
                sieve[j] = 1;
        }
}
/*
        A version of knapsack dp through a series of reductions:
            - first note that the array is decomposed into cycles a_i, and sum of a_i = n
            - next note that the total time to complete a full permutation K = lcm(a_0,a_1,a_2...)
            - then note that if gcd(a_i,a_j) != 1 for any pair, then it means that we can "reduce" some of
            a_i and a_j to 1s. This allows us to simplify the problem
            - Now, since all a_i are coprime, we know that each = p^e for some different prime and exponent.
            - so given p0^e0+p1^e1+p2^e2... = n, its "permutation time" is p0^e0*p1^e1*p2^e2...
            - After precomputing the primes, we can make the following dp recurrence:
                f(n,i) is the answer for permutation length n, considering the first i primes
                f(n,i) = f(n,i-1) + f(n-p[i],i-1)*p[i] + f(n-p[i]^2,i-1)*p[i]^2...
                Is knapsack dp, considers if next cycle length is 1,p[i],p[i]^2, ... and computes
                the contribution using solution bags
 */
int main()
{
    setIO("exercise");
    ll n,m;cin>>n>>m;
    gen_primes(n);

    for (int i=0;i<=n;i++) f[0][i] = 1;

    for (int i=1;i<sz(primes);i++)
        for (int j=0;j<=n;j++) {
            f[i][j] = f[i-1][j];
            for (int k=primes[i];k<=j;k*=primes[i])
                f[i][j] = (f[i][j] + f[i-1][j-k]*k)%m;
        }

    cout << f[sz(primes)-1][n] << '\n';

    return 0;
}
