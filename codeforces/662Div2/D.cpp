/*
                    Takeaway: This has a very intuitive brute force: Simply iterate over all (i,j), and "bloom" out in all directions
                    O((nm)^2)

                    One optimization I thought of was to dp, call f[i][j] the max bloom you can with center i,j
                    Then, for any (i,j), you can sort of "match" the 4 neighbors of it, and it will create another bloom

                    if (a[i][j]==a[i-1][j]==a[i+1][j]==a[i][j-1]==a[i][j+1]), then take min of all + 1.

                    But this doesn't lend to any easy dp recurrence... you have to add another dimension k = the max bloom,
                    and your stage will be k. Like interval dp, but on 2d.

                    O(nm*min(n,m)

                    The reason it isn't easy to recur is because f[i][j] takes in f from all directions, meaning you cant
                    guarentee optimal values for the f you call. If we could make it so that we only call f we calculate...


                    We can!

                    Now call f[i][j] the max bloom, but with the "bottom point" at i,j. This can be easily visualized.

                    You can see that if we get a dp recurrence, it will only call from i' < i, which is good!
                    The recurrence will take from (i-1,j-1),(i-1,j+1),(i-2,j). Up left, Up right, and further up
                    And we obv check if all the points are equal



                    So takeaway is: you find an intuitive brute force, but converting to dp is hard (call from uncalculated).
                    Try to find a variant that will only call from calculated



                    Alternate/intended sol?
                    Each rhombus is 4 triangles...
                    Do dp on each triangle, and ans = min of the 4

                    For each triangle:
                        f[i][j] = min(f[i-1][j],f[i][j-1]) + 1 if all are equal
                        Similar to above recurrence...
 */

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
#include <ext/pb_ds/assoc_container.hpp>    //order_of_key(x) - find # elements less than x, index
using namespace __gnu_pbds;                 //find_by_order(x) - return iterator to x lowest value (0 based), value
template <class T> using Tree = tree<T, null_type, less<T>,
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
void sort(vector<t> &a) {return sort(a.begin(),a.end());}

const int N = 2100;
int f[N][N];
char a[N][N];
int n,m;
int in_bound(int x,int y) {
    return x >= 2 && y >= 1 && y < m-1;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;

    for (int i=0;i<n;i++) {
        cin>>a[i];
        for (int j=0;j<m;j++)
            f[i][j] = 1;
    }

    //f[i][j] = 1 + min(f[i-1][j-1], f[i-1][j+1], f[i-2][j]) if the 5 points (i,j),(i-1,j-1),(i-1,j+1),(i-2,j),(i-1,j) are equal

    ll res = 0;
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++) {
            char c = a[i][j];
            if (in_bound(i,j) && a[i-1][j-1] == c && a[i-1][j+1] == c && a[i-1][j] == c && a[i-2][j] == c)
                f[i][j] = min(min(f[i-1][j-1],f[i-1][j+1]), f[i-2][j]) + 1;

            res += f[i][j];
        }

    cout << res << '\n';

    return 0;
}