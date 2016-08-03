require(igraph)


random_select <- function(candidate) {
  index <- sample(1:nrow(candidate),1)
  candidate[index, 'vid']
}

interchange_select <- function(candidates) {
  index <- -1
  if( sample(0:1,1) %% 2 == 0) { # 选最高上届点
    print("select high")
    index <- which.max(candidates$high)
  } else { # 选最低下界点
    print("select low")
    index <- which.min(candidates$low)
  }
  candidates[index, "vid"]
}


bounded_diameter <- function(g, select_fun) {
  
  delta_high <- .Machine$double.xmax  # 直径上界
  delta_low <- -.Machine$double.xmax # 直径下界
  
  candidates <- data.frame(vid = as.character(V(g)), 
                           low = -.Machine$double.xmax, # 当前离心率上限
                           high = .Machine$double.xmax) # 当前离心率下限
  
  round <- 0
  run_state <- data.frame()
  while(delta_low < delta_high && nrow(candidates) > 0) {
    
    print(sprintf("%d,%d", round, nrow(candidates)))
    v <- select_fun(candidates)
    
    d <- distances(g, v) # ssp距离
    ecc_v <- max(d) # 当前离心率
    print(sprintf("ecc = %.2f", ecc_v))
    
    # 更新每个点离心率的上界和下界
#     for(w in 1:nrow(candidates)){ # 计算瓶颈
#       vid <- candidates[w,'vid']
#       dwv <- d[1, vid]
#       candidates[w,'low'] <- max(candidates[w,'low'], 
#                                  max(ecc_v - dwv, dwv))
#       candidates[w, 'high'] <- min(candidates[w, 'high'], 
#                                    ecc_v + dwv)
#     }
#     
    # 向量版本，效率非常高
    all_dwv <- sapply(candidates$vid, function(vid)d[1, vid])
    candidates$high <-apply(data.frame(candidates$high, 
                                       all_dwv+ecc_v),
                            1,
                            min)
    candidates$low <- apply(data.frame(candidates$low, 
                                       ecc_v - all_dwv, 
                                       all_dwv),
                            1,
                            max)
    
    # 更新总上界和总下界
    delta_low <- max(delta_low, max(candidates$low))
    delta_high <- min(delta_high, max(candidates$high), 2*ecc_v) 
    # 当偶然ecc_v是直径，上界也不会收敛到最后，本轮过后，该点会被“误删除”，
    # 但是真实的下界得到了保留，这也是为什么下界总是ok，上界不ok的原因，
    # 其实可以保留当前节点，这样也并不会多几轮，但是不会出现那种上界低于下界的结果。
    # 但是，性能可能变差。 
    print(sprintf("low=%.2f, high=%.2f", delta_low, delta_high))
    
    # 剔除无用候选项
#     filter_index <- (candidates$high <= delta_low | 
#                      candidates$low >= delta_high | 
#                      candidates$low == candidates$high)
    # ok version
    filter_index <- ((candidates$high <= delta_low & 
                      candidates$low >= delta_high/2) | 
                      candidates$low == candidates$high)
#     filter_index <- ((candidates$high <= delta_low & 
#                         candidates$low >= delta_high/2)) 
    # 上面这个版本 仍然会丢到直径，所以还是之前那个比较好，效率会高。
    # 不会出现上界低于下界的版本
    # 每个节点下界的两倍有可能是上界，所以只有2倍下界完全大于等于上界才被删除
    candidates <- candidates[!filter_index,]
    
    round <- round + 1
    run_state <- rbind(run_state,
                       data.frame(r = round,
                                  low = delta_low,
                                  high = delta_high,
                                  candidates = nrow(candidates)
                                   ))
  }
  
  list(low = delta_low,high = delta_high, rst = run_state)
}

############################################################
# 随机小世界网络
############################################################

# 准备数据
set.seed(564)
n <- 1000
g <- sample_smallworld(1, n, 3, 0.25)
# E(g)$weight <- (runif(1)+0.1)*30
# E(g)$weight <- degree(g)
is.weighted(g)
is.directed(g)
length(V(g))
length(E(g))


# 交替策略 
my_dia <- bounded_diameter(g, interchange_select)
my_dia
diameter(g)

# 绘图
require(ggplot2)
p <- ggplot(data = my_dia$rst)
p <- p + geom_line(aes(x=r, y=low, color='low bound',group=1))
p <- p + geom_line(aes(x=r, y=high, color='high bound',group=1))
p <- p + geom_line(aes(x=r, y=candidates, color='candidates',group=1))
p <- p + geom_line(aes(x=r, y=high-low, color='range',group=1))
p

# 随机策略
my_dia <- bounded_diameter(g, random_select)
my_dia
diameter(g)

p <- ggplot(data = my_dia$rst)
p <- p + geom_line(aes(x=r, y=low, color='low bound',group=1))
p <- p + geom_line(aes(x=r, y=high, color='high bound',group=1))
p <- p + geom_line(aes(x=r, y=candidates, color='candidates',group=1))
p <- p + geom_line(aes(x=r, y=high-low, color='range',group=1))
p


###################################################################
# 论文数据
###################################################################

source_file <- "../data/AstroPhys.txt";directed <- FALSE
# source_file <- "../data/Enron.txt";directed <- FALSE
# source_file <- "../data/web.txt";directed <- TRUE
# source_file <- "../data/skitter.txt";directed = FALSE
 
dg <- graph_from_data_frame(read.table(source_file, sep = '\t', header=F),
                           directed = directed)

# # cf数据
# load("../data/sns_ge5.RData")
# dg <- graph_from_data_frame(sns_ge5)
# rm(sns_ge5);gc()


is.directed(dg)
is.weighted(dg)

cc <- components(dg)
top_one <- cc$membership == which.max(cc$csize)
dg_top1 <- induced_subgraph(dg,v=V(dg)[top_one])
is.connected(dg)
is.connected(dg_top1)
is.weighted(dg_top1)
length(V(dg_top1))
length(E(dg_top1))

set.seed(38)

exp <- 1
dia_rst <- data.frame()
for(e in 1:exp) {
  print(sprintf("================Experiment: %d===========",e))
  my_dia <- bounded_diameter(dg_top1, interchange_select)
  dia_rst <- rbind(dia_rst,
                   cbind(exp = e, my_dia$rst))
}
require(plyr)
stat_round <- ddply(dia_rst, .(exp), function(x) c(round_count = max(x$r))) 
mean(stat_round$round_count)
 
 
require(ggplot2)
p <- ggplot(data = dia_rst)
p <- p + geom_line(aes(x=r, y=low, color='low bound',group=1))
p <- p + geom_line(aes(x=r, y=high, color='high bound',group=1))
p <- p + geom_line(aes(x=r, y=high-low, color='range',group=1))
p

p <- ggplot(data = dia_rst)
p <- p + geom_line(aes(x=r, y=candidates, color='candidates',group=1))
p



load("../data/sns_ge5.RData")
cf_g <- 
is.directed(sns_ge5)
