// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _MATRIXSETDELEGATES_H_
#define _MATRIXSETDELEGATES_H_

   // Access to the direct value
#define MATRIX_SET_GET_VALUE_FN(xfm) _transform_##xfm
#define MATRIX_SET_GET_VALUE(xfm) inline const MatrixF &MATRIX_SET_GET_VALUE_FN(xfm)() { return mTransform[xfm]; }
#define MATRIX_SET_BIND_VALUE(xfm) mEvalDelegate[xfm].bind(this, &MatrixSet::MATRIX_SET_GET_VALUE_FN(xfm))

#define MATRIX_SET_IS_INVERSE_OF_FN(inv_xfm, src_xfm) _##inv_xfm##_is_inverse_of_##src_xfm
#define MATRIX_SET_IS_INVERSE_OF(inv_xfm, src_xfm) inline const MatrixF &MATRIX_SET_IS_INVERSE_OF_FN(inv_xfm, src_xfm)() \
   { \
      m_matF_invert_to(mEvalDelegate[src_xfm](), mTransform[inv_xfm]); \
      MATRIX_SET_BIND_VALUE(inv_xfm); \
      return mTransform[inv_xfm]; \
   }


#define MATRIX_SET_MULT_ASSIGN_FN(matA, matB, matC) _##matC##_is_##matA##_x_##matB
#define MATRIX_SET_MULT_ASSIGN(matA, matB, matC) inline const MatrixF &MATRIX_SET_MULT_ASSIGN_FN(matA, matB, matC)() \
   { \
      m_matF_x_matF_aligned(mEvalDelegate[matA](), mEvalDelegate[matB](), mTransform[matC]); \
      MATRIX_SET_BIND_VALUE(matC); \
      return mTransform[matC]; \
   }


#endif // _MATRIXSETDELEGATES_H_
