#ifndef VST_PROXY_HPP
#define VST_PROXY_HPP

#ifdef VSTSDK_INSTALLED
#include <vstsdk/aeffect.h>
#include <vstsdk/audioeffectx.h>
#else
#include "pluginterfaces/vst2.x/aeffect.h"
#include "public.sdk/source/vst2.x/audioeffectx.h"
#endif

#include <vst/vst_master.hpp>

namespace vst {
  
  class proxy : public master/*, public AudioEffectX*/
  {
  protected:
    VstIntPtr callback
      (VstInt32 opcode, VstInt32 index, VstIntPtr value, void *ptr, float opt);
    
  public:
    proxy(const std::string &path);
    virtual ~proxy();

    void open();
    void close();
    void suspend();
    void resume();
    
    void set_sample_rate(float sampleRate);
    void set_block_size(VstInt32 blockSize);
    void process_replacing(float **inputs, float **outputs, VstInt32 sampleFrames);
    void process_double_replacing(double** inputs, double** outputs, VstInt32 sampleFrames);
    
    void set_parameter(VstInt32 index, float value);
    float get_parameter(VstInt32 index);
    void set_parameter_automated(VstInt32 index, float value) {}

    VstInt32 get_program();
    void set_program(VstInt32 program);
    void set_program_name(char *name);
    void get_program_name(char *name);
    void get_parameter_label(VstInt32 index, char *label);
    void get_parameter_display(VstInt32 index, char *text);
    void get_parameterName(VstInt32 index, char *text);
    VstInt32 get_chunk(void **data, bool isPreset = false);
    VstInt32 set_chunk(void *data, VstInt32 byteSize, bool isPreset = false);
    
    bool get_editor_rect(ERect **rect);
    bool open_editor(void *ptr);
    void close_editor();
    void idle();
  };
  
} // end of namespace wrap
#endif //ndef VST_PROXY_HPP
