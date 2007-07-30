#ifndef BORG_UTIL_ANSI_COLOR_HPP
#define BORG_UTIL_ANSI_COLOR_HPP

#include <borg/color/rgb.hpp>

namespace borg {

//---------------------------------------------------------------------------
class ansi_color;
  
//---------------------------------------------------------------------------
template<class Scalar, class T>
class ansi_color_impl
{
public:
  typedef Scalar scalar_type;
  typedef T value_type;
  
  static value_type get_r(scalar_type const &v) { return (v % 10) & 0x01; }
  static value_type get_g(scalar_type const &v) { return (v % 10) & 0x02; }
  static value_type get_b(scalar_type const &v) { return (v % 10) & 0x04; }
  
  // could these possibly be optimized? (the / 10, * 10 thing)
  static void set_r(scalar_type &v, value_type r) { int tmp = v / 10; v %= 10; v &= ~0x01; v |= r << 0; v += tmp * 10; }
  static void set_g(scalar_type &v, value_type g) { int tmp = v / 10; v %= 10; v &= ~0x02; v |= g << 1; v += tmp * 10; }
  static void set_b(scalar_type &v, value_type b) { int tmp = v / 10; v %= 10; v &= ~0x04; v |= b << 2; v += tmp * 10; }
  
  static bool is_foreground(scalar_type const &v) { return (v / 10) == 3; }
  static bool is_background(scalar_type const &v) { return (v / 10) == 4; }
  static bool is_in_range(scalar_type const &v) { return (v % 10) <= 7; }
  static bool is_valid_foreground(scalar_type const &v) { return is_in_range(v) && is_foreground(v); }
  static bool is_valid_background(scalar_type const &v) { return is_in_range(v) && is_background(v); }
  static bool is_valid(scalar_type const &v) { return is_in_range(v) && (is_foreground(v) || is_background(v)); }
  
  static scalar_type create(value_type r, value_type g, value_type b, bool bg = false) { return (bg ? 40 : 30) + (r << 0) + (g << 1) + (b << 2); }
  static scalar_type create_foreground(value_type r, value_type g, value_type b) { return 30 + (r << 0) + (g << 1) + (b << 2); }
  static scalar_type create_background(value_type r, value_type g, value_type b) { return 40 + (r << 0) + (g << 1) + (b << 2); }
};

  
//---------------------------------------------------------------------------
//! ANSI color code. Represented by a byte which must have a value between
//! 30 and 37 or 40 and 47.
//! Provides generic interface for RGB color access.
//---------------------------------------------------------------------------
class ansi_color
    : public rgb_interface< ansi_color, ansi_color_impl<boost::uint8_t, bool> >
{
public:
  typedef boost::uint8_t scalar_type;
  typedef ansi_color_impl<scalar_type, bool> impl;
  
  ansi_color(scalar_type v, bool bg = false)
    // if not valid, but in range (modulus is 0-7), create a foreground color.
    : x(impl::is_valid(v) ? v : (impl::is_in_range(v) ? (v % 10) + (bg ? 40 : 30) : 0))
  {}
  
  template<class Storage, class Impl>
  ansi_color(rgb_interface<Storage, Impl> const &rgb, bool bg = false)
    : x(impl::create(rgb.red(), rgb.green(), rgb.blue(), bg))
  {}
  
  scalar_type 
  scalar() const
  {
    return x;
  }

private:

  friend class ansi_color_impl<scalar_type,bool>;
  friend class rgb_interface<ansi_color, impl>;

  scalar_type x;

  // scalar access only by friends.
  operator scalar_type &() { return x; }
  operator scalar_type const &() const { return x; }
};
  
  
} // namespace borg
//---------------------------------------------------------------------------
#endif //ndef BORG_UTIL_ANSI_COLOR_HPP
