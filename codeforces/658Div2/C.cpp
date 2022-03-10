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

int a[200000],b[200000];
string aa,bb;
void swap(int ind) {
    for (int i=0;i<=ind;i++)a[i] = 1-a[i];
    for (int i=0;i<=ind/2;i++)
        swap(a[i],a[ind-i]);
}
int calc(int itr,int x,int nswap) {
    int ind = nswap%2? x-itr:x+itr;
    int res = nswap%2? 1-a[ind]:a[ind];
    return res;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t;cin>>t;
    while(t--) {
        int n;cin>>n;
        /*for (int i=0;i<n;i++) cin>>a[i];
        for (int i=0;i<n;i++) cin>>b[i];*/
        cin>>aa>>bb;
        for (int i=0;i<n;i++) a[i] = aa[i]-'0',b[i]=bb[i]-'0';

        vi res;
        int itr=n-1;
        int x = 0, nswap = 0;
        while(itr>0) {
            while(itr>0 && calc(itr,x,nswap)==b[itr]) itr--;
            if (itr<=0) break;
            if (calc(0,x,nswap) != calc(itr,x,nswap)) res.pb(1), a[0] = 1-a[0];
            res.pb(itr+1);
            if (nswap%2==0) x += itr; else x -= itr;
            nswap++;
            //swap(itr);
            itr--;
        }

        if (calc(itr,x,nswap) != b[0]) res.pb(1);

        cout << res.size() << ' ';
        for (int i=0;i<res.size();i++) cout << res[i] << ' ';
        cout << endl;
    }

    return 0;
}