#ifndef BORG_ZEND_VALUE_HPP
#define BORG_ZEND_VALUE_HPP

#include <php5/TSRM/TSRM.h>
#include <php5/Zend/zend.h>

#include "borg/zend/traits.hpp"
#include "borg/script/value.hpp"

namespace borg {
namespace script {

//----------------------------------------------------------------------------
template<>
struct value_impl<zend::traits>
{
  BORG_SCRIPT_VALUE_TYPES(zend::traits)

  static void
  print_r(value_type const *val, int indent = 2)
  {
    ::zend_print_zval_r((zval *)val, indent TSRMLS_CC);
  }

};

//---------------------------------------------------------------------------

}// namespace script
}// namespace borg

#endif //ndef BORG_ZEND_TRAITS_HPP
