//----------------------------------------------------------------------------
//! \file  indentation_state.hpp  
//! \brief Implements indentation_state.
//! \svn   $Id: wrapper.hpp 42 2007-03-23 01:49:14Z nexbyte $
//----------------------------------------------------------------------------
#ifndef INDENTATION_STATE_HPP
#define INDENTATION_STATE_HPP

#include <boost/operators.hpp>
#include <stack>

namespace io { namespace filter { namespace detail {

using std::stack;
using std::string;
using std::exception;
//using namespace boost::iostreams;

//----------------------------------------------------------------------------
class indentation_underflow : public exception
{
public:
  explicit indentation_underflow() : m_what("indentation underflow") {}
  virtual ~indentation_underflow() throw() {}
  const char *what() const throw() { return m_what.c_str(); }

private:
  string m_what;
};

//----------------------------------------------------------------------------
class indentation_state /*:
  boost::additive< indentation_state >,
  boost::incrementable< indentation_state >,
  boost::decrementable< indentation_state >,
  boost::equality_comparable< indentation_state >,
  boost::less_than_comparable< indentation_state >*/
{
public:
  explicit
  indentation_state() {}

  explicit
  indentation_state(int indentation)
  {
    if(indentation > 0)
      m_indentation.push(indentation);
  }
  
  //! Returns current indentation state (number of chars).
  int
  get() const
  {
    if(m_indentation.empty())
      return 0;
    
    return m_indentation.top();
  }
  
  //! Adds a new level of indentation.
  indentation_state &
  push(int n = 1)
  {
    m_indentation.push(get() + n);
    return *this;
  }
  
  //! Rolls back one level of indentation.
  indentation_state &
  pop()
  {
    if(m_indentation.empty())
      throw indentation_underflow();
    
    m_indentation.pop();
    return *this;
  }

  //! Indentation level.
  int
  depth() const
  {
    return m_indentation.size();
  }
  
  indentation_state &
  set(int n)
  {
    if(n > get())
      return push(n - get());
    
    if(n < get())
    {
      int o;
      while((o = get()) > n && o > 0)
      {
        pop();
      }
      if(o != n)
        m_indentation.push(n);
    }
    
    return *this;
  }
  
/*  indentation_state &
  operator+=(int n) 
  { 
    return push(n); 
  }

  indentation_state &
  operator++()
  { 
    return push(1); 
  }

  indentation_state &
  operator-=(int n) 
  {
    return set(get() - n);
  }

  indentation_state &
  operator--()
  {
    (*this) -= 1;
    return *this;
  }
  
  operator
  int() const
  {
    return get();
  }
  
  bool
  operator<(int n) const
  {
    return get() < n;
  }

  bool
  operator==(int n) const
  {
    return get() == n;
  }
  
  indentation_state &
  operator=(int n)
  {
    return set(n);
  }*/
  
private:
  stack<int> m_indentation;
};

//----------------------------------------------------------------------------

}}} // namespace io::filter::detail
//----------------------------------------------------------------------------
#endif //ndef INDENTATION_STATE_HPP
