import random as rnd
def find_path(graph, start, end, path):
    path += [start]
    if start == end:
        return path
    if graph[start] == []:
        return None
    for node in graph[start]:
        if node not in path and len(graph[node]) > 2:
            newpath = find_path(graph, node, end, path)
            if newpath: return newpath
    return None

def generate_graph(num_nodes):
    graph = {}
    for node in range(0, num_nodes):
        print('go')
        graph[node] = [child for child in 
                rnd.sample(range(node,num_nodes),(rnd.randint(0,6 if num_nodes - node > 6 else num_nodes - node))) if (child not in graph) or (child == graph[node-1].sort()[0])]
    return graph

def graph_traversable(graph): return find_path(graph,0,max(graph.keys()),[]) is not None

def generate_traversable_graph(num_nodes):
    while True:
        graph = generate_graph(num_nodes) 
        if graph_traversable(graph): return graph

generate_traversable_graph(10)


