#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class segment {
public:
	int x1;
	int y1;
	int x2;
	int y2;
	vector<int> overlap;

	segment(int _x1, int _y1, int _x2, int _y2) {
		if (_x1 <= _x2) {
			x1 = _x1;
			y1 = _y1;
			x2 = _x2;
			y2 = _y2;
		}
		else {
			x1 = _x2;
			y1 = _y2;
			x2 = _x1;
			y2 = _y1;
		}
	}
};

int N;
int counts = 0;
int maxValue = 0;
vector<int> visited;
vector<vector<int>> relation;


bool cmp(segment s1, segment s2) {
	if (s1.x1 == s2.x1) {
		return s1.y1 < s2.y1;
	}
	return s1.x1 < s2.x1;
}


int CCW(int x1, int y1, int x2, int y2, int x3, int y3) {
	int a = x1 * y2 + x2 * y3 + x3 * y1;
	int b = y1 * x2 + y2 * x3 + y3 * x1;
	if (a < b) return 1;
	if (a == b) return 0;
	return -1;
}


bool boxOverlap(segment s1, segment s2) {
	if (s1.x1 > s2.x1)
		swap(s1, s2);
	int x1 = s1.x1;
	int y1 = s1.y1 < s1.y2 ? s1.y1 : s1.y2;
	int x2 = s1.x2;
	int y2 = s1.y1 < s1.y2 ? s1.y2 : s1.y1;
	int x3 = s2.x1;
	int y3 = s2.y1 < s2.y2 ? s2.y1 : s2.y2;
	int x4 = s2.x2;
	int y4 = s2.y1 < s2.y2 ? s2.y2 : s2.y1;

	if (x1 <= x4 && x3 <= x2 && y1 <= y4 && y3 <= y2)
		return true;
	return false;
}


void dfs(int i, int& size) {
	for (int j = 0; j < N; j++) {
		if (relation[i][j] == 1 && !(visited[j])) {
			visited[j] = 1;
			size++;
			dfs(j, size);
		}
	}
	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	vector<segment> v;
	for (int i = 0; i < N; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		v.push_back(segment(x1, y1, x2, y2));
	}


	for (int i = 0; i < N; i++) {
		segment s1 = v[i];
		for (int j = 0; j < N; j++) {
			segment s2 = v[j];
			if (boxOverlap(s1, s2)) {
				int abc = CCW(s1.x1, s1.y1, s1.x2, s1.y2, s2.x1, s2.y1);
				int abd = CCW(s1.x1, s1.y1, s1.x2, s1.y2, s2.x2, s2.y2);
				int cda = CCW(s2.x1, s2.y1, s2.x2, s2.y2, s1.x1, s1.y1);
				int cdb = CCW(s2.x1, s2.y1, s2.x2, s2.y2, s1.x2, s1.y2);

				if (abc * abd == 0 && cda * cdb == 0) {
					if (s1.x1 <= s2.x2 && s2.x1 <= s1.x2)
						v[i].overlap.push_back(j);
				}
				else if (abc * abd <= 0 && cda * cdb <= 0)
					v[i].overlap.push_back(j);
			}
		}
	}

	relation = vector<vector<int>>(N, vector<int>(N, 0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < v[i].overlap.size(); j++) {
			relation[i][v[i].overlap[j]] = 1;
		}
	}

	
	visited = vector<int>(N, 0);

	for (int i = 0; i < N; i++) {
		int size = 1;
		if (!visited[i]) {
			visited[i] = 1;
			counts++;
			dfs(i, size);
			maxValue = max(maxValue, size);
		}
	}

	cout << counts << '\n' << maxValue << '\n';


	return 0;
}