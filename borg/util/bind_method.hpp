#ifndef BIND_METHOD_HPP
#define BIND_METHOD_HPP

#include <borg/util/method_traits.hpp>

#warning "TODO: use boost::preprocessor here"

namespace borg {

//---------------------------------------------------------------------------
template<typename fnT, int arity = method_traits<fnT>::arity>
  class bound_method
{
public:
  typedef method_traits<fnT> traits;
  typedef typename traits::this_type this_type;
  typedef typename traits::result_type result_type;
  
  bound_method(fnT m, this_type &t) : m_fn(m), m_this(t) {}
  bound_method(fnT m, this_type *t) : m_fn(m), m_this(*t) {}
  
  result_type operator()() 
  {
    return (m_this.*m_fn)();
  }

private:
  fnT m_fn;
  this_type &m_this;
};

template<typename fnT>
  class bound_method<fnT, 1>
{
public:
  typedef method_traits<fnT> traits;
  typedef typename traits::this_type this_type;
  typedef typename traits::result_type result_type;
  typedef typename traits::arg1_type arg1_type;
  
  bound_method(fnT m, this_type &t) : m_fn(m), m_this(t) {}
  bound_method(fnT m, this_type *t) : m_fn(m), m_this(*t) {}
  
  result_type operator()(arg1_type a1)
  {
    return (m_this.*m_fn)(a1);
  }

private:
  fnT m_fn;
  this_type &m_this;
};

template<typename fnT>
  class bound_method<fnT, 2>
{
public:
  typedef method_traits<fnT> traits;
  typedef typename traits::this_type this_type;
  typedef typename traits::result_type result_type;
  typedef typename traits::arg1_type arg1_type;
  typedef typename traits::arg2_type arg2_type;
  
  bound_method(fnT m, this_type &t) : m_fn(m), m_this(t) {}
  bound_method(fnT m, this_type *t) : m_fn(m), m_this(*t) {}
  
  result_type operator()(arg1_type a1, arg2_type a2)
  {
    return (m_this.*m_fn)(a1, a2);
  }

private:
  fnT m_fn;
  this_type &m_this;
};

template<typename fnT>
  class bound_method<fnT, 3>
{
public:
  typedef method_traits<fnT> traits;
  typedef typename traits::this_type this_type;
  typedef typename traits::result_type result_type;
  typedef typename traits::arg1_type arg1_type;
  typedef typename traits::arg2_type arg2_type;
  typedef typename traits::arg3_type arg3_type;
  
  bound_method(fnT m, this_type &t) : m_fn(m), m_this(t) {}
  bound_method(fnT m, this_type *t) : m_fn(m), m_this(*t) {}
  
  result_type operator()(arg1_type a1, arg2_type a2, arg3_type a3)
  {
    return (m_this.*m_fn)(a1, a2, a3);
  }

private:
  fnT m_fn;
  this_type &m_this;
};

template<typename fnT>
  bound_method<fnT> bind_method(fnT f, typename method_traits<fnT>::this_type *const t)
{
  return bound_method<fnT>(f, t);
}

template<typename fnT>
  bound_method<fnT> bind_method(fnT f, typename method_traits<fnT>::this_type &t)
{
  return bound_method<fnT>(f, &t);
}

} // namespace borg
//---------------------------------------------------------------------------
#endif //ndef BIND_METHOD_HPP
