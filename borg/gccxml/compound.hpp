#ifndef BORG_GCCXML_COMPOUND_HPP
#define BORG_GCCXML_COMPOUND_HPP

#include <boost/lexical_cast.hpp>
#include <borg/gccxml/traits.hpp>
#include <borg/gccxml/libxml2.hpp>
#include <borg/ast/compound.hpp>
#include <borg/util/exception.hpp>

namespace borg {
namespace ast  {

template<class XmlTraits>
struct compound_impl< gccxml::traits<XmlTraits> >
{
  typedef gccxml::traits<XmlTraits> traits;
  
  BORG_AST_COMPOUND_TYPES( typename traits )

  static members_type
  get_children(const compound_type &compound)
  {
    xml::dom::attribute_t<XmlTraits> members = 
      compound.get_attribute_node("members");
    
    if(members == 0)
      return members_type("", compound.owner_document());
//      throw exception<traits>("No 'members' attribute!");
    
    return members;
  }

  static bool
  is_struct(const compound_type &compound)
  {
    return compound.name() == "Struct";      
  }

  static bool
  is_class(const compound_type &compound)
  {
    return compound.name() == "Class";
  }

  static bool
  is_union(const compound_type &compound)
  {
    return compound.name() == "Union";
  }

  static bool
  is_enum(const compound_type &compound)
  {
    return compound.name() == "Enumeration";
  }
  
    
};

//----------------------------------------------------------------------------
}// namespace ast
namespace gccxml {
  
typedef ast::compound_t<libxml2_traits> compound_t;
  
} // namespace gccxml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_COMPOUND_HPP
