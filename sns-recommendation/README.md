 <!--MathJax数学公式-->
  <script type="text/x-mathjax-config">
  MathJax.Hub.Config({tex2jax: {inlineMath: [['$','$'], ['\\(','\\)']]}});
  </script>
  <script type="text/javascript" async src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS_CHTML"></script>
	

## (2005)Prediction and Ranking Algorithms for Event-Based Network Data

本文主要解决时序网络中，如果根据已有的网络事件（边），预测未来的事件。同事涉及时序网络章，每个节点影响力的变化，感觉这个也可以做tap的事情，但是目前不是我关系的。

预测事件，使用了逻辑回归，但是其他二元分类模型也可以。使用了top k的准确率来作为评估方法，当然其他二元分类器的评估指标也是适合的，关键看应用场景。训练集和预测集的选取，有点类似幸运星付费的训练集，选取一段时间的数据，预测后面一段时间是否会做。特征计算，主要是考虑数据对的特征，如相识性，最短距离，邻居的特征等。但是没有描述如何选取正负标签，我推测这个标签就是现有的边，负标签就是随机选取那些没有成对的边。


## (2005)Evaluating Similarity Measures - A Large-Scale Study in Orkut Social Network.pdf

有涉及社群推荐相关内容。将社团看成主体，用户看成社团的成员，为社团推荐社团，间接就是为用户推荐社团。

## (2006)Link Prediction using supervised Learning

**正负样本选取方法**

Then, we prepare the classification dataset, by choosing those author pairs, that appeared in the train years, but did not publish any papers together in those years. Each such pair either represent a positive example or a negative example,
depending on whether those author pairs published at least one paper in the test years or not.

正样本应该是非常稀少的，因为任意两个作者在训练集中没有一起发过论文，在后面几年一起发论文的概率应该很小，假设每个人与其他人发论文的概率是均等的，那么就是1/n，远远小于0.5。但是论文中提到的正负标签比例是1：1，感觉是人工采样出来的，而不是真实的。

上面的理解是错的，文章的本意是预测新增的link，训练时间没有link，预测时间有link，才是正，否则是负，也就是训练和预测都有link，是负样本。1：1，说明在预测时间，增加了一倍合作关系（边）。




使用了三类特征

* 相识性
* 成对聚合
* 网络拓扑结构

评估方法采用了

* Accuracy
* Precision
* Recall
* F-value
* Squared-Error  需要计算概率而不是label


一种判断特征好坏的方法，是单独看特征在不同标签小的概率分布，重合面积越小，特征越好。





## (2007)Recommendations in Taste Related Domains - Collaborative Filtering vs Social Filtering

协同过滤，引入了社交属性，效果明显好于不引入。

三角形就可以表示一个小社区，并不一定要社群发现。

第一个实验主要通过统计的方法，检测好友关系与品位的相关性，发现好友对，三个好友，和4个好友均有明显相关性，而且随着人数越多，相关系数越大。

第二个实验主要考虑了两个算法

* 传统User CF
* 基于社交网络的User CF

后者在取邻居时，采用了sns关系，取了一度好友和二度好友，而不是全局比较，这样在时间上有大幅度性能提升。根据实验，后者在MAE和F-Measure上明显好于前置。


## (2007)Local Probabilistic Models for Link Prediction
推荐事件，而不是朋友，关系是可以重复建立的，与相对永久的朋友关系不太一样，正负样本采样方法无法借鉴。



## (2009)“Make New Friends, but Keep the Old” – Recommending People on Social Networking Sites

本文尝试了4中社交网络好友推荐算法，在IBM公司内部试验，

* 内容相似度
* 内容相似度+好友关系
* 共同好友
* SONAR（基于外部好友关系）

这四类算法大致分两类，前两者为一类，基于内容，后两者为一类，基于关系链。基于类容的更容易发现陌生人，基于好友关系的，更容易发现线下熟人。一种策略是先基于熟人推荐，发现线下熟人网络，等关系建立后，在推荐陌生但相似的陌生人。

## 知乎专栏：从好友推荐算法说起

