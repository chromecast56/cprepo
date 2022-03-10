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
        double h,c,t;
        cin>>h>>c>>t;

        if (t <= (h+c)/2) {
            cout << "2\n";
            continue;
        }

        double k = (c-t)/(h+c-2*t);
        int k1 = floor(k), k2 = k1+1;

        int ans = abs((k1*h+(k1-1)*c)/(2*k1-1) - t) <= abs((k2*h+(k2-1)*c)/(2*k2-1) - t) ? k1 : k2;
        cout << ans*2-1 << endl;
    }

    return 0;
}