#ifndef BORG_ZEND_TRAITS_HPP
#define BORG_ZEND_TRAITS_HPP

#include <php5/Zend/zend.h>

namespace borg {
namespace zend {

//----------------------------------------------------------------------------
struct traits
{
  typedef ::zval value_type;
};

//---------------------------------------------------------------------------
  
}// namespace zend
}// namespace borg

# ifdef ZTS
#  include <pthread.h>
extern "C" void ***tsrm_ls;
# endif  
#endif //ndef BORG_ZEND_TRAITS_HPP
