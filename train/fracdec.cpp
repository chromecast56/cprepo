/*
ID: jamesli5
PROG: fracdec
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

string convert(int num, int den)
{
    // If the numerator is zero, answer is 0
    if (num == 0)
        return "0";

    int init = num / den;

    string res = to_string(init);

    // If completely divisible, return answer.
    if (num % den == 0)
        return res + ".0";

    res += ".";
    int rem = num % den;
    map<int, int> mp;

    int ind;
    bool repeating = false;
    while (rem > 0 && !repeating) {
        if (mp.find(rem) != mp.end()) {

            // Index to insert parentheses
            ind = mp[rem];
            repeating = true;
            break;
        }
        else
            mp[rem] = res.size();

        rem *= 10;

        int temp = rem / den;
        res += to_string(temp);
        rem = rem % den;
    }
    if (repeating) {
        res += ")";
        res.insert(ind, "(");
    }
    return res;
}
int main()
{
    ofstream fout("fracdec.out");
    ifstream fin("fracdec.in");

    int n,d;
    fin >> n >> d;
    string res = convert(n,d);
    for (int i=76;i<(int)res.size();i+=77)
        res.insert(i,"\n");

    fout << res << "\n";
    return 0;
}