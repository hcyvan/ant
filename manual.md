# Dns
Dns是一个关于域名解析的类。

+ Dns& **getHostByName**(const string& name): 对主机名name进行解析，返回原来的Dns对象。
+ const string **getHostName**(void)const: 返回主机的官方名。
+ const vector<string> **getAliases**(void)const: 返回主机的别名列表。
+ const int **getAddrType**(void)const: 返回AF\_INET表示地址为ipv4，返回AF\_INET6表示地址为ipv6。
+ const vector<string> **getAddrList**(void)const: 返回主机的地址列表。
+ static void **openTcp**(void): 在访问DNS服务器的时候采用TCP连接，在需要查询多个条目时较UDP效率高。
+ static void **closeTcp**(void): 关闭openTcp()设置的TCP连接。 
