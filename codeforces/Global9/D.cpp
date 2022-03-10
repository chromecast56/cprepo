/*
                Note when you do the operation, x'+y' = x+y, so the sum of the elements is constant
                (You can experiment with this)
                We want to maxmise x^2+y^2, so if x'=x+d and y'=y-d, x^2+y^2 will always be greater after any operation
                In turn, the sum of a_i^2 is maximized when all the operations we can do on the resulting array result in d=0

                WLOG the array is sorted at the end
                For given i<j, then the bitset of a_i should be a subset of a_j. (a_j contains all the 1 bits of a_i, and maybe more)

                This will happen when all the on bits flow to one side

                    - Maintain number of 1 bits for each position
                    - Greedily select all possible for a_i, and add to res
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

int a[20];      //count the number of occurences of bit i in all a_i
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n;cin>>n;
    int s = 0;
    for (int i=0;i<n;i++) {
        int x; cin>>x;

        for (int j=0;j<20;j++)
            if (x & (1<<j))
                a[j]++;
    }

    ll res = 0;
    for (int i=0;i<n;i++) {
        ll val = 0;
        for (int j=0;j<20;j++)
            if (a[j])
                val += (1<<j), a[j]--;

        res += val*val;
    }

    cout << res << '\n';

    return 0;
}