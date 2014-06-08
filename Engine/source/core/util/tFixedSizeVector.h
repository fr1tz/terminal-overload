// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TFIXEDSIZEVECTOR_H_
#define _TFIXEDSIZEVECTOR_H_


/// A vector with a compile-time constant size.
template< typename T, S32 SIZE >
class FixedSizeVector
{
   protected:

      T mArray[ SIZE ];

   public:

      typedef T* iterator;
      typedef const T* const_iterator;

      FixedSizeVector() {}
      FixedSizeVector( const T& a ) { mArray[ 0 ] = a; }
      FixedSizeVector( const T& a, const T& b ) { mArray[ 0 ] = a; mArray[ 1 ] = b; }
      FixedSizeVector( const T& a, const T& b, const T& c ) { mArray[ 0 ] = a; mArray[ 1 ] = b; mArray[ 2 ] = c; }
      FixedSizeVector( const T& a, const T& b, const T& c, const T& d ) { mArray[ 0 ] = a; mArray[ 1 ] = b; mArray[ 2 ] = c; mArray[ 3 ] = d; }
      FixedSizeVector( const T& a, const T& b, const T& c, const T& d, const T& e ) { mArray[ 0 ] = a; mArray[ 1 ] = b; mArray[ 2 ] = c; mArray[ 3 ] = d; mArray[ 4 ] = e; }
      FixedSizeVector( const T& a, const T& b, const T& c, const T& d, const T& e, const T& f )
         { mArray[ 0 ] = a; mArray[ 1 ] = b; mArray[ 2 ] = c; mArray[ 3 ] = d; mArray[ 4 ] = e; mArray[ 5 ] = f; }
      FixedSizeVector( const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g )
         { mArray[ 0 ] = a; mArray[ 1 ] = b; mArray[ 2 ] = c; mArray[ 3 ] = d; mArray[ 4 ] = e; mArray[ 5 ] = f; mArray[ 6 ] = g; }
      FixedSizeVector( const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g, const T& h )
         { mArray[ 0 ] = a; mArray[ 1 ] = b; mArray[ 2 ] = c; mArray[ 3 ] = d; mArray[ 4 ] = e; mArray[ 5 ] = f; mArray[ 6 ] = g; mArray[ 7 ] = h; }
      FixedSizeVector( const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g, const T& h, const T& i )
         { mArray[ 0 ] = a; mArray[ 1 ] = b; mArray[ 2 ] = c; mArray[ 3 ] = d; mArray[ 4 ] = e; mArray[ 5 ] = f; mArray[ 6 ] = g; mArray[ 7 ] = h; mArray[ 8 ] = i; }
      FixedSizeVector( const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g, const T& h, const T& i, const T& j )
         { mArray[ 0 ] = a; mArray[ 1 ] = b; mArray[ 2 ] = c; mArray[ 3 ] = d; mArray[ 4 ] = e; mArray[ 5 ] = f; mArray[ 6 ] = g; mArray[ 7 ] = h; mArray[ 8 ] = i; mArray[ 9 ] = j; }
      FixedSizeVector( const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g, const T& h, const T& i, const T& j, const T& k )
         { mArray[ 0 ] = a; mArray[ 1 ] = b; mArray[ 2 ] = c; mArray[ 3 ] = d; mArray[ 4 ] = e; mArray[ 5 ] = f; mArray[ 6 ] = g; mArray[ 7 ] = h; mArray[ 8 ] = i; mArray[ 9 ] = j; mArray[ 10 ] = k; }
      FixedSizeVector( const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g, const T& h, const T& i, const T& j, const T& k, const T& l )
         { mArray[ 0 ] = a; mArray[ 1 ] = b; mArray[ 2 ] = c; mArray[ 3 ] = d; mArray[ 4 ] = e; mArray[ 5 ] = f; mArray[ 6 ] = g; mArray[ 7 ] = h; mArray[ 8 ] = i; mArray[ 9 ] = j; mArray[ 10 ] = k; mArray[ 11 ] = l; }
      FixedSizeVector( const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g, const T& h, const T& i, const T& j, const T& k, const T& l, const T& m )
         { mArray[ 0 ] = a; mArray[ 1 ] = b; mArray[ 2 ] = c; mArray[ 3 ] = d; mArray[ 4 ] = e; mArray[ 5 ] = f; mArray[ 6 ] = g; mArray[ 7 ] = h; mArray[ 8 ] = i; mArray[ 9 ] = j; mArray[ 10 ] = k; mArray[ 11 ] = l; mArray[ 12 ] =m; }

      U32 size() const { return SIZE; }
      bool empty() const { return ( SIZE == 0 ); }
      const T* address() const { return mArray; }
      T* address() { return mArray; }

      iterator begin() { return &mArray[ 0 ]; }
      iterator end() { return &mArray[ SIZE ]; }
      const_iterator begin() const { return &mArray[ 0 ]; }
      const_iterator end() const { return &mArray[ SIZE ]; }

      const T& first() const
      {
         AssertFatal( !empty(), "FixedSizeVector::first - Vector is empty" );
         return mArray[ 0 ];
      }
      T& first()
      {
         AssertFatal( !empty(), "FixedSizeVector::first - Vector is empty" );
         return mArray[ 0 ];
      }
      const T& last() const
      {
         AssertFatal( !empty(), "FixedSizeVector::last - Vector is empty" );
         return mArray[ size() - 1 ];
      }
      T& last()
      {
         AssertFatal( !empty(), "FixedSizeVector::last - Vector is empty" );
         return mArray[ size() - 1 ];
      }

      const T& operator []( U32 index ) const
      {
         AssertFatal( index <= size(), "FixedSizeVector::operator[] - Index out of range" );
         return mArray[ index ];
      }
      T& operator []( U32 index )
      {
         AssertFatal( index <= size(), "FixedSizeVector::operator[] - Index out of range" );
         return mArray[ index ];
      }
};

#endif // !_TFIXEDSIZEVECTOR_H_
