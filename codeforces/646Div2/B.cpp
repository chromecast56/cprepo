#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;

int l0[1001],l1[1001],r0[1001],r1[1001]; //l0 = change [0,i) to 0, r0 = change [i,n) to 0
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t; cin>>t;
    while(t--) {
        string x;
        cin>>x;

        memset(l0,0,sizeof(l0)); memset(l1,0,sizeof(l1)); memset(r0,0,sizeof(r0)); memset(r1,0,sizeof(r1));


         //change all to target pre/suffix
        for (int i=1;i<=x.size();i++) {
            if (x[i-1] == '0') l0[i]++;
            else l1[i]++;
            l0[i] += l0[i-1];
            l1[i] += l1[i-1];
        }
        for (int i=x.size()-1;i>=0;i--) {
            if (x[i] == '0') r0[i]++;
            else r1[i]++;
            r0[i] += r0[i+1];
            r1[i] += r1[i+1];
        }

        int res = 10000;
        for (int i=0;i<x.size();i++) {                          //stupidhead dont miss the edge cases it even gave you an edge case of 1 and 1111 dont just make an exception stupid
            int a = min(l0[i]+r1[i],l1[i]+r0[i]);
            res = min(res,a);
        }

        //if (x.size()==1) res = 0;

        cout << res << '\n';
    }

    return 0;
}