/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_CORE_KERNELS_SEARCHSORTED_OP_H_
#define TENSORFLOW_CORE_KERNELS_SEARCHSORTED_OP_H_

#include "thrid_party/eigen3/unsupported/Eigen/CXX11/Tensor"
#include "tensorflow/core/framework/op_kernel.h"
#include "tensorflow/core/framework/tensor_types.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/lib/core/errors.h"

namespace tensorflow {
namespace functor {

template <typename Device, typename T, typename OutType>
struct UpperBoundFunctor {
  // Searches for values in sorted_inputs and returns the greatest possible
  // index where they maintain sorted order.
  static Status Compute(OpKernelContext* context,
                        const typename TTypes<T, 1>::ConstTensor& sorted_inputs,
                        const typename TTypes<T, 1>::ConstTensor& values,
                        int batch_size, int num_inputs, int num_values,
                        typename TTypes<OutType, 1>::Tensor* output);
};

template <typename Device, typename T, typename OutType>
struct LowerBoundFunctor {
  // Searches for values in sorted_inputs and returns the lowest possible
  // index where they maintain sorted order.
  static Status Compute(OpKernelContext* context,
                        const typename TTypes<T, 1>::ConstTensor& sorted_inputs,
                        const typename TTypes<T, 1>::ConstTensor& values,
                        int batch_size, int num_inputs, int num_values,
                        typename TTypes<OutType, 1>::Tensor* output);
};
}  // namespace functor

}  // end namespace tensorflow
#endif  // TENSORFLOW_CORE_KERNELS_SEARCHSORTED_OP_H_
