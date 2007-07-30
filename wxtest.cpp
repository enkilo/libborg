#include <iostream>
#include "drawtest.hpp"
/*#include <event.hpp>

#include <cairo.h>
#ifdef WIN32
#include <cairo-win32.h>
#endif
#include <vst/vst_proxy.hpp>
#include <types/rect_type.hpp>

#include <wx/wrappers.hpp>*/
#include <borg/wx.hpp>
#include <borg/wx/tk.hpp>
#include <borg/wx/listbox.hpp>
#include "widgets/togglebutton_widget.hpp"

using namespace std;
using namespace borg;
using namespace event;
using namespace boost;

//---------------------------------------------------------------------------
class wxtest_listbox : public wx::listbox
{
public:
  typedef wx::listbox base_type;
  
  BORG_TK_LISTBOX_TYPES(wx::traits)
  
  wxtest_listbox(widget_type &parent, const string_array_type &choices)
    : base_type(parent, wx::default_id,
                point_type(25, 250), size_type(200, 200), choices, (style_type)single,
                wx::default_validator, "wxtest_listbox")
  {}
  
  wxtest_listbox(widget_type &parent, index_type n = 0, const string_type choices[] = 0)
    : base_type(parent, wx::default_id,
                point_type(25, 250), size_type(200, 200), n, choices, (style_type)single,
                wx::default_validator, "wxtest_listbox")
  {}
};

struct wrap_rect : public wxRect
{
  inline wrap_rect(int x, int y, int w, int h) :
    wxRect(x, y, w, h)
  {}
  
  inline int width() { return wxRect::GetWidth(); }
    
};

//!///////////////////////////////////////////////////////////////////////////
class wxtest_frame : public wx::frame //wxFrame
{
public:
  BORG_TK_FRAME_TYPES(wx::traits)

  wxtest_frame(wxApp *app);
  virtual ~wxtest_frame();
  
  void UpdateUI();
  
private:
  DECLARE_EVENT_TABLE()

  wxApp *m_app;
  wxButton *m_button;
  wxWindow *m_widget;
  wxtest_listbox *m_listbox;

  bool on_mouseup(int x, int y, event::mouse::button b);
  bool on_mousedown(int x, int y, event::mouse::button b);
  bool on_mousedclick(int x, int y, event::mouse::button b);
  bool on_mousemove(int x, int y, int buttons);
  bool on_redraw(dc_type &dc, const list<rect_type> &rects);

  // event handlers
  void OnUpdateUI(wxUpdateUIEvent &event);
  void OnClose(wxCloseEvent &event);
  void OnSize(wxSizeEvent &event);
  void OnPaint(wxPaintEvent &event);
  void OnMouse(wxMouseEvent &event);
};

//---------------------------------------------------------------------------
BEGIN_EVENT_TABLE(wxtest_frame, wxFrame)
  EVT_UPDATE_UI(0, wxtest_frame::OnUpdateUI)
  EVT_CLOSE(wxtest_frame::OnClose)
  EVT_SIZE(wxtest_frame::OnSize)
  EVT_PAINT(wxtest_frame::OnPaint)
  EVT_LEFT_DOWN(wxtest_frame::OnMouse)
  EVT_LEFT_UP(wxtest_frame::OnMouse)
  EVT_LEFT_DCLICK(wxtest_frame::OnMouse)
  EVT_RIGHT_DOWN(wxtest_frame::OnMouse)
  EVT_RIGHT_UP(wxtest_frame::OnMouse)
  EVT_RIGHT_DCLICK(wxtest_frame::OnMouse)
  EVT_MIDDLE_DOWN(wxtest_frame::OnMouse)
  EVT_MIDDLE_UP(wxtest_frame::OnMouse)
  EVT_MIDDLE_DCLICK(wxtest_frame::OnMouse)
  EVT_MOUSEWHEEL(wxtest_frame::OnMouse)
  EVT_MOTION(wxtest_frame::OnMouse)
END_EVENT_TABLE()

