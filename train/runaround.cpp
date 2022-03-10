/*
ID: jamesli5
PROG: runround
LANG: C++11
*/
#include <bits/stdc++.h>


/*
Side note: the intended solution was to generate all n! permutations and taking the smallest one that's above the input
 Theoretically this solution should have TLEd, but this was the hardest case:

    ------- test 7 [length 8 bytes] ----
    9000000
Test 7: TEST OK [0.018 secs, 1328 KB]

    Quite dissapointing honestly, there was only 7 digits when there could have been 9.
    However the time allotted is 2 sec per case - 2/0.018 ~ 111.11, which means that this could
    have barely passed, given enough luck

 */
using namespace std;

int v[10];
bool isUnique(long num)
{
    for (int i = 0; i< 10; i++)
        v[i] = 0;
    while(num > 0)
    {
        if (num%10==0 || v[num%10])
            return 0;
        v[num%10] = 1;
        num /= 10;
    }
    return 1;
}
bool isRun(long num)
{
    for (int i = 0; i < 10; i++)
        v[i]= 0;

    string a = to_string(num);
    int i = 0;
    while (v[i] != 2)
    {
        v[i]++;
        i = (i+a.at(i)-'0') % a.size();
    }
    if (v[0] < 2)
        return 0;
    for (int i = 0; i < a.size(); i++)
        if (!v[i])
            return 0;
    return 1;
}
int main()
{
    ofstream fout("runround.out");
    ifstream fin("runround.in");

    int n;
    fin >> n;

    long i = n+1;
    for (i; i < INT_MAX; i++)
    {
        if (isUnique(i) &&
        isRun(i))
            break;
    }

    fout << i << "\n";

    return 0;
}