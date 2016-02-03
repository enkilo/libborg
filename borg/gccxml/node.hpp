#ifndef BORG_GCCXML_NODE_HPP
#define BORG_GCCXML_NODE_HPP

#include <borg/gccxml/traits.hpp>
#include <borg/ast/node.hpp>
#include <borg/util/exception.hpp>
//#include <borg/gccxml/libxml2.hpp>

namespace borg {
namespace ast  {

template<class XmlTraits>
struct node_impl< gccxml::traits<XmlTraits> >
{
  typedef gccxml::traits<XmlTraits> traits;
  
  BORG_AST_NODE_TYPES(typename traits)
  BORG_PP_USE_TYPE(typename traits, sequence_type)

  typedef typename traits::id_type id_type;
    
  //----------------------------------------------------------------------------
  static id_type
  get_id(const node_type &node)
  {
    using namespace gccxml;

    id_type ret;
    
    if(node == 0)
      throw exception<traits>("null node!");
    
    if(node.name() == "Function")
      ret = function_node;
    else if(node.name() == "Typedef")
      ret = typedef_node;
    else if(node.name() == "Namespace")
      ret = namespace_node;
    else if(node.name() == "Argument")
      ret = argument_node;
    else if(node.name() == "Variable")
      ret = variable_node;
    else if(node.name() == "Enumeration")
      ret = enumeration_node;
    else if(node.name() == "EnumValue")
      ret = enum_value_node;
    else if(node.name() == "PointerType")
      ret = pointer_type_node;
    else if(node.name() == "FundamentalType")
      ret = fundamental_type_node;
    else if(node.name() == "ReferenceType")
      ret = reference_type_node;
    else if(node.name() == "Union")
      ret = union_node;
    else if(node.name() == "Struct")
      ret = struct_node;
    else if(node.name() == "Class")
      ret = class_node;
    else if(node.name() == "ArrayType")
      ret = array_type_node;
    else if(node.name() == "Field")
      ret = field_node;
    else if(node.name() == "Constructor")
      ret = constructor_node;
    else if(node.name() == "CvQualifiedType")
      ret = cv_qualified_type_node;
    else if(node.name() == "FunctionType")
      ret = function_type_node;
    else if(node.name() == "File")
      ret = file_node;
    else if(node.name() == "OperatorFunction")
      ret = operator_function_node;
    else if(node.name() == "Destructor")
      ret = destructor_node;
    else if(node.name() == "Method")
      ret = method_node;
    else if(node.name() == "OperatorMethod")
      ret = operator_method_node;
    else if(node.name() == "Converter")
      ret = converter_node;
    else if(node.name() == "MethodType")
      ret = method_type_node;
    else if(node.name() == "OffsetType")
      ret = offset_type_node;
    else if(node.name() == "Unimplemented")
      ret = unimplemented_node;
    else
      throw exception< traits >
        ((std::string)"gccxml::node::id(): unknown element: " 
         + (const char *)(const unsigned char *)node.name());
    
    return ret;
  }

  //----------------------------------------------------------------------------
  static const char *
  nodename(const node_type &node)
  {
    return (const char *)(const unsigned char *)node.name();
  }

  //----------------------------------------------------------------------------
  static bool
  is_named(const node_type &node)
  {
    return !!node.get_attribute_node("name");
  }

  //----------------------------------------------------------------------------
  static bool
  is_typed(const node_type &node)
  {
    // Unclear yet whether it is a function or not.    
    return node.get_attribute_node("type") /*||
           node.get_attribute_node("returns")*/;
  }

  //----------------------------------------------------------------------------
  static bool
  is_scoped(const node_type &node)
  {
    return node.get_attribute_node("context");
  }

  //----------------------------------------------------------------------------
  static bool
  is_compound(const node_type &node)
  {
    return !!node.get_attribute_node("members") || (node.name() == "Enumeration");
  }

  //----------------------------------------------------------------------------
  static sequence_type
  get_arguments(const node_type &node)
  {
    return node.child_nodes();
  }
  
    
};

//----------------------------------------------------------------------------
}// namespace ast
}// namespace borg

#include <borg/ast/argument.hpp>
#include <borg/ast/namespace.hpp>
#include <borg/ast/variable.hpp>
#include <borg/ast/operator_function.hpp>
#include <borg/ast/typedef.hpp>
#include <borg/ast/compound.hpp>
#include <borg/ast/file.hpp>
#include <borg/ast/array_type.hpp>

template<class CharT, class CharTraits, class XmlTraits>
std::basic_ostream<CharT, CharTraits> &
operator<<(std::basic_ostream<CharT, CharTraits> &os,
           const borg::ast::node_t< borg::gccxml::traits<XmlTraits> > &node)
{
  using namespace borg::gccxml;
  using namespace borg::ast;
  
  //os << "nodeid: " << node.nodename() << std::endl;
  
//  if(node.id() == constructor_node && node.is_named())
//    os << "id: " << node.id() << std::endl;
  
  switch(node.id())
  {
    case argument_node:
      os << node_cast<argument_t>(node);
      break;

    case function_node:
    case method_node:
      os << node_cast<function_t>(node);
      break;

    case constructor_node:
    case destructor_node:
      os << node_cast<basic_function_t>(node);
      break;

    case namespace_node:
      os << node_cast<namespace_t>(node);
      break;
    
    case operator_function_node:
    case operator_method_node:
    case converter_node:
      os << node_cast<operator_function_t>(node);
      break;

    case field_node:
    case variable_node:
      os << node_cast<variable_t>(node);
      break;
    
    case fundamental_type_node:
    case pointer_type_node:
    case reference_type_node:
    case cv_qualified_type_node:
    case method_type_node:
    case function_type_node:
    case offset_type_node:
      os << node_cast<basic_type_t>(node);
      break;

    case array_type_node:
      os << node_cast<array_type_t>(node);
      break;
    
    case typedef_node:
      os << node_cast<typedef_t>(node);
      break;
    
    case struct_node:
    case class_node:
    case union_node:
    case enumeration_node:
      os << node_cast<compound_t>(node);
      break;
    
    case file_node:
      os << node_cast<file_t>(node);
      break;
    
    case unimplemented_node:
      break;
    
    default:
      throw borg::exception< traits<XmlTraits> >
        ("Node type " + borg::ast::name(node) + " not handled");
  }
  
  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_NODE_HPP
