enum visited
{
    UNVISITED,
    VISITED
};

class Graph
{
private:
    int num_vertex;         // Number of vertices of the graph. (i.e nodes)
    int num_edge;           // Number of edges of the graph
    int **adjacency_matrix; // A matrix to store adjacency relations. [n][m] is akin to asking is there an edge starting from n and ends at m.
    int *mark;              // An array to store whether the relative node is visited or not
public:
    Graph(int n); // Constructor that gets num_vertex (n) as input
    ~Graph();     // Destructor
    int n();      // Returns number of vertices (i.e num_vertex)
    int e();      // Returns number of edges (i.e. num_edge)
};