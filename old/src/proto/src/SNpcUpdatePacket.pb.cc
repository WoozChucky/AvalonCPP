// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SNpcUpdatePacket.proto

#include "Proto/SNpcUpdatePacket.pb.h"

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
PROTOBUF_CONSTEXPR CreaturePacket::CreaturePacket(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.name_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.id_)*/nullptr
  , /*decltype(_impl_.positionx_)*/0
  , /*decltype(_impl_.positiony_)*/0
  , /*decltype(_impl_.velocityx_)*/0
  , /*decltype(_impl_.velocityy_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct CreaturePacketDefaultTypeInternal {
  PROTOBUF_CONSTEXPR CreaturePacketDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~CreaturePacketDefaultTypeInternal() {}
  union {
    CreaturePacket _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 CreaturePacketDefaultTypeInternal _CreaturePacket_default_instance_;
PROTOBUF_CONSTEXPR SNpcUpdatePacket::SNpcUpdatePacket(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.creatures_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct SNpcUpdatePacketDefaultTypeInternal {
  PROTOBUF_CONSTEXPR SNpcUpdatePacketDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~SNpcUpdatePacketDefaultTypeInternal() {}
  union {
    SNpcUpdatePacket _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 SNpcUpdatePacketDefaultTypeInternal _SNpcUpdatePacket_default_instance_;
}  // namespace Movement
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
static ::_pb::Metadata file_level_metadata_SNpcUpdatePacket_2eproto[2];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_SNpcUpdatePacket_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_SNpcUpdatePacket_2eproto = nullptr;

const uint32_t TableStruct_SNpcUpdatePacket_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Movement::CreaturePacket, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Movement::CreaturePacket, _impl_.id_),
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Movement::CreaturePacket, _impl_.name_),
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Movement::CreaturePacket, _impl_.positionx_),
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Movement::CreaturePacket, _impl_.positiony_),
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Movement::CreaturePacket, _impl_.velocityx_),
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Movement::CreaturePacket, _impl_.velocityy_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Movement::SNpcUpdatePacket, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Movement::SNpcUpdatePacket, _impl_.creatures_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Avalon::Network::Packets::Movement::CreaturePacket)},
  { 12, -1, -1, sizeof(::Avalon::Network::Packets::Movement::SNpcUpdatePacket)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::Avalon::Network::Packets::Movement::_CreaturePacket_default_instance_._instance,
  &::Avalon::Network::Packets::Movement::_SNpcUpdatePacket_default_instance_._instance,
};

const char descriptor_table_protodef_SNpcUpdatePacket_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\026SNpcUpdatePacket.proto\022\037Avalon.Network"
  ".Packets.Movement\032\tbcl.proto\"\201\001\n\016Creatur"
  "ePacket\022\025\n\002Id\030\001 \001(\0132\t.bcl.Guid\022\014\n\004Name\030\002"
  " \001(\t\022\021\n\tPositionX\030\003 \001(\002\022\021\n\tPositionY\030\004 \001"
  "(\002\022\021\n\tVelocityX\030\005 \001(\002\022\021\n\tVelocityY\030\006 \001(\002"
  "\"V\n\020SNpcUpdatePacket\022B\n\tCreatures\030\001 \003(\0132"
  "/.Avalon.Network.Packets.Movement.Creatu"
  "rePacketb\006proto3"
  ;
static const ::_pbi::DescriptorTable* const descriptor_table_SNpcUpdatePacket_2eproto_deps[1] = {
  &::descriptor_table_bcl_2eproto,
};
static ::_pbi::once_flag descriptor_table_SNpcUpdatePacket_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_SNpcUpdatePacket_2eproto = {
    false, false, 296, descriptor_table_protodef_SNpcUpdatePacket_2eproto,
    "SNpcUpdatePacket.proto",
    &descriptor_table_SNpcUpdatePacket_2eproto_once, descriptor_table_SNpcUpdatePacket_2eproto_deps, 1, 2,
    schemas, file_default_instances, TableStruct_SNpcUpdatePacket_2eproto::offsets,
    file_level_metadata_SNpcUpdatePacket_2eproto, file_level_enum_descriptors_SNpcUpdatePacket_2eproto,
    file_level_service_descriptors_SNpcUpdatePacket_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_SNpcUpdatePacket_2eproto_getter() {
  return &descriptor_table_SNpcUpdatePacket_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_SNpcUpdatePacket_2eproto(&descriptor_table_SNpcUpdatePacket_2eproto);
namespace Avalon {
namespace Network {
namespace Packets {
namespace Movement {

// ===================================================================

class CreaturePacket::_Internal {
 public:
  static const ::bcl::Guid& id(const CreaturePacket* msg);
};

const ::bcl::Guid&
CreaturePacket::_Internal::id(const CreaturePacket* msg) {
  return *msg->_impl_.id_;
}
void CreaturePacket::clear_id() {
  if (GetArenaForAllocation() == nullptr && _impl_.id_ != nullptr) {
    delete _impl_.id_;
  }
  _impl_.id_ = nullptr;
}
CreaturePacket::CreaturePacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Avalon.Network.Packets.Movement.CreaturePacket)
}
CreaturePacket::CreaturePacket(const CreaturePacket& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  CreaturePacket* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.name_){}
    , decltype(_impl_.id_){nullptr}
    , decltype(_impl_.positionx_){}
    , decltype(_impl_.positiony_){}
    , decltype(_impl_.velocityx_){}
    , decltype(_impl_.velocityy_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.name_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_name().empty()) {
    _this->_impl_.name_.Set(from._internal_name(),
      _this->GetArenaForAllocation());
  }
  if (from._internal_has_id()) {
    _this->_impl_.id_ = new ::bcl::Guid(*from._impl_.id_);
  }
  ::memcpy(&_impl_.positionx_, &from._impl_.positionx_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.velocityy_) -
    reinterpret_cast<char*>(&_impl_.positionx_)) + sizeof(_impl_.velocityy_));
  // @@protoc_insertion_point(copy_constructor:Avalon.Network.Packets.Movement.CreaturePacket)
}

inline void CreaturePacket::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.name_){}
    , decltype(_impl_.id_){nullptr}
    , decltype(_impl_.positionx_){0}
    , decltype(_impl_.positiony_){0}
    , decltype(_impl_.velocityx_){0}
    , decltype(_impl_.velocityy_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.name_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

CreaturePacket::~CreaturePacket() {
  // @@protoc_insertion_point(destructor:Avalon.Network.Packets.Movement.CreaturePacket)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void CreaturePacket::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.name_.Destroy();
  if (this != internal_default_instance()) delete _impl_.id_;
}

void CreaturePacket::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void CreaturePacket::Clear() {
// @@protoc_insertion_point(message_clear_start:Avalon.Network.Packets.Movement.CreaturePacket)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.name_.ClearToEmpty();
  if (GetArenaForAllocation() == nullptr && _impl_.id_ != nullptr) {
    delete _impl_.id_;
  }
  _impl_.id_ = nullptr;
  ::memset(&_impl_.positionx_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.velocityy_) -
      reinterpret_cast<char*>(&_impl_.positionx_)) + sizeof(_impl_.velocityy_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* CreaturePacket::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .bcl.Guid Id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_id(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string Name = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_name();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Avalon.Network.Packets.Movement.CreaturePacket.Name"));
        } else
          goto handle_unusual;
        continue;
      // float PositionX = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 29)) {
          _impl_.positionx_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // float PositionY = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 37)) {
          _impl_.positiony_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // float VelocityX = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 45)) {
          _impl_.velocityx_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // float VelocityY = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 53)) {
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

uint8_t* CreaturePacket::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Avalon.Network.Packets.Movement.CreaturePacket)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // .bcl.Guid Id = 1;
  if (this->_internal_has_id()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, _Internal::id(this),
        _Internal::id(this).GetCachedSize(), target, stream);
  }

  // string Name = 2;
  if (!this->_internal_name().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Avalon.Network.Packets.Movement.CreaturePacket.Name");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_name(), target);
  }

  // float PositionX = 3;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_positionx = this->_internal_positionx();
  uint32_t raw_positionx;
  memcpy(&raw_positionx, &tmp_positionx, sizeof(tmp_positionx));
  if (raw_positionx != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(3, this->_internal_positionx(), target);
  }

  // float PositionY = 4;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_positiony = this->_internal_positiony();
  uint32_t raw_positiony;
  memcpy(&raw_positiony, &tmp_positiony, sizeof(tmp_positiony));
  if (raw_positiony != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(4, this->_internal_positiony(), target);
  }

  // float VelocityX = 5;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_velocityx = this->_internal_velocityx();
  uint32_t raw_velocityx;
  memcpy(&raw_velocityx, &tmp_velocityx, sizeof(tmp_velocityx));
  if (raw_velocityx != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(5, this->_internal_velocityx(), target);
  }

  // float VelocityY = 6;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_velocityy = this->_internal_velocityy();
  uint32_t raw_velocityy;
  memcpy(&raw_velocityy, &tmp_velocityy, sizeof(tmp_velocityy));
  if (raw_velocityy != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(6, this->_internal_velocityy(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Avalon.Network.Packets.Movement.CreaturePacket)
  return target;
}

size_t CreaturePacket::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Avalon.Network.Packets.Movement.CreaturePacket)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string Name = 2;
  if (!this->_internal_name().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_name());
  }

  // .bcl.Guid Id = 1;
  if (this->_internal_has_id()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *_impl_.id_);
  }

  // float PositionX = 3;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_positionx = this->_internal_positionx();
  uint32_t raw_positionx;
  memcpy(&raw_positionx, &tmp_positionx, sizeof(tmp_positionx));
  if (raw_positionx != 0) {
    total_size += 1 + 4;
  }

  // float PositionY = 4;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_positiony = this->_internal_positiony();
  uint32_t raw_positiony;
  memcpy(&raw_positiony, &tmp_positiony, sizeof(tmp_positiony));
  if (raw_positiony != 0) {
    total_size += 1 + 4;
  }

  // float VelocityX = 5;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_velocityx = this->_internal_velocityx();
  uint32_t raw_velocityx;
  memcpy(&raw_velocityx, &tmp_velocityx, sizeof(tmp_velocityx));
  if (raw_velocityx != 0) {
    total_size += 1 + 4;
  }

  // float VelocityY = 6;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_velocityy = this->_internal_velocityy();
  uint32_t raw_velocityy;
  memcpy(&raw_velocityy, &tmp_velocityy, sizeof(tmp_velocityy));
  if (raw_velocityy != 0) {
    total_size += 1 + 4;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData CreaturePacket::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    CreaturePacket::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*CreaturePacket::GetClassData() const { return &_class_data_; }


void CreaturePacket::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<CreaturePacket*>(&to_msg);
  auto& from = static_cast<const CreaturePacket&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Avalon.Network.Packets.Movement.CreaturePacket)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_name().empty()) {
    _this->_internal_set_name(from._internal_name());
  }
  if (from._internal_has_id()) {
    _this->_internal_mutable_id()->::bcl::Guid::MergeFrom(
        from._internal_id());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_positionx = from._internal_positionx();
  uint32_t raw_positionx;
  memcpy(&raw_positionx, &tmp_positionx, sizeof(tmp_positionx));
  if (raw_positionx != 0) {
    _this->_internal_set_positionx(from._internal_positionx());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_positiony = from._internal_positiony();
  uint32_t raw_positiony;
  memcpy(&raw_positiony, &tmp_positiony, sizeof(tmp_positiony));
  if (raw_positiony != 0) {
    _this->_internal_set_positiony(from._internal_positiony());
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

void CreaturePacket::CopyFrom(const CreaturePacket& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Avalon.Network.Packets.Movement.CreaturePacket)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CreaturePacket::IsInitialized() const {
  return true;
}

void CreaturePacket::InternalSwap(CreaturePacket* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.name_, lhs_arena,
      &other->_impl_.name_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(CreaturePacket, _impl_.velocityy_)
      + sizeof(CreaturePacket::_impl_.velocityy_)
      - PROTOBUF_FIELD_OFFSET(CreaturePacket, _impl_.id_)>(
          reinterpret_cast<char*>(&_impl_.id_),
          reinterpret_cast<char*>(&other->_impl_.id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata CreaturePacket::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_SNpcUpdatePacket_2eproto_getter, &descriptor_table_SNpcUpdatePacket_2eproto_once,
      file_level_metadata_SNpcUpdatePacket_2eproto[0]);
}

// ===================================================================

class SNpcUpdatePacket::_Internal {
 public:
};

SNpcUpdatePacket::SNpcUpdatePacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Avalon.Network.Packets.Movement.SNpcUpdatePacket)
}
SNpcUpdatePacket::SNpcUpdatePacket(const SNpcUpdatePacket& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  SNpcUpdatePacket* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.creatures_){from._impl_.creatures_}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:Avalon.Network.Packets.Movement.SNpcUpdatePacket)
}

inline void SNpcUpdatePacket::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.creatures_){arena}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

SNpcUpdatePacket::~SNpcUpdatePacket() {
  // @@protoc_insertion_point(destructor:Avalon.Network.Packets.Movement.SNpcUpdatePacket)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void SNpcUpdatePacket::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.creatures_.~RepeatedPtrField();
}

void SNpcUpdatePacket::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void SNpcUpdatePacket::Clear() {
// @@protoc_insertion_point(message_clear_start:Avalon.Network.Packets.Movement.SNpcUpdatePacket)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.creatures_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* SNpcUpdatePacket::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // repeated .Avalon.Network.Packets.Movement.CreaturePacket Creatures = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_creatures(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
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

uint8_t* SNpcUpdatePacket::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Avalon.Network.Packets.Movement.SNpcUpdatePacket)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .Avalon.Network.Packets.Movement.CreaturePacket Creatures = 1;
  for (unsigned i = 0,
      n = static_cast<unsigned>(this->_internal_creatures_size()); i < n; i++) {
    const auto& repfield = this->_internal_creatures(i);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
        InternalWriteMessage(1, repfield, repfield.GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Avalon.Network.Packets.Movement.SNpcUpdatePacket)
  return target;
}

size_t SNpcUpdatePacket::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Avalon.Network.Packets.Movement.SNpcUpdatePacket)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .Avalon.Network.Packets.Movement.CreaturePacket Creatures = 1;
  total_size += 1UL * this->_internal_creatures_size();
  for (const auto& msg : this->_impl_.creatures_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData SNpcUpdatePacket::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    SNpcUpdatePacket::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*SNpcUpdatePacket::GetClassData() const { return &_class_data_; }


void SNpcUpdatePacket::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<SNpcUpdatePacket*>(&to_msg);
  auto& from = static_cast<const SNpcUpdatePacket&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Avalon.Network.Packets.Movement.SNpcUpdatePacket)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.creatures_.MergeFrom(from._impl_.creatures_);
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void SNpcUpdatePacket::CopyFrom(const SNpcUpdatePacket& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Avalon.Network.Packets.Movement.SNpcUpdatePacket)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SNpcUpdatePacket::IsInitialized() const {
  return true;
}

void SNpcUpdatePacket::InternalSwap(SNpcUpdatePacket* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.creatures_.InternalSwap(&other->_impl_.creatures_);
}

::PROTOBUF_NAMESPACE_ID::Metadata SNpcUpdatePacket::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_SNpcUpdatePacket_2eproto_getter, &descriptor_table_SNpcUpdatePacket_2eproto_once,
      file_level_metadata_SNpcUpdatePacket_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Movement
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Avalon::Network::Packets::Movement::CreaturePacket*
Arena::CreateMaybeMessage< ::Avalon::Network::Packets::Movement::CreaturePacket >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Avalon::Network::Packets::Movement::CreaturePacket >(arena);
}
template<> PROTOBUF_NOINLINE ::Avalon::Network::Packets::Movement::SNpcUpdatePacket*
Arena::CreateMaybeMessage< ::Avalon::Network::Packets::Movement::SNpcUpdatePacket >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Avalon::Network::Packets::Movement::SNpcUpdatePacket >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
