/*
                                Just a regular BIT, with get and add methods
 */

#include <bits/stdc++.h>

using namespace std;

struct BIT {
    static const ll MAXN = 100000;
    ll BT[MAXN+2];
    ll get(ll ind) {
        ll sum = 0;
        ind++;
        while (ind>0) {
            sum += BT[ind];
            ind -= ind & (-ind);
        }
        return sum;
    }
    void add(ll ind, ll val) {
        ind++;
        while (ind <= MAXN) {
            BT[ind] += val;
            ind += ind & (-ind);
        }
    }
};
int main()
{

    return 0;
}