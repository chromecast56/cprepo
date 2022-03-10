#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
typedef vector<int> vi;


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    int t;
    cin>>t;
    while(t--) {
        string x;
        cin>>x;
        int n = x.size();
        if (n>=2 && x.substr(n-2,2) == "po") cout << "FILIPINO\n";
        if (n>=4 && (x.substr(n-4,4) == "desu" || x.substr(n-4,4) == "masu")) cout << "JAPANESE\n";
        if (n>=5 && x.substr(n-5,5) == "mnida") cout << "KOREAN\n";
    }

    return 0;
}