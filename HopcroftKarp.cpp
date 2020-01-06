typedef struct HopcroftKarp {
	int n, m;
	const int INF = 987654321;
	vector<int> A, B, dist;
	vector<bool> used;
	vector<vector<int>> adj;
	HopcroftKarp(int _n, int _m) : n(_n), m(_m), adj(_n, vector<int>()) {
	}
	void add_edge(int st, int en) {
		adj[st].push_back(en);
	}
	void bfs() {
		queue<int> Q;
		for (int i = 0; i < n; i++) {
			if (!used[i]) {
				Q.push(i);
				dist[i] = 0;
			}
			else dist[i] = INF;
		}
		while (!Q.empty()) {
			int here = Q.front(); Q.pop();
			for (int th : adj[here]) {
				if (B[th] != -1 && dist[B[th]] == INF) {
					dist[B[th]] = dist[here] + 1;
					Q.push(B[th]);
				}
			}
		}
	}
	bool dfs(int x) {
		for (int th : adj[x]) {
			if (B[th] == -1 || dist[x] + 1 == dist[B[th]] && dfs(B[th])) {
				used[x] = true;
				A[x] = th;
				B[th] = x;
				return true;
			}
		}
		return false;
	}
	int find_matching() {
		A.assign(n, -1); B.assign(m, -1);
		used.assign(n, false); dist.assign(n, INF);
		int match = 0;
		while (true) {
			int flow = 0;
			bfs();
			for (int i = 0; i < n; i++)
				if (!used[i] && dfs(i)) flow++;
			if (!flow) break;
			match += flow;
		}
		return match;
	}
	vector<int> match_result() {
		return A;
	}
}BM;