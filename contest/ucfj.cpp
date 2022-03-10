#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
typedef vector<pii> vpii; typedef vector<pll> vpll;
#define F first
#define S second
#define all(x) (x).begin(),(x).end()
#define pb push_back

void setIO(string name = "") {
    ios_base::sync_with_stdio(0); cin.tie(0);
}
int BT[200100];

int bit_get(int ind) {
    int sum = 0;
    ind++;
    while (ind>0) {
        sum += BT[ind];
        ind -= ind & (-ind);
    }
    return sum;
}
void bit_add(int ind, int val) {
    ind++;
    while (ind < 200100) {
        BT[ind] += val;
        ind += ind & (-ind);
    }
}
int main()
{
    setIO();
    int n;cin>>n;
    vl a;
    for (int i=0;i<n;i++) {
        int x;cin>>x;a.pb(x);
    }

    vl l_occ(n+1,n-1), r_occ(n+1);
    vl l(n),r(n);
    for (int i=0;i<n;i++) {
        r[i] = r_occ[a[i]]+1;
        if (r[i]==1) r[i]--;
        r_occ[a[i]] = i;
    }
    for (int i=n-1;i>=0;i--) {
        l[i] = l_occ[a[i]]-1;
        if (l[i]==n-2) l[i]++;
        l_occ[a[i]] = i;
    } //stress test later

    vpll q(n);
    ll res=0;
    for (int i=0;i<n;i++) {
        bit_add(r[i],1);
        q[i].F = bit_get(i);
    }

    for (int i=0;i<200100;i++) BT[i]=0;
    vpii arr;
    for (int i=0;i<n;i++) arr.pb({l[i],i});
    sort(all(arr));
    int itr=0;
    for (int i=0;i<n;i++) {
        while(itr<=arr[i].F) bit_add(r[itr],1), itr++;
        arr[i].F = bit_get(arr[i].S);
    }

    for (int i=0;i<n;i++) q[arr[i].S].S = arr[i].F;

    for (int i=0;i<n;i++) {
        res += q[i].S - q[i].F;
    }
    cout << res << '\n';
    return 0;
}


