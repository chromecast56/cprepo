#include<bits/stdc++.h>

using namespace std;
const int MAXN = 100000;

int N, q[MAXN]; //store prev best
long long L,A[MAXN], dp[MAXN];
double slope(int j,int k)
{return ((double)A[k]*A[k]-A[j]*A[j]+2*L*A[k]-2*L*A[j]+dp[k]-dp[j])/(2.0*A[k]-2.0*A[j]);}
long long solve()
{
    int i,j;
    int h=0,t=0;
    for(i=1;i<=N;i++)
    {
//		cout << "i:" <<i<<'\n';
        while(h<t && slope(q[h],q[h+1])<A[i])
            h++;
        j = q[h];
        dp[i] = dp[j] + (A[i]-A[j]-L)*(A[i]-A[j]-L);
        while(h<t && slope(q[t-1],q[t])>slope(q[t],i))
            t--;
        q[++t]=i;
//		cout <<j<<' '<<h<<' '<<t<<'\n';
//		cout << dp[i] << '\n';
    }
    return dp[N];
}
int main()
{
    cin >> N >> L;
    L++;
    for (int i=1;i<=N;i++) cin >> A[i];
    for (int i=1;i<=N;i++) A[i] += A[i-1]; //psum
    for (int i=1;i<=N;i++) A[i] += i; //S[i] --> S[i] + i
    cout << solve() <<'\n';
    return 0;
}