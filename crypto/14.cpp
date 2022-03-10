/*
FAILED :( Cannot find a way to have fast nth roots
 */

#include <bits/stdc++.h>
#include "BigInt.h"
#include "RSA.h"
using namespace std;
typedef long long ll;
#define sz(x) (x).size()

//Chinese Remainder Theorem
BigInt CRT(vector<BigInt> &N,vector<BigInt> &C) { //given A=c[i]%n[i] for all i, find A%n[0]*n[1]...
    //assume n[i] are pairwise relatively prime
    bool tester = 1;
    for (int i=0;i<sz(N);i++)
        for (int j=i+1;j<sz(N);j++)
            if (!(GCD(N[i],N[j]) == 1))
                tester = 0;

    assert(tester);

    BigInt pN = 1;
    for (int i=0;i<sz(N);i++)
        pN = pN*N[i];

    BigInt res = 0;
    BigInt b,B;
    for (int i=0;i<sz(N);i++) {
        b = pN/N[i];
        B = inv(b,N[i]);
        res = (res+C[i]*b*B)%pN;
    }
    return res;
}
//generate CRT for all permutations, print to the console
void all_CRT(vector<BigInt> &N,vector<BigInt> &C) {
    cout << endl;
    sort(C.begin(),C.end());
    do {
        cout << CRT(N,C) << ",\n";
    }
    while(next_permutation(C.begin(),C.end()));
}
int main()
{
    vector<BigInt> N(5),C(5); //enc moduluses, ciphertexts

    for (int i=0;i<5;i++) {
        string x;cin>>x;
        N[i] = x;
    }
    for (int i=0;i<5;i++) {
        string x;cin>>x;
        C[i] = x;
    }

    all_CRT(N,C);

    //get the nth root for each possible plaintext
    /*BigInt pos_pt;
    for (int i=0;i<120;i++) {
        string x;cin>>x;
        pos_pt = x;
        cout << num_to_ASCII(pos_pt) << '\n';
    }*/

    return 0;
}