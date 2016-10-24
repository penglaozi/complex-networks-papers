  <!--MathJax数学公式-->
  <script type="text/x-mathjax-config">
  MathJax.Hub.Config({tex2jax: {inlineMath: [['$','$'], ['\\(','\\)']]}});
  </script>
  <script type="text/javascript" async src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS_CHTML"></script>
	

## 好友推荐效果分析指标

* 拓扑结构
	* 直径
	* 孤立点，小社群和巨片参数
		* 孤立点数量
		* 小社群数量，平局成员数，星形结构数量
		* 巨片点数
	* 度分布：均值，方差等
	* 网络弹性
	* 小世界结构
		* 较短的平均距离
		* 较高的平均聚集系数，任意点i的聚集系数可表示为$C(i)=\frac{2|\lbrace e\_{jk}: e\_{jk} \in E, v\_j, v\_k \in N(v\_i) \rbrace|}{k\_i(k\_i-1)}$
* 游戏表现
	* 活跃时长
	* 付费金额
	* 好友互动


## (2006)Structure and Evolution of Online Social Networks
本文是雅虎研究院的一篇论文，通过研究旗下两款社交产品的时间演化，发现了主要三类用户：孤立点，小社群，和巨片。并且，统计了小社群和巨变的内部构造。最后，根据经验，设计了一个社群演化模型，与实际的演进吻合的比较好。