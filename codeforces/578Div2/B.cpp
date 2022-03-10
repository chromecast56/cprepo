#include <bits/stdc++.h>

using namespace std;

int A[100];
string solve(int N,int M,int K) {
    for(int i=0;i<N-1;i++)
    {
        if (A[i]+K < A[i+1]) {
            M -= A[i+1]-(A[i]+K);
        }
        else {
            int lo = max(0,A[i+1]-K);
            M += A[i]-lo;
        }
        if (M<0) return "NO\n";
    }
    return "YES\n";
}
int main()
{
    int T;cin>>T;
    while(T--)
    {
        int N,M,K;cin>>N>>M>>K;
        for(int i=0;i<N;i++) cin>>A[i];
        cout << solve(N,M,K);
    }

    return 0;
}