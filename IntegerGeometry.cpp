
struct Point {
	ll x, y;
	bool operator==(const Point& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator<(const Point& rhs) const {
		return x == rhs.x ? y < rhs.y : x < rhs.x;
	}
	bool operator>(const Point& rhs) const {
		return x == rhs.x ? y > rhs.y : x > rhs.x;
	}
	bool operator<=(const Point& rhs) const {
		return x == rhs.x ? y <= rhs.y : x <= rhs.x;
	}
	bool operator>=(const Point& rhs) const {
		return x == rhs.x ? y >= rhs.y : x >= rhs.x;
	}
	Point operator+(const Point& rhs) const {
		return Point{ x + rhs.x, y + rhs.y };
	}
	Point operator-(const Point& rhs) const {
		return Point{ x - rhs.x, y - rhs.y };
	}
	Point operator*(ll t) const {
		return Point{ x * t, y * t };
	}
};

int ccw(Point a, Point b, Point c) {
	ll t = 1LL * a.x * (b.y - c.y) + 1LL * b.x * (c.y - a.y) + 1LL * c.x * (a.y - b.y);
	return t ? (t > 0 ? 1 : -1) : 0;
}

struct Line {
	Point a, b;
};

bool segment_intersect(Line p, Line q) {
	Point a = p.a, b = p.b, c = q.a, d = q.b;
	int ab = ccw(a, b, c) * ccw(a, b, d);
	int cd = ccw(c, d, a) * ccw(c, d, b);
	if (!ab && !cd) {
		if (a > b) swap(a, b);
		if (c > d) swap(c, d);
		return a <= d && c <= b;
	}
	return ab <= 0 && cd <= 0;
}

int ccw(pt a, pt b, pt c) {
	ll t = 1LL * a.x * (b.y - c.y) + 1LL * b.x * (c.y - a.y) + 1LL * c.x * (a.y - b.y);
	return t ? (t > 0 ? 1 : -1) : 0;
}

vector<Point> convex_hull(vector<Point>& v) {
	sort(v.begin(), v.end());
	vector<Point> hi, lo;
	for (Point& t : v) {
		while (hi.size() >= 2 && ccw(*++hi.rbegin(), *hi.rbegin(), t) >= 0) hi.pop_back();
		while (lo.size() >= 2 && ccw(*++lo.rbegin(), *lo.rbegin(), t) <= 0) lo.pop_back();
		hi.push_back(t); lo.push_back(t);
	}
	hi.insert(hi.end(), ++lo.rbegin(), --lo.rend());
	return hi;
}

const int INF = 1000000000;
bool point_in_polygon(vector<Point>& poly, pt k) {
	pt temp = make_pair(k.x + 1, INF);
	int s = 0;
	for (int i = 0; i < poly.size(); i++)
		if (segment_intersect({ poly[i], poly[(i + 1) % poly.size()] }, { k, temp })) s++;
	return s % 2;
}

pt read_pt() {
	ll t1, t2;
	cin >> t1 >> t2; Point t;
	return t = { t1,t2 };
}
