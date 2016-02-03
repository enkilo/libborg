#ifndef BORG_TK_APPLICATION_HPP
#define BORG_TK_APPLICATION_HPP

#include <borg/preproc.hpp>
#include <borg/util/dereference_cast.hpp>

namespace borg {
namespace tk {

//---------------------------------------------------------------------------
#define BORG_TK_APPLICATION_TYPES(Traits) \
  BORG_PP_USE_TYPE(Traits, application_type)

//---------------------------------------------------------------------------
template<class Traits>
struct application_impl;
    
//---------------------------------------------------------------------------
template<class Derived, class Traits>
struct application_interface
{  
  
  
};
  
//---------------------------------------------------------------------------
template<class Derived, class Traits>
struct application_facade
{
  
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class application
    : Traits::application_type
    , public application_interface< application<Traits>, Traits >
    , public application_facade< application<Traits>, Traits >
{
public:
  BORG_PP_USE_TYPE(typename Traits, application_type)
  
  application() {}
};
  
//---------------------------------------------------------------------------

} // namespace tk
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_TK_APPLICATION_HPP
