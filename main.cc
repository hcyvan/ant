#include <iostream>
#include "lib.h"
#include "tcp.h"
#include "http.h"
#include "dns.h"
#include "spider.h"




int main()
{
  //const string name("www.126.com");
  const string name("http://www.baidu.com");

  Spider a;
  a.get(name);
  a.get(name);
  //  cout <<a.get()<<endl;
  

	
  return 0;
}
