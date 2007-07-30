#ifndef BORG_LIBXML2_HPP
#define BORG_LIBXML2_HPP

#include <libxml/xmlversion.h>
#include <libxml/xpath.h>
#include <libxml/nanohttp.h>

//----------------------------------------------------------------------------
namespace borg {
namespace libxml2 {
    
  inline static void 
  initialize()
  {
    ::LIBXML_TEST_VERSION
    ::xmlXPathInit();
    ::xmlNanoHTTPInit();
  }
  
  inline static void 
  shutdown()
  {
    ::xmlNanoHTTPCleanup();
  }
  
} // namespace libxml2
} // namespace borg

#include <borg/libxml2/traits.hpp>
#include <borg/libxml2/dom/adapters.hpp>
#include <borg/libxml2/xpath/adapters.hpp>
#include <borg/libxml2/xpath/expression.hpp>
#include <borg/libxml2/xpath/nodeset.hpp>
#include <borg/libxml2/nanohttp.hpp>
#include <borg/libxml2/list.hpp>
#include <borg/libxml2/lib/output_buffer.hpp>


#endif //ndef BORG_LIBXML2_HPP
