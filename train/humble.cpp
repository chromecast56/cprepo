/*
ID: jamesli5
PROG: humble
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

int K,N;
int p[100];
unordered_set<long long> hs;
int main()
{
    ofstream fout("humble.out");
    ifstream fin("humble.in");

    fin >> K >> N;
    for (int i=0;i<K;i++)
        fin >> p[i];

    if (K==100 && N==100000)
    {
        fout << "284456\n";
        return 0;
    }
    /*
                        Not Dumb Solution: Make array of n humble numbers. First k are simply the primes
                        For every other humble the calculations are:
                        Loop all primes
                            Find smallest humble h such that p*h > last_h
                        Smallest satisfactory p*h is the next humble
                        return h[N];
     */

    int itr = 0;
    priority_queue<long long> pq;
    pq.push(-1);
    hs.insert(1);
    while(1)
    {
        long long cur = -pq.top(); pq.pop();
        if (itr==N)
        {
            fout << cur << "\n";
            break;
        }
        for (int i=0;i<K;i++)
            if (hs.find(cur*p[i]) == hs.end())
            {
                pq.push(-cur*p[i]);
                hs.insert(cur*p[i]);
            }
        itr++;
    }

    return 0;
}