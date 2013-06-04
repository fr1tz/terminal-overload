// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TSMESHINTRINSICS_H_
#define _TSMESHINTRINSICS_H_

/// This is the batch-by-transform skin loop
///
/// @param mat       Bone transform
/// @param count     Number of input elements in the batch
/// @param batch     Pointer to the first element in an aligned array of input elements
/// @param outPtr    Pointer to index 0 of a TSMesh aligned vertex buffer
/// @param outStride Size, in bytes, of one entry in the vertex buffer
extern void (*m_matF_x_BatchedVertWeightList)
                                   (const MatrixF &mat, 
                                    const dsize_t count,
                                    const TSSkinMesh::BatchData::BatchedVertWeight * __restrict batch,
                                    U8 * const __restrict outPtr,
                                    const dsize_t outStride);

/// Set the vertex position and normal to (0, 0, 0)
///
/// @param count     Number of elements
/// @param outPtr    Pointer to a TSMesh aligned vertex buffer
/// @param outStride Size, in bytes, of one entry in the vertex buffer
extern void (*zero_vert_normal_bulk)
                          (const dsize_t count, 
                           U8 * __restrict const outPtr, 
                           const dsize_t outStride);

#endif

