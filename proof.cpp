#include <iostream>
#include <borg/wrap/wrap_traits.hpp>
#include <borg/wrap/traits/need_const.hpp>
#include <borg/wrap/core/wrap_as_member.hpp>
#include <borg/wrap/core/inherit.hpp>
#include <borg/wrap/traits/make_reference.hpp>
#include <borg/wrap/traits/make_const.hpp>
#include <borg/wrap/traits/is_const_reference.hpp>
#include <borg/wrap/reference.hpp>
#include <borg/types/rect_type.hpp>
#include <borg/integer_traits.hpp>
#include <borg/string/char_traits.hpp>
#include <borg/xerces.hpp>

using namespace std;
using namespace borg;
using namespace boost;

struct test_me
{
  double a;
  double b;
};

#define check(e...) \
  cout << #e << ": " << e << endl;

#define PRINT_EXPR(expr) std::cout << #expr ": " << (expr) << std::endl;

template<typename T>
  void print_traits(T arg)
{
  check(boost::is_function<T>::value)
}

int main()
{
  check(boost::is_pod<int>::value);
  check(boost::has_trivial_constructor< borg::rect<int> >::value);

  check(boost::is_scalar<double>::value);
  check(boost::is_scalar<float>::value);
  check(boost::is_scalar<int>::value);
  check(boost::is_scalar<long long>::value);
      
  check(boost::is_fundamental<double>::value);
  check(boost::is_fundamental<float>::value);
  check(boost::is_fundamental<int>::value);
  check(boost::is_fundamental<long long>::value);
      
  check(boost::has_trivial_constructor<double>::value);
  check(boost::has_trivial_constructor<float>::value);
  check(boost::has_trivial_constructor<int>::value);
  check(boost::has_trivial_constructor<long long>::value);
      
  check(boost::is_const<const int>::value);
  check(boost::is_const<const int &>::value);
  check(boost::is_const<int const &>::value);
  check(boost::is_const<int &>::value);
  check(boost::is_const< boost::remove_reference<const int &>::type >::value);
  check(boost::is_const< boost::remove_reference<int const &>::type >::value);
  check(boost::is_const< boost::remove_reference<int &>::type >::value);

  check(boost::is_integral<const int>::value);
  check(boost::is_integral<const int &>::value);
  check(boost::is_integral<int const &>::value);
  check(boost::is_integral<int &>::value);
  check(boost::is_integral< boost::remove_reference<const int &>::type >::value);
  check(boost::is_integral< boost::remove_reference<int const &>::type >::value);
  check(boost::is_integral< boost::remove_reference<int &>::type >::value);

  check(boost::is_const<const int>::value);
  check(boost::is_const<const int *>::value);
  check(boost::is_const<int const *>::value);
  check(boost::is_const<int *>::value);
  check(boost::is_const< boost::remove_pointer<const int *>::type >::value);
  check(boost::is_const< boost::remove_pointer<int const *>::type >::value);
  check(boost::is_const< boost::remove_pointer<int *>::type >::value);

  check(boost::is_integral<const int>::value);
  check(boost::is_integral<const int *>::value);
  check(boost::is_integral<int const *>::value);
  check(boost::is_integral<int *>::value);
  check(boost::is_integral< boost::remove_pointer<const int *>::type >::value);
  check(boost::is_integral< boost::remove_pointer<int const *>::type >::value);
  check(boost::is_integral< boost::remove_pointer<int *>::type >::value);

  check(boost::is_same<int *, int *>::value);
  check(boost::is_same< boost::remove_pointer<int *>::type, int>::value);
  check(boost::is_same< boost::remove_reference<int &>::type, int>::value);

  check(borg::is_mutable<int>::value);
  check(borg::is_mutable<int &>::value);
  check(borg::is_mutable<int *>::value);
  check(borg::is_mutable<const int>::value);
  check(borg::is_mutable<int(int,int)>::value);
  check(boost::is_pointer<int(int,int)>::value);
  check(boost::is_reference<int(int,int)>::value);

  check(boost::has_trivial_assign<int>::value);
  check(boost::has_trivial_assign<int &>::value);
  check(boost::has_trivial_assign<int *>::value);
  check(boost::has_trivial_assign<const int>::value);
  check(boost::has_trivial_assign<const int &>::value);
  check(boost::has_trivial_assign<const int *>::value);

  check(boost::is_const< borg::need_const<int>::type >::value);
  check(boost::is_const< boost::remove_const<const int>::type >::value);
  check(boost::is_const< borg::need_const<const int>::type >::value);
  check(boost::is_const< boost::remove_const<int>::type >::value);

  check(boost::is_const< borg::need_const<int>::type >::value);
  check(boost::is_const< boost::remove_const<int const>::type >::value);
  check(boost::is_const< borg::need_const<int const>::type >::value);
  check(boost::is_const< boost::remove_const<int>::type >::value);

  check(boost::is_const<int &>::value);
  check(boost::is_const<int>::value);
  check(borg::is_mutable<int &>::value);
  check(borg::is_mutable<int>::value);

  check(boost::is_const< borg::make_reference<int>::type >::value);
  check(boost::is_const< borg::make_reference<int &>::type >::value);
  check(boost::is_reference< borg::make_reference<int>::type >::value);
  check(boost::is_reference< borg::make_reference<int &>::type >::value);

  check(boost::is_const< borg::make_reference<const int>::type >::value);
  check(boost::is_const< borg::make_reference<const int &>::type >::value);
  check(boost::is_reference< borg::make_reference<const int>::type >::value);
  check(boost::is_reference< borg::make_reference<const int &>::type >::value);

  check(borg::is_const_reference< borg::make_const_reference<int>::type >::value);
  check(borg::is_const_reference< borg::make_const_reference<int>::type >::value);
  check(borg::is_const_reference< borg::make_const_reference<int &>::type >::value);
  check(borg::is_const_reference< borg::make_const_reference<int &>::type >::value);

  check(borg::is_const_reference< borg::make_const_reference<const int>::type >::value);
  check(borg::is_const_reference< borg::make_const_reference<const int>::type >::value);
  check(borg::is_const_reference< borg::make_const_reference<const int &>::type >::value);
  check(borg::is_const_reference< borg::make_const_reference<const int &>::type >::value);

  check(boost::is_integral<char>::value);
  check(boost::is_integral<short>::value);
  check(boost::is_integral<int>::value);
  check(boost::is_integral<long>::value);
  check(boost::is_integral<long long>::value);
  check(boost::is_integral<float>::value);
  check(boost::is_integral<double>::value);
  check(boost::is_integral<long double>::value);
  
  check(boost::is_scalar<char>::value);
  check(boost::is_scalar<short>::value);
  check(boost::is_scalar<int>::value);
  check(boost::is_scalar<long>::value);
  check(boost::is_scalar<long long>::value);
  check(boost::is_scalar<float>::value);
  check(boost::is_scalar<double>::value);
  check(boost::is_scalar<long double>::value);
  
  check(boost::is_pod<char>::value);
  check(boost::is_pod<short>::value);
  check(boost::is_pod<int>::value);
  check(boost::is_pod<long>::value);
  check(boost::is_pod<long long>::value);
  check(boost::is_pod<float>::value);
  check(boost::is_pod<double>::value);
  check(boost::is_pod<long double>::value);
  
  check(boost::is_fundamental<char>::value);
  check(boost::is_fundamental<short>::value);
  check(boost::is_fundamental<int>::value);
  check(boost::is_fundamental<long>::value);
  check(boost::is_fundamental<long long>::value);
  check(boost::is_fundamental<float>::value);
  check(boost::is_fundamental<double>::value);
  check(boost::is_fundamental<long double>::value);
  
  check(borg::fits_word<char>::value);
  check(borg::fits_word<short>::value);
  check(borg::fits_word<int>::value);
  check(borg::fits_word<long>::value);
  check(borg::fits_word<long long>::value);
  check(borg::fits_word<float>::value);
  check(borg::fits_word<double>::value);
  check(borg::fits_word<long double>::value);
  
  check(borg::fits_word< borg::add_const_reference<char>::type >::value);
  check(borg::fits_word< borg::add_const_reference<short>::type >::value);
  check(borg::fits_word< borg::add_const_reference<int>::type >::value);
  check(borg::fits_word< borg::add_const_reference<long>::type >::value);
  check(borg::fits_word< borg::add_const_reference<long long>::type >::value);
  check(borg::fits_word< borg::add_const_reference<float>::type >::value);
  check(borg::fits_word< borg::add_const_reference<double>::type >::value);
  check(borg::fits_word< borg::add_const_reference<long double>::type >::value);
  
  check(boost::is_pointer< borg::reference_to_pointer<long double &>::type >::value);
  check(boost::is_pointer< borg::reference_to_pointer<long double>::type >::value);

  check(boost::is_const< boost::add_const<long>::type >::value);
  check(boost::is_const< borg::make_const<long>::type >::value);

  check(borg::is_const_reference< borg::fit_into_word<long long>::type >::value);
  check(borg::is_const_reference< borg::fit_into_word<long>::type >::value);

  check(boost::is_const< borg::need_const<int>::type >::value);
  check(boost::is_const< borg::need_const<const int>::type >::value);
//  check(boost::is_const<need_const<int &>::type>::value);
  
  cout << sizeof(long long &) << endl;

  
  
/*  int a = 10;
  encapsulate<int &> test(a);
  cout << test.get() << endl;*/

  wrap_as_member<void *> w(0);
  std::cout << w.get() << std::endl;
  
  int c = 321;
  int b = 123;
  wrap_as_member<void *> w2(&c);
  w2.set(static_cast<void *>(&b));
  std::cout << w2.get() << std::endl;
  
    
  test_me tm = { 3.141592, 8 };
  core::inherit<test_me> tmw;
  
  test_me &tmr = tmw.get();
  const test_me &tmcr = tmw.get();
  
  tmr.a = 1.5;
  
  cout << "a: " << tmcr.a << " b: " << tmcr.b << endl;
  
  int lala = 23;
  reference<int> r(lala);
  
  r = 45;
  
  PRINT_EXPR(borg::integer_traits<char>::const_bits)
  PRINT_EXPR(borg::integer_traits<short>::const_bits)
  PRINT_EXPR(borg::integer_traits<unsigned int>::const_bits)
  PRINT_EXPR(borg::integer_traits<long>::const_bits)
  PRINT_EXPR(borg::integer_traits<long long>::const_bits)

  PRINT_EXPR(sizeof(borg::char_traits< char, borg::xerces::traits >::int_type))
  PRINT_EXPR(sizeof(borg::char_traits< XMLCh, borg::xerces::traits >::int_type))

  PRINT_EXPR((borg::char_traits<char, borg::xerces::traits>::eof()))
  PRINT_EXPR(sizeof(std::char_traits<char>::int_type))
  PRINT_EXPR(std::char_traits<char>::eof())
            
  cout << lala << endl;
}
