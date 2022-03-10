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

    int t; cin>>t;
    while(t--) {
        int a,b; cin>>a>>b;
        if (a<b) swap(a,b);

        int i = a-b; //add the difference
        if (a-2*i<0 || b-i<0) cout << b << '\n'; //limited by 1
        else {
            a -= 2*i;

            i += 2*(a/3), a %= 3;
             if (a >= 2) i++;
             cout << i << '\n';
        }
        //cout << (a-b) + 2*(b/3) << '\n'; //make equal
    }

    return 0;
}