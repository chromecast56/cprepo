#ifndef PROJECTS_RSA_H
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
BigInt pow(BigInt a, BigInt b) { //binary exponentiation
    BigInt res = 1;
    while (b >= 1) {
        if (b % 2 == 1)
            res = res*a;
        a = a*a;
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
BigInt GCD(BigInt a,BigInt b) {BigInt x=0,y=0;return GCD(a,b,x,y);}
//modular inverse
BigInt inv(BigInt a, BigInt n) {
    BigInt x,y;
    BigInt gcd = GCD(a,n,x,y);
    if (!(gcd == 1))
        return -1;
    if (x.sign==-1)
        x = x+n;
    return x;
}
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
#define PROJECTS_RSA_H

#endif //PROJECTS_RSA_H
