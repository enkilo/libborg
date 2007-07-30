#ifndef BORG_UTIL_LAZY_INSTANCE_HPP
#define BORG_UTIL_LAZY_INSTANCE_HPP

namespace borg {

//----------------------------------------------------------------------------
template<class T>
class lazy_instance
{
public:
  lazy_instance() 
    : m_inst() 
  {}

  ~lazy_instance()
  {
    if(m_inst)
      delete m_inst;
  }

  operator T &()
  {
    return *get();
  }

  operator T const &() const
  {
    return *get();
  }

private:
  T *m_inst;
  T *get()
  {
    if(!m_inst)
      m_inst = new T;
    
    return m_inst;
  }
  
};  

} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_UTIL_LAZY_INSTANCE_HPP
