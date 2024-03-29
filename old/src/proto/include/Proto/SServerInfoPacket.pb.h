// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SServerInfoPacket.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_SServerInfoPacket_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_SServerInfoPacket_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_SServerInfoPacket_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_SServerInfoPacket_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_SServerInfoPacket_2eproto;
namespace Avalon {
namespace Network {
namespace Packets {
namespace Handshake {
class SServerInfoPacket;
struct SServerInfoPacketDefaultTypeInternal;
extern SServerInfoPacketDefaultTypeInternal _SServerInfoPacket_default_instance_;
}  // namespace Handshake
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
PROTOBUF_NAMESPACE_OPEN
template<> ::Avalon::Network::Packets::Handshake::SServerInfoPacket* Arena::CreateMaybeMessage<::Avalon::Network::Packets::Handshake::SServerInfoPacket>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Avalon {
namespace Network {
namespace Packets {
namespace Handshake {

// ===================================================================

class SServerInfoPacket final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Avalon.Network.Packets.Handshake.SServerInfoPacket) */ {
 public:
  inline SServerInfoPacket() : SServerInfoPacket(nullptr) {}
  ~SServerInfoPacket() override;
  explicit PROTOBUF_CONSTEXPR SServerInfoPacket(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  SServerInfoPacket(const SServerInfoPacket& from);
  SServerInfoPacket(SServerInfoPacket&& from) noexcept
    : SServerInfoPacket() {
    *this = ::std::move(from);
  }

  inline SServerInfoPacket& operator=(const SServerInfoPacket& from) {
    CopyFrom(from);
    return *this;
  }
  inline SServerInfoPacket& operator=(SServerInfoPacket&& from) noexcept {
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
  static const SServerInfoPacket& default_instance() {
    return *internal_default_instance();
  }
  static inline const SServerInfoPacket* internal_default_instance() {
    return reinterpret_cast<const SServerInfoPacket*>(
               &_SServerInfoPacket_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(SServerInfoPacket& a, SServerInfoPacket& b) {
    a.Swap(&b);
  }
  inline void Swap(SServerInfoPacket* other) {
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
  void UnsafeArenaSwap(SServerInfoPacket* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  SServerInfoPacket* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<SServerInfoPacket>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const SServerInfoPacket& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const SServerInfoPacket& from) {
    SServerInfoPacket::MergeImpl(*this, from);
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
  void InternalSwap(SServerInfoPacket* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Avalon.Network.Packets.Handshake.SServerInfoPacket";
  }
  protected:
  explicit SServerInfoPacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kPublicKeyFieldNumber = 2,
    kServerVersionFieldNumber = 1,
  };
  // bytes PublicKey = 2;
  void clear_publickey();
  const std::string& publickey() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_publickey(ArgT0&& arg0, ArgT... args);
  std::string* mutable_publickey();
  PROTOBUF_NODISCARD std::string* release_publickey();
  void set_allocated_publickey(std::string* publickey);
  private:
  const std::string& _internal_publickey() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_publickey(const std::string& value);
  std::string* _internal_mutable_publickey();
  public:

  // int32 ServerVersion = 1;
  void clear_serverversion();
  int32_t serverversion() const;
  void set_serverversion(int32_t value);
  private:
  int32_t _internal_serverversion() const;
  void _internal_set_serverversion(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:Avalon.Network.Packets.Handshake.SServerInfoPacket)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr publickey_;
    int32_t serverversion_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_SServerInfoPacket_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// SServerInfoPacket

// int32 ServerVersion = 1;
inline void SServerInfoPacket::clear_serverversion() {
  _impl_.serverversion_ = 0;
}
inline int32_t SServerInfoPacket::_internal_serverversion() const {
  return _impl_.serverversion_;
}
inline int32_t SServerInfoPacket::serverversion() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Handshake.SServerInfoPacket.ServerVersion)
  return _internal_serverversion();
}
inline void SServerInfoPacket::_internal_set_serverversion(int32_t value) {
  
  _impl_.serverversion_ = value;
}
inline void SServerInfoPacket::set_serverversion(int32_t value) {
  _internal_set_serverversion(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Handshake.SServerInfoPacket.ServerVersion)
}

// bytes PublicKey = 2;
inline void SServerInfoPacket::clear_publickey() {
  _impl_.publickey_.ClearToEmpty();
}
inline const std::string& SServerInfoPacket::publickey() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Handshake.SServerInfoPacket.PublicKey)
  return _internal_publickey();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void SServerInfoPacket::set_publickey(ArgT0&& arg0, ArgT... args) {
 
 _impl_.publickey_.SetBytes(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Handshake.SServerInfoPacket.PublicKey)
}
inline std::string* SServerInfoPacket::mutable_publickey() {
  std::string* _s = _internal_mutable_publickey();
  // @@protoc_insertion_point(field_mutable:Avalon.Network.Packets.Handshake.SServerInfoPacket.PublicKey)
  return _s;
}
inline const std::string& SServerInfoPacket::_internal_publickey() const {
  return _impl_.publickey_.Get();
}
inline void SServerInfoPacket::_internal_set_publickey(const std::string& value) {
  
  _impl_.publickey_.Set(value, GetArenaForAllocation());
}
inline std::string* SServerInfoPacket::_internal_mutable_publickey() {
  
  return _impl_.publickey_.Mutable(GetArenaForAllocation());
}
inline std::string* SServerInfoPacket::release_publickey() {
  // @@protoc_insertion_point(field_release:Avalon.Network.Packets.Handshake.SServerInfoPacket.PublicKey)
  return _impl_.publickey_.Release();
}
inline void SServerInfoPacket::set_allocated_publickey(std::string* publickey) {
  if (publickey != nullptr) {
    
  } else {
    
  }
  _impl_.publickey_.SetAllocated(publickey, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.publickey_.IsDefault()) {
    _impl_.publickey_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Avalon.Network.Packets.Handshake.SServerInfoPacket.PublicKey)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Handshake
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_SServerInfoPacket_2eproto
