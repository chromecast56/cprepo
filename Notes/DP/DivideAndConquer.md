Divide and Conquer is an optimization technique commonly used in dp.

It's used for dp problems of the following structure:
> f(i,j) = min_{k<=j} (f(i-1,k) + W(k,j)

Where W(i,j) is some weight function. Note that the 2nd f can be
f(i-2,k), or f(i-3,k)... But most <br> problems will have i-1.

Solving this dp regularly is O(kn^2), where 0<=i<k and 0<=j<n. But
can we do better? <br> In fact, we can actually achieve O(knlogn) if
W(i,j) satisfies the <b> monotonicity condition </b>

<h4> Monotonicity Condition </h4>
____________________________________________________________________
<br> In the above function, say that we know the k that optimizes
f(i,j). In other words, we know <br> the k that makes f(i-1,k) + W(k,j)
a min. Now, say that k' is the optimial value that minimizes <br>
f(i,j+1). Then if k <= k' for all k, the monotonicity condition is
satisfied.

<h5> Why does this matter? </h5>
Well, say that we calculated f(i,n/2), and saved its k value.
Then, if we wanted to calculate <br> f(i,n/4), the possible k' values
are in the range 0 to k. Likewise, the possible k' values for <br>
f(i,3n/4) are k to n. This greatly reduces our search space. <br>
If you think about how we were calculating dp before, our search
space was always 0 to n!

This means we can employ a divide and conquer approach for each "stage",
or i, making <br> the time complexity O(knlogn). <br>

Note that for some problems, they can specified into a k=1 case, so they
are O(nlogn). <br> You shouldn't just think "divide and
conquer --> knlogn --> kinda n^2"

f(i) = min(f(j) + C(j,i)), and determine if g(i) is monotonic.
