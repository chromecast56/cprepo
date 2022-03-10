#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
typedef vector<int> vi;

bool comp(string &a,string &b) {
    int m = min(a.size(),b.size());
    if (a.substr(0,m) == b.substr(0,m))
        return a.size() < b.size();
    return a.substr(0,m) < b.substr(0,m);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    int t;
    cin>>t;
    while(t--) {
        string a,b;
        cin>>a>>b;

        int ind = 0;
        char mm = a[0];
        for (int i=0;i<a.size();i++) mm = min(mm,a[i]);

        while(a[ind] == mm) ind++;
        int ind2 = ind;
        char m = a[ind];
        for (int i=ind+1;i<a.size();i++)
            if (m >= a[i]) {
                m = a[i];
                ind2 = i;
            }

        swap(a[ind],a[ind2]);
        if (comp(a,b)) cout << a << '\n';
        else        cout << "---\n";
    }

    return 0;
}