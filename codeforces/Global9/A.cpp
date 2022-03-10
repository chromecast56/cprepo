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
        int a,b,n;cin>>a>>b>>n;
        if (b>a) swap(a,b);
        int res = 0;
        while(1) {
            b += a, res++;
            if (b>n) break;
            a += b, res++;
            if (a>n) break;
        }
        cout << res << '\n';
    }

    return 0;
}