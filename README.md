# ModularDecomposition
Code to compute modular decompositions of reasonably large graphs using the algorithm of [Habib et al.](https://doi.org/10.1142/S0129054199000125) ("Partition Refinement Techniques: An Interesting Algorithmic Toolkit", Habib et al. '99) to compute a factorizing permutation. The algorithm runs in time $O(n+mlog(n))$, however the current implementation *probably* needs quadratic time $O(n^2)$ due to a poor choice of graph data structure. This could be improved, but the current implementation can handle even dense graphs upward of $1000$ vertices with runtimes below 1 second.

Given a factorizing permutation, the algorithm of [Capelle et al.](https://hal.inria.fr/hal-00958972/document) can be used to compute a modular decomposition of the graph in linear time.
