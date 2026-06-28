My project desription was "Come up with a one-week examination project about regularized least-squares method for signal deconvolution."
In the following I will explain what I did and comment on the findings.

First I implemented the Tikhonov regularization for 3 different regularization matrices:
1: Identity (Standard Ridge regression)
2: First derivative (for equal spaced points)
3: Second derivative (for equal spaced points).
These were compared and as expected does the second derivative work best for smooth data (as it penalizes curvature).
I compared gaussian, cosine, linear and step function data. For the step function data the first derivative regularization worked best,
showing that one should adapt the regularization matrix to the data.
The GCV routine (more due to that later) also comes very close to the optimal error (calculated by minimizing the difference between the calculated points
and the original unblurred data), thereby showing that the routine works (in reality one of course doesn't have this data and it was just used for testing)

I furthermore implemented 2 different ways of computing the optimal regularization parameter alpha.
The one described in the book for when the variance of the noise is known, as well as the GCV routine for when the noise is unknown (https://www.geeksforgeeks.org/machine-learning/mastering-generalized-cross-validation-gcv-theory-applications-and-best-practices/)
As seen in the "Size" figure the 2 produce similar results as long as the number of data points are large enough. 
For a small amount of datapoints the discrepancy principle of course fails and the GCV becomes far superior.
For the GCV i use a newton minimizer, while I use a newton rootfinding algorithm for when the variance is known.
I used the ones writen in the course but adapted them to only 1D for efficiency.
Numerical details and small comments can be found in the code.

I also investigated the effect of the size of the noise.
As seen in the "Noise" plot on gets the expected behavior. The deconvolution becomes better for smaller noise 
and the regularization parameter increases with increasing noise to reduce the amplification of the noise during inversion of the ill-conditioned matrix B.
One also sees that, through an exponantial increase in the regularization parameter, the error seems to flatten out for increasing noise.

Lastly I investigated the effect of the "blurring" matrix B, where I to no surprise found that a larger blurring
leads to a larger error in the reconstructed data. 
At the same time a smaller blurring results in a larger regularization parameter (see the "Blur" plot). This seems counter intuitive to begin with, 
as one would expect the problem to get more and more ill-conditioned. Using the Frobenius norm in an estimate of the condition number (https://en.wikipedia.org/wiki/Condition_number)
we infact see that a larger blurring results in a more ill-conditioned blurring matrix. Why doesn't alpha increase then?
This could be explained by the fact that alpha is not chosen to make the problem the least ill-condtioned,
but rather to minimize the prediction error. One might suspect that a large blurring smoothes the data more,
so that alpha actually decreases when penalizing curvature. To test this theory I also plotted the norm of D*y_recovered (D penalizes curvature), which was shown to be quite constant, therby supporting the theory.

(Since the inverse in the GCV is somewhat expensive, the code taken 1-2 minutes to run)