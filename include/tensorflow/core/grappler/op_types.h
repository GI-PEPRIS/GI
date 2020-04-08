/* Copyright 2017 The TensorFlow Authors. All Rights Reserved.

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

#ifndef TENSORFLOW_CORE_GRAPPLER_OP_TYPES_H_
#define TENSORFLOW_CORE_GRAPPLER_OP_TYPES_H_

#include "tensorflow/core/framework/node_def.pb.h"
#include "tensorflow/core/framework/op.h"
#include "tensorflow/core/lib/core/status.h"

#include "tensorflow/tensorflow.h" //herman

namespace tensorflow {
namespace grappler {
TF_API_NO_C bool IsAdd(const NodeDef& node);
TF_API_NO_C bool IsAddN(const NodeDef& node);
TF_API_NO_C bool IsAll(const NodeDef& node);
TF_API_NO_C bool IsAngle(const NodeDef& node);
TF_API_NO_C bool IsAny(const NodeDef& node);
TF_API_NO_C bool IsAnyDiv(const NodeDef& node);
TF_API_NO_C bool IsAnyMatMul(const NodeDef& node);
TF_API_NO_C bool IsAnyMax(const NodeDef& node);
TF_API_NO_C bool IsAnyMaxPool(const NodeDef& node);
TF_API_NO_C bool IsAnyMin(const NodeDef& node);
TF_API_NO_C bool IsAnyMul(const NodeDef& node);
TF_API_NO_C bool IsApproximateEqual(const NodeDef& node);
TF_API_NO_C bool IsArg(const NodeDef& node);
TF_API_NO_C bool IsArgMax(const NodeDef& node);
TF_API_NO_C bool IsArgMin(const NodeDef& node);
TF_API_NO_C bool IsAssert(const NodeDef& node);
TF_API_NO_C bool IsAssign(const NodeDef& node);
TF_API_NO_C bool IsAtan2(const NodeDef& node);
TF_API_NO_C bool IsAvgPoolGrad(const NodeDef& node);
TF_API_NO_C bool IsBetainc(const NodeDef& node);
TF_API_NO_C bool IsBiasAdd(const NodeDef& node);
TF_API_NO_C bool IsBiasAddGrad(const NodeDef& node);
TF_API_NO_C bool IsBitcast(const NodeDef& node);
TF_API_NO_C bool IsCast(const NodeDef& node);
TF_API_NO_C bool IsCheckNumerics(const NodeDef& node);
TF_API_NO_C bool IsCollective(const NodeDef& node);
TF_API_NO_C bool IsComplex(const NodeDef& node);
TF_API_NO_C bool IsComplexAbs(const NodeDef& node);
TF_API_NO_C bool IsConcat(const NodeDef& node);
TF_API_NO_C bool IsConcatOffset(const NodeDef& node);
TF_API_NO_C bool IsConj(const NodeDef& node);
TF_API_NO_C bool IsConjugateTranspose(const NodeDef& node);
TF_API_NO_C bool IsConstant(const NodeDef& node);
TF_API_NO_C bool IsControlFlow(const NodeDef& node);
TF_API_NO_C bool IsConv2D(const NodeDef& node);
TF_API_NO_C bool IsConv2DBackpropFilter(const NodeDef& node);
TF_API_NO_C bool IsConv2DBackpropInput(const NodeDef& node);
TF_API_NO_C bool IsConv3D(const NodeDef& node);
TF_API_NO_C bool IsDepthwiseConv2dNative(const NodeDef& node);
TF_API_NO_C bool IsDepthwiseConv2dNativeBackpropFilter(const NodeDef& node);
TF_API_NO_C bool IsDepthwiseConv2dNativeBackpropInput(const NodeDef& node);
TF_API_NO_C bool IsDequeueOp(const NodeDef& node);
TF_API_NO_C bool IsDiv(const NodeDef& node);
TF_API_NO_C bool IsDivNoNan(const NodeDef& node);
TF_API_NO_C bool IsElementWiseMonotonic(const NodeDef& node, bool* is_non_decreasing);
TF_API_NO_C bool IsElu(const NodeDef& node);
TF_API_NO_C bool IsEluGrad(const NodeDef& node);
TF_API_NO_C bool IsEnter(const NodeDef& node);
TF_API_NO_C bool IsEqual(const NodeDef& node);
TF_API_NO_C bool IsExit(const NodeDef& node);
TF_API_NO_C bool IsExp(const NodeDef& node);
TF_API_NO_C bool IsFakeParam(const NodeDef& node);
TF_API_NO_C bool IsFill(const NodeDef& node);
TF_API_NO_C bool IsFloorDiv(const NodeDef& node);
TF_API_NO_C bool IsFloorMod(const NodeDef& node);
TF_API_NO_C bool IsFusedBatchNorm(const NodeDef& node);
TF_API_NO_C bool IsFusedBatchNormGrad(const NodeDef& node);
TF_API_NO_C bool IsGreater(const NodeDef& node);
TF_API_NO_C bool IsGreaterEqual(const NodeDef& node);
TF_API_NO_C bool IsHistogramSummary(const NodeDef& node);
TF_API_NO_C bool IsHostConstant(const NodeDef& node);
TF_API_NO_C bool IsIdentity(const NodeDef& node);
TF_API_NO_C bool IsIdentityN(const NodeDef& node);
TF_API_NO_C bool IsIdentityNSingleInput(const NodeDef& node);
TF_API_NO_C bool IsIf(const NodeDef& node);
TF_API_NO_C bool IsIgamma(const NodeDef& node);
TF_API_NO_C bool IsIgammac(const NodeDef& node);
TF_API_NO_C bool IsImag(const NodeDef& node);
TF_API_NO_C bool IsImmutableConst(const NodeDef& node);
TF_API_NO_C bool IsInvGrad(const NodeDef& node);
TF_API_NO_C bool IsLess(const NodeDef& node);
TF_API_NO_C bool IsLessEqual(const NodeDef& node);
TF_API_NO_C bool IsLog(const NodeDef& node);
TF_API_NO_C bool IsLogicalAnd(const NodeDef& node);
TF_API_NO_C bool IsLogicalNot(const NodeDef& node);
TF_API_NO_C bool IsLogicalOr(const NodeDef& node);
TF_API_NO_C bool IsMatMul(const NodeDef& node);
TF_API_NO_C bool IsMax(const NodeDef& node);
TF_API_NO_C bool IsMaxPoolGrad(const NodeDef& node);
TF_API_NO_C bool IsMaximum(const NodeDef& node);
TF_API_NO_C bool IsMean(const NodeDef& node);
TF_API_NO_C bool IsMerge(const NodeDef& node);
TF_API_NO_C bool IsMin(const NodeDef& node);
TF_API_NO_C bool IsMinimum(const NodeDef& node);
TF_API_NO_C bool IsMirrorPad(const NodeDef& node);
TF_API_NO_C bool IsMirrorPadGrad(const NodeDef& node);
TF_API_NO_C bool IsMod(const NodeDef& node);
TF_API_NO_C bool IsMul(const NodeDef& node);
TF_API_NO_C bool IsMulNoNan(const NodeDef& node);
TF_API_NO_C bool IsNeg(const NodeDef& node);
TF_API_NO_C bool IsNextIteration(const NodeDef& node);
TF_API_NO_C bool IsNoOp(const NodeDef& node);
TF_API_NO_C bool IsNotEqual(const NodeDef& node);
TF_API_NO_C bool IsOnesLike(const NodeDef& node);
TF_API_NO_C bool IsPack(const NodeDef& node);
TF_API_NO_C bool IsPack(const NodeDef& node);
TF_API_NO_C bool IsPad(const NodeDef& node);
TF_API_NO_C bool IsPartitionedCall(const NodeDef& node);
TF_API_NO_C bool IsPlaceholder(const NodeDef& node);
TF_API_NO_C bool IsPolygamma(const NodeDef& node);
TF_API_NO_C bool IsPow(const NodeDef& node);
TF_API_NO_C bool IsPrint(const NodeDef& node);
TF_API_NO_C bool IsProd(const NodeDef& node);
TF_API_NO_C bool IsQuantizedMatMul(const NodeDef& node);
TF_API_NO_C bool IsQueue(const NodeDef& node);
TF_API_NO_C bool IsRandomShuffle(const NodeDef& node);
TF_API_NO_C bool IsRank(const NodeDef& node);
TF_API_NO_C bool IsReadVariableOp(const NodeDef& node);
TF_API_NO_C bool IsReal(const NodeDef& node);
TF_API_NO_C bool IsRealDiv(const NodeDef& node);
TF_API_NO_C bool IsReciprocalGrad(const NodeDef& node);
TF_API_NO_C bool IsRecv(const NodeDef& node);
TF_API_NO_C bool IsReduction(const NodeDef& node);
TF_API_NO_C bool IsRelu(const NodeDef& node);
TF_API_NO_C bool IsRelu6(const NodeDef& node);
TF_API_NO_C bool IsRelu6Grad(const NodeDef& node);
TF_API_NO_C bool IsReluGrad(const NodeDef& node);
TF_API_NO_C bool IsReshape(const NodeDef& node);
TF_API_NO_C bool IsRestore(const NodeDef& node);
TF_API_NO_C bool IsRetval(const NodeDef& node);
TF_API_NO_C bool IsReverse(const NodeDef& node);
TF_API_NO_C bool IsReverseV2(const NodeDef& node);
TF_API_NO_C bool IsRsqrt(const NodeDef& node);
TF_API_NO_C bool IsRsqrtGrad(const NodeDef& node);
TF_API_NO_C bool IsSelect(const NodeDef& node);
TF_API_NO_C bool IsSeluGrad(const NodeDef& node);
TF_API_NO_C bool IsSend(const NodeDef& node);
TF_API_NO_C bool IsShape(const NodeDef& node);
TF_API_NO_C bool IsShapeN(const NodeDef& node);
TF_API_NO_C bool IsShuffle(const NodeDef& node);
TF_API_NO_C bool IsSigmoidGrad(const NodeDef& node);
TF_API_NO_C bool IsSize(const NodeDef& node);
TF_API_NO_C bool IsSlice(const NodeDef& node);
TF_API_NO_C bool IsSnapshot(const NodeDef& node);
TF_API_NO_C bool IsSoftmax(const NodeDef& node);
TF_API_NO_C bool IsSoftplusGrad(const NodeDef& node);
TF_API_NO_C bool IsSoftsignGrad(const NodeDef& node);
TF_API_NO_C bool IsSplit(const NodeDef& node);
TF_API_NO_C bool IsSplitV(const NodeDef& node);
TF_API_NO_C bool IsSqrt(const NodeDef& node);
TF_API_NO_C bool IsSqrtGrad(const NodeDef& node);
TF_API_NO_C bool IsSquare(const NodeDef& node);
TF_API_NO_C bool IsSquaredDifference(const NodeDef& node);
TF_API_NO_C bool IsSqueeze(const NodeDef& node);
TF_API_NO_C bool IsStackCloseOp(const NodeDef& node);
TF_API_NO_C bool IsStackOp(const NodeDef& node);
TF_API_NO_C bool IsStackPopOp(const NodeDef& node);
TF_API_NO_C bool IsStackPushOp(const NodeDef& node);
TF_API_NO_C bool IsStatefulPartitionedCall(const NodeDef& node);
TF_API_NO_C bool IsStopGradient(const NodeDef& node);
TF_API_NO_C bool IsStridedSlice(const NodeDef& node);
TF_API_NO_C bool IsStridedSliceGrad(const NodeDef& node);
TF_API_NO_C bool IsSub(const NodeDef& node);
TF_API_NO_C bool IsSum(const NodeDef& node);
TF_API_NO_C bool IsSwitch(const NodeDef& node);
TF_API_NO_C bool IsSymbolicGradient(const NodeDef& node);
TF_API_NO_C bool IsTanhGrad(const NodeDef& node);
TF_API_NO_C bool IsTensorArray(const NodeDef& node);
TF_API_NO_C bool IsTile(const NodeDef& node);
TF_API_NO_C bool IsTranspose(const NodeDef& node);
TF_API_NO_C bool IsTruncateDiv(const NodeDef& node);
TF_API_NO_C bool IsTruncateMod(const NodeDef& node);
TF_API_NO_C bool IsUnpack(const NodeDef& node);
TF_API_NO_C bool IsVariable(const NodeDef& node);
TF_API_NO_C bool IsWhile(const NodeDef& node);
TF_API_NO_C bool IsXdivy(const NodeDef& node);
TF_API_NO_C bool IsZerosLike(const NodeDef& node);
TF_API_NO_C bool IsZeta(const NodeDef& node);

// Return true if the op is an aggregation (e.g. Add, AddN).
// Returns false if it could not be determined to be so.
TF_API_NO_C bool IsAggregate(const NodeDef& node);

// Return true if the op is commutative (e.g. Mul, Add).
// Returns false if it could not be determined to be so.
TF_API_NO_C bool IsCommutative(const NodeDef& node);

// Returns true if the node is known to use persistent memory to store its
// value.
TF_API_NO_C bool IsPersistent(const NodeDef& node);

// Returns true if the node belongs to the NC_DATASET class (see graph/graph.h).
TF_API_NO_C bool IsDataset(const NodeDef& node);

// Returns true if the node op is marked as stateful, or if it was not found in
// op_registry.
TF_API_NO_C bool IsStateful(const NodeDef node, const OpRegistryInterface* op_registry);
TF_API_NO_C bool IsStateful(const NodeDef node);  // use OpRegistry::Global()

TF_API_NO_C bool IsFreeOfSideEffect(const NodeDef& node,
                        const OpRegistryInterface* op_registry);
TF_API_NO_C bool IsFreeOfSideEffect(const NodeDef& node);  // use OpRegistry::Global()

// Returns true if the takes a tensor reference as input.
// Returns false if the op type is unknown.
TF_API_NO_C bool HasRefInput(const NodeDef& node);

TF_API_NO_C bool ModifiesFrameInfo(const NodeDef& node);

// Returns true if the op is known to write to one or more of its inputs.
TF_API_NO_C bool ModifiesInputsInPlace(const NodeDef& node);

// Returns true if the op is an element-wise involution, i.e. if it is its
// own inverse such that f(f(x)) == x.
TF_API_NO_C bool IsInvolution(const NodeDef& node);

// Returns true if the op preserves the order and value of elements
// and shape of its first input tensor.
TF_API_NO_C bool IsValueAndOrderAndShapePreserving(const NodeDef& node);

// Returns true if the op preserves the order and value of elements in its
// first input tensor and possible changes its shape.
TF_API_NO_C bool IsValueAndOrderPreserving(const NodeDef& node);

// Returns true if the op in node only rearranges the order of elements in its
// first input tensor and possible changes its shape. More precisely, this
// function returns true if the op commutes with all element-wise operations.
TF_API_NO_C bool IsValuePreserving(const NodeDef& node);

// Returns true if node is idempotent w.r.t. its first input, i.e. if
// Op(Op(x, y, z), y, z) = Op(x, y, z).
TF_API_NO_C bool IsIdempotent(const NodeDef& node);

TF_API_NO_C bool IsUnaryElementWise(const NodeDef& node);

// Returns true if we can find an opdef corresponding to the op of the node.
TF_API_NO_C bool HasOpDef(const NodeDef& node);

// Returns true if the op changes the scalar type of its first input elements
// and preserves the number of elements.
TF_API_NO_C bool IsCastLike(const NodeDef& node);

// Returns true if this op never forwards any of its inputs, i.e. always
// allocates buffers for its inputs.
TF_API_NO_C bool NeverForwardsInputs(const NodeDef& node);

}  // end namespace grappler
}  // end namespace tensorflow

#endif  // TENSORFLOW_CORE_GRAPPLER_OP_TYPES_H_
