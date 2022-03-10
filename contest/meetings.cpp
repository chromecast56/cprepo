#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
typedef vector<int> vi;
const int N = 101;
const int L = 1000000001;

int n; ll l;
struct cow
{
    int w,d;
    double x;
    bool operator<(const cow &a) const {
        return x < a.x;
    }
};
deque<cow> c;

int main()
{
 //   ofstream fout("meetings.out");
  //  ifstream fin("meetings.in");
    ios_base::sync_with_stdio(false);
    cin.tie();
    cin>>n>>l;

    double W = 0;
    for (int i=0;i<n;i++) {
        int w,d; double x; cin>>w>>x>>d;
        c.push_back({w,d,x});
        W += w;
    }
    sort(c.begin(),c.end());

    double cur_w = 0;
    int res = 0;
    while(cur_w <= W/2) {
        double t = 1000000100;
        if (c[0].d==-1) t = min(t,c[0].x);
        if (c.back().d==1) t = min(t,l-c.back().x);
        for (int i=0;i<c.size()-1;i++) {
            if (c[i].d==1 && c[i+1].d==-1)
                t = min(t,(c[i+1].x-c[i].x)/2);
        }

        for (int i=0;i<c.size();i++) {
            c[i].x += c[i].d*t;
            if (i != 0 && c[i].x == c[i-1].x) {
                res++;
                c[i-1].d *= -1;
                c[i].d *= -1;
            }
        }
        while(c[0].x <= 0)
            cur_w += c[0].w, c.pop_front();
        while(c.back().x >= l)
            cur_w += c.back().w, c.pop_back();
    }
    cout << res << '\n';
    return 0;
}