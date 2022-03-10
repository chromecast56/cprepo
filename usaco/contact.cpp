/*
ID: jamesli5
PROG: contact
LANG: C++11
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
typedef vector<int> vi;
const int maxn = 200001;

struct cmp {
    bool operator()(const string &a, const string &b) const {
        if (a.size()==b.size()) return a<b;
        return a.size()<b.size();
    }
};
int a,b,n;
string X;
unordered_map<string,int> mp; //bit, frequency
set<string,cmp> freq[maxn];
int main()
{
    ofstream fout("contact.out");
    ifstream fin("contact.in");
    fin>>a>>b>>n;
    while(1) {
        string x; fin>>x;
        X += x;
        if (x.size() != 80ll) break;
    }
    for (char c: X) c -= '0';

    for (int i=0;i<X.size();i++) {
        string x;
        for (int j=0;j<a-1;j++)
            x += X[i+j];
        for (int j=a-1; j<b && i+j<X.size();j++) {
            x += X[i+j];
            mp[x]++;
        }
    }
    for (auto v: mp)
        freq[v.S].insert(v.F);

    int itr = 200000;
    while(n && itr) {
        if (!freq[itr].empty()) {
            fout << itr << '\n';
            string res; int num=0;
            for (auto s: freq[itr]) {
                res += s + ' ';
                num++;
                if (num%6==0) res.back() = '\n';
            }
            res.back() = '\n';
            fout << res;
            n--;
        }
        itr--;
    }

    return 0;
}