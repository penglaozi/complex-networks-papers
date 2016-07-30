

## ANF: A Fast and Scalable Tool for Data Mining in Massive Graphs

**年份** 2002

**作者** Christopher R. Palmer；Phillip B. Gibbons；Christos Faloutsos


一种估算框架，特点是效率高，线性扩展，可并行化，准确率高。

根据周围邻居节点，一层一层向外扩张，关键是在融合过程中，有大量重复数据，如果精确去重，效率十分低下，所以采用了一种称之为基数估算的方法，在保证精度的同事，极大减少了时间与空间复杂度。下面是一个网友对基数估算的系列博文，读后很有启发，

1. [基数估计算法概览](http://blog.codinglabs.org/articles/cardinality-estimation.html)
* [解读Cardinality Estimation算法（第一部分：基本概念）](http://blog.codinglabs.org/articles/algorithms-for-cardinality-estimation-part-i.html)
* [解读Cardinality Estimation算法（第二部分：Linear Counting）](http://blog.codinglabs.org/articles/algorithms-for-cardinality-estimation-part-ii.html)
* [解读Cardinality Estimation算法（第三部分：LogLog Counting）](http://blog.codinglabs.org/articles/algorithms-for-cardinality-estimation-part-iii.html)
* [解读Cardinality Estimation算法（第四部分：HyperLogLog Counting及Adaptive Counting）](http://blog.codinglabs.org/articles/algorithms-for-cardinality-estimation-part-iv.html)
* [五种常用基数估计算法效果实验及实践建议](http://blog.codinglabs.org/articles/cardinality-estimate-exper.html)


## Fast Approximation of the \Neighbourhood" Function for Massive Graphs

**年份** 2001

**作者** Christopher R. Palmer;Phillip B. Gibbons;Christos Faloutsos

此论文内容与*ANF: A Fast and Scalable Tool for Data Mining in Massive Graphs*类似，估计是该论文的一个较早的版本，作者都是同一拨人。这篇论文讲得稍微清楚一点。



