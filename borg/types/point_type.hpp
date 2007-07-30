#ifndef POINT_TYPE_HPP
#define POINT_TYPE_HPP

#include <math.h>
#include <complex>

namespace borg
{
  //! Structure point
  template<typename T>
    struct point
  {
    //! Value typedef.
    typedef T value_type;
    
    static const double pi = 3.14159265358979323846;
  
    //! Default constructor.
    //! Unspecified parameters default to 0.
    explicit point(const T &__x = T(), const T &__y = T());
    
    //! Construct from complex.
    point(const std::complex<T> &__z);
    
    // Lets the compiler synthesize the copy constructor   
    // point (const point<T>&);
    //!  Copy constructor.
    template<typename U> point(const point<U> &__pt);
    
    T &x();
    const T &x() const;
    T &y();
    const T &y() const;
    
    //! Calc the angle.
    template<typename _Ta>
      _Ta angle() const
    {
      return atan2(_M_y, _M_x);
    }
    
    //! Subtraction operator.
    template<typename U>
      point<T> &operator-=(const point<U> &__pt);
    
    //! Add scalar x and y offsets.
    point<T> &offset(const T &__x, const T &__y);
    
  private:
    T _M_x;
    T _M_y;
  };

  template<typename T>
    inline T &
    point<T>::x() { return _M_x; }

  template<typename T>
    inline const T &
    point<T>::x() const { return _M_x; }

  template<typename T>
    inline T &
    point<T>::y() { return _M_y; }

  template<typename T>
    inline const T &
    point<T>::y() const { return _M_y; }

  template<typename T>
    inline
    point<T>::point(const T& __x, const T& __y)
    : _M_x(__x), _M_y(__y) { }

  template<typename T>
    inline
    point<T>::point(const std::complex<T> &__z)
    : _M_x(__z.real()), _M_y(__z.imag()) 
  {}

  template<typename T>
    template<typename U>
    inline
    point<T>::point(const point<U>& __pt)
    : _M_x(static_cast<T>(__pt.x())),
      _M_y(static_cast<T>(__pt.y()))
  {}
  
  //! Subtraction operator.
  template<typename T>
    template<typename U>
    inline
    point<T> &point<T>::operator-=(const point<U> &__pt)
  {
    _M_x -= static_cast<T>(__pt.x());
    _M_y -= static_cast<T>(__pt.y());
    return *this;
  }

  // Calc the angle.
  template</*typename T*/>
    template</*typename _Ta*/>
    inline double point<int>::angle<double>() const
  {
    double a;
    if(_M_x == 0)
    {
      if(_M_y == 0) a = 0;
      else a = (_M_y <= 0 ? 0 : pi);
    }
    else
    {
      if(_M_y == 0) a = (_M_x < 0 ? -pi : pi) / 2;
      else a = atan2(_M_y, _M_x);
    }
    return a;
  }

} // end namespace std

template<typename T, typename U>
  inline
  borg::point<T> operator-(const borg::point<T> &__pt1, const borg::point<U> &__pt2)
{
  borg::point<T> ret = __pt1;
  ret -= __pt2;
/*  borg::point<T> ret(__pt1.x() - static_cast<T>(__pt2.x()),
                      __pt1.y() - static_cast<T>(__pt2.y()));*/
  return ret;
}

//! Stream insertion operator for points.
template<typename Toint, typename charT, class traits>
  std::basic_ostream<charT, traits> &
  operator<<(std::basic_ostream<charT, traits> &os, const borg::point<Toint> &pt)
{
  std::basic_ostringstream<charT, traits> s;

  s.flags(os.flags()/* | std::ios_base::hex*/);
  s.imbue(os.getloc());
  s.precision(os.precision());

  s << '['
    << pt.x() << ',' << pt.y() 
    << ']';

  return os << s.str();
}

#endif // POINT_TYPE_HPP

