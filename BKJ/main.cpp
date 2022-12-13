#include <iostream>
#include <vector>
using namespace std;


enum MAXorMIN
{
	// PQ��ü ������ �б� ���ϰ� enum���� �������
	MIN = false,
	MAX = true
};

class PQ
{
public:
	PQ(bool b)
	{
		isMAX = b; // true�� �ϸ� maxHeap
	}

	void push(int n)
	{
		v.push_back(n);
		// vector�� ��������� �迭�� �ص� ���� ����

		int root = static_cast<int>(v.size()) - 1;
		int c = root;

		do
		{ // �θ���� �� �� �ڸ� �ٲ�
			root = max((c - 1) / 2, 0);
			int rN = v[root];
			int cN = v[c];

			// minHeap, maxHeap�� ����ؼ� ���Լ��� ����
			if (compare(rN, cN))
			{
				v[root] = cN;
				v[c] = rN;
			}

			c = root;
		} while (c > 0);
	}

	// minHeap�� maxHeap ���̿��� ������ ��ȯ�� ���
	void exChange(int n)
	{
		if (v.size() == 0) return;

		int size = static_cast<int>(v.size()) - 1;

		v[0] = n;

		int c = 0;
		int root = 0;

		// �θ�� �ڽ� �� �� ��ȯ
		do
		{
			c = (root * 2) + 1;
			if (c > size) break;

			if (c < size && compare(v[c], v[c + 1]))
				c++;

			int rN = v[root];
			int cN = v[c];


			if (c <= size && compare(rN, cN))
			{
				v[root] = cN;
				v[c] = rN;
			}

			root = c;

		} while (root < size);


	}

	int top()
	{
		if ((int)v.size() == 0) return -1;
		return v[0];
	}

	bool compare(int r, int c)
	{
		if (isMAX) return r < c; // maxHeap�� ū�� ����
		return r > c; // minHeap�� ������ ����
	}

	int size()
	{
		return static_cast<int>(v.size());
	}

	bool empty()
	{
		return static_cast<int>(v.size()) == 0;
	}

public:
	bool isMAX = false;
	vector<int> v;
};

int main()
{
	ios::sync_with_stdio(false); // �ӵ� �������� �ڵ�
	cin.tie(NULL); // �ӵ� �������� �ڵ�

	vector<int> v;
	int N, n;
	cin >> N;

	PQ max = PQ(MAX);
	PQ min = PQ(MIN);


	for (int i = 0; i < N; i++)
	{
		cin >> n;
		v.push_back(n);
	}



	for (int i = 0; i < N; i++)
	{
		n = v[i];

		if (max.size() == min.size())
			max.push(n); // ���� ���� �������� ����
		else
			min.push(n); // ū ���� �������� ����
		// �׷� maxHeap�� minHeap�� top���� ��� ���� ��

		if (!max.empty() && !min.empty() && max.top() > min.top())
		{
			int maxN, minN;
			maxN = max.top();
			minN = min.top();

			max.exChange(minN);
			min.exChange(maxN);
		}
		cout << max.top() << '\n';
	}

	return 0;
}