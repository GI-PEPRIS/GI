// This file is MACHINE GENERATED! Do not edit.

#ifndef D__TF_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_SUMMARY_OPS_H_
#define D__TF_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_SUMMARY_OPS_H_

// This file is MACHINE GENERATED! Do not edit.

#include "tensorflow/cc/framework/ops.h"
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/lib/gtl/array_slice.h"

namespace tensorflow {
namespace ops {

/// @defgroup summary_ops Summary Ops
/// @{

/// Flushes and closes the summary writer.
///
/// Also removes it from the resource manager. To reopen, use another
/// CreateSummaryFileWriter op.
///
/// Arguments:
/// * scope: A Scope object
/// * writer: A handle to the summary writer resource.
///
/// Returns:
/// * the created `Operation`
class CloseSummaryWriter {
 public:
  CloseSummaryWriter(const ::tensorflow::Scope& scope, ::tensorflow::Input
                   writer);
  operator ::tensorflow::Operation() const { return operation; }

  Operation operation;
};

/// Creates summary database writer accessible by given resource handle.
///
/// This can be used to write tensors from the execution graph directly
/// to a database. Only SQLite is supported right now. This function
/// will create the schema if it doesn't exist. Entries in the Users,
/// Experiments, and Runs tables will be created automatically if they
/// don't already exist.
///
/// Arguments:
/// * scope: A Scope object
/// * writer: Handle to SummaryWriter resource to overwrite.
/// * db_uri: For example "file:/tmp/foo.sqlite".
/// * experiment_name: Can't contain ASCII control characters or <>. Case
/// sensitive. If empty, then the Run will not be associated with any
/// Experiment.
/// * run_name: Can't contain ASCII control characters or <>. Case sensitive.
/// If empty, then each Tag will not be associated with any Run.
/// * user_name: Must be valid as both a DNS label and Linux username. If
/// empty, then the Experiment will not be associated with any User.
///
/// Returns:
/// * the created `Operation`
class CreateSummaryDbWriter {
 public:
  CreateSummaryDbWriter(const ::tensorflow::Scope& scope, ::tensorflow::Input
                      writer, ::tensorflow::Input db_uri, ::tensorflow::Input
                      experiment_name, ::tensorflow::Input run_name,
                      ::tensorflow::Input user_name);
  operator ::tensorflow::Operation() const { return operation; }

  Operation operation;
};

/// Creates a summary file writer accessible by the given resource handle.
///
/// Arguments:
/// * scope: A Scope object
/// * writer: A handle to the summary writer resource
/// * logdir: Directory where the event file will be written.
/// * max_queue: Size of the queue of pending events and summaries.
/// * flush_millis: How often, in milliseconds, to flush the pending events and
/// summaries to disk.
/// * filename_suffix: Every event file's name is suffixed with this suffix.
///
/// Returns:
/// * the created `Operation`
class CreateSummaryFileWriter {
 public:
  CreateSummaryFileWriter(const ::tensorflow::Scope& scope, ::tensorflow::Input
                        writer, ::tensorflow::Input logdir, ::tensorflow::Input
                        max_queue, ::tensorflow::Input flush_millis,
                        ::tensorflow::Input filename_suffix);
  operator ::tensorflow::Operation() const { return operation; }

  Operation operation;
};

/// Flushes the writer's unwritten events.
///
/// Arguments:
/// * scope: A Scope object
/// * writer: A handle to the summary writer resource.
///
/// Returns:
/// * the created `Operation`
class FlushSummaryWriter {
 public:
  FlushSummaryWriter(const ::tensorflow::Scope& scope, ::tensorflow::Input
                   writer);
  operator ::tensorflow::Operation() const { return operation; }

  Operation operation;
};

/// Outputs a `tf.Event` protocol buffer.
///
/// When CreateSummaryDbWriter is being used, this op can be useful for
/// importing data from event logs.
///
/// Arguments:
/// * scope: A Scope object
/// * writer: A handle to a summary writer.
/// * event: A string containing a binary-encoded tf.Event proto.
///
/// Returns:
/// * the created `Operation`
class ImportEvent {
 public:
  ImportEvent(const ::tensorflow::Scope& scope, ::tensorflow::Input writer,
            ::tensorflow::Input event);
  operator ::tensorflow::Operation() const { return operation; }

  Operation operation;
};

/// Returns a handle to be used to access a summary writer.
///
/// The summary writer is an in-graph resource which can be used by ops to write
/// summaries to event files.
///
/// Arguments:
/// * scope: A Scope object
///
/// Returns:
/// * `Output`: the summary writer resource. Scalar handle.
class SummaryWriter {
 public:
  /// Optional attribute setters for SummaryWriter
  struct Attrs {
    /// Defaults to ""
    Attrs SharedName(StringPiece x) {
      Attrs ret = *this;
      ret.shared_name_ = x;
      return ret;
    }

