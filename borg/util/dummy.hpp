#ifndef BORG_DUMMY_HPP
#define BORG_DUMMY_HPP

namespace borg {

//---------------------------------------------------------------------------

struct dummy 
{
  typedef struct dummy const &ref;
  typedef struct dummy const *ptr;
};

} // namespace borg

#endif //ndef BORG_DUMMY_HPP
