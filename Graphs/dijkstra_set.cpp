template <typename type>
vector<type> dijkstraSet(const Graph<type> &g, vector<int> lst) {
	set<pair<type, int>> mst;
	vector<type> dst(g.n, numeric_limits<type> :: max());
	for (int src : lst) {
		assert(0 <= src and src < g.n);
		dst[src] = 0; mst.insert(make_pair(0, src)); 
  }
	while (!mst.empty()) {
		int x = mst.begin() -> second; mst.erase(mst.begin());
		for (int id : g.gph[x]) {
			auto &ed = g.edg[id]; int y = ed.from ^ ed.to ^ x;
			if (dst[y] > dst[x] + ed.cost) {
				mst.erase(make_pair(dst[y], y));
				dst[y] = dst[x] + ed.cost;
				mst.insert(make_pair(dst[y], y)); 
      } 
    } 
  } 
	return dst; 
}

template <typename type>
vector<type> dijkstraSet(const Graph<type> &g, int src) {
	return dijkstraSet(g, vector<int>(1, src)); 
}