#include <borg/wx/tk.hpp>
#include "vst/vst_wxeditor.hpp"
#include "widgets/scope_drawer.hpp"
#include "reverse_buffer.hpp"

//#define msg(x...) do { char b[1024]; sprintf(b,x); MessageBox(0, (b), "MSG", 0); } while(0);
#define msg(x...) do { FILE *fp = stderr; fprintf(fp, x); fputc('\n',fp); fflush(fp); } while(0);

/* Plugin GUI */
class TestEditor : public vst::wxeditor
{
public:
  TestEditor(vst::plugin &effect, buffer<float> &output);
  virtual ~TestEditor();
  
protected:
  virtual bool getRect(ERect **rect);
  virtual bool open(void *ptr);
  virtual void close();
  
//  virtual void setParameter(long index, float value);
//  virtual void valueChanged(CDrawContext *context, CControl *control);
    
  virtual void idle();
  
private:
  friend class Test;
  
  bool isOpen;
//  CRect size;
  borg::tk::scope_drawer<borg::wx::traits> *scope;
//  CScopeView *test;
//  CBitmap *bmp;
};

/* Plugin DSP */
class Test : public vst::plugin
{
protected:
  TestEditor *editor;
//  Shakers *shakers;
  VstInt32 currentNote;
  reverse_buffer<float> *buffer;

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

