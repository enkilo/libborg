//----------------------------------------------------------------------------
//! \file  constructible_from_concept.hpp  
//! \brief Implements wrapper concepts.
//!
//! \svn $Id: constructible_from_concept.hpp 37 2007-03-22 02:16:30Z nexbyte $
//----------------------------------------------------------------------------
#ifndef CONSTRUCTIBLE_FROM_CONCEPT_HPP
#define CONSTRUCTIBLE_FROM_CONCEPT_HPP

#include <boost/type_traits/remove_reference.hpp>
#include <boost/concept_archetype.hpp>

namespace borg {

//----------------------------------------------------------------------------
//! X is constructible from Y.
//----------------------------------------------------------------------------
template<class X, class Y>
  struct ConstructibleFromConcept
{
  typedef typename boost::remove_reference<Y>::type y_type;

  void constraints()
  {      
    y_type &y = boost::static_object<y_type>::get();
    X x(y);
    boost::ignore_unused_variable_warning(x);
  }
};

} // end of namespace borg
//----------------------------------------------------------------------------
#endif //ndef CONSTRUCTIBLE_FROM_CONCEPT_HPP
