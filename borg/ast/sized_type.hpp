#ifndef BORG_AST_SIZED_TYPE_HPP
#define BORG_AST_SIZED_TYPE_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <boost/mpl/void.hpp>
#include <borg/ast/basic_type.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
#define BORG_AST_SIZED_TYPE_TYPES(Traits) \
  BORG_AST_NODE_TYPES(Traits); \
  BORG_PP_USE_TYPE(Traits, size_type); \
  BORG_PP_USE_TYPE(Traits, sized_type_type);
  
//---------------------------------------------------------------------------
WRAP_PATTERN_FORWARD(sized_type)

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct sized_type_interface
//    : public node_interface<Traits, Derived>
{
  BORG_AST_SIZED_TYPE_TYPES(typename Traits)
 
  typedef sized_type_impl<Traits> impl;

  static bool
  is_sized() { return true; }    
  
  size_type
  size() const
  {
    return impl::get_size
      (dereference_cast<Derived const>(this));
  }
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct sized_type_facade
{
  
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class sized_type_t
    : public wrapper<typename Traits::sized_type_type>
    , public sized_type_interface< Traits, sized_type_t<Traits> >
    , public sized_type_facade< Traits, sized_type_t<Traits> >
{
public:
  BORG_AST_SIZED_TYPE_TYPES(typename Traits)
    
  typedef wrapper<typename Traits::sized_type_type> base_type;
    
  sized_type_t(const sized_type_type &fn) 
    : base_type(fn)
  {}
};

//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

template<class CharT, class CharTraits, class AstTraits>
std::basic_ostream<CharT, CharTraits> &
operator<<(std::basic_ostream<CharT, CharTraits> &os,
           const borg::ast::sized_type_t<AstTraits> &sized_type)
{
  os << sized_type.name();
  
  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_SIZED_TYPE_HPP
