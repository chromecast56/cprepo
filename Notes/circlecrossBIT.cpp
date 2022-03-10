#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100001;
int N;
map<int,int> mp; //val,ind
int BT[MAXN];

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
    while (ind <= MAXN) {
        BT[ind] += val;
        ind += ind & (-ind);
    }
}
int main()
{
    ofstream fout("circlecross.out");
    ifstream fin("circlecross.in");

    fin >> N;
    int res = 0;
    vector<pair<int,int>> c(N,make_pair(-1,-1));
    for (int i=0;i<2*N;i++)
    {
        int val; fin >> val; val--;

        if (c[val].first==-1)
            c[val].first = i;
        else
            c[val].second = i;
    }
    sort(c.begin(),c.end());

    for (int i=0;i<N;i++)
    {
        res += bit_get(c[i].second) - bit_get(c[i].first);
        bit_add(c[i].second,1);
    }

    fout << res << "\n";
    return 0;
}