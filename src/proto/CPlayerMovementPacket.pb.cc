// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CPlayerMovementPacket.proto

#include "CPlayerMovementPacket.pb.h"

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
namespace Movement {
PROTOBUF_CONSTEXPR CPlayerMovementPacket::CPlayerMovementPacket(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.accountid_)*/0
  , /*decltype(_impl_.characterid_)*/0
  , /*decltype(_impl_.elapsedgametime_)*/0
  , /*decltype(_impl_.x_)*/0
  , /*decltype(_impl_.y_)*/0
  , /*decltype(_impl_.velocityx_)*/0
  , /*decltype(_impl_.velocityy_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct CPlayerMovementPacketDefaultTypeInternal {
  PROTOBUF_CONSTEXPR CPlayerMovementPacketDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~CPlayerMovementPacketDefaultTypeInternal() {}
  union {
    CPlayerMovementPacket _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 CPlayerMovementPacketDefaultTypeInternal _CPlayerMovementPacket_default_instance_;
}  // namespace Movement
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
static ::_pb::Metadata file_level_metadata_CPlayerMovementPacket_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_CPlayerMovementPacket_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_CPlayerMovementPacket_2eproto = nullptr;

const uint32_t TableStruct_CPlayerMovementPacket_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Movement::CPlayerMovementPacket, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Movement::CPlayerMovementPacket, _impl_.accountid_),
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Movement::CPlayerMovementPacket, _impl_.characterid_),
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Movement::CPlayerMovementPacket, _impl_.elapsedgametime_),
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Movement::CPlayerMovementPacket, _impl_.x_),
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Movement::CPlayerMovementPacket, _impl_.y_),
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Movement::CPlayerMovementPacket, _impl_.velocityx_),
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Movement::CPlayerMovementPacket, _impl_.velocityy_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Avalon::Network::Packets::Movement::CPlayerMovementPacket)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::Avalon::Network::Packets::Movement::_CPlayerMovementPacket_default_instance_._instance,
};

const char descriptor_table_protodef_CPlayerMovementPacket_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\033CPlayerMovementPacket.proto\022\037Avalon.Ne"
  "twork.Packets.Movement\"\224\001\n\025CPlayerMoveme"
  "ntPacket\022\021\n\tAccountId\030\001 \001(\005\022\023\n\013Character"
  "Id\030\002 \001(\005\022\027\n\017ElapsedGameTime\030\003 \001(\002\022\t\n\001X\030\004"
  " \001(\002\022\t\n\001Y\030\005 \001(\002\022\021\n\tVelocityX\030\006 \001(\002\022\021\n\tVe"
  "locityY\030\007 \001(\002b\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_CPlayerMovementPacket_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_CPlayerMovementPacket_2eproto = {
    false, false, 221, descriptor_table_protodef_CPlayerMovementPacket_2eproto,
    "CPlayerMovementPacket.proto",
    &descriptor_table_CPlayerMovementPacket_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_CPlayerMovementPacket_2eproto::offsets,
    file_level_metadata_CPlayerMovementPacket_2eproto, file_level_enum_descriptors_CPlayerMovementPacket_2eproto,
    file_level_service_descriptors_CPlayerMovementPacket_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_CPlayerMovementPacket_2eproto_getter() {
  return &descriptor_table_CPlayerMovementPacket_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_CPlayerMovementPacket_2eproto(&descriptor_table_CPlayerMovementPacket_2eproto);
namespace Avalon {
namespace Network {
namespace Packets {
namespace Movement {

// ===================================================================

class CPlayerMovementPacket::_Internal {
 public:
};

CPlayerMovementPacket::CPlayerMovementPacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Avalon.Network.Packets.Movement.CPlayerMovementPacket)
}
CPlayerMovementPacket::CPlayerMovementPacket(const CPlayerMovementPacket& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  CPlayerMovementPacket* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.accountid_){}
    , decltype(_impl_.characterid_){}
    , decltype(_impl_.elapsedgametime_){}
    , decltype(_impl_.x_){}
    , decltype(_impl_.y_){}
    , decltype(_impl_.velocityx_){}
    , decltype(_impl_.velocityy_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&_impl_.accountid_, &from._impl_.accountid_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.velocityy_) -
    reinterpret_cast<char*>(&_impl_.accountid_)) + sizeof(_impl_.velocityy_));
  // @@protoc_insertion_point(copy_constructor:Avalon.Network.Packets.Movement.CPlayerMovementPacket)
}

inline void CPlayerMovementPacket::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.accountid_){0}
    , decltype(_impl_.characterid_){0}
    , decltype(_impl_.elapsedgametime_){0}
    , decltype(_impl_.x_){0}
    , decltype(_impl_.y_){0}
    , decltype(_impl_.velocityx_){0}
    , decltype(_impl_.velocityy_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

CPlayerMovementPacket::~CPlayerMovementPacket() {
  // @@protoc_insertion_point(destructor:Avalon.Network.Packets.Movement.CPlayerMovementPacket)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void CPlayerMovementPacket::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void CPlayerMovementPacket::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void CPlayerMovementPacket::Clear() {
// @@protoc_insertion_point(message_clear_start:Avalon.Network.Packets.Movement.CPlayerMovementPacket)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&_impl_.accountid_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.velocityy_) -
      reinterpret_cast<char*>(&_impl_.accountid_)) + sizeof(_impl_.velocityy_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* CPlayerMovementPacket::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
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
      // int32 CharacterId = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.characterid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // float ElapsedGameTime = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 29)) {
          _impl_.elapsedgametime_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // float X = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 37)) {
          _impl_.x_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // float Y = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 45)) {
          _impl_.y_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // float VelocityX = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 53)) {
          _impl_.velocityx_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // float VelocityY = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 61)) {
          _impl_.velocityy_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
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

uint8_t* CPlayerMovementPacket::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Avalon.Network.Packets.Movement.CPlayerMovementPacket)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 AccountId = 1;
  if (this->_internal_accountid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_accountid(), target);
  }

  // int32 CharacterId = 2;
  if (this->_internal_characterid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_characterid(), target);
  }

  // float ElapsedGameTime = 3;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_elapsedgametime = this->_internal_elapsedgametime();
  uint32_t raw_elapsedgametime;
  memcpy(&raw_elapsedgametime, &tmp_elapsedgametime, sizeof(tmp_elapsedgametime));
  if (raw_elapsedgametime != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(3, this->_internal_elapsedgametime(), target);
  }

  // float X = 4;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_x = this->_internal_x();
  uint32_t raw_x;
  memcpy(&raw_x, &tmp_x, sizeof(tmp_x));
  if (raw_x != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(4, this->_internal_x(), target);
  }

  // float Y = 5;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_y = this->_internal_y();
  uint32_t raw_y;
  memcpy(&raw_y, &tmp_y, sizeof(tmp_y));
  if (raw_y != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(5, this->_internal_y(), target);
  }

  // float VelocityX = 6;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_velocityx = this->_internal_velocityx();
  uint32_t raw_velocityx;
  memcpy(&raw_velocityx, &tmp_velocityx, sizeof(tmp_velocityx));
  if (raw_velocityx != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(6, this->_internal_velocityx(), target);
  }

  // float VelocityY = 7;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_velocityy = this->_internal_velocityy();
  uint32_t raw_velocityy;
  memcpy(&raw_velocityy, &tmp_velocityy, sizeof(tmp_velocityy));
  if (raw_velocityy != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(7, this->_internal_velocityy(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Avalon.Network.Packets.Movement.CPlayerMovementPacket)
  return target;
}

size_t CPlayerMovementPacket::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Avalon.Network.Packets.Movement.CPlayerMovementPacket)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 AccountId = 1;
  if (this->_internal_accountid() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_accountid());
  }

  // int32 CharacterId = 2;
  if (this->_internal_characterid() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_characterid());
  }

  // float ElapsedGameTime = 3;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_elapsedgametime = this->_internal_elapsedgametime();
  uint32_t raw_elapsedgametime;
  memcpy(&raw_elapsedgametime, &tmp_elapsedgametime, sizeof(tmp_elapsedgametime));
  if (raw_elapsedgametime != 0) {
    total_size += 1 + 4;
  }

  // float X = 4;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_x = this->_internal_x();
  uint32_t raw_x;
  memcpy(&raw_x, &tmp_x, sizeof(tmp_x));
  if (raw_x != 0) {
    total_size += 1 + 4;
  }

  // float Y = 5;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_y = this->_internal_y();
  uint32_t raw_y;
  memcpy(&raw_y, &tmp_y, sizeof(tmp_y));
  if (raw_y != 0) {
    total_size += 1 + 4;
  }

  // float VelocityX = 6;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_velocityx = this->_internal_velocityx();
  uint32_t raw_velocityx;
  memcpy(&raw_velocityx, &tmp_velocityx, sizeof(tmp_velocityx));
  if (raw_velocityx != 0) {
    total_size += 1 + 4;
  }

  // float VelocityY = 7;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_velocityy = this->_internal_velocityy();
  uint32_t raw_velocityy;
  memcpy(&raw_velocityy, &tmp_velocityy, sizeof(tmp_velocityy));
  if (raw_velocityy != 0) {
    total_size += 1 + 4;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData CPlayerMovementPacket::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    CPlayerMovementPacket::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*CPlayerMovementPacket::GetClassData() const { return &_class_data_; }


void CPlayerMovementPacket::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<CPlayerMovementPacket*>(&to_msg);
  auto& from = static_cast<const CPlayerMovementPacket&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Avalon.Network.Packets.Movement.CPlayerMovementPacket)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_accountid() != 0) {
    _this->_internal_set_accountid(from._internal_accountid());
  }
  if (from._internal_characterid() != 0) {
    _this->_internal_set_characterid(from._internal_characterid());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_elapsedgametime = from._internal_elapsedgametime();
  uint32_t raw_elapsedgametime;
  memcpy(&raw_elapsedgametime, &tmp_elapsedgametime, sizeof(tmp_elapsedgametime));
  if (raw_elapsedgametime != 0) {
    _this->_internal_set_elapsedgametime(from._internal_elapsedgametime());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_x = from._internal_x();
  uint32_t raw_x;
  memcpy(&raw_x, &tmp_x, sizeof(tmp_x));
  if (raw_x != 0) {
    _this->_internal_set_x(from._internal_x());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_y = from._internal_y();
  uint32_t raw_y;
  memcpy(&raw_y, &tmp_y, sizeof(tmp_y));
  if (raw_y != 0) {
    _this->_internal_set_y(from._internal_y());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_velocityx = from._internal_velocityx();
  uint32_t raw_velocityx;
  memcpy(&raw_velocityx, &tmp_velocityx, sizeof(tmp_velocityx));
  if (raw_velocityx != 0) {
    _this->_internal_set_velocityx(from._internal_velocityx());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_velocityy = from._internal_velocityy();
  uint32_t raw_velocityy;
  memcpy(&raw_velocityy, &tmp_velocityy, sizeof(tmp_velocityy));
  if (raw_velocityy != 0) {
    _this->_internal_set_velocityy(from._internal_velocityy());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void CPlayerMovementPacket::CopyFrom(const CPlayerMovementPacket& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Avalon.Network.Packets.Movement.CPlayerMovementPacket)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CPlayerMovementPacket::IsInitialized() const {
  return true;
}

void CPlayerMovementPacket::InternalSwap(CPlayerMovementPacket* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(CPlayerMovementPacket, _impl_.velocityy_)
      + sizeof(CPlayerMovementPacket::_impl_.velocityy_)
      - PROTOBUF_FIELD_OFFSET(CPlayerMovementPacket, _impl_.accountid_)>(
          reinterpret_cast<char*>(&_impl_.accountid_),
          reinterpret_cast<char*>(&other->_impl_.accountid_));
}

::PROTOBUF_NAMESPACE_ID::Metadata CPlayerMovementPacket::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_CPlayerMovementPacket_2eproto_getter, &descriptor_table_CPlayerMovementPacket_2eproto_once,
      file_level_metadata_CPlayerMovementPacket_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Movement
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Avalon::Network::Packets::Movement::CPlayerMovementPacket*
Arena::CreateMaybeMessage< ::Avalon::Network::Packets::Movement::CPlayerMovementPacket >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Avalon::Network::Packets::Movement::CPlayerMovementPacket >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
