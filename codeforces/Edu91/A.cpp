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
    int t; cin>>t;
    while(t--) {
        int n;cin>>n;
        int m=n,M=0;
        int a=0,b=0;
        bool bo = 1;
        for (int i=1;i<=n;i++) {
            int x;
            cin >> x;


            if (bo && m < M && M > x) {
                bo = 0;
                cout << "Yes\n";
                cout << a << ' ' << b << ' ' << i << '\n';
            }

            if (m > x) {
                m = x; M = 0;
                a=i;
            }
            else if (M <= x) {
                M = x; b = i;
            }
        }

        if (bo) cout << "No\n";
    }
    return 0;
}