#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace boost::interprocess;

int main ()
{
  char hello[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '\0'};
   try {
      message_queue::remove("message_queue");
      message_queue::remove("receive_queue");

      message_queue mq(create_only, "message_queue", 1, sizeof(hello));

      std::this_thread::sleep_for(std::chrono::milliseconds(5000));

      message_queue mp(open_only, "receive_queue");

      unsigned int priority;
      std::size_t recvd_size;
      
      for (int j = 0; j < 10; ++j) {
	auto start = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < 1; ++i){
	  mq.send(&hello, sizeof(hello), 0);
	  mp.receive(&hello, sizeof(hello), recvd_size, priority);
	}
	auto finish = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n";
      }
   }
   catch(interprocess_exception &ex){
      std::cout << ex.what() << std::endl;
      return 1;
   }

   message_queue::remove("receive_queue");
   message_queue::remove("message_queue");

   return 0;
}
