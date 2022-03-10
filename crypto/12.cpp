/*
INPUT FILE:
1730707308614781579409176171025304944530150817607168440633741646874885148067471194681114060400754914302716320445094334808 3
144798705314350429763923825533268017939591855543188741804885542310423901212486131899734529156989228773807281323282089247 5
882007613802242751058503540515956197924365912643425775762639149243479784589205273399379706877350409245257492458995863714 79
509028003450939337840433681886060660833256868959854431180339067676188671365732255048182195376396605906892691485212459972 659
1610591034980188659598655253050337531016638253782107382462470244010781232482208459464914631299513483672396853250648658995 6012554456489666823043
226258004168077036541581615148470444308859841240020049530913518837918944161358020743051947445490287766425970741510825119 15349
 */

#include <bits/stdc++.h>
#include"BigInt.h"
#include"RSA.h"
using namespace std;
typedef long long ll;

//convert the string to ASCII
string num_to_ASCII(BigInt x) {
    string str = x.toString();
    assert(str.size()%3==0);

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
bool verify(BigInt S,BigInt e,BigInt P,BigInt n) {
    return pow(S,e,n) == P;
}
int main() {
    BigInt e=3, n("2759756735601919831588269702432712903951563920497128742338802224564722530491167762014287556825447174576540773577497658789");

    BigInt S,P;
    vector<BigInt> sigs, fac;
    for (int i=0;i<6;i++) {
        string a,b; cin>>a>>b;
        S = BigInt(a), P = BigInt(b);
        sigs.push_back(S), fac.push_back(P);
        cout << verify(S,e,P,n) << '\n';
    }

    P = ASCII_to_num("the flowers");

    vector<int> a(6);
    //find the prime factorization of P

    for (int i=0;i<6;i++)
        while(P%fac[i]==0)
            P = P/fac[i], a[i]++;

    assert(P==1);
    BigInt forge = 1;
    for (int i=0;i<6;i++)
        forge = (forge*pow(sigs[i],a[i],n))%n;

    cout << forge << '\n';
    cout << verify(forge,e,ASCII_to_num("the flowers"),n);
}