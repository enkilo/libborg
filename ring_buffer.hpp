#ifndef CXX_RING_BUFFER
#define CXX_RING_BUFFER

#include <interface/buffer.hpp>

template<typename T>
class ring_buffer : virtual public buffer<T>
{  
protected:
  T *m_data;
  size_t m_size;
  size_t m_head;
  size_t m_tail;
  
public:
  ring_buffer<T>(size_t n = 1024)
  {
    m_data = new T[n];
    m_size = n;
    m_head = m_tail = 0;
  }
  
  virtual ~ring_buffer<T>() {}
  
  virtual size_t size() const { return m_size; }
  virtual inline size_t length() const;

  virtual inline const T &operator[](size_t index) const;
  virtual inline T &operator[](size_t index);
  
  virtual inline size_t put(const T &s);
  virtual inline size_t put(const T *s, size_t n);
  
  virtual inline size_t get(T &s);
  virtual inline size_t get(T *s, size_t n);
};

template<typename T>
inline size_t ring_buffer<T>::length() const
{
  return (m_head >= m_tail) ? (m_head - m_tail) : (m_size - m_tail + m_head);
}

template<typename T>
inline const T &ring_buffer<T>::operator[](size_t index) const
{
  return m_data[index];
}

template<typename T>
inline T &ring_buffer<T>::operator[](size_t index)
{
  return m_data[index];
}

template<typename T>
inline size_t ring_buffer<T>::put(const T &s)
{
  m_data[m_head++] = s;
  if(m_head == m_size) m_head = 0;
  if(m_head == m_tail) 
  {
    m_tail++;
    if(m_tail == m_size) m_tail = 0;
  }
  return 1;
}

template<typename T>
inline size_t ring_buffer<T>::put(const T *s, size_t n)
{
  register size_t cnt = n;
  while(cnt--)
  {
    m_data[m_head++] = *s++;
    if(m_head == m_size) m_head = 0;
    if(m_head == m_tail)
    {
      m_tail++;
      if(m_tail == m_size) m_tail = 0;
    }
  }
  return n;
}

template<typename T>
inline size_t ring_buffer<T>::get(T &s)
{
  if(m_head == m_tail) return 0;
  s = m_data[m_tail++];
  if(m_tail == m_size) m_tail = 0;
  return 1;
}

template<typename T>
inline size_t ring_buffer<T>::get(T *s, size_t n)
{
  if(n > ring_buffer<T>::length())
    n = ring_buffer<T>::length();
  
  register size_t cnt = n;
  while(cnt--)
  {
    *s++ = m_data[m_tail++];
    if(m_tail == m_size) m_tail = 0;
  }
  return n;
}

#endif /* CXX_RING_BUFFER */
