#warning "obsolete"
#ifndef _cxx_scope_view_
#define _cxx_scope_view_

#include <interface/widget.hpp>
#include <interface/buffer.hpp>

template<typename viewT>
class scope_view : public viewT
{
protected:
  buffer<float> &sigbuf;
  size_t nsamples;

public:
  scope_view(buffer<float> &sb, size_t n) : 
    sigbuf(sb),
    nsamples(n)
  {}
  
  virtual ~scope_view() {}
};

#endif /* _cxx_scope_view_ */
