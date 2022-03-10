/*
                        My editorial:


                        Notice that a cannot be transformed into b if the set of elements in a is different than those of in b
                        Notice that if n is odd and the center elements (n/2) of a and b are different, we cannot map them

                        Lemma: The set of "pairs" in a is unchanged after a given amount of operations, where a pair is defined by {a_i, a_n-i)
                        Proof: Say that we want to do an operation of prefix size l. Obviously if i > l, then the pair is unchanged

                        If i <= l, then by drawing the array out we can figure out that {a_i,a_n-i} maps to {a_n-l+i,a_l-i}
                        If we replace i'=l-i, the mapping results in {a_n-i',a_i'}, which means that the paired structure is still intact
                        The pairs dont get entangled!

                        This shows that if the set of pairs in a != b, then we cannot possibly map a to b. But how do we guarentee
                        that we can map a to b if their set of pairs is equal?

                        We can construct an algorithm: we map from center to edge
                        To get a_i to a_j, notice that a_i maps to a_n-l+i, or j = n-l+i. Solve for l, do an operation of size l.



                        This is an invariant, the given function does not change after a number of operations


 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;


int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();
    int t; cin>>t;
    while(t--) {
        int n; cin>>n;
        int a[510],b[510];
        vector<pii> paira,pairb;

        for (int i=0;i<n;i++) cin>>a[i];
        for (int i=0;i<n;i++) cin>>b[i];

        //if multiset of a != b, or n%2==1 and the centers are different, we cannot transpose a to b. (Multiset condition is figured out in the paired multiset condition later)
        if (n%2==1 && a[n/2] != b[n/2]) {cout << "No\n"; continue;}

        for (int i=0;i<n/2;i++) {
            pii x = {a[i],a[n-i-1]}, y = {b[i],b[n-i-1]};
            if (x.F > x.S) swap(x.F,x.S);
            if (y.F > y.S) swap(y.F,y.S);

            paira.pb(x);
            pairb.pb(y);
        }

        sort(paira.begin(),paira.end());
        sort(pairb.begin(),pairb.end());
        bool res = 1;
        for (int i=0;i<n/2;i++)
            if (paira[i] != pairb[i]) res = 0;

        cout << (res? "Yes\n":"No\n");
    }


    return 0;
}