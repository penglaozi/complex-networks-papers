
## Determiing the Diameter of Small world Networks

**年份** 2011

**作者** Frank W. Takes;Walter A. Kosters

**思路**

通过不断缩小直径的上限和下限，该上限与下限与节点离心率有很大关系。

直径与两倍eccentricity的关系 ：假设w,v两点距离为直径D，d(x)为x点的离心率，如果D>2d(x),那么可以通过x，得到2d(x)的直径，与假设矛盾。


**算法复杂度** O(mn)
 
精确计算小世界网络的直径。在小世界网络上复杂度没有具体给出。但是通过实验，在百万级点的小世界网络上，只需要少量SSSP，即可得到直径，如果只需要一个范围，可以在更少的SSSP上获得。




## Fast Estimation of Diameter and Shortest Paths without matrix multiplication

**年份** 1999

**作者** D. Aingworth; C. Checkuri; R. Motwani

**算法复杂度**  $m\sqrt{n \log n} + n^2\log n$


## Better Approximation Algorithms for the Graph Diameter

**年份** 2014

**作者** Shiri Chechik; Daniel H. Larkin; Liam Roditty; Grant Schoenebeck; Robert E. Tarjan; Virginia Vassilevska Williams

**复杂度** O(m^(3/2));O(mn^(2/3))

估算，复杂度太高。


## Fast Approximation Algorithms for the Diameter and Radius of Sparse Graphs

**年份** 2013

**作者** Liam Roditty; Virginia Vassilevska Williams

**复杂度** O(mn^(1/2))。

估算，复杂度太高。


## 总结
上面3片估算的论文，按照时间顺序，一脉相承，复杂度都不低，而且证明无法降到更低。第一篇关于小世界网络直径计算，虽然复杂度不低，但是实际效果计算可以在很少的迭代得到精确直径。考虑到我们主要面对的图也是小世界网络，所以可以在此模型上试验。