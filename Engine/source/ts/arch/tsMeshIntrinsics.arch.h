// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TSMESHINTRINSICS_ARCH_H_
#define _TSMESHINTRINSICS_ARCH_H_

#if defined(TORQUE_CPU_X86)
# // x86 CPU family implementations
extern void zero_vert_normal_bulk_SSE(const dsize_t count, U8 * __restrict const outPtr, const dsize_t outStride);
extern void m_matF_x_BatchedVertWeightList_SSE(const MatrixF &mat, const dsize_t count, const TSSkinMesh::BatchData::BatchedVertWeight * __restrict batch, U8 * const __restrict outPtr, const dsize_t outStride);
#if (_MSC_VER >= 1500)
extern void m_matF_x_BatchedVertWeightList_SSE4(const MatrixF &mat, const dsize_t count, const TSSkinMesh::BatchData::BatchedVertWeight * __restrict batch, U8 * const __restrict outPtr, const dsize_t outStride);
#endif
#
#elif defined(TORQUE_CPU_PPC)
# // PPC CPU family implementations
#  if defined(TORQUE_OS_XENON)
extern void zero_vert_normal_bulk_X360(const dsize_t count, U8 * __restrict const outPtr, const dsize_t outStride);
extern void m_matF_x_BatchedVertWeightList_X360(const MatrixF &mat, const dsize_t count, const TSSkinMesh::BatchData::BatchedVertWeight * __restrict batch, U8 * const __restrict outPtr, const dsize_t outStride);
#  else
extern void zero_vert_normal_bulk_gccvec(const dsize_t count, U8 * __restrict const outPtr, const dsize_t outStride);
extern void m_matF_x_BatchedVertWeightList_gccvec(const MatrixF &mat, const dsize_t count, const TSSkinMesh::BatchData::BatchedVertWeight * __restrict batch, U8 * const __restrict outPtr, const dsize_t outStride);
#  endif
#
#else
# // Other CPU types go here...
#endif

#endif // _TSMESHINTRINSICS_ARCH_H_

