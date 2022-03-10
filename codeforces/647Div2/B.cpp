#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;

unordered_set<int> s;
int a[1100];
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t; cin>>t;
    while(t--) {
        int n; cin>>n;
        s.clear();
        for (int i=0;i<n;i++) {
            cin >> a[i];
            s.insert(a[i]);
        }

        int res = -1;
        for (int i=1;i<1024;i++) {
            bool b = 1; //1 = it works
            for (int j=0;j<n;j++) {
                int x = a[j]^i;
                if (s.find(a[j] ^ i) == s.end()) {
                    b = 0; break;
                }
            }


            if (b) {
                res = i;
                break;
            }
        }

        cout << res << '\n';
    }

    return 0;
}