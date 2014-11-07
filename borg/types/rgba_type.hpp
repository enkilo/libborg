#ifndef BORG_TYPES_RGBA_HPP
#define BORG_TYPES_RGBA_HPP

#include <boost/static_assert.hpp>
#include <borg/magnitude.hpp>

namespace borg {

//! Generic RGBA primitive.
template<class T>
struct rgba
{
  BOOST_STATIC_ASSERT(!std::numeric_limits<T>::is_integer ||
                      !std::numeric_limits<T>::is_signed);

  //! Default constructor.
  rgba() : 
    r(0), g(0), b(0), a(normal<T>::max()) // default alpha is opaque
  {}

  //! Construct from magnitude values.
  template<class U>
  rgba(const magnitude<U> &__r, const magnitude<U> &__g,
       const magnitude<U> &__b, const magnitude<U> &__a = normal<U>::max()) 
    : r(__r)
    , g(__g)
    , b(__b)
    , a(__a)
  {}

  //! Construct from scalar values.
  template<class U>
    rgba(const U &__r,
         const U &__g,
         const U &__b, 
         const U &__a = normal<U>::max()) 
    : r(__r)
    , g(__g)
    , b(__b)
    , a(__a)
  {}

  //! Copy construct.
  template<class U>
    rgba
      (const U &__rgba) 
    : r(__rgba.r)
    , g(__rgba.g)
    , b(__rgba.b)
    , a(__rgba.a)
  {}

  //! Set by scalar values of the same type.
  rgba &operator()
    (const T &__r,
     const T &__g,
     const T &__b, 
     const T &__a)
  {
    r = __r; g = __g; b = __b; a = __a;
    return *this; 
  }

  //! Comparision.
  bool operator!=(const rgba &other) const 
  { 
    return (r != other.r || g != other.g ||
            b != other.b || a != other.a); 
  }
  
  //! Comparision.
  bool operator==(const rgba &other) const
  { 
    return (r == other.r && g == other.g &&
            b == other.b && a == other.a);
  }
  
  //@{
  //! Magnitude members.
  magnitude<T> r;
  magnitude<T> g;
  magnitude<T> b;
  magnitude<T> a;
  //@}
};

} // end of namespace borg

//! Stream insertion operator for RGBA colors.
template<typename rgbaT, typename charT, class traits>
  std::basic_ostream<charT, traits> &
  operator<<(std::basic_ostream<charT, traits> &os, const borg::rgba<rgbaT> &r)
{
  std::basic_ostringstream<charT, traits> s;
  
  s.flags(os.flags() | std::ios_base::hex);
  s.imbue(os.getloc());
  s.precision(os.precision());
  
  s << '{'
    << (double)r.r << ',' << (double)r.g << ','
    << (double)r.b << ',' << (double)r.a
    << '}';
  
  return os << s.str();
}

#endif // BORG_TYPES_RGBA_HPP
