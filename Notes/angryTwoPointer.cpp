#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> hb;
vector<int> l,r;
void dp(vector<int> &a)
{
    a.resize(N,2000000000);
    int it = 0;
    a[0] = 0;
    for (int i=1;i<N;i++)
    {
        while(it+1 < i && abs(hb[i]-hb[it+1]) > a[it+1]+1)
            it++;
        a[i] = min(abs(hb[i]-hb[it]), a[it+1]+1);
    }
    reverse(hb.begin(),hb.end());
}
int main()
{
    ofstream fout("angry.out");
    ifstream fin("angry.in");

    fin >> N;
    for (int i=0;i<N;i++)
    {
        int a; fin >> a;
        hb.push_back(a);
    }
    sort(hb.begin(),hb.end());
    hb.resize(unique(hb.begin(), hb.end()) - hb.begin());

    dp(l); //l[i] - min R bale i needs to explode at to destroy all leftbound bales
    dp(r); //r[i] - min R bale i needs to explode at to destroy all rightbound bales
    reverse(r.begin(),r.end());

    double res = 1000000000;
    int i=0, j=N-1;
    while(i<j) { //for every i/j, its always best to launch the cow in the middle
        double R = max((double)(hb[j]-hb[i])/2, (double) (1+max(l[i],r[j])));   //R = dist/2, or 1+max(l,r)
        res = min(res,R);
        if (l[i+1] < r[j-1])       //two pointer method
            i++;
        else
            j--;
    }
    fout << fixed << setprecision(1) << res << "\n";

    return 0;
}