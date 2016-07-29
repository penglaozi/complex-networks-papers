论文概要

## Determiing the Diameter of Small world Networks

精确计算小世界网络的直径。在小世界网络上复杂度没有具体给出。

直径与两倍eccentricity的关系 。

假设w,v两点距离为直径D，d(x)为x点的离心率，如果D>2d(x),那么可以通过x，得到2d(x)的直径，与假设矛盾。

已经试验了离心率估算直径，误差太大，放弃。


## Fast Estimation of Diameter and Shortest Paths without matrix multiplication

估算，复杂度太高，$m\sqrt{n \log n} + n^2\log n$

## ANF: A Fast and Scalable Tool for Data Mining in Massive Graphs

**年份** 2002

一种估算框架，特点是效率高，线性扩展，可并行化，准确率高。

第三节是算法细节

没看懂


ANF的核心是奇数估计法，
参考下面系列blog

[基数估计算法概览](http://blog.codinglabs.org/articles/cardinality-estimation.html)
 加概览，总共5篇