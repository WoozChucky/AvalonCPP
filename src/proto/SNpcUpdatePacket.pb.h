// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SNpcUpdatePacket.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_SNpcUpdatePacket_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_SNpcUpdatePacket_2eproto

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
#include "bcl.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_SNpcUpdatePacket_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_SNpcUpdatePacket_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_SNpcUpdatePacket_2eproto;
namespace Avalon {
namespace Network {
namespace Packets {
namespace Movement {
class CreaturePacket;
struct CreaturePacketDefaultTypeInternal;
extern CreaturePacketDefaultTypeInternal _CreaturePacket_default_instance_;
class SNpcUpdatePacket;
struct SNpcUpdatePacketDefaultTypeInternal;
extern SNpcUpdatePacketDefaultTypeInternal _SNpcUpdatePacket_default_instance_;
}  // namespace Movement
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
PROTOBUF_NAMESPACE_OPEN
template<> ::Avalon::Network::Packets::Movement::CreaturePacket* Arena::CreateMaybeMessage<::Avalon::Network::Packets::Movement::CreaturePacket>(Arena*);
template<> ::Avalon::Network::Packets::Movement::SNpcUpdatePacket* Arena::CreateMaybeMessage<::Avalon::Network::Packets::Movement::SNpcUpdatePacket>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Avalon {
namespace Network {
namespace Packets {
namespace Movement {

// ===================================================================

class CreaturePacket final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Avalon.Network.Packets.Movement.CreaturePacket) */ {
 public:
  inline CreaturePacket() : CreaturePacket(nullptr) {}
  ~CreaturePacket() override;
  explicit PROTOBUF_CONSTEXPR CreaturePacket(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  CreaturePacket(const CreaturePacket& from);
  CreaturePacket(CreaturePacket&& from) noexcept
    : CreaturePacket() {
    *this = ::std::move(from);
  }

  inline CreaturePacket& operator=(const CreaturePacket& from) {
    CopyFrom(from);
    return *this;
  }
  inline CreaturePacket& operator=(CreaturePacket&& from) noexcept {
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
  static const CreaturePacket& default_instance() {
    return *internal_default_instance();
  }
  static inline const CreaturePacket* internal_default_instance() {
    return reinterpret_cast<const CreaturePacket*>(
               &_CreaturePacket_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(CreaturePacket& a, CreaturePacket& b) {
    a.Swap(&b);
  }
  inline void Swap(CreaturePacket* other) {
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
  void UnsafeArenaSwap(CreaturePacket* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  CreaturePacket* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<CreaturePacket>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const CreaturePacket& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const CreaturePacket& from) {
    CreaturePacket::MergeImpl(*this, from);
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
  void InternalSwap(CreaturePacket* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Avalon.Network.Packets.Movement.CreaturePacket";
  }
  protected:
  explicit CreaturePacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNameFieldNumber = 2,
    kIdFieldNumber = 1,
    kPositionXFieldNumber = 3,
    kPositionYFieldNumber = 4,
    kVelocityXFieldNumber = 5,
    kVelocityYFieldNumber = 6,
  };
  // string Name = 2;
  void clear_name();
  const std::string& name() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_name(ArgT0&& arg0, ArgT... args);
  std::string* mutable_name();
  PROTOBUF_NODISCARD std::string* release_name();
  void set_allocated_name(std::string* name);
  private:
  const std::string& _internal_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_name(const std::string& value);
  std::string* _internal_mutable_name();
  public:

  // .bcl.Guid Id = 1;
  bool has_id() const;
  private:
  bool _internal_has_id() const;
  public:
  void clear_id();
  const ::bcl::Guid& id() const;
  PROTOBUF_NODISCARD ::bcl::Guid* release_id();
  ::bcl::Guid* mutable_id();
  void set_allocated_id(::bcl::Guid* id);
  private:
  const ::bcl::Guid& _internal_id() const;
  ::bcl::Guid* _internal_mutable_id();
  public:
  void unsafe_arena_set_allocated_id(
      ::bcl::Guid* id);
  ::bcl::Guid* unsafe_arena_release_id();

  // float PositionX = 3;
  void clear_positionx();
  float positionx() const;
  void set_positionx(float value);
  private:
  float _internal_positionx() const;
  void _internal_set_positionx(float value);
  public:

  // float PositionY = 4;
  void clear_positiony();
  float positiony() const;
  void set_positiony(float value);
  private:
  float _internal_positiony() const;
  void _internal_set_positiony(float value);
  public:

  // float VelocityX = 5;
  void clear_velocityx();
  float velocityx() const;
  void set_velocityx(float value);
  private:
  float _internal_velocityx() const;
  void _internal_set_velocityx(float value);
  public:

  // float VelocityY = 6;
  void clear_velocityy();
  float velocityy() const;
  void set_velocityy(float value);
  private:
  float _internal_velocityy() const;
  void _internal_set_velocityy(float value);
  public:

  // @@protoc_insertion_point(class_scope:Avalon.Network.Packets.Movement.CreaturePacket)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
    ::bcl::Guid* id_;
    float positionx_;
    float positiony_;
    float velocityx_;
    float velocityy_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_SNpcUpdatePacket_2eproto;
};
// -------------------------------------------------------------------

class SNpcUpdatePacket final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Avalon.Network.Packets.Movement.SNpcUpdatePacket) */ {
 public:
  inline SNpcUpdatePacket() : SNpcUpdatePacket(nullptr) {}
  ~SNpcUpdatePacket() override;
  explicit PROTOBUF_CONSTEXPR SNpcUpdatePacket(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  SNpcUpdatePacket(const SNpcUpdatePacket& from);
  SNpcUpdatePacket(SNpcUpdatePacket&& from) noexcept
    : SNpcUpdatePacket() {
    *this = ::std::move(from);
  }

  inline SNpcUpdatePacket& operator=(const SNpcUpdatePacket& from) {
    CopyFrom(from);
    return *this;
  }
  inline SNpcUpdatePacket& operator=(SNpcUpdatePacket&& from) noexcept {
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
  static const SNpcUpdatePacket& default_instance() {
    return *internal_default_instance();
  }
  static inline const SNpcUpdatePacket* internal_default_instance() {
    return reinterpret_cast<const SNpcUpdatePacket*>(
               &_SNpcUpdatePacket_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(SNpcUpdatePacket& a, SNpcUpdatePacket& b) {
    a.Swap(&b);
  }
  inline void Swap(SNpcUpdatePacket* other) {
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
  void UnsafeArenaSwap(SNpcUpdatePacket* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  SNpcUpdatePacket* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<SNpcUpdatePacket>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const SNpcUpdatePacket& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const SNpcUpdatePacket& from) {
    SNpcUpdatePacket::MergeImpl(*this, from);
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
  void InternalSwap(SNpcUpdatePacket* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Avalon.Network.Packets.Movement.SNpcUpdatePacket";
  }
  protected:
  explicit SNpcUpdatePacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kCreaturesFieldNumber = 1,
  };
  // repeated .Avalon.Network.Packets.Movement.CreaturePacket Creatures = 1;
  int creatures_size() const;
  private:
  int _internal_creatures_size() const;
  public:
  void clear_creatures();
  ::Avalon::Network::Packets::Movement::CreaturePacket* mutable_creatures(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Avalon::Network::Packets::Movement::CreaturePacket >*
      mutable_creatures();
  private:
  const ::Avalon::Network::Packets::Movement::CreaturePacket& _internal_creatures(int index) const;
  ::Avalon::Network::Packets::Movement::CreaturePacket* _internal_add_creatures();
  public:
  const ::Avalon::Network::Packets::Movement::CreaturePacket& creatures(int index) const;
  ::Avalon::Network::Packets::Movement::CreaturePacket* add_creatures();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Avalon::Network::Packets::Movement::CreaturePacket >&
      creatures() const;

  // @@protoc_insertion_point(class_scope:Avalon.Network.Packets.Movement.SNpcUpdatePacket)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Avalon::Network::Packets::Movement::CreaturePacket > creatures_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_SNpcUpdatePacket_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CreaturePacket

// .bcl.Guid Id = 1;
inline bool CreaturePacket::_internal_has_id() const {
  return this != internal_default_instance() && _impl_.id_ != nullptr;
}
inline bool CreaturePacket::has_id() const {
  return _internal_has_id();
}
inline const ::bcl::Guid& CreaturePacket::_internal_id() const {
  const ::bcl::Guid* p = _impl_.id_;
  return p != nullptr ? *p : reinterpret_cast<const ::bcl::Guid&>(
      ::bcl::_Guid_default_instance_);
}
inline const ::bcl::Guid& CreaturePacket::id() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Movement.CreaturePacket.Id)
  return _internal_id();
}
inline void CreaturePacket::unsafe_arena_set_allocated_id(
    ::bcl::Guid* id) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.id_);
  }
  _impl_.id_ = id;
  if (id) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:Avalon.Network.Packets.Movement.CreaturePacket.Id)
}
inline ::bcl::Guid* CreaturePacket::release_id() {
  
  ::bcl::Guid* temp = _impl_.id_;
  _impl_.id_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::bcl::Guid* CreaturePacket::unsafe_arena_release_id() {
  // @@protoc_insertion_point(field_release:Avalon.Network.Packets.Movement.CreaturePacket.Id)
  
  ::bcl::Guid* temp = _impl_.id_;
  _impl_.id_ = nullptr;
  return temp;
}
inline ::bcl::Guid* CreaturePacket::_internal_mutable_id() {
  
  if (_impl_.id_ == nullptr) {
    auto* p = CreateMaybeMessage<::bcl::Guid>(GetArenaForAllocation());
    _impl_.id_ = p;
  }
  return _impl_.id_;
}
inline ::bcl::Guid* CreaturePacket::mutable_id() {
  ::bcl::Guid* _msg = _internal_mutable_id();
  // @@protoc_insertion_point(field_mutable:Avalon.Network.Packets.Movement.CreaturePacket.Id)
  return _msg;
}
inline void CreaturePacket::set_allocated_id(::bcl::Guid* id) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.id_);
  }
  if (id) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalGetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(id));
    if (message_arena != submessage_arena) {
      id = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, id, submessage_arena);
    }
    
  } else {
    
  }
  _impl_.id_ = id;
  // @@protoc_insertion_point(field_set_allocated:Avalon.Network.Packets.Movement.CreaturePacket.Id)
}

// string Name = 2;
inline void CreaturePacket::clear_name() {
  _impl_.name_.ClearToEmpty();
}
inline const std::string& CreaturePacket::name() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Movement.CreaturePacket.Name)
  return _internal_name();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void CreaturePacket::set_name(ArgT0&& arg0, ArgT... args) {
 
 _impl_.name_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Movement.CreaturePacket.Name)
}
inline std::string* CreaturePacket::mutable_name() {
  std::string* _s = _internal_mutable_name();
  // @@protoc_insertion_point(field_mutable:Avalon.Network.Packets.Movement.CreaturePacket.Name)
  return _s;
}
inline const std::string& CreaturePacket::_internal_name() const {
  return _impl_.name_.Get();
}
inline void CreaturePacket::_internal_set_name(const std::string& value) {
  
  _impl_.name_.Set(value, GetArenaForAllocation());
}
inline std::string* CreaturePacket::_internal_mutable_name() {
  
  return _impl_.name_.Mutable(GetArenaForAllocation());
}
inline std::string* CreaturePacket::release_name() {
  // @@protoc_insertion_point(field_release:Avalon.Network.Packets.Movement.CreaturePacket.Name)
  return _impl_.name_.Release();
}
inline void CreaturePacket::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    
  } else {
    
  }
  _impl_.name_.SetAllocated(name, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.name_.IsDefault()) {
    _impl_.name_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Avalon.Network.Packets.Movement.CreaturePacket.Name)
}

// float PositionX = 3;
inline void CreaturePacket::clear_positionx() {
  _impl_.positionx_ = 0;
}
inline float CreaturePacket::_internal_positionx() const {
  return _impl_.positionx_;
}
inline float CreaturePacket::positionx() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Movement.CreaturePacket.PositionX)
  return _internal_positionx();
}
inline void CreaturePacket::_internal_set_positionx(float value) {
  
  _impl_.positionx_ = value;
}
inline void CreaturePacket::set_positionx(float value) {
  _internal_set_positionx(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Movement.CreaturePacket.PositionX)
}

