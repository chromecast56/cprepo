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

    int n;
    cin >> n;
    int a[100100];

    for (int i=0;i<n;i++) cin >> a[i];

    int res = 0;
    for (int b = 30; b >= 0; b--) {
        int maxall = 0;
        int maxhere = 0;

        for (int i=0;i<n;i++) {
            maxhere += a[i];
            if (a[i] > b || maxhere < 0)
                maxhere = 0;


            maxall = max(maxall,maxhere);

        }

        res = max(res,maxall - b);
    }

    cout << res << '\n';

    return 0;
}