// The parts where you need to do work are
// marked further below in the code with "TODO".
// todo code starts on line 135.

/*
from the instructions on coursera:

We can use disjoint sets to implement a breadth first traversal. The code below 
implements a bfs() method that implements a breadth first traversal that also 
measures the distance (in number of edges) from each vertex to the vertex serving 
as the source of the traversal. 
BREADTH FIRST TRAVERSAL

This algorithm uses disjoint sets to keep track of two sets. All of the vertices 
are initialized to be singletons (the only element of their set). The bfs(int i, 
int n, int m, int edges[][2]) method is called with the index i of the source 
vertex of the traversal. This vertex is assigned a distance of zero, and this 
vertex index i will be a member of the set of all processed vertices (vertices 
that the breadth first traversal has visited and measured an edge distance).
i = index of the source vertex of the traversal, or the vertex to traverse from
n = total number of vertexes
m = total number of edges

We then iterate. (We iterate no more than m times (which is the number edges). 
If the graph was, for example, 
a long line of edges and the start vertex was at one end, then each iteration 
would process only one edge. For most graphs, we will probably need fewer iterations 
so we have a conditional break later in the loop.) Each of these iterations adds a 
layer of breadth to the traversal.

In each iteration, an inner loop cycles through all of the edges in the edge list. 
If any edge has one and only one vertex in the already-processed set (the same set 
as the start vertex i) then we add its other vertex to the current frontier set.

After the inner loop has iterated through all of the edges, the frontier set 
contains all of the vertices one edge away from all of the already-processed edges. 
When each of these vertices is added to the frontier set, we assign its distance to 
be the current loop counter of the outer loop. Since all of the vertices one edge 
away from the already-processed set of vertices have now been found (and their 
distance has been recorded), these new vertices can now be added to the 
already-processed set with a union operation. Then the outer loop can increment 
the edge distance counter and the next frontier of new vertices can be found.

In the code below, there are two conditions that need to be filled in 
(these are the todo).
Each edge (say edge j) has two vertices: edge[j][0] and edge[j][1]. 
The condition needs to 
determine if one of these vertices is in the already processed set and the other 
is not, and if so, then the one that is not should be added to the frontier set.

frontier set:
https://medium.com/tebs-lab/breadth-first-search-and-depth-first-search-4310f3bf8416
To implement these two algorithms, we need to define two terms, the frontier and the
explored list. The frontier is the list of nodes we know about, but have not visited. 
The explored list is the list of nodes that we’ve already visited. We use the frontier 
to track of which nodes will be explored next — the ordering of the frontier controls
which search algorithm we’re performing. The explored list is used to prevent us from
searching nodes we’ve already explored — and thus prevents us from searching in an
infinite loop if there are cycles.
Because there might be multiple paths to any particular node, the frontier may end up 
with multiple entries for a single node. The explored list, however, will always contain 
only one entry per node — once we explore a node we ignore it if we encounter it again in 
the future. Thus the explored list is actually a set. To be “explored” a node simply needs 
to have had all of its children added to the frontier.
 
Your job is to figure out the condition using the variables defined, to determine 
if the appropriate vertex is a member (or not a member) of the already-processed 
set.

There are two conditions, line 186 and line 205. This is what you have to fix.
*/

/*
https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/

Starting from the root, all the nodes at a particular level are visited first and 
then the nodes of the next level are traversed till all the nodes are visited.

To do this a queue is used. All the adjacent unvisited nodes of the current level 
are pushed into the queue and the nodes of the current level are marked visited 
and popped from the queue.
*/

#include <iostream>
#include <string>

// Note: You must not change the definition of DisjointSets here.
class DisjointSets {
public:
  int s[256];
  int distance[256];

  DisjointSets() {
    for (int i = 0; i < 256; i++) 
      s[i] = distance[i] = -1;
  }

  int find(int i) {  
    return s[i] < 0 ? i : find(s[i]); 
  }

  void dsunion(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
      s[root_i] = root_j;
    }
  }

  void bfs(int i, int n, int m, int edges[][2]);
};

/*
 * In the function below, there are two conditions
 * that need to be programmed to correctly record
 * the array of shortest distances from the
 * start vertex i to all other vertices.
 *
 * Parameters:
 * i: index of the vertex to begin searching from
 * n: total number of vertices
 * m: total number of edges
 * edges: the graph data structure, as an array of edges,
 *   where each edge is an array of two ints
 *
 * Results: Nothing is returned, but the distance
 * array should contain the shortest distances
 * to each vertex.
 */

