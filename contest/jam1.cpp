#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;

pii a[1001];
vi G[1001];
int v[1001];
void reset() {
    for (int i=0;i<=1000;i++) v[i] = 0,a[i] = {0,0}, G[i].clear();
}
int check_two(int cur, int col = 1) {
    if (v[cur]) {
        if (v[cur] != col) return 0;
        else return 1;
    }
    v[cur] = col;
    for (auto ne: G[cur])
        if (!check_two(ne,3-col))
            return 0;
    return 1;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();
    int t;cin>>t;

    for (int test=1;test<=t;test++) {
        reset();
        int n; cin>>n;
        for (int i=0;i<n;i++) {
            cin >> a[i].F >> a[i].S;

            for (int j=0;j<i;j++)
                if ((a[j].F < a[i].S && a[j].S > a[i].F) || (a[j].F>a[i].S && a[j].S<a[i].F))
                    G[i].pb(j), G[j].pb(i);
        }
        bool check = 1;
        for (int i=0;i<n;i++)
            if (!v[i])
                if (!check_two(i))
                    check = 0;

        cout << "Case #" << test << ": ";
        if (!check) cout << "IMPOSSIBLE";
        else
            for (int i=0;i<n;i++)
                if (v[i]==1) cout << 'C';
                else cout << 'J';
        cout << endl;
    }
    return 0;
}