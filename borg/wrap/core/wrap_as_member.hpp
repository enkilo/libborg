//----------------------------------------------------------------------------
//! \file   wrap_as_member.hpp  
//! \brief  Implements the wrap_as_member class.
//!
//! \svn $Id: wrap_as_member.hpp 68 2007-04-03 19:59:53Z nexbyte $
//----------------------------------------------------------------------------
#ifndef WRAP_AS_MEMBER_HPP
#define WRAP_AS_MEMBER_HPP

#include <boost/concept_check.hpp>
#include <boost/utility/enable_if.hpp>
#include <borg/wrap/wrap_traits.hpp>
#include <borg/wrap/wrap_concepts.hpp>
#include <borg/wrap/traits/is_assignable_to.hpp>
#include <borg/wrap/traits/is_basically_same.hpp>
#include <borg/wrap/unwrap_cast.hpp>

namespace borg {

using namespace boost::type_traits;
  
//! Wrapper requiring explicit initialisation and explicit unwrapping.
template< class ValueT, class Traits = wrap_traits<ValueT> >
struct wrap_as_member
{
  //! \name Types from traits.
  //@{
  BORG_WRAP_TRAITS(typename Traits)
  //@}

  //! \name Concept checks.
  //@{  

  //! Checking whether wrap_type is constructible from init_type.
  BOOST_CLASS_REQUIRE2(wrap_type, init_type, borg, ConstructibleFromConcept);

  //! Checking whether wrap_type is returnable as unwrap_type.
  BOOST_CLASS_REQUIRE2(wrap_type, unwrap_type, borg, ReturnableAsConcept);

  //@}

  //! Define ourselves.
  typedef wrap_as_member<ValueT, Traits> this_type;
  
  //! Initialise wrapper from \a w.
  explicit
  wrap_as_member(init_type w) : m_wrapee(w) {}

  //! Create a copy of wrapper \a w.
  template<class param, class param_traits, template<class, class> class param_impl>
  explicit
  wrap_as_member(param_impl<param, param_traits> const &w) 
    : m_wrapee(w.get()) 
  {}
/*  wrap_as_member(const typename lazy_enable_if<
                     is_basically_same<param, value_type>,
                     param_impl<param, param_traits>
                 >::type &w) : m_wrapee(w.get()) {}
*/
  //! Return m_wrapee.
  
//  wrap_type const &
//  get() const { return m_wrapee; }

  typename boost::lazy_enable_if_c< Traits::is_mutable, boost::add_reference<value_type> >::type
  get() { return m_wrapee; }

  const value_type &
  get() const { return m_wrapee; }

  //! Return m_wrapee.
/*  wrap_type &
  get() { return m_wrapee; }*/

  //! Return m_wrapee as pointer if it is a reference.
/*  template<typename ret>
  typename lazy_enable_if<
      ice_or< is_pointer<value_type>::value,
              is_pointer<ret>::value >,
      ret
  >::type
  get_pointer()
  {
    function_requires<ReturnableAsConcept<wrap_type, ret> >();
    return m_wrapee;
  }*/

  //! Set a new m_wrapee \a w.
  //! Enable this method only if the wrap_type is mutable.
  template<typename param>
  typename boost::lazy_enable_if<
             is_assignable_to<param, wrap_type>,
             boost::add_reference<this_type> 
           >::type
  set(param w)
  {
    // Checking whether wrap_type is assignable.
    boost::function_requires< boost::AssignableConcept<wrap_type> >();

    // Checking whether param is convertible to wrap_type.
    boost::function_requires< boost::ConvertibleConcept<param, wrap_type> >();

    // Assign new m_wrapee.
    m_wrapee = w;
    return *this;
  }

private:
  wrap_type m_wrapee; //!< The wrapped value or object.
};

//----------------------------------------------------------------------------

template<class T, class Traits>
inline static
typename Traits::unwrap_type
unwrap_cast(const wrap_as_member<T, Traits> &w)
{
  return wrapper_core_access::get(w);
}
    
} // namespace borg

//----------------------------------------------------------------------------
#endif //ndef WRAP_AS_MEMBER_HPP
