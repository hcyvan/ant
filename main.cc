#include <iostream>
#include "lib.h"
#include "tcp.h"
#include "http.h"
#include "dns.h"
#include "spider.h"




int main()
{
	//const string name("www.126.com");
	const string name("http://mail.126.com/js6/main.jsp?sid=jAzqdaPTLCawFybAQnTTPOwvyzdLWRFy&df=mail126_letter#module=welcome.WelcomeModule|{}");

	cout <<Spider::get(name)<<endl;


	
	return 0;
}
