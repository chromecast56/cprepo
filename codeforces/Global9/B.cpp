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

ll stupidpow(int a,int b) {             //NOTE: REGULAR pow WILL BE DOUBLES, might be 19.99999999, 20.00000001, etc.
    ll res = 1;
    while(b--)
         res *= a;
    return res;
}
void print(int a, int b) {
    string x = "codeforces";
    for (int i=0;i<10;i++) {
        if (i<b)
            for (int j=0;j<a;j++)
                cout << x[i];
        else
            for (int j=0;j<a-1;j++)
                cout << x[i];
    }
    cout << endl;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    ll k;
    cin>>k;

    for (int i=0;i<=50;i++) {
        ll a = stupidpow(i,10);
        if (a>=k) {
            for (int j=1;j<=10;j++)
                if (stupidpow(i,j)*stupidpow(i-1,10-j) >= k) {
                    print(i,j);
                    return 0;
                }
        }
    }

    return 0;
}