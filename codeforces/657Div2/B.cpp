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
        int l,r,m;cin>>l>>r>>m;

        int a,b,c;
        for (int i=l;i<=r;i++) {//loop on a
            int x = m%i;
            if (x<=(r-l)) { //x=b-c

                if (i > m) a=i,b=l,c=l+x; else a=i,b=l+x,c=l;
                break;
            }
        }

        cout << a << ' ' << b << ' ' << c << '\n';
    }

    return 0;
}