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
        int n; cin>>n;
        int a[600];
        for (int i=0;i<n;i++) cin>>a[i];

        int zcount=0, ocount=0;
        for (int i=0;i<n;i++) {
            int x; cin>>x;
            if (x) ocount++; else zcount++;
        }

        if ((ocount && !zcount) || (zcount && !ocount)) { //mean that only 1, only 0. Check if array is sorted
            bool b = 1;
            for (int i=0;i<n-1;i++) if (a[i] > a[i+1]) b=0;
            cout << (b? "Yes\n" : "No\n");
        }
        else
            cout << "Yes\n"; //otherwise there is at least 1 of each. Means that no matter what given a,b,c 1,0,0 we can rearrange whatever order


    }

    return 0;
}