#include <bits/stdc++.h>
/*
                            Feedback: Very very buggy

                            Bugs encountered:
                                - Forgot to flush G[i] for each test case
                                - Assumed that the union of subsets would cover all of the array, however it
                                doesn't guarentee this in the problem statement

                            What to do next time: Dont take any unecessary shortcuts in order for the code to look better
                            Only introduces more bugs
 */

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;

vi q;
int query() {
    cout << "? " << q.size() << ' ';
    for (auto val: q) cout << val << ' ';
    cout << endl;
    cout.flush();
    q.clear();

    int res; cin>>res;
    if (res == -1) exit(EXIT_FAILURE);
    return res;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t; cin>>t;
    while(t--) {
        vi G[1010];

        int n,k;
        cin>>n>>k;
        for (int i=0;i<k;i++) {
            int j;cin>>j;
            while(j--) {
                int ind; cin>>ind;
                G[i].pb(ind);
            }
        }
        for (int i=1;i<=n;i++) q.pb(i); //pb all for initial

        int a_m = query(); //max value
        int l=0,r=k-1;            //bsearch in [0,k) for subset that includes a_m
        while(l<r) {
            int m = (l+r)>>1;
            for (int i=l;i<=m;i++)
                q.insert(q.end(),G[i].begin(),G[i].end());
            if (query() == a_m) //max val is in [l,m]
                r = m;
            else            //max val in [m+1,r]
                l = m+1;
        }

        for (int i=1;i<=n;i++) if (find(G[l].begin(),G[l].end(),i) == G[l].end()) q.pb(i); //pb all but max subset
        int a_n = query();

        cout << "! ";
        for (int i=0;i<k;i++)
            if (i==l) cout << a_n << ' ';
            else cout << a_m << ' ';

        cout << endl;
        string res; cin>>res;
        if (res == "Incorrect") exit(EXIT_FAILURE);
    }

    return 0;
}