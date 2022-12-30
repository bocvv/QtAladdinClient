// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: wrapper_client.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_wrapper_5fclient_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_wrapper_5fclient_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3012000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3012004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_wrapper_5fclient_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_wrapper_5fclient_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_wrapper_5fclient_2eproto;
namespace mediapipe {
class StudyStatusNum;
class StudyStatusNumDefaultTypeInternal;
extern StudyStatusNumDefaultTypeInternal _StudyStatusNum_default_instance_;
class WrapperClient;
class WrapperClientDefaultTypeInternal;
extern WrapperClientDefaultTypeInternal _WrapperClient_default_instance_;
}  // namespace mediapipe
PROTOBUF_NAMESPACE_OPEN
template<> ::mediapipe::StudyStatusNum* Arena::CreateMaybeMessage<::mediapipe::StudyStatusNum>(Arena*);
template<> ::mediapipe::WrapperClient* Arena::CreateMaybeMessage<::mediapipe::WrapperClient>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace mediapipe {

// ===================================================================

class StudyStatusNum PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:mediapipe.StudyStatusNum) */ {
 public:
  inline StudyStatusNum() : StudyStatusNum(nullptr) {};
  virtual ~StudyStatusNum();

  StudyStatusNum(const StudyStatusNum& from);
  StudyStatusNum(StudyStatusNum&& from) noexcept
    : StudyStatusNum() {
    *this = ::std::move(from);
  }