void DisjointSets::bfs(int i, int n, int m, int edges[][2]) {

  // The shortest distance from the start vertex i
  // to itself is simply 0.
  distance[i] = 0;

  // We will loop over all of the shortest possible
  // distances from i to another vertex, starting
  // with distance d=1. We increase d by 1 after
  // each iteration.
  // The longest "shortest distance" possible is m
  // (a path using each edge once), so we set an
  // upper limit on the iterations.
  // However, we do break out of the loop at the
  // bottom if we detect that we have reached
  // all of the vertices.

  for (int d = 1; d <= m; d++) {

    // We initialize a variable f with -1 to show
    // that nothing has been marked on the frontier
    // during this iteration yet. Soon, we will
    // change f to the index of the first vertex that
    // we add to the frontier during this iteration.
    // Then, f can represent a temporary frontier set.
    int f = -1;

    // rooti is the index identifying the set
    // that includes the start vertex i. This set
    // contains all of the vertices that were
    // added to the frontier during previous
    // iterations.
    int rooti = find(i);

    // We loop through all of the edges
    // during each distance iteration.
    // ---
    // (Note: This is done here for simplicity,
    // but it is NOT efficient!
    // This could be much more efficient
    // if we used a queue of vertices to
    // check on the frontier boundary instead.
    // That would avoid repeatedly checking the
    // same edges. The lecture describes the way
    // to efficiently implement BFS, and you'll
    // look at an efficient implementation in
    // the graph search project code.)

    for (int j = 0; j < m; j++) {

      // root0 and root1 are the indices
      // identifying the sets that the vertices
      // of this edge belong to. (Maybe the same set,
      // or maybe two different sets.)

      int root0 = find(edges[j][0]);
      int root1 = find(edges[j][1]);

      //if ( ***todo INSERT CONDITION HERE*** ) {
      if (root0 == rooti && root1 != rooti) {
        // ^ TODO: You must edit the condition here!
        // If this edge crosses the frontier
        // because the [0] vertex is on the inside
        // (already reached from the start index i),
        // and the [1] vertex is on the outside,
        // then we will add the [1] vertex to the
        // frontier set and record its distance.

        // You don't need to edit this part:

        if (f == -1) {
          // This is the first edge crossing the
          // frontier during this iteration, so start
          // a new frontier set with the [1] vertex.
          f = edges[j][1];
        }
        else {
          // We already have a frontier set during
          // this iteration, so add vertex [1] to it.
          dsunion(f,edges[j][1]);
        }

        // The shortest distance to this edge's
        // vertex [1] is d.
        distance[edges[j][1]] = d;

      }
      //else if ( ***todo INSERT CONDITION HERE*** ) {
      else if (root0 != rooti && root1 == rooti) {
        // ^ TODO: You must edit the condition here!
        // If this edge crosses the frontier
        // because the [1] vertex is on the inside
        // (already reached from the start index i),
        // and the [0] vertex is on the outside,
        // then we will add the [0] vertex to the
        // frontier set and record its distance.

        // You don't need to edit this part:

        // (The code below is similar to the
        // previous case above, but we're acting
        // on vertex [0].)

        if (f == -1) {
          f = edges[j][0];
        }
        else {
          dsunion(f,edges[j][0]);
        }

        distance[edges[j][0]] = d;
      }

      // If neither one of the two cases above was
      // applicable, then we implicitly do nothing
      // in this iteration.
    }

    // After looping over the edges for the current
    // distance, we need to combine the current,
    // temporary frontier set with the previously
    // reached set of nodes using shorter distances.
    // This prevents bugs: it ensures that you can
    // use rooti to refer to the set of nodes that
    // were found on the frontier during previous
    // iterations of the OUTER loop, not including
    // nodes that were recently added to the frontier
    // during the same iteration of the INNER loop.

    if (f == -1) {
      // If no vertices were added to the frontier
      // during this iteration, then we've already
      // explored everything, so we are done.
      // We can stop iterating early.
      break;
    }
    else {
      // Otherwise, union the latest frontier
      // set with the set of vertices that have
      // previously been reached from vertex i.
      dsunion(f,i);
    }

  }
}

int main() {

  // A test case for you to experiment with:

  const int NUM_VERTS = 8;
  const int NUM_EDGES = 8;

  int edges[NUM_EDGES][2] = {{0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,3}};

  DisjointSets d;

  const int START_VERTEX = 3;
  d.bfs(START_VERTEX, NUM_VERTS, NUM_EDGES, edges);

  for (int i = 0; i < NUM_VERTS; i++) {
    std::cout << "Distance to vertex " << i << " is " << d.distance[i] << std::endl;
  }

// This should print:
// Distance to vertex 0 is 3
// Distance to vertex 1 is 2
// Distance to vertex 2 is 1
// Distance to vertex 3 is 0
// Distance to vertex 4 is 1
// Distance to vertex 5 is 2
// Distance to vertex 6 is 2
// Distance to vertex 7 is 1

  return 0;
}

