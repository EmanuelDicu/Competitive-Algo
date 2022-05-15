template <typename type>
vector<type> dijkstraPriorityQueue(const Graph<type> &g, vector<int> lst) {
	vector<type> dst(g.n, numeric_limits<type> :: max());
	priority_queue<pair<type, int>, vector<pair<type, int>>, greater<pair<type, int>>> prq;
	for (int src : lst) {
		assert(0 <= src and src < g.n);
		dst[src] = 0; prq.push(make_pair(0, src)); 
  }
	while (!prq.empty()) {
		type c = prq.top().first; int x = prq.top().second; prq.pop();
		if (dst[x] != c) {
			continue; }
		for (int id : g.gph[x]) {
			auto &ed = g.edg[id]; int y = ed.from ^ ed.to ^ x;
			if (dst[y] > dst[x] + ed.cost) {
				dst[y] = dst[x] + ed.cost;
				prq.push(make_pair(dst[y], y)); 
      } 
    } 
  }
	return dst; 
}
 
template <typename type>
vector<type> dijkstraPriorityQueue(const Graph<type> &g, int src) {
	return dijkstraPriorityQueue(g, vector<int>(1, src)); 
}
 