  inline StudyStatusNum& operator=(const StudyStatusNum& from) {
    CopyFrom(from);
    return *this;
  }
  inline StudyStatusNum& operator=(StudyStatusNum&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
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
  static const StudyStatusNum& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const StudyStatusNum* internal_default_instance() {
    return reinterpret_cast<const StudyStatusNum*>(
               &_StudyStatusNum_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(StudyStatusNum& a, StudyStatusNum& b) {
    a.Swap(&b);
  }
  inline void Swap(StudyStatusNum* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(StudyStatusNum* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline StudyStatusNum* New() const final {
    return CreateMaybeMessage<StudyStatusNum>(nullptr);
  }

  StudyStatusNum* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<StudyStatusNum>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const StudyStatusNum& from);
  void MergeFrom(const StudyStatusNum& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(StudyStatusNum* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "mediapipe.StudyStatusNum";
  }
  protected:
  explicit StudyStatusNum(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_wrapper_5fclient_2eproto);
    return ::descriptor_table_wrapper_5fclient_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kPlayPhoneNumFieldNumber = 1,
    kLookLampNumFieldNumber = 2,
    kLookMonitorNumFieldNumber = 3,
    kLookBookNumFieldNumber = 4,
    kLookOtherNumFieldNumber = 5,
    kLookNoneNumFieldNumber = 6,
    kTotalFramesFieldNumber = 7,
  };
  // required int64 play_phone_num = 1;
  bool has_play_phone_num() const;
  private:
  bool _internal_has_play_phone_num() const;
  public:
  void clear_play_phone_num();
  ::PROTOBUF_NAMESPACE_ID::int64 play_phone_num() const;
  void set_play_phone_num(::PROTOBUF_NAMESPACE_ID::int64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int64 _internal_play_phone_num() const;
  void _internal_set_play_phone_num(::PROTOBUF_NAMESPACE_ID::int64 value);
  public:

  // required int64 look_lamp_num = 2;
  bool has_look_lamp_num() const;
  private:
  bool _internal_has_look_lamp_num() const;
  public:
  void clear_look_lamp_num();
  ::PROTOBUF_NAMESPACE_ID::int64 look_lamp_num() const;
  void set_look_lamp_num(::PROTOBUF_NAMESPACE_ID::int64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int64 _internal_look_lamp_num() const;
  void _internal_set_look_lamp_num(::PROTOBUF_NAMESPACE_ID::int64 value);
  public:

  // required int64 look_monitor_num = 3;
  bool has_look_monitor_num() const;
  private:
  bool _internal_has_look_monitor_num() const;
  public:
  void clear_look_monitor_num();
  ::PROTOBUF_NAMESPACE_ID::int64 look_monitor_num() const;
  void set_look_monitor_num(::PROTOBUF_NAMESPACE_ID::int64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int64 _internal_look_monitor_num() const;
  void _internal_set_look_monitor_num(::PROTOBUF_NAMESPACE_ID::int64 value);
  public:

  // required int64 look_book_num = 4;
  bool has_look_book_num() const;
  private:
  bool _internal_has_look_book_num() const;
  public:
  void clear_look_book_num();
  ::PROTOBUF_NAMESPACE_ID::int64 look_book_num() const;
  void set_look_book_num(::PROTOBUF_NAMESPACE_ID::int64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int64 _internal_look_book_num() const;
  void _internal_set_look_book_num(::PROTOBUF_NAMESPACE_ID::int64 value);
  public:

  // required int64 look_other_num = 5;
  bool has_look_other_num() const;
  private:
  bool _internal_has_look_other_num() const;
  public:
  void clear_look_other_num();
  ::PROTOBUF_NAMESPACE_ID::int64 look_other_num() const;
  void set_look_other_num(::PROTOBUF_NAMESPACE_ID::int64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int64 _internal_look_other_num() const;
  void _internal_set_look_other_num(::PROTOBUF_NAMESPACE_ID::int64 value);
  public:

  // required int64 look_none_num = 6;
  bool has_look_none_num() const;
  private:
  bool _internal_has_look_none_num() const;
  public:
  void clear_look_none_num();
  ::PROTOBUF_NAMESPACE_ID::int64 look_none_num() const;
  void set_look_none_num(::PROTOBUF_NAMESPACE_ID::int64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int64 _internal_look_none_num() const;
  void _internal_set_look_none_num(::PROTOBUF_NAMESPACE_ID::int64 value);
  public:

  // required int64 total_frames = 7;
  bool has_total_frames() const;
  private:
  bool _internal_has_total_frames() const;
  public:
  void clear_total_frames();
  ::PROTOBUF_NAMESPACE_ID::int64 total_frames() const;
  void set_total_frames(::PROTOBUF_NAMESPACE_ID::int64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int64 _internal_total_frames() const;
  void _internal_set_total_frames(::PROTOBUF_NAMESPACE_ID::int64 value);
  public:

  // @@protoc_insertion_point(class_scope:mediapipe.StudyStatusNum)
 private:
  class _Internal;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::int64 play_phone_num_;
  ::PROTOBUF_NAMESPACE_ID::int64 look_lamp_num_;
  ::PROTOBUF_NAMESPACE_ID::int64 look_monitor_num_;
  ::PROTOBUF_NAMESPACE_ID::int64 look_book_num_;
  ::PROTOBUF_NAMESPACE_ID::int64 look_other_num_;
  ::PROTOBUF_NAMESPACE_ID::int64 look_none_num_;
  ::PROTOBUF_NAMESPACE_ID::int64 total_frames_;
  friend struct ::TableStruct_wrapper_5fclient_2eproto;
};
// -------------------------------------------------------------------

class WrapperClient PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:mediapipe.WrapperClient) */ {
 public:
  inline WrapperClient() : WrapperClient(nullptr) {};
  virtual ~WrapperClient();

  WrapperClient(const WrapperClient& from);
  WrapperClient(WrapperClient&& from) noexcept
    : WrapperClient() {
    *this = ::std::move(from);
  }

  inline WrapperClient& operator=(const WrapperClient& from) {
    CopyFrom(from);
    return *this;
  }
  inline WrapperClient& operator=(WrapperClient&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
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
  static const WrapperClient& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const WrapperClient* internal_default_instance() {
    return reinterpret_cast<const WrapperClient*>(
               &_WrapperClient_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(WrapperClient& a, WrapperClient& b) {
    a.Swap(&b);
  }
  inline void Swap(WrapperClient* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(WrapperClient* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline WrapperClient* New() const final {
    return CreateMaybeMessage<WrapperClient>(nullptr);
  }

  WrapperClient* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<WrapperClient>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const WrapperClient& from);
  void MergeFrom(const WrapperClient& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(WrapperClient* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "mediapipe.WrapperClient";
  }
  protected:
  explicit WrapperClient(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_wrapper_5fclient_2eproto);
    return ::descriptor_table_wrapper_5fclient_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kStudyStatusNumFieldNumber = 4,
    kBadPoseFieldNumber = 1,
    kLowAttentionFieldNumber = 2,
    kUsePhoneFieldNumber = 3,
  };
  // required .mediapipe.StudyStatusNum study_status_num = 4;
  bool has_study_status_num() const;
  private:
  bool _internal_has_study_status_num() const;
  public:
  void clear_study_status_num();
  const ::mediapipe::StudyStatusNum& study_status_num() const;
  ::mediapipe::StudyStatusNum* release_study_status_num();
  ::mediapipe::StudyStatusNum* mutable_study_status_num();
  void set_allocated_study_status_num(::mediapipe::StudyStatusNum* study_status_num);
  private:
  const ::mediapipe::StudyStatusNum& _internal_study_status_num() const;
  ::mediapipe::StudyStatusNum* _internal_mutable_study_status_num();
  public:
  void unsafe_arena_set_allocated_study_status_num(
      ::mediapipe::StudyStatusNum* study_status_num);
  ::mediapipe::StudyStatusNum* unsafe_arena_release_study_status_num();

  // optional bool bad_pose = 1;
  bool has_bad_pose() const;
  private:
  bool _internal_has_bad_pose() const;
  public:
  void clear_bad_pose();
  bool bad_pose() const;
  void set_bad_pose(bool value);
  private:
  bool _internal_bad_pose() const;
  void _internal_set_bad_pose(bool value);
  public:

  // optional bool low_attention = 2;
  bool has_low_attention() const;
  private:
  bool _internal_has_low_attention() const;
  public:
  void clear_low_attention();
  bool low_attention() const;
  void set_low_attention(bool value);
  private:
  bool _internal_low_attention() const;
  void _internal_set_low_attention(bool value);
  public:

  // optional bool use_phone = 3;
  bool has_use_phone() const;
  private:
  bool _internal_has_use_phone() const;
  public:
  void clear_use_phone();
  bool use_phone() const;
  void set_use_phone(bool value);
  private:
  bool _internal_use_phone() const;
  void _internal_set_use_phone(bool value);
  public:

  // @@protoc_insertion_point(class_scope:mediapipe.WrapperClient)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::mediapipe::StudyStatusNum* study_status_num_;
  bool bad_pose_;
  bool low_attention_;
  bool use_phone_;
  friend struct ::TableStruct_wrapper_5fclient_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// StudyStatusNum

// required int64 play_phone_num = 1;
inline bool StudyStatusNum::_internal_has_play_phone_num() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool StudyStatusNum::has_play_phone_num() const {
  return _internal_has_play_phone_num();
}
inline void StudyStatusNum::clear_play_phone_num() {
  play_phone_num_ = PROTOBUF_LONGLONG(0);
  _has_bits_[0] &= ~0x00000001u;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 StudyStatusNum::_internal_play_phone_num() const {
  return play_phone_num_;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 StudyStatusNum::play_phone_num() const {
  // @@protoc_insertion_point(field_get:mediapipe.StudyStatusNum.play_phone_num)
  return _internal_play_phone_num();
}
inline void StudyStatusNum::_internal_set_play_phone_num(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _has_bits_[0] |= 0x00000001u;
  play_phone_num_ = value;
}
inline void StudyStatusNum::set_play_phone_num(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _internal_set_play_phone_num(value);
  // @@protoc_insertion_point(field_set:mediapipe.StudyStatusNum.play_phone_num)
}

// required int64 look_lamp_num = 2;
inline bool StudyStatusNum::_internal_has_look_lamp_num() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool StudyStatusNum::has_look_lamp_num() const {
  return _internal_has_look_lamp_num();
}
inline void StudyStatusNum::clear_look_lamp_num() {
  look_lamp_num_ = PROTOBUF_LONGLONG(0);
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 StudyStatusNum::_internal_look_lamp_num() const {
  return look_lamp_num_;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 StudyStatusNum::look_lamp_num() const {
  // @@protoc_insertion_point(field_get:mediapipe.StudyStatusNum.look_lamp_num)
  return _internal_look_lamp_num();
}
inline void StudyStatusNum::_internal_set_look_lamp_num(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _has_bits_[0] |= 0x00000002u;
  look_lamp_num_ = value;
}
inline void StudyStatusNum::set_look_lamp_num(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _internal_set_look_lamp_num(value);
  // @@protoc_insertion_point(field_set:mediapipe.StudyStatusNum.look_lamp_num)
}

// required int64 look_monitor_num = 3;
inline bool StudyStatusNum::_internal_has_look_monitor_num() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool StudyStatusNum::has_look_monitor_num() const {
  return _internal_has_look_monitor_num();
}
inline void StudyStatusNum::clear_look_monitor_num() {
  look_monitor_num_ = PROTOBUF_LONGLONG(0);
  _has_bits_[0] &= ~0x00000004u;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 StudyStatusNum::_internal_look_monitor_num() const {
  return look_monitor_num_;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 StudyStatusNum::look_monitor_num() const {
  // @@protoc_insertion_point(field_get:mediapipe.StudyStatusNum.look_monitor_num)
  return _internal_look_monitor_num();
}
inline void StudyStatusNum::_internal_set_look_monitor_num(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _has_bits_[0] |= 0x00000004u;
  look_monitor_num_ = value;
}
inline void StudyStatusNum::set_look_monitor_num(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _internal_set_look_monitor_num(value);
  // @@protoc_insertion_point(field_set:mediapipe.StudyStatusNum.look_monitor_num)
}

// required int64 look_book_num = 4;
inline bool StudyStatusNum::_internal_has_look_book_num() const {
  bool value = (_has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline bool StudyStatusNum::has_look_book_num() const {
  return _internal_has_look_book_num();
}
inline void StudyStatusNum::clear_look_book_num() {
  look_book_num_ = PROTOBUF_LONGLONG(0);
  _has_bits_[0] &= ~0x00000008u;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 StudyStatusNum::_internal_look_book_num() const {
  return look_book_num_;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 StudyStatusNum::look_book_num() const {
  // @@protoc_insertion_point(field_get:mediapipe.StudyStatusNum.look_book_num)
  return _internal_look_book_num();
}
inline void StudyStatusNum::_internal_set_look_book_num(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _has_bits_[0] |= 0x00000008u;
  look_book_num_ = value;
}
inline void StudyStatusNum::set_look_book_num(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _internal_set_look_book_num(value);
  // @@protoc_insertion_point(field_set:mediapipe.StudyStatusNum.look_book_num)
}

// required int64 look_other_num = 5;
inline bool StudyStatusNum::_internal_has_look_other_num() const {
  bool value = (_has_bits_[0] & 0x00000010u) != 0;
  return value;
}
inline bool StudyStatusNum::has_look_other_num() const {
  return _internal_has_look_other_num();
}
inline void StudyStatusNum::clear_look_other_num() {
  look_other_num_ = PROTOBUF_LONGLONG(0);
  _has_bits_[0] &= ~0x00000010u;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 StudyStatusNum::_internal_look_other_num() const {
  return look_other_num_;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 StudyStatusNum::look_other_num() const {
  // @@protoc_insertion_point(field_get:mediapipe.StudyStatusNum.look_other_num)
  return _internal_look_other_num();
}
inline void StudyStatusNum::_internal_set_look_other_num(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _has_bits_[0] |= 0x00000010u;
  look_other_num_ = value;
}
inline void StudyStatusNum::set_look_other_num(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _internal_set_look_other_num(value);
  // @@protoc_insertion_point(field_set:mediapipe.StudyStatusNum.look_other_num)
}

// required int64 look_none_num = 6;
inline bool StudyStatusNum::_internal_has_look_none_num() const {
  bool value = (_has_bits_[0] & 0x00000020u) != 0;
  return value;
}
inline bool StudyStatusNum::has_look_none_num() const {
  return _internal_has_look_none_num();
}
inline void StudyStatusNum::clear_look_none_num() {
  look_none_num_ = PROTOBUF_LONGLONG(0);
  _has_bits_[0] &= ~0x00000020u;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 StudyStatusNum::_internal_look_none_num() const {
  return look_none_num_;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 StudyStatusNum::look_none_num() const {
  // @@protoc_insertion_point(field_get:mediapipe.StudyStatusNum.look_none_num)
  return _internal_look_none_num();
}
inline void StudyStatusNum::_internal_set_look_none_num(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _has_bits_[0] |= 0x00000020u;
  look_none_num_ = value;
}
inline void StudyStatusNum::set_look_none_num(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _internal_set_look_none_num(value);
  // @@protoc_insertion_point(field_set:mediapipe.StudyStatusNum.look_none_num)
}

// required int64 total_frames = 7;
inline bool StudyStatusNum::_internal_has_total_frames() const {
  bool value = (_has_bits_[0] & 0x00000040u) != 0;
  return value;
}
inline bool StudyStatusNum::has_total_frames() const {
  return _internal_has_total_frames();
}
inline void StudyStatusNum::clear_total_frames() {
  total_frames_ = PROTOBUF_LONGLONG(0);
  _has_bits_[0] &= ~0x00000040u;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 StudyStatusNum::_internal_total_frames() const {
  return total_frames_;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 StudyStatusNum::total_frames() const {
  // @@protoc_insertion_point(field_get:mediapipe.StudyStatusNum.total_frames)
  return _internal_total_frames();
}
inline void StudyStatusNum::_internal_set_total_frames(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _has_bits_[0] |= 0x00000040u;
  total_frames_ = value;
}
inline void StudyStatusNum::set_total_frames(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _internal_set_total_frames(value);
  // @@protoc_insertion_point(field_set:mediapipe.StudyStatusNum.total_frames)
}

// -------------------------------------------------------------------

// WrapperClient

// optional bool bad_pose = 1;
inline bool WrapperClient::_internal_has_bad_pose() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool WrapperClient::has_bad_pose() const {
  return _internal_has_bad_pose();
}
inline void WrapperClient::clear_bad_pose() {
  bad_pose_ = false;
  _has_bits_[0] &= ~0x00000002u;
}
inline bool WrapperClient::_internal_bad_pose() const {
  return bad_pose_;
}
inline bool WrapperClient::bad_pose() const {
  // @@protoc_insertion_point(field_get:mediapipe.WrapperClient.bad_pose)
  return _internal_bad_pose();
}
inline void WrapperClient::_internal_set_bad_pose(bool value) {
  _has_bits_[0] |= 0x00000002u;
  bad_pose_ = value;
}
inline void WrapperClient::set_bad_pose(bool value) {
  _internal_set_bad_pose(value);
  // @@protoc_insertion_point(field_set:mediapipe.WrapperClient.bad_pose)
}

// optional bool low_attention = 2;
inline bool WrapperClient::_internal_has_low_attention() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool WrapperClient::has_low_attention() const {
  return _internal_has_low_attention();
}
inline void WrapperClient::clear_low_attention() {
  low_attention_ = false;
  _has_bits_[0] &= ~0x00000004u;
}
inline bool WrapperClient::_internal_low_attention() const {
  return low_attention_;
}
inline bool WrapperClient::low_attention() const {
  // @@protoc_insertion_point(field_get:mediapipe.WrapperClient.low_attention)
  return _internal_low_attention();
}
inline void WrapperClient::_internal_set_low_attention(bool value) {
  _has_bits_[0] |= 0x00000004u;
  low_attention_ = value;
}
inline void WrapperClient::set_low_attention(bool value) {
  _internal_set_low_attention(value);
  // @@protoc_insertion_point(field_set:mediapipe.WrapperClient.low_attention)
}

// optional bool use_phone = 3;
inline bool WrapperClient::_internal_has_use_phone() const {
  bool value = (_has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline bool WrapperClient::has_use_phone() const {
  return _internal_has_use_phone();
}
inline void WrapperClient::clear_use_phone() {
  use_phone_ = false;
  _has_bits_[0] &= ~0x00000008u;
}
inline bool WrapperClient::_internal_use_phone() const {
  return use_phone_;
}
inline bool WrapperClient::use_phone() const {
  // @@protoc_insertion_point(field_get:mediapipe.WrapperClient.use_phone)
  return _internal_use_phone();
}
inline void WrapperClient::_internal_set_use_phone(bool value) {
  _has_bits_[0] |= 0x00000008u;
  use_phone_ = value;
}
inline void WrapperClient::set_use_phone(bool value) {
  _internal_set_use_phone(value);
  // @@protoc_insertion_point(field_set:mediapipe.WrapperClient.use_phone)
}

// required .mediapipe.StudyStatusNum study_status_num = 4;
inline bool WrapperClient::_internal_has_study_status_num() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  PROTOBUF_ASSUME(!value || study_status_num_ != nullptr);
  return value;
}
inline bool WrapperClient::has_study_status_num() const {
  return _internal_has_study_status_num();
}
inline void WrapperClient::clear_study_status_num() {
  if (study_status_num_ != nullptr) study_status_num_->Clear();
  _has_bits_[0] &= ~0x00000001u;
}
inline const ::mediapipe::StudyStatusNum& WrapperClient::_internal_study_status_num() const {
  const ::mediapipe::StudyStatusNum* p = study_status_num_;
  return p != nullptr ? *p : *reinterpret_cast<const ::mediapipe::StudyStatusNum*>(
      &::mediapipe::_StudyStatusNum_default_instance_);
}
inline const ::mediapipe::StudyStatusNum& WrapperClient::study_status_num() const {
  // @@protoc_insertion_point(field_get:mediapipe.WrapperClient.study_status_num)
  return _internal_study_status_num();
}
inline void WrapperClient::unsafe_arena_set_allocated_study_status_num(
    ::mediapipe::StudyStatusNum* study_status_num) {
  if (GetArena() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(study_status_num_);
  }
  study_status_num_ = study_status_num;
  if (study_status_num) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:mediapipe.WrapperClient.study_status_num)
}
inline ::mediapipe::StudyStatusNum* WrapperClient::release_study_status_num() {
  auto temp = unsafe_arena_release_study_status_num();
  if (GetArena() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
  return temp;
}
inline ::mediapipe::StudyStatusNum* WrapperClient::unsafe_arena_release_study_status_num() {
  // @@protoc_insertion_point(field_release:mediapipe.WrapperClient.study_status_num)
  _has_bits_[0] &= ~0x00000001u;
  ::mediapipe::StudyStatusNum* temp = study_status_num_;
  study_status_num_ = nullptr;
  return temp;
}
inline ::mediapipe::StudyStatusNum* WrapperClient::_internal_mutable_study_status_num() {
  _has_bits_[0] |= 0x00000001u;
  if (study_status_num_ == nullptr) {
    auto* p = CreateMaybeMessage<::mediapipe::StudyStatusNum>(GetArena());
    study_status_num_ = p;
  }
  return study_status_num_;
}
inline ::mediapipe::StudyStatusNum* WrapperClient::mutable_study_status_num() {
  // @@protoc_insertion_point(field_mutable:mediapipe.WrapperClient.study_status_num)
  return _internal_mutable_study_status_num();
}
inline void WrapperClient::set_allocated_study_status_num(::mediapipe::StudyStatusNum* study_status_num) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArena();
  if (message_arena == nullptr) {
    delete study_status_num_;
  }
  if (study_status_num) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      ::PROTOBUF_NAMESPACE_ID::Arena::GetArena(study_status_num);
    if (message_arena != submessage_arena) {
      study_status_num = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, study_status_num, submessage_arena);
    }
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  study_status_num_ = study_status_num;
  // @@protoc_insertion_point(field_set_allocated:mediapipe.WrapperClient.study_status_num)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace mediapipe

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_wrapper_5fclient_2eproto
