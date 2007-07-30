#ifndef BORG_MAGNITUDE_HPP
#define BORG_MAGNITUDE_HPP

#include <borg/normalize.hpp>

//----------------------------------------------------------------------------
namespace borg {

template<typename T, bool Bipolar = false>
struct magnitude
{
  typedef normal<T, Bipolar> normal_type;

  static const bool is_specialized = false;
  static const bool is_bipolar = Bipolar;
  
  magnitude(T const &__mag) 
    : m_mag(__mag)
  {}

  magnitude() : m_mag(0)
  {}
  
  template<typename U>
  explicit 
  magnitude(const magnitude<U> &__mag)
    : m_mag(normalize<T, U, Bipolar>(__mag))
  {}

  operator       T &()       { return m_mag; }
  operator const T &() const { return m_mag; }

private:
  T m_mag;
};

//----------------------------------------------------------------------------

} // end of namespace borg

#endif // BORG_MAGNITUDE_HPP
