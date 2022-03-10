#include <bits/stdc++.h>

using namespace std;

bool v[10];
int main()
{
    int N;cin>>N;
    string x; cin>>x;
    for(int i=0;i<x.size();i++)
    {
        if (x[i]=='L') {
            int itr=0;
            while(v[itr])itr++;
            v[itr]=1;
        }
        else if (x[i]=='R') {
            int itr=9;
            while(v[itr])itr--;
            v[itr]=1;
        }
        else {
            v[x[i]-'0'] = 0;
        }
    }
    for(int i=0;i<10;i++)cout<<v[i];
    cout<<'\n';

    return 0;
}