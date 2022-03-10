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

    int t;
    cin>>t;
    while(t--) {
        ll n,k;cin>>n>>k;

        ll c = 0;
        while(1) {
            if ((n+9*c-k*(k+1)/2) % (k+1) == 0) //find least c st f(x) is a valid integer
                break;
            c++;
        }

        ll fx = (n+9*c-k*(k+1)/2)/(k+1);
        vi res;

        if (c != 0) {
            res.pb(10-k); fx -= 10-k; //want last to be the tip over
            for (int i=0;i<c;i++)
                res.pb(9), fx -= 9;
            res.pb(fx); assert(fx <= 9 && fx >= 0);
        }
        else { //no 9s
            if (fx <= 9)
                res.pb(fx);
            else {

            }
        }


        for (int i = res.size()-1;i>=0;i--)
            cout<<res[i];
        cout<<endl;
    }

    return 0;
}