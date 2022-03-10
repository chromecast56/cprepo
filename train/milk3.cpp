/*
ID: jamesli5
PROG: milk3
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;
int A,B,C;

struct State
{
    int a,b,c;
    int hash()
    {
        return 400*a+20*b+c;
    }
};
vector<State> vect;
void genTransitions(State a)
{
    vect.clear(); State next;

    next = {a.a-min(a.a,B-a.b),a.b+min(a.a,B-a.b),a.c}; vect.push_back(next);
    next = {a.a-min(a.a,C-a.c),a.b,a.c+min(a.a,C-a.c)}; vect.push_back(next);

    next = {a.a+min(a.b,A-a.a),a.b-min(a.b,A-a.a),a.c}; vect.push_back(next);
    next = {a.a,a.b-min(a.b,C-a.c),a.c+min(a.b,C-a.c)}; vect.push_back(next);

    next = {a.a+min(a.c,A-a.a),a.b,a.c-min(a.c,A-a.a)}; vect.push_back(next);
    next = {a.a,a.b+min(a.c,B-a.b),a.c-min(a.c,B-a.b)}; vect.push_back(next);

}
int main()
{
    ofstream fout("milk3.out");
    ifstream fin("milk3.in");

    fin >> A >> B >> C;

    list<State> q;
    bool v[10000];

    State t = {0,0,C};
    q.push_back(t);

   bool res[21];
    while(!q.empty())
    {
        State cur = q.front(); q.pop_front();

        if (!v[cur.hash()])
        {
            v[cur.hash()] = 1;
            if (cur.a == 0)
                res[cur.c] = 1;

            genTransitions(cur);
            for (auto &next: vect)
                q.push_back(next);
        }
    }
    int last;
    for (int i = 20; i >= 0; i--)
        if (res[i]) {last = i; break;}
    for (int i = 0; i <= 20; i++) {
        if (i==last) fout << i << "\n";
        else if (res[i]) fout << i << ' ';
    }

    return 0;
}

