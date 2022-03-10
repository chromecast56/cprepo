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
        string x; cin>>x;
        int a=0,b=0,c=0;
        for (int i=0;i<x.size();i++) {
            if (x[i]=='R') a++;
            if (x[i]=='P') b++;
            if (x[i]=='S') c++;
        }

        char res;
        if (a >= max(b,c)) res = 'P';
        else if (b >= max(a,c)) res = 'S';
        else res = 'R';

        for (int i=0;i<x.size();i++) cout << res;
        cout << endl;
    }

    return 0;
}