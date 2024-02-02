// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SOpenChatPacket.proto

#include "SOpenChatPacket.pb.h"

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
PROTOBUF_CONSTEXPR SOpenChatPacket::SOpenChatPacket(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.clientid_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct SOpenChatPacketDefaultTypeInternal {
  PROTOBUF_CONSTEXPR SOpenChatPacketDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~SOpenChatPacketDefaultTypeInternal() {}
  union {
    SOpenChatPacket _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 SOpenChatPacketDefaultTypeInternal _SOpenChatPacket_default_instance_;
}  // namespace Social
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
static ::_pb::Metadata file_level_metadata_SOpenChatPacket_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_SOpenChatPacket_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_SOpenChatPacket_2eproto = nullptr;

const uint32_t TableStruct_SOpenChatPacket_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Social::SOpenChatPacket, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Social::SOpenChatPacket, _impl_.clientid_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Avalon::Network::Packets::Social::SOpenChatPacket)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::Avalon::Network::Packets::Social::_SOpenChatPacket_default_instance_._instance,
};

const char descriptor_table_protodef_SOpenChatPacket_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\025SOpenChatPacket.proto\022\035Avalon.Network."
  "Packets.Social\"#\n\017SOpenChatPacket\022\020\n\010Cli"
  "entId\030\001 \001(\tb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_SOpenChatPacket_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_SOpenChatPacket_2eproto = {
    false, false, 99, descriptor_table_protodef_SOpenChatPacket_2eproto,
    "SOpenChatPacket.proto",
    &descriptor_table_SOpenChatPacket_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_SOpenChatPacket_2eproto::offsets,
    file_level_metadata_SOpenChatPacket_2eproto, file_level_enum_descriptors_SOpenChatPacket_2eproto,
    file_level_service_descriptors_SOpenChatPacket_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_SOpenChatPacket_2eproto_getter() {
  return &descriptor_table_SOpenChatPacket_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_SOpenChatPacket_2eproto(&descriptor_table_SOpenChatPacket_2eproto);
namespace Avalon {
namespace Network {
namespace Packets {
namespace Social {

// ===================================================================

class SOpenChatPacket::_Internal {
 public:
};

SOpenChatPacket::SOpenChatPacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Avalon.Network.Packets.Social.SOpenChatPacket)
}
SOpenChatPacket::SOpenChatPacket(const SOpenChatPacket& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  SOpenChatPacket* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.clientid_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.clientid_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.clientid_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_clientid().empty()) {
    _this->_impl_.clientid_.Set(from._internal_clientid(), 
      _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:Avalon.Network.Packets.Social.SOpenChatPacket)
}

inline void SOpenChatPacket::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.clientid_){}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.clientid_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.clientid_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

SOpenChatPacket::~SOpenChatPacket() {
  // @@protoc_insertion_point(destructor:Avalon.Network.Packets.Social.SOpenChatPacket)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void SOpenChatPacket::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.clientid_.Destroy();
}

void SOpenChatPacket::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void SOpenChatPacket::Clear() {
// @@protoc_insertion_point(message_clear_start:Avalon.Network.Packets.Social.SOpenChatPacket)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.clientid_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* SOpenChatPacket::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string ClientId = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_clientid();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Avalon.Network.Packets.Social.SOpenChatPacket.ClientId"));
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

uint8_t* SOpenChatPacket::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Avalon.Network.Packets.Social.SOpenChatPacket)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string ClientId = 1;
  if (!this->_internal_clientid().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_clientid().data(), static_cast<int>(this->_internal_clientid().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Avalon.Network.Packets.Social.SOpenChatPacket.ClientId");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_clientid(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Avalon.Network.Packets.Social.SOpenChatPacket)
  return target;
}

size_t SOpenChatPacket::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Avalon.Network.Packets.Social.SOpenChatPacket)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string ClientId = 1;
  if (!this->_internal_clientid().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_clientid());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData SOpenChatPacket::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    SOpenChatPacket::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*SOpenChatPacket::GetClassData() const { return &_class_data_; }


void SOpenChatPacket::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<SOpenChatPacket*>(&to_msg);
  auto& from = static_cast<const SOpenChatPacket&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Avalon.Network.Packets.Social.SOpenChatPacket)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_clientid().empty()) {
    _this->_internal_set_clientid(from._internal_clientid());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void SOpenChatPacket::CopyFrom(const SOpenChatPacket& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Avalon.Network.Packets.Social.SOpenChatPacket)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SOpenChatPacket::IsInitialized() const {
  return true;
}

void SOpenChatPacket::InternalSwap(SOpenChatPacket* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.clientid_, lhs_arena,
      &other->_impl_.clientid_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata SOpenChatPacket::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_SOpenChatPacket_2eproto_getter, &descriptor_table_SOpenChatPacket_2eproto_once,
      file_level_metadata_SOpenChatPacket_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Social
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Avalon::Network::Packets::Social::SOpenChatPacket*
Arena::CreateMaybeMessage< ::Avalon::Network::Packets::Social::SOpenChatPacket >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Avalon::Network::Packets::Social::SOpenChatPacket >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
