#ifndef BORG_XML_XPATH_EVALUATOR_HPP
#define BORG_XML_XPATH_EVALUATOR_HPP

#include <borg/string.hpp>
#include <borg/xml/dom/node.hpp>
#include <borg/xml/xpath/types.hpp>
#include <borg/xml/xpath/result.hpp>
#include <borg/util/dereference_cast.hpp>

namespace borg {
namespace xml {
namespace xpath {
  
using borg::dereference_cast;
using dom::node_t;
using dom::document_t;
//using xpath::expression_t;
  
//---------------------------------------------------------------------------
/*template<class Traits>
struct evaluator_impl
{
  XML_XPATH_TYPES(typename Traits)
  
  //! Create a precompiled XPath expression.
  template<class StringT, class NSResolverT>
  static expression_type
  compile(evaluator_type const eval, const StringT &s, const NSResolverT &r)
  {
    return eval->createExpression(s, r);
  }
  
  //! Create a namespace resolver for the namespace of the given node.
  template<class NodeT>
  static ns_resolver_type
  create_ns_resolver(evaluator_type const eval, const NodeT &n)
  {
    return eval->createNSResolver(n);
  }
  
};*/

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct evaluator_interface
{
  XML_XPATH_TYPES(typename Traits)

  typedef evaluator_impl<Traits> impl;

  expression_t<Traits>
  compile(const string<wchar_type, Traits> &expr, const ns_resolver_t<Traits> &r) const
  {
    return impl::compile
      ((evaluator_type)dereference_cast<Derived const>(this), expr, r);
  }

  expression_t<Traits>
  compile(const string<wchar_type, Traits> &expr) const
  {
    return impl::compile
      (dereference_cast<Derived const>(this), expr);
  }

  ns_resolver_t<Traits>
  create_ns_resolver(const node_t<Traits> &n) const
  {
    return impl::create_ns_resolver
      ((evaluator_type)dereference_cast<Derived const>(this), n);
  }
  
  result_t<Traits>
  eval(const expression_t<Traits> &expr) const
  {
    return impl::eval
      ((evaluator_type)dereference_cast<Derived const>(this), expr);
  }
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct evaluator_facade
{
  template<class Expr>
  result_t<Traits>
  operator()(const Expr &expr)
  {
    return dereference_cast<Derived>(this).eval(expr);
  }
  
};

//---------------------------------------------------------------------------
template<class Traits>
class evaluator
    : public evaluator_t<Traits>
{
  typedef evaluator_impl<Traits> impl;
  typedef evaluator_t<Traits> base_type;

public:
  evaluator(const document_t<Traits> &doc)
      : base_type(impl::create(doc))
      , m_delete(true)
  {}

  ~evaluator()
  {
    if(m_delete)
      impl::destroy(unwrap_cast(*this));
  }

private:
  bool m_delete;
};

//---------------------------------------------------------------------------

} // namespace xpath
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_XPATH_EVALUATOR_HPP
