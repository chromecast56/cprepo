/*
            Given a string N, find the index and length of the Largeset Palindromic Substring (LPS)
 */
#include<bits/stdc++.h>

using namespace std;
int L[500000]; //Longest palindromic substring for (0,i)
string manacher(string n)
{
    int N = 2*n.size()+1;
    int C=1, R=2; //center, right-bound
    L[0]=0; L[1]=1;

    int max_len=0,max_cen=0; //max length, center ind of it
    for (int i=2;i<N;i++) {
        int iMirror = 2*C-i;
        if (R-i) //if theres room to expand
            L[i] = min(R-i,L[iMirror]); //know that L[i] is at least its mirror (KEY OPTIMIZATION)

        /* While expansion is between 0 and N and (It is an even ind (is on a '#' char), or it is odd ind and chars on left/right match)
         */
            while((i+L[i]<N && i-L[i]>0) && (((i+L[i]+1)%2==0) || n[(i+L[i]+1)/2] == n[(i-L[i]-1)/2])) //expand as far as possible
            L[i]++;

        if (max_len<L[i]) {
            max_len=L[i];
            max_cen=i;
        }
        if (R < i+L[i]) { //if expansion passes right bound, update rb and center
            R = i+L[i];
            C = i;
        }
    }

    return n.substr((max_cen-max_len)/2, max_len);

}
int main()
{
    cout << "Enter string N:\n";
    string n;
    cin >> n;
    cout << manacher(n)<<'\n';

    return 0;
}