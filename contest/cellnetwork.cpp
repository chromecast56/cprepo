#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
typedef vector<pii> vpii; typedef vector<pll> vpll;
#define F first
#define S second
#define sz(x) (int) (x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define pb push_back
const int MOD = 1e9+7; //998244353
const int MX = 2e5+100;
const ll INF = 1e18;

set<ll> city_locs;
set<ll> tower_locs;
int n, m;

bool check(ll r) {
    for (auto it = city_locs.begin(); it != city_locs.end(); it++) {
        ll city = *it;
        ll lower = min(*tower_locs.rbegin(), *tower_locs.lower_bound(city - r));
        if (abs(city - lower) > r) {
            return false;
        }
    }
    return true;
}

int main() {
    cin >> n >> m;
    ll loc;
    for (int i = 0; i < n; i++) {
        cin >> loc;
        city_locs.insert(loc);
    }
    for (int i = 0; i < m; i++) {
        cin >> loc;
        tower_locs.insert(loc);
    }
    ll min = 0;
    ll max = 10000000000;
    while (min != max) {
        ll mid = (min + max) / 2;
        if (check(mid)) {
            max = mid;
        } else {
            min = mid + 1;
        }
    }
    cout << min << endl;
}