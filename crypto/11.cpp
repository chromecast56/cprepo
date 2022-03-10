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
void Task1() {
    cout<<"Task 1 \n---------------------------------------------------------\n";
    //generate random primes
    BigInt p("366966395674480720615723260825252737771782329080355420087267671361517671709705136475160633515516094929899199610183876061343963646764908869456511643949");
    BigInt q("312346331690750143450651289879654870631867052087443838859983691190992018850452001682616393677899280264175533825513055253347364706072513093326573936203");

    //compute n and phi
    BigInt n = p*q, phi = (p-1)*(q-1);

    //generate random e such that gcd(e,phi) = 1
    BigInt e("617687268716486858416481");
    assert(GCD(e,phi) == 1);

    //compute inverse of e in phi
    BigInt d = inv(e,phi);
    if (d.sign==-1) d = d+phi;

    //plaintext
    BigInt P = ASCII_to_num("I <3 cake");
    cout<<"Plaintext: " << P << '\n';

    //encrypt the plaintext
    P = pow(P,e,n);
    cout << "Ciphertext: " << P << '\n';

    //decrypt the plaintext
    P = pow(P,d,n);

    string x = num_to_ASCII(P);
    cout << "Original string: " << x << '\n';
}
void Task2() {
    cout<<"Task 2 \n---------------------------------------------------------\n";
    //generate random primes
    BigInt p("815783817496827872301832182631130851654181515148772876057725731869106841044536094080693460817931374396988531856043221962921539422816579446675272700449");
    BigInt q("880211272163542330663370697319941426249016250233996952404574294074821244979565167562467729729425001576696780863066711875320577822766076327235875341079");

    //compute n and phi
    BigInt n = p*q, phi = (p-1)*(q-1);

    //generate random e such that gcd(e,phi) = 1
    BigInt e("2871682476841684628413");
    assert(GCD(e,phi) == 1);

    //compute inverse of e in phi
    BigInt d = inv(e,phi);
    if (d.sign==-1) d = d+phi;

    //plaintext
    BigInt M = ASCII_to_num("I <3 food");
    cout << "Message: " << M << '\n';

    //sign the message
    BigInt SM = pow(M,d,n);
    cout << "Signed Message: " << SM << '\n';

    //verify signature
    SM = pow(SM,e,n);

    bool b = M==SM;
    cout << "Signature verified (true/false): " << b << '\n';
}
int main()
{
     /*Task1();
     Task2();*/
     cout <<ASCII_to_num("the flowers");

/*
OUTPUT:

Task 1
---------------------------------------------------------
Plaintext: 173132160151132199197207201
Ciphertext: 714471285111848338911976232513378502838518640812852356998431792117765369935922869933954349750363507846798247
258667570585236000871705998136191527652770899418460615179750164048615106590393601387867466822197288593302904564628790798
16072169590541695568541092814088632437156796754037173470904444055641752
Original string: I <3 cake
Task 2
---------------------------------------------------------
Message: 173132160151132202211211200
Signed Message: 13982550348297564024913265236853518608732025655817209798878461241319814637024401695175831585953675779835
687313808746458266225394799399334502407960817036225635569043525917148358393152215186322868844170919461334334701516796767
3256108681771771436849668365656371130893463443857805720327525123984725833257
Signature verified (true/false): 1

*/

    return 0;
}