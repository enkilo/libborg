#include <vst/vst_proxy.hpp>
#include <borg/msg.hpp>

#define DEBUG 1

namespace vst {

//-------------------------------------------------------------------
proxy::proxy(const std::string &path) : 
  master(path) //, AudioEffectX(0, 0, 0)
{
}

//-------------------------------------------------------------------
proxy::~proxy()
{
}  

//-------------------------------------------------------------------
VstIntPtr
proxy::callback(VstInt32 opcode, VstInt32 index, VstIntPtr value, void *ptr, float opt)
{
#ifdef DEBUG
  MSG_BOX("proxy::callback(%p, %i, %i, %p, %p, %f)",
         m_aeffect, opcode, index, (void *)value, ptr, opt);
#endif /* DEBUG */
  return 0;
}

//-------------------------------------------------------------------
void
proxy::open()
{
  call(effOpen, 0, 0, 0, 0);
}

//-------------------------------------------------------------------
void
proxy::close()
{
  call(effClose, 0, 0, 0, 0);
  rtld::close();
}
  
//-------------------------------------------------------------------
void
proxy::suspend()
{
  call(effMainsChanged, 0, 0, 0, 0);
}
  
//-------------------------------------------------------------------
void
proxy::resume()
{
  call(effMainsChanged, 0, 1, 0, 0);
}

//-------------------------------------------------------------------
void 
proxy::set_sample_rate(float sampleRate)
{
  call(effSetSampleRate, 0, 0, 0, sampleRate);
}

//-------------------------------------------------------------------
void
proxy::set_block_size(VstInt32 blockSize)
{
  call(effSetBlockSize, 0, blockSize, 0, 0);
}
  
//-------------------------------------------------------------------
void 
proxy::process_replacing(float **inputs, float **outputs, VstInt32 sampleFrames)
{
  m_aeffect->processReplacing
    (m_aeffect, inputs, outputs, sampleFrames);
}
  
//-------------------------------------------------------------------
#if VST_2_4_EXTENSIONS
void 
proxy::process_double_replacing(double** inputs, double** outputs, VstInt32 sampleFrames)
{
  m_aeffect->processDoubleReplacing(m_aeffect, inputs, outputs, sampleFrames);
}  
#endif // VST_2_4_EXTENSIONS
  
//-------------------------------------------------------------------
void
proxy::set_parameter(VstInt32 index, float value)
{
  m_aeffect->setParameter(m_aeffect, index, value);
}
  
//-------------------------------------------------------------------
float
proxy::get_parameter(VstInt32 index)
{
  return m_aeffect->getParameter(m_aeffect, index);
}

//-------------------------------------------------------------------
VstInt32
proxy::get_program()
{
  return (VstInt32)call(effGetProgram, 0, 0, 0, 0);
}

//-------------------------------------------------------------------
void 
proxy::set_program(VstInt32 program)
{
  call(effSetProgram, 0, (VstIntPtr)program, 0,  0);
}

//-------------------------------------------------------------------
void 
proxy::set_program_name(char *name)
{
  call(effSetProgramName, 0, 0, name, 0);
}

//-------------------------------------------------------------------
void 
proxy::get_program_name(char *name)
{
  call(effGetProgramName, 0, 0, name, 0);
}

//-------------------------------------------------------------------
void 
proxy::get_parameter_label(VstInt32 index, char *label)
{
  call(effGetParamLabel, index, 0, label,  0);
}

//-------------------------------------------------------------------
void
proxy::get_parameter_display(VstInt32 index, char *text)
{
  call(effGetParamDisplay, index, 0, text,  0);
}

//-------------------------------------------------------------------
void 
proxy::get_parameterName(VstInt32 index, char *text)
{
  call(effGetParamName, index, 0, text,  0);
}

//-------------------------------------------------------------------
VstInt32 
proxy::get_chunk(void **data, bool isPreset)
{
  return (VstInt32)call(effGetChunk, isPreset, 0, data, 0);
}

//-------------------------------------------------------------------
VstInt32 
proxy::set_chunk(void *data, VstInt32 byteSize, bool isPreset)
{
  return (VstInt32)call(effSetChunk, isPreset, (VstIntPtr)byteSize, data, 0);
}

//-------------------------------------------------------------------
bool
proxy::get_editor_rect(ERect **rect)
{
  return (bool)call(effEditGetRect, 0, 0, (void *)rect, 0);
}
  
//-------------------------------------------------------------------
bool
proxy::open_editor(void *ptr)
{
  return (bool)call(effEditOpen, 0, 0, ptr, 0);
}

//-------------------------------------------------------------------
void
proxy::close_editor()
{
  call(effEditClose, 0, 0, 0, 0);
}

//-------------------------------------------------------------------
void
proxy::idle()
{
  call(effEditIdle, 0, 0, 0, 0);
}

//-------------------------------------------------------------------
} // end of namespace vst
