// This file is MACHINE GENERATED! Do not edit.

#ifndef D__TF_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_RESOURCE_VARIABLE_OPS_H_
#define D__TF_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_RESOURCE_VARIABLE_OPS_H_

// This file is MACHINE GENERATED! Do not edit.

#include "tensorflow/cc/framework/ops.h"
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/lib/gtl/array_slice.h"

#include "tensorflow/tensorflow.h"//herman

namespace tensorflow {
namespace ops {

/// @defgroup resource_variable_ops Resource Variable Ops
/// @{

/// Adds a value to the current value of a variable.
///
/// Any ReadVariableOp which depends directly or indirectly on this assign is
/// guaranteed to see the incremented value or a subsequent newer one.
/// 
/// Outputs the incremented value, which can be used to totally order the
/// increments to this variable.
///
/// Arguments:
/// * scope: A Scope object
/// * resource: handle to the resource in which to store the variable.
/// * value: the value by which the variable will be incremented.
///
/// Returns:
/// * the created `Operation`
class TF_CLASS AssignAddVariableOp {
 public:
  AssignAddVariableOp(const ::tensorflow::Scope& scope, ::tensorflow::Input
                    resource, ::tensorflow::Input value);
  operator ::tensorflow::Operation() const { return operation; }

  Operation operation;
};

/// Subtracts a value from the current value of a variable.
///
/// Any ReadVariableOp which depends directly or indirectly on this assign is
/// guaranteed to see the incremented value or a subsequent newer one.
/// 
/// Outputs the incremented value, which can be used to totally order the
/// increments to this variable.
///
/// Arguments:
/// * scope: A Scope object
/// * resource: handle to the resource in which to store the variable.
/// * value: the value by which the variable will be incremented.
///
/// Returns:
/// * the created `Operation`
class AssignSubVariableOp {
 public:
  AssignSubVariableOp(const ::tensorflow::Scope& scope, ::tensorflow::Input
                    resource, ::tensorflow::Input value);
  operator ::tensorflow::Operation() const { return operation; }

  Operation operation;
};

/// Assigns a new value to a variable.
///
/// Any ReadVariableOp with a control dependency on this op is guaranteed to return
/// this value or a subsequent newer value of the variable.
///
/// Arguments:
/// * scope: A Scope object
/// * resource: handle to the resource in which to store the variable.
/// * value: the value to set the new tensor to use.
///
/// Returns:
/// * the created `Operation`
class TF_CLASS AssignVariableOp {
 public:
  AssignVariableOp(const ::tensorflow::Scope& scope, ::tensorflow::Input
                 resource, ::tensorflow::Input value);
  operator ::tensorflow::Operation() const { return operation; }

  Operation operation;
};

/// Creates a handle to a CriticalSection resource.
///
/// Arguments:
/// * scope: A Scope object
///
/// Optional attributes (see `Attrs`):
/// * container: the container this critical section is placed in.
/// * shared_name: the name by which this critical section is referred to.
///
/// Returns:
/// * `Output`: The resource tensor.
class TF_CLASS CriticalSectionOp {
 public:
  /// Optional attribute setters for CriticalSectionOp
  struct Attrs {
    /// the container this critical section is placed in.
    ///
    /// Defaults to ""
    Attrs Container(StringPiece x) {
      Attrs ret = *this;
      ret.container_ = x;
      return ret;
    }

    /// the name by which this critical section is referred to.
    ///
    /// Defaults to ""
    Attrs SharedName(StringPiece x) {
      Attrs ret = *this;
      ret.shared_name_ = x;
      return ret;
    }

    StringPiece container_ = "";
    StringPiece shared_name_ = "";
  };
  CriticalSectionOp(const ::tensorflow::Scope& scope);
  CriticalSectionOp(const ::tensorflow::Scope& scope, const
                  CriticalSectionOp::Attrs& attrs);
  operator ::tensorflow::Output() const { return resource; }
  operator ::tensorflow::Input() const { return resource; }
  ::tensorflow::Node* node() const { return resource.node(); }