//---------------------------------------------------------------------------
bool wxtest_frame::on_mouseup(int x, int y, event::mouse::button b)
{
  cout << "mouseup(" << x << ", " << y << ", " << b << ")" << endl;
  return false;
}

//---------------------------------------------------------------------------
bool wxtest_frame::on_mousedown(int x, int y, event::mouse::button b)
{
  cout << "mousedown(" << x << ", " << y << ", " << b << ")" << endl;
  return false;
}

//---------------------------------------------------------------------------
bool wxtest_frame::on_mousemove(int x, int y, int buttons)
{
  cout << "mousemove(" << x << ", " << y << ", " << buttons << ")" << endl;
  return false;  
}

//---------------------------------------------------------------------------
bool wxtest_frame::on_redraw(dc_type &dc, const list<rect_type> &rects)
{  
  return false;  
}

//---------------------------------------------------------------------------
wxtest_frame::wxtest_frame(wxApp *app) 
  : wx::frame(wx::default_id, "wxtest")//, vsttest("vsttest.dlL")
  , m_app(app)
{
  
  wx::traits::size_type sza = get_best_size();
  
  std::cout << "best_size: " << sza.GetWidth() << "x" << sza.GetHeight() << std::endl;
  
  move(point_type(0,0));
  show();
  
  set_status_text("this is a test");
  
  wxSize sz(100, 100);
  wxPoint pt(GetSize().GetWidth() - sz.x, GetSize().GetHeight() - sz.y);
  
  m_widget = new wxWindow(this, wxID_ANY, pt, sz, wxSUNKEN_BORDER);
  m_widget->SetBackgroundColour(wxColour(0, 96, 255));

  mem_fn(&wxtest_frame::on_mouseup)(this,0,0,mouse::lbutton);

  event::signal<event::mouseup, wx::traits> onmouseup;
  onmouseup.bind(&wxtest_frame::on_mouseup, this);
  onmouseup(3, 4, mouse::lbutton);

  wx::widget *v = new wx::widget(*this, wx::default_id, wxPoint(150, 50), wxSize(10, 100), wxRAISED_BORDER);

  wx::array<wxString> items;
  
  items.push_back("item 1");
  items.push_back("item 2");
  items.push_back("item 3");
  
  m_listbox = new wxtest_listbox(*this, items);
//  m_listbox->set(items);
  m_listbox->append("test");
  
  std::cout << "num items: " << m_listbox->count() << std::endl;
  
//  (*m_listbox)->Refresh();
  (*m_listbox)->Update();
  
/*  borg::tk::togglebutton< wx::traits > *toggle =
    new borg::tk::togglebutton<wx::traits >
    (*this, rect_type(40, 100, 250, 50), "toggle me!");*/

//  (void)toggle;
  
/*  ERect *erect;
  vsttest.get_editor_rect(&erect);
  
  rect<int> r(erect->left, erect->top,
              erect->right - erect->left,
              erect->bottom - erect->top);

  vsttest.get_editor_rect(&erect);*/

//  tk::adjust<wrap::wx> *adj = new tk::adjust<wrap::wx>(w, rect<int>(40, 40, 250, 50), "%0.5f test");
//  widget_wrapper<wx::traits> adjparent = adj->get_parent();

  wx::bitmap bmp(400, 100);

  std::cout << "bitmap loaded? " << bmp.load_file("test.bmp") << std::endl;
  std::cout << "size of bitmap wrapper: " << sizeof(borg::tk::bitmap_wrapper<wx::traits>) << std::endl;
  std::cout << "bitmap dimensions: " << bmp.width() << "x" << bmp.height() << std::endl;
  std::cout << "bitmap depth: " << bmp.get_depth() << std::endl;
  
/*  v->onmousemove.bind(&wxtest_frame::on_mousemove, this);
  v->onmouseup.bind(&wxtest_frame::on_mouseup, this);
  v->onmousedown.connect(event::bind_method(&wxtest_frame::on_mousedown, this));*/
  
  
//  v->onredraw.connect(util::bind_method(&wxtest_frame::on_redraw, this));
}

