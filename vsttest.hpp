#include <borg/vstgui/vstgui_tk.hpp>
#include <vst/vst_plugin.hpp>
#include <vstgui/aeffguieditor.h>
#include <borg/vstgui/vstgui_wrappers.hpp>
#include <widgets/scope_drawer.hpp>
#include <reverse_buffer.hpp>
#include <ring_buffer.hpp>
#include <widgets/scope_drawer.hpp>
#include <iostream>

//#define msg(x...) do { char b[1024]; sprintf(b,x); MessageBox(0, (b), "MSG", 0); } while(0);
#define msg(x...) do { FILE *fp = stderr; fprintf(fp, x); fputc('\n',fp); fflush(fp); } while(0);

using namespace VSTGUI;
using namespace std;
using namespace abstract;
using namespace borg;
using namespace borg::tk;

class CScopeView : public CView
{
protected:
  scope_drawer<vstgui::traits> &drawer;
  COffscreenContext *context;
//  CBitmap *pixmap;
  
public:
  
  
  CScopeView(CFrame *pFrame, const CRect &size, scope_drawer<vstgui::traits> &drw) :
    CView(size), drawer(drw)
  {
//    pixmap = new CBitmap(*pFrame, size.width(), size.height());
    context = new COffscreenContext(pFrame, size.width(), size.height(), kBlackCColor);

      
    setDirty();
  }
  
  virtual ~CScopeView() {}
  virtual void draw(CDrawContext *dc)
  {
    CView::draw(dc);

    dc_wrapper<vstgui::traits> vstdc(context);
    vstgui::traits::rect_type rect(0, 0, size.width(), size.height());

    vstdc.set_stroke_color(34, 90, 192);
    vstdc.set_fill_color(0, 0, 0, 255);
//    vstdc.set_draw_style(draw_stroked_and_filled);
    vstdc.draw_rect(rect);
    
    drawer(*dc, rect);

    vstdc.set_stroke_color(128, 128, 128);
    vstdc.draw_rect(rect);

    context->copyFrom(dc, size);
  }
};

/* Plugin GUI */
class TestEditor : public AEffGUIEditor
{
public:
  TestEditor(AudioEffect *pEffect, buffer<float> &output);
  virtual ~TestEditor();
  
protected:
  virtual bool getRect(ERect **rect);
  virtual bool open(void *ptr);
  virtual void close();
  
  virtual void setParameter(long index, float value);
  virtual void valueChanged(CDrawContext *context, CControl *control);

  virtual void idle();
  
private:
  friend class Test;
  
  bool isOpen;
  CRect size;
  scope_drawer<vstgui::traits> *scope;
  CScopeView *test;
  CBitmap *bmp;
  widget<vstgui::traits> *testwidget;
  
  bool draw_testwidget(CDrawContext &dc, const list<CRect> &rects)
  {
    dc_wrapper<vstgui::traits> mydc(&dc);
    mydc.set_fill_color(45, 180, 140);
//    dc.set_draw_style(abstract::draw_filled);
    
    vstgui::traits::rect_type r;
    testwidget->rect(r);

    
    mydc.draw_rect(r);
    
//    cout << "redrawing testwidget: " << r << endl;
    return true;
  }
  
};

/* Plugin DSP */
class Test : public vst::plugin
{
protected:
  TestEditor *editor;
//  Shakers *shakers;
  VstInt32 currentNote;
  buffer<float> *buf;

public:
  Test();
  virtual ~Test();
  
  void processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames);
  VstInt32 processEvents(VstEvents *events);

  void noteOn(VstInt32 note, VstInt32 velocity, VstInt32 delta);
  void noteOff();

  VstInt32 canDo(char *text);
  virtual VstInt32 getNumMidiInputChannels();
};

