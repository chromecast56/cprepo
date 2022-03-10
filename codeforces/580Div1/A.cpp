#include <bits/stdc++.h>

using namespace std;

bool v[401];
int a[200],b[200];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n,m;cin>>n;
    for(int i=0;i<n;i++)cin>>a[i];
    cin>>m;
    for(int i=0;i<m;i++)cin>>b[i];

    bool sol=0;
    for(int i=0;i<n;i++) v[a[i]]=1;
    for(int i=0;i<m;i++) v[b[i]]=1;

    for(int i=0;i<n && !sol;i++)
        for(int j=0;j<m && !sol;j++)
            if(!v[a[i]+b[j]]) {
                sol=1;
                cout << a[i] << ' ' << b[j];
            }
    return 0;
}