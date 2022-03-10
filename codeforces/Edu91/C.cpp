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
        int n,x; cin>>n>>x;
        vi a(n), dp(n);

        for (int i=0;i<n;i++) cin>>a[i];

        sort(a.rbegin(),a.rend());

        int itr = 0, res = 0;
        while(itr < n) {
            int i = 1;
            while(itr<n && i*a[itr] < x)
                itr++, i++;

            if (itr != n ) res++;
            itr++;
        }
        cout << res << '\n';
    }

    return 0;
}