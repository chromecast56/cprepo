<h4> Problem </h4>
_____________________________________________________

Given an array a, you want to answer queries of form (l,r), 
relating to the subarray a[l...r]

For simpler tasks like sum, or max, this is simply a subset of what the
powerful segment tree <br> can do, and can be done in O(Qlogn). But for
more complicated tasks it can get tricky. For example, what if you wanted
the mode over a subarray?

Another example is "Powerful Array" from Codeforces:
> Define cnt_i the number of occurences of i in subarray a[l...r]

> Define the "cost" of a subarray the sum of i* cnt_i*cnt_i for all i

> We want to query for the cost of Q subarrays

Simple solution is to loop from l to r, and is O(NQ). 

A more efficient solution, but still O(NQ) is to utilize previous solutions
when calculating. For example, if we know the cost of a subarray a[l...r],
then by "shifting" the subarray through a series of add and remove functions
we can effectively use it for future subarrays a[l'...r'].  

However, the reason it's still O(NQ) is because the order of the queries 
can fuck us over. For example, we can have q_1 = {0,1}, but have
q_2 = {100000,100001}

This is where Mo's algorithm comes in. First, we define a block size of
sqrt(N). Then we group queries into the sqrt(N) blocks dictated by l value.
Inside these blocks, we then sort by increasing r value. To look at the
amortized time complexity, we can look at how the global l and r values move
as they go to each query.

Define Q' as the number of queries in some specific block. Notice that
after visualizing the query structure, that l will "bounce around" its
block. Worst case, a bounce will cover sqrtN add/remove operations (for some
data structure that can do it in O(1)) for
all Q' queries. Summing this up for all Q' yields QsqrtN operations
of l.

Notice that r values aren't restricted to blocks. This is why we sort them,
so we can maintain a sweepline-type amortized complexity. At each block,
r will gradually climb to the top of the array, and then go back down 
as l reaches the next block. Thus, each block iteration (sqrtN) has O(n)
complexity for r, for a total complexity of NsqrtN.  

Thus, the final time complexity for Mo's algorithm is O((N+Q)sqrtN),
or O(QlogQ + (N+Q)sqrtN) accounting for the sorting of the queries.
Note that for more complex operations, like finding the mode, add and
remove operations become logn, adding a log factor to the complexity
(the DS needed would be a priority queue, sorted by pii(cnt_i,i))


