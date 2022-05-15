	
#include <cstdio>
#include <algorithm>
#include <vector>
#include <bitset>
#include <deque>
 
const int SIZE = 1e5 + 5;
const int INFI = 0x3f3f3f3f;
 
int nr_nodes, nr_edges, nr_articulation_points, nr_biconnected_components;
struct str{ int node1, node2; }; int lower[SIZE], level[SIZE], node1, node2, nr_critical_edges;
std::vector <int> edge[SIZE], articulation_point; std::vector< std::vector <int> > biconnected_component;
std::bitset <SIZE> marked; std::deque <int> my_stack; std::vector <str> critical_edge;
 
inline void dfs( int root, int node, int node_level, int node_father ) {
    lower[node] = level[node] = node_level; marked[node] = 1;
    my_stack.push_back(node); int nr_sons = 0;
    
    std::vector <int> :: iterator it;
    for( it = edge[node].begin(); it != edge[node].end(); it ++ ) {
        int next_node = *it;
        
        if( next_node == node_father )
            continue;
        
        if( marked[next_node] ) {
            lower[node] = std::min( lower[node], level[next_node] );
            continue;
        } else {
            nr_sons ++;
            dfs( root, next_node, node_level + 1, node );
            lower[node] = std::min( lower[node], lower[next_node] );
            
            if( level[node] < lower[next_node] ) {
                nr_critical_edges ++;
                critical_edge.push_back( {node, next_node} );
            }
            
            if( level[node] <= lower[next_node] ) {
                nr_biconnected_components ++; nr_articulation_points ++; int aux_node;
                biconnected_component.push_back( std::vector <int> (0) );
                
                do {
                    aux_node = my_stack.back();
                    my_stack.pop_back();
                    biconnected_component[nr_biconnected_components - 1].push_back( aux_node );
                } while( aux_node != next_node );
                
                biconnected_component[nr_biconnected_components - 1].push_back(node);
                articulation_point.push_back(node);
            }
        }
    }
    
    if( node == root && nr_sons > 1 ) {
        nr_articulation_points ++;
        articulation_point.push_back(node);
    }
    
    return;
}
 
int main( int argc, const char *argv[] ) {
    
    freopen( "biconex.in" , "r", stdin  );
    freopen( "biconex.out", "w", stdout );
    
    scanf( "%d %d", &nr_nodes, &nr_edges );
    
    for( int i = 1; i <= nr_edges; i ++ ) {
        scanf( "%d %d", &node1, &node2 );
        
        edge[node1].push_back(node2);
        edge[node2].push_back(node1);
    }
    
    for( int i = 1; i <= nr_nodes; i ++ ) {
        if( !marked[i] )
            dfs( i, i, 1, 0 );
    }
    
    int task = 1;
    
    switch( task ) {
        case 1: {
            printf( "%d\n", nr_biconnected_components );
            
            for( int i = 0; i < nr_biconnected_components; i ++ ) {
                std::sort( biconnected_component[i].begin(), biconnected_component[i].end() );
                std::vector <int> :: iterator it;
                
                for( it = biconnected_component[i].begin(); it != biconnected_component[i].end(); it ++ ) {
                    int node = *it;
                    printf( "%d ", node );
                }
                
                printf( "\n" );
            }
            
            break;
        }
        case 2: {
            printf( "%d\n", nr_articulation_points );
            
            std::sort( articulation_point.begin(), articulation_point.end() );
            std::vector <int> :: iterator it;
            
            for( it = articulation_point.begin(); it != articulation_point.end(); it ++ ) {
                int node = *it;
                printf( "%d ", node );
            }
            
            printf( "\n" );
            break;
        }
        case 3: {
            printf( "%d\n", nr_critical_edges );
            std::vector <str> :: iterator it;
            
            for( it = critical_edge.begin(); it != critical_edge.end(); it ++ ) {
                str next_edge = *it;
                printf( "%d %d\n", next_edge.node1, next_edge.node2 );
            }
            
            break;
        }
    }
    
    return 0;
}