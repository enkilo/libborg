#ifndef SIZE_TYPE_HPP
#define SIZE_TYPE_HPP

#include <ostream>

namespace borg
{
  //! Structure size
  template<typename T>
    struct size
  {
    //! Value typedef.
    typedef T value_type;
    
    //! Default constructor.
    //! Unspecified parameters default to 0.
    explicit size(const T &__w = T(), const T &__h = T());
    
    // Lets the compiler synthesize the copy constructor   
    // size (const size<T>&);
    //!  Copy constructor.
    template<typename U> size(const size<U> &__pt);
    
    T &w();
    const T &w() const;
    T &h();
    const T &h() const;
    
    //! Calc the angle.
    template<typename _Ta>
      _Ta angle() const
    {
      return atan2(_M_h, _M_w);
    }
    
    //! Subtraction operator.
    template<typename U>
      size<T> &operator-=(const size<U> &__pt);
    
    //! Add scalar x and y offsets.
    size<T> &offset(const T &__w, const T &__h);
    
  private:
    T _M_w;
    T _M_h;
  };

  template<typename T>
    inline T &
    size<T>::w() { return _M_w; }

  template<typename T>
    inline const T &
    size<T>::w() const { return _M_w; }

  template<typename T>
    inline T &
    size<T>::h() { return _M_h; }

  template<typename T>
    inline const T &
    size<T>::h() const { return _M_h; }

  template<typename T>
    inline
    size<T>::size(const T& __w, const T& __h)
    : _M_w(__w), _M_h(__h) { }

  template<typename T>
    template<typename U>
    inline
    size<T>::size(const size<U>& __sz)
    : _M_w(static_cast<T>(__sz.w())),
      _M_h(static_cast<T>(__sz.h()))
  {}
  
  //! Subtraction operator.
  template<typename T>
    template<typename U>
    inline
    size<T> &size<T>::operator-=(const size<U> &__sz)
  {
    _M_w -= static_cast<T>(__sz.w());
    _M_h -= static_cast<T>(__sz.h());
    return *this;
  }

} // end namespace std

//! Stream insertion operator for sizes.
template<typename _Tsize, typename charT, class traits>
  std::basic_ostream<charT, traits> &
  operator<<(std::basic_ostream<charT, traits> &os, const borg::size<_Tsize> &sz)
{
  std::basic_ostringstream<charT, traits> s;

  s.flags(os.flags() | std::ios_base::hex);
  s.imbue(os.getloc());
  s.precision(os.precision());

  s << '['
    << sz.w() << ',' << sz.h()
    << ']';

  return os << s.str();
}

#endif // SIZE_TYPE_HPP

