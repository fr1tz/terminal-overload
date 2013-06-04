// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TALGORITHM_H_
#define _TALGORITHM_H_


/// Finds the first matching value within the container
/// returning the the element or last if its not found.
template <class Iterator, class Value>
Iterator find(Iterator first, Iterator last, Value value)
{
   while (first != last && *first != value)
      ++first;
   return first;
}

/// Exchanges the values of the two elements.
template <typename T> 
inline void swap( T &left, T &right )
{
   T temp = right;
   right = left;
   left = temp;
}

/// Steps thru the elements of an array calling detete for each.
template <class Iterator, class Functor>
void for_each( Iterator first, Iterator last, Functor func )
{
   for ( ; first != last; first++ )
      func( *first );
}

/// Functor for deleting a pointer.
/// @see for_each
struct delete_pointer
{
  template <typename T>
  void operator()(T *ptr){ delete ptr;}
};

#endif //_TALGORITHM_H_
