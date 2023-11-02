#include <iostream>
#include <vector>

class DisjointSets {
public:
	int s[256]; //size of set

	DisjointSets() { for (int i = 0; i < 256; i++) s[i] = -1; } //initialize the set

	int find(int i); //this function is what you need to implement
};

/* Modify the find() method below to
 * implement PATH COMPRESSION so that
 * element i and all of its ancestors
 * in the up-tree refer directly to the
 * root after that initial call to find()
 * returns.
 */

//the function should return int
int DisjointSets::find(int i) {

  //first create a std::vector called traversal_path
  //1) std::vector is a sequence container that encapsulates dynamic size arrays.
  static std::vector<int> traversal_path;
  
  //https://byjus.com/maths/what-is-disjoint-set/
  //next remember what a disjoint set is:
  //A pair of sets which does not have any common element are called disjoint sets. 
  //For example, set A={2,3} and set B={4,5} are disjoint sets. But set C={3,4,5} 
  //and {3,6,7} are not disjoint as both the sets C and D are having 3 as a common
  //element. Learn more about Disjoint Set here.
  
  //https://en.wikipedia.org/wiki/Disjoint-set_data_structure
  //Applications
  //A demo for Union-Find when using Kruskal's algorithm to find minimum spanning tree.

  //Disjoint-set data structures model the partitioning of a set, for example to keep   
  //track of the connected components of an undirected graph. This model can then be used 
  //to determine whether two vertices belong to the same component, or whether adding an 
  //edge between them would result in a cycle. The Union–Find algorithm is used in high-
  //performance implementations of unification.[20]

  //This data structure is used by the Boost Graph Library to implement its Incremental 
  //Connected Components functionality. It is also a key component in implementing 
  //Kruskal's algorithm to find the minimum spanning tree of a graph.

  //The Hoshen-Kopelman algorithm uses a Union-Find in the algorithm.
  //See also Partition refinement, a different data structure for maintaining disjoint 
  //sets, with updates that split sets apart rather than merging them together
  //Dynamic connectivity
  
  //next, remember in a disjoint set the value of a node is -1 if it is a root node, 
  //else if the value of the node is not -1, the it is not a root node,and you must
  //traverse upwards until you find the node that is a root node.
  
  /*
  this is the original function you are given
  if ( s[i] < 0 ) {
    return i;
  } else {
    return find(s[i]);
  }
  */
  
  //https://tutorialhorizon.com/algorithms/disjoint-set-union-find-algorithm-union-by-rank-and-path-compression/
  //Path compression:
  //Path compression` is a way of flattening the structure of the tree whenever Find is used on it. 
  //Since each element visited on the way to a root is part of the same set, all of these visited 
  //elements can be reattached directly to the root. The resulting tree is much flatter, speeding up 
  //future operations not only on these elements, but also on those referencing them.
  
  //  0           0
  // 1           1 3
  //2 3         2   4
  //   4
  
  // find(3)
  // traverse up to find the set representative which is 0
  // so make subset with 3 as the child of 0 so tree will be flattened so
  // next time find(3) is called, path will be reduced.
  
  //Pseudo code:
  //function Find(x)
    //if x.parent != x
      //x.parent := Find(x.parent)
    //return x.parent

  //make use of the traversal_path.begin, and traversal_path.end() functions, and also
  //use iter function as well.
  
  //per https://cplusplus.com/reference/vector/vector/, 
  //std::vector is a sequence container representing arrays that can change in size.
  //in c++98 at least, it has begin and end iterators, push_back and pop_back modifiers
  
  //ok so we modify the original function given in the task
  //so if the value is less then zero, then it means it is the root node
  //and if it is the root node, then do path compression?
  if ( s[i] < 0 ) {
    for (auto iter = traversal_path.begin(); iter != traversal_path.end(); iter++)
    {
      //path compression from i to root node
      int node = *iter;
      s[node] = i;
    }
    return i;
  } 
  else {
    //add current node into traversal path
    traversal_path.push_back(i);
    return find(s[i]);
  }
  
}

int main() {
  DisjointSets d;

  //add in the values of the set, 4 elements
  d.s[1] = 3;
  d.s[3] = 5;
  d.s[5] = 7;
  d.s[7] = -1; //this is the root node, with value of -1

  std::cout << "d.find(3) = " << d.find(3) << std::endl; //find the element 3, print it out
  std::cout << "d.s(1) = " << d.s[1] << std::endl; //output s[1]
  std::cout << "d.s(3) = " << d.s[3] << std::endl; //output s[3]
  std::cout << "d.s(5) = " << d.s[5] << std::endl; //output s[5]
  std::cout << "d.s(7) = " << d.s[7] << std::endl; //output s[7]

  return 0;
}

/*
//code from the challenge page:
Correct

Tested disjoint set (11, 26, 40, 55, 63, 78, 81, 90, 93, 100, 108, 115, 125, 134, 150).
d.find(26) = 150, expected 150.
After find ran, expected all of these to be set to 150:
d.s[26] = 150.
d.s[40] = 150.
d.s[55] = 150.
d.s[63] = 150.
d.s[78] = 150.
d.s[81] = 150.
d.s[90] = 150.
d.s[93] = 150.
d.s[100] = 150.
d.s[108] = 150.
d.s[115] = 150.
d.s[125] = 150.
d.s[134] = 150.
After find ran, expected this to be 26:
d.s[11] = 26.
*/
