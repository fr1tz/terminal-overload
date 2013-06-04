// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TUNMANAGEDVECTOR_H_
#define _TUNMANAGEDVECTOR_H_


/// An array that does not manage the memory it gets passed.  Conversely, the
/// array cannot be enlarged.
///
/// @note As the array does not manage the instances it uses, it will also not
///   destruct them when it is itself destructed.
template< typename T >
class UnmanagedVector
{
   protected:

      U32 mCount;
      T* mArray;

   public:

      typedef T* iterator;
      typedef const T* const_iterator;

      UnmanagedVector()
         : mCount( 0 ), mArray( NULL ) {}
      UnmanagedVector( T* array, U32 count )
         : mArray( array ), mCount( count ) {}

      U32 size() const { return mCount; }
      bool empty() const { return ( mCount == 0 ); }
      const T* address() const { return mArray; }
      T* address() { return mArray; }

      void clear() { mCount = 0; mArray = NULL; }

      iterator begin() { return &mArray[ 0 ]; }
      iterator end() { return &mArray[ mCount ]; }
      const_iterator begin() const { return &mArray[ 0 ]; }
      const_iterator end() const { return &mArray[ mCount ]; }

      const T& first() const
      {
         AssertFatal( !empty(), "UnmanagedVector::first - Vector is empty" );
         return mArray[ 0 ];
      }
      T& first()
      {
         AssertFatal( !empty(), "UnmanagedVector::first - Vector is empty" );
         return mArray[ 0 ];
      }
      const T& last() const
      {
         AssertFatal( !empty(), "UnmanagedVector::last - Vector is empty" );
         return mArray[ mCount - 1 ];
      }
      T& last()
      {
         AssertFatal( !empty(), "UnmanagedVector::last - Vector is empty" );
         return mArray[ mCount - 1 ];
      }

      const T& operator []( U32 index ) const
      {
         AssertFatal( index <= size(), "UnmanagedVector::operator[] - Index out of range" );
         return mArray[ index ];
      }
      T& operator []( U32 index )
      {
         AssertFatal( index <= size(), "UnmanagedVector::operator[] - Index out of range" );
         return mArray[ index ];
      }
};

#endif // !_TUNMANAGEDVECTOR_H_
