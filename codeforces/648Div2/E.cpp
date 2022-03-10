#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;


int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n; cin>>n;
    ll a[510];
    ll res = 0;
    for (int i=0;i<n;i++) cin >> a[i];
    for (int i=0;i<n;i++) for (int j=i;j<n;j++) for (int k = j;k<n;k++) res = max(res,a[i]|a[j]|a[k]);

    cout << res << '\n';

    return 0;
}