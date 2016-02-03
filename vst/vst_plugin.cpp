#include <vst/vst_plugin.hpp>
#include <borg/msg.hpp>

namespace vst {

audioMasterCallback master = 0;
static AudioEffect *effect;

//-------------------------------------------------------------------
plugin::plugin() : AudioEffectX(master, 0, 0)
{
  MSG_BOX("new plugin: master=%p, &ceffect=%p", master, &cEffect);
  
  effect = this;
}

//-------------------------------------------------------------------
plugin::~plugin()
{
}  

//-------------------------------------------------------------------
} // end of namespace vst
