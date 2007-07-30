#ifndef SKIP_ALGORITHMS_HPP
#define SKIP_ALGORITHMS_HPP

namespace borg {

//----------------------------------------------------------------------------
template<typename IteratorT>
IteratorT
skip_n(const IteratorT &it, size_t n)
{
  typedef IteratorT iterator_type;
  iterator_type ret = it;
  while(n)
  {
    ++ret;
    --n;
  }
  return ret;
}

}// namespace borg
//---------------------------------------------------------------------------
#endif //ndef SKIP_ALGORITHMS_HPP
