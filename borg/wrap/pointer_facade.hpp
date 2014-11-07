#ifndef BORG_WRAP_POINTER_FACADE_HPP
#define BORG_WRAP_POINTER_FACADE_HPP

namespace borg {

using namespace boost::type_traits;
  
//----------------------------------------------------------------------------
//! Provides implicit conversion and (if mutable) assignment operators.
//----------------------------------------------------------------------------
template<class Derived, class Traits>
struct pointer_facade
{
  //! \name Typedefs from the traits.
  //@{
  BORG_WRAP_TRAITS(typename Traits)
  //@}
  
  //! \name Concept checks.
  //@{
  BOOST_STATIC_ASSERT(boost::is_pointer<value_type>::value);
//  BOOST_CLASS_REQUIRE3(Derived, value_type, wrap_type, wrap, WrapperCoreConcept);
  //@}
  
  typedef typename boost::remove_pointer<value_type>::type pointee_type;
    
  //! Implicit conversion to value_type
  operator value_type() const
  {
   return wrapper_core_access::get(*reinterpret_cast<Derived const *const>(this));
  }

  //! Assignment operator, enabled only if param is assignable to value_type.
  template<class ValueU>
  Derived &
  operator=(typename boost::lazy_enable_if<
                is_assignable_to<ValueU, value_type>,
                typename const_traits::param_type
            >::type w)
  {
//    static_cast<derived *>(this)->set(w);
    wrapper_core_access::set(static_cast<Derived *const>(this), w);
    return *static_cast<Derived *>(this);
  }

  //! const dereference operator.
  template<class ret>
  typename boost::lazy_enable_if_c<
      ice_not< boost::is_void<pointee_type>::value >::value, ret >::type
  operator*() const
  { 
    return wrapper_core_access::get(*reinterpret_cast<Derived const *const>(this));
    //return const_cast<derived *>(reinterpret_cast<derived const *>(this))->get();
  }

  //! pre-increment operator.
  Derived &
  operator++() 
  { 
    ((Derived *)(this))->set(((Derived const *)(this))->get() + 1);
    return *(Derived *)(this);
  }

  //! post-increment operator.
  Derived
  operator++(int)
  { 
    Derived tmp = *(Derived const *)this;
    ((Derived *)(this))->set(((Derived const *)(this))->get() + 1);
    return tmp;
  }

  //! arrow operator
  unwrap_type 
  operator->() const
  { 
    return wrapper_core_access::get(*reinterpret_cast<Derived const *const>(this));
//    return const_cast<Derived *>(reinterpret_cast<Derived const *>(this))->get();
  }

  //! conversion to boolean
  operator bool() const
  {
    return ((Derived const *)(this))->get() != 0;
  }
  
  //! boolean not operator
  bool 
  operator!() const
  {
    return ((Derived const *)(this))->get() == 0;
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

}// namespace borg
//----------------------------------------------------------------------------
#endif //ndef POINTER_FACADE_HPP
