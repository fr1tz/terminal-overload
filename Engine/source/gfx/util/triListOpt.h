// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TRI_LIST_OPT_H_
#define _TRI_LIST_OPT_H_

#include "core/util/tVector.h"

namespace TriListOpt
{
   typedef U32 IndexType;

   const U32 MaxSizeVertexCache = 32;

   struct VertData
   {
      S32 cachePosition;
      F32 score;
      U32 numReferences;
      U32 numUnaddedReferences;
      S32 *triIndex;

      VertData() : cachePosition(-1), score(0.0f), numReferences(0), numUnaddedReferences(0), triIndex(NULL) {}
      ~VertData() { if(triIndex != NULL) delete [] triIndex; triIndex = NULL; }
   };

   struct TriData
   {
      bool isInList;
      F32 score;
      U32 vertIdx[3];

      TriData() : isInList(false), score(0.0f) { dMemset(vertIdx, 0, sizeof(vertIdx)); }
   };

   class LRUCacheModel
   {
      struct LRUCacheEntry
      {
         LRUCacheEntry *next;
         U32 vIdx;
         VertData *vData;

         LRUCacheEntry() : next(NULL), vIdx(0), vData(NULL) {}
      };

      LRUCacheEntry *mCacheHead;

   public:
      LRUCacheModel() : mCacheHead(NULL) {}
      ~LRUCacheModel();
      void enforceSize(const dsize_t maxSize, Vector<U32> &outTrisToUpdate);
      void useVertex(const U32 vIdx, VertData *vData);
      S32 getCachePosition(const U32 vIdx);
   };


   /// This method will look at the index buffer for a triangle list, and generate
   /// a new index buffer which is optimized using Tom Forsyth's paper:
   /// "Linear-Speed Vertex Cache Optimization" 
   /// http://home.comcast.net/~tom_forsyth/papers/fast_vert_cache_opt.html
   /// @param   numVerts Number of vertices indexed by the 'indices'
   /// @param numIndices Number of elements in both 'indices' and 'outIndices'
   /// @param    indices Input index buffer
   /// @param outIndices Output index buffer
   ///
   /// @note Both 'indices' and 'outIndices' can point to the same memory.
   void OptimizeTriangleOrdering(const dsize_t numVerts, const dsize_t numIndices, const U32 *indices, IndexType *outIndices);

   namespace FindVertexScore
   {
      const F32 CacheDecayPower = 1.5f;
      const F32 LastTriScore = 0.75f;
      const F32 ValenceBoostScale = 2.0f;
      const F32 ValenceBoostPower = 0.5f;

      F32 score(const VertData &vertexData);
   };
};

#endif