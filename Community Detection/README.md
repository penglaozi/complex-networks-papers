## Fast algorithm for detecting community structure in networks

**年份** 2003 

**作者** M. E. J. Newman

**思路** 最大模块度，贪心算法

**复杂度** O((n+m)^2),稀疏图是O(n^2)。

**实验** 

* 在部分数据上，此算法与Girvan-Newman算法(最大介数消除)比起来，在z\_out小时，差不多，但是在z\_out变大时，此算法稍微高效。
* 在某些数据上，此算法比GN算法差。
* 但是在数据量长到一定情况时，此算法计算效率的优势就十分明显。


## Finding community structure in very large networks

**年份** 2004

**作者** Aaron Clauset; M. E. J. Newman; Cristopher Moore

此论文是[上篇论文](1)的续篇，在此基础上，将复杂度降到了O(nlog^2n)，这样就可以大规模图上使用了。大体的贪心思想没有变化，主要是在每一轮取最大聚合时，用了堆这个数据结构，使得线性效率变为对数平方效率。


一旦detaQ变成负数，后面的都会变成负数，此时，可以停止算法。

无法用spark实现，多次迭代，每次迭代计算较小，但是迭代之间前后依赖。

上篇论文和此篇论文都有M. E. J. Newman参与。

[1]:Fast algorithm for detecting community structure in networks.pdf

## Finding and evaluating community structure in networks

**年份** 2003年 

**作者** M. E. J. Newman; M. Girvan

此论文就是其他论文中多次提及的Girvan-Newman算法。思路主要是找到介数最高的边，然后删除掉，最后剩下的就是社群。因为**介数高的边是社群之间的桥梁**，所以删除后，剩下的就是社群。但是，此算法计算量及其高，首先介数计算复杂度是O(nm),其次每次删除一个边，需要重新计算介数，因为图的结构已经改变。所以，此算法只能在比较小的图上应用。
