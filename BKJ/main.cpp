#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define MAX 10001
using namespace std;

// ���� ���� ��� ( SCC - Strongly Connected Component ) �˰���

bool finished[MAX];		// SCC�� ���ԵǾ� �ִ� �ֵ��� üũ�Ͽ� �ߺ� ����
int seqID[MAX], id;		// �� ��忡 ������ȣ�� �Űܼ� root ��带 üũ��
vector<int> v[MAX];		// �� ������ ��� �׷���
vector<vector<int>> SCC;	// SCC�� ��� vector

stack<int> s;			// stack�� Ȱ���Ͽ� scc ����

int dfs(int node)
{
	int start = seqID[node] = ++id;
	s.push(node);

	for (size_t i = 0; i < v[node].size(); i++)
	{
		int next = v[node][i];

		if (seqID[next] == 0)
			start = min(start, dfs(next));

		else if (finished[next] == false)
			start = min(start, seqID[next]);
	}

	if (start == seqID[node])
	{

		vector<int> scc;
		while (true)
		{
			int _node = s.top();
			s.pop();
			finished[_node] = true;
			scc.push_back(_node);

			if (_node == node)
				break;
			
		}

		SCC.push_back(scc);
	}
	return start;
}

bool com(vector<int>& a, vector<int>& b)
{
	return a[0] < b[0];
}

int main()
{
	int V, E;
	cin >> V >> E;

	int s, d;
	for (int i = 0; i < E; i++)
	{
		cin >> s >> d;
		v[s].push_back(d);
	}
	
	for (int i = 1; i <= V; i++)
	{
		if (seqID[i] == 0) dfs(i);
	}
	
	// �������� ����
	for (int i = 0; i < SCC.size(); i++)
		sort(SCC[i].begin(), SCC[i].end());
	sort(SCC.begin(), SCC.end(), com);
	
	cout << SCC.size()<< "\n";
	for (int i = 0; i < SCC.size(); i++)
	{
		for (int j = 0; j < SCC[i].size(); j++)
			cout << SCC[i][j] << " ";
		cout << "-1\n";
	}

	return 0;
}
