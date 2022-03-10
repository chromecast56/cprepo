#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
typedef vector<int> vi;

pii barn, lake, rock;
int main()
{
    ofstream fout("buckets.out");
    ifstream fin("buckets.in");
    ios_base::sync_with_stdio(false);
    cin.tie();
    for (int i=0;i<10;i++) {
        string x; fin>>x;
        for (int j=0;j<10;j++)
            if (x[j]=='B') barn = {i,j};
            else if (x[j]=='L') lake = {i,j};
            else if (x[j]=='R') rock = {i,j};
    }
    int res = abs(barn.F-lake.F)+abs(barn.S-lake.S);

    bool f = (barn.F==rock.F&&rock.F==lake.F);
    bool s = (barn.S==rock.S&&rock.S==lake.S);

    if ((((barn.F<rock.F&&rock.F<lake.F)||(barn.F>rock.F&&rock.F>lake.F))&&s)||(f&&((barn.S<rock.S&&rock.S<lake.S)||(barn.S>rock.S&&rock.S>lake.S))))
        fout << res+1 << '\n';
    else
        fout << res-1 << '\n';

    return 0;
}