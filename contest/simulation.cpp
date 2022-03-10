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

vector<vi> mp;
vector<pair<vi,vi>> res;
vi base = {1,2,3,4,5,6,7,8,9};
bool check1(vi &a) { //check if it satisfies king problem
    for (int i=0;i<sz(a)-1;i++) if (abs(a[i+1]-a[i])<=1) return 0;
    return 1;
}
bool check2(vi &a, vi &b) { //check if pairs satisfy
    for (int i=0;i<sz(a)-1;i++)
        if (abs(a[i+1]-b[i])<=1 || abs(b[i+1]-a[i])<=1 || abs(a[i]-b[i])<=1) return 0;
    if (abs(a.back()-b.back())<=1) return 0;
    return 1;
}
void print_sol(vi &a, vi &b) {
    for (int i=0;i<sz(a);i++) {
        int x1 = a[i],x2 = b[i];
        for (int j=1;j<=sz(a);j++) {
            if (j==x1 || j==x2) cout << "#  ";
            else cout << ".  ";
        }
        cout << endl;
    }
    cout << endl;
}

unordered_set<int> hsh;
ll hashh(vi &a,vi &b) { //hash function for pairs of permutations
    ll h=1;
    for (int i=0;i<sz(a);i++) {
        h = h*13 + 2*max(a[i],b[i])+min(a[i],b[i]);
    }
    return h;
}
int bins[11][11];
int main()
{
    do {
        if (check1(base)) {
            mp.pb(base);
            //for (int i=0;i<sz(base);i++) cout << base[i] << ' '; cout << endl;
        }
    }
    while(next_permutation(all(base)));
    //cout << sz(mp);
    for (int i=0;i<sz(mp);i++)
        for (int j=i+1;j<sz(mp);j++)
            if (check2(mp[i],mp[j]) && hsh.find(hashh(mp[i],mp[j])) == hsh.end()) {
                hsh.insert(hashh(mp[i],mp[j]));
                res.pb({mp[i],mp[j]});
                cout << "SOLUTION #" << sz(res) << ": \n";
                print_sol(mp[i],mp[j]);
            }

    //debugging
    /*for (int i=0;i<sz(res);i++) {
        int x1 = min(res[i].F[0],res[i].S[0]), x2 = max(res[i].F[0],res[i].S[0]);
        bins[x1][x2]++;
    }*/
    cout << sz(res) << '\n';

    return 0;
}