    /// Defaults to ""
    Attrs Container(StringPiece x) {
      Attrs ret = *this;
      ret.container_ = x;
      return ret;
    }

    StringPiece shared_name_ = "";
    StringPiece container_ = "";
  };
  SummaryWriter(const ::tensorflow::Scope& scope);
  SummaryWriter(const ::tensorflow::Scope& scope, const SummaryWriter::Attrs&
              attrs);
  operator ::tensorflow::Output() const { return writer; }
  operator ::tensorflow::Input() const { return writer; }
  ::tensorflow::Node* node() const { return writer.node(); }

  static Attrs SharedName(StringPiece x) {
    return Attrs().SharedName(x);
  }
  static Attrs Container(StringPiece x) {
    return Attrs().Container(x);
  }

  ::tensorflow::Output writer;
};

/// Writes a `Summary` protocol buffer with audio.
///
/// The summary has up to `max_outputs` summary values containing audio. The
/// audio is built from `tensor` which must be 3-D with shape `[batch_size,
/// frames, channels]` or 2-D with shape `[batch_size, frames]`. The values are
/// assumed to be in the range of `[-1.0, 1.0]` with a sample rate of `sample_rate`.
///
/// The `tag` argument is a scalar `Tensor` of type `string`.  It is used to
/// build the `tag` of the summary values:
///
/// *  If `max_outputs` is 1, the summary value tag is '*tag*/audio'.
/// *  If `max_outputs` is greater than 1, the summary value tags are
///    generated sequentially as '*tag*/audio/0', '*tag*/audio/1', etc.
///
/// Arguments:
/// * scope: A Scope object
/// * writer: A handle to a summary writer.
/// * step: The step to write the summary for.
/// * tag: Scalar. Used to build the `tag` attribute of the summary values.
/// * tensor: 2-D of shape `[batch_size, frames]`.
/// * sample_rate: The sample rate of the signal in hertz.
///
/// Optional attributes (see `Attrs`):
/// * max_outputs: Max number of batch elements to generate audio for.
///
/// Returns:
/// * the created `Operation`
class WriteAudioSummary {
 public:
  /// Optional attribute setters for WriteAudioSummary
  struct Attrs {
    /// Max number of batch elements to generate audio for.
    ///
    /// Defaults to 3
    Attrs MaxOutputs(int64 x) {
      Attrs ret = *this;
      ret.max_outputs_ = x;
      return ret;
    }

    int64 max_outputs_ = 3;
  };
  WriteAudioSummary(const ::tensorflow::Scope& scope, ::tensorflow::Input writer,
                  ::tensorflow::Input step, ::tensorflow::Input tag,
                  ::tensorflow::Input tensor, ::tensorflow::Input sample_rate);
  WriteAudioSummary(const ::tensorflow::Scope& scope, ::tensorflow::Input writer,
                  ::tensorflow::Input step, ::tensorflow::Input tag,
                  ::tensorflow::Input tensor, ::tensorflow::Input sample_rate,
                  const WriteAudioSummary::Attrs& attrs);
  operator ::tensorflow::Operation() const { return operation; }

  static Attrs MaxOutputs(int64 x) {
    return Attrs().MaxOutputs(x);
  }

  Operation operation;
};

/// Writes a `GraphDef` protocol buffer to a `SummaryWriter`.
///
/// Arguments:
/// * scope: A Scope object
/// * writer: Handle of `SummaryWriter`.
/// * step: The step to write the summary for.
/// * tensor: A scalar string of the serialized tf.GraphDef proto.
///
/// Returns:
/// * the created `Operation`
class WriteGraphSummary {
 public:
  WriteGraphSummary(const ::tensorflow::Scope& scope, ::tensorflow::Input writer,
                  ::tensorflow::Input step, ::tensorflow::Input tensor);
  operator ::tensorflow::Operation() const { return operation; }

  Operation operation;
};

/// Writes a `Summary` protocol buffer with a histogram.
///
/// The generated
/// [`Summary`](https://www.tensorflow.org/code/tensorflow/core/framework/summary.proto)
/// has one summary value containing a histogram for `values`.
///
/// This op reports an `InvalidArgument` error if any value is not finite.
///
/// Arguments:
/// * scope: A Scope object
/// * writer: A handle to a summary writer.
/// * step: The step to write the summary for.
/// * tag: Scalar.  Tag to use for the `Summary.Value`.
/// * values: Any shape. Values to use to build the histogram.
///
/// Returns:
/// * the created `Operation`
class WriteHistogramSummary {
 public:
  WriteHistogramSummary(const ::tensorflow::Scope& scope, ::tensorflow::Input
                      writer, ::tensorflow::Input step, ::tensorflow::Input
                      tag, ::tensorflow::Input values);
  operator ::tensorflow::Operation() const { return operation; }

