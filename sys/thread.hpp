#ifndef _sys_thread_hpp__
#define _sys_thread_hpp__

#include <pthread.h>
#define thread thread_

namespace sys {
  
class xthread
{
public:
  xthread();
  int cancel();
  
protected:
  virtual long run() = 0;

  // initializes attributes
  void init();

  // creates thread using pthread_create
  int create();

private:
  // calls run() virtual method
  static void *start(void *ptr);

  pthread_t m_tid;
  pthread_attr_t m_attr;
  long m_ret;
};

}
#endif // _sys_thread_hpp__
