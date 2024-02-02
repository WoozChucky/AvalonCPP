// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SChatMessagePacket.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_SChatMessagePacket_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_SChatMessagePacket_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_SChatMessagePacket_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_SChatMessagePacket_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_SChatMessagePacket_2eproto;
namespace Avalon {
namespace Network {
namespace Packets {
namespace Social {
class SChatMessagePacket;
struct SChatMessagePacketDefaultTypeInternal;
extern SChatMessagePacketDefaultTypeInternal _SChatMessagePacket_default_instance_;
}  // namespace Social
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
PROTOBUF_NAMESPACE_OPEN
template<> ::Avalon::Network::Packets::Social::SChatMessagePacket* Arena::CreateMaybeMessage<::Avalon::Network::Packets::Social::SChatMessagePacket>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Avalon {
namespace Network {
namespace Packets {
namespace Social {

// ===================================================================

class SChatMessagePacket final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Avalon.Network.Packets.Social.SChatMessagePacket) */ {
 public:
  inline SChatMessagePacket() : SChatMessagePacket(nullptr) {}
  ~SChatMessagePacket() override;
  explicit PROTOBUF_CONSTEXPR SChatMessagePacket(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  SChatMessagePacket(const SChatMessagePacket& from);
  SChatMessagePacket(SChatMessagePacket&& from) noexcept
    : SChatMessagePacket() {
    *this = ::std::move(from);
  }

  inline SChatMessagePacket& operator=(const SChatMessagePacket& from) {
    CopyFrom(from);
    return *this;
  }
  inline SChatMessagePacket& operator=(SChatMessagePacket&& from) noexcept {
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
  static const SChatMessagePacket& default_instance() {
    return *internal_default_instance();
  }
  static inline const SChatMessagePacket* internal_default_instance() {
    return reinterpret_cast<const SChatMessagePacket*>(
               &_SChatMessagePacket_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(SChatMessagePacket& a, SChatMessagePacket& b) {
    a.Swap(&b);
  }
  inline void Swap(SChatMessagePacket* other) {
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
  void UnsafeArenaSwap(SChatMessagePacket* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  SChatMessagePacket* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<SChatMessagePacket>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const SChatMessagePacket& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const SChatMessagePacket& from) {
    SChatMessagePacket::MergeImpl(*this, from);
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
  void InternalSwap(SChatMessagePacket* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Avalon.Network.Packets.Social.SChatMessagePacket";
  }
  protected:
  explicit SChatMessagePacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kCharacterNameFieldNumber = 3,
    kMessageFieldNumber = 4,
    kDateTimeFieldNumber = 5,
    kAccountIdFieldNumber = 1,
    kCharacterIdFieldNumber = 2,
  };
  // string CharacterName = 3;
  void clear_charactername();
  const std::string& charactername() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_charactername(ArgT0&& arg0, ArgT... args);
  std::string* mutable_charactername();
  PROTOBUF_NODISCARD std::string* release_charactername();
  void set_allocated_charactername(std::string* charactername);
  private:
  const std::string& _internal_charactername() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_charactername(const std::string& value);
  std::string* _internal_mutable_charactername();
  public:

  // string Message = 4;
  void clear_message();
  const std::string& message() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_message(ArgT0&& arg0, ArgT... args);
  std::string* mutable_message();
  PROTOBUF_NODISCARD std::string* release_message();
  void set_allocated_message(std::string* message);
  private:
  const std::string& _internal_message() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_message(const std::string& value);
  std::string* _internal_mutable_message();
  public:

  // .bcl.DateTime DateTime = 5;
  bool has_datetime() const;
  private:
  bool _internal_has_datetime() const;
  public:
  void clear_datetime();
  const ::bcl::DateTime& datetime() const;
  PROTOBUF_NODISCARD ::bcl::DateTime* release_datetime();
  ::bcl::DateTime* mutable_datetime();
  void set_allocated_datetime(::bcl::DateTime* datetime);
  private:
  const ::bcl::DateTime& _internal_datetime() const;
  ::bcl::DateTime* _internal_mutable_datetime();
  public:
  void unsafe_arena_set_allocated_datetime(
      ::bcl::DateTime* datetime);
  ::bcl::DateTime* unsafe_arena_release_datetime();

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

  // @@protoc_insertion_point(class_scope:Avalon.Network.Packets.Social.SChatMessagePacket)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr charactername_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr message_;
    ::bcl::DateTime* datetime_;
    int32_t accountid_;
    int32_t characterid_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_SChatMessagePacket_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// SChatMessagePacket

// int32 AccountId = 1;
inline void SChatMessagePacket::clear_accountid() {
  _impl_.accountid_ = 0;
}
inline int32_t SChatMessagePacket::_internal_accountid() const {
  return _impl_.accountid_;
}
inline int32_t SChatMessagePacket::accountid() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Social.SChatMessagePacket.AccountId)
  return _internal_accountid();
}
inline void SChatMessagePacket::_internal_set_accountid(int32_t value) {
  
  _impl_.accountid_ = value;
}
inline void SChatMessagePacket::set_accountid(int32_t value) {
  _internal_set_accountid(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Social.SChatMessagePacket.AccountId)
}

// int32 CharacterId = 2;
inline void SChatMessagePacket::clear_characterid() {
  _impl_.characterid_ = 0;
}
inline int32_t SChatMessagePacket::_internal_characterid() const {
  return _impl_.characterid_;
}
inline int32_t SChatMessagePacket::characterid() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Social.SChatMessagePacket.CharacterId)
  return _internal_characterid();
}
inline void SChatMessagePacket::_internal_set_characterid(int32_t value) {
  
  _impl_.characterid_ = value;
}
inline void SChatMessagePacket::set_characterid(int32_t value) {
  _internal_set_characterid(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Social.SChatMessagePacket.CharacterId)
}

// string CharacterName = 3;
inline void SChatMessagePacket::clear_charactername() {
  _impl_.charactername_.ClearToEmpty();
}
inline const std::string& SChatMessagePacket::charactername() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Social.SChatMessagePacket.CharacterName)
  return _internal_charactername();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void SChatMessagePacket::set_charactername(ArgT0&& arg0, ArgT... args) {
 
 _impl_.charactername_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Social.SChatMessagePacket.CharacterName)
}
inline std::string* SChatMessagePacket::mutable_charactername() {
  std::string* _s = _internal_mutable_charactername();
  // @@protoc_insertion_point(field_mutable:Avalon.Network.Packets.Social.SChatMessagePacket.CharacterName)
  return _s;
}
inline const std::string& SChatMessagePacket::_internal_charactername() const {
  return _impl_.charactername_.Get();
}
inline void SChatMessagePacket::_internal_set_charactername(const std::string& value) {
  
  _impl_.charactername_.Set(value, GetArenaForAllocation());
}
inline std::string* SChatMessagePacket::_internal_mutable_charactername() {
  
  return _impl_.charactername_.Mutable(GetArenaForAllocation());
}
inline std::string* SChatMessagePacket::release_charactername() {
  // @@protoc_insertion_point(field_release:Avalon.Network.Packets.Social.SChatMessagePacket.CharacterName)
  return _impl_.charactername_.Release();
}
inline void SChatMessagePacket::set_allocated_charactername(std::string* charactername) {
  if (charactername != nullptr) {
    
  } else {
    
  }
  _impl_.charactername_.SetAllocated(charactername, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.charactername_.IsDefault()) {
    _impl_.charactername_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Avalon.Network.Packets.Social.SChatMessagePacket.CharacterName)
}

// string Message = 4;
inline void SChatMessagePacket::clear_message() {
  _impl_.message_.ClearToEmpty();
}
inline const std::string& SChatMessagePacket::message() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Social.SChatMessagePacket.Message)
  return _internal_message();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void SChatMessagePacket::set_message(ArgT0&& arg0, ArgT... args) {
 
 _impl_.message_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Social.SChatMessagePacket.Message)
}
inline std::string* SChatMessagePacket::mutable_message() {
  std::string* _s = _internal_mutable_message();
  // @@protoc_insertion_point(field_mutable:Avalon.Network.Packets.Social.SChatMessagePacket.Message)
  return _s;
}
inline const std::string& SChatMessagePacket::_internal_message() const {
  return _impl_.message_.Get();
}
inline void SChatMessagePacket::_internal_set_message(const std::string& value) {
  
  _impl_.message_.Set(value, GetArenaForAllocation());
}
inline std::string* SChatMessagePacket::_internal_mutable_message() {
  
  return _impl_.message_.Mutable(GetArenaForAllocation());
}
inline std::string* SChatMessagePacket::release_message() {
  // @@protoc_insertion_point(field_release:Avalon.Network.Packets.Social.SChatMessagePacket.Message)
  return _impl_.message_.Release();
}
inline void SChatMessagePacket::set_allocated_message(std::string* message) {
  if (message != nullptr) {
    
  } else {
    
  }
  _impl_.message_.SetAllocated(message, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.message_.IsDefault()) {
    _impl_.message_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Avalon.Network.Packets.Social.SChatMessagePacket.Message)
}

// .bcl.DateTime DateTime = 5;
inline bool SChatMessagePacket::_internal_has_datetime() const {
  return this != internal_default_instance() && _impl_.datetime_ != nullptr;
}
inline bool SChatMessagePacket::has_datetime() const {
  return _internal_has_datetime();
}
inline const ::bcl::DateTime& SChatMessagePacket::_internal_datetime() const {
  const ::bcl::DateTime* p = _impl_.datetime_;
  return p != nullptr ? *p : reinterpret_cast<const ::bcl::DateTime&>(
      ::bcl::_DateTime_default_instance_);
}
inline const ::bcl::DateTime& SChatMessagePacket::datetime() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Social.SChatMessagePacket.DateTime)
  return _internal_datetime();
}
inline void SChatMessagePacket::unsafe_arena_set_allocated_datetime(
    ::bcl::DateTime* datetime) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.datetime_);
  }
  _impl_.datetime_ = datetime;
  if (datetime) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:Avalon.Network.Packets.Social.SChatMessagePacket.DateTime)
}
inline ::bcl::DateTime* SChatMessagePacket::release_datetime() {
  
  ::bcl::DateTime* temp = _impl_.datetime_;
  _impl_.datetime_ = nullptr;
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
inline ::bcl::DateTime* SChatMessagePacket::unsafe_arena_release_datetime() {
  // @@protoc_insertion_point(field_release:Avalon.Network.Packets.Social.SChatMessagePacket.DateTime)
  
  ::bcl::DateTime* temp = _impl_.datetime_;
  _impl_.datetime_ = nullptr;
  return temp;
}
inline ::bcl::DateTime* SChatMessagePacket::_internal_mutable_datetime() {
  
  if (_impl_.datetime_ == nullptr) {
    auto* p = CreateMaybeMessage<::bcl::DateTime>(GetArenaForAllocation());
    _impl_.datetime_ = p;
  }
  return _impl_.datetime_;
}
inline ::bcl::DateTime* SChatMessagePacket::mutable_datetime() {
  ::bcl::DateTime* _msg = _internal_mutable_datetime();
  // @@protoc_insertion_point(field_mutable:Avalon.Network.Packets.Social.SChatMessagePacket.DateTime)
  return _msg;
}
inline void SChatMessagePacket::set_allocated_datetime(::bcl::DateTime* datetime) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.datetime_);
  }
  if (datetime) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalGetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(datetime));
    if (message_arena != submessage_arena) {
      datetime = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, datetime, submessage_arena);
    }
    
  } else {
    
  }
  _impl_.datetime_ = datetime;
  // @@protoc_insertion_point(field_set_allocated:Avalon.Network.Packets.Social.SChatMessagePacket.DateTime)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Social
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_SChatMessagePacket_2eproto
