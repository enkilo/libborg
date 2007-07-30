#ifndef _CXX_reverse_buffer_
#define _CXX_reverse_buffer_

#include <interface/buffer.hpp>

template<typename T>
  class reverse_buffer : public buffer<T>
{  
protected:
  T *m_data;
  size_t m_size;
  size_t m_head;
  size_t m_tail;
  
public:
  reverse_buffer<T>(size_t n = 1024)
  {
    m_data = new T[n];
    m_size = n;
    m_head = m_tail = n - 1;
  }
  
  virtual ~reverse_buffer<T>() {}
  
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
  inline size_t reverse_buffer<T>::length() const
{
  return (m_head <= m_tail) ? (m_tail - m_head) : (m_size - m_head + m_tail);
}

template<typename T>
  inline const T &reverse_buffer<T>::operator[](size_t index) const
{
  return m_data[(m_head + index) % m_size];
}

template<typename T>
  inline T &reverse_buffer<T>::operator[](size_t index)
{
  return m_data[(m_head + index) % m_size];
}

template<typename T>
  inline size_t reverse_buffer<T>::put(const T &s)
{
  m_data[m_head] = s;
  if(m_head == 0) m_head = m_size;
  m_head--;
  if(m_head == m_tail)
  {
    if(m_tail == 0) m_tail = m_size;
    m_tail--;
  }
  return 1;
}

template<typename T>
  inline size_t reverse_buffer<T>::put(const T *s, size_t n)
{
  register size_t cnt = n;
  while(cnt--)
  {
    m_data[m_head] = *s++;
    if(m_head == 0) m_head = m_size;
    m_head--;
    if(m_head == m_tail) {
      if(m_tail == 0) m_tail = m_size;
      m_tail--;
    }
  }
  return n;
}

template<typename T>
  inline size_t reverse_buffer<T>::get(T &s)
{
  if(m_head == m_tail) return 0;
  s = m_data[m_tail];
  if(m_tail == 0) m_tail = m_size;
  m_tail--;
  return 1;
}

template<typename T>
  inline size_t reverse_buffer<T>::get(T *s, size_t n)
{
  if(n > reverse_buffer<T>::length())
    n = reverse_buffer<T>::length();
  
  register size_t cnt = n;
  while(cnt--)
  {
    *s++ = m_data[m_tail];
    if(m_tail == 0) m_tail = m_size;
    m_tail--;
  }
  return n;
}

#endif /* _CXX_reverse_buffer_ */
