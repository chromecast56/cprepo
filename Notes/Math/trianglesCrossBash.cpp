/*
                    The problem is very straightforward: Given n points (n<=300), count how many triangles formed by
                    the points have "x" points inside it, where x ranges from 0 to n-2.

                    Obvious (maybe not so obvious, but very implementation heavy) sol is to loop over all
                    triples, then count how many points inside each triple using cross products. O(n^4)

                    We can see that since n is so small, O(n^3), even O(n^3logn) suffices. The problem is now to
                    remove a linear factor.

                    Usually in problems like this (but in simple arrays), the key is to improve the transitions between
                    the states. Reducing it to constant/logrithmic instead of linear. With arbitrary points this is hard
                    However, processing the points in a specific order should be doable

                    One idea is processing by angle: taking an arbitrary point, and imagining two rays and choosing
                    all possible pairs of rays. To go from one "ray state" to the next, i.e. moving the "right" ray
                    to the right, there should be a doable transition.

                    Indeed there is. For every left ray, there'll be a linear amount of right rays going to the right.
                    Each time you move the right ray, you add a point into the active set of all possible points
                    captured by the two rays (points are colinear, so rays are 1/1). You can then sort the
                    points by the angle they make with the left ray, and you can see that as the "left ray angle"
                    increases, the number of points captured also increases: monotonic.

                    So, the point of the right ray makes a "left ray angle", and all points in the active set
                    with angle less than the right ray point are captured, and the others are not

                    This means that we should finally represent the set as an OST of angles


                    Final algo:
                    Loop over all points
                        - Find valid points, to prevent overcounting. Say that we want our base point to be the
                        left most in the triangle, and we close points above it but not below
                        - Loop over pairs of points (rays) sorted by angle, using appropriate transitions and OSTs.

`                   Final time complexity is O(n^3logn)

 */
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

int n;
vi res;
vector<pll> v;
pll operator-(pll &a,pll &b) {return {a.F-b.F,a.S-b.S};}
ll cross(pll a,pll b,pll c) { //returns ba x bc
    pll u = a-b, v = c-b;
    return u.F*v.S - u.S*v.F;
}
double angle(pll a,pll b,pll c) { //return angle of abc
    pll u = a-b,v=c-b;
    double dot = u.F*v.F+u.S*v.S, mu = u.F*u.F+u.S*u.S, mv = v.F*v.F+v.S*v.S;
    return (dot/sqrt(mu*mv));
}
struct angle_cmp { //sort by angle to vector AB
    pll a, b;
    angle_cmp(pll a,pll b) :a(a),b(b) {}
    bool operator()(int i,int j) { //sort points by angle to vector AB
        double ta = angle(b,a,v[i]), tb = angle(b,a,v[j]);
        return ta > tb;
    }
};
void solve() {
    res.resize(n);
    for (int i=0;i<n;i++) { //itr point a
        vi a;//a will store all the indexes of points that satisfy the condition: to the right of a, but point top can be vertical
        //This means that its vector cross vertical should be positive (not 0), or it is up which can be 0
        for (int j=0;j<n;j++)
            if (i != j && (cross(v[j],v[i],{v[i].F,v[i].S+1}) > 0 || (v[i].F==v[j].F && v[i].S < v[j].S)))
                a.pb(j);

        sort(all(a),angle_cmp(v[i],{v[i].F,v[i].S+1}));
        //tree<int, null_type, angle_cmp> s(angle_cmp(v[i],v[j])); //set of active points (using order statistic tree for indexes), do note null_type middle reference
        tree<double, null_type,greater<double>,rb_tree_tag, tree_order_statistics_node_update> s;
        for (int j=0;j<sz(a);j++) {
            int cnt = 0;
            s.clear();
            for (int k=j+1;k<sz(a);k++) {
                //do query
                double th = angle(v[i],v[a[j]],v[a[k]]);
                cnt = s.order_of_key(th);
                res[cnt]++;
                s.insert(th);
            }
        }
    }
}
int main()
{
    ofstream fout("triangles.out");
    ifstream fin("triangles.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fin>>n;
    for (int i=0;i<n;i++) {
        int x,y;fin>>x>>y;
        v.pb({x,y});
    }

    solve();
    for (int i=0;i<n-2;i++)
        fout << res[i] << '\n';
    return 0;
}