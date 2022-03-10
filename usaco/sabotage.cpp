#include <bits/stdc++.h>

using namespace std;

int N;
int A[100001];

long long sum = 0;
int r3(double a)
{
    return (int) 1000*a+.5;
}
bool check(double b)
{
    double best,cur;
    best = cur = A[1] - b;

    for (int i=2;i<N-1;i++)
    {
        if (cur < 0) cur = 0;
        cur += A[i] - b;

        if (best < cur)
            best = cur;
    }
    return (sum - N*b) - best <= 0;
}
int main()
{
    ofstream fout("sabotage.out");
    ifstream fin("sabotage.in");

    ios_base::sync_with_stdio(false); //faster I/O
    fin.tie(NULL); //include only for non-interactive problems

    fin >> N;
    for (int i=0;i<N;i++) {
        fin >> A[i];
        sum += A[i];
    }

    double lo = 0, hi = 100000*10000;
    while(r3(lo) != r3(hi))
    {
        double mid = (lo+hi)/2;
        if (check(mid))
            hi = mid;
        else
            lo = mid;
    }
    fout << fixed << setprecision(3) << lo << '\n';

    return 0;
}