  static Attrs Container(StringPiece x) {
    return Attrs().Container(x);
  }
  static Attrs SharedName(StringPiece x) {
    return Attrs().SharedName(x);
  }

  ::tensorflow::Output resource;
};

/// Deletes the resource specified by the handle.
///
/// All subsequent operations using the resource will result in a NotFound
/// error status.
///
/// Arguments:
/// * scope: A Scope object
/// * resource: handle to the resource to delete.
///
/// Optional attributes (see `Attrs`):
/// * ignore_lookup_error: whether to ignore the error when the resource
/// doesn't exist.
///
/// Returns:
/// * the created `Operation`
class TF_CLASS DestroyResourceOp {
 public:
  /// Optional attribute setters for DestroyResourceOp
  struct Attrs {
    /// whether to ignore the error when the resource
    /// doesn't exist.
    ///
    /// Defaults to true
    Attrs IgnoreLookupError(bool x) {
      Attrs ret = *this;
      ret.ignore_lookup_error_ = x;
      return ret;
    }

    bool ignore_lookup_error_ = true;
  };
  DestroyResourceOp(const ::tensorflow::Scope& scope, ::tensorflow::Input
                  resource);
  DestroyResourceOp(const ::tensorflow::Scope& scope, ::tensorflow::Input
                  resource, const DestroyResourceOp::Attrs& attrs);
  operator ::tensorflow::Operation() const { return operation; }

  static Attrs IgnoreLookupError(bool x) {
    return Attrs().IgnoreLookupError(x);
  }

  Operation operation;
};

/// Executes function `f` within critical section `critical_section`.
///
/// While `f` is running in `critical_section`, no other functions which wish to
/// use this critical section may run.
/// 
/// Often the use case is that two executions of the same graph, in parallel,
/// wish to run `f`; and we wish to ensure that only one of them executes
/// at a time.  This is especially important if `f` modifies one or more
/// variables at a time.
/// 
/// It is also useful if two separate functions must share a resource, but we
/// wish to ensure the usage is exclusive.
/// 
/// The signature of `f` is expected to be:
/// 
/// ```
///   outputs <- F(arguments)
/// ```
/// Typically, but this is not required, `arguments` contain resources.  The
/// primary purpose of this op is to limit access to these resources to one
/// execution of `F` at a time.
///
/// Arguments:
/// * scope: A Scope object
/// * critical_section: The handle of the `critical_section`.
/// * arguments: Arguments for `f`, including any captured inputs appended at the end.
/// * f: The `Function` to execute.
///
/// Returns:
/// * `OutputList`: The outputs of `f`.
class TF_CLASS ExecuteInCriticalSection {
 public:
  ExecuteInCriticalSection(const ::tensorflow::Scope& scope, ::tensorflow::Input
                         critical_section, ::tensorflow::InputList arguments,
                         const NameAttrList& f, const DataTypeSlice&
                         output_types, const
                         gtl::ArraySlice<PartialTensorShape>& output_shapes);
  ::tensorflow::Output operator[](size_t index) const { return outputs[index]; }


  ::tensorflow::OutputList outputs;
};

/// Reads the value of a variable.
///
/// The tensor returned by this operation is immutable.
/// 
/// The value returned by this operation is guaranteed to be influenced by all the
/// writes on which this operation depends directly or indirectly, and to not be
/// influenced by any of the writes which depend directly or indirectly on this
/// operation.
///
/// Arguments:
/// * scope: A Scope object
/// * resource: handle to the resource in which to store the variable.
/// * dtype: the dtype of the value.
///
/// Returns:
/// * `Output`: The value tensor.
class TF_CLASS ReadVariableOp {
 public:
  ReadVariableOp(const ::tensorflow::Scope& scope, ::tensorflow::Input resource,
               DataType dtype);
  operator ::tensorflow::Output() const { return value; }
  operator ::tensorflow::Input() const { return value; }
  ::tensorflow::Node* node() const { return value.node(); }

