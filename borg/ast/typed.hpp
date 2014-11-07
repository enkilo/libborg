#ifndef BORG_AST_TYPED_NODE_HPP
#define BORG_AST_TYPED_NODE_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <boost/mpl/void.hpp>
#include <borg/ast/basic_type.hpp>
#include <borg/ast/node_cast.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
#define BORG_AST_TYPED_TYPES(Traits) \
  BORG_AST_BASIC_TYPE_TYPES(Traits); \
  BORG_PP_USE_TYPE(Traits, typed_type);
  
//---------------------------------------------------------------------------
WRAP_PATTERN_FORWARD(named)
WRAP_PATTERN_FORWARD(typed)

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct typed_interface
    : public node_interface<Traits, Derived>
{
  BORG_AST_TYPED_TYPES(typename Traits)
 
  typedef typed_impl<Traits> impl;
    
  basic_type_t<Traits>
  type() const
  {
    return impl::get_type
      (dereference_cast<Derived const>(this));
  }
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct typed_facade
{
  
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class typed_t
    : public wrapper<typename Traits::typed_type>
    , public typed_interface< Traits, typed_t<Traits> >
    , public typed_facade< Traits, typed_t<Traits> >
{
public:
  BORG_AST_TYPED_TYPES(typename Traits)
    
  typedef wrapper<typename Traits::typed_type> base_type;
    
  typed_t(const typed_type &fn) 
    : base_type(fn)
  {}
};

//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

template<class CharT, class CharTraits, class AstTraits>
std::basic_ostream<CharT, CharTraits> &
operator<<(std::basic_ostream<CharT, CharTraits> &os,
           const borg::ast::typed_t<AstTraits> &typed)
{
  using namespace borg::ast;
  
  os << typed.type();

  if(typed.is_named())
    os << ' ' << node_cast<named_t>(typed);
  
  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_TYPED_NODE_HPP
