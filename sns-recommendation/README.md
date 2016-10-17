## (2005)Evaluating Similarity Measures - A Large-Scale Study in Orkut Social Network.pdf

有涉及社群推荐相关内容。将社团看成主体，用户看成社团的成员，为社团推荐社团，间接就是为用户推荐社团。

## (2007)Recommendations in Taste Related Domains - Collaborative Filtering vs Social Filtering

协同过滤，引入了社交属性，效果明显好于不引入。

三角形就可以表示一个小社区，并不一定要社群发现。

第一个实验主要通过统计的方法，检测好友关系与品位的相关性，发现好友对，三个好友，和4个好友均有明显相关性，而且随着人数越多，相关系数越大。

第二个实验主要考虑了两个算法

* 传统User CF
* 基于社交网络的User CF

后者在取邻居时，采用了sns关系，取了一度好友和二度好友，而不是全局比较，这样在时间上有大幅度性能提升。根据实验，后者在MAE和F-Measure上明显好于前置。



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



## (2012)Trust-Based Local and Social Recommendation

基于sns的物品推荐，知乎专栏有一篇[阅读笔记](https://zhuanlan.zhihu.com/p/20602389)。虽然不是好友推荐，但是后面可能有机会遇见该问题。

## (2010)Inferring social ties from geographic coincidences
如果在时间和地点上有巧合的两个人，他们成为好友的概率非常高。比如在一天内，A和B两个人都在一天假日吃饭，并在海岸城k歌，然后又在coco park某酒吧喝酒，那么他们可能是好友。
本文章将上面的观察，定量的用概率模型分析；同时用了一些线上数据验证了该模型。


## (2010)Folks in Folksonomies - social link prediction from shared metadata
这篇文章首先重网络结构和统计方面，验证了标签相识的用户之间成为好友的几率越大。然后，直接使用好友像适度排序，选取相似度最大的预测为好友，使用常规的**ROC/AUC**方法评估预测结果。

文章使用了一种**基于邻居的抽样方法**，而不是任意对两个用户抽样。因为后者得到的样本，好友会非常稀疏，结果无法比较。前者，虽然结果有偏，但是至少结果可以比较。如何基于邻居呢？邻居就是1度，2度等等好友，设定一个上限，比如60，全部取出来就是样本，正样本就是1度朋友，负样本就是大于1度的朋友。


## 总结--好友推荐相关思路

* 方向1 基于协同过滤+SNS社交关系：1)邻居换成好友，而不是相似用户；2）邻居且好友，意见有加成
* 方向2 基于共同好友：2度，3度好友，排序根据共同好友数
* 方向3 好友与社团：使用LR，对社团做画像，将用户与社团匹配，变成二元分类问题
* 方向4 社团与社团：将研究单位变成社团，对社团推荐社团，然后可以归纳到用户与社团推荐
* 方向5 迁移学习：构建单一游戏外的全网络，结合方向1与2



## 后续工作

人+社团/好友推荐，基于模型，梳理数据etl

## [(2014)A Survey of Friendbook Recommendation Services](https://www.ijsr.net/archive/v3i11/T0NUMTQxMDE0.pdf)

太短，不知所云


## (2015)A Survey of Link Recommendation for Social Networks: Methods, Theoretical Foundations, and Future Research Directions

这篇文章介绍了好友推荐的几个方向，并且将这些方法与社会经济学相结合。最后，提出了一些新的比较新颖的方向。我们关心的是现有好友推荐的方向和相关论文，大体如下：

* 基于学习
	* 分类：使用各种分类器（svm,lr,decision tree），包括boost，bagging等和特征工程。
		* O’Madadhain et al. (2005)Prediction and Ranking Algorithms for Event-Based Network Data
		* Hasan et al. (2006)Link Prediction using Supervised Learning 
		* Wang et al. (2007)Local Probabilistic Models for Link Prediction
		* Lichtenwalter et al. (2010)New Perspectives and Methods in Link Prediction
		* Scellato et al. (2011)Exploiting Place Features in Link Prediction on Location-based Social Networks
		* Gong et al. (2012)Jointly Predicting Links and Inferring Attributes using a Social-Attribute Network
		* Bliss et al. (2014)An Evolutionary Algorithm Approach to Link Prediction in Dynamic Social Networks
		* Zhang et al. (2014)Meta-path based Multi-network Collective Link Prediction
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


## 好友推荐评估指标

* MAP
* 二元分类器评估指标，召回率，准确率，f值，AUC，ROC