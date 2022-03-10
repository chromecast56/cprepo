#include <bits/stdc++.h>

using namespace std;
const int MAXN = 6;


int M,N;
int A[MAXN][MAXN];
int B[MAXN][MAXN];
bool check(int b) //put in 'have to paint' constraint later
{

    memset(B,-1,sizeof(B));
    for (int i=0;i<M;i++)
        for (int j=0;j<N;j++)
            if (B[i][j] == -1 || B[i][j] != A[i][j]) {
                if ()
            }
    return 1;
}
int main()
{
//    ofstream fout("skicourse.out");
//    ifstream fin("skicourse.in");

    ios_base::sync_with_stdio(false); //faster I/O
    cin.tie(NULL); //include only for non-interactive problems

    cin >> M >> N;
    for (int i=0;i<M;i++)
        for (int j=0;j<N;j++)
        {
            char c; cin >> c;
            A[i][j] = (c=='R'? 0:1);
        }

    int lo=1,hi=min(M,N);
    while(lo<hi) {
        int mid=(lo+hi)/2;
        if (check(mid))
            lo=mid;
        else hi=mid-1;
    }

    cout << lo << '\n';
    return 0;
}
