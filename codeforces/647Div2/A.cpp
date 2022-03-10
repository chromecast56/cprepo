#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;


int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t;
    cin>>t;
    while(t--) {
        long double a,b;
        cin>>a>>b;

        ll x = log2(max(a,b)/min(a,b));
        if (x == log2(max(a,b)/min(a,b)))
            cout << (x+2)/3 << '\n';
        else cout << "-1\n";
    }

    return 0;
}