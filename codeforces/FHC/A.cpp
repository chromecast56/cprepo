#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
#define F first
#define S second
#define sz(x) (int) (x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define pb push_back
const int MOD = 1e9+7; //998244353
const int MX = 2e5+100;
const ll INF = 1e18;

#include <ext/pb_ds/tree_policy.hpp> //set but with more operations: Tree<T>
#include <ext/pb_ds/assoc_container.hpp>    //order_of_key(x) - find # elements less than x, index
using namespace __gnu_pbds;                 //find_by_order(x) - return iterator to x lowest value (0 based), value
template <class T> using Tree = tree<T, null_type, less<T>,
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
vector<t> sort(vector<t> &a) {return sort(a.begin(),a.end());}

bool res[60][60];
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ofstream fout("../codeforces/FHC/output.txt"); //relative directory... relative to executable -> project
    int t;cin>>t;
    for (int test = 1;test<=t;test++) {
        int n;cin>>n;
        memset(res,0,sizeof(res));
        string a,b;cin>>a>>b;
        for (int i=0;i<n;i++)
            for (int j=0;j<n;j++) {
                if (i==j)
                    res[i][j] = 1;
                else if (b[i]=='N'||a[j]=='N') continue;
                else {
                    bool bo = 1;

                    int ii = min(i,j), jj = max(i,j);
                    for (int k=ii+1;k<jj;k++)
                        if (a[k]=='N'||b[k]=='N')
                            bo=0;
                    res[i][j] = bo;
                }
            }

        fout << "Case #" << test << ":\n";
        for (int i=0;i<n;i++) {
            for (int j=0;j<n;j++) fout << (res[i][j]?'Y':'N');
            fout << '\n';
        }
    }

    fout.flush();
    fout.close();

    return 0;
}