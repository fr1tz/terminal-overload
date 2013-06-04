// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFXOCCLUSIONQUERY_H_
#define _GFXOCCLUSIONQUERY_H_

#ifndef _GFXDEVICE_H_
#include "gfx/gfxDevice.h"
#endif


/// A geometry visibility query object.
/// @see GFXDevice::createOcclusionQuery
class GFXOcclusionQuery : public GFXResource
{
protected:

   GFXDevice *mDevice;
   
   GFXOcclusionQuery( GFXDevice *device ) 
      : mDevice( device )
   {
   }   

public:

   /// The states returned by getStatus()
   /// If you modify this enum you should also modify statusToString()
   enum OcclusionQueryStatus
   {
      Unset,         ///<      
      Waiting,       ///< 
      Error,         ///< 
      Occluded,
      NotOccluded
   };   
      
   virtual ~GFXOcclusionQuery() {}
   
   /// Prepares the query returning true if the last query
   /// has been processed and more geometry can be issued.
   /// @see getStatus
   virtual bool begin() = 0;
   
   /// Called after your geometry is drawn to submit
   /// the query for processing.
   virtual void end() = 0;   
   
   /// Returns the status of the last submitted query.  In general
   /// you should avoid blocking for the result until the frame 
   /// following your query to keep from stalling the CPU.
   /// @return       Status    
   /// @param block  If true CPU will block until the query finishes.
   /// @param data   Number of pixels rendered, valid only if status returned is NotOccluded.
   virtual OcclusionQueryStatus getStatus( bool block, U32 *data = NULL ) = 0;
   
   /// Returns a status string.
   static String statusToString( OcclusionQueryStatus status );

   // GFXResource
   virtual void zombify() = 0;   
   virtual void resurrect() = 0;
   virtual const String describeSelf() const = 0;
};

#endif // _GFXOCCLUSIONQUERY_H_