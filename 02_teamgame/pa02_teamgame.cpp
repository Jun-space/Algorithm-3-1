#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
	int N, k;
	long long fail = 0;
	long long time = 0;
	vector<long long> problem;

	cin >> N >> k;


	for (int i = 0; i < N; i++) {
		long long t;
		cin >> t;

		if (k - 1 == i)
			fail = t;
		else 
			problem.push_back(t);
	}

	sort(problem.begin(), problem.end());

	for (int i = 0; i < problem.size(); i++) {
		time += problem[i] * (N - i);
	}

	time += fail;

	cout << time << '\n';

	return 0;
}