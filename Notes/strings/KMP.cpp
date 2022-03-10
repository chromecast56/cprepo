/*
        Given a string N, and a pattern string M, our goal is to find every occurence of M in N
 */
#include<bits/stdc++.h>

using namespace std;

//lps auxiliary array defined as: lps[j] is the largest len such that:
// Prefix m.substr(0,len) is equal to suffix m.substr(M-len,M), and len != j (not the entire substr)
vector<int> computeLPS(string m) {
    int M = m.size();
    vector<int> lps(M);
    int i=1,len=0;
    while(i < M) {
        if (m[i] == m[len]) //natch prefix and suffix
            lps[i] = ++len, i++;
        else { //no match
            if (len) //shift len over
                len = lps[len-1];
            else
                lps[i] = 0, i++;
        }
    }
    return lps;
}
void KMP(string n,string m) //given a string n, find all occurrences of m
{
    vector<int> lps = computeLPS(m);
    int N = n.size();
    int M = m.size();

    int i=0,j=0; //i: ind for N   j: ind for M
    while(i<N) {
        if (n[i] == m[j])
            i++, j++;

        if (j == M) {
            cout << "Found pattern at index " << (i-j) << '\n';
            j = lps[j-1]; //know that lps[j-1] chars will already match
        }
        else if (i<N && n[i] != m[j]) { //mismatch after j matches
            if (j)
                j = lps[j-1]; //know lps[j-1] will match
            else
                i++;
        }
    }
}
int main()
{
    cout << "Enter strings N and M:\n";
    string n,m;
    cin >> n >> m;
    KMP(n,m);
    return 0;
}