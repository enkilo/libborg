#ifndef VST_MASTER_HPP
#define VST_MASTER_HPP

#include <vst/vst_loader.hpp>
#include <map>

namespace vst {
  
  class master : public loader
  {
  public:
    master(const std::string &path);
    virtual ~master();

  protected:
    AEffect *m_aeffect;
    
    //! Calls from plugin to master.
    virtual VstIntPtr callback
      (VstInt32 opcode, VstInt32 index, VstIntPtr value, 
       void *ptr, float opt) = 0;

    //! Calls from master to plugin.
    VstIntPtr call
      (VstInt32 opcode, VstInt32 index, VstIntPtr value, 
       void *ptr, float opt) const;
    
  private:
    static std::map<AEffect *, master *> m_map;
    
    static VstIntPtr dispatch
      (AEffect *effect, VstInt32 opcode, VstInt32 index,
       VstIntPtr value, void *ptr, float opt);
  };
  
} // end of namespace wrap
#endif //ndef VST_MASTER_HPP
