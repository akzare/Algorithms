# -*- coding: utf-8 -*-
"""
A Hamiltonian path, also called a Hamilton path, is a graph path between two vertices of a graph that visits each vertex exactly once. 
If a Hamiltonian path exists whose endpoints are adjacent, then the resulting graph cycle is called a Hamiltonian cycle (or Hamiltonian cycle).
"""

# A class to represent a graph object
class Graph:
 
    # Constructor
    def __init__(self, edges, N):
 
        # A list of lists to represent an adjacency list
        self.adjList = [[] for _ in range(N)]
 
        # add edges to the undirected graph
        for (src, dest) in edges:
            self.adjList[src].append(dest)
            self.adjList[dest].append(src)
 
 
def printAllHamiltonianPaths(g, v, visited, path, N):
 
    # if all the vertices are visited, then the Hamiltonian path exists
    if len(path) == N:
        # print the Hamiltonian path
        print(path)
        return
 
    # Check if every edge starting from vertex `v` leads to a solution or not
    for w in g.adjList[v]:
 
        # process only unvisited vertices as the Hamiltonian
        # path visit each vertex exactly once
        if not visited[w]:
            visited[w] = True
            path.append(w)
 
            # check if adding vertex `w` to the path leads to the solution or not
            printAllHamiltonianPaths(g, w, visited, path, N)
 
            # backtrack
            visited[w] = False
            path.pop()
 
 
if __name__ == '__main__':
    # Test cases
    # consider a complete graph having 4 vertices
    edges = [(0, 1), (0, 2), (0, 3), (1, 2), (1, 3), (2, 3)]
    # edges = [(1, 2), (2, 3), (2, 4), (3, 4), (3, 5)]
    # edges = [(1, 4), (1, 2), (2, 3), (2, 5), (3, 6)]
    # edges = [(1, 4), (1, 2), (2, 3), (2, 5), (3, 6),(5,6)]
    # total number of nodes in the graph
    N = 4
 
    # build a graph from the given edges
    g = Graph(edges, N)
 
    # starting node
    start = 0
 
    # add starting node to the path
    path = [start]
 
    # mark the start node as visited
    visited = [False] * N
    visited[start] = True
 
    printAllHamiltonianPaths(g, start, visited, path, N)
