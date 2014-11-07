#warning "obsolete"
//----------------------------------------------------------------------------
//! \file  implicit_wrapper.hpp  
//! \brief Implements wrap::implicit_wrapper.
//! \svn   $Id: implicit_wrapper.hpp 66 2007-04-03 17:06:06Z nexbyte $
//----------------------------------------------------------------------------
#ifndef IMPLICIT_WRAPPER_HPP
#define IMPLICIT_WRAPPER_HPP

#include <wrap/wrap_as_member.hpp>
#include <wrap/wrapper_facade.hpp>

namespace wrap {
  
  //! Wrapper allowing implicit initialisation and implicit unwrapping.
  template<typename T, class traits = wrap_traits<T>,
           bool is_mutable_ = traits::is_mutable>
    struct implicit_wrapper :
    public wrap_as_member<T, traits, is_mutable_>,
    public wrapper_facade<implicit_wrapper<T, traits, is_mutable_>, T, traits>
  {
    //! Define ourselves.
    typedef implicit_wrapper<T, traits, is_mutable_> this_type;
    //! Define our traits.
    typedef traits traits_type;
    //! Type which is wrapped.
    typedef typename traits::value_type value_type;
    //! Type which is effectively wrapped.
    typedef typename traits::wrap_type wrap_type;
    //! Type from which the wrapper is initialised.
    typedef typename traits::init_type init_type;
    //! Type which is returned from get method.
    typedef typename traits::unwrap_type unwrap_type;
    //! Type which is expected by the set method.
    typedef typename traits::param_type param_type;

    //! Concept checks.
    BOOST_CLASS_REQUIRE(wrap_type, boost, CopyConstructibleConcept);
    
    //! Cannot be changed once initialized.
    BOOST_STATIC_CONSTANT(bool, is_mutable = is_mutable_);

    //! Analogous explicit wrapper (the one we inherit from).
    typedef wrap_as_member<value_type, traits, is_mutable_> wrap_as_member_type;

    //! Create a copy of wrapper \a w.
    template<typename argT, typename arg_traits, bool arg_is_mutable_>
      implicit_wrapper(const wrap_as_member<argT, arg_traits, arg_is_mutable_> &w)
      : wrap_as_member_type(w.get())
    {}
    
    //! Initialise wrapper from \a w.
    implicit_wrapper(init_type w) 
      : wrap_as_member_type(w)
    {}
  };

} // end of namespace wrap
#endif //ndef IMPLICIT_WRAPPER_HPP