[传送门](https://zhuanlan.zhihu.com/p/20533434)

主要讲了基于二度好友的推荐，其中还列举了facebook的一个潜在好友评分的公式。

## (2010)New Perspectives and Methods in Link Prediction
推荐实践，而不是朋友，正负样本采样方法无法借鉴。



## (2010)Inferring social ties from geographic coincidences
如果在时间和地点上有巧合的两个人，他们成为好友的概率非常高。比如在一天内，A和B两个人都在一天假日吃饭，并在海岸城k歌，然后又在coco park某酒吧喝酒，那么他们可能是好友。
本文章将上面的观察，定量的用概率模型分析；同时用了一些线上数据验证了该模型。


## (2010)Folks in Folksonomies - social link prediction from shared metadata
这篇文章首先重网络结构和统计方面，验证了标签相识的用户之间成为好友的几率越大。然后，直接使用好友像适度排序，选取相似度最大的预测为好友，使用常规的**ROC/AUC**方法评估预测结果。

文章使用了一种**基于邻居的抽样方法**，而不是任意对两个用户抽样。因为后者得到的样本，好友会非常稀疏，结果无法比较。前者，虽然结果有偏，但是至少结果可以比较。如何基于邻居呢？邻居就是1度，2度等等好友，设定一个上限，比如60，全部取出来就是样本，正样本就是1度朋友，负样本就是大于1度的朋友。

## (2011)Exploiting Place Features in Link Prediction on Location-based Social Networks

这一遍文章**非常好**，解决了好友推荐的两个疑惑

1. 如果确定预测空间：本文通过缩小搜索范围，将搜索空间限制在好友的好友和到访过相同地点的用户之间，最后通过交接，进一步缩小搜索空间。
2. 如何设计特征：本文虽然是结合地理位置设计好友推荐的特征，但是有些地方还是值得简介。

游戏好友推荐，可以将地理位置换成玩法偏好，付费能力等方面进行相似性评估，可能效果类似。同时，本文对单个特征的性能评估，二元分类模型的评估和相关文献方面都给出了很大的参考价值。


## (2012)Trust-Based Local and Social Recommendation

基于sns的物品推荐，知乎专栏有一篇[阅读笔记](https://zhuanlan.zhihu.com/p/20602389)。虽然不是好友推荐，但是后面可能有机会遇见该问题。
## 总结--好友推荐相关思路

* 方向1 基于协同过滤+SNS社交关系：1)邻居换成好友，而不是相似用户；2）邻居且好友，意见有加成
* 方向2 基于共同好友：2度，3度好友，排序根据共同好友数
* 方向3 好友与社团：使用LR，对社团做画像，将用户与社团匹配，变成二元分类问题
* 方向4 社团与社团：将研究单位变成社团，对社团推荐社团，然后可以归纳到用户与社团推荐
* 方向5 迁移学习：构建单一游戏外的全网络，结合方向1与2

## (2012)Jointly Predicting Links and Inferring Attributes using a Social-Attribute Network

使用的hop2-links 作为好友预测的候选空间。本文还有用户属性预估，并且用预估的属性增加好友预测的准确率。

## 后续工作

人+社团/好友推荐，基于模型，梳理数据etl

## (2014)An Evolutionary Algorithm Approach to Link Prediction in Dynamic Social Networks

预测动态事件，tweet交互，不适合。

## [(2014)A Survey of Friendbook Recommendation Services](https://www.ijsr.net/archive/v3i11/T0NUMTQxMDE0.pdf)

太短，不知所云

## (2014)Meta-path based Multi-network Collective Link Prediction

多个图的link预测，后面如果探索多个游戏的巨大社交网络，可以参考这篇文章

## (2015)A Survey of Link Recommendation for Social Networks: Methods, Theoretical Foundations, and Future Research Directions

这篇文章介绍了好友推荐的几个方向，并且将这些方法与社会经济学相结合。最后，提出了一些新的比较新颖的方向。我们关心的是现有好友推荐的方向和相关论文，大体如下：

* 基于学习
	* 分类：使用各种分类器（svm,lr,decision tree），包括boost，bagging等和特征工程。
		* O’Madadhain et al. (2005)Prediction and Ranking Algorithms for Event-Based Network Data。已阅
		* Hasan et al. (2006)Link Prediction using Supervised Learning 已读
		* Wang et al. (2007)Local Probabilistic Models for Link Prediction 已阅读
		* Lichtenwalter et al. (2010)New Perspectives and Methods in Link Prediction 已阅读
		* Scellato et al. (2011)Exploiting Place Features in Link Prediction on Location-based Social Networks 已阅读
		* Gong et al. (2012)Jointly Predicting Links and Inferring Attributes using a Social-Attribute Network 已阅
		* Bliss et al. (2014)An Evolutionary Algorithm Approach to Link Prediction in Dynamic Social Networks 已阅读
		* Zhang et al. (2014)Meta-path based Multi-network Collective Link Prediction 已阅读
	* 概率模型:利用一些数学建模方法，归纳概率模型，然后通过最大似然计算相关参数
	* 关系学习：利用类似贝叶斯网络的关系模型
* 基于相似
	* 节点相似(nodal proximity):陌生人推荐。
		* Chen et al. 2009. (2009)Make New Friends, but Keep the Old – Recommending People on social network sites。已阅读
		* Crandall et al. 2010,(2010)Inferring social ties from geographic coincidences。已阅读
		* Schifanella et al. 2010, (2010)Folks in Folksonomies: social link prediction from shared metadata。已阅读
	* 结构相似(structural proximity)
		* 基于邻居：熟人推荐，相关算法可以参考[这里](https://zhuanlan.zhihu.com/p/20533434)
		* 基于路径：最短路径和page rank类似算法

可以先从比较成熟的方案实践，然后再涉及其他方案，优先级   

* P0: 基于邻居，节点相似和分类算法
* P1：模型概率，关系学习，基于路径


## 如何评估推荐效果

后面可以将基于分类器推荐好友的文章看看，这些文章主要是将好友关系作为特征工程，主要还是灵活使用分类器。



## [数据挖掘系列篇(20):社交网络SNS的好友推荐算法](https://zhuanlan.zhihu.com/p/20943978)

知乎的一篇文章sns好友推荐的综述，还是要看看。



## 为什么要在游戏中推荐好友？
游戏朋友之间的互动可以提高用户**活跃**和**付费**表现。

茫茫人海中，对某个用户，推荐什么样的人才能增加好友互动呢？

1. **可能认识的人** 真实世界的线下熟人或其他游戏的线上熟人,有互动的基础。
2. **志同道合的人** 相同的玩法偏好，共同语言，有互动的动机。

所以，游戏好友推荐就是为每个用户找到上面两类人（**预测空间**），然后科学的对潜在好友排序，使得用户添加好友的可能性最大化。

