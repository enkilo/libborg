//----------------------------------------------------------------------------
//! \file  returnable_as_concept.hpp
//! \brief Implements the ReturnableAsConcept check.
//!
//! \svn $Id: wrap_concepts.hpp 37 2007-03-22 02:16:30Z nexbyte $
//----------------------------------------------------------------------------
#ifndef RETURNABLE_AS_CONCEPT_HPP
#define RETURNABLE_AS_CONCEPT_HPP

#include <boost/type_traits/remove_reference.hpp>

namespace borg {

//----------------------------------------------------------------------------
//! X is returnable as Y.
//----------------------------------------------------------------------------
template<class X, class Y>
  struct ReturnableAsConcept
{
  typedef typename boost::remove_reference<X>::type x_type;

  Y return_constraints(x_type &x) { return x; }

  void constraints()
  {
    x_type &x = boost::static_object<x_type>::get();
    return_constraints(x);
  }
};

} // namespace borg
//----------------------------------------------------------------------------
#endif //ndef RETURNABLE_AS_CONCEPT_HPP
