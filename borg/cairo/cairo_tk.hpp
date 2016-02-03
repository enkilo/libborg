#ifndef CAIRO_TK_HPP
#define CAIRO_TK_HPP

#include <cairo/cairo.h>


#if defined(CAIRO_HAS_WIN32_SURFACE) || defined(WIN32)
#include <cairo/cairo-win32.h>
#endif // CAIRO_HAS_WIN32_SURFACE

#include <borg/cairo/cairo_dc.hpp>
#include <borg/util/assert.hpp>

// declare instantiable stuff in namespace "tk" as specialization of the templates..
namespace borg {
namespace tk {

template<>
  class paint_dc<cairo::traits> : public dc_wrapper<cairo::traits>
{
protected:
  cairo_surface_t *m_surface;
  cairo_t *m_cairo;
  
public:
  //! Takes a system drawcontext handle and creates both, 
  //! a cairo_surface_t and a cairo_t upon it.
  paint_dc(void *__sysdc)
#if defined(CAIRO_HAS_WIN32_SURFACE) || defined(WIN32)
    : dc_wrapper<cairo::traits>(cairo_create(cairo_win32_surface_create((HDC)__sysdc)))
#elif defined(CAIRO_HAS_XLIB_SURFACE)
    : dc_wrapper<cairo::traits>(cairo_create(0))
#else
#error "Could not determine cairo surface type."
#endif
    , m_surface(cairo_get_target(get()))
  {
    m_cairo = get();

    ASSERT(m_cairo)
    ASSERT(m_surface)
        
    /* std::cout << "surface: " << m_surface << std::endl;
    std::cout << "cairo: " << &wrapper_type::unwrap() << std::endl;*/
  }
    
  //! Takes an existing cairo_surface_t and creates a new cairo_t.
  paint_dc(cairo_surface_t *__surface) :
    dc_wrapper<cairo::traits>(cairo_create(__surface)),
    m_surface(0) 
  {
    m_cairo = get();
      
    ASSERT(m_cairo)
    ASSERT(m_surface)
  }

  //! Takes a cairo_t which must already be associated with a cairo_surface_t target.
  paint_dc(cairo_t *__cairo) :
    dc_wrapper<cairo::traits>(__cairo), 
    m_surface(0), m_cairo(0)
  {
    ASSERT(cairo_get_target(get()))
  }
    
  //! Free the surface if it was us who allocated it.
  ~paint_dc()
  {
    if(m_cairo)
      cairo_destroy(m_cairo);
    
/*     if(m_surface)
        cairo_surface_destroy(m_surface);*/
  }
};

template<>
  class client_dc<cairo::traits> : public dc_wrapper<cairo::traits>
{
public:
  client_dc(cairo_t *__cairo) : dc_wrapper<cairo::traits>(__cairo) {}
};

} // namespace tk
namespace cairo {

  typedef tk::paint_dc<traits> paint_dc;
  typedef tk::client_dc<traits> client_dc;
} // namespace cairo
} // namespace borg

#endif // CAIRO_TK_HPP
