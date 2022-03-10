#include <bits/stdc++.h>
#include"BigInt.h"
using namespace std;

BigInt pow(BigInt a, BigInt b, BigInt n) { //binary exponentiation
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
BigInt inv(BigInt a, BigInt n) {
    BigInt x,y;
    BigInt gcd = GCD(a,n,x,y);
    if (!(gcd == 1))
        return -1;
    return x;
}
pair<BigInt,BigInt> fermat(BigInt &N) { //returns a prime factor of N, given |p-q| is small
    BigInt k = sqrt(N);
    BigInt g = 0;
    BigInt x = 0, h = 0;
    while(1) {
        g=g+1;
        x = (k+g)*(k+g) - N;
        h = sqrt(x);
        if (h*h==x)
            return {k+g+h,k+g-h};
    }
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
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    BigInt N("3200909051105364201164693808053590029074088922158723491051061550"
              "60354982373745822760188140190156925797800414301292359333160317916449796387911"
              "3975835000986070024699519343049991253001543465847139349037243"
              "65610968721184751500313502813254545068947558283543302413045"
              "43510484932712882843267408729913128177370687561457233486167486584"
              "87242931184584005382638341");

    BigInt e("45938274932874982748938989492800101");
    BigInt E("164696529922507745352876453332548487012810673654"
              "61374082000954560590670403131701326596773093267"
              "336272541708241772786897929678696837032101026"
              "31692715251241388457103568881887427174337319839702"
              "934337074114069079964028787201219122008132"
              "800911350242389943062437915595376659222211331548822861"
              "710469042657218207369516502014847384607200570429591504554077212313");

    BigInt p,q; //prime factors
    tie(p,q) = fermat(N);
    BigInt phi = (p-1)*(q-1);

    BigInt d = inv(e,phi); //find decryption exponent
    if (d.sign==-1)
        d = d+phi;

    BigInt mes = pow(E,d,N);
    cout << "MESSAGE: " << ASCII(mes) << '\n';
    cout << "PRIVATE KEY: (" << N << ", " << d << ")\n";
    cout << "PHI: " << phi << '\n';
    cout << "PRIME FACTORS: " << p << ' ' << q << '\n';

    return 0;
}