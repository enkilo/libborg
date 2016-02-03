#include <vst/vst_master.hpp>
#include <borg/msg.hpp>

namespace vst {

//-------------------------------------------------------------------
  std::map<AEffect *, master *> master::m_map;
  
//-------------------------------------------------------------------
master::master(const std::string &path) : loader(path), m_aeffect(0)
{
  if(is_open())
    m_aeffect = (*m_main)(dispatch);
  
  if(m_aeffect == 0)
    close();
  else
    m_map[m_aeffect] = this;
}

//-------------------------------------------------------------------
master::~master()
{
}  

//-------------------------------------------------------------------
VstIntPtr master::dispatch
  (AEffect *effect, VstInt32 opcode, VstInt32 index, VstIntPtr value, 
   void *ptr, float opt)
{
  // get version request
  if(effect == 0 && index == 0 && value == 0 && ptr == 0 && opt == 0)
    return kVstVersion;
  
  master *mst = m_map[effect];

  if(mst)
    return mst->callback(opcode, index, value, ptr, opt);
  
  MSG_BOX("vst::master for (AEffect *)%p not found!", effect);
  return 0;
}
  
//-------------------------------------------------------------------
VstIntPtr master::call(VstInt32 opcode, VstInt32 index, VstIntPtr value,
                       void *ptr, float opt) const
{
  if(m_aeffect == 0)
  {
    MSG_BOX("vst::master::call() with m_aeffect=NULL");
    return 0;
  }
  
  if(m_aeffect->dispatcher == 0)
  {
    MSG_BOX("vst::master::call() with m_aeffect->dispatcher=NULL");
    return 0;
  }
  
  return m_aeffect->dispatcher(m_aeffect, opcode, index, value, ptr, opt);
}

//-------------------------------------------------------------------
} // end of namespace vst
