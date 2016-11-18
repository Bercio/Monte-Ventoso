import random as rnd
from itertools import chain
def find_path(graph, start, end, path):
    path += [start]
    if start == end:
        return path
    if graph[start] == []:
        return None
    for node in graph[start]:
        if node not in path and (len(graph[node]) > 1 or node == end):
            newpath = find_path(graph, node, end, path)
            if newpath: return newpath
    return None

def generate_graph(num_nodes):

    def maieutica(node):
        endpoint = 6 if (num_nodes - node) > 6 else num_nodes - node
        return rnd.sample(range(node+1,node+endpoint), rnd.randint(0,endpoint -1))

    def taigeto(child, node,graph):
        """due nodi possono solo connettersi allo stesso figlio se sono 
        adiacenti e non vi sono altri figli 'di mezzo' (i nodi vengono ordinati 
        in ordine di grandezza)"""
        return child not in chain.from_iterable(graph.values()) or (graph[node-1] != [] and child == max(graph[node-1]))

    graph = {}
    for node in range(0, num_nodes):
        graph[node] = [child for child in maieutica(node) if taigeto(child,node,graph)]
    return graph

def graph_traversable(graph): return find_path(graph,0,max(graph.keys()),[]) is not None

def generate_traversable_graph(num_nodes):
    while True:
        graph = generate_graph(num_nodes) 
        if graph_traversable(graph): return graph



