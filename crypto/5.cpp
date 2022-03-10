#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
typedef vector<pii> vpii; typedef vector<pll> vpll;
#define F first
#define S second
#define sz(x) (int) (x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define pb push_back
const int MOD = 1e9+7; //998244353
const int MX = 2e5+100;
const ll INF = 1e18;


char cry(char &c,int shift) {
    int index = (c-'a'+shift)%26;
    index = (index+26)%26; //-?

    return index + 'a';
}
/*
Shift every letter in string a clockwise according to the shift value - negative shift values are counterclockwise
 returns the string in uppercase
 */
string crypt(string a,int shift) {
    transform(a.begin(), a.end(), a.begin(), ::tolower);
    string res;
    for (auto letter: a)
        if (letter == ' ') //whitespace
            res += letter;
        else
            res += cry(letter,shift);

    transform(res.begin(),res.end(),res.begin(), ::toupper);

    return res;
}
string crypt1c(string a) {
    string res;
    transform(a.begin(), a.end(), a.begin(), ::tolower);

    for (int i=0;i<sz(a);i++)
        res += cry(a[i],-i-1);

    transform(res.begin(),res.end(),res.begin(), ::toupper);
    return res;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cout<<"Problem 1:\n";
    cout<<"a) " << crypt("A page of history is equal to a volume of logic",11) << endl;
    cout<<"b) " << crypt("AOLYLHYLUVZLJYLAZILAALYAOHUAOLZLJYLALZAOHALCLYFIVKFNBLZZLZ",-7) << endl;
    cout<<"c) " << crypt1c("XJHRFTNZHMZGAHIUETXZJNBWNUTRHEPOMDNBJMAUGORFAOIZOCC") << endl;

    cout<<endl;

    //try all 26 possibilities
    cout << "Problem 2:\n";
    for (int i=0;i<26;i++)
        cerr << crypt("LWKLQNWKDWLVKDOOQHYHUVHHDELOOERDUGORYHOBDVDWUHH",i) << endl;
    cout << "a) " << crypt("LWKLQNWKDWLVKDOOQHYHUVHHDELOOERDUGORYHOBDVDWUHH",23) << endl;

    for (int i=0;i<26;i++)
        cerr << crypt("UXENRBWXCUXENFQRLQJUCNABFQNWRCJUCNAJCRXWORWMB",i) << endl;
    cout << "b) " << crypt("UXENRBWXCUXENFQRLQJUCNABFQNWRCJUCNAJCRXWORWMB",17) << endl;

    for (int i=0;i<26;i++)
        cerr << crypt("BGUTBMBGZTFHNLXMKTIPBMAVAXXLXTEPTRLEXTOXKHHFYHKMAXFHNLX",i) << endl;
    cout << "c) " << crypt("BGUTBMBGZTFHNLXMKTIPBMAVAXXLXTEPTRLEXTOXKHHFYHKMAXFHNLX",7) << endl;



    return 0;
}