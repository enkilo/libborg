#ifndef BORG_APR_RING_HPP
#define BORG_APR_RING_HPP

#include <apr/apr_ring.h>
#include <borg/apr/types.hpp>

namespace apr {

//---------------------------------------------------------------------------

//! a ring is a kind of doubly-linked list that can be manipulated
//! without knowing where its head is.


template<ElemT>
struct ring_entry
{
  ElemT next;
  ElemT prev;
};

template<ElemT>
struct ring_head : public ring_entry<ElemT>
{
  typedef ring_entry<ElemT> base_type;
  
  /// first element of the ring, constant
  const ElemT &
  first() const { return APR_RING_FIRST(this); }
  
  /// first element of the ring, mutable
  ElemT &
  first() { return APR_RING_FIRST(this); }
    
  /// last element of the ring, constant
  const ElemT &
  last() const { return APR_RING_LAST(this); }
  
  /// last element of the ring, mutable
  ElemT &
  last() { return APR_RING_LAST(this); }    
};

}// namespace apr
//---------------------------------------------------------------------------
#endif //ndef BORG_APR_RING_HPP