  ::tensorflow::Output value;
};

/// Gather slices from the variable pointed to by `resource` according to `indices`.
///
/// `indices` must be an integer tensor of any dimension (usually 0-D or 1-D).
/// Produces an output tensor with shape `indices.shape + params.shape[1:]` where:
/// 
/// ```python
///     # Scalar indices
///     output[:, ..., :] = params[indices, :, ... :]
/// 
///     # Vector indices
///     output[i, :, ..., :] = params[indices[i], :, ... :]
/// 
///     # Higher rank indices
///     output[i, ..., j, :, ... :] = params[indices[i, ..., j], :, ..., :]
/// ```
///
/// Arguments:
/// * scope: A Scope object
///
/// Returns:
/// * `Output`: The output tensor.
class TF_CLASS ResourceGather {
 public:
  /// Optional attribute setters for ResourceGather
  struct Attrs {
    /// Defaults to true
    Attrs ValidateIndices(bool x) {
      Attrs ret = *this;
      ret.validate_indices_ = x;
      return ret;
    }

    bool validate_indices_ = true;
  };
  ResourceGather(const ::tensorflow::Scope& scope, ::tensorflow::Input resource,
               ::tensorflow::Input indices, DataType dtype);
  ResourceGather(const ::tensorflow::Scope& scope, ::tensorflow::Input resource,
               ::tensorflow::Input indices, DataType dtype, const
               ResourceGather::Attrs& attrs);
  operator ::tensorflow::Output() const { return output; }
  operator ::tensorflow::Input() const { return output; }
  ::tensorflow::Node* node() const { return output.node(); }

  static Attrs ValidateIndices(bool x) {
    return Attrs().ValidateIndices(x);
  }

  ::tensorflow::Output output;
};

/// Adds sparse updates to the variable referenced by `resource`.
///
/// This operation computes
/// 
///     # Scalar indices
///     ref[indices, ...] += updates[...]
/// 
///     # Vector indices (for each i)
///     ref[indices[i], ...] += updates[i, ...]
/// 
///     # High rank indices (for each i, ..., j)
///     ref[indices[i, ..., j], ...] += updates[i, ..., j, ...]
/// 
/// Duplicate entries are handled correctly: if multiple `indices` reference
/// the same location, their contributions add.
/// 
/// Requires `updates.shape = indices.shape + ref.shape[1:]`.
/// 
/// <div style="width:70%; margin:auto; margin-bottom:10px; margin-top:20px;">
/// <img style="width:100%" src='https://www.tensorflow.org/images/ScatterAdd.png' alt>
/// </div>
///
/// Arguments:
/// * scope: A Scope object
/// * resource: Should be from a `Variable` node.
/// * indices: A tensor of indices into the first dimension of `ref`.
/// * updates: A tensor of updated values to add to `ref`.
///
/// Returns:
/// * the created `Operation`
class TF_CLASS ResourceScatterAdd {
 public:
  ResourceScatterAdd(const ::tensorflow::Scope& scope, ::tensorflow::Input
                   resource, ::tensorflow::Input indices, ::tensorflow::Input
                   updates);
  operator ::tensorflow::Operation() const { return operation; }

  Operation operation;
};

/// Assigns sparse updates to the variable referenced by `resource`.
///
/// This operation computes
/// 
///     # Scalar indices
///     ref[indices, ...] = updates[...]
/// 
///     # Vector indices (for each i)
///     ref[indices[i], ...] = updates[i, ...]
/// 
///     # High rank indices (for each i, ..., j)
///     ref[indices[i, ..., j], ...] = updates[i, ..., j, ...]
///
/// Arguments:
/// * scope: A Scope object
/// * resource: Should be from a `Variable` node.
/// * indices: A tensor of indices into the first dimension of `ref`.
/// * updates: A tensor of updated values to add to `ref`.
///
/// Returns:
/// * the created `Operation`
class TF_CLASS ResourceScatterUpdate {
 public:
  ResourceScatterUpdate(const ::tensorflow::Scope& scope, ::tensorflow::Input
                      resource, ::tensorflow::Input indices,
                      ::tensorflow::Input updates);
  operator ::tensorflow::Operation() const { return operation; }

