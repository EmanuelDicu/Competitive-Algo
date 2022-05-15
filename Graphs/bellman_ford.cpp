template <typename type>
vector<type> bellmanFord(const Graph<type> &g, vector<int> lst, const int lim = 1000000) {
	vector<type> dst(g.n, numeric_limits<type> :: max());
	deque<int> que; vector<bool> oki(g.n, false); int cnt = 0;
	for (int src : lst) {
		assert(0 <= src and src < g.n);
		dst[src] = 0; oki[src] = true; que.push_back(src); 
  }
	while (que.size()) {
		int x = que.front(); oki[x] = false; que.pop_front();
		for (int id : g.gph[x]) {
			auto &ed = g.edg[id]; int y = ed.from ^ ed.to ^ x;
			if (dst[y] > dst[x] + ed.cost) {
				dst[y] = dst[x] + ed.cost;
				if (!oki[y]) {
					oki[y] = true; ++cnt; que.push_back(y);
					if (cnt == lim) {
						return vector<type>(); 
          } 
        } 
      } 
    } 
  }
	return dst; 
}
 
template <typename type>
vector<type> bellmanFord(const Graph<type> &g, int src, const int lim = 1000000) {
	return bellmanFord(g, vector<int>(1, src), lim);
}
 