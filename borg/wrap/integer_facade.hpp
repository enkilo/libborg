//----------------------------------------------------------------------------
//! \file  integer_facade.hpp
//! \brief Implements borg::integer_facade. 
//! \svn   $Id: integer_facade.hpp 13 2007-03-19 11:55:21Z nexbyte $
//----------------------------------------------------------------------------
#ifndef INTEGER_FACADE_HPP
#define INTEGER_FACADE_HPP

#include <borg/wrap/wrapper_facade.hpp>

namespace borg {

using namespace boost::type_traits;
  
//----------------------------------------------------------------------------
//! Provides implicit conversion and (if mutable) assignment operators.
//----------------------------------------------------------------------------
template<class Derived,
         class value = typename Derived::value_type, 
         class Traits = wrap_traits<value> >
    
struct integer_facade : public wrapper_facade<Derived, Traits>
{
  //! \name Typedefs from the traits.
  //@{
  BORG_WRAP_TRAITS(typename Traits)
  //@}
  
  //! \name Concept checks.
  //@{
  BOOST_STATIC_ASSERT(boost::is_integral<value_type>::value);
//  BOOST_CLASS_REQUIRE3(Derived, value_type, wrap_type, wrap, WrapperCoreConcept);
  //@}
  
  //! pre-increment operator.
  Derived &
  operator++() 
  { 
    ((Derived *)(this))->set(((Derived *)(this))->get() + 1);
    return *(Derived *)(this);
  }

  //! post-increment operator.
  Derived
  operator++(int)
  { 
    Derived tmp = *(Derived *)this;
    ((Derived *)(this))->set(((Derived *)(this))->get() + 1);
    return tmp;
  }

  //! add operator
  Derived &
  operator+=(Derived const &a)
  { 
    Derived tmp = *(Derived *)this;
    ((Derived *)(this))->set(((Derived const *)(this))->get() + a.get());
    return tmp;
  }

  //! conversion to boolean
  operator bool() const
  {
    return ((Derived const *)(this))->get();
  }
  
  //! boolean not operator
  bool 
  operator!() const
  {
    return !((Derived const *)(this))->get();
  }
  
  //! address operator
  const value_type *
  operator&() const
  {
    return &((Derived const *)(this))->get();
  }

  value_type *
  operator&()
  {
    return &((Derived *)(this))->get();
  }  
};

} // namespace borg
#endif //ndef INTEGER_FACADE_HPP
