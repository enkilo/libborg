#ifndef RANGE_TRUNC_HPP
#define RANGE_TRUNC_HPP

namespace borg {

//----------------------------------------------------------------------------
template<typename IndexT, typename SizeT>
IndexT &
range_trunc(IndexT &index, const SizeT &size)
{
  if(index >= size) index = size - 1;
  return index;
}

template<typename IndexT, typename SizeT>
void
range_trunc(IndexT &start, IndexT &length, const SizeT &size)
{
  if(start >= size) start = size - 1;
  if(start + length >= size) length = size - 1 - start;
}

}// namespace borg
//---------------------------------------------------------------------------
#endif //ndef RANGE_TRUNC_HPP
