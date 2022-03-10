
/*
ID: jamesli5
PROG: holstein
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

int V,G;
int v[26], g[16][26];
vector<int> feeds;

int test[26]; //helper array for works() method

void genFeeds(int ind) //make a vector of the feeds we want (given by i)
{
    feeds.clear();
    for (int i = 0; i < G; i++)
        if (pow(2,i) == (ind & -ind)) {
            ind -= (ind & -ind);
            feeds.push_back(i + 1);
        }

}
bool works(int ind) //does this feed config work?
{
    genFeeds(ind);
    for(int i=1;i<=V;i++) test[i] = 0;

    for (auto &next: feeds)
        for (int i = 1; i <= V; i++)
            test[i] += g[next][i];

    for (int i = 1; i <= V; i++)
        if (test[i] < v[i])
            return 0;
    return 1;
}
int main()
{
    ofstream fout("holstein.out");
    ifstream fin("holstein.in");

    fin >> V;
    for(int i=1;i<=V;i++)
        fin >> v[i];

    fin >> G;
    for(int i=1;i<=G;i++)
        for(int j=1;j<=V;j++)
            fin >> g[i][j];

    //when i is represented in binary, each '1' means that we use that feed, and each '0' means we don't
    int res = 100;
    for (int i = 1; i < pow(2,G); i++) //go through once to find min amount of feeds
        if (works(i))
            res = min(res,(int)feeds.size());

    int min_i = 1;
    for (min_i; min_i < pow(2,G); min_i++) //go through again to find the smallest feedtype
        if (works(min_i) && (int) feeds.size() == res)
            break;

    fout << res << ' ';
    for (int i = 0; i < (int) feeds.size()-1; i++)
        fout << feeds[i] << ' ';
    fout << feeds[feeds.size()-1] << "\n";
    return 0;
}