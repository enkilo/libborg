#ifndef VST_PLUGIN_HPP
#define VST_PLUGIN_HPP

#ifdef VSTSDK_INSTALLED
#include <vstsdk/audioeffectx.h>
#else
#include "public.sdk/source/vst2.x/audioeffectx.h"
#endif

//! Called by VSTPluginMain
#define VST_PLUGIN(_class) \
AudioEffect *createEffectInstance(audioMasterCallback audioMaster) \
{ \
  vst::master = audioMaster; \
  _class *aeff = new _class(); \
  return aeff; \
}

#define DLL_MAIN() \
HINSTANCE hInstance; \
BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpvReserved) \
{ \
  hInstance = hInst; \
  return TRUE; \
}

namespace vst {

extern audioMasterCallback master;

class plugin : public AudioEffectX
{
public:
  plugin();
  virtual ~plugin();
};
  
} // end of namespace wrap
#endif // VST_PLUGIN_HPP
