#include <iostream>
#include <string>
using namespace std;
string s;


int palindrome();
int pseudoPalin(int left, int right, bool removeL);
bool isPalin(int left, int right);


int main() {
	int n;
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> s;
		cout << palindrome() << '\n';
	}

	return 0;
}


int palindrome() {
	int l = s.length();
	int left = 0;
	int right = l - 1;

	if (s[left] != s[right]) return 0;


	left++;
	right--;
	while (left <= right) {
		if (s[left] != s[right]) {
			int a = pseudoPalin(left, right, true);
			int b = pseudoPalin(left, right, false);
			return a > b ? a : b;
		}
		left++;
		right--;
	}
	return l;
}

int pseudoPalin(int left, int right, bool removeL) {
	int remove = 0;
	int tmp = left;
	int a = 0;
	int b = 0;
	for (int limit = left; limit < right; limit++)
		if (isPalin(left, limit)) a = limit - left + 1;
	for (int limit = right; limit > left; limit--)
		if (isPalin(limit, right)) b = right - limit + 1;

	while (s[left] != s[right]) {
		if (removeL) left++;
		else right--;
		remove++;
	}
	while (left < right) {
		if (s[left] != s[right]) {
			int n = a > b ? a : b;
			return 2 * tmp + n;


		}
		left++;
		right--;
	}
	return s.length() - remove;
}

bool isPalin(int left, int right) {
	while (left <= right) {
		if (s[left] != s[right])
			return false;
		left++;
		right--;
	}
	return true;
}