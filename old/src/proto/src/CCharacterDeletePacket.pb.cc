// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CCharacterDeletePacket.proto

#include "Proto/CCharacterDeletePacket.pb.h"

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
namespace Character {
PROTOBUF_CONSTEXPR CCharacterDeletePacket::CCharacterDeletePacket(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.characterid_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct CCharacterDeletePacketDefaultTypeInternal {
  PROTOBUF_CONSTEXPR CCharacterDeletePacketDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~CCharacterDeletePacketDefaultTypeInternal() {}
  union {
    CCharacterDeletePacket _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 CCharacterDeletePacketDefaultTypeInternal _CCharacterDeletePacket_default_instance_;
}  // namespace Character
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
static ::_pb::Metadata file_level_metadata_CCharacterDeletePacket_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_CCharacterDeletePacket_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_CCharacterDeletePacket_2eproto = nullptr;

const uint32_t TableStruct_CCharacterDeletePacket_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Character::CCharacterDeletePacket, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Character::CCharacterDeletePacket, _impl_.characterid_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Avalon::Network::Packets::Character::CCharacterDeletePacket)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::Avalon::Network::Packets::Character::_CCharacterDeletePacket_default_instance_._instance,
};

const char descriptor_table_protodef_CCharacterDeletePacket_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\034CCharacterDeletePacket.proto\022 Avalon.N"
  "etwork.Packets.Character\"-\n\026CCharacterDe"
  "letePacket\022\023\n\013CharacterId\030\001 \001(\005b\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_CCharacterDeletePacket_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_CCharacterDeletePacket_2eproto = {
    false, false, 119, descriptor_table_protodef_CCharacterDeletePacket_2eproto,
    "CCharacterDeletePacket.proto",
    &descriptor_table_CCharacterDeletePacket_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_CCharacterDeletePacket_2eproto::offsets,
    file_level_metadata_CCharacterDeletePacket_2eproto, file_level_enum_descriptors_CCharacterDeletePacket_2eproto,
    file_level_service_descriptors_CCharacterDeletePacket_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_CCharacterDeletePacket_2eproto_getter() {
  return &descriptor_table_CCharacterDeletePacket_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_CCharacterDeletePacket_2eproto(&descriptor_table_CCharacterDeletePacket_2eproto);
namespace Avalon {
namespace Network {
namespace Packets {
namespace Character {

// ===================================================================

class CCharacterDeletePacket::_Internal {
 public:
};

CCharacterDeletePacket::CCharacterDeletePacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Avalon.Network.Packets.Character.CCharacterDeletePacket)
}
CCharacterDeletePacket::CCharacterDeletePacket(const CCharacterDeletePacket& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  CCharacterDeletePacket* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.characterid_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _this->_impl_.characterid_ = from._impl_.characterid_;
  // @@protoc_insertion_point(copy_constructor:Avalon.Network.Packets.Character.CCharacterDeletePacket)
}

inline void CCharacterDeletePacket::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.characterid_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

CCharacterDeletePacket::~CCharacterDeletePacket() {
  // @@protoc_insertion_point(destructor:Avalon.Network.Packets.Character.CCharacterDeletePacket)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void CCharacterDeletePacket::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void CCharacterDeletePacket::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void CCharacterDeletePacket::Clear() {
// @@protoc_insertion_point(message_clear_start:Avalon.Network.Packets.Character.CCharacterDeletePacket)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.characterid_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* CCharacterDeletePacket::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 CharacterId = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.characterid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
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

uint8_t* CCharacterDeletePacket::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Avalon.Network.Packets.Character.CCharacterDeletePacket)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 CharacterId = 1;
  if (this->_internal_characterid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_characterid(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Avalon.Network.Packets.Character.CCharacterDeletePacket)
  return target;
}

size_t CCharacterDeletePacket::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Avalon.Network.Packets.Character.CCharacterDeletePacket)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 CharacterId = 1;
  if (this->_internal_characterid() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_characterid());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData CCharacterDeletePacket::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    CCharacterDeletePacket::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*CCharacterDeletePacket::GetClassData() const { return &_class_data_; }


void CCharacterDeletePacket::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<CCharacterDeletePacket*>(&to_msg);
  auto& from = static_cast<const CCharacterDeletePacket&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Avalon.Network.Packets.Character.CCharacterDeletePacket)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_characterid() != 0) {
    _this->_internal_set_characterid(from._internal_characterid());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void CCharacterDeletePacket::CopyFrom(const CCharacterDeletePacket& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Avalon.Network.Packets.Character.CCharacterDeletePacket)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CCharacterDeletePacket::IsInitialized() const {
  return true;
}

void CCharacterDeletePacket::InternalSwap(CCharacterDeletePacket* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_.characterid_, other->_impl_.characterid_);
}

::PROTOBUF_NAMESPACE_ID::Metadata CCharacterDeletePacket::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_CCharacterDeletePacket_2eproto_getter, &descriptor_table_CCharacterDeletePacket_2eproto_once,
      file_level_metadata_CCharacterDeletePacket_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Character
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Avalon::Network::Packets::Character::CCharacterDeletePacket*
Arena::CreateMaybeMessage< ::Avalon::Network::Packets::Character::CCharacterDeletePacket >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Avalon::Network::Packets::Character::CCharacterDeletePacket >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
