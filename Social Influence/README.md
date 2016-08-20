

## (2007)Clustering by Passing Messages

**作者** Brendan J. Frey*; Delbert Dueck

AP算法原生论文。

主要思路：刚开始，每个节点都是中心，然后通过规则，每个节点都为项其他节点释放信息，同事也重其他节点接受信息。随着迭代次数增加，有些节点的值会变大，有些会变小，释放和接受数据的节点也会根据这些值而发生变化，最后得到一些特别显著的点。复杂度有点高，需要计算相似矩阵，如果在网络中，是否可以加以只计算相领边的相似度。

算法demo，[参考这里](http://www.psi.toronto.edu/affinitypropagation/apmovie.swf)。


## (2009)A Binary Variable Model for Affinity Propagation

**作者** Inmar E. Givoni; Brendan J. Frey


AP算法改进


## (2009)Social Influence Analysis in Large-scale Networks

TAP算法主要基于两个算法

* [Affinity Propagation](http://www.psi.toronto.edu/index.php?q=affinity%20propagation)
* Factor Graph