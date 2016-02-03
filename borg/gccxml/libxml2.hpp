#ifndef BORG_GCCXML_LIBXML2_HPP
#define BORG_GCCXML_LIBXML2_HPP

#include <borg/gccxml/traits.hpp>
#include <borg/libxml2.hpp>
#include <borg/xml/dom/idreflist.hpp>

namespace borg {
namespace gccxml  {

//----------------------------------------------------------------------------
typedef traits<libxml2::traits> libxml2_traits;

//----------------------------------------------------------------------------
typedef ast::declaration_t<libxml2_traits> declaration_t;
typedef ast::function_t<libxml2_traits>    function_t;
typedef ast::node_t<libxml2_traits>        node_t;
typedef ast::scoped_t<libxml2_traits>      scoped_t;
typedef ast::named_t<libxml2_traits>       named_t;
typedef ast::namespace_t<libxml2_traits>   namespace_t;
typedef ast::tree_t<libxml2_traits>        tree_t;
//typedef ast::sequence_t<libxml2_traits>    sequence_t;
  
//----------------------------------------------------------------------------

}// namespace gccxml
}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_LIBXML2_HPP
