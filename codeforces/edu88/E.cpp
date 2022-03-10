/*
            Notice that whenever we have a_i = 1, it will "overpower" all the other mods, and make the end result 0
            Also notice that if we have a_i = 2 and a_i != 1, it can be seen that 2 will "overpower" all other even a_i,
            as a result of descent. But, if we experiment with a_i = 2, a_j = 3, we can see that xmod2mod3 and xmod3mod2
            result in different answers. We can prove this rigorously, but with this assumption, we can say:

                - Given that a_i is the smallest modulo, all other a_i must be multiples of a_i in order to be
                cyclically stable.

            This means that we can iterate over all least a_i and sum all solutions. This can be tricky though. We
            know we will have n/a_i possible values, and since a_i is fixed we have n/a_i - 1 possibilities. We want
            to choose k-1 of them (again, since a_i is fixed), resulting in sum = (n/a_i - 1)c(k-1)

            Seems simple, but how would we divide to get the answer? We're working in a modulus, and dividing could
            result in fractions, which is obviously not correct. Take for example, 12mod5 = 2mod5, and we want to divide
            by 3. 12/3mod5 = 4mod5, but 2/3mod5 is fractional. How do we get the right multiple in order to divide safely?

            We could iterate over all multiples, like 2mod5, 7mod5, 12mod5, etc. But this would take way too long
            (magnitude in billions or trillions). This is where we have to use the mathmatical idea that
            division in modular arithmetic is essentially multiplication of its inverse. Basically:

                - n/m mod p -= n*m' mod p
                - Where m*m' = 1modp

            This makes sense, in nonmodular stuff x * inv(x) = x*1/x = 1
            Now we can use flt to determine m':

                - Note m^(p-1) = 1modp
                - m * m^(p-2) = 1modp

                - m' = m^(p-2) modp

            Now we can use the modular multiplicative inverse to calculate "divisions", and thus calculate combinations.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;


ll dp[1000000]; //dp[i] = i! mod p
ll p = 998244353;

ll mult(ll x,ll y) {
    return (x*y) % p;
}
ll pow(ll n, ll k) { //compute n^k
    if (k==0) return 1;
    if (k==1) return n;
    int x = pow(n,k/2);
    return k % 2 ? mult(mult(x,x),n) : mult(x,x);
}
ll inv(ll x) { //return the multiplicative inverse in mod p (note since p is prime, we can use fermats little theorem)
    return pow(x,p-2);
}
ll c(ll n, ll k) { //compute nCk
    assert(n>=k);

    int x = inv(dp[k]), y = inv(dp[n-k]);
    return mult(dp[n], mult(inv(dp[k]), inv(dp[n-k])));
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n,k;
    cin>>n>>k;

    dp[0] = 1, dp[1] = 1;
    for (int i=2;i<=500000;i++)
        dp[i] = (i*dp[i-1]) % p;

    ll res = 0;
    for (int i=1;i<=n;i++)
        if (n/i >= k)  //we have enough elements to form an array, add (n/i-1)c(k-1) to total
            res = (res + c(n/i-1,k-1)) % p;


    cout << res << '\n';

    return 0;
}