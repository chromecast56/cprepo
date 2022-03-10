#include <bits/stdc++.h>

using namespace std;
const int MAX = 10000000;

struct cow
{
    int x,y;
    bool h;
    cow(int xx,int yy,bool hh) {
        x=xx;y=yy;h=hh;
    }
};
bool compX(cow const &a, cow const &b)
{
    return a.x==b.x?a.y<b.y:a.x<b.x;
}
bool compY(cow const &a, cow const &b)
{
    return a.y==b.y?a.x<b.x:a.y<b.y;
}
int N;
vector<cow> c;
int res1 = 0, res2 = MAX;
vector<cow> cY;
int main()
{
    ofstream fout("cowrect.out");
    ifstream fin("cowrect.in");

    ios_base::sync_with_stdio(false); //faster I/O
    fin.tie(NULL);

    fin >> N;
    for (int i=0;i<N;i++)
    {
        int a,b; char h;
        fin >> a >> b >> h;

        c.push_back(cow(a,b,h=='H'));
        cY.push_back(cow(a,b,h=='H'));
    }
    sort(c.begin(),c.end(),&compX);
    sort(cY.begin(),cY.end(),&compY);

    for (int h1=0;h1<N;h1++)
        for (int h2=h1;h2<N;h2++)
        {
            if (!cY[h1].h || !cY[h2].h) continue; //if y-endpoints are G

            int sz = 0;
            int mx = MAX,Mx=0,my=MAX,My=0;
            for (int i=0;i<N;i++) {

                int itr = i;
                while(c[i].x==c[itr].x)
                {
                    if (c[itr].y < cY[h1].y || c[itr].y > cY[h2].y) {
                        itr++;
                        continue;
                    }
                    if (!c[itr].h) {
                        sz=0,mx=MAX,Mx=0,my=MAX,My=0;
                        while(c[i].x==c[itr].x)
                            itr++;
                        break;
                    }

                    sz++;
                    mx = min(mx,c[itr].x), Mx = max(Mx,c[itr].x);
                    my = min(my,c[itr].y), My = max(My,c[itr].y);

                    itr++;
                }
                i = itr-1;

                if (res1 < sz || (res1 == sz && res2 > (Mx-mx)*(My-my)))
                    res1 = sz, res2 = (Mx-mx)*(My-my);
            }


    fout << res1 << "\n";
    fout << res2 << "\n";

    return 0;
}
