#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
typedef vector<int> vi;


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t; cin>>t;
    while(t--) {
        int x;
        string a;
        cin>>x>>a;

        ll l = 0, res = a.size();
        bool app = 1;
        while(l < x) {
            ll B = res-l-1;
            string b;
            if (app) {
                b = a.substr(l+1,a.size()-l-1);
                a.resize(l+1);
                res -= b.size();
                B = b.size();
                for (int i=0;i< a[l]-'0';i++) {
                    if (app)
                        a += b;
                    res = (res+B)%1000000007;
                    if (app && res > x)
                        app = 0;
                }
            }
            else {
                ll add = (((a[l]-'0')-1)*B)%1000000007;
                res = (res+add)%1000000007;
            }
            l++;
        }
        cout << res << '\n';
    }

    return 0;
}