// float PositionY = 4;
inline void CreaturePacket::clear_positiony() {
  _impl_.positiony_ = 0;
}
inline float CreaturePacket::_internal_positiony() const {
  return _impl_.positiony_;
}
inline float CreaturePacket::positiony() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Movement.CreaturePacket.PositionY)
  return _internal_positiony();
}
inline void CreaturePacket::_internal_set_positiony(float value) {
  
  _impl_.positiony_ = value;
}
inline void CreaturePacket::set_positiony(float value) {
  _internal_set_positiony(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Movement.CreaturePacket.PositionY)
}

// float VelocityX = 5;
inline void CreaturePacket::clear_velocityx() {
  _impl_.velocityx_ = 0;
}
inline float CreaturePacket::_internal_velocityx() const {
  return _impl_.velocityx_;
}
inline float CreaturePacket::velocityx() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Movement.CreaturePacket.VelocityX)
  return _internal_velocityx();
}
inline void CreaturePacket::_internal_set_velocityx(float value) {
  
  _impl_.velocityx_ = value;
}
inline void CreaturePacket::set_velocityx(float value) {
  _internal_set_velocityx(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Movement.CreaturePacket.VelocityX)
}

// float VelocityY = 6;
inline void CreaturePacket::clear_velocityy() {
  _impl_.velocityy_ = 0;
}
inline float CreaturePacket::_internal_velocityy() const {
  return _impl_.velocityy_;
}
inline float CreaturePacket::velocityy() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Movement.CreaturePacket.VelocityY)
  return _internal_velocityy();
}
inline void CreaturePacket::_internal_set_velocityy(float value) {
  
  _impl_.velocityy_ = value;
}
inline void CreaturePacket::set_velocityy(float value) {
  _internal_set_velocityy(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Movement.CreaturePacket.VelocityY)
}

