#ifndef BORG_AST_ARRAY_TYPE_HPP
#define BORG_AST_ARRAY_TYPE_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/ast/typed.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
#define BORG_AST_ARRAY_TYPE_TYPES(Traits) \
  BORG_AST_NODE_TYPES(Traits) \
  BORG_PP_USE_TYPE(Traits, size_type) \
  BORG_PP_USE_TYPE(Traits, array_type_type)
  
//---------------------------------------------------------------------------
BORG_AST_FORWARD(array_type)

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct array_type_interface 
    : public typed_interface<Traits, Derived>
{  
  BORG_AST_ARRAY_TYPE_TYPES(typename Traits)
 
  typedef array_type_impl<Traits> impl;
  
  static bool
  is_array()
  {
    return true;
  }
  
  size_type
  extent() const
  {
    return impl::get_extent(dereference_cast<Derived const>(this));
  }
  
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct array_type_facade
{
  
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class array_type_t
    : public wrapper<typename Traits::array_type_type>
    , public array_type_interface< Traits, array_type_t<Traits> >
    , public array_type_facade< Traits, array_type_t<Traits> >
{
public:
  BORG_AST_ARRAY_TYPE_TYPES(typename Traits)
    
  typedef wrapper<typename Traits::array_type_type> base_type;
    
  array_type_t(const array_type_type &fn) 
    : base_type(fn)
  {}
};
  
//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

template<class CharT, class CharTraits, class AstTraits>
std::basic_ostream<CharT, CharTraits> &
operator<<(std::basic_ostream<CharT, CharTraits> &os,
           const borg::ast::array_type_t<AstTraits> &array_type)
{
  os << array_type.type();
  os << '[' << array_type.extent() << ']';

  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_ARRAY_TYPE_HPP
