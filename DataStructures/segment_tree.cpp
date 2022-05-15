template <class Type>
struct SegmentTree {
    private:
        static const int INF = 0x3f3f3f3f; // TREBUIE MODIFICAT
        Type *left_index, *right_index;
 
        struct tree_node {
            Type minim, maxim, lazy, sum, type;
            tree_node *left_son, *right_son;
 
            tree_node() {
                minim = +INF; maxim = -INF;
                lazy = sum = type = NULL;
                left_son = right_son = NULL;
            }
        } *root = new tree_node;
 
        void reset_tree( tree_node *node ) {
 
            if( node -> left_son  != NULL )
                reset_tree( node -> left_son );
 
            if( node -> right_son != NULL )
                reset_tree( node -> right_son );
 
            if( node != root )
                delete node;
            else {
                node -> left_son = node -> right_son = NULL; node -> lazy = node -> type = NULL;
                node -> minim = +INF; node -> maxim = -INF; node -> sum = NULL;
            }
            return;
        }
 
        void update_lazy( tree_node *node, int left, int right ) {
 
            switch( node -> type ) {
                case 1: { // ADD( left, right, lazy )
                    node -> minim += node -> lazy;
                    node -> maxim += node -> lazy;
                    node -> sum   += node -> lazy * ( right - left + 1 );
 
                    break;
                }
                case 2: { // MUL( left, right, lazy )
                    node -> minim *= node -> lazy;
                    node -> maxim *= node -> lazy;
                    node -> sum   *= node -> lazy;
 
                    break;
                }
                case 3: { // DIV( left, right, lazy )
                    node -> minim /= node -> lazy;
                    node -> maxim /= node -> lazy;
                    node -> sum   /= node -> lazy;
 
                    break;
                }
                case 4: { // SET( left, right, lazy )
                    node -> minim = node -> lazy;
                    node -> maxim = node -> lazy;
                    node -> sum   = node -> lazy * ( right - left + 1 );
 
                    break;
                }
            }
 
            if( left != right ) {
                node -> left_son  -> lazy = node -> lazy; node -> left_son  -> type = node -> type;
                node -> right_son -> lazy = node -> lazy; node -> right_son -> type = node -> type;
            }
 
            node -> lazy = node -> type = 0;
            return;
        }
 
        void update_node( tree_node *node, int left, int right ) {
 
            int middle = left + ( right - left ) / 2;
 
            if( node -> left_son -> lazy  != 0 )
                update_lazy( node -> left_son, left, middle );
 
            if( node -> right_son -> lazy != 0 )
                update_lazy( node -> right_son, middle + 1, right );
 
            node -> minim = std::min( node -> left_son -> minim, node -> right_son -> minim );
            node -> maxim = std::max( node -> left_son -> maxim, node -> right_son -> maxim );
            node -> sum   = node -> left_son -> sum + node -> right_son -> sum;
            return;
        }
 
        void build_tree( tree_node *node, int left, int right ) {
            if( left > right ) return;
 
            if( left == right ) {
                node -> minim = *( left_index + left - 1 );
                node -> maxim = *( left_index + left - 1 );
                node -> sum   = *( left_index + left - 1 );
                return;
            }
 
            node -> left_son = new tree_node;
            node -> right_son = new tree_node;
 
            int middle = left + ( right - left ) / 2;
 
            build_tree( node -> left_son, left, middle );
            build_tree( node -> right_son, middle + 1, right );
 
            update_node( node, left, right );
            return;
        }
 
        void add_value( tree_node *node, int left, int right, int start, int finish, Type value ) {
 
            if( node -> lazy != 0 )
                update_lazy( node, left, right );
 
            if( left > right || left > finish || start > right )
                return;
 
            if( start <= left && right <= finish ) {
                node -> minim += value;
                node -> maxim += value;
                node -> sum   += value * ( right - left + 1 );
 
                if( left != right ) {
                    node -> left_son  -> lazy = node -> left_son  -> type != node -> type ? value : node -> left_son  -> lazy + value;
                    node -> right_son -> lazy = node -> right_son -> type != node -> type ? value : node -> right_son -> lazy + value;
                    node -> left_son  -> type = node -> right_son -> type = 1;
                }
 
                return;
            }
 
            int middle = left + ( right - left ) / 2;
 
            add_value( node -> left_son, left, middle, start, finish, value );
            add_value( node -> right_son, middle + 1, right, start, finish, value );
 
            update_node( node, left, right );
            return;
        }
 
        void mul_value( tree_node *node, int left, int right, int start, int finish, Type value ) {
 
            if( node -> lazy != 0 )
                update_lazy( node, left, right );
 
            if( left > right || left > finish || start > right )
                return;
 
            if( start <= left && right <= finish ) {
                node -> minim *= value;
                node -> maxim *= value;
                node -> sum   *= value;
 
                if( left != right ) {
                    node -> left_son  -> lazy = node -> left_son  -> type != node -> type ? value : node -> left_son  -> lazy * value;
                    node -> right_son -> lazy = node -> right_son -> type != node -> type ? value : node -> right_son -> lazy * value;
                    node -> left_son  -> type = node -> right_son -> type = 2;
                }
 
                return;
            }
 
            int middle = left + ( right - left ) / 2;
 
            mul_value( node -> left_son, left, middle, start, finish, value );
            mul_value( node -> right_son, middle + 1, right, start, finish, value );
 
            update_node( node, left, right );
            return;
        }
 
