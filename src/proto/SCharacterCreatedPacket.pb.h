// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SCharacterCreatedPacket.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_SCharacterCreatedPacket_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_SCharacterCreatedPacket_2eproto

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
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_SCharacterCreatedPacket_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_SCharacterCreatedPacket_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_SCharacterCreatedPacket_2eproto;
namespace Avalon {
namespace Network {
namespace Packets {
namespace Character {
class SCharacterCreatedPacket;
struct SCharacterCreatedPacketDefaultTypeInternal;
extern SCharacterCreatedPacketDefaultTypeInternal _SCharacterCreatedPacket_default_instance_;
}  // namespace Character
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
PROTOBUF_NAMESPACE_OPEN
template<> ::Avalon::Network::Packets::Character::SCharacterCreatedPacket* Arena::CreateMaybeMessage<::Avalon::Network::Packets::Character::SCharacterCreatedPacket>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Avalon {
namespace Network {
namespace Packets {
namespace Character {

enum SCharacterCreateResult : int {
  Ok = 0,
  NameAlreadyExists = 1,
  NameTooShort = 2,
  NameTooLong = 3,
  InvalidClass = 4,
  MaxCharactersReached = 5,
  AlreadyInGame = 6,
  InternalDatabaseError = 7,
  SCharacterCreateResult_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  SCharacterCreateResult_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool SCharacterCreateResult_IsValid(int value);
constexpr SCharacterCreateResult SCharacterCreateResult_MIN = Ok;
constexpr SCharacterCreateResult SCharacterCreateResult_MAX = InternalDatabaseError;
constexpr int SCharacterCreateResult_ARRAYSIZE = SCharacterCreateResult_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* SCharacterCreateResult_descriptor();
template<typename T>
inline const std::string& SCharacterCreateResult_Name(T enum_t_value) {
  static_assert(::std::is_same<T, SCharacterCreateResult>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function SCharacterCreateResult_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    SCharacterCreateResult_descriptor(), enum_t_value);
}
inline bool SCharacterCreateResult_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, SCharacterCreateResult* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<SCharacterCreateResult>(
    SCharacterCreateResult_descriptor(), name, value);
}
// ===================================================================

class SCharacterCreatedPacket final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Avalon.Network.Packets.Character.SCharacterCreatedPacket) */ {
 public:
  inline SCharacterCreatedPacket() : SCharacterCreatedPacket(nullptr) {}
  ~SCharacterCreatedPacket() override;
  explicit PROTOBUF_CONSTEXPR SCharacterCreatedPacket(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  SCharacterCreatedPacket(const SCharacterCreatedPacket& from);
  SCharacterCreatedPacket(SCharacterCreatedPacket&& from) noexcept
    : SCharacterCreatedPacket() {
    *this = ::std::move(from);
  }

  inline SCharacterCreatedPacket& operator=(const SCharacterCreatedPacket& from) {
    CopyFrom(from);
    return *this;
  }
  inline SCharacterCreatedPacket& operator=(SCharacterCreatedPacket&& from) noexcept {
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
  static const SCharacterCreatedPacket& default_instance() {
    return *internal_default_instance();
  }
  static inline const SCharacterCreatedPacket* internal_default_instance() {
    return reinterpret_cast<const SCharacterCreatedPacket*>(
               &_SCharacterCreatedPacket_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(SCharacterCreatedPacket& a, SCharacterCreatedPacket& b) {
    a.Swap(&b);
  }
  inline void Swap(SCharacterCreatedPacket* other) {
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
  void UnsafeArenaSwap(SCharacterCreatedPacket* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  SCharacterCreatedPacket* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<SCharacterCreatedPacket>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const SCharacterCreatedPacket& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const SCharacterCreatedPacket& from) {
    SCharacterCreatedPacket::MergeImpl(*this, from);
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
  void InternalSwap(SCharacterCreatedPacket* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Avalon.Network.Packets.Character.SCharacterCreatedPacket";
  }
  protected:
  explicit SCharacterCreatedPacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kAccountIdFieldNumber = 1,
    kResultFieldNumber = 2,
  };
  // int32 AccountId = 1;
  void clear_accountid();
  int32_t accountid() const;
  void set_accountid(int32_t value);
  private:
  int32_t _internal_accountid() const;
  void _internal_set_accountid(int32_t value);
  public:

  // .Avalon.Network.Packets.Character.SCharacterCreateResult Result = 2;
  void clear_result();
  ::Avalon::Network::Packets::Character::SCharacterCreateResult result() const;
  void set_result(::Avalon::Network::Packets::Character::SCharacterCreateResult value);
  private:
  ::Avalon::Network::Packets::Character::SCharacterCreateResult _internal_result() const;
  void _internal_set_result(::Avalon::Network::Packets::Character::SCharacterCreateResult value);
  public:

  // @@protoc_insertion_point(class_scope:Avalon.Network.Packets.Character.SCharacterCreatedPacket)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    int32_t accountid_;
    int result_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_SCharacterCreatedPacket_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// SCharacterCreatedPacket

// int32 AccountId = 1;
inline void SCharacterCreatedPacket::clear_accountid() {
  _impl_.accountid_ = 0;
}
inline int32_t SCharacterCreatedPacket::_internal_accountid() const {
  return _impl_.accountid_;
}
inline int32_t SCharacterCreatedPacket::accountid() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Character.SCharacterCreatedPacket.AccountId)
  return _internal_accountid();
}
inline void SCharacterCreatedPacket::_internal_set_accountid(int32_t value) {
  
  _impl_.accountid_ = value;
}
inline void SCharacterCreatedPacket::set_accountid(int32_t value) {
  _internal_set_accountid(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Character.SCharacterCreatedPacket.AccountId)
}

// .Avalon.Network.Packets.Character.SCharacterCreateResult Result = 2;
inline void SCharacterCreatedPacket::clear_result() {
  _impl_.result_ = 0;
}
inline ::Avalon::Network::Packets::Character::SCharacterCreateResult SCharacterCreatedPacket::_internal_result() const {
  return static_cast< ::Avalon::Network::Packets::Character::SCharacterCreateResult >(_impl_.result_);
}
inline ::Avalon::Network::Packets::Character::SCharacterCreateResult SCharacterCreatedPacket::result() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Character.SCharacterCreatedPacket.Result)
  return _internal_result();
}
inline void SCharacterCreatedPacket::_internal_set_result(::Avalon::Network::Packets::Character::SCharacterCreateResult value) {
  
  _impl_.result_ = value;
}
inline void SCharacterCreatedPacket::set_result(::Avalon::Network::Packets::Character::SCharacterCreateResult value) {
  _internal_set_result(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Character.SCharacterCreatedPacket.Result)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Character
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::Avalon::Network::Packets::Character::SCharacterCreateResult> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Avalon::Network::Packets::Character::SCharacterCreateResult>() {
  return ::Avalon::Network::Packets::Character::SCharacterCreateResult_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_SCharacterCreatedPacket_2eproto
