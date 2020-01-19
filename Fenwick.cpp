using namespace std;
typedef long long ll;

struct fenwick {
	int sz;  vector<ll> v;
	fenwick(int _sz) : sz(_sz + 1), v(_sz + 1) {}
	void update(int pos, ll val) {
		for (int i = pos; i < sz; i += (i&-i))
			v[i] += val;
	}
	ll query(int pos) {
		ll s = 0;
		for (int i = pos; i > 0; i -= (i&-i))
			s += v[i];
		return s;
	}
	ll query(int le, int ri) {
		if (!le) return query(ri);
		else return query(ri) - query(le - 1);
	}
};