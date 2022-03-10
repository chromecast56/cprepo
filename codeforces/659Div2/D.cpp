/*
                    Game theory:

                    Motivation: If you "control" the most significant bit, there is no way for your opponent to beat you
                    Call i the most significant bit, and a the number of 1s, and b the number of 0s in bit i (sum over all vals)

                    If there is an even number of 1s (a), you cannot force a 1 imbalance (you take 1, he take 1, you take 0, he take 0)
                    Go onto the next bit. If this repeats until 0, this means that the xor sum of everything is 0, and we have a draw

                    WLOG a%2==1

                    Cases:
                        a%4==1: We take a 1 and there are 4*k remaining 1s. Test out some cases, you will find that you
                        can force zugzuang by repeating the other player's moves no matter what

                        a%4==3:
                            b%2==0: Now the second player can zugzuang. If we take a 1, they take a 1 and if we ever
                            take another one, this is equal to the reverse case of a%4==1.

                            b%2==1: We take a 0, and is the reverse case of previous. We win

                        2nd player only wins iff a%4==3 and b%2==0


                        Next time: Do casework on parity, most significant digit, etc. In these game theory questions
                        it typically boils down to zugzuang.
 */

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


int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;cin>>t;
    while(t--) {
        int n;cin>>n;
        vi a(n);
        int x = 0; //store or of all elements
        for (int i=0;i<n;i++) cin>>a[i], x ^= a[i];

        if (!x) {
            cout << "DRAW\n";
            continue;
        }

      vi f(2);
        for (int i=30;i>=0;i--)
            if (x & 1<<i) {
                for (int j=0;j<n;j++) f[a[j]>>i & 1]++;

                assert(f[1]%2==1);
                if (f[1]%4==3 && f[0]%2==0) cout << "LOSE\n";
                else cout << "WIN\n";

                break;
            }
    }

    return 0;
}