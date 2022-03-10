#include <bits/stdc++.h>

using namespace std;

const int maxn = 1<<17;
const int SIZE = 1<<16; //SIZE should be a power of 2 for correctness, see http://i.imgur.com/cwKpYH1.png
                        //Note how the start of the values isn't at the beginning, and val 1 may interfere with val 13
int bb[maxn],bp[maxn],pb[maxn],pp[maxn]; //b -> can use endpt  p -> can't use endpt
void update(int ind)
{
    int l = ind*2, r = ind*2+1;
    pp[ind] = max(pb[l]+pp[r], pp[l]+bp[r]);
    pb[ind] = max(pb[l]+pb[r], pp[l]+bb[r]);
    bp[ind] = max(bb[l]+pp[r], bp[l]+bp[r]);
    bb[ind] = max(bb[l]+pb[r], bp[l]+bb[r]);
}
int main()
{
//    ofstream fout("optmilk.out");
//    ifstream fin("optmilk.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n,d; cin>>n>>d;
    for (int i=0;i<n;i++)
        cin >> bb[i+SIZE];

    for (int i=SIZE-1;i>0;i--) update(i); //build the segtree

    long long res = 0ll;
    while(d--)
    {
        int i,v; cin>>i>>v; i--;
        bb[i+SIZE] = v;

        for (int j = (i+SIZE)/2; j>0; j>>=1)
            update(j);
        res += bb[1];
    }
    cout << res << '\n';

    return 0;
}