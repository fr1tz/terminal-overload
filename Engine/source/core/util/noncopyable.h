// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _CORE_NONCOPYABLE_H_
#define _CORE_NONCOPYABLE_H_

class Noncopyable
{
protected:
   Noncopyable() {}
   ~Noncopyable() {}

private:
   Noncopyable(const Noncopyable&);
   const Noncopyable& operator=(const Noncopyable&);
};

#endif
