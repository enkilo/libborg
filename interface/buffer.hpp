#ifndef _CXX_buffer_
#define _CXX_buffer_

#include <cstddef>

template<typename T> class buffer
{
public:
  virtual ~buffer<T>() {}

  virtual size_t length() const = 0;
  virtual size_t size() const = 0;
  virtual bool resize(size_t size) { return false; };

  virtual size_t get(T &s) = 0;
  virtual size_t get(T *s, size_t n) = 0;
  
  virtual inline size_t peek(T &s, size_t index = 0) const;
  virtual inline size_t peek(T *s, size_t n, size_t index = 0) const;

  virtual size_t put(const T &s) = 0;
  virtual size_t put(const T *s, size_t n) = 0;

  virtual inline bool poke(const T &s, size_t index = 0);
  virtual inline bool poke(const T *s, size_t n, size_t index = 0);
  
  virtual inline buffer<T> &operator<<(const T &s);
  virtual inline buffer<T> &operator>>(T &s);

  virtual const T &operator[](size_t index) const = 0;
  virtual T &operator[](size_t index) = 0;
};

template<typename T>
  inline size_t buffer<T>::peek(T &s, size_t index) const
{
  if(length() > index)
  {
    s = (*this)[index++];
    return 1;
  }
  return 0;
}

template<typename T>
  inline size_t buffer<T>::peek(T *s, size_t n, size_t index) const
{
  if(length() < index + n)
    n = length();

  register size_t cn = n;
  while(cn--)
    *s++ = (*this)[index++];
  return n;
}

template<typename T>
  inline bool buffer<T>::poke(const T &s, size_t index)
{
  if(length() > index)
  {
    (*this)[index] = s;
    return 1;
  }
  return 0;
}


template<typename T>
  inline bool buffer<T>::poke(const T *s, size_t n, size_t index)
{
  if(length() < index + n)
    n = length();
  
  register size_t cn = n;

  while(cn--)
    (*this)[index++] = *s++;

  return n;
}

template<typename T>
  inline buffer<T> &buffer<T>::operator<<(const T &s)
{
  put(s);
  return *this;
}

template<typename T>
  inline buffer<T> &buffer<T>::operator>>(T &s)
{
  get(s);
  return *this;
}

#endif /* _CXX_buffer_ */
