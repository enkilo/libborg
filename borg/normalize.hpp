#ifndef BORG_NORMALIZE_HPP
#define BORG_NORMALIZE_HPP

#include <limits>

namespace borg {

template<typename T> 
  struct absdiff
{
  typedef T type;
  typedef T delta;

  static delta range(const type &__min, const type &__max)
  { return __max - __min; }
};

template<>
  struct absdiff<char>
{
  typedef char type;
  typedef unsigned char delta;
  
  static delta range(const type &__min, const type &__max)
  { return __max - __min; }
};

template<>
  struct absdiff<short>
{
  typedef short type;
  typedef unsigned short delta;
  
  static delta range(const type &__min, const type &__max)
  { return __max - __min; }
};

template<>
  struct absdiff<int>
{
  typedef int type;
  typedef unsigned int delta;
  
  static delta range(const type &__min, const type &__max)
  { return __max - __min; }
};

template<>
  struct absdiff<long>
{
  typedef long type;
  typedef unsigned long delta;
  
  static delta range(const type &__min, const type &__max)
  { return __max - __min; }
};

template<>
  struct absdiff<long long>
{
  typedef long long type;
  typedef unsigned long long delta;
  
  static delta range(const type &__min, const type &__max)
  { return __max - __min; }
};

template<>
  struct absdiff<float>
{
  typedef float type;
  typedef double delta;
  
  static delta range(const type &__min, const type &__max)
  { return __max - __min; }
};

template<>
  struct absdiff<double>
{
  typedef double type;
  typedef long double delta;
  
  static delta range(const type &__min, const type &__max)
  { return __max - __min; }
};


template<typename T, bool Bipolar = false>
  struct normal
{
  typedef std::numeric_limits<T> limits;

  static const bool is_specialized = false;
  static const bool is_bipolar = Bipolar;

  static T min() throw()
  { return is_bipolar ? (limits::is_integer ? limits::min() : -1) : 0; }

  static T max() throw()
  { return limits::is_integer ? limits::max() : 1; }
};

//! Unipolar specialization 0 .. max
template<typename T>
  struct normal<T, false>
{
  typedef std::numeric_limits<T> limits;

  static const bool is_specialized = false; // not fully specialised
  static const bool is_bipolar = false;

  static T min() throw() { return 0; }
  static T max() throw() { return limits::max(); }
  static T range() throw() 
  { return max() - min(); }
    
};

//! Unipolar unsigned char, usually 0 .. 255
template<>
  struct normal<unsigned char, false>
{
  typedef std::numeric_limits<unsigned char> limits;

  static const bool is_specialized = true;
  static const bool is_integer = true;
  static const bool is_signed = false;
  static const bool is_bipolar = false;

  static unsigned char min() throw() { return 0; }
  static unsigned char max() throw() { return limits::max(); }
  static unsigned char range() throw() { return max() - min(); }
};

//! Bipolar signed char, usually -128 .. 127
template<>
  struct normal<char, true>
{
  typedef std::numeric_limits<char> limits;

  static const bool is_specialized = true;
  static const bool is_integer = true;
  static const bool is_signed = true;
  static const bool is_bipolar = true;

  static char min() throw() { return limits::min(); }
  static char max() throw() { return limits::max(); }
  static unsigned char range() throw() { return max() - min(); }
};

//! Unipolar unsigned short, usually 0 .. 65535
template<>
  struct normal<unsigned short, false>
{
  typedef std::numeric_limits<unsigned short> limits;

  static const bool is_specialized = true;
  static const bool is_integer = true;
  static const bool is_signed = false;
  static const bool is_bipolar = false;

  static unsigned short min() throw() { return 0; }
  static unsigned short max() throw() { return limits::max(); }
  static unsigned short range() throw() { return max() - min(); }
};

//! Bipolar signed short, usually -32768 .. 32767 
template<>
  struct normal<short, true>
{
  typedef std::numeric_limits<short> limits;

