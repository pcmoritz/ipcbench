#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace boost::interprocess;

int main ()
{
   try{
     char hello[] = { 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0' };
     
      message_queue mq(open_only, "message_queue");

      message_queue mp(create_only, "receive_queue", 10, sizeof(hello)); 

      unsigned int priority;
      message_queue::size_type recvd_size;

      for (int j = 0; j < 30; ++j) {
	for(int i = 0; i < 10; ++i) {
	  int number;
	  mq.receive(&hello, sizeof(hello), recvd_size, priority);
	  if(number != i || recvd_size != sizeof(number))
            return 1;
	  int number2 = number + 1;
	  mp.send(&hello, sizeof(hello), 0);
	}
      }
   }
   catch(interprocess_exception &ex){
      message_queue::remove("message_queue");
      std::cout << ex.what() << std::endl;
      return 1;
   }
   message_queue::remove("message_queue");
   message_queue::remove("message_queue");
   return 0;
}
