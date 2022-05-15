class PositionTreap {
private:
    static const int SIZE = 400005;
    
    static const int MOD1 = 1000000007;
    static const int MOD2 = 1000000009;
    
    static const int CNS1 = 29;
    static const int CNS2 = 32;
    
    bool oki;
    std::pair<int, int> hash[SIZE];
    
    struct Treap {
        int key, size, priority; bool lazy;
        std::pair<int, int> hash; Treap *left, *right;
        
        Treap(): key(0), size(0), priority(INT_MIN), lazy(false),
        hash(std::make_pair(0, 0)), left(NULL), right(NULL) {};
        
        Treap(int _key, int _priority, Treap* _left, Treap* _right):
            key(_key), priority(_priority), left(_left), right(_right), size(1), lazy(false) {};
    } *root, *nil;
    
    void update(Treap* node) {
        node -> size = 1 + node -> left -> size + node -> right -> size;
        
        if (node -> lazy) {
            node -> lazy = false;
            std::swap(node -> left, node -> right);
            
            if (node -> left  != nil)
                node -> left -> lazy  ^= true;
            if (node -> right != nil)
                node -> right -> lazy ^= true;
        }
        
        if (oki) {
            node -> hash.first  = (int) ((1LL * node -> left -> hash.first +
                                          1LL * hash[node -> left -> size + 0].first  * node -> key +
                                          1LL * hash[node -> left -> size + 1].first  * node -> right -> hash.first ) % MOD1);
            
            node -> hash.second = (int) ((1LL * node -> left -> hash.second +
                                          1LL * hash[node -> left -> size + 0].second * node -> key +
                                          1LL * hash[node -> left -> size + 1].second * node -> right -> hash.second) % MOD2);
        }
        
        return;
    }
    
    std::pair<Treap*, Treap*> split(Treap* node, int position) {
        if (node == nil)
            return std::make_pair(nil, nil);
        update(node);
        
        if (position == node -> left -> size + 1) {
            std::pair<Treap*, Treap*> split(node, node -> right);
            split.first -> right = nil; update(split.first);
            return split;
        }
        
        if (position < node -> left -> size + 1) {
            std::pair<Treap*, Treap*> _split(split(node -> left, position));
            node -> left = _split.second; _split.second = node; update(node);
            return _split;
        }
        else {
            std::pair<Treap*, Treap*> _split(split(node -> right, position - node -> left -> size - 1));
            node -> right = _split.first; _split.first = node; update(node);
            return _split;
        }
            
        return std::make_pair(nil, nil);
    }
    
    Treap* join(Treap* left, Treap* right) {
        if (left  == nil) return right;
        if (right == nil) return left;
        update(left); update(right);
        
        if (left -> priority > right -> priority) {
            left -> right = join(left -> right, right);
            update(left); return left;
        }
        else {
            right -> left = join(left, right -> left);
            update(right); return right;
        }
        
        return nil;
    }
    
    Treap* insert(Treap* node, int position, const int key, const int priority) {
        if (node == nil)
            return node = new Treap(key, priority, nil, nil );
        update(node);
        
        if (node -> priority <= priority) {
            std::pair<Treap*, Treap*> _split(split(node, position - 1));
            node = new Treap(key, priority, _split.first, _split.second);
            update(node); return node;
        }
        
        if (position <= node -> left -> size + 1)
            node -> left  = insert(node -> left, position, key, priority);
        else
            node -> right = insert(node -> right, position - node -> left -> size - 1, key, priority);
        
        update(node);
        return node;
    }
    
    Treap* erase(Treap* node, int position) {
        if (node == nil)
            return nil;
        update(node);
        
        if (node -> left -> size + 1 == position)
            return node = join(node -> left, node -> right);
        
        if (position <= node -> left -> size + 1)
            node -> left  = erase(node -> left, position);
        else
            node -> right = erase(node -> right, position - node -> left -> size - 1);
        
        update(node);
        return node;
    }
    
    int find(Treap* node, int position) {
        if (node == nil)
            return -1;
        update(node);
        
        if (node -> left -> size + 1 == position)
            return node -> key;
        
        if (position <= node -> left -> size + 1)
            return find(node -> left, position);
        else
            return find(node -> right, position - node -> left -> size - 1);
        
        return -1;
    }
    
    void print(Treap* node) {
        if(node == nil)
            return;
        update(node);
        
        print(node -> left);
        out << node -> key << " ";
        print(node -> right);
        
        return;
    }
    
    std::tuple<Treap*, Treap*, Treap*> split3(Treap* node, const int left, const int right) {
        std::pair<Treap*, Treap*> split2(split(node, right));
        std::pair<Treap*, Treap*> split1(split(split2.first, left - 1));
        return std::make_tuple(split1.first, split1.second, split2.second);
    }
    
    Treap* join3(Treap* node1, Treap* node2, Treap* node3) {
        return join(node1, join(node2, node3));
    }
public:
    PositionTreap(bool _oki = false) : oki(_oki) {
        srand(unsigned(time(0)));
        
        root = nil = new Treap();
        nil -> left = nil -> right = nil;
        root -> left = root -> right = nil;
        
        if (oki) {
            hash[0] = std::make_pair(1, 1);
            for (int i = 1; i < SIZE; ++i)
                hash[i] = std::make_pair((1LL * hash[i - 1].first  * CNS1) % MOD1,
                                         (1LL * hash[i - 1].second * CNS2) % MOD2);
        }
    }
    
    void insert(const int key, const int position) {
        root = insert(root, position, key, rand() * rand());
        return;
    }
    
    void erase(const int position) {
        root = erase(root, position);
        return;
    }
    
    void erase(const int left, const int right) {
        std::tuple<Treap*, Treap*, Treap*> _split(split3(root, left, right));
        root = join(std::get<0>(_split), std::get<2>(_split));
        return;
    }
    
    void reverse(const int left, const int right) {
        std::tuple<Treap*, Treap*, Treap*> _split(split3(root, left, right)); std::get<1>(_split) -> lazy = true;
        root = join3(std::get<0>(_split), std::get<1>(_split), std::get<2>(_split));
        return;
    }
    
    int find(const int position) {
        return find(root, position);
    }
    
    int size(void) {
        return root -> size;
    }
    
    void print(void) {
        print(root);
        out << "\n";
        return;
    }
}