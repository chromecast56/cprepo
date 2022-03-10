#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
typedef vector<pii> vpii; typedef vector<pll> vpll;
#define F first
#define S second
#define sz(x) (int) (x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define pb push_back
const int MOD = 1e9+7; //998244353
const int MX = 2e5+100;
const ll INF = 1e18;

#include <ext/pb_ds/tree_policy.hpp> //set but with more operations: Tree<T>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;                                 //order_of_key(x) - find # elements less than x, index Set greater<> for comparator if needed
template <class T> using Tree = tree<T, null_type, less<T>,               //find_by_order(x) - return iterator to x lowest value (0 based), value
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
void sort(vector<t> &a) {return sort(a.begin(),a.end());}

//returns the extended gcd of two integers a,b (ax+by=gcd(a,b))
//src: https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
int GCD(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}
//returns the modular inverse, or -1 if dne
int inv(ll a,int mod = 26) {
    int x,y;
    int gcd = GCD(a,mod,x,y);
    if (gcd != 1)
        return -1;
    return x;
}
/*
        Encryption and decryption w/ affine cipher
        (a,b) is the key
        encrypt(a,b,txt) -> (a*txt[i]+b)% MOD
        decrypt(a,b,enc) -> (a^-1(enc[i]-b)% MOD
 */
int encrypt1(int a,int b,int txt,int mod = 30) {
    return (a*txt+b)%mod;
}
string decrypt(int a,int b,string enc) {
    a = inv(a);
    if (a==-1)
        return "Key not valid";
    string res = "";
    for (auto ch: enc) {
        int x = ch-'A';
        int id = (a*(x-b+26))%26;
        res += id+'A';
    }
    return res;
}

int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cout << decrypt(9,17,"CRWWZ") << '\n';

    for (int i=0;i<30;i++)
        for (int j=i+1;j<30;j++)
            if (encrypt1(10,0,i) == encrypt1(10,0,j))
                cout << i << ' ' << j << '\n';

    return 0;
}