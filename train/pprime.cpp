/*
ID: jamesli5
PROG: pprime
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

int a,b;
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
int main()
{
    ofstream fout("pprime.out");
    ifstream fin("pprime.in");

    fin >> a >> b;

    vector<int> res;
    string str, str_rev;
    for (int dig = 1; dig <= 5; dig++)
    {

        for (int i = pow(10,dig-1); i < pow(10,dig); i++) //10 to 99   -->    1001 to 9999
        {

            str = to_string(i);
            str_rev = to_string(i); reverse(str_rev.begin(), str_rev.end());

            if (dig != 5 && isPrime(stoi(str + str_rev)))
                res.push_back(stol(str + str_rev));

            if (isPrime(stol(str + str_rev.substr(1,str.size()-1))))
                res.push_back(stol(str + str_rev.substr(1,str.size()-1)));
        }
    }
    sort(res.begin(),res.end());
    for (auto &next: res)
        if (a <= next && next <= b)
            fout << next << "\n";

    return 0;
}