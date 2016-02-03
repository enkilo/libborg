#ifndef BORG_AST_SCOPED_HPP
#define BORG_AST_SCOPED_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <boost/mpl/void.hpp>
#include <borg/ast/node.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
#define BORG_AST_SCOPED_TYPES(Traits) \
  BORG_AST_NODE_TYPES(Traits); \
  BORG_PP_USE_TYPE(Traits, scoped_type)
  
//---------------------------------------------------------------------------
WRAP_PATTERN_FORWARD(scoped)

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct scoped_interface
    : public node_interface<Traits, Derived>
{
  BORG_AST_SCOPED_TYPES(typename Traits)
 
  typedef scoped_impl<Traits> impl;
    
  node_type
  context() const
  {
    return impl::get_context
      (dereference_cast<Derived const>(this));
  }
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct scoped_facade
{
  
  static bool
  is_scoped() { return true; }
  
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class scoped_t
    : public wrapper<typename Traits::scoped_type>
    , public scoped_interface< Traits, scoped_t<Traits> >
    , public scoped_facade< Traits, scoped_t<Traits> >
{
public:
  BORG_AST_SCOPED_TYPES(typename Traits)
    
  typedef wrapper<typename Traits::scoped_type> base_type;
    
  scoped_t(const scoped_type &fn) 
    : base_type(fn)
  {}
};

//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_SCOPED_HPP