        void div_value( tree_node *node, int left, int right, int start, int finish, Type value ) {
 
            if( node -> lazy != 0 )
                update_lazy( node, left, right );
 
            if( left > right || left > finish || start > right )
                return;
 
            if( start <= left && right <= finish ) {
                node -> minim *= value;
                node -> maxim *= value;
                node -> sum   *= value;
 
                if( left != right ) {
                    node -> left_son  -> lazy = node -> left_son  -> type != node -> type ? value : node -> left_son  -> lazy * value;
                    node -> right_son -> lazy = node -> right_son -> type != node -> type ? value : node -> right_son -> lazy * value;
                    node -> left_son  -> type = node -> right_son -> type = 3;
                }
 
                return;
            }
 
            int middle = left + ( right - left ) / 2;
 
            div_value( node -> left_son, left, middle, start, finish, value );
            div_value( node -> right_son, middle + 1, right, start, finish, value );
 
            update_node( node, left, right );
            return;
        }
 
        void set_value( tree_node *node, int left, int right, int start, int finish, Type value ) {
 
            if( node -> lazy != 0 )
                update_lazy( node, left, right );
 
            if( left > right || left > finish || start > right )
                return;
 
            if( start <= left && right <= finish ) {
                node -> minim = value;
                node -> maxim = value;
                node -> sum   = value * ( right - left + 1 );
 
                if( left != right ) {
                    node -> left_son -> lazy = node -> right_son -> lazy = value;
                    node -> left_son -> type = node -> right_son -> type = 4;
                }
 
                return;
            }
 
            int middle = left + ( right - left ) / 2;
 
            set_value( node -> left_son, left, middle, start, finish, value );
            set_value( node -> right_son, middle + 1, right, start, finish, value );
 
            update_node( node, left, right );
            return;
        }
 
        Type get_min( tree_node *node, int left, int right, int start, int finish ) {
            Type value1, value2, value3; value3 = INF;
 
            if( node -> lazy != 0 )
                update_lazy( node, left, right );
 
            if( left > right || left > finish || start > right )
                return value3;
 
            if( start <= left && right <= finish )
                return node -> minim;
 
            int middle = left + ( right - left ) / 2;
 
            value1 = get_min( node -> left_son, left, middle, start, finish );
            value2 = get_min( node -> right_son, middle + 1, right, start, finish );
 
            value3 = std::min( value1, value2 );
            return value3;
        }
 
        Type get_max( tree_node *node, int left, int right, int start, int finish ) {
            Type value1, value2, value3; value3 = -INF;
 
            if( node -> lazy != 0 )
                update_lazy( node, left, right );
 
            if( left > right || left > finish || start > right )
                return value3;
 
            if( start <= left && right <= finish )
                return node -> maxim;
 
            int middle = left + ( right - left ) / 2;
 
            value1 = get_max( node -> left_son, left, middle, start, finish );
            value2 = get_max( node -> right_son, middle + 1, right, start, finish );
 
            value3 = std::max( value1, value2 );
            return value3;
        }
 
        Type get_sum( tree_node *node, int left, int right, int start, int finish ) {
            Type value1, value2, value3; value3 = 0;
 
            if( node -> lazy != 0 )
                update_lazy( node, left, right );
 
            if( left > right || left > finish || start > right )
                return value3;
 
            if( start <= left && right <= finish )
                return node -> sum;
 
            int middle = left + ( right - left ) / 2;
 
            value1 = get_sum( node -> left_son, left, middle, start, finish );
            value2 = get_sum( node -> right_son, middle + 1, right, start, finish );
 
            value3 = value1 + value2;
            return value3;
        }
 
    public:
        void build_tree( Type *start_pos, Type *finish_pos ) {
            reset_tree( root ); left_index = start_pos; right_index = finish_pos;
            build_tree( root, 1, right_index - left_index );
            return;
        }
 
        void add_value( Type *start_pos, Type *finish_pos, Type value ) {
            add_value( root, 1, right_index - left_index, start_pos - left_index + 1, finish_pos - left_index, value );
            return;
        }
 
        void mul_value( Type *start_pos, Type *finish_pos, Type value ) {
            mul_value( root, 1, right_index - left_index, start_pos - left_index + 1, finish_pos - left_index, value );
            return;
        }
 
        void div_value( Type *start_pos, Type *finish_pos, Type value ) {
            div_value( root, 1, right_index - left_index, start_pos - left_index + 1, finish_pos - left_index, value );
            return;
        }
 
        void set_value( Type *start_pos, Type *finish_pos, Type value ) {
            set_value( root, 1, right_index - left_index, start_pos - left_index + 1, finish_pos - left_index, value );
            return;
        }
 
        Type get_min( Type *start_pos, Type *finish_pos ) {
            return get_min( root, 1, right_index - left_index, start_pos - left_index + 1, finish_pos - left_index );
        }
 
        Type get_max( Type *start_pos, Type *finish_pos ) {
            return get_max( root, 1, right_index - left_index, start_pos - left_index + 1, finish_pos - left_index );
        }
 
        Type get_sum( Type *start_pos, Type *finish_pos ) {
            return get_sum( root, 1, right_index - left_index, start_pos - left_index + 1, finish_pos - left_index );
        }
};