#ifndef STATE_OBSERVER_HPP
#define STATE_OBSERVER_HPP

namespace borg {
  
template<typename StateT, typename Subject>
struct state_observer
{
  typedef state_observer<StateT, Subject> this_type;
  
  state_observer(Subject &subject, const StateT &state = StateT())
    : m_subject(subject), m_state(state)
  {}

  const StateT &
  get() const
  {
    return m_state;
  }
  
  operator StateT() const { return get(); }
  
  state_observer<StateT, Subject> &
  set(const StateT &state)
  {
    if(!(m_state == state))
    {
      m_state = state;
      m_subject.notify(*this);
    }
    return *this;
  }
  
  state_observer<StateT, Subject> &
  operator=(const StateT &state) { return set(state); }
  
private:
  StateT m_state;
  Subject &m_subject;
};
  
template<typename StateT, typename Subject>
state_observer<StateT, Subject>
state_observe(const StateT &initial = StateT(), Subject subject = Subject())
{
  return state_observer<StateT, Subject>(subject, initial);
}
  
} // namespace borg
//---------------------------------------------------------------------------
#endif //ndef STATE_OBSERVER_HPP
