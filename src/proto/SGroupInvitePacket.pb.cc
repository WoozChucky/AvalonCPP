// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SGroupInvitePacket.proto

#include "SGroupInvitePacket.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace Avalon {
namespace Network {
namespace Packets {
namespace Social {
PROTOBUF_CONSTEXPR SGroupInvitePacket::SGroupInvitePacket(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.invitername_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.accountid_)*/0
  , /*decltype(_impl_.inviteraccountid_)*/0
  , /*decltype(_impl_.invitercharacterid_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct SGroupInvitePacketDefaultTypeInternal {
  PROTOBUF_CONSTEXPR SGroupInvitePacketDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~SGroupInvitePacketDefaultTypeInternal() {}
  union {
    SGroupInvitePacket _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 SGroupInvitePacketDefaultTypeInternal _SGroupInvitePacket_default_instance_;
}  // namespace Social
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
static ::_pb::Metadata file_level_metadata_SGroupInvitePacket_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_SGroupInvitePacket_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_SGroupInvitePacket_2eproto = nullptr;

const uint32_t TableStruct_SGroupInvitePacket_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Social::SGroupInvitePacket, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Social::SGroupInvitePacket, _impl_.accountid_),
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Social::SGroupInvitePacket, _impl_.inviteraccountid_),
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Social::SGroupInvitePacket, _impl_.invitercharacterid_),
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Social::SGroupInvitePacket, _impl_.invitername_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Avalon::Network::Packets::Social::SGroupInvitePacket)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::Avalon::Network::Packets::Social::_SGroupInvitePacket_default_instance_._instance,
};

const char descriptor_table_protodef_SGroupInvitePacket_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\030SGroupInvitePacket.proto\022\035Avalon.Netwo"
  "rk.Packets.Social\"r\n\022SGroupInvitePacket\022"
  "\021\n\tAccountId\030\001 \001(\005\022\030\n\020InviterAccountId\030\002"
  " \001(\005\022\032\n\022InviterCharacterId\030\003 \001(\005\022\023\n\013Invi"
  "terName\030\004 \001(\tb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_SGroupInvitePacket_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_SGroupInvitePacket_2eproto = {
    false, false, 181, descriptor_table_protodef_SGroupInvitePacket_2eproto,
    "SGroupInvitePacket.proto",
    &descriptor_table_SGroupInvitePacket_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_SGroupInvitePacket_2eproto::offsets,
    file_level_metadata_SGroupInvitePacket_2eproto, file_level_enum_descriptors_SGroupInvitePacket_2eproto,
    file_level_service_descriptors_SGroupInvitePacket_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_SGroupInvitePacket_2eproto_getter() {
  return &descriptor_table_SGroupInvitePacket_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_SGroupInvitePacket_2eproto(&descriptor_table_SGroupInvitePacket_2eproto);
namespace Avalon {
namespace Network {
namespace Packets {
namespace Social {

// ===================================================================

class SGroupInvitePacket::_Internal {
 public:
};

SGroupInvitePacket::SGroupInvitePacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Avalon.Network.Packets.Social.SGroupInvitePacket)
}
SGroupInvitePacket::SGroupInvitePacket(const SGroupInvitePacket& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  SGroupInvitePacket* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.invitername_){}
    , decltype(_impl_.accountid_){}
    , decltype(_impl_.inviteraccountid_){}
    , decltype(_impl_.invitercharacterid_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.invitername_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.invitername_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_invitername().empty()) {
    _this->_impl_.invitername_.Set(from._internal_invitername(), 
      _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.accountid_, &from._impl_.accountid_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.invitercharacterid_) -
    reinterpret_cast<char*>(&_impl_.accountid_)) + sizeof(_impl_.invitercharacterid_));
  // @@protoc_insertion_point(copy_constructor:Avalon.Network.Packets.Social.SGroupInvitePacket)
}

inline void SGroupInvitePacket::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.invitername_){}
    , decltype(_impl_.accountid_){0}
    , decltype(_impl_.inviteraccountid_){0}
    , decltype(_impl_.invitercharacterid_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.invitername_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.invitername_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

SGroupInvitePacket::~SGroupInvitePacket() {
  // @@protoc_insertion_point(destructor:Avalon.Network.Packets.Social.SGroupInvitePacket)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void SGroupInvitePacket::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.invitername_.Destroy();
}

void SGroupInvitePacket::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void SGroupInvitePacket::Clear() {
// @@protoc_insertion_point(message_clear_start:Avalon.Network.Packets.Social.SGroupInvitePacket)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.invitername_.ClearToEmpty();
  ::memset(&_impl_.accountid_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.invitercharacterid_) -
      reinterpret_cast<char*>(&_impl_.accountid_)) + sizeof(_impl_.invitercharacterid_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* SGroupInvitePacket::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 AccountId = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.accountid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 InviterAccountId = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.inviteraccountid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 InviterCharacterId = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          _impl_.invitercharacterid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string InviterName = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 34)) {
          auto str = _internal_mutable_invitername();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Avalon.Network.Packets.Social.SGroupInvitePacket.InviterName"));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* SGroupInvitePacket::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Avalon.Network.Packets.Social.SGroupInvitePacket)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 AccountId = 1;
  if (this->_internal_accountid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_accountid(), target);
  }

  // int32 InviterAccountId = 2;
  if (this->_internal_inviteraccountid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_inviteraccountid(), target);
  }

  // int32 InviterCharacterId = 3;
  if (this->_internal_invitercharacterid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(3, this->_internal_invitercharacterid(), target);
  }

  // string InviterName = 4;
  if (!this->_internal_invitername().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_invitername().data(), static_cast<int>(this->_internal_invitername().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Avalon.Network.Packets.Social.SGroupInvitePacket.InviterName");
    target = stream->WriteStringMaybeAliased(
        4, this->_internal_invitername(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Avalon.Network.Packets.Social.SGroupInvitePacket)
  return target;
}

size_t SGroupInvitePacket::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Avalon.Network.Packets.Social.SGroupInvitePacket)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string InviterName = 4;
  if (!this->_internal_invitername().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_invitername());
  }

  // int32 AccountId = 1;
  if (this->_internal_accountid() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_accountid());
  }

  // int32 InviterAccountId = 2;
  if (this->_internal_inviteraccountid() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_inviteraccountid());
  }

  // int32 InviterCharacterId = 3;
  if (this->_internal_invitercharacterid() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_invitercharacterid());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData SGroupInvitePacket::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    SGroupInvitePacket::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*SGroupInvitePacket::GetClassData() const { return &_class_data_; }


void SGroupInvitePacket::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<SGroupInvitePacket*>(&to_msg);
  auto& from = static_cast<const SGroupInvitePacket&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Avalon.Network.Packets.Social.SGroupInvitePacket)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_invitername().empty()) {
    _this->_internal_set_invitername(from._internal_invitername());
  }
  if (from._internal_accountid() != 0) {
    _this->_internal_set_accountid(from._internal_accountid());
  }
  if (from._internal_inviteraccountid() != 0) {
    _this->_internal_set_inviteraccountid(from._internal_inviteraccountid());
  }
  if (from._internal_invitercharacterid() != 0) {
    _this->_internal_set_invitercharacterid(from._internal_invitercharacterid());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void SGroupInvitePacket::CopyFrom(const SGroupInvitePacket& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Avalon.Network.Packets.Social.SGroupInvitePacket)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SGroupInvitePacket::IsInitialized() const {
  return true;
}

void SGroupInvitePacket::InternalSwap(SGroupInvitePacket* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.invitername_, lhs_arena,
      &other->_impl_.invitername_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(SGroupInvitePacket, _impl_.invitercharacterid_)
      + sizeof(SGroupInvitePacket::_impl_.invitercharacterid_)
      - PROTOBUF_FIELD_OFFSET(SGroupInvitePacket, _impl_.accountid_)>(
          reinterpret_cast<char*>(&_impl_.accountid_),
          reinterpret_cast<char*>(&other->_impl_.accountid_));
}

::PROTOBUF_NAMESPACE_ID::Metadata SGroupInvitePacket::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_SGroupInvitePacket_2eproto_getter, &descriptor_table_SGroupInvitePacket_2eproto_once,
      file_level_metadata_SGroupInvitePacket_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Social
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Avalon::Network::Packets::Social::SGroupInvitePacket*
Arena::CreateMaybeMessage< ::Avalon::Network::Packets::Social::SGroupInvitePacket >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Avalon::Network::Packets::Social::SGroupInvitePacket >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
