#include <iostream>
#include <list>
#include <stack>
using namespace std;

// Class representing a graph
class Graph {
    int vertices;                 // Number of vertices in the graph
    list<int>* adjacencyList;     // Adjacency list to store edges
    void fillStackWithVertices(int v, bool visited[], stack<int>& Stack);  // Helper function for DFS
    void DepthFirstSearch(int v, bool visited[]);  // Depth-first search traversal

public:
    Graph(int V);                 // Constructor
    void addEdge(int v, int w);   // Function to add an edge to the graph
    void printStronglyConnectedComponents();  // Function to print strongly connected components
    Graph getTranspose();         // Function to get the transpose of the graph
};

// Constructor to initialize the graph
Graph::Graph(int V) {
    this->vertices = V;
    adjacencyList = new list<int>[V];  // Create an array of adjacency lists
}

// Depth-first search traversal
void Graph::DepthFirstSearch(int v, bool visited[]) {
    visited[v] = true;  // Mark the current vertex as visited
    cout << v << " ";   // Print the current vertex

    // Recursive for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adjacencyList[v].begin(); i != adjacencyList[v].end(); ++i)
        if (!visited[*i])
            DepthFirstSearch(*i, visited);
}

// Function to get the transpose of the graph
Graph Graph::getTranspose() {
    Graph transposedGraph(vertices);  // Create a new graph with the same number of vertices
    for (int v = 0; v < vertices; v++) {
        list<int>::iterator i;
        for (i = adjacencyList[v].begin(); i != adjacencyList[v].end(); ++i) {
            transposedGraph.adjacencyList[*i].push_back(v);  // Add reverse edges to the transposed graph
        }
    }
    return transposedGraph;
}

// Function to add an edge to the graph
void Graph::addEdge(int v, int w) {
    adjacencyList[v].push_back(w);  // Add w to v list
}

// Helper function for DFS to fill the stack with vertices
// this importan for the second pass of the DFS
void Graph::fillStackWithVertices(int v, bool visited[], stack<int>& Stack) {
    visited[v] = true;  // Mark the current vertex as visited

    // Recursive call for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adjacencyList[v].begin(); i != adjacencyList[v].end(); ++i)
        if (!visited[*i])
            fillStackWithVertices(*i, visited, Stack);

    // All vertices that are reachable from v are processed by now, so push v to Stack
    Stack.push(v);
}

// Function to print strongly connected components
void Graph::printStronglyConnectedComponents() {
    stack<int> Stack;  // Create a stack to store vertices

    bool* visited = new bool[vertices];  // Mark all the vertices as not visited
    for (int i = 0; i < vertices; i++)
        visited[i] = false;

    // Fill vertices in stack according to their finishing times
    for (int i = 0; i < vertices; i++)
        if (visited[i] == false)
            fillStackWithVertices(i, visited, Stack);

    // Create a reversed graph
    Graph transposedGraph = getTranspose();

    // Mark all the vertices as not visited for the second DFS
    for (int i = 0; i < vertices; i++)
        visited[i] = false;

    //  process all vertices in order defined by Stack
    while (Stack.empty() == false) {
        int v = Stack.top();
        Stack.pop();

        if (visited[v] == false) {
            transposedGraph.DepthFirstSearch(v, visited);  // Print strongly connected component
            cout << endl;
        }
    }
}

int main() {
    Graph graph(7);  // Create a graph 
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
    graph.addEdge(5, 3);
    graph.addEdge(5, 6);

    cout << "Strongly Connected Components:\n";
    graph.printStronglyConnectedComponents();  // Print the strongly connected components of the graph
    return 0;
}

