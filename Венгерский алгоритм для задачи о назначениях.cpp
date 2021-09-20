#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {

    ifstream fin("input.txt");
	int INF = 1000000000;
    int n, m;

    fin >> n >> m;
    //cout<<n<<m;
    vector<vector<long long>> a(n+1, vector<long long>(m+1, INT_MAX));
    long long ra, rb, c, s, f, q;
	int read;
    for (int i = 0; i < n; i++)
        a[i][i] = 0;
    for (int i = 1; i <= n; i++)
    {
		for (int j = 1; j <= m; j++)
		{
			fin >> read;
			a[i][j] = read;
		}
    }
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}

	vector<int> u(n + 1), v(m + 1), p(m + 1), way(m + 1);
	for (int i = 1; i <= n; ++i) {
		p[0] = i;
		int j0 = 0;
		vector<int> minv(m + 1, INF);
		vector<char> used(m + 1, false);
		do {
			used[j0] = true;
			int i0 = p[j0], delta = INF, j1;
			for (int j = 1; j <= m; ++j)
				if (!used[j]) {
					int cur = a[i0][j] - u[i0] - v[j];
					if (cur < minv[j])
						minv[j] = cur, way[j] = j0;
					if (minv[j] < delta)
						delta = minv[j], j1 = j;
				}
			for (int j = 0; j <= m; ++j)
				if (used[j])
					u[p[j]] += delta, v[j] -= delta;
				else
					minv[j] -= delta;
			j0 = j1;
		} while (p[j0] != 0);
		do {
			int j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while (j0);
	}
	cout << "\n\n\n\tAnswer:\n\n";
	vector<int> ans(n + 1);
	for (int j = 1; j <= m; ++j)
		ans[p[j]] = j;
	for (int j = 1; j <= m; ++j)
		cout << "\tworker #" << j << " best pick #" << ans[j] << " job;\n";

    return 0;
}
