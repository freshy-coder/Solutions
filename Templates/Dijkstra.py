import heapq
queue = [(0,s-1)] # basically our known area. 0 is distance.
heapq.heapify(queue) # will sort heap by first element which is the distance to start node.
# queue.append((0,1))
distances = [sys.maxsize] * n # distances to each node from start node
distances[s-1] = 0 # distance to start node is just 0
# print(distances)

while (len(queue) > 0):
    curdist,u = heapq.heappop(queue) # take the next shortest current distance and the node
    # the below line will also kind of act as a filter that filters out our known area
    if curdist > distances[u]: continue # if the current distance is more than what's stored in the distances, that's going to screw up below values. skip.
    for v, dist in adjlist[u]: # for all children and the distances to the children
        if distances[v] > distances[u] + dist: # if the distance from start node to the children is greater than the current node to that child,
            distances[v] = distances[u] + dist # update it!
            heapq.heappush(queue, (distances[v], v)) # push the new child in there with their own distance to start node
if distances[e-1] == sys.maxsize: # if there's no distance discovered to the endpoint, then it would still be the original sys.maxsize
    print(-1)
else:
    print(distances[e-1])