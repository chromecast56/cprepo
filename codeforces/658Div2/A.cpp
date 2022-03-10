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

    int t;cin>>t;
    while(t--) {
        int n,m;cin>>n>>m;
        vi a(n), b(m);
        for (int i=0;i<n;i++) cin>>a[i];
        for (int i=0;i<m;i++) cin>>b[i];

        bool bo = 0;
        for (auto x: a) {
            for (auto y: b)
                if (y==x) {
                    bo=1;break;
                }

            if (bo) {
                cout << "YES\n";
                cout << 1 << ' ' << x  << '\n';
                break;
            }
        }

        if (!bo)
            cout << "NO\n";
    }

    return 0;
}