#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;
typedef vector<pii> vpii;

template <class t>          //vector sort template
vector<t> sort(vector<t> &a) {return sort(a.begin(),a.end());}


int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n,m,x,k,y;
    cin>>n>>m>>x>>k>>y;

    vector<ll> a(n+2), b(m+2);
    for (int i=1;i<=n;i++) cin>>a[i];
    for (int i=1;i<=m;i++) cin>>b[i];

    ll res = 0;
    int pitr =  0;
    int itr = 1;
    for (int i=1;i<=m+1;i++) {

        while(itr <= n+1 && a[itr] != b[i]) itr++;

        if (itr == n+2) {
            cout << "-1\n";
            return 0;
        }

        ll M=0;
        for (int j = pitr+1; j < itr;j++) //find max value in subsegment
            M = max(M,a[j]);

        bool b0=0, b1=0; //b0 = we can fireball+berserk to 0, b1 = we can berserk to 0
        ll add;
        int sz = itr-pitr-1;
        if (sz >= k) b0 = 1;
        if (a[pitr] >= M || a[itr] >= M) b1 = 1;

        if (!b0&&!b1) {
            cout << "-1\n";
            return 0;
        }
        if (b0) { //if we have at least k elements
            ll c = min(x, y*k);

            if (b1)
                add = (sz%k)*y + (sz/k)*c;
            else
                add =  x + (sz%k)*y + (sz/k - 1)*c;
        }
        else { //less than k
            add = sz*y;
        }


        res += add;

        pitr = itr;
    }

    cout << res << '\n';

    return 0;
}