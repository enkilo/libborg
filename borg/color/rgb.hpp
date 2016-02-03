#ifndef BORG_COLOR_RGB_HPP
#define BORG_COLOR_RGB_HPP

#include <boost/cstdint.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <borg/preproc.hpp>
#include <borg/util/dereference_cast.hpp>
#include <string>

//---------------------------------------------------------------------------
namespace borg
{

//---------------------------------------------------------------------------
//! Color container.
//---------------------------------------------------------------------------
template<class T>
struct rgb_value
{
  typedef T value_type;
  
  T r;
  T g;
  T b;
};
  
//---------------------------------------------------------------------------
//! Color container, specialised for 1 bit per channel. 
//! Packs them into a byte as follows: 1 = red, 2 = green, 4 = blue, which 
//! can be directly used as the decimal modulus of ANSI colors (+30 for 
//! foreground and +40 for background).
//---------------------------------------------------------------------------
template<>
struct rgb_value<bool>
{
  typedef bool value_type;
  
  boost::uint8_t x; //!< packed color value.
};


//---------------------------------------------------------------------------
//! RGB color implementation. Implements static getters and setters, taking
//! the color container as first argument.
//---------------------------------------------------------------------------
template<class Container, class T = typename Container::value_type>
class rgb_impl
{
public:
  typedef T value_type;

  static value_type &get_r(Container &c) { return c.r; }
  static value_type &get_g(Container &c) { return c.g; }
  static value_type &get_b(Container &c) { return c.b; }

  static value_type const &get_r(Container const &c) { return c.r; }
  static value_type const &get_g(Container const &c) { return c.g; }
  static value_type const &get_b(Container const &c) { return c.b; }

  static void set_r(Container &c, value_type r) { c.r = r; }
  static void set_g(Container &c, value_type g) { c.g = g; }
  static void set_b(Container &c, value_type b) { c.b = b; }
};
  
//---------------------------------------------------------------------------
template< template<class T> class ContainerTmpl >
class rgb_impl< ContainerTmpl<bool> >
{
public:
  typedef ContainerTmpl<bool> container_type;
  typedef bool value_type;

  // Facing a similar problem than std::container<bool> whose iterator
  // is forced to return a proxy rather than a reference.
  // 
  // However having a set_X() method we do not require a reference
  // and thus can keep it simple.
  static value_type get_r(container_type const &c) { return c.x & 0x01; }
  static value_type get_g(container_type const &c) { return c.x & 0x02; }
  static value_type get_b(container_type const &c) { return c.x & 0x04; }

  static void set_r(container_type &c, value_type r) { c.x &= ~0x01; c.x |= r << 0; }
  static void set_g(container_type &c, value_type g) { c.x &= ~0x02; c.x |= g << 1; }
  static void set_b(container_type &c, value_type b) { c.x &= ~0x04; c.x |= b << 2; }
};
  
//---------------------------------------------------------------------------
//! Generic RGB color interface. Every adapter color should inherit from it 
//! and provide the backing rgb_impl class.
//---------------------------------------------------------------------------
template<class Derived, class Impl>
class rgb_interface
{
public:
  BORG_PP_USE_TYPE(typename Impl, value_type)

  value_type red()   const { return Impl::get_r(dereference_cast<Derived const>(this)); }
  value_type green() const { return Impl::get_g(dereference_cast<Derived const>(this)); }    
  value_type blue()  const { return Impl::get_b(dereference_cast<Derived const>(this)); }

