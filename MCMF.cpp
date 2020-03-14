using namespace std;
typedef pair<double,ll> pdl;

struct MCMF {
	struct edge {
		int tar, rev;
		double cost;
		ll res, cap;
	};
	int n;
	vector<vector<edge>> adj;
	MCMF(int _n) : adj(_n), n(_n) {}
	
	void add_edge(int s, int e, double cost, ll cap) {
		adj[s].push_back({ e,adj[e].size(),cost,cap,cap });
		adj[e].push_back({ s,adj[s].size(),cost,cap,cap });
	}

	pdl push_flow(int s, int e) {
		vector<pdl> dist(n, { LINF,0 });
		vector<int> from(n, -1), v(n);

		//SPFA
		dist[s] = { 0,LINF };
		queue<int> q; v[s] = 1; q.push(s);
		while (!q.empty()) {
			int hr = q.front(); q.pop();
			v[hr] = 0;
			for (auto th : adj[hr]) {
				if (!th.res) continue;
				int ntar = th.tar;
				double ncost = dist[hr].first + th.cost;
				ll nflow = min(dist[hr].second, th.res);
				if (dist[ntar].first > ncost) {
					dist[ntar] = { ncost,nflow };
					from[ntar] = th.rev;
					if (v[ntar]) continue;
					v[ntar] = 1; q.push(ntar);
				}
			}
		}

		//move flow
		int p = e;
		double pcost = dist[p].first;
		ll flow = dist[p].second;
		if (!flow) return { 0,0 };
		
		while (from[p] != -1) {
			int nedge = from[p];
			int np = adj[p][nedge].tar;
			int fedge = adj[p][nedge].rev;
			adj[p][nedge].res += flow;
			adj[p][fedge].res -= flow;
			p = np;
		}
		return make_pair(pcost * flow, flow);
	}

	pdl solve(int s, int e) {
		double tc = 0; ll tf = 0;
		while (1) {
			auto ret = push_flow(s, e);
			if (ret.second <= 0) break;
			tc += ret.first; tf += ret.second;
		}
		return { tc,tf };
	}
};