  static const bool is_specialized = true;
  static const bool is_integer = true;
  static const bool is_signed = true;
  static const bool is_bipolar = true;

  static short min() throw() { return limits::min(); }
  static short max() throw() { return limits::max(); }
  static unsigned short range() throw() { return max() - min(); }
};

//! Unipolar unsigned int, usually 0 .. 4294967295
template<>
  struct normal<unsigned int, false>
{
  typedef std::numeric_limits<unsigned int> limits;

  static const bool is_specialized = true;
  static const bool is_integer = true;
  static const bool is_signed = false;
  static const bool is_bipolar = false;

  static unsigned int min() throw() { return 0; }
  static unsigned int max() throw() { return limits::max(); }
  static unsigned int range() throw() { return max() - min(); }
};

//! Bipolar signed int, usually -2147483648 .. 2147483647
template<>
  struct normal<int, true>
{
  typedef std::numeric_limits<int> limits;

  static const bool is_specialized = true;
  static const bool is_integer = true;
  static const bool is_signed = true;
  static const bool is_bipolar = true;

  static int min() throw() { return limits::min(); }
  static int max() throw() { return limits::max(); }
  static unsigned int range() throw() { return max() - min(); }
};

//! Unipolar float, 0.0f .. 1.0f
template<>
  struct normal<float, false>
{
  typedef std::numeric_limits<float> limits;

  static const bool is_specialized = true;
  static const bool is_integer = false;
  static const bool is_signed = true;
  static const bool is_bipolar = false;

  static float min() throw() { return 0.0f; }
  static float max() throw() { return 1.0f; }
  static float range() throw() { return 1.0f; }
};

//! Bipolar float, -1.0f .. 1.0f
template<>
  struct normal<float, true>
{
  typedef std::numeric_limits<float> limits;

  static const bool is_specialized = true;
  static const bool is_integer = false;
  static const bool is_signed = true;
  static const bool is_bipolar = true;

  static float min() throw() { return -1.0f; }
  static float max() throw() { return 1.0f; }
  static float range() throw() { return 2.0f; }
};

//! Unipolar double, 0.0f .. 1.0f
template<>
  struct normal<double, false>
{
  typedef std::numeric_limits<double> limits;

  static const bool is_specialized = true;
  static const bool is_integer = false;
  static const bool is_signed = true;
  static const bool is_bipolar = false;

  static double min() throw() { return 0.0; }
  static double max() throw() { return 1.0; }
  static double range() throw() { return 1.0; }      
};

//! Bipolar double, -1.0f .. 1.0f
template<>
  struct normal<double, true>
{
  typedef std::numeric_limits<double> limits;

  static const bool is_specialized = true;
  static const bool is_integer = false;
  static const bool is_signed = true;
  static const bool is_bipolar = true;

  static double min() throw() { return -1.0; }
  static double max() throw() { return 1.0; }
  static double range() throw() { return 2.0; }      
};  

template<typename _Tout, typename _Tin, bool Bipolar>
  _Tout normalize(const _Tin &__x, const _Tin &__min, const _Tin &__max)
{
  return (__x - __min) * normal<_Tout, Bipolar>::range() / (__max - __min) + 
    normal<_Tout, Bipolar>::min();
}

template<typename _Tout, typename _Tin, bool Bipolar>
  _Tout normalize(const _Tin &__x, const _Tin &__range)
{
  return __x * normal<_Tout, Bipolar>::range() / __range +
    normal<_Tout, Bipolar>::min();
}

template<typename _Tout, typename _Tin, bool Bipolar>
  _Tout normalize(const _Tin &__x)
{
  return static_cast<_Tout>((__x - normal<_Tin, Bipolar>::min()) * normal<_Tout, Bipolar>::range() /
    normal<_Tin, Bipolar>::range() + normal<_Tout, Bipolar>::min());
}

//----------------------------------------------------------------------------
  
} // end of namespace borg

#endif // BORG_NORMALIZE_HPP
