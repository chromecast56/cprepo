#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
typedef vector<pii> vpii; typedef vector<pll> vpll;
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
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;                                 //order_of_key(x) - find # elements less than x, index Set greater<> for comparator if needed
template <class T> using Tree = tree<T, null_type, less<T>,               //find_by_order(x) - return iterator to x lowest value (0 based), value
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
void sort(vector<t> &a) {return sort(a.begin(),a.end());}


int main()
{
    ofstream fout("262144.out");
    ifstream fin("262144.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;cin>>n;
    vi a(n);
    for (int i=0;i<n;i++) cin>>a[i];

    //O(an) sol, passes within constraints fine

    //greedily go from 1 to 40, combine all possible. If odd segment, can actually do both cases in O(n) (subexponential) time. Ex. 1111111 -> 222X222, where X is a seperator
    //Nice two cases at once trick!
    //for even segments, we just merge all, and replace empty tiles with 0. This muddles implementation a bit, but this way we dont need any complicated logn query datastructures
    int res = 0;
    for (int i=1;i<=60;i++) {
        for (int j=0;j<n;j++)
            if (a[j]==i) {
                res = i;
                int itr = j+1;
                while(itr < n && (a[itr]==i || !a[itr]))
                    itr++;

                int cnt = 0;
                for (int k=j;k<itr;k++) if (a[k] == i) cnt++;

                //i2 means different things for the two test cases
                int i2 = j;
                if (cnt%2==0) { //merge all tiles and push to left side, replace other space with 0 (for easier impl)
                    //i2 = index after the cnt/2'th val
                    int goal = cnt/2;
                    while(goal) {
                        if (a[i2]==i) goal--;
                        i2++;
                    }
                    for (int k=j;k<i2;k++) if (a[k]) a[k]++;
                    for (int k=i2;k<itr;k++) a[k] = 0;
                }
                else { //trick! Split into two cases, by ++ everything, and replacing the cnt/2'th val with a barrier (-1)
                    //i2 = index of cnt/2+1'th val
                    int goal = cnt/2+1;
                    while(goal) {
                        if (a[i2]==i) goal--;
                        i2++;
                    }
                    i2--;

                    for (int k=j;k<itr;k++) if (a[k]) a[k]++;
                    a[i2] = -1;
                }

                j = --itr;
            }
    }

    cout << res << '\n';

    return 0;
}