//---------------------------------------------------------------------------
wxtest_frame::~wxtest_frame()
{
}
  
//---------------------------------------------------------------------------
void
wxtest_frame::UpdateUI()
{
}

//---------------------------------------------------------------------------
/*void wxtest_frame::drawtest()
{
}*/
  
//---------------------------------------------------------------------------
void
wxtest_frame::OnUpdateUI(wxUpdateUIEvent &event)
{
  cout << "OnUpdateUI" << endl;
}

//---------------------------------------------------------------------------
void
wxtest_frame::OnClose(wxCloseEvent &event)
{
  borg::tk::widget_wrapper<wx::traits> w = this;
  
  point_type pt;
  w.get_position(pt);
  cout << "pos on close: " << pt.x << "," << pt.y << endl;
  
  cout << "Close" << endl;
//  Close();

//  SetEvtHandlerEnabled(false);
//  if(!event.CanVeto())
    Destroy();

  
  event.Skip();
//  Update();
  
//  cout << "main loop is running: " << m_app->IsMainLoopRunning() << endl;
//  m_app->ExitMainLoop();
//  event.Veto();
}

//---------------------------------------------------------------------------
void
wxtest_frame::OnSize(wxSizeEvent &event)
{
  wxSize size = event.GetSize();
  cout << "Resize to: " << size.x << "x" << size.y << endl;
}

