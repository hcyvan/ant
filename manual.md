# Dns
Dns是一个关于域名解析的类。

+ Dns& **getHostByName**(const string& name): 对主机名name进行解析，返回原来的Dns对象。与**getAddrInfo**互斥。
+ const string **getHostName**(void)const: 返回主机的官方名。
+ const vector<string> **getAliases**(void)const: 返回主机的别名列表。
+ const int **getAddrType**(void)const: 返回AF\_INET表示地址为ipv4，返回AF\_INET6表示地址为ipv6。
+ const vector<string> **getAddrList**(void)const: 返回主机的地址列表。
+ static void **openTcp**(void): 在访问DNS服务器的时候采用TCP连接，在需要查询多个条目时较UDP效率高。
+ static void **closeTcp**(void): 关闭openTcp()设置的TCP连接。
+ AddrInfo **getAddrInfo**(const string& name,const int port=80): 对主机名name进行解析，返回原来的Dns对象。与**getHostByName**互斥。注意参数中的port，通过**getAddrInfo**已经确定了要链接主机的端口。推荐此方法。

# HttpConnect
HttpConnect负责与Web服务器的链接。可通过**set**()方法重复设置要连接的对象。

+ HttpConnect& **set**(const string& ip,int objport),HttpConnect& **set**(const AddrInfo):设置要连接的主机。
+ HttpConnect& **setTimeout**(int sec,int usec=0): 设置与web服务器连接的超时时间。用在**handshake()**之前。
+ HttpConnect& **handshake()**(void): 与目标主机进行连接。
+ int **getFd**(void): 获取最近一次**set**之后的*fd*。
+ int **getIp4**(void): 获取最近一次**set**之后的*fd*。
