<h1>LCA: Binary Lifting </h1>

Suppose that you want to compute the "LCA", or Lowest Common Ancestor
of two nodes. <br> in a tree. Or, in other words:
> lca(u,v): Given two nodes u and v, find the node furthest from the root
<br> such that it is an ancestor of both u and v.

One simple solution is to just go up the ancestors of u and v, and find
the first one that <br> occurs for both of them. But since the balance
of the tree isn't guarenteed, it can take <br> O(n). Not goood

The problem is that it takes too long to travel through each parent of
u and v, since every <br> algorithm that does this is is O(n). The key
is to skip some nodes using preprocessing.

<h3> Preproccessing </h3>
___________________________________________________________________________
Define f[i][j] as the 2^j'th ancestor of node i. This means that there
are n possible values <br> for i, and logn possible values for j, so
in total preproccessing will take O(nlogn). It might be <br>
a bit weird to determine the reoccurence function:

> f[i][j] = f[f[i][j-1]][j-1]

Basically, the 2^j'th ancestor of i is equal to the 2^(j-1)'th ancestor
of the 2^(j-1)'th ancestor of i. <br>
Code snippet of preprocessing:
> for (int i=0;i<n;i++)
>> for (int j=0; j<ceil(log2(n)); j++)
>>> if (f[i][j-1] != -1)
>>>> f[i][j] = f[f[i][j-1][j-1];

Where initial base cases are:
> f[i][0] = parent of i

> f[i][j] = -1 for all other j

<h3>LCA calculation</h3>
___________________________________________________________________________
Calculating the LCA using the preproccessing can be tricky. First, we want
to "elevate" both <br> nodes u and v to the same "depth", where depth
is the number of nodes it takes to jump from
<br> root to node i. This can be done by preproccessing the depth of each
node, and then summing <br> f[u][j] values from j=(logn to 0).
Notice that this is why we use preproccessing: if we know every
<br> 2^j'th ancestor of every node, we can jump to any ancestor for any node
in O(logn) time by <br> representing the jump levels in binary!

<br>
After nodes u and v are in the same level, we can then use the same technique.
However, unlike before, we don't know how far we want to jump. This can be 
modified by instead looping from j=(logn to 0), and then jumping only if 
jumping doesn't result in u and v being the same node. This ensures that 
after the loop, nodes u and v will be one node away from their LCA,
and we can then return f[u][0] or f[v][0] for the final answer.


