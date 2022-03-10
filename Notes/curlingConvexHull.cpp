/*
                    NOTE: Convex hull algorithm is ok

                    Apparently the 'check if point is inside convex hull' algorithm is messed up and I'm not sure why
                    Don't use this code for pt inside hull algo, look at usaco solution instead
 */
#include <bits/stdc++.h>

using namespace std;

int N;
struct point
{
    long long x,y;
    bool operator<(const point &a) const {
        return x==a.x?y<a.y:x<a.x;
    }
};

vector<point> A, B;
//cross product of vectors OA and OB        Positive for counterclockwise, negative for clockwise
long long cross(point &O,point &A,point &B)
{;
    return (A.x-O.x)*(B.y-O.y) - (B.x-O.x)*(A.y-O.y);
}
vector<point> convex_hull(vector<point> &v)
{
    sort(v.begin(),v.end());

    int n = v.size(), k = 0;
    if (n <= 3) return v;

    vector<point> res(2*n);
    //build lower hull
    for (int i=0;i<n;i++)
    {
        while(k >= 2 && cross(res[k-2],res[k-1],v[i]) <= 0) //remove k-1 if it is a clockwise turn
            k--;
        res[k++] = v[i];
    }
    //build upper hull
    int t = k+1; //t represents all pts in lower hull and the  initial pt for upper
    for (int i=n-1;i>0;i--)
    {
        while(k >= t && cross(res[k-2],res[k-1],v[i-1]) <= 0) //remove k-1 if it is a clockwise turn
            k--;
        res[k++] = v[i-1];
    }
    res.resize(k-1); //resize

    return res;
}
bool is_in(point &p, vector<point> &C, point cen) //is p in the polygon C? (helper centroid pt)
{
    int lo=0,hi=C.size();
    while(lo+1 < hi) //bsearch for two adjacent vectors that encompass p
    {
        int mid = (lo+hi)/2;

        //draw it out, realize that this has to hold if p is between lo and mid (assuming that C is sorted counterclockwise)
        if (cross(cen,p,C[lo]) <= 0 && cross(cen,p,C[mid]) >= 0)
            hi = mid;
        else
            lo = mid;
    }
    hi %= C.size(); //edge case w/ lo=N-1,hi=N;
    int d1 = cross(C[hi],C[lo],p), d2 = cross(C[lo],cen,p), d3 = cross(cen,C[hi],p);

    //check if the triangle that lo/hi creates contains p
    return (d1 >= 0 && d2 >= 0 && d3 >= 0) || (d1 <= 0 && d2 <= 0 && d3 <= 0);
}
int solve(vector<point> &C, vector<point> &P) //given chull and list of points, see how many pts are inside polygon
{
    int n = C.size();
    point cen {0,0};
    for (auto &p: C)  //compute centroid of chull
        cen.x += p.x, cen.y += p.y;

    cen.x /= n; cen.y /= n;

    int res = 0;
    for (auto &p: P)
        if (is_in(p,C,cen))
            res++;
    return res;
}
int main()
{
    ofstream fout("curling.out");
    ifstream fin("curling.in");

    ios_base::sync_with_stdio(false); //faster I/O
    fin.tie(NULL); //include only for non-interactive problems

    fin >> N;
    for (int i=0;i<2*N;i++)
    {
        long long x,y; fin >> x >> y;

        point p = {x,y};
        if (i<N) A.push_back(p);
        else B.push_back(p);
    }

    vector<point> cA = convex_hull(A); //compute convex hulls, in counterclockwise order starting from leftmost x
    vector<point> cB = convex_hull(B);

    fout << solve(cA,B) << ' ' << solve(cB,A) << '\n';

    return 0;
}