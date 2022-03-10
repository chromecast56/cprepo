<h5> Updates</h5>
______________________________________ <br>
Intuitively, updates with Mo's algorithm doesn't make since. After all,
it's based on the reordering of queries to optimize our two pointer, adding
in updates requires that we stay in order! But we can notice that adding
time is simply adding another "dimension" to Mo's.

For each query, add in a time variable (notice that we usually already do
to print them!). Notice that in regular Mo's, we fix the left pointer
to a specific block, and allow the right pointer to move freely in a
direction. What if we fix l and r, and allow t to move freely?
In other words, before we had <[l], r>, what if we now have <[l], [r], t>?

(By fixing, I mean letting it "bounce" within the block before going
to the next)

Our comparison function will be changed a bit:
> if (l/B != a.l/B) {
>> if (r/B != a.r/B)
>>> return t < a.t;

>> return r < a.r;

>}

> return l < a.l;

<h5> Time complexity </h5>

Right Pointer: For any given l block, the r will iterate through its 
blocks to N in the worst case (N*N/B). Additionally, it will at some point 
"bounce" inside its block at most Q times (BQ). So, the right pointer
time complexity is O(N^2/B + QB)

Left Pointer: As mentioned before, it's just QB (QsqrtN if regular Mo's)

Time Pointer: For every distinct pair of left and right block, the time
pointer has free reign from 0 to Q, moving right. Time complexity is
O(Q*N^2/B^2)



So, the final time complexity is O(QB + N^2/B + QN^2/B^2). Note that
N^2/B can be ignored, since maxing/mining B has it outclassed by
QN^2/B^2. So, the actual final is O(Q(B + N^2/B^2). Differentiating
B+N^2/B^2 w/ respect to B yields 1-2N^2/B^3, or B = (2N^2)^1/3. This
is assymptotically equal to N^2/3. 

Plugging in B=N^2/3 yields the actual actual time complexity of
O(Q(N^2/3)), or roughly O(N^5/3) for N=Q

Comments on how SquareArrayQuery.cpp should be modified for updates
are added.
