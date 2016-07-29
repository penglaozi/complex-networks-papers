require(igraph)

n <- 1000
g <- sample_smallworld(1, n, 10, 0.05)
# E(g)$weight <- (runif(1)+0.1)*30
is.weighted(g)
dia <- diameter(g)
dia

# d_list <- eccentricity(g)
# summary(d_list)

dis <- distances(g)
d_list2 <- apply(dis,1,max)
summary(d_list2)

ord_dis <- d_list2[order(d_list2)] 
 

d_plot <- rbind(data.frame(x=1:n, y = ord_dis, type = 'low'),
                data.frame(x=1:n, y = 2*ord_dis, type = 'high'))

require(ggplot2)
p <- qplot(x=x,y=y,data=d_plot,color=type,geom='line')
p <- p + scale_y_continuous(limits = c(0, max(d_plot$y)))
p


# 结论:不能使用两倍离心率估算直径，误差太大 

