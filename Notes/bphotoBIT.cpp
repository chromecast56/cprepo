#include <bits/stdc++.h>

using namespace std;

struct BIT {
    static const int MAXN = 100000;
    int BT[MAXN+2];
    int get(int ind) {
        int sum = 0;
        ind++;
        while (ind>0) {
            sum += BT[ind];
            ind -= ind & (-ind);
        }
        return sum;
    }
    void add(int ind, int val) {
        ind++;
        while (ind <= MAXN) {
            BT[ind] += val;
            ind += ind & (-ind);
        }
    }
};
BIT L,R;
int N;
int A[MAXN];
int main()
{
    ofstream fout("bphoto.out");
    ifstream fin("bphoto.in");

    fin >> N;
    vector<pair<int,int>> B;

    for (int i=0;i<N;i++)
    {
        int x; fin >> x;
        B.push_back(make_pair(x,i));
    }
    sort(B.begin(),B.end());
    for (int i=0;i<N;i++)
        A[B[i].second] = i;

    for (int i=1;i<N;i++) //initialize right BIT
        R.add(A[i], 1);

    int res = 0;
    for (int i=0;i<N;i++)
    {
        int r = R.get(MAXN-1)-R.get(A[i]);
        int l = L.get(MAXN-1)-L.get(A[i]);

        if (l > 2*r || r > 2*l)
            res++;

        if (i!=N-1)
        {
            L.add(A[i],1);
            R.add(A[i+1],-1);
        }
    }
    fout << res << "\n";

    return 0;
}