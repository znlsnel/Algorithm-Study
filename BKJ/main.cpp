#include <iostream>
#include <vector>
#include <queue>

// �ƽ�Ű�ڵ�
// �ҹ��� ( 97 ~ 122 )
// �빮�� ( 65 ~ 90 )
// �Է� ���� ���ڸ� 0 ~ 51������ index ��ȣ�� �ٲ���
#define chgId(char) char = char > 90 ? char - 71 : char - 65
#define MAX  52

using namespace std;

// ��� ��尡 ��� vector
vector<int> v[MAX];

// �� ������ �ִ� ���� ����
int limit[MAX][MAX];

// �� ������ ���� ���� ����
int flow[MAX][MAX];

// �θ� ��� ����
int parent[MAX];

int MaxFlow()
{
	// A : 0,      Z : 25 
	int result = 0, start = 0, end = 25;

	while (true)
	{
		// parent�� -1�� �ʱ�ȭ
		fill(parent, parent + MAX, -1);
		queue<int> q;
		q.push(start);

		while (!q.empty())
		{
			int curr = q.front();
			q.pop();

			for (int i = 0; i < v[curr].size(); i++)
			{
				int next = v[curr][i];

				// ��� ���� ������ �����ְ� �̹� �˻��� ��尡 �ƴҶ�
				if (limit[curr][next] > flow[curr][next] && parent[next] == -1)
				{
					q.push(next);
					// �θ��� ����
					parent[next] = curr;
				}
			}
		}
	
		// parent[end]�� -1�̶�� ���� end�� ������� ������ �������� �ʴٴ� ��
		// �� �˻��� �Ϸ�Ǿ��ٴ� ���� �ǹ���
		if (parent[end] == -1) return result;

		// end�� ���� ��η� ��� ���� �� �ִ� �뷮�� ����
		int min = 1000;
		for (int i = end; i != start; i = parent[i])
		{
			// �� ������  �ִ� ���� - ���� ���� = ���� ����
			int remain = limit[parent[i]][i] - flow[parent[i]][i];
			if (min > remain) min = remain;
		}

		// ���� �帣�� �ִ� �� üũ
		for (int i = end; i != start; i = parent[i])
		{
			flow[parent[i]][i] += min;
			flow[i][parent[i]] -= min;
		}
		result += min;
	}

}

int main()
{
	int N;
	char start, dest;
	int capacity;
	cin >> N;
	
	for (int i = 0; i < N; i++)
	{
		cin >> start >> dest >> capacity;
		chgId(start);
		chgId(dest);

		v[start].push_back(dest);
		v[dest].push_back(start);

		limit[start][dest] += capacity;
		limit[dest][start] += capacity;
	}
	cout << MaxFlow();

	return 0;
}