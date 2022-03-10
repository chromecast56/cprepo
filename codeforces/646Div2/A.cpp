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

    int t; cin>>t;
    while(t--) {
        int n,x;
        cin>>n>>x;

        int e=0,o=0;
        for (int i=0;i<n;i++) {
            int a; cin>>a;
            if (a%2) o++; else e++;
        }

        bool b = 0; //0 = false, 1 = true
        for (int i=0;i<=o;i++)
            if (i%2 && i <= x && x <= i+e)
                b = 1;

        if (b) cout << "Yes\n"; else cout << "No\n";
    }

    return 0;
}