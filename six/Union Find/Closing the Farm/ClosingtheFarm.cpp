// You should immediately get the notion of processing backwards and seeing if the farm's open at each point
// to confirm that, you know that the end result will be all farms are closed. That is, when going backwards, outside of the barn that's being opened in reverse at that moment and barns you already opened, there are no other open barns. So you can go backwards.
// then its simple U-F:
// to reopen a barn, union all of its nodes (store neighbors DFS) 