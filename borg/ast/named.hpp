#ifndef BORG_AST_NAMED_HPP
#define BORG_AST_NAMED_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <boost/mpl/void.hpp>
#include <borg/ast/node.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
#define BORG_AST_NAMED_TYPES(Traits) \
  BORG_AST_NODE_TYPES(Traits); \
  BORG_PP_USE_TYPE(Traits, named_type);
  
//---------------------------------------------------------------------------
WRAP_PATTERN_FORWARD(named)

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct named_interface
//    : public node_interface<Traits, Derived>
{
  BORG_AST_NAMED_TYPES(typename Traits)
 
  typedef named_impl<Traits> impl;

  string_type
  name() const
  {
    return impl::get_name
      (dereference_cast<Derived const>(this));
  }
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct named_facade
{
  
  static bool
  is_named() { return true; }    
  
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class named_t
    : public wrapper<typename Traits::named_type>
    , public named_interface< Traits, named_t<Traits> >
    , public named_facade< Traits, named_t<Traits> >
{
public:
  BORG_AST_NAMED_TYPES(typename Traits)
    
  typedef wrapper<typename Traits::named_type> base_type;
    
  named_t(const named_type &fn) 
    : base_type(fn)
  {}
};

//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

template<class CharT, class CharTraits, class AstTraits>
std::basic_ostream<CharT, CharTraits> &
operator<<(std::basic_ostream<CharT, CharTraits> &os,
           const borg::ast::named_t<AstTraits> &named)
{
  if(named.name() && named.name() != "")
    os << named.name();
  else
    os << "<anonymous>";
  
  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_NAMED_HPP
