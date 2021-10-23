# Boruvka's algorithm to find Minimum Spanning
# Tree of a given connected, undirected and weighted graph

from collections import defaultdict

class Graph:

	def __init__(self,vertices):
		self.V= vertices 
		self.graph = [] 

	def addEdge(self,u,v,w):
		self.graph.append([u,v,w])

	def find(self, parent, i):
		if parent[i] == i:
			return i
		return self.find(parent, parent[i])
		
	def union(self, parent, rank, x, y):
		xroot = self.find(parent, x)
		yroot = self.find(parent, y)

		if rank[xroot] < rank[yroot]:
			parent[xroot] = yroot
		elif rank[xroot] > rank[yroot]:
			parent[yroot] = xroot
		
		else :
			parent[yroot] = xroot
			rank[xroot] += 1

	def boruvkaMST(self):
		parent = []; rank = [];

		cheapest =[]

		numTrees = self.V
		MSTweight = 0

		for node in range(self.V):
			parent.append(node)
			rank.append(0)
			cheapest =[-1] * self.V
	
		while numTrees > 1:

			for i in range(len(self.graph)):

				u,v,w = self.graph[i]
				set1 = self.find(parent, u)
				set2 = self.find(parent ,v)

				if set1 != set2:	
					
					if cheapest[set1] == -1 or cheapest[set1][2] > w :
						cheapest[set1] = [u,v,w]

					if cheapest[set2] == -1 or cheapest[set2][2] > w :
						cheapest[set2] = [u,v,w]
						
			for node in range(self.V):

				if cheapest[node] != -1:
					u,v,w = cheapest[node]
					set1 = self.find(parent, u)
					set2 = self.find(parent ,v)

					if set1 != set2 :
						MSTweight += w
						self.union(parent, rank, set1, set2)
						print ("Edge %d-%d with weight %d included in MST" % (u,v,w))
						numTrees = numTrees - 1
			
			cheapest =[-1] * self.V

		print ("Weight of MST is %d" % MSTweight)