  void red  (value_type r) { return Impl::set_r(dereference_cast<Derived>(this), r); }
  void green(value_type g) { return Impl::set_g(dereference_cast<Derived>(this), g); }
  void blue (value_type b) { return Impl::set_b(dereference_cast<Derived>(this), b); }
};
  
//---------------------------------------------------------------------------
//! Concrete RGB color class.
//---------------------------------------------------------------------------
template<class T>
class rgb 
    : private rgb_value<T>
    , public rgb_interface< rgb<T>, rgb_impl<rgb_value<T>, T> >
{
  typedef rgb_impl<rgb_value<T>, T> impl;
  typedef T value_type;
  
  friend class rgb_interface< rgb<T>, impl >;
  
public:
  
  rgb() {}
  
  rgb(std::string const &str)
  {
    std::istringstream istrm(str);
    istrm >> (*this);
  }
  
/*  template<class U>
  rgb(rgb<U> const &rgb)
  {
    impl::set_r(*this, rgb.red());
    impl::set_g(*this, rgb.green());
    impl::set_b(*this, rgb.blue());
  }*/
  
  rgb(rgb<T> const &rgb)
  {
    impl::set_r(*this, rgb.red());
    impl::set_g(*this, rgb.green());
    impl::set_b(*this, rgb.blue());
  }
  
  rgb(T const &r, T const &g, T const &b)
  {
    // hmmn, doing this in the initializer list would be preferrable.
    // but as we're generic it's the impl class that handles the mapping 
    // to the underlying scalar(s).
    // 
    // how about impl::create, a static constructor function which returns
    // the scalar? 
    // this wouldn't scale to large value types and is probably more expensive
    // than the following calls (nifty compilers would inline both the same way
    // anyway).
    impl::set_r(*this, r);
    impl::set_g(*this, g);
    impl::set_b(*this, b);
  }
};
  
  
} // namespace borg

//---------------------------------------------------------------------------
template<class RGB, class Impl, class CharT, class Traits>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> &input, 
           borg::rgb_interface<RGB, Impl> &rgb)
{
  BORG_PP_USE_TYPE(typename Impl, value_type);

//  value_type v;
  double v;
  input >> v; rgb.red((value_type)v); input.get();
  input >> v; rgb.green((value_type)v); input.get();
  input >> v; rgb.blue((value_type)v);
  return input;  
}

template<class T, class CharT, class Traits>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> &input, 
           borg::rgb<T> &rgb)
{
  typedef T value_type;

//  value_type v;
  double v;
  input >> v; rgb.red((T)v); input.get();
  input >> v; rgb.green((T)v); input.get();
  input >> v; rgb.blue((T)v);
  return input;  
}

//---------------------------------------------------------------------------
/*template<class RGB, class Impl, class CharT, class Traits>
typename boost::enable_if
<
    boost::is_integral<typename Impl::value_type>
  , std::basic_ostream<CharT, Traits> & 
>::type
operator<<(std::basic_ostream<CharT, Traits> &output,
           borg::rgb_interface<RGB, Impl> const &rgb)
{
  output << (long)rgb.red();
  output << ',';
  output << (long)rgb.green();
  output << ',';
  output << (long)rgb.blue();
  return output;
}
*/
template<class T>
std::ostream &
operator<<(std::ostream &output, borg::rgb<T> const &rgb)
{
/*  output << (int)rgb.red();
  output << ',';
  output << (int)rgb.green();
  output << ',';
  output << (int)rgb.blue();*/
#warning heh?
  return output;
}

//---------------------------------------------------------------------------
//! This will allow the use of any class using borg::rgb_interface (<- not true ATM, its only borg::rgb) together
//! with boost::program_options.
//---------------------------------------------------------------------------  
#include <boost/program_options.hpp>

namespace boost {
namespace program_options {

/*template<class T>
inline static void
validate(any &v, const std::vector<std::string> &values,
         borg::rgb<T> *, int)
{
  if(v.empty())
    v = any(borg::rgb<T>());

  borg::rgb<T> *rgb = any_cast< borg::rgb<T> >(&v);

  for(int i = 0; i < values.size(); ++i)
  {
//    try {
//      *rgb = lexical_cast< borg::rgb<T> >(values[i]);
//    }
//    catch(const bad_lexical_cast &e) {
//      throw_exception(invalid_option_value(values[i]));
//    }
  }
}
*/
//---------------------------------------------------------------------------

} // namespace program_options
} // namespace boost

//---------------------------------------------------------------------------
#endif //ndef BORG_COLOR_RGB_HPP
