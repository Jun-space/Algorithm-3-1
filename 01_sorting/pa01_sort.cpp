#include <iostream>
#include <vector>
using namespace std;

vector<int> li;
int choice, k, N;
int kPass = 0;


void selection();
void heap();
void adjust(int, int);
void quick();
void quickSort(int, int);
int partition(int, int);


int main() {
	cin >> choice >> k;
	cin >> N;

	for (int i = 0; i < N; i++) {
		int t;
		cin >> t;
		li.push_back(t);
	}

	if (choice == 1) selection();
	else if (choice == 2) heap();
	else if (choice == 3) quick();
	
	return 0;
}


void selection() {
	for (int i = 0; i < k; i++) {
		int min_index = i;
		for (int j = i + 1; j < N; j++) {
			min_index = li[min_index] <= li[j] ? min_index : j;
		}
		int min = li[min_index];
		li[min_index] = li[i];
		li[i] = min;
	}

	for (int i = 0; i < N; i++)
		cout << li[i] << '\n';
}


void heap() {
	for (int i = N / 2; i >= 0; i--) {
		adjust(i, N);
	}

	for (int i = 1; i <= k; i++) {
		int tmp = li[0];
		li[0] = li[N - i];
		li[N - i] = tmp;

		adjust(0, N - i);
	}

	for (int i = 0; i < N - k; i++)
		cout << li[i] << '\n';
}


void adjust(int root, int n) {
	int parent = root;
	int child = 2 * root + 1;

	while (child <= n - 1) {
		if (child < n - 1) child = li[child] < li[child + 1] ? child : child + 1;
		if (li[parent] <= li[child]) break;

		int tmp = li[child];
		li[child] = li[parent];
		li[parent] = tmp;

		parent = child;
		child = 2 * parent + 1;
	}
}


void quick() {
	quickSort(0, N - 1);

	for (int i = 0; i < N; i++)
		cout << li[i] << '\n';
}


void quickSort(int left, int right) {
	if (left < right && kPass < k) {
		int pivot = partition(left, right);
		quickSort(left, pivot - 1);
		quickSort(pivot + 1, right);
	}
}


int partition(int left, int right) {
	int pivot = li[left];
	int low = left;
	int high = right;
	while (true) {
		while (li[left] <= pivot && left < high) left++;
		while (pivot < li[right] && right > low) right--;
		
		if (left < right) {
			int tmp = li[left];
			li[left] = li[right];
			li[right] = tmp;
			left = low;
			right = high;
		}
		else
			break;
	}
	li[low] = li[right];
	li[right] = pivot;

	kPass++;
	return right;
}