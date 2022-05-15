template <typename type>
class HldForest : public LcaForest<type> {
 
public:
 
	using LcaForest<type> :: n;
	using LcaForest<type> :: edg;
	using LcaForest<type> :: gph;
	using LcaForest<type> :: prv;
	using LcaForest<type> :: szt;
	using LcaForest<type> :: pos;
	using LcaForest<type> :: ord;
	using LcaForest<type> :: dpt;
	using LcaForest<type> :: dfs;
	using LcaForest<type> :: dfsAll;
	using LcaForest<type> :: buildLca;
	using LcaForest<type> :: lca;
 
	vector<int> fst, vis;
	
	HldForest(int _n) : LcaForest<type>(_n) {
		vis.resize(n); 
  }
 
	void buildHld(const vector<int> &lst) {
		for (int cnt = 0; cnt <= 1; ++cnt) {
			if (lst.empty()) {
				dfsAll(); 
      } else {
				ord.clear();
				for (int x : lst) {
					dfs(x, false); 
        } 
      }
			if (cnt == 1) {
				break; 
      }
			for (int x = 0; x < n; ++x) {
				if (gph[x].empty()) {		
					continue; 
        }
				int bsz = -1, bid = 0;
				for (int i = 0; i < (int) gph[x].size(); ++i) {
					int id = gph[x][i], y = edg[id].from ^ edg[id].to ^ x;
					if (prv[y] == x and szt[y] > bsz) {
						bsz = szt[y]; bid = i; 
          } 
        }
				swap(gph[x][0], gph[x][bid]); 
      } 
    } 
		buildLca(); fst.resize(n);
		for (int i = 0; i < n; ++i) {
			fst[i] = i; 
    }		
		for (int i = 0; i < n - 1; ++i) {
			int x = ord[i], y = ord[i + 1];
			if (prv[y] == x) {
				fst[y] = fst[x]; 
      } 
    } 
  }
 
	void buildHld(int x) {
		buildHld(vector<int>(1, x)); 
  }
	
	void buildHldAll(void) {
		buildHld(vector<int>()); 
  }
 
	vector<pair<int, int>> getPath(int x, int y) {
		vector<pair<int, int>> lst[2];
		assert(!fst.empty()); int z = lca(x, y);
		if (z == -1) { 
			return vector<pair<int, int>>(); 
    }
		for (int id = 0; id <= 1; ++id) {
			int v = (id == 0 ? x : y);
			while (v != z) {
				if (dpt[fst[v]] <= dpt[z]) {
					lst[id].push_back(make_pair(pos[z] + 1, pos[v])); break; 
        }
				lst[id].push_back(make_pair(pos[fst[v]], pos[v])); v = prv[fst[v]]; 
      } 
    }
		vector<pair<int, int>> ans;
		for (int i = 0; i < (int) lst[0].size(); ++i) {
			ans.push_back(make_pair(lst[0][i].second, lst[0][i].first)); 
    }
		ans.push_back(make_pair(-1, pos[z]));
		for (int i = (int) lst[1].size() - 1; i >= 0; --i) {
			ans.push_back(make_pair(lst[1][i].first, lst[1][i].second)); 
    }
		return ans; 
  }
	
	bool applyOnPath(int x, int y, bool wlca, function<void(int, int, bool)> f) {
		// f(x, y, true if path [x -> y] goes up, false otherwise)
		assert(!fst.empty()); int z = lca(x, y), v, cnt;
		if (z == -1) {
			return false; 
    }
		v = x;
		while (v != z) {
			if (dpt[fst[v]] <= dpt[z]) {
				f(pos[z] + 1, pos[v], true); break; 
      }
			f(pos[fst[v]], pos[v], true); v = prv[fst[v]]; 
    }
		if (wlca) {
			f(pos[z], pos[z], false); 
    }
		v = y; cnt = 0;
		while (v != z) {
			if (dpt[fst[v]] <= dpt[z]) {
				f(pos[z] + 1, pos[v], false); break; 
      }
			vis[cnt++] = v; v = prv[fst[v]]; 
    }
		for (int i = cnt - 1; i >= 0; --i) {
			v = vis[i]; f(pos[fst[v]], pos[v], false); 
    } 
		return true; 
  }
};