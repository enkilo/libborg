#ifndef RECT_TYPE_HPP
#define RECT_TYPE_HPP

#include <borg/types/point_type.hpp>
#include <borg/types/size_type.hpp>

namespace borg
{
  //! Structure rect
  template<typename T>
  struct rect : public point<T>, public size<T>
  {
    //! Value typedef.
    typedef T value_type;
    typedef point<value_type> point_type;
    
    //! Default constructor.
    //! Unspecified parameters default to 0.
    rect(const T &__x = T(), const T &__y = T(),
         const T &__w = T(), const T &__h = T());
    
    rect(const point_type &__pt, const size<T> &__sz);
    
    rect(const point_type &s, const point_type &e);
    
    // Lets the compiler synthesize the copy constructor   
    // rect (const rect<T>&);
    //!  Copy constructor.
    template<typename U>
    rect(const rect<U> &__pt);
    
/*    T &x();
    const T &x() const;
    T &y();
    const T &y() const;
    T &w();
    const T &w() const;
    T &h();
    const T &h() const;*/

    T x2() const;
    T y2() const;
    
    rect<T> &operator()(const T &__x, const T &__y,
                        const T &__w, const T &__h);
    
    //! Get the center of the rectangle.
    point_type center() const;
    
    rect<T> merge(const rect<T> &r);
    //! Add scalar x and y offsets.
//    rect<T> &offset(const T &__x, const T &__y);

/*  private:
    T _M_x;
    T _M_y;
    T _M_w;
    T _M_h;*/
  };

/*  template<typename T>
    inline T &
    rect<T>::x() { return _M_x; }

  template<typename T>
    inline const T &
    rect<T>::x() const { return _M_x; }

  template<typename T>
    inline T &
    rect<T>::y() { return _M_y; }

  template<typename T>
    inline const T &
    rect<T>::y() const { return _M_y; }

  template<typename T>
    inline T &
    rect<T>::w() { return _M_w; }

  template<typename T>
    inline const T &
    rect<T>::w() const { return _M_w; }

  template<typename T>
    inline T &
    rect<T>::h() { return _M_h; }

  template<typename T>
    inline const T &
    rect<T>::h() const { return _M_h; }*/

  template<typename T>
    inline
    rect<T>::rect(const point_type &__pt, const size<T> &__sz) :
      point_type(__pt), size<T>(__sz)
  {}
  
  template<typename T>
    inline
    rect<T>::rect(const point_type &s, const point_type &e) :
      point_type(s), size<T>(e.x() - s.x(), e.y() - s.y())
  {}
  
  template<typename T>
    inline T
    rect<T>::x2() const { return point_type::x() + size<T>::w(); }

  template<typename T>
    inline T
    rect<T>::y2() const { return point_type::y() + size<T>::h(); }

  template<typename T>
    inline rect<T> &
    rect<T>::operator()(const T &__x, const T &__y,
                          const T &__w, const T &__h)
  {
    point_type::x() = __x;
    point_type::y() = __y;
    size<T>::w() = __w;
    size<T>::h() = __h;
    return *this;
  }
    
  template<typename T>
    inline
    rect<T>::rect(const T& __x, const T& __y,
                    const T& __w, const T& __h)
    : point_type(__x, __y), size<T>(__w, __h)
  {}

  template<typename T>
    template<typename U>
    inline
    rect<T>::rect(const rect<U>& __rc) :
      point_type(__rc), size<T>(__rc)
  {}

  //! Get the center of the rectangle.
  template<typename T>
    inline
    point<T> rect<T>::center() const
  {
    return point_type(point_type::x() + size<T>::w() / 2, point_type::y() + size<T>::h() / 2);
  }
  
//! Merge with another rectangle.
  template<typename T>
    inline
    rect<T> rect<T>::merge(const rect<T> &r)
  {
    point_type s(r.x() < point_type::x() ? r.x() : point_type::x(),
                 r.y() < point_type::y() ? r.y() : point_type::y());
    
    point_type e(r.x2() > point_type::x() ? r.x2() : x2(),
                 r.y2() < point_type::y() ? r.y2() : y2());
    
    return rect<T>(s, e);
  }
    
  
} // end namespace std

//! Stream insertion operator for rgba colors.
template<typename _Trect, typename charT, class traits>
  std::basic_ostream<charT, traits> &
  operator<<(std::basic_ostream<charT, traits> &os, const borg::rect<_Trect> &r)
{
  std::basic_ostringstream<charT, traits> s;

  s.flags(os.flags() | std::ios_base::hex);
  s.imbue(os.getloc());
  s.precision(os.precision());

  s << '['
    << r.x() << ',' << r.y() << '|'
    << r.w() << 'x' << r.h()
    << ']';

  return os << s.str();
}

//! Stream insertion operator for rgba colors.
template<typename _Trect>
  std::ostream &
  operator<<(std::ostream &os, const borg::rect<_Trect> &r)
{
  std::ostringstream s;

  s.flags(os.flags() | std::ios_base::hex);
  s.imbue(os.getloc());
  s.precision(os.precision());

  s << '['
    << r.x() << ',' << r.y() << '|'
    << r.w() << 'x' << r.h()
    << ']';

  return os << s.str();
}

#endif // RECT_TYPE_HPP
