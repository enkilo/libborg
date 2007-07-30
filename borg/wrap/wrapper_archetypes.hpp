#warning "obsolete"
//----------------------------------------------------------------------------
//! \file  wrapper_archetypes.hpp  
//! \brief Implements wrapper archetypes.
//! \svn   $Id: wrapper_archetypes.hpp 66 2007-04-03 17:06:06Z nexbyte $
//----------------------------------------------------------------------------
#ifndef WRAPPER_ARCHETYPES_HPP
#define WRAPPER_ARCHETYPES_HPP

#include <wrap/wrap_traits.hpp>

namespace borg {

//! Wrapper archetype.
template<typename T, class traits = wrap_traits<T>,
         bool is_mutable_ = Traits::is_mutable>
  class wrapper_core_archetype
{
  typedef wrapper_core_archetype<T, traits, is_mutable_> self;
  
public:
  BOOST_STATIC_CONSTANT(bool, is_mutable = is_mutable_);
  BOOST_STATIC_CONSTANT(bool, is_reference = boost::is_reference<T>::value);
  
  typedef wrapper_core_archetype<T, traits, is_mutable_> const_wrapper_type;
  typedef wrapper_core_archetype<typename Traits::mutable_traits::wrap_type,
                                   typename Traits::mutable_traits, true> mutable_wrapper_type;

  typedef typename Traits::wrap_type wrap_type;
  typedef typename Traits::init_type init_type;
  typedef typename Traits::unwrap_type unwrap_type;

  template<typename argT, typename arg_traits, bool arg_is_mutable_>
    explicit
    wrapper_core_archetype(const wrapper_core_archetype<argT, arg_traits, arg_is_mutable_> &w)
      : wrapee(w.get()) 
    {}

  explicit 
  wrapper_core_archetype(init_type w) {}

  static self 
  create(init_type w) { return self(w); }
  
  unwrap_type 
  get() const { return static_object<unwrap_type>::get(); }
};

//! Specialisation for mutable types.
template<typename T, class traits>
  class wrapper_core_archetype<T, traits, true> :
    public wrapper_core_archetype<T const, typename Traits::const_traits, false>
{
  typedef wrapper_core_archetype<T, traits, false> self;

public:
  BOOST_STATIC_CONSTANT(bool, is_implicit = false);
  BOOST_STATIC_CONSTANT(bool, is_mutable = true);
  BOOST_STATIC_CONSTANT(bool, is_reference = boost::is_reference<T>::value);

  //! Analogous const (non-mutable) wrapper, from which we inherit.
  typedef wrapper_core_archetype<T const, typename Traits::const_traits, false> const_wrapper_type;
  //! Mutable (non-const) wrapper, in effect this one.
  typedef wrapper_core_archetype<T, traits, true> mutable_wrapper_type;
  //! Type which is wrapped.
  typedef typename Traits::wrap_type wrap_type;
  //! Type from which the wrapper is initialised.
  typedef typename Traits::init_type init_type;
  //! Type from which a new wrapee is set.
  typedef typename Traits::param_type param_type;

  //! Create a copy of wrapper \a w.
  template<typename argT, typename arg_traits, bool arg_is_mutable_>
    explicit
    wrapper_core_archetype(const wrapper_core_archetype<argT, arg_traits, arg_is_mutable_> &w)
      : const_wrapper_type(w.get())
    {}

  //! Initialise wrapper from \a w.
  explicit wrapper_core_archetypes(init_type w)
    : const_wrapper_type(w) 
  {}
  
  //! Static constructor.
  static self
  create(init_type w)
  {
    return mutable_wrapper_type(w);
  }
  
  //! Set a new wrapee \a w.
  self &
  set(param_type w) 
  {
    const_cast<typename Traits::wrap_type &>(const_wrapper_type::wrapee) = w;
    return *this;
  }
};

} // end of namespace borg
#endif //ndef WRAPPER_ARCHETYPES_HPP
