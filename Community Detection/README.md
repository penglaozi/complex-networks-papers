## Fast algorithm for detecting community structure in networks

**思路** 最大模块度，贪心算法

**复杂度** O((n+m)^2),稀疏图是O(n^2)。

**实验** 

* 在部分数据上，此算法与Girvan-Newman算法(最大介数消除)比起来，在z\_out小时，差不多，但是在z\_out变大时，此算法稍微高效。
* 在某些数据上，此算法比GN算法差。
* 但是在数据量长到一定情况时，此算法计算效率的优势就十分明显。




