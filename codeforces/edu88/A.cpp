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
        int n,m,k;
        cin>>n>>m>>k;

        int x = min(n/k,m);

        int rest = m-n/k;

        int y = x==n/k? (rest/(k-1) + (rest%(k-1)? 1:0)): 0;
        cout << x-y << '\n';
    }

    return 0;
}