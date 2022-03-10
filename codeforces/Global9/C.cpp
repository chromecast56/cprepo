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

    int n;cin>>n;
    vector<pii> res;
    for (int i=0;i<=n+1;i++)
        res.pb({i,i});

    for (int i=0;i<=n;i++)
        res.pb({i,i+1}), res.pb({i+1,i});

    cout << res.size() << '\n';
    for (auto a: res)
        cout << a.F << ' ' << a.S << '\n';

    return 0;
}