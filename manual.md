# Dns
Dns是一个关于域名解析的类。

+ Dns& **getHostByName**(const string& name): 对主机名name进行解析，返回原来的Dns对象。
+ const string **getHostName**(void)const: 返回主机的官方名。
+ const vector<string> **getAliases**(void)const: 返回主机的别名列表。
+ const int **getAddrType**(void)const: 返回AF\_INET表示地址为ipv4，返回AF\_INET6表示地址为ipv6。
+ const vector<string> **getAddrList**(void)const: 返回主机的地址列表。
