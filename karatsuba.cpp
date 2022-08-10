#include <bits/stdc++.h>

using namespace std;

string substract(string& a, int A, string& b, int B){ // it's guaranteed that a >= b
	string bComplement(A, '9'); // it will be b's complement base 10 after 2 cycles
	for(int i = 0; i < B; i++) bComplement[A - 1 - i] -= b[B - 1 - i] - '0'; // we have b's complement base 9 yet
	for(int i = A - 1; i >= 0; i--){ // we are adding 1 to bComplement
		if(bComplement[i] == '9') bComplement[i] = '0';
		else {bComplement[i]++; break;}
	} // we have b's complement base 10
	int carry = 0, cur; // will save sum a + bComplement - 10^A in bComplement
	for(int i = A - 1; i >= 0; i--){
		cur = a[i] - '0' + bComplement[i] - '0' + carry;
		bComplement[i] = '0' + (cur % 10);
		carry = cur >= 10;
	}
	int idx = 0;
	for(; idx < A - 1 && bComplement[idx] == '0'; idx++);
	return bComplement.substr(idx);
}

string add(string& a, int A, string& b, int B){ 
	if(A < B) return add(b, B, a, A);
	string res(A, '0');
	int carry = 0, dig1, dig2;
	for(int i = 0; i < A; i++){
		dig1 = a[A - 1 - i] - '0', dig2 = B - 1 - i >= 0 ? b[B - 1 - i] - '0' : 0;
		dig1 += dig2 + carry;
		res[A - i - 1] = '0' + (dig1 % 10);
		carry = dig1 >= 10;
	}
	return carry ? "1" + res : res;
}

string basicMultiplication(string& a, int A, string& b){ // school algo, but b.size() is 1 so it's O(A)
	string res(A, '0');
	int carry = 0, dig1, dig2 = b[0] - '0';
	for(int i = A - 1; i >= 0; i--){
		dig1 = a[i] - '0';
		dig1 = dig1 * dig2 + carry;
		res[i] = '0' + dig1 % 10;
		carry = dig1 / 10;
	}
	return carry ? to_string(carry) + res : res;
}

void addZeroes(string& s, int n){
	if(s[0] == '0') return;
	for(; n; n--) s += '0';
}

string karatsuba(string& s1, int n, string& s2, int m){
	if(m == 1) return basicMultiplication(s1, n, s2); // *
	int mid = (m >> 1); // divide
	string a = s1.substr(0, n - mid), b = s1.substr(n - mid); // divide
	string c = s2.substr(0, m - mid), d = s2.substr(m - mid); // divide
	string ac = karatsuba(a, n - mid, c, m - mid); // rec
	string bd = karatsuba(b, mid, d, mid); // rec
	string aPLUSb = add(a, n - mid, b, mid); //+
	string cPLUSd = add(c, m - mid, d, mid); //+
	string acPLUSbd = add(ac, ac.size(), bd, bd.size()); //+
	string trick = karatsuba(aPLUSb, aPLUSb.size(), cPLUSd, cPLUSd.size()); // rec
	string adPLUSbc = substract(trick, trick.size(), acPLUSbd, acPLUSbd.size()); //-
	addZeroes(ac, (mid << 1)); // O(m)
	addZeroes(adPLUSbc, mid); // O(m / 2)
	string res = add(ac, ac.size(), adPLUSbc, adPLUSbc.size()); //+
	res = add(res, res.size(), bd, bd.size()); //+
	return res;
}

string karatsubaMultiplication(string& s1, int n, string& s2, int m){
	if(m == 1 && s2[0] == '0') return "0";
	return n >= m ? karatsuba(s1, n, s2, m) : karatsuba(s2, m, s1, n);
}

int main() {
    return 0;
}