  Operation operation;
};

/// Writes a `Summary` protocol buffer with images.
///
/// The summary has up to `max_images` summary values containing images. The
/// images are built from `tensor` which must be 4-D with shape `[batch_size,
/// height, width, channels]` and where `channels` can be:
///
/// *  1: `tensor` is interpreted as Grayscale.
/// *  3: `tensor` is interpreted as RGB.
/// *  4: `tensor` is interpreted as RGBA.
///
/// The images have the same number of channels as the input tensor. For float
/// input, the values are normalized one image at a time to fit in the range
/// `[0, 255]`.  `uint8` values are unchanged.  The op uses two different
/// normalization algorithms:
///
/// *  If the input values are all positive, they are rescaled so the largest one
///    is 255.
///
/// *  If any input value is negative, the values are shifted so input value 0.0
///    is at 127.  They are then rescaled so that either the smallest value is 0,
///    or the largest one is 255.
///
/// The `tag` argument is a scalar `Tensor` of type `string`.  It is used to
/// build the `tag` of the summary values:
///
/// *  If `max_images` is 1, the summary value tag is '*tag*/image'.
/// *  If `max_images` is greater than 1, the summary value tags are
///    generated sequentially as '*tag*/image/0', '*tag*/image/1', etc.
///
/// The `bad_color` argument is the color to use in the generated images for
/// non-finite input values.  It is a `unit8` 1-D tensor of length `channels`.
/// Each element must be in the range `[0, 255]` (It represents the value of a
/// pixel in the output image).  Non-finite values in the input tensor are
/// replaced by this tensor in the output image.  The default value is the color
/// red.
///
/// Arguments:
/// * scope: A Scope object
/// * writer: A handle to a summary writer.
/// * step: The step to write the summary for.
/// * tag: Scalar. Used to build the `tag` attribute of the summary values.
/// * tensor: 4-D of shape `[batch_size, height, width, channels]` where
/// `channels` is 1, 3, or 4.
/// * bad_color: Color to use for pixels with non-finite values.
///
/// Optional attributes (see `Attrs`):
/// * max_images: Max number of batch elements to generate images for.
///
/// Returns:
/// * the created `Operation`
class WriteImageSummary {
 public:
  /// Optional attribute setters for WriteImageSummary
  struct Attrs {
    /// Max number of batch elements to generate images for.
    ///
    /// Defaults to 3
    Attrs MaxImages(int64 x) {
      Attrs ret = *this;
      ret.max_images_ = x;
      return ret;
    }

    int64 max_images_ = 3;
  };
  WriteImageSummary(const ::tensorflow::Scope& scope, ::tensorflow::Input writer,
                  ::tensorflow::Input step, ::tensorflow::Input tag,
                  ::tensorflow::Input tensor, ::tensorflow::Input bad_color);
  WriteImageSummary(const ::tensorflow::Scope& scope, ::tensorflow::Input writer,
                  ::tensorflow::Input step, ::tensorflow::Input tag,
                  ::tensorflow::Input tensor, ::tensorflow::Input bad_color,
                  const WriteImageSummary::Attrs& attrs);
  operator ::tensorflow::Operation() const { return operation; }

  static Attrs MaxImages(int64 x) {
    return Attrs().MaxImages(x);
  }

  Operation operation;
};

/// Writes a `Summary` protocol buffer with scalar values.
///
/// The input `tag` and `value` must have the scalars.
///
/// Arguments:
/// * scope: A Scope object
/// * writer: A handle to a summary writer.
/// * step: The step to write the summary for.
/// * tag: Tag for the summary.
/// * value: Value for the summary.
///
/// Returns:
/// * the created `Operation`
class WriteScalarSummary {
 public:
  WriteScalarSummary(const ::tensorflow::Scope& scope, ::tensorflow::Input
                   writer, ::tensorflow::Input step, ::tensorflow::Input tag,
                   ::tensorflow::Input value);
  operator ::tensorflow::Operation() const { return operation; }

  Operation operation;
};

/// Outputs a `Summary` protocol buffer with a tensor.
///
/// Arguments:
/// * scope: A Scope object
/// * writer: A handle to a summary writer.
/// * step: The step to write the summary for.
/// * tensor: A tensor to serialize.
/// * tag: The summary's tag.
/// * summary_metadata: Serialized SummaryMetadata protocol buffer containing
/// plugin-related metadata for this summary.
///
/// Returns:
/// * the created `Operation`
class WriteSummary {
 public:
  WriteSummary(const ::tensorflow::Scope& scope, ::tensorflow::Input writer,
             ::tensorflow::Input step, ::tensorflow::Input tensor,
             ::tensorflow::Input tag, ::tensorflow::Input summary_metadata);
  operator ::tensorflow::Operation() const { return operation; }

  Operation operation;
};

/// @}

}  // namespace ops
}  // namespace tensorflow

#endif  // D__TF_TENSORFLOW_TENSORFLOW_CONTRIB_CMAKE_BUILD_TENSORFLOW_CC_OPS_SUMMARY_OPS_H_
