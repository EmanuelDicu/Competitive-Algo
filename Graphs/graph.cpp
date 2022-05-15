template <typename type>
class Graph {
 
public:
 
	struct Edge {	
		int from, to; 
		type cost; 
	};
 
	int n;
	vector<Edge> edg;
	vector<vector<int>> gph;
 
	Graph(int _n) : n(_n) {
		gph.resize(n); 
  }
	
	virtual int addEdge(int from, int to, type cost = 1) {
		assert(0 <= min(from, to) and max(from, to) < n);
		int id = (int) edg.size();
		gph[from].push_back(id);
		edg.push_back({from, to, cost}); 
		return id; 
  }
};