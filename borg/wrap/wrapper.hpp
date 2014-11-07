//----------------------------------------------------------------------------
//! \file  wrapper.hpp  
//! \brief Implements borg::wrapper.
//! \svn   $Id: wrapper.hpp 42 2007-03-23 01:49:14Z nexbyte $
//----------------------------------------------------------------------------
#ifndef BORG_WRAP_WRAPPER_HPP
#define BORG_WRAP_WRAPPER_HPP

#include <borg/wrap/wrap_traits.hpp>
#include <borg/wrap/core/wrap_as_member.hpp>
#include <borg/wrap/wrapper_facade.hpp>
#include <borg/wrap/wrapper_core_access.hpp>

namespace borg {

using namespace boost::mpl;
  
template<class derived, class traits = typename derived::traits_type>
  struct empty_t {};

//----------------------------------------------------------------------------
//! Generic wrapper, parametrized method and facade.
//----------------------------------------------------------------------------
template< class ValueT,
          class Traits = wrap_traits<ValueT>,
          class BaseT = wrap_as_member<ValueT, Traits>,
          template<class, class> class Facade = wrapper_facade,
          template<class, class> class Adapter = empty_t >
struct wrapper : public BaseT,
                 public Adapter<BaseT, Traits>,
                 public Facade<BaseT, Traits>
{
  //! \name Typedefs from traits.
  //@{
  BORG_WRAP_TRAITS(typename Traits)
  //@}
  
  //! Define ourselves.
  typedef wrapper<ValueT, Traits, BaseT, Facade, Adapter> this_type;
    
  //! Facade.
  typedef Facade<this_type, Traits> facade_type;

  //! Concept checks.
//  BOOST_CLASS_REQUIRE(wrap_type, boost, CopyConstructibleConcept);
  
  //! Initialise wrapper from \a w.
  wrapper(init_type w) 
    : BaseT(w)
  {}

  //! Create a copy of wrapper \a w.
  template< class ValueU,
            class TraitsU,
            template<class, class> class Core >
  wrapper(Core<ValueU, TraitsU> const &w)
//    : BaseT(w.get())
//    : BaseT(wrapper_core_access::get(w))
    : BaseT(w)
  {}
};

} // namespace borg

//----------------------------------------------------------------------------
#endif //ndef BORG_WRAP_WRAPPER_HPP
