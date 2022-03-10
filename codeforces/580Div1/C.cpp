#include <bits/stdc++.h>

using namespace std;

int res[200005];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n;cin>>n;

    if (n*n*(2*n+1)%(2*n) != n) {
        cout << "NO\n";
        return 0;
    }
    res[1] = 1; res[2] = 2*n;
    int sum = (n*n*(2*n+1)-n)/(2*n);
    for(int i=3;i<=2*n;i++) {
        if (i%2) res[i] = sum-res[i-1]-res[i-2];
        else res[i] = 1+sum-res[i-1]-res[i-2];
    }
    cout << "YES\n";
    for(int i=1;i<2*n-1;i++) cout<<res[i]<<' ';
    cout << res[2*n] << '\n';

    /*for(int i=1;i<=n;i++)
        cout << i << ' ' << i*i*(2*i+1) << ' ' << (i*i*(2*i+1)%(2*i)) << '\n';*/

    return 0;
}