#include <iostream>
#include <algorithm>

using namespace std;
long long int arr[5000000];

int main() {
	// ����� �ӵ��� �����ֱ� ����
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	// N�� �Է¹��� ���� ����, K�� ���������� �� ��° ������
	int N, K;
	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	sort(arr, arr + N);

	cout << arr[K - 1];

	return 0;
}