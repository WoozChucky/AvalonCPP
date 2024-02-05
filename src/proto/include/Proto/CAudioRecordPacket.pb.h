// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CAudioRecordPacket.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_CAudioRecordPacket_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_CAudioRecordPacket_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_CAudioRecordPacket_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_CAudioRecordPacket_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_CAudioRecordPacket_2eproto;
namespace Avalon {
namespace Network {
namespace Packets {
namespace Audio {
class CAudioRecordPacket;
struct CAudioRecordPacketDefaultTypeInternal;
extern CAudioRecordPacketDefaultTypeInternal _CAudioRecordPacket_default_instance_;
}  // namespace Audio
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
PROTOBUF_NAMESPACE_OPEN
template<> ::Avalon::Network::Packets::Audio::CAudioRecordPacket* Arena::CreateMaybeMessage<::Avalon::Network::Packets::Audio::CAudioRecordPacket>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Avalon {
namespace Network {
namespace Packets {
namespace Audio {

// ===================================================================

class CAudioRecordPacket final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Avalon.Network.Packets.Audio.CAudioRecordPacket) */ {
 public:
  inline CAudioRecordPacket() : CAudioRecordPacket(nullptr) {}
  ~CAudioRecordPacket() override;
  explicit PROTOBUF_CONSTEXPR CAudioRecordPacket(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  CAudioRecordPacket(const CAudioRecordPacket& from);
  CAudioRecordPacket(CAudioRecordPacket&& from) noexcept
    : CAudioRecordPacket() {
    *this = ::std::move(from);
  }

  inline CAudioRecordPacket& operator=(const CAudioRecordPacket& from) {
    CopyFrom(from);
    return *this;
  }
  inline CAudioRecordPacket& operator=(CAudioRecordPacket&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const CAudioRecordPacket& default_instance() {
    return *internal_default_instance();
  }
  static inline const CAudioRecordPacket* internal_default_instance() {
    return reinterpret_cast<const CAudioRecordPacket*>(
               &_CAudioRecordPacket_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(CAudioRecordPacket& a, CAudioRecordPacket& b) {
    a.Swap(&b);
  }
  inline void Swap(CAudioRecordPacket* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(CAudioRecordPacket* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  CAudioRecordPacket* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<CAudioRecordPacket>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const CAudioRecordPacket& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const CAudioRecordPacket& from) {
    CAudioRecordPacket::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(CAudioRecordPacket* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Avalon.Network.Packets.Audio.CAudioRecordPacket";
  }
  protected:
  explicit CAudioRecordPacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kSoundBufferFieldNumber = 1,
  };
  // bytes SoundBuffer = 1;
  void clear_soundbuffer();
  const std::string& soundbuffer() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_soundbuffer(ArgT0&& arg0, ArgT... args);
  std::string* mutable_soundbuffer();
  PROTOBUF_NODISCARD std::string* release_soundbuffer();
  void set_allocated_soundbuffer(std::string* soundbuffer);
  private:
  const std::string& _internal_soundbuffer() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_soundbuffer(const std::string& value);
  std::string* _internal_mutable_soundbuffer();
  public:

  // @@protoc_insertion_point(class_scope:Avalon.Network.Packets.Audio.CAudioRecordPacket)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr soundbuffer_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_CAudioRecordPacket_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CAudioRecordPacket

// bytes SoundBuffer = 1;
inline void CAudioRecordPacket::clear_soundbuffer() {
  _impl_.soundbuffer_.ClearToEmpty();
}
inline const std::string& CAudioRecordPacket::soundbuffer() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Audio.CAudioRecordPacket.SoundBuffer)
  return _internal_soundbuffer();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void CAudioRecordPacket::set_soundbuffer(ArgT0&& arg0, ArgT... args) {
 
 _impl_.soundbuffer_.SetBytes(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Audio.CAudioRecordPacket.SoundBuffer)
}
inline std::string* CAudioRecordPacket::mutable_soundbuffer() {
  std::string* _s = _internal_mutable_soundbuffer();
  // @@protoc_insertion_point(field_mutable:Avalon.Network.Packets.Audio.CAudioRecordPacket.SoundBuffer)
  return _s;
}
inline const std::string& CAudioRecordPacket::_internal_soundbuffer() const {
  return _impl_.soundbuffer_.Get();
}
inline void CAudioRecordPacket::_internal_set_soundbuffer(const std::string& value) {
  
  _impl_.soundbuffer_.Set(value, GetArenaForAllocation());
}
inline std::string* CAudioRecordPacket::_internal_mutable_soundbuffer() {
  
  return _impl_.soundbuffer_.Mutable(GetArenaForAllocation());
}
inline std::string* CAudioRecordPacket::release_soundbuffer() {
  // @@protoc_insertion_point(field_release:Avalon.Network.Packets.Audio.CAudioRecordPacket.SoundBuffer)
  return _impl_.soundbuffer_.Release();
}
inline void CAudioRecordPacket::set_allocated_soundbuffer(std::string* soundbuffer) {
  if (soundbuffer != nullptr) {
    
  } else {
    
  }
  _impl_.soundbuffer_.SetAllocated(soundbuffer, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.soundbuffer_.IsDefault()) {
    _impl_.soundbuffer_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Avalon.Network.Packets.Audio.CAudioRecordPacket.SoundBuffer)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Audio
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_CAudioRecordPacket_2eproto