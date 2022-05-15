template <typename type>
class Forest : public Graph<type> {
	
public:
 
	using Graph<type> :: n;
	using Graph<type> :: edg;
	using Graph<type> :: gph;
 
	Forest(int _n) : 
		Graph<type>(_n) {}
 
	int addEdge(int from, int to, type cost = 1) {
		assert(0 <= min(from, to) and max(from, to) < n);
		int id = (int) edg.size();
		gph[from].push_back(id); gph[to].push_back(id);
		edg.push_back({from, to, cost});
		return id; 
  }
};