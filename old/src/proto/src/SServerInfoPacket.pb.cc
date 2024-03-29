// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SServerInfoPacket.proto

#include "Proto/SServerInfoPacket.pb.h"

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
namespace Handshake {
PROTOBUF_CONSTEXPR SServerInfoPacket::SServerInfoPacket(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.publickey_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.serverversion_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct SServerInfoPacketDefaultTypeInternal {
  PROTOBUF_CONSTEXPR SServerInfoPacketDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~SServerInfoPacketDefaultTypeInternal() {}
  union {
    SServerInfoPacket _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 SServerInfoPacketDefaultTypeInternal _SServerInfoPacket_default_instance_;
}  // namespace Handshake
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
static ::_pb::Metadata file_level_metadata_SServerInfoPacket_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_SServerInfoPacket_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_SServerInfoPacket_2eproto = nullptr;

const uint32_t TableStruct_SServerInfoPacket_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Handshake::SServerInfoPacket, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Handshake::SServerInfoPacket, _impl_.serverversion_),
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Handshake::SServerInfoPacket, _impl_.publickey_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Avalon::Network::Packets::Handshake::SServerInfoPacket)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::Avalon::Network::Packets::Handshake::_SServerInfoPacket_default_instance_._instance,
};

const char descriptor_table_protodef_SServerInfoPacket_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\027SServerInfoPacket.proto\022 Avalon.Networ"
  "k.Packets.Handshake\"=\n\021SServerInfoPacket"
  "\022\025\n\rServerVersion\030\001 \001(\005\022\021\n\tPublicKey\030\002 \001"
  "(\014b\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_SServerInfoPacket_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_SServerInfoPacket_2eproto = {
    false, false, 130, descriptor_table_protodef_SServerInfoPacket_2eproto,
    "SServerInfoPacket.proto",
    &descriptor_table_SServerInfoPacket_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_SServerInfoPacket_2eproto::offsets,
    file_level_metadata_SServerInfoPacket_2eproto, file_level_enum_descriptors_SServerInfoPacket_2eproto,
    file_level_service_descriptors_SServerInfoPacket_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_SServerInfoPacket_2eproto_getter() {
  return &descriptor_table_SServerInfoPacket_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_SServerInfoPacket_2eproto(&descriptor_table_SServerInfoPacket_2eproto);
namespace Avalon {
namespace Network {
namespace Packets {
namespace Handshake {

// ===================================================================

class SServerInfoPacket::_Internal {
 public:
};

SServerInfoPacket::SServerInfoPacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Avalon.Network.Packets.Handshake.SServerInfoPacket)
}
SServerInfoPacket::SServerInfoPacket(const SServerInfoPacket& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  SServerInfoPacket* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.publickey_){}
    , decltype(_impl_.serverversion_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.publickey_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.publickey_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_publickey().empty()) {
    _this->_impl_.publickey_.Set(from._internal_publickey(),
      _this->GetArenaForAllocation());
  }
  _this->_impl_.serverversion_ = from._impl_.serverversion_;
  // @@protoc_insertion_point(copy_constructor:Avalon.Network.Packets.Handshake.SServerInfoPacket)
}

inline void SServerInfoPacket::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.publickey_){}
    , decltype(_impl_.serverversion_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.publickey_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.publickey_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

SServerInfoPacket::~SServerInfoPacket() {
  // @@protoc_insertion_point(destructor:Avalon.Network.Packets.Handshake.SServerInfoPacket)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void SServerInfoPacket::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.publickey_.Destroy();
}

void SServerInfoPacket::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void SServerInfoPacket::Clear() {
// @@protoc_insertion_point(message_clear_start:Avalon.Network.Packets.Handshake.SServerInfoPacket)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.publickey_.ClearToEmpty();
  _impl_.serverversion_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* SServerInfoPacket::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 ServerVersion = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.serverversion_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // bytes PublicKey = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_publickey();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
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

uint8_t* SServerInfoPacket::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Avalon.Network.Packets.Handshake.SServerInfoPacket)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 ServerVersion = 1;
  if (this->_internal_serverversion() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_serverversion(), target);
  }

  // bytes PublicKey = 2;
  if (!this->_internal_publickey().empty()) {
    target = stream->WriteBytesMaybeAliased(
        2, this->_internal_publickey(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Avalon.Network.Packets.Handshake.SServerInfoPacket)
  return target;
}

size_t SServerInfoPacket::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Avalon.Network.Packets.Handshake.SServerInfoPacket)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes PublicKey = 2;
  if (!this->_internal_publickey().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_publickey());
  }

  // int32 ServerVersion = 1;
  if (this->_internal_serverversion() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_serverversion());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData SServerInfoPacket::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    SServerInfoPacket::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*SServerInfoPacket::GetClassData() const { return &_class_data_; }


void SServerInfoPacket::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<SServerInfoPacket*>(&to_msg);
  auto& from = static_cast<const SServerInfoPacket&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Avalon.Network.Packets.Handshake.SServerInfoPacket)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_publickey().empty()) {
    _this->_internal_set_publickey(from._internal_publickey());
  }
  if (from._internal_serverversion() != 0) {
    _this->_internal_set_serverversion(from._internal_serverversion());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void SServerInfoPacket::CopyFrom(const SServerInfoPacket& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Avalon.Network.Packets.Handshake.SServerInfoPacket)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SServerInfoPacket::IsInitialized() const {
  return true;
}

void SServerInfoPacket::InternalSwap(SServerInfoPacket* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.publickey_, lhs_arena,
      &other->_impl_.publickey_, rhs_arena
  );
  swap(_impl_.serverversion_, other->_impl_.serverversion_);
}

::PROTOBUF_NAMESPACE_ID::Metadata SServerInfoPacket::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_SServerInfoPacket_2eproto_getter, &descriptor_table_SServerInfoPacket_2eproto_once,
      file_level_metadata_SServerInfoPacket_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Handshake
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Avalon::Network::Packets::Handshake::SServerInfoPacket*
Arena::CreateMaybeMessage< ::Avalon::Network::Packets::Handshake::SServerInfoPacket >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Avalon::Network::Packets::Handshake::SServerInfoPacket >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
