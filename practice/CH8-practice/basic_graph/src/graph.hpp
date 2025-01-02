enum visited
{
    UNVISITED,
    VISITED
};

class Graph
{
    // Edge weights are integer values
    // Weight of 0 indicates vertices are not connected
    // vertices has integer IDs. Thus we can addres them with integer numbers starting from 0
private:
    int id;                 // ID of the graph object. For debugging purposes
    int num_vertex;         // Number of vertices of the graph. (i.e nodes)
    int num_edge;           // Number of edges of the graph
    int **adjacency_matrix; // A matrix to store adjacency relations. [n][m] is akin to asking is there an edge starting from n and ends at m.
    int *mark;              // An array to store whether the relative node is visited or not
public:
    Graph();                              // Default constructor
    Graph(int id, int n);                 // Constructor that gets num_vertex (n) as input
    Graph(const Graph &other);            // Copy constructor
    Graph &operator=(const Graph &other); // Assignment operator

    ~Graph();                            // Destructor
    int n() const;                       // Returns number of vertices (i.e num_vertex)
    int e() const;                       // Returns number of edges (i.e. num_edge)
    int first(int v) const;              // Returns the first neighbor of vertex v, if no neighbour is found returns -1
    int next(int v, int p_v) const;      // Returns the next neighbor of vertex v after vertex p_v
    void setEdge(int v1, int v2, int w); // Connect vertices v1 & v2 with weight w
    void delEdge(int v1, int v2);        // Disconnect v1 and v2
    bool isEdge(int v1, int v2) const;   // Is vertex v1 & v2 are connected ?
    int weight(int v1, int v2) const;    // Return the edge weight between v1 & v2. (note that returns 0 if no edge)
    int getMark(int v1) const;           // Returns the mark of vertex v1
    void setMark(int v1, int val);       // Set mark of the vertex v1 (UNVISITED:0, VISITED:1)
    void clearMark();                    // Clear marks of the all vertices to UNVISITED:0
    void printAdjacencyMatrix() const;   // Prints adjacency matrix
    void printMarkMatrix() const;        // Prints mark matrix
};
