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

int mex(vi &a) {

    for (int i=0;i<a.size();i++)
        if (!a[i]) return i;

    return a.size();
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t; cin>>t;
    while(t--) {
        int n;cin>>n;
        vi a(n);
        vi freq(n+1);         //

        unordered_set<int> ls; //list of "bad" points indicies
        for (int i=0;i<n;i++) {
            cin>>a[i];
            if (a[i] != i) ls.insert(i);
            freq[a[i]]++;
        }


        vi res;
        while(!ls.empty()) { //next time: can just for loop to check bad points, can also for loop to make the freq list
            int x = mex(freq);
            if (x == n) {                   //the array has all points 0 to n-1, just pick a bad point
                int back = *ls.begin();

                freq[a[back]]--;
                freq[n]++;
                a[back] = n;

                res.pb(back);
            }
            else { // mex < n                       know that mex is a bad point
                freq[a[x]]--;
                freq[x]++;
                a[x] = x; //a[mex] = mex
                ls.erase(x);

                res.pb(x);
            }
        }


        cout << res.size() << endl;
        for (int i=0;i<res.size();i++) cout << res[i]+1 << ' ';

        cout << endl;
    }
    return 0;
}