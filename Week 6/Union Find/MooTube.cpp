// You can process queries offline! and maybe build a graph in a different order to satisfy the queries
// 1. sort queries by relevance (highest to lowest)
// 2. go through queries. Add all edges with higher relevance, using union-find
// 3. keep track of size, and bingo.