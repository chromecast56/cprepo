#include <bits/stdc++.h>
#include"BigInteger.h" //Big Integer code: https://github.com/williamchanrico/biginteger-cpp
using namespace std;
typedef long long ll;
BigInt n;
BigInt p(BigInt a, BigInt b) { //binary exponentiation
    BigInt res = 1;
    while (b >= 1) {
        if (b % 2 == 1)
            res = (res*a)%n;
        a = (a*a)%n;
        b = b/2;
    }
    return res;
}
//source: assignment 6 - extended gcd
BigInt GCD(BigInt a, BigInt b, BigInt& x, BigInt& y) {
    x = 1, y = (BigInt) 0;
    BigInt x1 = 0, y1 = 1, a1 = a, b1 = b;
    BigInt q;
    while (b1>=1) {
        q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}
//modular inverse
BigInt inv(BigInt a) {
    BigInt x,y;
    BigInt gcd = GCD(a,n,x,y);
    if (!(gcd == 1))
        return -1;
    return x;
}
//convert the string to ASCII
string ASCII(BigInt x) {
    string str = x.toString();
    assert(str.size()%3==0);

    string res;
    for (int i=0;i<str.size();i+=3)
        res += (char) (100*(str[i]-'1') + 10*(str[i+1]-'0') + (str[i+2]-'0'));
    return res;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    //problem 1:
    n = "29905476219696696488459695569542874982899982395591783167345616213742428520932978964701105762419";

    BigInt a,b;
    a = "18470867236652042114674202412672361508286922624798954047462848141594604481105199772044318568085";
    b = "29101241661082444091235600206473561533438079973101886056474137926863097442817516466883649517741";
    BigInt ans = p(a,b);

    cout << ans.toString() << '\n';
    cout << ASCII(ans) << '\n';

    //problem 2
    BigInt eA,eC,encrA,encrC;
    n = "29905476219696696488459695569542874982899982395591783167345616213742428520932978964701105762419";
    eA = "257982598332521";
    eC = "8357598759827897559827";
    encrA = "25742211972573775074584023844806862826724677794637841736155082773353826650560036988594385927380";
    encrC = "11021170567433275103287488918357139494535033415363428500376802294402114235404106032323041033864";
    BigInt gcd,x,y;
    gcd = GCD(eA,eC,x,y); //gcd is 1
    cout << gcd.toString() << '\n';

    //make encrA and encrC their respective inverses, if x or y is negative)
    if (x.sign == -1)
        encrA = inv(encrA), x.sign = 1;
    if (y.sign == -1)
        encrC = inv(encrC), y.sign = 1;

    ans = (p(encrA,x)*p(encrC,y))%n;

    cout << ans.toString() << '\n';
    cout << ASCII(ans) << '\n';

    return 0;
}