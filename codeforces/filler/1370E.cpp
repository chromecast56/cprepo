
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

int solve(int b, vi &v) {
    int res = 0, cur = 0;
    for (int i=0;i<v.size();i++) {
        cur += b*v[i];
        if (cur<0) cur=0;
        res = max(res,cur);
    }

    return res;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n;
    cin>>n;

    string a,b;
    cin>>a>>b;

    map<int,int> mp;
    vi v;

    int n0 =0,m0=0;
    for (int i=0;i<n;i++) {
        if (a[i]=='0'&&b[i]=='1') v.pb(1);        //store 0/1 pairs = 0
        else if (a[i]=='1'&&b[i]=='0') v.pb(-1);   //store 1/0 pairs = 1
        else assert (a[i]==b[i]);

        if (a[i]=='0') n0++;
        if (b[i]=='0') m0++;
    }

    if (n0!=m0) { //have to have equal 0s/1s
        puts("-1");
        return 0;
    }

    /*while(mp.size()) {
        res++;
        int cur = mp.begin()->S; mp.erase(mp.begin());

        vi erase; //store list of values to erase (dont want to erase in the foreach)       //technically we can have two sets of indicies, values 0 and 1, and directly simulate the answer by monotonically
                                                                                                increasing an index alternating between the sets using std:upper_bound. Better solution below
        *//*for (auto v: mp) //ineficient, bad for strings of 0000
            if ((cur^1) == v.S)
                cur ^= 1, erase.pb(v.F);*//*

        for (auto v: erase)
            mp.erase(v);
    }*/

    //this is equivalent to maximum depth in bracket matching (equivalent to max sum subarray)

    cout << max(solve(1,v),solve(-1,v)) << '\n';

    return 0;
}
