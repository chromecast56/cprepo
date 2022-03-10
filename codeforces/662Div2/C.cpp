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

int check(vi &a,int m) {
    int n = a.size();
    priority_queue<int> pq;
    for (int i=0;i<n;i++)
        if (a[i])
            pq.push(a[i]);

    vi b(2*n); //for each index, store the numbers that can be used again (frequencies)
    for (int i=0;i<n;i++) {
        if (b[i])
            pq.push(b[i]);

        if (pq.empty())
            return 0;

        int cur = pq.top(); pq.pop();
        b[i+m] = --cur;
    }

    return 1;
}
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
        for (int i=0;i<n;i++) {
            int x;cin>>x; x--;
            a[x]++;
        }
        /*int mx = a[0], cnt=1;
        while(mx == a[cnt]) cnt++;

        cout << (n-cnt)/(mx-1) - 1 << '\n';*/
        int l=0,r=n-2;
        while(l<r) {
            int m = (l+r+1)>>1;
            if (check(a,m+1)) l = m;
            else r = m-1;
        }

        cout << l << '\n';
        /*
                    The better, more intuitive,  albiet slower binary search method:
                    Obviously if some x works, then x' < x works.

                    How to solve for some particular x?
                    Greedily choose by highest frequency
                    Once you choose some number to be in a position a[i], you make sure you cannot choose it for positions
                    (i+1,i+k). Can do with pq

                    This is what I initially thought to do, but instead just chose in i,i+k,i+2k... which is not good
                    Ex. 1212343455
                    ____________________________________________________________________________________________________
                    Take case by case, with additional restrictions
                    Try mx==2, cnt==1
                    try cnt==2,3,4...
                    You see that its always optimal to have some element at the end where cnt[a[end]] == max
                    For cnt=1, subtract the element, divide by # remaining mx, then -1 for pairwise distance
                    for cnt>1, you subtract cnt elements, bc you subtract n for every additional mx element
                    you need to fit at the end...

                    cout << (n-cnt)/(mx-1) - 1 << '\n';

         */
    }

    return 0;
}