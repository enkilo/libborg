#ifndef DRAWTEST_HPP
#define DRAWTEST_HPP

#include <borg/tk/dc.hpp>

template<class dc>
inline void drawtest(dc &drawable)
{
//  std::cout << "clip: " << drawable.getClip() << std::endl;
  
 // drawable.setAntiAliased(false);
  
  drawable.set_draw_style(types::draw_stroked);
  drawable.set_stroke_color(borg::rgba<typename dc::color_type>(255, 0, 0));
  drawable.draw_rect(borg::rect<typename dc::vector_type>(0, 0, 100, 100));
  
  drawable.move_to(50, 50);
  drawable.line_to(150, 75);
  
/*  drawable.set_fill_color(borg::rgba<typename dc::color_type>(255, 255, 255));
  
  drawable.set_fill_color(borg::rgba<typename dc::color_type>(255, 0, 0));
  drawable.move_to(std::point<typename dc::vector_type>(0, 0));
  drawable.line_to(std::point<typename dc::vector_type>(200, 200));
  
  drawable.set_fill_color(borg::rgba<typename dc::color_type>(255, 160, 0));
  drawable.move_to(std::point<typename dc::vector_type>(100, 100));
  drawable.line_to(std::point<typename dc::vector_type>(0, 200));
  
  drawable.set_fill_color(borg::rgba<typename dc::color_type>(0,160,255));
  drawable.move_to(std::point<typename dc::vector_type>(50, 100));
  drawable.line_to(std::point<typename dc::vector_type>(150, 0));

  drawable.set_fill_color(borg::rgba<typename dc::color_type>(64,255,0));
  drawable.draw_rect(borg::rect<typename dc::vector_type>(50, 50, 100, 100));
  
  drawable.set_fill_color(borg::rgba<typename dc::color_type>(255, 0, 128));
  drawable.draw_ellipse(borg::rect<typename dc::vector_type>(50, 125, 150, 200));

  drawable.set_text_color(borg::rgba<typename dc::color_type>(0, 0, 0));
  drawable.set_fill_color(borg::rgba<typename dc::color_type>(0, 0, 255));
  drawable.set_font(abstract::font_very_big);
  drawable.draw_text("test!", borg::rect<typename dc::vector_type>(40, 80, 100, 20));
  
  drawable.set_fill_color(borg::rgba<typename dc::color_type>(64,0,255));
  
#define deg(a) ((a) * M_PI / 180)
  
  drawable.draw_arc(borg::rect<typename dc::vector_type>(25, 100, 100, 80), deg(45), deg(135));*/
}

#endif //ndef DRAWTEST_HPP
