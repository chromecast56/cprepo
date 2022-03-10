<h1>Heavy Light Decomposition </h1>
Take a Tree of N nodes (N-1 edges, no edge loops). Your goal is to perform the 
following queries:  
>query_sum(a,b): Determine the sum of the nodes spanning from node A to B.

>query_update(e,newVal): Update edge E with value newVal
>
It can be seen that by maintaining the tree with no additional
datastructures, query_update() can <br> be done in O(1) and query_sum() can be done 
in O(n). This seems a lot like RSQ! Segment <br> Trees can be implemented for RSQ.
>But using Segment Trees for Trees instead of Arrays requires modification

Notice that you can't just maintain the tree as a segment tree. How would
you do that? You could <br> maintain it as an Euler tour of edges, where
a query would consist of many smaller queries of <br>
the segment tree. But it's clear that this could be super inefficient, up
to O(nlogn) per query.

_______________________________
This is where Heavy Light Decomposition comes in. It will essentially provide
a dfs ordering <br> that will allow us to "chain" certain nodes in an
overarching segment tree, so that we can "jump" <br> over many nodes in the
same chain with one query. In fact, it guarentees a total of O(logn) <br>
segment tree queries, leading to an O(log^2n) query solution.
_________________________________
Start at the root, 
and denote the "size" <br> of each node as the number of nodes in its subtree
(including itself). Then, for each node, <br> pick its child with the largest
size, and then mark the edge connecting to it as "heavy". <br>Looking at the tree, 
there should be "chains" of heavy nodes:

<img src="pictures/HLDecomp.png" alt="error">

For example, the above example would dfs through all the green nodes first,
then <br> pink, purple, orange, blue...

By doing this, we aren't really building a "true 100% working" segment tree, <br>
but since we will only do queries inside chains, of which their orderings are
<br> guarenteed to be correct, it is sufficient for our purposes.

Say that we want <br>
to do an operation that goes from the root to a leaf. Our search space is n.
<br> If we go down a heavy edge, then we can utilize the segment tree to "skip" 
over many <br> nodes in our summation. If we go down a light edge, then by the 
definition that <br> size(lightChild) < 1/2size(parent), our search space
will always at least cut in half.

This means that we do O(logn) "jumps" from the root to a leaf. Since 
Segment Tree <br> querying is O(logn) and we may do a query at every jump,
our final query complexity <br> is O(log^2n). Note that in practice this
is basically a large constant O(logn).  
To implement this you would do something like:
>query_sum(a,b) = query_tree(a,lca(a,b)) + query_tree(b,lca(a,b))

Implementing query_update can be done very easily. Notice that updating
an edge <br> only affects one "chain", so you can just call the update
function of <br> Segment Tree. This is O(logn).


Please note that the implementation of HLD can be quite tedious, as you
essentially <br> have to maintain a Segment Tree, of which
one takes up 40-50 lines of <br> code. You also have to DFS to preproccess
for the LCA function and size array, and <br> maintain the ID's of the
chains and their respective "heads". Up to 200 lines of code <br>
may be needed.
__________________________________
<a href="https://github.com/anudeep2011/programming/blob/master/qtree.cpp"> 
Implementation of HLD for RMQ: </a>
