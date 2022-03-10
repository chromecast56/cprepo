/*
ID: jamesli5
PROG: lamps
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;
/*
            Basically the official solution, I didn't reason far enough to realize that I could just represent
            the string w/ just the first 6 lights, which made coding this a bit harder
            (could've used bit manipulation instead)
 */


int test[100];
int N,C;
vector<int> on,off;
struct lamps
{
    vector<int> a;
};
bool comp(lamps a,lamps b)
{
    for (int i = 0; i < N; i++)
        if (a.a[i]==0 && b.a[i]==1)
            return 1;
        else if (a.a[i]==1 && b.a[i]==0)
            return 0;

    return 1;
}
bool simu(int a,int b,int c,int d)
{
    for (int i = 0; i < N; i++)
    {
        switch(i%6)
        {
            case 0: test[i] = 1-((a+b+d)%2); break;
            case 1: test[i] = 1-((a+c)%2); break;
            case 2: test[i] = 1-((a+b)%2); break;
            case 3: test[i] = 1-((a+c+d)%2); break;
            case 4: test[i] = 1-((a+b)%2); break;
            case 5: test[i] = 1-((a+c)%2); break;
        }
    }
    for (auto &i: on)
        if (!test[i-1])
            return 0;
    for (auto &i: off)
        if (test[i-1])
            return 0;
    return 1;
}
int main()
{
    ofstream fout("lamps.out");
    ifstream fin("lamps.in");

    fin >> N >> C;

    vector<lamps> res;

    int val;
    fin >> val;
    while(val != -1)
    {
        on.push_back(val);
        fin >> val;
    }
    fin >> val;
    while(val != -1)
    {
        off.push_back(val);
        fin >> val;
    }

    for (int a=0;a<2;a++) //all switch
        for (int b=0;b<2;b++) //odd switch
            for (int c=0;c<2;c++) //even switch
                for (int d=0;d<2;d++) //1mod3 switch
                    if ((a+b+c+d) <= C && (a+b+c+d)%2 == C%2) //need to make sure we switch the right amount
                        if (simu(a,b,c,d))
                        {
                            vector<int> e;
                            lamps a = {e};
                            for (int i = 0; i < N; i++)
                                a.a.push_back(test[i]);
                            res.push_back(a);
                        }
    sort(res.begin(),res.end(),comp);
    for (auto &next: res)
    {
        for (int i = 0; i < N; i++)
            fout << next.a[i];
        fout << "\n";
    }
    if (res.size()==0)
        fout << "IMPOSSIBLE\n";

    return 0;
}