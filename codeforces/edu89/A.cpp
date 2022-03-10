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
        ll a,b,c;
        cin>>a>>b>>c;

        if (c >= a*b) {
            cout << 1 << ' ' << -1 << '\n';
            continue;
        }

        if (a < c) cout << 1 << ' ' << b << '\n';
        else cout << -1 << ' ' << b << '\n';

    }

    return 0;
}