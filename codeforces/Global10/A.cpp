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
        int n; cin>>n; vi a(n);
        for (int i=0;i<n;i++) cin>>a[i];

        for (int i=0;i<n;i++) {
            if (i%2==0 && a[i]<0) a[i] *= -1;
            if (i%2==1 && a[i]>0) a[i] *= -1;

            cout << a[i] << ' ';
        }
        cout << endl;
    }

    return 0;
}