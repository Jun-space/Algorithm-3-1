#include <iostream>
#include <string>
#include <vector>
using namespace std;


void solution(string s);
int kMer(string s, int k);


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	for (; N--;) {
		string s;
		cin >> s;
		solution(s);
	}
	return 0;
}


void solution(string s) {
	int length = s.length();
	int best = 1000;
	for (int i = 1; i <= length/2; i++) {
		int value = kMer(s, i);
		if (best > value) best = value;
	}
	cout << best << '\n';
}


int kMer(string s, int k) {
	int length = s.length();
	int result = length;
	bool flag = false;
	int count = 0;
	for (int i = 0; i < length - 2 * k + 1; i += k) {
		if (s.substr(i, k) == s.substr(i + k, k)) {
			if (flag == false) count++;
			flag = true;
			count++;
			result -= k;
		}
		else {
			if (flag) {
				while (count > 0) {
					result++;
					count /= 10;
				}
			}
			flag = false;	
		}	
	}
	while (count > 0) {
		result++;
		count /= 10;
	}
	return result;
}