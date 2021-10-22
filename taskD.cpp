#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

int N, M, Sn, Sm, Fn, Fm;

pair<int, int> move(char dir, pair<int,int> &buf)
{
	pair<int, int> res(buf);
	switch (dir)
	{
	case 'N':
		res.first += 1;
		break;
	case 'S':
		res.first -=1;
		break;
	case 'W':
		res.second += 1;
		break;
	case 'E':
		res.second -= 1;
		break;
	default:
		break;
	}
	if (res.first == -1)
		res.first = N - 1;
	if (res.second == -1)
		res.second = M - 1;
	if (res.first == N)
		res.first = 0;
	if (res.second == M)
		res.second = 0;
	//if(res.fir)
	return res;
}

bool isFin(pair<int,int> &tmp)
{
	if (tmp.first == Fn && tmp.second == Fm)
		return true;
	else
		return false;
}

char direction(pair<int, int> &fir, pair<int, int> &sec)
{
	string dirs = "NEWS";
	for (int i = 0; i < 4; i++)
	{
		pair<int, int> tmp = move(dirs[i], fir);
		if (tmp.first == sec.first && tmp.second == sec.second)
			return dirs[i];
	}
	return 'B';
}

void daWay(vector<vector<pair<int, int>>> &prev){
	stack<char> res;
	
	pair<int, int> mover(Fn,Fm);
		
	while (mover.first != Sn || mover.second != Sm)
	{
		int a = mover.first;
		int b = mover.second;
		res.push(direction(mover, prev[a][b]));
		mover.first = prev[a][b].first;
		mover.second= prev[a][b].second;
		
	}
	while (!res.empty())
	{
		cout << res.top();
		res.pop();
	}
	
}

int main() {
	
	ifstream fin("input.txt");
	fin >> N >> M >> Sn >> Sm >> Fn >> Fm;
	vector<vector<char>> m(N, vector<char>(M));
	vector<vector<pair<int, int>>> prev(N, vector<pair<int, int>>(M, pair<int,int> (-1, -1)));

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			fin >> m[i][j];
	}
	
	string dirs("NESW");
	
	queue<pair<int, int>> way;
	way.push(pair<int, int>(Sn, Sm));
	pair<int, int> work;
	prev[Sn][Sm] = pair<int, int>(-2, -2);
	m[Sn][Sm] = 'B';
	while (!way.empty())
	{
		work = way.front();
		way.pop();
		for (int i = 0; i < 4; i++)
		{
			pair<int, int> tmp = move(dirs[i], work);
			if (m[tmp.first][tmp.second] == '0' && prev[tmp.first][tmp.second].first==-1)
			{
				prev[tmp.first][tmp.second] = work;
				if (isFin(tmp))
				{
					daWay(prev);
					return 0;
				}
				way.push(tmp);
			}

		}
		
	}

	cout << -1;
	return 0;
}