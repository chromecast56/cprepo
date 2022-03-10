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
        ll v,c,a,b;
        cin>>v>>c>>a>>b;

        if (a==0 || b==0) {
            if (v >= a && c >= b) puts("Yes"); else puts("No");
            continue;
        }
        if (v>c) a -= v-c, v=c;
        else if (v<c) b -= c-v;c=v;

        if (v >= a && c >= b ) puts("Yes"); else puts("No");
    }

    return 0;
}