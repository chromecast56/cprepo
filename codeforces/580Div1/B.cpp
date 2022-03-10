#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5+5;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n;cin>>n;
    unordered_map<int,int> mp;
    long long res=0;
    for(int i=1;i<=n;i++) {
        int v;cin>>v;
        if (v>0)
            res+=abs(1-v),mp[1]++;
        else if (v<0)
            res+=abs(-1-v),mp[-1]++;
        else
            mp[0]++;
    }
    while(mp[0]) {
        if (mp[-1]%2) mp[-1]++,res++;
        else mp[1]++,res++;
        mp[0]--;
    }
    if (mp[-1]%2) res+=2;

    cout<<res<<'\n';

    return 0;
}