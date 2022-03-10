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
const int N = 10000100;


int dp[N]; //sieve for primality, if prime = 0, not prime = min prime divisor
int a[500500];
int res[500500][2];
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    for (int i=2;i<N;i++) //sieve
        if (!dp[i]) {
            for (int j=2*i;j<N;j+=i)
                if (!dp[j]) dp[j] = i;
        }

    //GOAL: for each a_i we want at least 1 prime divisor
    int n; cin>>n;
    for (int i=0;i<n;i++)
        cin>>a[i];


    for (int i=0;i<n;i++) {
        int p = dp[a[i]]; //minimum prime divisor

        if (p == 0)  { //a[i] is already prime
            res[i][0] = res[i][1] = -1; continue;
        }
        while(a[i]%p == 0) a[i] /= p;

        if (a[i] == 1)  //p is the only prime divisor
            res[i][0] = res[i][1] = -1;
        else
            res[i][0] = p, res[i][1] = a[i];                //then p, a[i]/p^v_p(a[i]) always works (LTE)
    }

    for (int i=0;i<2;i++) {
        for (int j=0;j<n;j++)
            cout << res[j][i] << ' ';
        cout << endl;
    }


    return 0;
}