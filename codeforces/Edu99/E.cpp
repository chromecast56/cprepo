/*
                        Summary:

                        Reverse the arrays
                        Now we go from maximum to minimym

                        Because each segment must have DECREASING minimums, the possible positions of the dividers cannot overlap
                        To elaborate, each dividor of the array has some wiggle room (Ex. If you have array 4,5,4,5,2,1 and b_0 = 4, then the first dividor can range from 0 to 3)
                        And they are nonoverlapping
                        If they overlap, then b is not monotonically decreasing

                        This means that we can simply multiply the sizes of the wiggle rooms together (or 0 if its not possible)

                        How to do this?


                        Use 2 pointer:

                        Slow pointer will iterate over all the dividers
                        Because the possible positions of consecutive dividers is monotonically increasing,
                        the fast pointer will be the dividor index. With this pointer we check the minimum position, iterate to the maximum position (for a given divider that corresponds to a b_i)
                        , and then iterate to the min position for the next divider

                        min position = The first position where a_i = b_d (if a_i jumps over b_d then the config is impossible)
                        max position = The first position before a_i < b_d      (but we can say max' = first where a_i < b_d)

                        And multiply the (max'-min) together

                        We can add a_n+1 = -1 so that we're able to finish the last divider correctly

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
const int N = 200200;

int a[N], b[N];

int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n,m;
    cin>>n>>m;
    for (int i=0;i<n;i++) cin>>a[i];
    for (int i=0;i<m;i++) cin>>b[i];

    reverse(a,a+n);
    reverse(b,b+m);
    a[n] = -1;
    //algo = find a_x, find a_m then a_y and repeat... since steps 2/3 repeat we do step 1 outside the loop

    int pos = 0, mn = a[0];

    while(pos < n && mn > b[0])                         //update, check, update, check...  Always update before check               If you update after check, then the condition might not be met and the thing wont update
        pos++, mn = min(mn,a[pos]);

    if (pos == n || mn < b[0]) { //means that the minimum of the prefix jumps over b[0], no way to make it equal
        puts("0");
        return 0;
    }

    assert(mn == b[0]);


    ll res = 1;
    for (int itr=0;itr<m-1;itr++) { //calc for m-1 subarrays
        bool f = 1;

        int npos = pos;
        while(npos < n && mn != b[itr+1]) { //2 pointer to find a_m and a_y
            npos++;
            mn = min(mn,a[npos]);

            if (f && mn < b[itr]) {
                f = 0;
                res = (res*(npos-pos)) % 998244353;
            }
        }

        if (npos == n || mn != b[itr+1]) {
            puts("0");
            return 0;
        }

        pos = npos;
    }

    if (*min_element(a+pos,a+n) != b[m-1]) {
        puts("0");
        return 0;
    }

    cout << res << '\n';

    //check if last subarray works

    return 0;
}