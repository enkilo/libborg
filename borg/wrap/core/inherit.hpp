#ifndef BORG_WRAP_INHERIT_HPP
#define BORG_WRAP_INHERIT_HPP

#include <boost/concept_check.hpp>
#include <boost/utility/enable_if.hpp>
#include <borg/wrap/wrap_traits.hpp>
#include <borg/wrap/wrap_concepts.hpp>

namespace borg {
namespace core {

//! Wrapper requiring explicit initialisation and explicit unwrapping.
template< class BaseT, class Traits = wrap_traits<BaseT> >
struct inherit : public Traits::wrap_type
{
  //! \name Types from traits:
  //@{
  BORG_WRAP_TRAITS(typename Traits)
  //@}
  
  //! Checking whether wrap_type is constructible from init_type.
  BOOST_CLASS_REQUIRE2(wrap_type, init_type, borg, ConstructibleFromConcept);
  //! Checking whether wrap_type is returnable as unwrap_type.
  BOOST_CLASS_REQUIRE2(wrap_type, unwrap_type, borg, ReturnableAsConcept);
  
  //! Define ourselves.
  typedef inherit<BaseT, Traits> this_type;

  //! Create a copy of wrapper \a w.
  template<class param>
  explicit
  inherit(typename boost::lazy_enable_if<
                   ice_not< is_basically_same<param, init_type>::value >,
                   param
               >::type w) : BaseT(w.get()) {}

  //! Initialise wrapper from \a w.
//  explicit
//  inherit(init_type w) : BaseT(w) {}
  explicit
  inherit() : BaseT() {}
  
  //! Static constructor.
/*    static const_wrapper_type
  create(init_type w)
  {
    return const_wrapper_type(w);
  }*/
  
  //! Return wrapee.
  const wrap_type &
  get() const { return *static_cast<wrap_type *>(this); }

  //! Return wrapee.
  wrap_type &
  get() { return *static_cast<wrap_type *>(this); }

  //! Set a new m_wrapee \a w.
  //! Enable this method only if the wrap_type is mutable.
  template<typename param>
  typename boost::lazy_enable_if<
               is_assignable_to<param, wrap_type>,
               this_type &
           >::type
  set(param w)
  {
    // Concept check: See if wrap_type is assignable.
    boost::function_requires<boost::AssignableConcept<wrap_type> >();

    // Concept check: See if param is convertible to wrap_type.
    boost::function_requires<boost::ConvertibleConcept<param, wrap_type> >();

    // Assign new wrapee.
    *static_cast<wrap_type *>(this) = w;
    return *this;
  }
};

} // end of namespace core
} // end of namespace borg

//----------------------------------------------------------------------------
#endif //ndef BORG_WRAP_INHERIT_HPP
