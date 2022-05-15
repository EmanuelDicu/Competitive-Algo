	template <class type>
class MaxFlow {
private:
    static constexpr type INF = std::numeric_limits<type> :: max() / 2;
    static constexpr long double EPS = 1e-6;
    
    static inline int cmp(const type x) {
        if (fabs(x) < EPS)
            return 0;
        return x < 0 ? -1 : 1;
    }
    
    struct edge {
        int x, y; type flo, cap;
        
        edge(int _x, int _y, type _cap) :
        x(_x), y(_y), cap(_cap), flo(0) {};
    };
    
    std::vector<bool> oki; std::deque<int> que;
    std::vector<edge> lst; std::vector<type> dis;
    std::vector<int> ptx; std::vector<std::vector<int>> edg;
    
    bool bfs(const int src, const int dst, type cap) {
        std::fill(dis.begin(), dis.end(), (type)INF); dis[src] = 0;
        
        for (que.assign(1, src); que.size() and dis[dst] == INF; que.pop_front()) {
            int x = que.front();
            if (x == dst) continue;
            
            for (int it : edg[x]) {
                int y = lst[it].y;
                
                if (cmp(lst[it].cap - lst[it].flo - cap) < 0)
                    continue;
                if (dis[y] > dis[x] + 1) {
                    dis[y] = dis[x] + 1;
                    que.push_back(y);
                }
            }
        }
        
        return dis[dst] != INF;
    }
    
    bool dfs(const int x, const int dst, type cap) {
        if (x == dst) return cap;
        
        for (; ptx[x] < edg[x].size(); ++ptx[x]) {
            int it = edg[x][ptx[x]], y = lst[it].y;
            
            if (cmp(dis[y] - dis[x] - 1) != 0 or
                cmp(lst[it].cap - lst[it].flo - cap) < 0)
                continue;
            
            if (dfs(y, dst, cap)) {
                lst[it].flo += cap;
                lst[it ^ 1].flo -= cap;
                return true;
            }
        }
        
        return false;
    }
    
    void fill(const int x, std::vector<int> &ans) {
        oki[x] = true;
        
        for (int it : edg[x]) {
            int y = lst[it].y;
            
            if (cmp(lst[it].cap - lst[it].flo) and !oki[y])
                fill(y, ans);
        }
    }
public:
    MaxFlow(int sz) {
        edg.resize(sz); dis.resize(sz);
        oki.resize(sz); ptx.resize(sz);
    }
    
    inline void addUndirectedEdge(const int x, const int y, const type c) {
        edg[x].push_back((int) lst.size()); lst.push_back(edge(x, y, c));
        edg[y].push_back((int) lst.size()); lst.push_back(edge(y, x, c));
    }
    
    inline void addDirectedEdge(const int x, const int y, const type c) {
        edg[x].push_back((int) lst.size()); lst.push_back(edge(x, y, c));
        edg[y].push_back((int) lst.size()); lst.push_back(edge(y, x, 0));
    }
    
    type getMaxFlow(const int src, const int dst) {
        type lim = INF;
        for (int i = 0; i < lst.size(); ++i) {
            lst[i].flo = 0;
            lim = std::max(lim, lst[i].cap);
        }
        
        type ans = 0;
        for (; cmp(lim); ) {
            if (!bfs(src, dst, lim)) {
                lim /= 2;
                continue;
            }
            
            std::fill(ptx.begin(), ptx.end(), 0);
            while (dfs(src, dst, lim))
                ans += lim;
        }
        
        return ans;
    }
    
    type getMinCut(const int src, const int dst, std::vector<int> &ans) {
        std::fill(oki.begin(), oki.end(), false);
        type sol = getMaxFlow(src, dst);
        
        fill(src, ans); ans.clear();
        for (int i = 0; i < edg.size(); ++i)
            if (oki[i]) ans.push_back(i);
        
        return sol;
    }
};