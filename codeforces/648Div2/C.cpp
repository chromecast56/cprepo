#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;

int a[1000000], b[1000000], bv[1000000];                     // v is inverse
int v[1000000]; // add to v[i] if it takes a shift of size i   - find maximum of v
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();
    int n; cin>>n;
    for (int i=0;i<n;i++) {
        cin >> a[i];
        a[n+i] = a[i];
    }

    for (int i=0;i<n;i++) {
        cin>>b[i];
        bv[b[i]] = i;
    }

    for (int i=0;i<n;i++) { //loop over: for every a[i] see how much RIGHT shifts to get to b[i] (right+left wouldnt work)
        int x = bv[a[i]] - i < 0? (bv[a[i]]-i+n) : (bv[a[i]]-i);
        v[x]++;
    }

    int res = 0;
    for (int i=0;i<n;i++) res = max(res,v[i]);

    cout << res << '\n';

    return 0;
}