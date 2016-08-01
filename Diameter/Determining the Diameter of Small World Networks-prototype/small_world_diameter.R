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
    
    # 更新每个点离心率的上届和下界
    for(w in 1:nrow(candidates)){
      vid <- candidates[w,'vid']
      dwv <- d[1, vid]
      candidates[w,'low'] <- max(candidates[w,'low'], 
                                 max(ecc_v - dwv, dwv))
      candidates[w, 'high'] <- min(candidates[w, 'high'], 
                                   ecc_v + dwv)
    }
    
    # 更新总上界和总下界
    delta_low <- max(max(candidates$low), delta_low)
    delta_high <- min(max(candidates$high), 2*ecc_v)
    print(sprintf("low=%.2f, hight=%.2f", delta_low, delta_high))
    
    # 剔除无用候选项
    filter_index <- (candidates$high <= delta_low | 
                     candidates$low >= delta_high | 
                     candidates$low == candidates$high)
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

# 准备数据
n <- 1000
g <- sample_smallworld(1, n, 10, 0.05)
E(g)$weight <- (runif(1)+0.1)*30
is.weighted(g)
is.directed(g)

# 计算直径 
my_dia <- bounded_diameter(g, interchange_select)
my_dia
diameter(g)

# 绘图
require(ggplot2)
run_state <- my_dia$rst

p <- ggplot(data = run_state)
p <- p + geom_line(aes(x=r, y=low, color='low bound',group=1))
p <- p + geom_line(aes(x=r, y=high, color='high bound',group=1))
p <- p + geom_line(aes(x=r, y=candidates, color='candidates',group=1))
p <- p + geom_line(aes(x=r, y=high-low, color='range',group=1))
p

my_dia <- bounded_diameter(g, random_select)
my_dia
diameter(g)

p <- ggplot(data = my_dia$rst)
p <- p + geom_line(aes(x=r, y=low, color='low bound',group=1))
p <- p + geom_line(aes(x=r, y=high, color='high bound',group=1))
p <- p + geom_line(aes(x=r, y=candidates, color='candidates',group=1))
p <- p + geom_line(aes(x=r, y=high-low, color='range',group=1))
p


d <- read.table("data/AstroPhys.txt", sep = '\t', header=F)
names(d) <- c('src','dst')
dg <-graph_from_data_frame(d)
dg <- as.undirected(dg)
is.directed(dg)
is.weighted(dg)

cc <- components(dg)
top_one <- cc$membership == which.max(cc$csize)
dg_top1 <- induced_subgraph(dg,v=V(dg)[top_one])
is.connected(dg)
is.connected(dg_top1)

my_dia_2 <- bounded_diameter(dg_top1, interchange_select)
my_dia_2
 
p <- ggplot(data = my_dia_2$rst)
p <- p + geom_line(aes(x=r, y=low, color='low bound',group=1))
p <- p + geom_line(aes(x=r, y=high, color='high bound',group=1))
p <- p + geom_line(aes(x=r, y=candidates, color='candidates',group=1))
p <- p + geom_line(aes(x=r, y=high-low, color='range',group=1))
p



