// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: saved_model.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_saved_5fmodel_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_saved_5fmodel_2eproto

#include <limits>
#include <string>

#include "protobuf/port_def.inc"
#if PROTOBUF_VERSION < 3009000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3009001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include "protobuf/port_undef.inc"
#include "protobuf/io/coded_stream.h"
#include "protobuf/arena.h"
#include "protobuf/arenastring.h"
#include "protobuf/generated_message_table_driven.h"
#include "protobuf/generated_message_util.h"
#include "protobuf/inlined_string_field.h"
#include "protobuf/metadata.h"
#include "protobuf/generated_message_reflection.h"
#include "protobuf/message.h"
#include "protobuf/repeated_field.h"  // IWYU pragma: export
#include "protobuf/extension_set.h"  // IWYU pragma: export
#include "protobuf/unknown_field_set.h"
#include "meta_graph.pb.h"
// @@protoc_insertion_point(includes)
#include "protobuf/port_def.inc"
#define PROTOBUF_INTERNAL_EXPORT_saved_5fmodel_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_saved_5fmodel_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_saved_5fmodel_2eproto;
namespace tensorflow {
class SavedModel;
class SavedModelDefaultTypeInternal;
extern SavedModelDefaultTypeInternal _SavedModel_default_instance_;
}  // namespace tensorflow
PROTOBUF_NAMESPACE_OPEN
template<> ::tensorflow::SavedModel* Arena::CreateMaybeMessage<::tensorflow::SavedModel>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace tensorflow {

// ===================================================================

class SavedModel :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:tensorflow.SavedModel) */ {
 public:
  SavedModel();
  virtual ~SavedModel();

  SavedModel(const SavedModel& from);
  SavedModel(SavedModel&& from) noexcept
    : SavedModel() {
    *this = ::std::move(from);
  }

  inline SavedModel& operator=(const SavedModel& from) {
    CopyFrom(from);
    return *this;
  }
  inline SavedModel& operator=(SavedModel&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArena() const final {
    return GetArenaNoVirtual();
  }
  inline void* GetMaybeArenaPointer() const final {
    return MaybeArenaPtr();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const SavedModel& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const SavedModel* internal_default_instance() {
    return reinterpret_cast<const SavedModel*>(
               &_SavedModel_default_instance_);
  }
  static const /*constexpr*/ int kIndexInFileMessages =
    0;

  friend void swap(SavedModel& a, SavedModel& b) {
    a.Swap(&b);
  }
  inline void Swap(SavedModel* other) {
    if (other == this) return;
    if (GetArenaNoVirtual() == other->GetArenaNoVirtual()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(SavedModel* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArenaNoVirtual() == other->GetArenaNoVirtual());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline SavedModel* New() const final {
    return CreateMaybeMessage<SavedModel>(nullptr);
  }

  SavedModel* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<SavedModel>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const SavedModel& from);
  void MergeFrom(const SavedModel& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SavedModel* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "tensorflow.SavedModel";
  }
  protected:
  explicit SavedModel(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_saved_5fmodel_2eproto);
    return ::descriptor_table_saved_5fmodel_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMetaGraphsFieldNumber = 2,
    kSavedModelSchemaVersionFieldNumber = 1,
  };
  // repeated .tensorflow.MetaGraphDef meta_graphs = 2;
  int meta_graphs_size() const;
  void clear_meta_graphs();
  ::tensorflow::MetaGraphDef* mutable_meta_graphs(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::tensorflow::MetaGraphDef >*
      mutable_meta_graphs();
  const ::tensorflow::MetaGraphDef& meta_graphs(int index) const;
  ::tensorflow::MetaGraphDef* add_meta_graphs();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::tensorflow::MetaGraphDef >&
      meta_graphs() const;

  // int64 saved_model_schema_version = 1;
  void clear_saved_model_schema_version();
  ::PROTOBUF_NAMESPACE_ID::int64 saved_model_schema_version() const;
  void set_saved_model_schema_version(::PROTOBUF_NAMESPACE_ID::int64 value);

  // @@protoc_insertion_point(class_scope:tensorflow.SavedModel)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::tensorflow::MetaGraphDef > meta_graphs_;
  ::PROTOBUF_NAMESPACE_ID::int64 saved_model_schema_version_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_saved_5fmodel_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// SavedModel

// int64 saved_model_schema_version = 1;
inline void SavedModel::clear_saved_model_schema_version() {
  saved_model_schema_version_ = PROTOBUF_LONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::int64 SavedModel::saved_model_schema_version() const {
  // @@protoc_insertion_point(field_get:tensorflow.SavedModel.saved_model_schema_version)
  return saved_model_schema_version_;
}
inline void SavedModel::set_saved_model_schema_version(::PROTOBUF_NAMESPACE_ID::int64 value) {
  
  saved_model_schema_version_ = value;
  // @@protoc_insertion_point(field_set:tensorflow.SavedModel.saved_model_schema_version)
}

// repeated .tensorflow.MetaGraphDef meta_graphs = 2;
inline int SavedModel::meta_graphs_size() const {
  return meta_graphs_.size();
}
inline ::tensorflow::MetaGraphDef* SavedModel::mutable_meta_graphs(int index) {
  // @@protoc_insertion_point(field_mutable:tensorflow.SavedModel.meta_graphs)
  return meta_graphs_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::tensorflow::MetaGraphDef >*
SavedModel::mutable_meta_graphs() {
  // @@protoc_insertion_point(field_mutable_list:tensorflow.SavedModel.meta_graphs)
  return &meta_graphs_;
}
inline const ::tensorflow::MetaGraphDef& SavedModel::meta_graphs(int index) const {
  // @@protoc_insertion_point(field_get:tensorflow.SavedModel.meta_graphs)
  return meta_graphs_.Get(index);
}
inline ::tensorflow::MetaGraphDef* SavedModel::add_meta_graphs() {
  // @@protoc_insertion_point(field_add:tensorflow.SavedModel.meta_graphs)
  return meta_graphs_.Add();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::tensorflow::MetaGraphDef >&
SavedModel::meta_graphs() const {
  // @@protoc_insertion_point(field_list:tensorflow.SavedModel.meta_graphs)
  return meta_graphs_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace tensorflow

// @@protoc_insertion_point(global_scope)

#include "protobuf/port_undef.inc"
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_saved_5fmodel_2eproto
