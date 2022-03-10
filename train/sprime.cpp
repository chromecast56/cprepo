/*
ID: jamesli5
PROG: sprime
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

int len;
vector<long> res;
int dig1[] = {2,3,5,7};
int dig[] = {1,3,5,7,9};

bool isPrime(long n) //AKS primality test, O(sqrt(n)) w/ optimizations
{
    // Corner cases
    if (n <= 1)  return false;
    if (n <= 3)  return true;

    //easy cases, takes up 2/3 of all numbers
    if (n%2 == 0 || n%3 == 0) return false;

    for (int i=5; i*i<=n; i=i+6) //check only factors that are 1mod6 or 5mod6, others are for sure not good
        if (n%i == 0 || n%(i+2) == 0)
            return false;

    return true;
}
bool isSuperPrime(long n)
{
    while(n > 0)
    {
        if (!isPrime(n))
            return 0;
        n /= 10;
    }
    return 1;
}
void genNums(long n, int digit)
{
    if (digit == len)
    {
        if (isSuperPrime(n))
            res.push_back(n);
        return;
    }
    n *= 10;
    for (auto &next: dig)
        genNums(n+next,digit+1);
}
int main()
{
    ofstream fout("sprime.out");
    ifstream fin("sprime.in");

    fin >> len;

    for(auto &next: dig1)
        genNums(next,1);

    sort(res.begin(),res.end());
    for(auto &next: res)
        fout << next << "\n";
    return 0;
}
