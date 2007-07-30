#ifndef BORG_WRAP_REFERENCE_HPP
#define BORG_WRAP_REFERENCE_HPP

#include <boost/ref.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/wrap/reference_adapter.hpp>
#include <borg/wrap/reference_facade.hpp>

namespace borg {
 
//---------------------------------------------------------------------------
template<
    class ValueT,
    class Traits = wrap_traits< boost::reference_wrapper<ValueT> >,
    template<class, class> class adapter = reference_adapter 
>
struct reference : protected boost::reference_wrapper<ValueT>
{
  BORG_WRAP_TRAITS(typename Traits)

  typedef boost::reference_wrapper<ValueT> wrapper_type;

  reference() : wrapper_type(0) {}
  reference(ValueT &ref) : wrapper_type(ref) {}

  operator ValueT &() const
  {
    return wrapper_type::get();
  }
  
  reference<ValueT, Traits, adapter> &
  operator=(const ValueT &val)
  {
    *wrapper_type::get_pointer() = val;
    return *this;
  }
  
  ValueT *
  operator&() const
  {
    return wrapper_type::get_pointer();
  }
  
};

}// end of namespace borg
//---------------------------------------------------------------------------
#endif // BORG_WRAP_REFERENCE_HPP
