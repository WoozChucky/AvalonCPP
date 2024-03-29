// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CCharacterDeletePacket.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_CCharacterDeletePacket_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_CCharacterDeletePacket_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_CCharacterDeletePacket_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_CCharacterDeletePacket_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_CCharacterDeletePacket_2eproto;
namespace Avalon {
namespace Network {
namespace Packets {
namespace Character {
class CCharacterDeletePacket;
struct CCharacterDeletePacketDefaultTypeInternal;
extern CCharacterDeletePacketDefaultTypeInternal _CCharacterDeletePacket_default_instance_;
}  // namespace Character
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
PROTOBUF_NAMESPACE_OPEN
template<> ::Avalon::Network::Packets::Character::CCharacterDeletePacket* Arena::CreateMaybeMessage<::Avalon::Network::Packets::Character::CCharacterDeletePacket>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Avalon {
namespace Network {
namespace Packets {
namespace Character {

// ===================================================================

class CCharacterDeletePacket final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Avalon.Network.Packets.Character.CCharacterDeletePacket) */ {
 public:
  inline CCharacterDeletePacket() : CCharacterDeletePacket(nullptr) {}
  ~CCharacterDeletePacket() override;
  explicit PROTOBUF_CONSTEXPR CCharacterDeletePacket(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  CCharacterDeletePacket(const CCharacterDeletePacket& from);
  CCharacterDeletePacket(CCharacterDeletePacket&& from) noexcept
    : CCharacterDeletePacket() {
    *this = ::std::move(from);
  }

  inline CCharacterDeletePacket& operator=(const CCharacterDeletePacket& from) {
    CopyFrom(from);
    return *this;
  }
  inline CCharacterDeletePacket& operator=(CCharacterDeletePacket&& from) noexcept {
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
  static const CCharacterDeletePacket& default_instance() {
    return *internal_default_instance();
  }
  static inline const CCharacterDeletePacket* internal_default_instance() {
    return reinterpret_cast<const CCharacterDeletePacket*>(
               &_CCharacterDeletePacket_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(CCharacterDeletePacket& a, CCharacterDeletePacket& b) {
    a.Swap(&b);
  }
  inline void Swap(CCharacterDeletePacket* other) {
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
  void UnsafeArenaSwap(CCharacterDeletePacket* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  CCharacterDeletePacket* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<CCharacterDeletePacket>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const CCharacterDeletePacket& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const CCharacterDeletePacket& from) {
    CCharacterDeletePacket::MergeImpl(*this, from);
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
  void InternalSwap(CCharacterDeletePacket* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Avalon.Network.Packets.Character.CCharacterDeletePacket";
  }
  protected:
  explicit CCharacterDeletePacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kCharacterIdFieldNumber = 1,
  };
  // int32 CharacterId = 1;
  void clear_characterid();
  int32_t characterid() const;
  void set_characterid(int32_t value);
  private:
  int32_t _internal_characterid() const;
  void _internal_set_characterid(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:Avalon.Network.Packets.Character.CCharacterDeletePacket)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    int32_t characterid_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_CCharacterDeletePacket_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CCharacterDeletePacket

// int32 CharacterId = 1;
inline void CCharacterDeletePacket::clear_characterid() {
  _impl_.characterid_ = 0;
}
inline int32_t CCharacterDeletePacket::_internal_characterid() const {
  return _impl_.characterid_;
}
inline int32_t CCharacterDeletePacket::characterid() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Character.CCharacterDeletePacket.CharacterId)
  return _internal_characterid();
}
inline void CCharacterDeletePacket::_internal_set_characterid(int32_t value) {
  
  _impl_.characterid_ = value;
}
inline void CCharacterDeletePacket::set_characterid(int32_t value) {
  _internal_set_characterid(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Character.CCharacterDeletePacket.CharacterId)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Character
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_CCharacterDeletePacket_2eproto
