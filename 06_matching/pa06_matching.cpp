#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
string P, T;

int RK() {
	int n = T.length();
	int m = P.length();
	set<char> alphabet;
	for (int i = 0; i < n; i++)
		alphabet.insert(T[i]);
	for (int i = 0; i < m; i++)
		alphabet.insert(P[i]);

	int d = alphabet.size();
	int q = 65536;
	int p = 0;
	int b[1000] = { 0, };
	for (int i = 0; i < m; i++) {
		p = (d * p + P[i]) % q;
		b[0] = (d * b[0] + T[i]) % q;
	}
	int h = 1;
	for (int i = 1; i < m; i++)
		h = (h * d) % q;
	int count = 0;
	for (int i = 0; i < n - m + 1; i++) {
		count++;
		if (i != 0) {
			b[i] = (d * (b[i - 1] - h * T[i - 1]) + T[i + m - 1]) % q;
			if (b[i] < 0)
				b[i] += q;
		}
			
		if (p == b[i]) {
			int error = 0;
			for (int j = 0; j < m; j++) {
				count++;
				if (P[j] != T[i + j]) error++;
			}
			if (error == 0) {
				return count;
			}
		}
	}
	return count;
}

void preprocessing(int *sp) {
	int m = P.length();
	sp[0] = -1;
	int k = -1;
	for (int j = 1; j < m; j++) {
		while (k >= 0 && P[j] != P[k + 1]) k = sp[k];
		if (P[j] == P[k + 1]) k++;
		sp[j] = k;
	}
}


int KMP() {
	int n = T.length();
	int m = P.length();
	int sp[1000] = { 0, };
	preprocessing(sp);
	int j = -1;
	int count = 0;
	for (int i = 0; i < n; i++) {
		count++;
		while (j >= 0 && T[i] != P[j + 1]) {
			j = sp[j];
			count++;
		}
		if (P[j + 1] == T[i]) j++;
		if (j == m - 1) {
			return count;
		}
	}
	return count;
}

void computeSkip(map<char, int> &jump) {
	int m = P.length();
	for (int i = 0; i < m; i++) {
		jump[P[i]] = i;
	}
}


int BM() {
	int n = T.length();
	int m = P.length();
	map<char, int> jump;
	computeSkip(jump);
	int i = 0;
	int count = 0;
	while (i < n - m ) {
		count++;
		int j = m - 1;
		int k = i + m - 1;
		while (j > 0 && P[j] == T[k]) {
			count++;
			j--; k--;
		}
		if (j == 0) {
			return count;
		}
		i += max(1, j - jump[T[i + j]]);
			
	}
	return count;
}


int main() {
	int n;
	string s;
	cin >> n;
	for (; n--;) {
		cin >> s;
		P += s;
	}
	cin >> n;
	for (; n--;) {
		cin >> s;
		T += s;
	}
	
	vector<pair<int, int>> v;
	v.push_back({ RK(), 1 });
	v.push_back({ KMP(), 2 });
	v.push_back({ BM(), 3 });
	sort(v.begin(), v.end());

	if (v[0].first == v[1].first && v[1].first == v[2].first)
		cout << "0 0 0\n";
	else if (v[0].first == v[1].first)
		cout << "0 0 " << v[2].second << '\n';
	else if (v[1].first == v[2].first)
		cout << v[0].second << " 0 0" << '\n';
	else if (v[0].first == v[2].first)
		cout << "0 " << v[1].second << " 0" << '\n';
	else
		cout << v[0].second << ' ' << v[1].second << ' ' << v[2].second << '\n';

	return 0;
}