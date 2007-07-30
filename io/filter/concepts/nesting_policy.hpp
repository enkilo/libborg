//----------------------------------------------------------------------------
//! \file  nesting_policy.hpp  
//! \brief Implements the nesting_policy concept.
//!
//! \svn $Id: nesting_policy.hpp 37 2007-03-22 02:16:30Z nexbyte $
//----------------------------------------------------------------------------
#ifndef NESTING_POLICY_HPP
#define NESTING_POLICY_HPP

namespace io { namespace filter {

using namespace boost;

//----------------------------------------------------------------------------
template<class TT>
  struct NestingPolicyConcept
{
  void constraints()
  {
    TT &policy = static_object<TT>::get();

    policy.enter();
    policy.leave();
  }
};

}} // namespace io::filter
//----------------------------------------------------------------------------
#endif //ndef NESTING_POLICY_HPP
