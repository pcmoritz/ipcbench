#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace boost::interprocess;

int main ()
{
  std::cout << "hello" << std::endl;
  char hello[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '\0'};
   try{
      message_queue mq(open_only, "message_queue");

      message_queue mp(create_only, "receive_queue", 1, sizeof(hello)); 

      unsigned int priority;
      message_queue::size_type recvd_size;

      std::cout << "hello" << std::endl;

      for (int j = 0; j < 10; ++j) {
	for(int i = 0; i < 1; ++i) {
	  mq.receive(&hello, sizeof(hello), recvd_size, priority);
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
