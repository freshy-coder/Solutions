import time
start_time = time.time()

# BFS is effective at finding distances of all nodes to one node in undirected nonweighted
# how can we precalculate such information?
# bidirecitonal graphs add edges to adj two times, each time reversing order
# another good observation: we can find some sort of precomputation and go through every single node to make use of it

fin = open ('piggyback.in', 'r')
fout = open ('piggyback.out', 'w')

b, e, p, n, m = [int(x) for x in fin.readline().split()]
adj = [[] for i in range(n+1)]
for i in range(m):
    line = [int(x) for x in fin.readline().split()]
    adj[line[0]].append(line[1])
    adj[line[1]].append(line[0])

import sys
import heapq

def bfs (s):
    queue = [(0,s)] # basically our known area. 0 is distance.
    heapq.heapify(queue) # will sort heap by first element which is the distance to start node.
    # queue.append((0,1))
    distances = [sys.maxsize] * (n+1) # distances to each node from start node
    distances[s] = 0 # distance to start node is just 0
    # print(distances)

    while (len(queue) > 0):
        curdist,u = heapq.heappop(queue) # take the next shortest current distance and the node
        # the below line will also kind of act as a filter that filters out our known area
        if curdist > distances[u]: continue # if the current distance is more than what's stored in the distances, that's going to screw up below values. skip.
        for v in adj[u]: # relax neighbors
            if distances[v] > distances[u] + 1:
                distances[v] = distances[u] + 1
                heapq.heappush(queue, (distances[v], v)) # push the new child in there with their own distance to start node
                # print('from', u, 'to', v, queue)
    # print(distances)
    # print(adj)
    return distances

bfsRes = []
for node in [1,2,n]: # need to find distances of other nodes to 1, 2, and the last node
    bfsRes.append(bfs(node))
toOne = bfsRes[0]
toTwo = bfsRes[1]
toN = bfsRes[2]

possibleEnergy = []
for node in range(1, n): # try to convene at every node possible

    if sys.maxsize not in [toN[node], toTwo[node] , toOne[node]]: # check that this node is reachable by all others
        noPiggy = toTwo[node]*e + toOne[node]*b + toN[node]*(b+e)
        piggy = toTwo[node]*e + toOne[node]*b + toN[node]*(p)
        possibleEnergy.append(min(noPiggy, piggy))
print(min(possibleEnergy), file = fout)