highPerformanceNetworkServer
=============================
-----
**目标**: 高性能TCP网络服务器程序  

**简介**: 程序架构采用[master-worker模型](http://yaocoder.blog.51cto.com/2668309/1170944)，并利用libevent网络库来实现one loop per thread(一个事件循环一个线程)的IO模型。  
  
  
* **支持平台**: x86-64 linux  
* **开发语言**: C++  
* **开发平台**: ubuntu release 17.10
* **linux内核版本**: 4.13.0-46-generic 
* **gcc 版本**: 7.2.0
* **[libevent](http://libevent.org/)版本**: 2.0.21

**测试结果**:

* 对于tcp短连接以简单的请求——回应进行测试，10万个请求，平均响应时间约为16ms。
* 对于tcp长连接，根据业务实时做更新，目前10万级并发连接（加20s心跳），服务端可以轻松应对，资源消耗很小。


**参考文章**

* [网络编程释疑之：单台服务器上的并发TCP连接数可以有多少](http://yaocoder.blog.51cto.com/2668309/1312821)

* [网络编程释疑之：TCP半开连接的处理](http://yaocoder.blog.51cto.com/2668309/1309358)

* [网络编程释疑之：TCP的TIME_WAIT状态在服务器开发中的影响？](http://yaocoder.blog.51cto.com/2668309/1338567)

* [我的网络开发之旅——socket编程](http://yaocoder.blog.51cto.com/2668309/1556742)

**配和客户端库使用**
* [RPC_Framework: 基于TCP协议的远程过程调用框架——客户端](https://github.com/yaocoder/RPC_Framework) 
  1. 客户端和服务端均分为业务层，协议层（JSON），网络层（libevent），可以根据自己的业务定制每一层的接口；

  2. 客户端实现了与服务端的短连接请求，长连接请求，服务端的推送消息；

  3. 客户端提供跨平台的支持，目前已经经过windows，linux，android，ios的测试；

