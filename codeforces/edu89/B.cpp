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
        string x;cin>>x;
        vi v;
        for (int i=0;i<x.size();i++) v.pb(x[i]-'0');

        int res = 0;
        while(1) {
            bool b = 0;
            int n = v.size();

            for (int i=n-2;i>=0;i--)
                if ((v[i]^v[i+1]) == 1) {
                    b=1;
                    v.erase(v.begin()+(i+1));
                    v.erase(v.begin()+i);
                    res++; i--;
                }

            if (!b)
                break;
        }
        if (res%2) cout << "da\n";
        else cout << "net\n";
    }



    return 0;
}