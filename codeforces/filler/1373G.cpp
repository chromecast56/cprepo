/*
                            Summary: Each pawn has a minimum index tg to reach the special column, namely: tg = y + |k-x|
                            Say that the array "cnt" stores the number of pawn indexes per given row
                            Ex. cnt = {0,0,0,1,3,2}...
                            Every pawn can be placed at any column >= tg. So, we can form a naive solution as follows:
                                - Loop over the cnt array
                                - If cnt[i] is greater than 1, then move all the pawns to i+1 (as each square can only hold one pawn)
                                - Repeat this until we reach the last pawn group, whose value is x and index i
                                - Each pawn of the last group will fill subsequent arrays, and we use a = i+x-1 rows total
                                - So the answer is a-n, or 0 if a<n.
                                - For each update, either cnt[tg]++, or cnt[tg]--;
                                - Nice O(NM) solution

                            (To find the last pawn group you can naively search back from i=2n to i=n, no opt needed)

                            The fun optimization problem is to try to improve the update time complexity to logrithmic
                            Notice that when we "waterfall" the values, we leave only 0 or 1 afterwards
                            Call v = sum(i,inf) + i

                            I claim that v is a lower bound on the minimum rows needed, and the maximum of v_i is the
                            answer
                            How to prove this? We can use Halls Theorem!
                            Proof:
                                Idk??????

                            So, we store v_i in a segment tree. For updates, we do sum[0,i]++, --
                            For queries, we find the max [0,x] where x is the maximum tg.



                            Inspiration:


                            Bugs:
                                Stupid multiset.erase will erase all same values, have to use freq array overcome

 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;
typedef vector<pii> vpii;

template <class t>          //vector sort template
vector<t> sort(vector<t> &a) {return sort(a.begin(),a.end());}

int n,k,m;
set<pii> s; //store which pawns are on the board
set<int> smx; //store the max index
const int MAXN = 2000000;
const int N = 450000;

int t[MAXN];
int lazy[MAXN]; //amount to propogate to children
int cnt[500000];

void push(int v) {
    t[v*2] += lazy[v];
    t[v*2+1] += lazy[v];
    lazy[v*2] += lazy[v];
    lazy[v*2+1] += lazy[v];
    lazy[v] = 0;
}
void seg_sum(int l,int r,int sum,int tl=0,int tr=N-1, int v = 1) { //sum on [l..r)
    if (l > r) return;
    else if (l==tl && r==tr) { //be lazy and propogate later
        t[v] += sum;
        lazy[v] += sum;
    }
    else {          //otherwise have to search to children nodes
//        cerr << l << ' ' << r << ' ' << tl << ' ' << tr <<'\n';
        push(v);
        int tm = (tl+tr)>>1;
        seg_sum(l,min(r,tm),sum,tl,tm,v*2);
        seg_sum(max(l,tm+1),r,sum,tm+1,tr,v*2+1);
        t[v] = max(t[v*2],t[v*2+1]);
    }
}

int seg_max(int l,int r,int tl=0,int tr=N-1, int v = 1) {
    if (l>r) return -1000000000;
    else if (l <= tl && tr <= r) return t[v];
    else {  //go to children
//        cerr << l << ' ' << r << ' ' << tl << ' ' << tr <<'\n';
        push(v);
        int tm = (tl+tr)>>1;
        return max(seg_max(l,min(r,tm),tl,tm,v*2),seg_max(max(l,tm+1),r,tm+1,tr,v*2+1));
    }


}
int solve() {
    if (smx.empty()) return 0;
    return max(0,seg_max(0,*smx.rbegin()) - n);
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    cin>>n>>k>>m;
    k--;

    for (int i=0;i<2*n;i++)
        seg_sum(i,i, i);

    while(m--) {
        int x,y; cin>>x>>y;
        x--,y--;

        int tg = y + abs(k-x); //the fastest/lowest that the pawn can reach the column

        if (s.find({x,y}) == s.end()) { //cnt[tg]++
            s.insert({x,y});
            cnt[tg]++;
            if (cnt[tg]==1) smx.insert(tg);
            seg_sum(0,tg,1);
        }
        else {                          //cnt[tg]--
            s.erase({x,y});
            cnt[tg]--;
            if (cnt[tg]==0) smx.erase(tg);  //c++ multiset erase will erase all values, we dont want that!!
            seg_sum(0,tg,-1);
        }


        cout << solve() << '\n';
    }

    return 0;
}