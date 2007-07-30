#ifndef BORG_GCCXML_VARIABLE_HPP
#define BORG_GCCXML_VARIABLE_HPP

#include <borg/gccxml/declaration.hpp>
#include <borg/ast/variable.hpp>

namespace borg {
namespace ast  {

template<class XmlTraits>
struct variable_impl< gccxml::traits<XmlTraits> >
{
  typedef gccxml::traits<XmlTraits> traits;
  
  BORG_AST_DECLARATION_TYPES(typename traits)
    
};

//----------------------------------------------------------------------------
}// namespace ast
}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_VARIABLE_HPP
