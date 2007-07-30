#warning "obsolete"
#ifndef DC_HPP
#define DC_HPP

namespace tk {

//! Dummy for paint context (Painting during OnPaint events).
template<class toolkit> 
  class paint_dc;
  
//! Dummy for client context.
template<class toolkit>
  class client_dc;
  
//! Dummy for offscreen context.
template<class toolkit>
  class memory_dc;
  
//! Generic context.
template<class toolkit>
  class dc;
  
} // namespace tk
#endif // DC_HPP
