#include<list>
using namespace std;

// Graph class represents a directed graph
// using adjacency list representation
class Graph
{
    int V;    // No. of vertices

    // Pointer to an array containing
    // adjacency lists
    list<int> *adj;
    list<int> *adj_weight;

    // A recursive function used by DFS
    void DFSUtil(int v, bool visited[], int Dad[],int BW[]);
public:
    Graph(int V);   // Constructor

    // function to add an edge to graph
    void addEdge(int v, int w,int weight);

    // DFS traversal of the vertices
    // reachable from v
    void DFS(int v,int dest);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
    adj_weight = new list<int>[V];
}

void Graph::addEdge(int v, int w,int weight)
{
    adj[v].push_back(w); // Add w to v’s list.
    adj_weight[v].push_back(weight);
}

void Graph::DFSUtil(int v, bool visited[],int Dad[],int BW[])
{
    // Mark the current node as visited and
    // print it
    visited[v] = true;
    cout << v << " ";

    // Recur for all the vertices adjacent
    // to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
      Dad[*i] = v;
      if (!visited[*i])
          DFSUtil(*i, visited,Dad,BW);
    }

}

// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void Graph::DFS(int v,int dest)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    int *Dad = new int[V];
    for (int i = 0; i < V; i++)
        Dad[i] = -1;

    //Dad[v] = v;

    int *BW = new int[V];
    for (int i = 0; i < V; i++)
        BW[i] = -1;


    // Call the recursive helper function
    // to print DFS traversal
    cout<<"MaxBW path is : "<<endl;
    DFSUtil(v, visited,Dad,BW);

    int temp = dest;
    while(Dad[temp]!=-1)
    {
      cout<<Dad[temp]<<"->";
      temp = Dad[temp];
    }
}