// -------------------------------------------------------------------

// SNpcUpdatePacket

// repeated .Avalon.Network.Packets.Movement.CreaturePacket Creatures = 1;
inline int SNpcUpdatePacket::_internal_creatures_size() const {
  return _impl_.creatures_.size();
}
inline int SNpcUpdatePacket::creatures_size() const {
  return _internal_creatures_size();
}
inline void SNpcUpdatePacket::clear_creatures() {
  _impl_.creatures_.Clear();
}
inline ::Avalon::Network::Packets::Movement::CreaturePacket* SNpcUpdatePacket::mutable_creatures(int index) {
  // @@protoc_insertion_point(field_mutable:Avalon.Network.Packets.Movement.SNpcUpdatePacket.Creatures)
  return _impl_.creatures_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Avalon::Network::Packets::Movement::CreaturePacket >*
SNpcUpdatePacket::mutable_creatures() {
  // @@protoc_insertion_point(field_mutable_list:Avalon.Network.Packets.Movement.SNpcUpdatePacket.Creatures)
  return &_impl_.creatures_;
}
inline const ::Avalon::Network::Packets::Movement::CreaturePacket& SNpcUpdatePacket::_internal_creatures(int index) const {
  return _impl_.creatures_.Get(index);
}
inline const ::Avalon::Network::Packets::Movement::CreaturePacket& SNpcUpdatePacket::creatures(int index) const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Movement.SNpcUpdatePacket.Creatures)
  return _internal_creatures(index);
}
inline ::Avalon::Network::Packets::Movement::CreaturePacket* SNpcUpdatePacket::_internal_add_creatures() {
  return _impl_.creatures_.Add();
}
inline ::Avalon::Network::Packets::Movement::CreaturePacket* SNpcUpdatePacket::add_creatures() {
  ::Avalon::Network::Packets::Movement::CreaturePacket* _add = _internal_add_creatures();
  // @@protoc_insertion_point(field_add:Avalon.Network.Packets.Movement.SNpcUpdatePacket.Creatures)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Avalon::Network::Packets::Movement::CreaturePacket >&
SNpcUpdatePacket::creatures() const {
  // @@protoc_insertion_point(field_list:Avalon.Network.Packets.Movement.SNpcUpdatePacket.Creatures)
  return _impl_.creatures_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Movement
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_SNpcUpdatePacket_2eproto
