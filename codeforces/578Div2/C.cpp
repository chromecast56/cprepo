#include <bits/stdc++.h>

using namespace std;


long long gcd(long long a,long long b) {
    if (a==0) return b;
    return gcd(b%a,a);
}
int main()
{
    long long N,M,Q;
    cin>>N>>M>>Q;

    long long GCD = gcd(N,M);
    while(Q--)
    {
        long long a,b,c,d;cin>>a>>b>>c>>d;
        b--;d--;

        b /= a==1? N/GCD:M/GCD;
        d /= c==1? N/GCD:M/GCD;

        cout << (b==d?"YES":"NO") << '\n';
    }


    return 0;
}