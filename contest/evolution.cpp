#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;

vector<unordered_set<string>> cows;
unordered_map<string,int> sz;
vector<pair<int,string>> order;
bool visited[26];

bool dfs(vector<unordered_set<string>> &v, int ind = 0) {
    if (ind==sz.size()) return 1;

    vector<unordered_set<string>> a,b;

    for (int i=0;i<v.size();i++)
        if (v[i].find(order[ind].S) != v[i].end())
            a.push_back(v[i]);
        else
            b.push_back(v[i]);

    if (!a.empty() && visited[ind]) return 0;
    if (!a.empty()) visited[ind] = 1;

    return dfs(a,ind+1) && dfs(b,ind+1);
}
int main()
{
    ofstream fout("evolution.out");
    ifstream fin("evolution.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n; fin>>n;
    cows.resize(n);
    for (int i=0;i<n;i++) {
        int k; fin>>k;
        for (int j=0;j<k;j++) {
            string trait; fin>>trait;
            cows[i].insert(trait);
            sz[trait]++;
        }
    }

    for (auto &val: sz)
        order.emplace_back(val.S,val.F);

    sort(order.rbegin(),order.rend());

    fout << (dfs(cows) ? "yes" : "no") << '\n';

    return 0;
}