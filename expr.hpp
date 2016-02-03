#ifndef _cxx_expr_hpp_
#define _cxx_expr_hpp_

#include <ostream>
#include <sstream>

#include <operation.hpp>

template<class exprT>
  struct expr //: public exprT
  {
    expr(const exprT &x) {} //: exprT(x) {}
  };

//! Identity.
class identity
{
public:
  typedef float identity_type;
  
  identity() {}
  identity_type operator()(const identity_type &x) const { return x; }
  
  inline std::string str() const { return "x"; }
  inline identity complement() const { return *this; }
};

template<>
  struct expr<identity> : public identity
  {
    expr() {}
    expr(const identity &x) : identity(x) {}
  };

//! Stream insertion operator for identity.
template<typename _Tchar, class _Ctraits>
  std::basic_ostream<_Tchar, _Ctraits> &
  operator<<(std::basic_ostream<_Tchar, _Ctraits> &os, const expr<identity> &i)
{ return os << 'x'; }

//! Literal.
class literal
{
public:
  typedef float literal_type;
  
  literal(literal_type lit) : m_lit(lit) {}
  literal_type operator()(const literal_type &x) const { return m_lit; }

  inline std::string str() const { std::ostringstream ss; ss << m_lit; return ss.str(); }
  inline literal complement() const { return *this; }
  
private:
  literal_type m_lit;  
};

//! Stream insertion operator for literal.
template<typename _Tchar, class _Ctraits> 
  std::basic_ostream<_Tchar, _Ctraits> &
  operator<<(std::basic_ostream<_Tchar, _Ctraits> &os, const literal &l)
{ 
  return os << l(0); 
}

//! Equation with unknown x, solution y, no parameters.
template<class aT, class bT, typename opT>
  class binary_op
{
  aT m_a;
  bT m_b;

public:
  typedef opT operation_type;
  typedef typename operation_type::result_type result_type;
  typedef typename operation_type::complement_type complement_type;
  
  aT a() const { return m_a; }
  bT b() const { return m_b; }    
  
  binary_op(const aT &a, const bT &b) :
    m_a(a), m_b(b)
  {}
  
  result_type operator()(const result_type &x) const
  { return opT::apply(m_a(x), m_b(x)); }

  binary_op<aT, bT, complement_type> complement() const
  {
    return binary_op<aT, bT, complement_type>(m_a/*.complement()*/, m_b/*.complement()*/);
  }
  
  inline std::string str() const { std::ostringstream ss; ss << (*this); return ss.str(); }
};

template<class aT, class bT, typename opT>
  struct expr<binary_op<aT, bT, opT> > : public binary_op<aT, bT, opT>
  {
    expr(binary_op<aT, bT, opT> op) : binary_op<aT, bT, opT>(op) {}
  };

//! Stream insertion operator for binary operations.
template<class aT, class bT, typename opT, typename _Tchar, class _Ctraits>
  std::basic_ostream<_Tchar, _Ctraits> &
  operator<<(std::basic_ostream<_Tchar, _Ctraits> &os, const binary_op<aT, bT, opT> &op)
{ 
  opT::print(op.a().str(), op.b().str(), os);
  return os;
}

template<>
  struct expr<literal> : public literal
  {
    expr(float f) : literal(f) {}
    expr(const literal &l) : literal(l) {}
  };

template<>
  struct expr<float> : public literal
  {
    expr(const float &f) : literal(f) {}
  };

template<class aT, class bT>
  expr<binary_op<expr<aT>, expr<bT>, operation::divide<float, float> > >
  operator/(const expr<aT> &a, const expr<bT> &b)
{
  typedef binary_op<expr<aT>, expr<bT>,operation::divide<float, float> > exprT;
  return expr<exprT>(exprT(a, b));
}

template<class aT>
  expr<binary_op<expr<aT>, expr<float>, operation::divide<float, float> > >
  operator/(const expr<aT> &a, expr<float> b)
{
  typedef binary_op<expr<aT>, expr<float>,operation::divide<float, float> > exprT;
  return expr<exprT>(exprT(a, b));
}

template<class aT, class bT>
  expr<binary_op<expr<aT>, expr<bT>, operation::multiply<float, float> > >
  operator*(const expr<aT> &a, const expr<bT> &b)
{
  typedef binary_op<expr<aT>, expr<bT>,operation::multiply<float, float> > exprT;
  return expr<exprT>(exprT(a, b));
}

template<class aT>
  expr<binary_op<expr<aT>, expr<float>, operation::multiply<float, float> > >
  operator*(expr<aT> a, expr<float> b)
{
  typedef binary_op<expr<aT>, expr<float>, operation::multiply<float, float> > exprT;
  return expr<exprT>(exprT(a, b));
}

template<class aT, class bT>
  expr<binary_op<expr<aT>, expr<bT>, operation::add<float, float> > >
  operator+(const expr<aT> &a, const expr<bT> &b)
{
  typedef binary_op<expr<aT>, expr<bT>, operation::add<float, float> > exprT;
  return expr<exprT>(exprT(a, b));
}

template<class aT>
  expr<binary_op<expr<aT>, expr<float>, operation::add<float, float> > >
  operator+(expr<aT> a, expr<float> b)
{
  typedef binary_op<expr<aT>, expr<float>, operation::add<float, float> > exprT;
  return expr<exprT>(exprT(a, b));
}

template<class aT, class bT>
  expr<binary_op<expr<aT>, expr<bT>, operation::sub<float, float> > >
  operator-(const expr<aT> &a, const expr<bT> &b)
{
  typedef binary_op<expr<aT>, expr<bT>, operation::sub<float, float> > exprT;
  return expr<exprT>(exprT(a, b));
}

template<class aT>
  expr<binary_op<expr<aT>, expr<float>, operation::sub<float, float> > >
  operator-(expr<aT> a, expr<float> b)
{
  typedef binary_op<expr<aT>, expr<float>, operation::sub<float, float> > exprT;
  return expr<exprT>(exprT(a, b));
}

#endif // _cxx_expr_hpp_

