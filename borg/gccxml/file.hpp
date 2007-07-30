#ifndef BORG_GCCXML_FILE_HPP
#define BORG_GCCXML_FILE_HPP

#include <borg/gccxml/traits.hpp>
#include <borg/ast/file.hpp>

namespace borg {
namespace ast  {

template<class XmlTraits>
struct file_impl< gccxml::traits<XmlTraits> >
{
  BORG_AST_FILE_TYPES( typename gccxml::traits<XmlTraits> )
};

//----------------------------------------------------------------------------
} // namespace ast
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_FILE_HPP
