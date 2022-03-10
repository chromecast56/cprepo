/*
            ALTERNATIVE: Aho Corasick Algorithm
            (KMP Generalization, linear O(S+n+len_of_occur)
 */

#include <bits/stdc++.h>

using namespace std;

const unsigned long long MOD = 1000000007LL;
int main()
{
    ofstream fout("censor.out");
    ifstream fin("censor.in");

    string S;
    int n;
    fin >> S >> n;

    map<int, unordered_set<unsigned long long>,greater<unsigned long long>> hm; //sort map keys in reverse, want to try biggest words first

    while(n--)
    {
        string a;
        fin >> a;
        long long h=0;
        for(int i=0;i<(int)a.size();i++)
            h=(h*31+a[i]-'a')%MOD;
        hm[a.size()].insert(h);
    }
    string R = ""; //result
    vector<unsigned long long> rhash(1,0),expo(1,1);
    for(int i=0;i<(int)S.size();i++)
    {
        R += S[i];
        rhash.push_back((1ll*rhash.back()*31+S[i]-'a')%MOD);
        expo.push_back((1ll*expo.back()*31)%MOD);

        for (auto &a: hm)
        {
            int len = a.first;
            if (len > (int)R.size()) continue;

            unsigned long long subh = (1ll*rhash[R.size()-len]*expo[len])%MOD;
            unsigned long long hsh = (1ll*rhash.back()-subh +MOD)%MOD;
            if (a.second.find(hsh) != a.second.end())
            {
                R.resize(R.size()-len);                 //NOTE: Resize at end of vector is O(1)!
                rhash.resize(rhash.size()-len);
                expo.resize(expo.size()-len);
                break;
            }
        }
    }
    fout << R << "\n";
    return 0;
}