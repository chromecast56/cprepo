#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;
const int MAXN = 100100;
vi BT;
int n;

int bit_get(int ind) {
    int sum = 0;
    ind++;
    while (ind>0) {
        sum += BT[ind];
        ind -= ind & (-ind);
    }
    return sum;
}
void bit_add(int ind, int val) {
    ind++;
    while (ind < BT.size()) {
        BT[ind] += val;
        ind += ind & (-ind);
    }
}

ll solve(int *a) {
    fill(BT.begin(),BT.end(),0);
    ll result = 0;
    for (int i=n-1;i>=0;i--) {
        result += bit_get(a[i]-1);
        bit_add(a[i],1);
    }
    return result;
}
int a[MAXN];
int res[MAXN];
int main()
{
    ofstream fout("haircut.out");
    ifstream fin("haircut.in");
    ios_base::sync_with_stdio(false);
    cin.tie();
    fin>>n;
    BT.resize(n+100);
    for (int i=0;i<n;i++) {
        fin >> a[i];
    }

    for (int i=n-1;i>=0;i--) {
        for (int j=0;j<n;j++)
            if (a[j] == i+1)
                a[j]--;
        res[i] = solve(a);
    }

    for (int i=0;i<n;i++) fout << res[i] << '\n';


    return 0;
}