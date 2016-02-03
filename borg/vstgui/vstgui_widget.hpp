#warning "obsolete"
  template<>
    struct view_traits<tk::vstgui>
  {
    typedef CView *wrap_type;
    typedef int vector_type;
    typedef unsigned char color_type;
    typedef abstract::view<true> interface_type;
  };
  
  //! Wraps vstguiWindow class into an implementation of abstract::view.
  template<>
    class view<tk::vstgui> : public wrapper<view_traits<tk::vstgui>::wrap_type>,
                             public view_traits<tk::vstgui>
  {
  public:
    typedef view_traits<tk::vstgui> traits_type;
  
    view_TYPEDEF(traits_type::vector_type, 
                 traits_type::color_type)

    view(wrap_type __vstguiview) : wrapper<wrap_type>(__vstguiview)
    {}

    inline void
    view<tk::vstgui>::pos(point_type &pt) const
    {
      CRect rect = wrapper_type::get().getViewSize();
      pt.x() = rect.x;
      pt.y() = rect.y;
    }

    inline void
    view<tk::vstgui>::move(const point_type &pt)
    {
      CRect rect = wrapper_type::get().getViewSize();
      rect.x = pt.x();
      rect.y = pt.y();
      wrapper_type::get().setViewSize(rect);
    }
  
    inline void
    view<tk::vstgui>::size(size_type &sz) const
    {
      CRect rect = wrapper_type::get().getViewSize();
      sz.w() = rect.width();
      sz.h() = rect.height();
    }
    
    inline void
    view<tk::vstgui>::resize(const size_type &sz)
    {
      CRect rect = wrapper_type::get().getViewSize();
      rect.setWidth(sz.w());
      rect.setHeight(sz.h());
      wrapper_type::get().setViewSize(rect);
    }
  
    inline void
    view<tk::vstgui>::rect(rect_type &rt) const
    {
      CRect rect = wrapper_type::get().getViewSize();
      rt.x() = rect.x;
      rt.y() = rect.y;
      rt.w() = rect.width();
      rt.h() = rect.height();
    }

    /*  inline void
     view<tk::vstgui>::show(bool sw)
     {
     }*/
  };
