import random as rnd
import pygraphviz as pgv
from copy import deepcopy
from itertools import chain
import time
def find_path(graph, start, end, path,demo=False,visual=None):
    path += [start]
    if demo:
        visual.get_node(start).attr['color'] = 'red'
        visual.draw('demo.png')
        visual.get_node(start).attr['color'] = 'blue'
        time.sleep(3)
    if start == end:
        return path
    if graph[start] == []:
        return None
    for node in graph[start]:
        if node not in path and (len(graph[node]) > 1 or node == end):
            newpath = find_path(graph, node, end, path,demo,visual)
            if newpath: return newpath
    return None

def generate_graph(end,graph,path,max_children=-1,start=0):

    max_children = max_children if max_children > 0 else end/5

    def maieutica():
        last_node = 0 if start==0 else max(chain.from_iterable(graph.values()))
        endpoint = max_children if (end - last_node) > max_children else end - last_node
        return range(last_node+1,rnd.randint(last_node+1,last_node+endpoint+1))

    def taigeto(prob_nephew=0.3):
        """due nodi possono solo connettersi allo stesso figlio se sono 
        adiacenti e non vi sono altri figli 'di mezzo' (i nodi vengono ordinati 
        in ordine di grandezza)"""
        if start == 0 or start in graph[start-1] or graph[start-1] == [] or rnd.random() > prob_nephew: return []
        return [max(graph[start-1])]

    if start in path: 
        for child in graph[start]:
            generate_graph(end,graph, path,max_children,child)
        graph[start] += taigeto()
        path.pop(0)
        if path == []: return graph
    else:
        graph[start] = [child for child in maieutica()]
        path.append(start)
        if path[0] != start: return None
    return generate_graph(end,graph,path,max_children,path[0])

def mono_to_bidirectional(graph,prob_double=0.9,prob_back=0.2):
    g = deepcopy(graph)
    for node in g:
        for child in g[node]:
            if (node == 0 or child not in g[node-1]) and rnd.random() < prob_double:
                if rnd.random() < prob_back/prob_double:
                    graph[node].remove(child)
                graph[child].append(node)
    return graph

def graph_traversable(graph): return find_path(graph,0,max(graph.keys()),[]) is not None

def generate_traversable_graph(num_nodes,bi=False):
    while True:
        graph = generate_graph(num_nodes,{},[]) 
        if bi: graph = mono_to_bidirectional(graph)
        if graph_traversable(graph): return graph
def demo(num_nodes):
    g = generate_traversable_graph(num_nodes,True)
    G = pgv.AGraph(g,directed=True)
    G.layout('dot')
    find_path(g, 0, num_nodes, [],demo=True,visual=G)
        
while True:
    demo(20)