//---------------------------------------------------------------------------
void
wxtest_frame::OnPaint(wxPaintEvent &event)
{
  //wxPaintDC wxdc(this);
  //wx::dc wrap(&wxdc);
  wx::paint_dc wrap(*this);
  wxDC &wxdc = wrap;
  
//  wrap::drawable<int, unsigned char, wxDC> wrap(&wxdc);
  
  wrap.set_stroke_color(rgba<unsigned char>(255, 0, 0));
  wrap.draw_point(0, 0);

  wrap.set_stroke_color(rgba<unsigned char>(0, 255, 0));
  wrap.draw_point(1, 1);
  
  wrap.set_stroke_color(rgba<unsigned char>(0, 0, 255, 0));
//  wrap.set_fill_color(rgba<unsigned char>(0,0,0,0));

  wrap.set_draw_style(types::draw_stroked_and_filled);
  wrap.draw_rect(2, 2, 40, 40);

  wrap.set_fill_color(rgba<unsigned char>(255,255,0));
  wrap.set_draw_style(types::draw_filled);
  wrap.draw_elliptic_arc(50, 50, 100, 80, 0.0, M_PI_2 + M_PI_4);
  
  wrap.set_stroke_color(rgba<double>(1.0, 1.0, 0.0, 1.0));
  wrap.set_fill_color(rgba<double>(1.0, 0.0, 0.0, 0.5));
  wrap.draw_elliptic_arc(100, 50, 90, 60, M_PI_4, M_PI_4 + M_PI_2 + M_PI);

  
  wrap.set_font_color(rgba<unsigned char>(255, 255, 255, 255));
//  wrap.set_font_type(types::font_fixed);
  
  rect_type fontrect(100, 100, 200, 30);

  wrap.set_draw_style(types::draw_stroked);
  wrap.draw_rect(fontrect);
  wrap.draw_text("this is a test|¦", fontrect);
    
#ifdef CAIRO_HAS_WIN32_SURFACE
  HDC hdc = (HDC)wxdc.GetHDC();
  cairo_surface_t *csf = cairo_win32_surface_create(hdc);
#elif defined(CAIRO_HAS_XLIB_SURFACE)
#if 0 //def __WXGTK20__
   GdkWindow* hwin = wxdc.GetGDKWindow();
//   GdkDrawableImplX11 *impl = GDK_DRAWABLE_IMPL_X11(drawable);

//  G_DEFINE_TYPE (GdkDrawableImplX11, _gdk_drawable_impl_x11, GDK_TYPE_DRAWABLE);    
  
//   void *hdc = ;
   cairo_surface_t *csf; // = cairo_xlib_surface_create(GDK_SCREEN_XDISPLAY(impl));
#else
#define NO_CAIRO 1
#endif
#else
#error "Could not determine cairo surface type."
#endif
  
#ifndef NO_CAIRO
  cairo_t *ccx = cairo_create(csf);
  
  std::cout << "HDC: " << wrap.get_pointer() << std::endl;
  
  cairo::paint_dc cairo(wrap.get_pointer());
  ccx = 0;
 
  fflush(stdout);
  fflush(stderr);
  
  cairo.move_to(100, 100);
  cairo.line_to(125, 150);
  cairo.line_to(150, 125);

  cairo.set_draw_style(types::draw_stroked_and_filled);
  cairo.set_stroke_width(2.0);
  
  cairo.set_stroke_color(rgba<double>(1.0, 1.0, 0.0, 1.0));
  cairo.set_fill_color(rgba<double>(1.0, 0.0, 0.0, 0.5));
//  cairo.draw_ellipse(rect_type(100, 100, 60, 30));
  
  cairo.set_stroke_color(rgba<double>(1.0, 1.0, 0.0, 1.0));
  cairo.set_fill_color(rgba<double>(1.0, 0.0, 0.0, 0.5));
//  cairo.draw_arc(rect_type(100, 50, 90, 60), M_PI_4, M_PI_4 + M_PI_2 + M_PI);

  cairo.set_stroke_color(rgba<double>(0.0, 0.0, 0.0, 1.0));
  cairo.set_fill_color(rgba<double>(0.0, 0.1234, 0.9876, 0.5));
  cairo.draw_rect(0, 0, 60, 30);

  drawtest(cairo);
  
    
  cairo.set_font_color(rgba<double>(1.0, 1.0, 1.0, 1.0));
//  cairo.set_font_type(types::font_fixed);
  
  
  cairo::traits::rect_type fontrect2(100, 130, 200, 30);
  cairo.set_draw_style(types::draw_stroked);
  cairo.set_stroke_width(1.0);
  cairo.draw_rect(fontrect2);
  cairo.draw_text("this is a test|", fontrect2);
/*  
 
  cairo_set_source_rgb(ctx, 1.0, 0, 0);
  cairo_set_antialias(ctx, CAIRO_ANTIALIAS_DEFAULT);

  cairo_new_path(ctx);
  cairo_move_to(ctx, 100, 100);
  cairo_line_to(ctx, 125, 150);
  cairo_line_to(ctx, 150, 125);
  cairo_close_path(ctx);
  cairo_stroke(ctx);
  
  cairo_rectangle(ctx, 150, 40, 40, 20);
  cairo_stroke(ctx);
  
  cairo_destroy(ctx);
  
 */
//  cairo_surface_flush(csf);
  
//  cairo_surface_finish(csf);

  //cairo_surface_destroy(csf);
  
  
//  vsttest.idle();
#endif  
}

//---------------------------------------------------------------------------
void
wxtest_frame::OnMouse(wxMouseEvent &event)
{
  if(event.ButtonDown())
    cout << "Mouse button down" << endl;

  if(event.ButtonUp())
    cout << "Mouse button up" << endl;  
  
  
}

//!//////////////////////////////////////////////////////////////////////////
class wxtestApp : public wxApp
{
public:
  virtual bool OnInit()
  {
    cout << "App name: " << GetAppName() << endl;

    wxtest_frame *frame = new wxtest_frame(this);
    
//    frame->Show(true);
    SetTopWindow(frame);
    cout << "size of wxRect: " << sizeof(wxRect) << endl;
    cout << "size of wrap_rect: " << sizeof(wrap_rect) << endl;
    
    wrap_rect r(0, 1, 2, 3);
    cout << "rect width: " << r.width() << endl;
    
    return true;
  }
  
  virtual int OnExit()
  {
    cout << "wxApp::OnExit" << endl;
  }
};

//---------------------------------------------------------------------------
IMPLEMENT_APP(wxtestApp)
