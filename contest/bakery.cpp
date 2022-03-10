#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;


int v[35100];
int f[35100][51];
unordered_set<int> s;
int cost(int i,int j) {
    s.erase(s.begin(),s.end());
    for (int itr = i; itr <= j; itr++) s.insert(v[itr]);
    return s.size();
}
void compute(int l,int r, int optl, int optr, int k) {
    if (l>r) return;
    s.erase(s.begin(),s.end());
    int m = (l+r)/2;
    pii best = {-1,-1}; //val,ind

    for (int i=m; i>min(m,optr); i--) s.insert(v[i]);
    for (int i = min(m,optr); i >= optl; i--) {
        best = max(best,{f[i][k-1] + s.size(),i});
        s.insert(v[i]);
    }
    f[m][k] = best.F;
    int opt = best.S;
    compute(l,m-1,optl,opt,k);
    compute(m+1,r,opt,optr,k);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    int n,k;
    cin>>n>>k;

    for (int i=1;i<=n;i++) cin >> v[i];

    for (int i=1;i<=n;i++) { //base case
        s.insert(v[i]);
        f[i][1] = s.size();
    }

    for (int i=2; i<=k;i++)
        compute(1,n,1,n,i);

    cout << f[n][k] << '\n';

    return 0;
}
