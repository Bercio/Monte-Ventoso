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

def generate_graph(end,graph,start):

    def maieutica():
        last_node = 0 if start==0 else max(chain.from_iterable(graph.values()))
        endpoint = 4 if (end - last_node) > 4 else end - last_node
        return range(last_node+1,rnd.randint(last_node+1,last_node+endpoint+1))

    def taigeto(child):
        """due nodi possono solo connettersi allo stesso figlio se sono 
        adiacenti e non vi sono altri figli 'di mezzo' (i nodi vengono ordinati 
        in ordine di grandezza)"""
        return graph[start-1] != [] and child == max(graph[start-1])

    graph[start] = [child for child in maieutica()] 
    if graph[start] == []: return None 
    for child in graph[start]:
        generate_graph(end, graph, child)
    return graph

def graph_traversable(graph): return find_path(graph,0,max(graph.keys()),[]) is not None

def generate_traversable_graph(num_nodes):
    while True:
        graph = generate_graph(num_nodes,{},0) 
        if graph_traversable(graph): return graph



