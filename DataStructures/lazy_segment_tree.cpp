class LazySegmentTree {
 
public:
 
    struct Node {
        int val; //
 
		Node() : //
			val(numeric_limits<int> :: min()) {}; //
		Node (int _val) : //
			val(_val) {}; //
 
    } *sgt; static const Node nul;
    int siz, _lef, _rig; bool idx1;
    
    void updateLazy(int nod, int lef, int rig) {
        
    }
    
    Node mergeSons(Node son1, Node son2) {
        return Node(max(son1.val, son2.val)); } //
    
    template <typename type>
    void updateNode(int nod, int lef, int rig, type val) {
        sgt[nod] = val; //
        updateLazy(nod, lef, rig); }
    
    template <typename type>
    void _buildTree(int nod, int lef, int rig, type arr[]) {
        if (lef == rig) {
            updateNode(nod, lef, rig, arr[lef]); }
        else {
            int mid = (lef + rig) >> 1,
                lefSon = nod << 1, rigSon = nod << 1 | 1;
            _buildTree(lefSon, lef, mid, arr);
            _buildTree(rigSon, mid + 1, rig, arr);
            sgt[nod] = mergeSons(sgt[lefSon], sgt[rigSon]); } }
    
    template <typename type>
    void _updateTree(int nod, int lef, int rig, type val) {
        if (_lef <= lef and rig <= _rig) {
            updateNode(nod, lef, rig, val); }
        else {
            int mid = (lef + rig) >> 1,
                lefSon = nod << 1, rigSon = nod << 1 | 1;
            updateLazy(lefSon, lef, mid);
            updateLazy(rigSon, mid + 1, rig);
            if (_lef <= mid) {
                _updateTree(lefSon, lef, mid, val); }
            if (mid < _rig) {
                _updateTree(rigSon, mid + 1, rig, val); }
            sgt[nod] = mergeSons(sgt[lefSon], sgt[rigSon]); } }
    
    Node _queryTree(int nod, int lef, int rig) {
        if (_lef <= lef and rig <= _rig) {
            return sgt[nod]; }
        else {
            int mid = (lef + rig) >> 1,
                lefSon = nod << 1, rigSon = nod << 1 | 1;
            updateLazy(lefSon, lef, mid);
            updateLazy(rigSon, mid + 1, rig);
            if (_rig <= mid) {
                return _queryTree(lefSon, lef, mid); }
            if (mid < _lef) {
                return _queryTree(rigSon, mid + 1, rig); }
            return mergeSons(_queryTree(lefSon, lef, mid),
                             _queryTree(rigSon, mid + 1, rig)); } }
    
    int _findFirstKnow(int nod, int lef, int rig, std::function<bool(Node&)> &good) {
        if (lef == rig) {
            return lef; }
        else {
            int mid = (lef + rig) >> 1,
                lefSon = nod << 1, rigSon = nod << 1 | 1;
            updateLazy(lefSon, lef, mid);
            updateLazy(rigSon, mid + 1, rig);
            if (good(sgt[lefSon])) {
                return _findFirstKnow(lefSon, lef, mid, good); }
            else {
                return _findFirstKnow(rigSon, mid + 1, rig, good); } } }
    
    int _findFirst(int nod, int lef, int rig, std::function<bool(Node&)> &good) {
        if (_lef <= lef and _rig <= rig) {
            return good(sgt[nod]) ? _findFirstKnow(nod, lef, rig, good) : -1; }
        else {
            int mid = (lef + rig) >> 1, res = -1,
                lefSon = nod << 1, rigSon = nod << 1 | 1;
            updateLazy(lefSon, lef, mid);
            updateLazy(rigSon, mid + 1, rig);
            if (_lef <= mid) {
                res = _findFirst(lefSon, lef, mid, good); }
            if (mid < _rig and res == -1) {
                res = _findFirst(rigSon, mid + 1, rig, good); }
            return res; } }
    
    int _findLastKnow(int nod, int lef, int rig, std::function<bool(Node&)> &good) {
        if (lef == rig) {
            return lef; }
        else {
            int mid = (lef + rig) >> 1,
                lefSon = nod << 1, rigSon = nod << 1 | 1;
            updateLazy(lefSon, lef, mid);
            updateLazy(rigSon, mid + 1, rig);
            if (good(sgt[rigSon])) {
                return _findLastKnow(rigSon, mid + 1, rig, good); }
            else {
                return _findLastKnow(lefSon, lef, mid, good); } } }
    
    int _findLast(int nod, int lef, int rig, std::function<bool(Node&)> &good) {
        if (_lef <= lef and _rig <= rig) {
            return good(sgt[nod]) ? _findLastKnow(nod, lef, rig, good) : -1; }
        else {
            int mid = (lef + rig) >> 1, res = -1,
                lefSon = nod << 1, rigSon = nod << 1 | 1;
            updateLazy(lefSon, lef, mid);
            updateLazy(rigSon, mid + 1, rig);
            if (mid < _rig) {
                res = _findLast(rigSon, mid + 1, rig, good); }
            if (_lef <= mid and res == -1) {
                res = _findLast(lefSon, lef, mid, good); }
            return res; } }
 
public:
 
    LazySegmentTree(int _siz, bool _idx1 = false) : siz(_siz), idx1(_idx1) {
        sgt = new Node[siz << 2]; }
    
    void resizeTree(int _siz) {
        siz = _siz; }
    
    template <typename type>
    void buildTree(type *arr) {
        _buildTree(1, idx1, siz - 1 + idx1, arr); }
    
    template <typename type>
    void updateTree(int lef, int rig, type val = nul) {
        _lef = lef; _rig = rig;
        _updateTree(1, idx1, siz - 1 + idx1, val); }
    
    Node queryTree(int lef, int rig) {
        _lef = lef; _rig = rig;
        return _queryTree(1, idx1, siz - 1 + idx1); }
    
    int findFirst(int lef, int rig, std::function<bool(Node&)> good) {
        _lef = lef; _rig = rig;
        return _findFirst(1, idx1, siz - 1 + idx1, good); }
    
    int findLast(int lef, int rig, std::function<bool(Node&)> good) {
        _lef = lef; _rig = rig;
        return _findLast(1, idx1, siz - 1 + idx1, good); }
};