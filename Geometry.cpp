#define x first
#define y second

typedef pair<int, int> pt;

int ccw(pt a, pt b, pt c) {
	ll t = 1LL * a.x * (b.y - c.y) + 1LL * b.x * (c.y - a.y) + 1LL * c.x * (a.y - b.y);
	return t ? (t > 0 ? 1 : -1) : 0;
}

vector<pt> convex_hull(vector<pt>& v) {
	sort(v.begin(), v.end());
	vector<pt> hi, lo;
	for (pt& t : v) {
		while (hi.size() >= 2 && ccw(*++hi.rbegin(), *hi.rbegin(), t) >= 0) hi.pop_back();
		while (lo.size() >= 2 && ccw(*++lo.rbegin(), *lo.rbegin(), t) <= 0) lo.pop_back();
		hi.push_back(t); lo.push_back(t);
	}
	hi.insert(hi.end(), ++lo.rbegin(), --lo.rend());
	return hi;
}

bool segment_intersect(pt a, pt b, pt c, pt d) {
	int ab = ccw(a, b, c)*ccw(a, b, d);
	int cd = ccw(c, d, a)*ccw(c, d, b);
	if (!ab && !cd) {
		if (a > b) swap(a, b);
		if (c > d) swap(c, d);
		return a <= d && c <= b;
	}
	return ab <= 0 && cd <= 0;
}

const int INF = 1000000000;
bool point_in_polygon(vector<pt>& poly, pt k) {
	pt temp = make_pair(k.x + 1, INF);
	int s = 0;
	for (int i = 0; i < poly.size(); i++)
		if (segment_intersect(poly[i], poly[(i + 1) % poly.size()], k, temp)) s++;
	return s % 2;
}

pt read_pt() {
	int t1, t2;
	cin >> t1 >> t2;
	return make_pair(t1, t2);
}