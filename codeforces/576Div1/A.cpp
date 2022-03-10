/*
                Note: optimization could be made, as you know the cap of distinct numbers K is constant.
                Just precompute K, and loop over the window of unique A, no psum needed
 */
#include <bits/stdc++.h>

using namespace std;
const int maxn = 4e5+5;

int n,I;
int p[maxn];
vector<int> a;
unordered_map<int,int> mp;
int w(int K) {return ceil(log2(K))*n;}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();

    cin>>n>>I; I*=8;
    a.resize(n+1); a.push_back(-1);
    for(int i=0;i<n;i++) {
        cin>>a[i];
//        if (!mp[a[i]]) K++;

        mp[a[i]]++;
    }

    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());

    for(int i=1;i<a.size();i++) p[i] = p[i-1]+mp[a[i]];

    int j=1, res=0;
    for(int i=1;i<a.size();i++) {
        while(j<a.size() && w(j-i+1)<=I)
            j++;
        j--;

        res = max(res,p[j]-p[i-1]);
    }
    cout<<n-res<<'\n';
    return 0;
}