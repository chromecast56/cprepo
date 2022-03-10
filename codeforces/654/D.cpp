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

    int t;
    cin>>t;
    while(t--) {
        int n,k;cin>>n>>k;
        vector<vi> res(n);
        for (int i=0;i<n;i++) for (int j=0;j<n;j++) res[i].pb(0);

        for (int j=0;j<n;j++)
            for (int i=0;i<n;i++) {
                if (!k) {
                    goto end;
                }
                res[i][(j + i) % n] = 1;
                k--;
            }
        end:;

        int Mr=0,mr=n,Mc=0,mc=n;
        vi r(n), c(n);

        for (int a=0;a<n;a++)
            for (int b=0;b<n;b++)
                if (res[a][b])
                    r[a]++, c[b]++;

        for (int a=0;a<n;a++)
            Mr = max(Mr,r[a]), mr = min(mr,r[a]), Mc = max(Mc,c[a]), mc = min(mc,c[a]);

        cout << (Mr-mr) * (Mr-mr) + (Mc-mc) * (Mc-mc) << '\n';
        for (int a=0;a<n;a++) {
            for (int b=0;b<n;b++)
                cout<<res[a][b];
            cout << endl;
        }
    }

    return 0;
}