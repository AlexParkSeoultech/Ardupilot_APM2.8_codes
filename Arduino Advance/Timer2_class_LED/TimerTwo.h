#ifndef __TIMERTWO_H__
#define __TIMERTWO_H__
#include <stdint.h>
typedef void (*_procedure)(void );
class Timer2{
  public:
  void init(_procedure);
  static _procedure _proc;
};
#endif
