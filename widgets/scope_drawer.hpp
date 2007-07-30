#ifndef SCOPE_DRAWER_HPP
#define SCOPE_DRAWER_HPP

#include <interface/drawer.hpp>
#include <interface/buffer.hpp>
#include <borg/tk/dc.hpp>

namespace borg { 
namespace tk { 

  
template<class toolkit>
class scope_drawer
{
public:
  BORG_TK_DC_TYPES(typename toolkit)
  //DC_TRAITS(typename dc::dc_traits)

protected:
  buffer<float> &sigbuf;
  index_type nsamples;

public:
  scope_drawer(buffer<float> &sb, index_type n) :
    sigbuf(sb),
    nsamples(n)
  {}
  
  void operator()(dc_type &dst, const rect_type &area)
  {
    int yrange = area.getHeight() - 1;
    int xrange = area.getWidth();
    int index = nsamples - 1;
    float scale = .5f * (float)yrange;
    int px, py;
    int min, max;
    dc_wrapper<toolkit> dc(&dst);
    
    px = area.x - 1;
    py = min = max = (int)((1 - sigbuf[index]) * scale);
    
    dc.move_to(px, py);
    
    for(index_type i = 0; i < nsamples; i++)
    {
      int x = area.x + i * xrange / nsamples;
      int y = area.y + (int)((1 - sigbuf[index--]) * scale);

      if(x != px)
      {
        dc.line_to(px, py);
        
        if(min != max)
          dc.draw_line(point_type(px, min), point_type(px, max));

        if(y != py)
          dc.line_to(x, y);
        else
          dc.move_to(x, y);

        dc.draw_point(x, y);
      
        min = max = y;
      }
      else
      {
        if(y > max) max = y;
        if(y < min) min = y;
      }

      px = x;
      py = y;
    }
  }
};
  
} // namespace tk
} // namespace borg

#endif /* SCOPE_DRAWER_HPP */
