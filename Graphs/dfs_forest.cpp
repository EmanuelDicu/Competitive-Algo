template <typename type>
class DfsForest : public Forest<type> {
 
public:
 
	using Forest<type> :: n;
	using Forest<type> :: edg;
	using Forest<type> :: gph;
 
	vector<int> prv, pre, ord, pos,
			    end, szt, rot, dpt;
	vector<type> dst;
 
	DfsForest(int _n) : 
		Forest<type>(_n) {}
 
	void initialize(void) {
		prv = pre = pos = end = rot = dpt = vector<int>(n, -1);
		szt = vector<int>(n, 0); dst = vector<type>(n); ord.clear(); }
 
	void clear(void) {
		prv.clear(); pre.clear(); ord.clear(); pos.clear(); end.clear();
		szt.clear(); rot.clear(); dpt.clear(); dst.clear(); }
 
private:
 
	void doDfs(int x) {
		pos[x] = (int) ord.size(); ord.push_back(x); szt[x] = 1;
		for (int id : gph[x]) {
			if (id == pre[x]) {
				continue; }
			auto &ed = edg[id]; int y = ed.from ^ ed.to ^ x;
			dpt[y] = dpt[x] + 1; dst[y] = dst[x] + ed.cost;
			prv[y] = x; pre[y] = id; rot[y] = rot[x] != -1 ? rot[x] : y; 
			doDfs(y); szt[x] += szt[y]; }
		end[x] = (int) ord.size() - 1; }
 
	void doDfsFrom(int x) {
		dpt[x] = 0; dst[x] = type{}; rot[x] = x;
		prv[x] = pre[x] = -1; doDfs(x); }
 
public:
	
	void dfs(int x, bool cle = true) {
		if (prv.empty()) {
			initialize(); }	
		else {
			if (cle) {
				ord.clear(); } }
		doDfsFrom(x); }
 
	void dfsAll(void) {
		initialize();
		for (int x = 0; x < n; ++x) {
			if (dpt[x] == -1) {
				doDfsFrom(x); } } }
};