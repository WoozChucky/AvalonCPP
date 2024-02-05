// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CAudioRecordPacket.proto

#include <Proto/CAudioRecordPacket.pb.h>

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
namespace Audio {
PROTOBUF_CONSTEXPR CAudioRecordPacket::CAudioRecordPacket(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.soundbuffer_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct CAudioRecordPacketDefaultTypeInternal {
  PROTOBUF_CONSTEXPR CAudioRecordPacketDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~CAudioRecordPacketDefaultTypeInternal() {}
  union {
    CAudioRecordPacket _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 CAudioRecordPacketDefaultTypeInternal _CAudioRecordPacket_default_instance_;
}  // namespace Audio
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
static ::_pb::Metadata file_level_metadata_CAudioRecordPacket_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_CAudioRecordPacket_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_CAudioRecordPacket_2eproto = nullptr;

const uint32_t TableStruct_CAudioRecordPacket_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Audio::CAudioRecordPacket, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Audio::CAudioRecordPacket, _impl_.soundbuffer_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Avalon::Network::Packets::Audio::CAudioRecordPacket)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::Avalon::Network::Packets::Audio::_CAudioRecordPacket_default_instance_._instance,
};

const char descriptor_table_protodef_CAudioRecordPacket_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\030CAudioRecordPacket.proto\022\034Avalon.Netwo"
  "rk.Packets.Audio\")\n\022CAudioRecordPacket\022\023"
  "\n\013SoundBuffer\030\001 \001(\014b\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_CAudioRecordPacket_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_CAudioRecordPacket_2eproto = {
    false, false, 107, descriptor_table_protodef_CAudioRecordPacket_2eproto,
    "CAudioRecordPacket.proto",
    &descriptor_table_CAudioRecordPacket_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_CAudioRecordPacket_2eproto::offsets,
    file_level_metadata_CAudioRecordPacket_2eproto, file_level_enum_descriptors_CAudioRecordPacket_2eproto,
    file_level_service_descriptors_CAudioRecordPacket_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_CAudioRecordPacket_2eproto_getter() {
  return &descriptor_table_CAudioRecordPacket_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_CAudioRecordPacket_2eproto(&descriptor_table_CAudioRecordPacket_2eproto);
namespace Avalon {
namespace Network {
namespace Packets {
namespace Audio {

// ===================================================================

class CAudioRecordPacket::_Internal {
 public:
};

CAudioRecordPacket::CAudioRecordPacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Avalon.Network.Packets.Audio.CAudioRecordPacket)
}
CAudioRecordPacket::CAudioRecordPacket(const CAudioRecordPacket& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  CAudioRecordPacket* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.soundbuffer_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.soundbuffer_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.soundbuffer_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_soundbuffer().empty()) {
    _this->_impl_.soundbuffer_.Set(from._internal_soundbuffer(),
      _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:Avalon.Network.Packets.Audio.CAudioRecordPacket)
}

inline void CAudioRecordPacket::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.soundbuffer_){}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.soundbuffer_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.soundbuffer_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

CAudioRecordPacket::~CAudioRecordPacket() {
  // @@protoc_insertion_point(destructor:Avalon.Network.Packets.Audio.CAudioRecordPacket)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void CAudioRecordPacket::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.soundbuffer_.Destroy();
}

void CAudioRecordPacket::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void CAudioRecordPacket::Clear() {
// @@protoc_insertion_point(message_clear_start:Avalon.Network.Packets.Audio.CAudioRecordPacket)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.soundbuffer_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* CAudioRecordPacket::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // bytes SoundBuffer = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_soundbuffer();
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

uint8_t* CAudioRecordPacket::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Avalon.Network.Packets.Audio.CAudioRecordPacket)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // bytes SoundBuffer = 1;
  if (!this->_internal_soundbuffer().empty()) {
    target = stream->WriteBytesMaybeAliased(
        1, this->_internal_soundbuffer(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Avalon.Network.Packets.Audio.CAudioRecordPacket)
  return target;
}

size_t CAudioRecordPacket::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Avalon.Network.Packets.Audio.CAudioRecordPacket)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes SoundBuffer = 1;
  if (!this->_internal_soundbuffer().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_soundbuffer());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData CAudioRecordPacket::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    CAudioRecordPacket::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*CAudioRecordPacket::GetClassData() const { return &_class_data_; }


void CAudioRecordPacket::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<CAudioRecordPacket*>(&to_msg);
  auto& from = static_cast<const CAudioRecordPacket&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Avalon.Network.Packets.Audio.CAudioRecordPacket)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_soundbuffer().empty()) {
    _this->_internal_set_soundbuffer(from._internal_soundbuffer());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void CAudioRecordPacket::CopyFrom(const CAudioRecordPacket& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Avalon.Network.Packets.Audio.CAudioRecordPacket)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CAudioRecordPacket::IsInitialized() const {
  return true;
}

void CAudioRecordPacket::InternalSwap(CAudioRecordPacket* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.soundbuffer_, lhs_arena,
      &other->_impl_.soundbuffer_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata CAudioRecordPacket::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_CAudioRecordPacket_2eproto_getter, &descriptor_table_CAudioRecordPacket_2eproto_once,
      file_level_metadata_CAudioRecordPacket_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Audio
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Avalon::Network::Packets::Audio::CAudioRecordPacket*
Arena::CreateMaybeMessage< ::Avalon::Network::Packets::Audio::CAudioRecordPacket >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Avalon::Network::Packets::Audio::CAudioRecordPacket >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>