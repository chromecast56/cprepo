#include <bits/stdc++.h>
#include "BigInt.h"
#include "RSA.h"
using namespace std;
typedef long long ll;

string num_to_ASCII(BigInt x) {
    string str = x.toString();
    /*assert(str.size()%3==0);*/
    if (str.size()%3 != 0) return "INVALID";

    string res;
    for (int i=0;i<str.size();i+=3)
        res += (char) (100*(str[i]-'1') + 10*(str[i+1]-'0') + (str[i+2]-'0'));
    return res;
}
BigInt ASCII_to_num(string x) {
    BigInt res = 0;
    for (auto ch: x)
        res = res*1000 + (ch+100);
    return res;
}
int main()
{

    BigInt C("150598315159426420417362370315760759643687452249127260593893330249875774660837569082216166241764228321707042114");
    BigInt n("315562173921131111550753275258954314886929684614433857059068225329589007516900986203500713113234143069878550293");
    BigInt e("1835588100642725811278316299646156385857628660058608776628872255463681001129596115865795858135978837517124882698892069345209251312769967638417909171551219459094621692202465346003400944724101186482909006146466321559204641");

    for (int i=0;i<20;i++)
        cout << i << " iterations: " << num_to_ASCII(C) << '\n',
        C = pow(C,e,n);

    /*
            The text is decrypted after 9 iterations, with output:
            9 iterations: Elliptic Curve Cryptography
     */

    return 0;
}