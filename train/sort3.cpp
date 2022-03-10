/*
ID: jamesli5
PROG: sort3
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;
//int num[4];
int dif[4][4];

int main()
{
//    ofstream fout("sort3.out");
//    ifstream fin("sort3.in");

    int n;

    cin >> n;

    int a[n];
    int num[4];
    for(int i=0;i<n;i++)
    {
        cin >> a[i];
        num[a[i]]++;
    }

    for (int i=0;i<n;i++)
    {
        if (i < num[1] && a[i] != 1) dif[1][a[i]]++;
        else if (i < num[1]+num[2] && a[i] != 2) dif[2][a[i]]++;
        else if (a[i] != 3) dif[3][a[i]]++;
    }
    int res = 0;
    for (int i = 1; i <= 3; i++) //sum the doubles
        for (int j = i+1; j <= 3; j++)
        {
                int m = min(dif[i][j],dif[j][i]);
                res += m;
                dif[i][j] -= m;
                dif[j][i] -= m;
            }

    res += 2*(dif[1][2] + dif[1][3]); //one of these will be 0, other will have the number of triples

    cout << res << "\n";
    return 0;
}