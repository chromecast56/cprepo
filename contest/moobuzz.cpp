#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
typedef vector<int> vi;
            //1,2,4,7,8,11,13,14
int a[] = {1,2,4,7,8,11,13,14};
int main()
{
    ofstream fout("moobuzz.out");
    ifstream fin("moobuzz.in");
    ios_base::sync_with_stdio(false);
    cin.tie();
    int n;
    fin>>n; n--;

    int res = 0;
    res += 15*(n/8);
    n %= 8;
    res += a[n];
    fout << res << '\n';

    return 0;
}