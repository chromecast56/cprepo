/*
                Takeaway:
                    Since the string is "abacaba", it can be layered, meaning that we cant just do one pass
                    Ex. Case abaca?acaba.

                    We see OH change ? -> b makes it work but since it is layered we cant make it only 1
 */

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

string c = "abacaba";
bool check(string &x, bool b) { //0 = no ? 1 = yes ?
    for (int i=0;i<7;i++)
        if (!b) {
            if (x[i] != c[i]) return 0;
        }
        else {
            if (x[i] != '?' && x[i] != c[i]) return 0;
        }
    return 1;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t;cin>>t;
    while(t--) {
        int n;cin>>n;
        string x;cin>>x;
        int r1=0,r2=0;
        int ind = -1;

        bool b = 0;
        for (int start = 0;start+7<=n;start++) {
            string sub = x.substr(start,7);
            if (!check(sub,1)) continue;

            string t = x;
            for (int i=start;i<start+7;i++) t[i] = c[i-start];

            int num = 0;
            for (int i=0;i+7<=n;i++) {
                string ssub = t.substr(i,7);
                if (check(ssub,0)) num++;
            }

            if (num==1) {
                b=1;
                cout << "yes\n";
                for (int i=0;i<n;i++) if (t[i]=='?') cout << "z"; else cout << t[i];
                cout << endl;
                break;
            }
        }
        if (!b) cout << "No\n";
        /*for (int i=0;i+7<=x.size();i++) {
            string sub = x.substr(i,7);
            r1 += check(sub,0);
            if (check(sub,1) && ind==-1) r2++,ind=i;
        }

        if (r1 > 1 || (r1==0&&r2==0)) cout << "No\n";
        else {
            cout << "Yes\n";
            if (r1==1) {
               for (int i=0;i<x.size();i++) if (x[i]=='?') cout << 'z'; else cout << x[i];
            }
            else {
                for (int i=0;i<ind;i++) if (x[i]=='?') cout << 'z'; else cout << x[i];
                cout << c;
                for (int i=ind+7;i<x.size();i++) if (x[i]=='?') cout << 'z'; else cout << x[i];
            }
            cout << endl;
        }*/
    }
    return 0;
}