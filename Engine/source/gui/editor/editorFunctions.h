// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _EDITORFUNCTIONS_H_
#define _EDITORFUNCTIONS_H_

class SimObject;

// Returns true if the passed name can be assigned to the passed object.
// This is true if that name is not already in use and it is a valid identifier,
// ( starts with a alpha character ).
bool validateObjectName( const char *name, const SimObject *object );

#endif // _EDITORFUNCTIONS_H_