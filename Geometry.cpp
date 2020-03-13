#define x first
#define y second

Point ccw_perpendicular(Line &L) {
	Point t = L.dir;
	Point a = { -t.y,t.x }, b = { t.y,-t.x };
	Point np = a + L.pos;
	if (ccw_line(L, np) >= 0) return a;
	else return b;
}

Line moveLine_length(Line L, Point p, double d) {
	double k = dist(p, { 0,0 });
	p = p * (d / k);
	L.pos = L.pos + p;
	return L;
}

double crs(Point a, Point b, Point c, Point d) {
	return (b.x - a.x)*(d.y - c.y) - (b.y - a.y)*(d.x - c.x);
}

bool bad(Line &a, Line &b, Line &c) {
	Point v;
	if (!get_cross(a, b, v)) return false;
	return diff(crs(c.pos, c.dir + c.pos, c.pos, v), 0) <= 0;
}

vector<Point> HPI(vector<Line>& ln) {
	auto lsgn = [&](const Line& a) {
		if (a.pos.y == (a.pos + a.dir).y) return a.pos.x > (a.pos + a.dir).x;
		return a.pos.y > (a.pos + a.dir).y;
	};
	sort(ln.begin(), ln.end(), [&](const Line& a, const Line& b) {
		if (lsgn(a) != lsgn(b)) return lsgn(a) < lsgn(b);
		Point p = a.pos, q = a.pos + a.dir, r = b.pos, s = b.pos + b.dir;
		return crs(p, q, r, s) > 0;
	});

	deque<Line> dq;
	for (int i = 0; i < ln.size(); i++) {
		while (dq.size() >= 2 && bad(dq[dq.size() - 2], dq.back(), ln[i]))
			dq.pop_back();
		while (dq.size() >= 2 && bad(dq[0], dq[1], ln[i]))
			dq.pop_front();
		if (dq.size() < 2 || !bad(dq.back(), ln[i], dq[0]))
			dq.push_back(ln[i]);
	}

	vector<Point> res;
	if (dq.size() >= 3) for (int i = 0; i < dq.size(); i++) {
		int j = (i + 1) % (int)dq.size();
		Point v;
		if (!get_cross(dq[i], dq[j], v)) continue;
		res.push_back(v);
	}
	return res;
}

double rotating_calipus(vector<Point>& pt) {
	sort(pt.begin(), pt.end(), [](const Point& a, const Point& b) {
		return (a.x == b.x) ? a.y < b.y : a.x < b.x;
	});
	vector<Point> up, lo;
	for (const auto& p : pt) {
		while (up.size() >= 2 && ccw(*++up.rbegin(), *up.rbegin(), p) >= 0) up.pop_back();
		while (lo.size() >= 2 && ccw(*++lo.rbegin(), *lo.rbegin(), p) <= 0) lo.pop_back();
		up.emplace_back(p);
		lo.emplace_back(p);
	}

	double ma = 0;
	for (int i = 0, j = (int)lo.size() - 1; i + 1 < up.size() || j > 0; ) {
		ma = max(ma, dist(up[i], lo[j]));
		if (i + 1 == up.size()) --j;
		else if (j == 0) ++i;
		else if ((up[i + 1].y - up[i].y) * (lo[j].x - lo[j - 1].x) > (up[i + 1].x - up[i].x) * (lo[j].y - lo[j - 1].y))
			++i;
		else --j;
	}
	return ma;
}

Point vector_reform(Point p, double val) {
	double k = dist(p, { 0,0 });
	return p * (val / k);
}

