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


int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n; cin>>n;
    vector<pii> ua(n); //uncompresssed
    vi a(n); //compresssed

    for (int i=0;i<n;i++) cin>>ua[i].F, ua[i].S = i;

    sort(ua.begin(),ua.end());

    for (int i=0;i<n;i++)
        a[ua[i].S] = i;


    vector<pii> res;
    /*
                    Thought process:
                        Ok this is a constructive algorithm problem, we want to construct an ordering of the inversions
                        First we reduce the problem down to a permutation (only comparative)

                        Lets take all inversion pairs that deal with a_n first
                        This means that all the inversions (x, n) satisfy x > a_n
                        The target indicies are a_pos_an+1, a_pos_an+2...         Where pos is the inverse array of a

                        After we use these inverions, a_n has to equal n (bc no more pairs with j = n)
                        But we also dont want to mess up the orderings of a for future swaps

                        BIG NOTICE: if we swap a_n with a_pos_n+1, then a_pos_n+2, ... a_pos_n, then we sort of
                        "shift" each a_i = a_n+1,+2,+3... down a value, and then a_n = n. This will not affect the ordering
                        (as those < a_n arent affected, and those > a_n are shifted down uniformly)

                        Then, we can do the same for the permutation of size n-1, and so on

                        The BIG NOTICE is key for constructive algorithms

     */
    for (int i=n-1;i>0;i--) { //iteratively downsolve for smaller permutations
        vi pos(n);
        for (int i=0;i<n;i++) pos[a[i]] = i; //create inverse array

        for (int j = a[i]+1;j<=i;j++)
            swap(a[pos[j]],a[i]),
            res.pb({pos[j],i});
    }

    cout << res.size() << '\n';
    for (auto v: res) cout << v.F+1 << ' ' << v.S+1 << '\n';


    return 0;
}