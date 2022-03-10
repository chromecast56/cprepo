#include <bits/stdc++.h>

using namespace std;

const long long MAX = 1ll << 60;
int N;
struct point
{
    long long x,y;
    point(long long xx,long long yy)
    {
        x=xx;y=yy;
    }
};
struct compX
{
    bool operator()(const point &a,const point &b) const
    {
        if (a.x==b.x) return a.y<b.y;
        return a.x<b.x;
    }
};
struct compY
{
    bool operator()(const point &a,const point &b) const
    {
        if (a.y==b.y) return a.x<b.x;
        return a.y<b.y;
    }
};
long long solve(vector<long long> &x, vector<long long> &y)
{
    set<point,compX> setX;
    set<point,compY> setY;

    for (int i=0;i<N;i++)
    {
        setX.insert(point(x[i],y[i]));
        setY.insert(point(x[i],y[i]));
    }

    long long res1 = (setX.rbegin()->x - setX.begin()->x)*(setY.rbegin()->y - setY.begin()->y); //calc first area
    long long res2 = MAX;

    long long mx = setX.begin()->x;
    long long my = MAX, My = 0;

    for (int i=0;i<N-1;i++) //line sweep
    {
        point cur = *setX.begin();
        setX.erase(cur);
        setY.erase(cur);

        my = min(my,cur.y);
        My = max(My,cur.y);

        long long a1 = (cur.x-mx)*(My-my);
        long long a2 = (setX.rbegin()->x - setX.begin()->x)*(setY.rbegin()->y - setY.begin()->y);

        res2 = min(res2,a1+a2);
    }

    return res1 - res2;
}
int main()
{
    ofstream fout("split.out");
    ifstream fin("split.in");

    fin >> N;
    long long a,b;

    vector<long long> x,y;
    for (int i=0;i<N;i++)
    {
        fin >> a >> b;
        x.push_back(a);
        y.push_back(b);
    }

    fout << max(solve(x,y),solve(y,x)) << "\n";
    return 0;
}