#warning "obsolete"
#ifndef _CXX_SignalDrawer_
#define _CXX_SignalDrawer_

#include <borg/Drawer.hpp>
#include <borg/Buffer.hpp>

class SignalDrawer : virtual public Drawer
{
protected:
  Buffer<float> *sigbuf;
  size_t nsamples;

public:
  virtual ~SignalDrawer() {}
  virtual void setSignalBuffer(Buffer<float> *sb) { sigbuf = sb; }
  virtual void setNumSamples(size_t n) { nsamples = n; }
  virtual void operator()(Drawable &dst, const Rect &area) = 0;
};

#endif /* _CXX_Drawer_ */