  Operation operation;
};

/// Creates a handle to a Variable resource.
///
/// Arguments:
/// * scope: A Scope object
/// * dtype: the type of this variable. Must agree with the dtypes
/// of all ops using this variable.
/// * shape: The (possibly partially specified) shape of this variable.
///
/// Optional attributes (see `Attrs`):
/// * container: the container this variable is placed in.
/// * shared_name: the name by which this variable is referred to.
///
/// Returns:
/// * `Output`: The resource tensor.
class TF_CLASS VarHandleOp {
 public:
  /// Optional attribute setters for VarHandleOp
  struct Attrs {
    /// the container this variable is placed in.
    ///
    /// Defaults to ""
    Attrs Container(StringPiece x) {
      Attrs ret = *this;
      ret.container_ = x;
      return ret;
    }

    /// the name by which this variable is referred to.
    ///
    /// Defaults to ""
    Attrs SharedName(StringPiece x) {
      Attrs ret = *this;
      ret.shared_name_ = x;
      return ret;
    }

    StringPiece container_ = "";
    StringPiece shared_name_ = "";
  };
  VarHandleOp(const ::tensorflow::Scope& scope, DataType dtype,
            PartialTensorShape shape);
  VarHandleOp(const ::tensorflow::Scope& scope, DataType dtype,
            PartialTensorShape shape, const VarHandleOp::Attrs& attrs);
  operator ::tensorflow::Output() const { return resource; }
  operator ::tensorflow::Input() const { return resource; }
  ::tensorflow::Node* node() const { return resource.node(); }

  static Attrs Container(StringPiece x) {
    return Attrs().Container(x);
  }
  static Attrs SharedName(StringPiece x) {
    return Attrs().SharedName(x);
  }

  ::tensorflow::Output resource;
};

/// Checks whether a resource handle-based variable has been initialized.
///
/// Arguments:
/// * scope: A Scope object
/// * resource: the input resource handle.
///
/// Returns:
/// * `Output`: a scalar boolean which is true if the variable has been
/// initialized.
class TF_CLASS VarIsInitializedOp {
 public:
  VarIsInitializedOp(const ::tensorflow::Scope& scope, ::tensorflow::Input
                   resource);
  operator ::tensorflow::Output() const { return is_initialized; }
  operator ::tensorflow::Input() const { return is_initialized; }
  ::tensorflow::Node* node() const { return is_initialized.node(); }

  ::tensorflow::Output is_initialized;
};

/// Returns the shape of the variable pointed to by `resource`.
///
/// This operation returns a 1-D integer tensor representing the shape of `input`.
/// 
/// For example:
/// 
/// ```
/// # 't' is [[[1, 1, 1], [2, 2, 2]], [[3, 3, 3], [4, 4, 4]]]
/// shape(t) ==> [2, 2, 3]
/// ```
///
/// Arguments:
/// * scope: A Scope object
///
/// Returns:
/// * `Output`: The output tensor.
class TF_CLASS VariableShape {
 public:
  /// Optional attribute setters for VariableShape
  struct Attrs {
    /// Defaults to DT_INT32
    Attrs OutType(DataType x) {
      Attrs ret = *this;
      ret.out_type_ = x;
      return ret;
    }

    DataType out_type_ = DT_INT32;
  };
  VariableShape(const ::tensorflow::Scope& scope, ::tensorflow::Input input);
  VariableShape(const ::tensorflow::Scope& scope, ::tensorflow::Input input,
              const VariableShape::Attrs& attrs);
  operator ::tensorflow::Output() const { return output; }
  operator ::tensorflow::Input() const { return output; }
  ::tensorflow::Node* node() const { return output.node(); }

  static Attrs OutType(DataType x) {
    return Attrs().OutType(x);
  }

  ::tensorflow::Output output;
};

/// @}

}  // namespace ops
}  // namespace tensorflow

#endif  // D__TF_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_RESOURCE_VARIABLE_OPS_H_
