#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
#define F first
#define S second
#define sz(x) (int) (x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define pb push_back


int main()
{
    int res = 0;
    /*for (int a=0;a<30;a++)
        for (int b=a+1;b<30;b++)
            if ((1<<b)-(1<<a) < 1000)
                res++;*/

    /*for (int i=1;i<=66;i++)
        for (int j=1;j<i;j++)
            for (int k=1;k<j;k++)
                if (i+j+k==66)
                    res++;*/

    /*for (int b=-1000;b<=1000;b++)
        for (int d=1;d<=1000;d++)
            if (3*b*b+2*d*d==b*d*d)
                cout << b << ' ' << d << '\n';*/

    /*for (int m=1;m<=30;m++)
        for (int n=m+1;n<=30;n++) {
            bool good = 0;
            for (int a=0;a<500;a++)
                for (int b=0;b<500;b++)
                    if (m*(1+4*a)==n*(1+4*b))
                        good = 1;
            if (good) {
                res++;
                cout << m << ' ' << n << '\n';
            }
        }*/

    int n = 2020, m = 2021;
    res += 1; //1 case
    for (int i=2;i<100000;i++) {
        n += 18; m += 19;
        int gcd = __gcd(m,n);
        assert(n%gcd==0 && m%gcd==0);
        n /= gcd, m /= gcd;
        if (n+1==m) {
            cout << i << ' ';
            res += i;
        }
    }
    cout << endl;

    cout << res;

    return 0;
}


