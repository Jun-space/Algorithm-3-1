#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

int m, n;
vector<vector<int>> map;
pair<int, int> start, des;


void input();
void AStar();
int distance(pair<int, int> s, pair<int, int> d);

struct compare {
	bool operator()(pair<int, pair<int, int>> x, pair<int, pair<int, int>> y) {
		return x.first > y.first;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	input();
	AStar();
	return 0;
}


void input() {
	int zero, ob, t, x, y;
	string s;
	cin >> m >> n;
	map = vector<vector<int>>(m, vector<int>(n, 1));
	cin >> zero;
	for (int i = 0; i < zero; i++) {
		cin >> t >> x >> y;
		map[x][y] = 0;
	}
	cin >> s >> x >> y;
	start = make_pair(x, y);
	cin >> s >> x >> y;
	des = make_pair(x, y);

	cin >> s >> ob;
	for (int i = 0; i < ob; i++) {
		int x2, y2;
		cin >> x >> y >> x2 >> y2;
		if (x <= x2) {
			for (int i = x; i <= x2; i++) {
				if (y <= y2) {
					for (int j = y; j <= y2; j++)
						map[i][j] = 0;
				}
				else {
					for (int j = y; j >= y2; j--)
						map[i][j] = 0;
				}
			}
		}
		else {
			for (int i = x; i >= x2; i--) {
				if (y <= y2) {
					for (int j = y; j <= y2; j++)
						map[i][j] = 0;
				}
				else {
					for (int j = y; j >= y2; j--)
						map[i][j] = 0;
				}
			}
		}
	}
}


void AStar() {
	priority_queue<pair<int , pair<int, int>>, vector<pair<int, pair<int, int>>>, compare> openList;
	vector<vector<int>> close(m, vector<int>(n, 0));

	int value;
	openList.push({ distance(start, des), start });
	close[start.first][start.second] = 1;

	while (!openList.empty()) {
		int x = openList.top().second.first;
		int y = openList.top().second.second;
		value = openList.top().first;
		openList.pop();
		close[x][y] = 1;

		int manhatan = value - distance({ x, y }, des);

		if (x == des.first && y == des.second)
			break;
		

		if (x > 0 && map[x - 1][y] == 1 && close[x - 1][y] == 0)
			openList.push({ manhatan + 1 + distance({x - 1, y}, des), {x - 1, y} });
		if (y > 0 && map[x][y - 1] == 1 && close[x][y - 1] == 0)
			openList.push({ manhatan + 1 + distance({x, y - 1}, des), {x, y - 1} });
		if (x < m - 1 && map[x + 1][y] == 1 && close[x + 1][y] == 0)
			openList.push({ manhatan + 1 + distance({x + 1, y}, des), {x + 1, y} });
		if (y < n - 1 && map[x][y + 1] == 1 && close[x][y + 1] == 0)
			openList.push({ manhatan + 1 + distance({x, y + 1}, des), {x, y + 1} });
	}

	cout << value * 3 << '\n';
}

int distance(pair<int, int> s, pair<int, int> d) {
	return abs(s.first-d.first)+abs(s.second-d.second);
}
