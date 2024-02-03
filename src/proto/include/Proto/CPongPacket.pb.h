// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CPongPacket.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_CPongPacket_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_CPongPacket_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_CPongPacket_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_CPongPacket_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_CPongPacket_2eproto;
namespace Avalon {
namespace Network {
namespace Packets {
namespace Generic {
class CPongPacket;
struct CPongPacketDefaultTypeInternal;
extern CPongPacketDefaultTypeInternal _CPongPacket_default_instance_;
}  // namespace Generic
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
PROTOBUF_NAMESPACE_OPEN
template<> ::Avalon::Network::Packets::Generic::CPongPacket* Arena::CreateMaybeMessage<::Avalon::Network::Packets::Generic::CPongPacket>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Avalon {
namespace Network {
namespace Packets {
namespace Generic {

// ===================================================================

class CPongPacket final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Avalon.Network.Packets.Generic.CPongPacket) */ {
 public:
  inline CPongPacket() : CPongPacket(nullptr) {}
  ~CPongPacket() override;
  explicit PROTOBUF_CONSTEXPR CPongPacket(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  CPongPacket(const CPongPacket& from);
  CPongPacket(CPongPacket&& from) noexcept
    : CPongPacket() {
    *this = ::std::move(from);
  }

  inline CPongPacket& operator=(const CPongPacket& from) {
    CopyFrom(from);
    return *this;
  }
  inline CPongPacket& operator=(CPongPacket&& from) noexcept {
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
  static const CPongPacket& default_instance() {
    return *internal_default_instance();
  }
  static inline const CPongPacket* internal_default_instance() {
    return reinterpret_cast<const CPongPacket*>(
               &_CPongPacket_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(CPongPacket& a, CPongPacket& b) {
    a.Swap(&b);
  }
  inline void Swap(CPongPacket* other) {
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
  void UnsafeArenaSwap(CPongPacket* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  CPongPacket* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<CPongPacket>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const CPongPacket& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const CPongPacket& from) {
    CPongPacket::MergeImpl(*this, from);
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
  void InternalSwap(CPongPacket* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Avalon.Network.Packets.Generic.CPongPacket";
  }
  protected:
  explicit CPongPacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kSequenceNumberFieldNumber = 1,
    kTicksFieldNumber = 3,
    kAccountIdFieldNumber = 2,
  };
  // int64 SequenceNumber = 1;
  void clear_sequencenumber();
  int64_t sequencenumber() const;
  void set_sequencenumber(int64_t value);
  private:
  int64_t _internal_sequencenumber() const;
  void _internal_set_sequencenumber(int64_t value);
  public:

  // int64 Ticks = 3;
  void clear_ticks();
  int64_t ticks() const;
  void set_ticks(int64_t value);
  private:
  int64_t _internal_ticks() const;
  void _internal_set_ticks(int64_t value);
  public:

  // int32 AccountId = 2;
  void clear_accountid();
  int32_t accountid() const;
  void set_accountid(int32_t value);
  private:
  int32_t _internal_accountid() const;
  void _internal_set_accountid(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:Avalon.Network.Packets.Generic.CPongPacket)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    int64_t sequencenumber_;
    int64_t ticks_;
    int32_t accountid_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_CPongPacket_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CPongPacket

// int64 SequenceNumber = 1;
inline void CPongPacket::clear_sequencenumber() {
  _impl_.sequencenumber_ = int64_t{0};
}
inline int64_t CPongPacket::_internal_sequencenumber() const {
  return _impl_.sequencenumber_;
}
inline int64_t CPongPacket::sequencenumber() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Generic.CPongPacket.SequenceNumber)
  return _internal_sequencenumber();
}
inline void CPongPacket::_internal_set_sequencenumber(int64_t value) {
  
  _impl_.sequencenumber_ = value;
}
inline void CPongPacket::set_sequencenumber(int64_t value) {
  _internal_set_sequencenumber(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Generic.CPongPacket.SequenceNumber)
}

// int32 AccountId = 2;
inline void CPongPacket::clear_accountid() {
  _impl_.accountid_ = 0;
}
inline int32_t CPongPacket::_internal_accountid() const {
  return _impl_.accountid_;
}
inline int32_t CPongPacket::accountid() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Generic.CPongPacket.AccountId)
  return _internal_accountid();
}
inline void CPongPacket::_internal_set_accountid(int32_t value) {
  
  _impl_.accountid_ = value;
}
inline void CPongPacket::set_accountid(int32_t value) {
  _internal_set_accountid(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Generic.CPongPacket.AccountId)
}

// int64 Ticks = 3;
inline void CPongPacket::clear_ticks() {
  _impl_.ticks_ = int64_t{0};
}
inline int64_t CPongPacket::_internal_ticks() const {
  return _impl_.ticks_;
}
inline int64_t CPongPacket::ticks() const {
  // @@protoc_insertion_point(field_get:Avalon.Network.Packets.Generic.CPongPacket.Ticks)
  return _internal_ticks();
}
inline void CPongPacket::_internal_set_ticks(int64_t value) {
  
  _impl_.ticks_ = value;
}
inline void CPongPacket::set_ticks(int64_t value) {
  _internal_set_ticks(value);
  // @@protoc_insertion_point(field_set:Avalon.Network.Packets.Generic.CPongPacket.Ticks)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Generic
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_CPongPacket_2eproto