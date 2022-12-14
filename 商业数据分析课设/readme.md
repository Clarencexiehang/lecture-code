# 一.要求

![img](https://cdn.nlark.com/yuque/0/2022/png/32518068/1671098762965-bec6dbde-82c3-4fec-b1da-32268437cfcf.png)

![img](https://cdn.nlark.com/yuque/0/2022/png/32518068/1672316334443-c46c7ef3-f89d-4754-b3db-2e168de48446.png)













# 二.数据说明



样本用户每次开机时，都会形成一个对应的日志文件，文件的开头2行会记录以下2个值：

Last表示日志的最后一次更新时间点距离开机时间的秒数；

L_Start表示样本用户的开机时间（年-月-日时-分-秒）。



接下来，数据采集程序会以2秒一次的频率扫描样本用户计算机的当前焦点窗口，若焦点窗口发生变化，则会在日志中追加一条记录。其中：

T表示该记录的时间点，以距离开机时间的秒数形式记录，例如8933表示距离开机时间的8933秒后；

P表示焦点窗口的窗口进程名；

I表示焦点窗口的窗口进程号；

U表示浏览器窗口的地址栏内容，即当前浏览网页的URL（为了保护样本隐私，已将URL中第1个问号之后的参数部分截断）；

A表示浏览器窗口的地址栏句柄；

B表示浏览器窗口的当前标签页句柄；

V表示焦点窗口对应的程序版本号；

W表示非浏览器焦点窗口的窗口句柄；

N表示焦点窗口对应的程序名称（仅在第一次出现时记录）；

C表示焦点窗口对应的程序所属公司名（仅在第一次出现时记录）。









# 三.功能

主题是实现推送功能，效果为向不同的用户推送一些网站，关键词

## 1.行为统计可视化

* 每个用户不同时间段使用的程序，浏览的网页统计
* 每个用户的活跃时间段
* 不同收入人口使用程序，浏览网页的情况，常用程序（总体）

## 2.推送

通过深度学习预测推送网站，软件

*  按浏览次数（每个分类的总体浏览次数）
* 是否浏览过该网站
*  浏览的时间段



针对 每个用户预测： 

   网站名    群体中浏览次数   是否使用过该网站    使用最多的时间段   
                                                                                               

​    

