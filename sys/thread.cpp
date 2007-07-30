#include <sys/thread.hpp>

namespace sys {

//-----------------------------------------------------------------------------
xthread::xthread()
{
}

//-----------------------------------------------------------------------------
int xthread::create()
{
  return pthread_create(&m_tid, &m_attr, start, this);
}

//-----------------------------------------------------------------------------
void xthread::init()
{
  pthread_attr_init(&m_attr);
}

//-----------------------------------------------------------------------------
void *xthread::start(void *ptr)
{
  xthread *thread = reinterpret_cast<xthread *>(ptr);
  return (void *)thread->run();
}

//-----------------------------------------------------------------------------
int xthread::cancel()
{
  return pthread_cancel(m_tid);
}

//-----------------------------------------------------------------------------
}
