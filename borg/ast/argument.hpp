#ifndef BORG_AST_NODE_ARGUMENT_HPP
#define BORG_AST_NODE_ARGUMENT_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <boost/mpl/void.hpp>
#include <borg/ast/named.hpp>
#include <borg/ast/typed.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
#define BORG_AST_ARGUMENT_TYPES(Traits) \
  BORG_AST_NODE_TYPES(Traits); \
  BORG_PP_USE_TYPE(Traits, argument_type);

//---------------------------------------------------------------------------
WRAP_PATTERN_FORWARD(argument)

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct argument_interface
    : public typed_interface<Traits, Derived>
{
  BORG_AST_ARGUMENT_TYPES(typename Traits)
 
  typedef argument_impl<Traits> impl;
    
  string_type
  name() const
  {
    return impl::get_name
      (dereference_cast<Derived const>(this));
  }
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct argument_facade
{
  
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class argument_t
    : public wrapper<typename Traits::argument_type>
    , public argument_interface< Traits, argument_t<Traits> >
    , public argument_facade< Traits, argument_t<Traits> >
{
public:
  BORG_AST_ARGUMENT_TYPES(typename Traits)
    
  typedef wrapper<typename Traits::argument_type> base_type;
    
  argument_t(const argument_type &fn) 
    : base_type(fn)
  {}
};

//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

template<class CharT, class CharTraits, class AstTraits>
std::basic_ostream<CharT, CharTraits> &
operator<<(std::basic_ostream<CharT, CharTraits> &os,
           const borg::ast::argument_t<AstTraits> &arg)
{
  if(arg.name())
    os << ' ' << arg.name();
  
  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_NODE_ARGUMENT_HPP
