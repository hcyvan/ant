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
 //const string name("http://www.jumeiglobal.com/ajax_new/getDealsByPage?type=new&pagesize=20&index=10&page=index&callback=global_load_callback");

  Spider a;
  
 
    cout <<a.get(name)<<endl;
	
  return 0;
}
