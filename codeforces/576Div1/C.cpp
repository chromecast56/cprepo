#include <bits/stdc++.h>

using namespace std;

int n,m;
unordered_set<int> v;
vector<int> res;
bool vis(int a) {return v.find(a)!=v.end();}
void print(const string &out)
{
    cout << out << '\n';
    for(int i=0;i<n-1;i++) cout<<res[i]<<' ';
    cout<<res[n-1]<<'\n';
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    int t;cin>>t;
    while(t--)
    {
        v.clear();
        res.clear();
        bool impos=1;
        cin>>n>>m;
        for(int i=1;i<=m;i++) {
            int a,b;cin>>a>>b;

            if (!vis(a)&&!vis(b)) {
                v.insert(a),v.insert(b);
                res.push_back(i);

                if(impos && res.size()==n) {
                    impos=0;
                    print("Matching");
                }
            }
        }
        if (impos && res.size()<n) {
            res.clear();
            for(int i=1;i<=3*n;i++)
                if (!vis(i)) {
                    res.push_back(i);
                    if (res.size()==n) {
                        impos=0;
                        print("IndSet");
                        break;
                    }
                }
        }
        if (impos)
            cout<<"Impossible\n";
    }

    return 0;
}