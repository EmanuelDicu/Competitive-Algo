template <typename type>
class LcaForest : public DfsForest<type> {
 
public:
 
	using DfsForest<type> :: n;
	using DfsForest<type> :: edg;
	using DfsForest<type> :: gph;
	using DfsForest<type> :: prv;
	using DfsForest<type> :: pos;
	using DfsForest<type> :: end;
	using DfsForest<type> :: dpt;
 
	int hg;
	vector<vector<int>> anc;
 
	LcaForest(int _n) : 
		DfsForest<type>(_n) {}
 
	void buildLca(void) {
		assert(!prv.empty());
		int mx = *max_element(dpt.begin(), dpt.end()); 
		for (hg = 1; (1 << hg) <= mx; ++hg);
		anc.resize(n);
		for (int i = 0; i < n; ++i) {
			anc[i].resize(hg);
			anc[i][0] = prv[i]; 
    }
		for (int j = 1; j < hg; ++j) {
			for (int i = 0; i < n; ++i) {
				anc[i][j] = anc[i][j - 1] == -1 ? -1 : anc[anc[i][j - 1]][j - 1]; 
      } 
    } 
  }
 
	inline bool isAncestor(int x, int y) {
		return (pos[x] <= pos[y] and end[y] <= end[x]); 
  }
 
	inline int lca(int x, int y) {
		assert(!prv.empty());
		if (isAncestor(x, y)) 
      return x; 
		if (isAncestor(y, x))  
      return y; 
		for (int j = hg - 1; j >= 0; --j) 
			if (anc[x][j] != -1 and !isAncestor(anc[x][j], y)) 
				x = anc[x][j]; 
		return prv[x]; 
  }
}; 