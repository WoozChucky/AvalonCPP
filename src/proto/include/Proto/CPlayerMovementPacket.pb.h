// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CPlayerMovementPacket.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_CPlayerMovementPacket_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_CPlayerMovementPacket_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_CPlayerMovementPacket_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_CPlayerMovementPacket_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_CPlayerMovementPacket_2eproto;
namespace Avalon {
namespace Network {
namespace Packets {
namespace Movement {
class CPlayerMovementPacket;
struct CPlayerMovementPacketDefaultTypeInternal;
extern CPlayerMovementPacketDefaultTypeInternal _CPlayerMovementPacket_default_instance_;
}  // namespace Movement
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
PROTOBUF_NAMESPACE_OPEN
template<> ::Avalon::Network::Packets::Movement::CPlayerMovementPacket* Arena::CreateMaybeMessage<::Avalon::Network::Packets::Movement::CPlayerMovementPacket>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Avalon {
namespace Network {
namespace Packets {
namespace Movement {

// ===================================================================

class CPlayerMovementPacket final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Avalon.Network.Packets.Movement.CPlayerMovementPacket) */ {
 public:
  inline CPlayerMovementPacket() : CPlayerMovementPacket(nullptr) {}
  ~CPlayerMovementPacket() override;
  explicit PROTOBUF_CONSTEXPR CPlayerMovementPacket(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  CPlayerMovementPacket(const CPlayerMovementPacket& from);
  CPlayerMovementPacket(CPlayerMovementPacket&& from) noexcept
    : CPlayerMovementPacket() {
    *this = ::std::move(from);
  }

  inline CPlayerMovementPacket& operator=(const CPlayerMovementPacket& from) {
    CopyFrom(from);
    return *this;
  }
  inline CPlayerMovementPacket& operator=(CPlayerMovementPacket&& from) noexcept {
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
  static const CPlayerMovementPacket& default_instance() {
    return *internal_default_instance();
  }
  static inline const CPlayerMovementPacket* internal_default_instance() {
    return reinterpret_cast<const CPlayerMovementPacket*>(
               &_CPlayerMovementPacket_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(CPlayerMovementPacket& a, CPlayerMovementPacket& b) {
    a.Swap(&b);
  }
  inline void Swap(CPlayerMovementPacket* other) {
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
  void UnsafeArenaSwap(CPlayerMovementPacket* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  CPlayerMovementPacket* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<CPlayerMovementPacket>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const CPlayerMovementPacket& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const CPlayerMovementPacket& from) {
    CPlayerMovementPacket::MergeImpl(*this, from);
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
  void InternalSwap(CPlayerMovementPacket* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Avalon.Network.Packets.Movement.CPlayerMovementPacket";
  }
  protected:
  explicit CPlayerMovementPacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kAccountIdFieldNumber = 1,
    kCharacterIdFieldNumber = 2,
    kElapsedGameTimeFieldNumber = 3,
    kXFieldNumber = 4,
    kYFieldNumber = 5,
    kVelocityXFieldNumber = 6,
    kVelocityYFieldNumber = 7,
  };
  // int32 AccountId = 1;
  void clear_accountid();
  int32_t accountid() const;
  void set_accountid(int32_t value);
  private:
  int32_t _internal_accountid() const;
  void _internal_set_accountid(int32_t value);
  public:

  // int32 CharacterId = 2;
  void clear_characterid();
  int32_t characterid() const;
  void set_characterid(int32_t value);
  private:
  int32_t _internal_characterid() const;
  void _internal_set_characterid(int32_t value);
  public:

  // float ElapsedGameTime = 3;
  void clear_elapsedgametime();
  float elapsedgametime() const;
  void set_elapsedgametime(float value);
  private:
  float _internal_elapsedgametime() const;
  void _internal_set_elapsedgametime(float value);
  public:

  // float X = 4;
  void clear_x();
  float x() const;
  void set_x(float value);
  private:
  float _internal_x() const;
  void _internal_set_x(float value);
  public:

  // float Y = 5;
  void clear_y();
  float y() const;
  void set_y(float value);
  private:
  float _internal_y() const;
  void _internal_set_y(float value);
  public:

  // float VelocityX = 6;
  void clear_velocityx();
  float velocityx() const;
  void set_velocityx(float value);
  private:
  float _internal_velocityx() const;
  void _internal_set_velocityx(float value);
  public:

  // float VelocityY = 7;
  void clear_velocityy();
  float velocityy() const;
  void set_velocityy(float value);
  private:
  float _internal_velocityy() const;
  void _internal_set_velocityy(float value);
  public:

  // @@protoc_insertion_point(class_scope:Avalon.Network.Packets.Movement.CPlayerMovementPacket)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    int32_t accountid_;
    int32_t characterid_;
    float elapsedgametime_;
    float x_;
    float y_;
    float velocityx_;
    float velocityy_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_CPlayerMovementPacket_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CPlayerMovementPacket

// int32 AccountId = 1;
inline void CPlayerMovementPacket::clear_accountid() {
  _impl_.accountid_ = 0;
}
inline int32_t CPlayerMovementPacket::_internal_accountid() const {
  return _impl_.accountid_;
}
inline int32_t CPlayerMovementPacket::accountid() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Movement.CPlayerMovementPacket.AccountId)
  return _internal_accountid();
}
inline void CPlayerMovementPacket::_internal_set_accountid(int32_t value) {
  
  _impl_.accountid_ = value;
}
inline void CPlayerMovementPacket::set_accountid(int32_t value) {
  _internal_set_accountid(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Movement.CPlayerMovementPacket.AccountId)
}

// int32 CharacterId = 2;
inline void CPlayerMovementPacket::clear_characterid() {
  _impl_.characterid_ = 0;
}
inline int32_t CPlayerMovementPacket::_internal_characterid() const {
  return _impl_.characterid_;
}
inline int32_t CPlayerMovementPacket::characterid() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Movement.CPlayerMovementPacket.CharacterId)
  return _internal_characterid();
}
inline void CPlayerMovementPacket::_internal_set_characterid(int32_t value) {
  
  _impl_.characterid_ = value;
}
inline void CPlayerMovementPacket::set_characterid(int32_t value) {
  _internal_set_characterid(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Movement.CPlayerMovementPacket.CharacterId)
}

// float ElapsedGameTime = 3;
inline void CPlayerMovementPacket::clear_elapsedgametime() {
  _impl_.elapsedgametime_ = 0;
}
inline float CPlayerMovementPacket::_internal_elapsedgametime() const {
  return _impl_.elapsedgametime_;
}
inline float CPlayerMovementPacket::elapsedgametime() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Movement.CPlayerMovementPacket.ElapsedGameTime)
  return _internal_elapsedgametime();
}
inline void CPlayerMovementPacket::_internal_set_elapsedgametime(float value) {
  
  _impl_.elapsedgametime_ = value;
}
inline void CPlayerMovementPacket::set_elapsedgametime(float value) {
  _internal_set_elapsedgametime(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Movement.CPlayerMovementPacket.ElapsedGameTime)
}

// float X = 4;
inline void CPlayerMovementPacket::clear_x() {
  _impl_.x_ = 0;
}
inline float CPlayerMovementPacket::_internal_x() const {
  return _impl_.x_;
}
inline float CPlayerMovementPacket::x() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Movement.CPlayerMovementPacket.X)
  return _internal_x();
}
inline void CPlayerMovementPacket::_internal_set_x(float value) {
  
  _impl_.x_ = value;
}
inline void CPlayerMovementPacket::set_x(float value) {
  _internal_set_x(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Movement.CPlayerMovementPacket.X)
}

// float Y = 5;
inline void CPlayerMovementPacket::clear_y() {
  _impl_.y_ = 0;
}
inline float CPlayerMovementPacket::_internal_y() const {
  return _impl_.y_;
}
inline float CPlayerMovementPacket::y() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Movement.CPlayerMovementPacket.Y)
  return _internal_y();
}
inline void CPlayerMovementPacket::_internal_set_y(float value) {
  
  _impl_.y_ = value;
}
inline void CPlayerMovementPacket::set_y(float value) {
  _internal_set_y(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Movement.CPlayerMovementPacket.Y)
}

// float VelocityX = 6;
inline void CPlayerMovementPacket::clear_velocityx() {
  _impl_.velocityx_ = 0;
}
inline float CPlayerMovementPacket::_internal_velocityx() const {
  return _impl_.velocityx_;
}
inline float CPlayerMovementPacket::velocityx() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Movement.CPlayerMovementPacket.VelocityX)
  return _internal_velocityx();
}
inline void CPlayerMovementPacket::_internal_set_velocityx(float value) {
  
  _impl_.velocityx_ = value;
}
inline void CPlayerMovementPacket::set_velocityx(float value) {
  _internal_set_velocityx(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Movement.CPlayerMovementPacket.VelocityX)
}

// float VelocityY = 7;
inline void CPlayerMovementPacket::clear_velocityy() {
  _impl_.velocityy_ = 0;
}
inline float CPlayerMovementPacket::_internal_velocityy() const {
  return _impl_.velocityy_;
}
inline float CPlayerMovementPacket::velocityy() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Movement.CPlayerMovementPacket.VelocityY)
  return _internal_velocityy();
}
inline void CPlayerMovementPacket::_internal_set_velocityy(float value) {
  
  _impl_.velocityy_ = value;
}
inline void CPlayerMovementPacket::set_velocityy(float value) {
  _internal_set_velocityy(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Movement.CPlayerMovementPacket.VelocityY)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Movement
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_CPlayerMovementPacket_2eproto