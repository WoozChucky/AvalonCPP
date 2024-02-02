// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CRegisterPacket.proto

#include "CRegisterPacket.pb.h"

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
namespace Auth {
PROTOBUF_CONSTEXPR CRegisterPacket::CRegisterPacket(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.username_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.password_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct CRegisterPacketDefaultTypeInternal {
  PROTOBUF_CONSTEXPR CRegisterPacketDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~CRegisterPacketDefaultTypeInternal() {}
  union {
    CRegisterPacket _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 CRegisterPacketDefaultTypeInternal _CRegisterPacket_default_instance_;
}  // namespace Auth
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
static ::_pb::Metadata file_level_metadata_CRegisterPacket_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_CRegisterPacket_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_CRegisterPacket_2eproto = nullptr;

const uint32_t TableStruct_CRegisterPacket_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Auth::CRegisterPacket, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Auth::CRegisterPacket, _impl_.username_),
  PROTOBUF_FIELD_OFFSET(::Avalon::Network::Packets::Auth::CRegisterPacket, _impl_.password_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Avalon::Network::Packets::Auth::CRegisterPacket)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::Avalon::Network::Packets::Auth::_CRegisterPacket_default_instance_._instance,
};

const char descriptor_table_protodef_CRegisterPacket_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\025CRegisterPacket.proto\022\033Avalon.Network."
  "Packets.Auth\"5\n\017CRegisterPacket\022\020\n\010Usern"
  "ame\030\001 \001(\t\022\020\n\010Password\030\002 \001(\tb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_CRegisterPacket_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_CRegisterPacket_2eproto = {
    false, false, 115, descriptor_table_protodef_CRegisterPacket_2eproto,
    "CRegisterPacket.proto",
    &descriptor_table_CRegisterPacket_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_CRegisterPacket_2eproto::offsets,
    file_level_metadata_CRegisterPacket_2eproto, file_level_enum_descriptors_CRegisterPacket_2eproto,
    file_level_service_descriptors_CRegisterPacket_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_CRegisterPacket_2eproto_getter() {
  return &descriptor_table_CRegisterPacket_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_CRegisterPacket_2eproto(&descriptor_table_CRegisterPacket_2eproto);
namespace Avalon {
namespace Network {
namespace Packets {
namespace Auth {

// ===================================================================

class CRegisterPacket::_Internal {
 public:
};

CRegisterPacket::CRegisterPacket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Avalon.Network.Packets.Auth.CRegisterPacket)
}
CRegisterPacket::CRegisterPacket(const CRegisterPacket& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  CRegisterPacket* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.username_){}
    , decltype(_impl_.password_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.username_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.username_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_username().empty()) {
    _this->_impl_.username_.Set(from._internal_username(), 
      _this->GetArenaForAllocation());
  }
  _impl_.password_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.password_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_password().empty()) {
    _this->_impl_.password_.Set(from._internal_password(), 
      _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:Avalon.Network.Packets.Auth.CRegisterPacket)
}

inline void CRegisterPacket::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.username_){}
    , decltype(_impl_.password_){}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.username_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.username_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.password_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.password_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

CRegisterPacket::~CRegisterPacket() {
  // @@protoc_insertion_point(destructor:Avalon.Network.Packets.Auth.CRegisterPacket)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void CRegisterPacket::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.username_.Destroy();
  _impl_.password_.Destroy();
}

void CRegisterPacket::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void CRegisterPacket::Clear() {
// @@protoc_insertion_point(message_clear_start:Avalon.Network.Packets.Auth.CRegisterPacket)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.username_.ClearToEmpty();
  _impl_.password_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* CRegisterPacket::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string Username = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_username();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Avalon.Network.Packets.Auth.CRegisterPacket.Username"));
        } else
          goto handle_unusual;
        continue;
      // string Password = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_password();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Avalon.Network.Packets.Auth.CRegisterPacket.Password"));
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

uint8_t* CRegisterPacket::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Avalon.Network.Packets.Auth.CRegisterPacket)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string Username = 1;
  if (!this->_internal_username().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_username().data(), static_cast<int>(this->_internal_username().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Avalon.Network.Packets.Auth.CRegisterPacket.Username");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_username(), target);
  }

  // string Password = 2;
  if (!this->_internal_password().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_password().data(), static_cast<int>(this->_internal_password().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Avalon.Network.Packets.Auth.CRegisterPacket.Password");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_password(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Avalon.Network.Packets.Auth.CRegisterPacket)
  return target;
}

size_t CRegisterPacket::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Avalon.Network.Packets.Auth.CRegisterPacket)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string Username = 1;
  if (!this->_internal_username().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_username());
  }

  // string Password = 2;
  if (!this->_internal_password().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_password());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData CRegisterPacket::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    CRegisterPacket::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*CRegisterPacket::GetClassData() const { return &_class_data_; }


void CRegisterPacket::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<CRegisterPacket*>(&to_msg);
  auto& from = static_cast<const CRegisterPacket&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Avalon.Network.Packets.Auth.CRegisterPacket)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_username().empty()) {
    _this->_internal_set_username(from._internal_username());
  }
  if (!from._internal_password().empty()) {
    _this->_internal_set_password(from._internal_password());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void CRegisterPacket::CopyFrom(const CRegisterPacket& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Avalon.Network.Packets.Auth.CRegisterPacket)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CRegisterPacket::IsInitialized() const {
  return true;
}

void CRegisterPacket::InternalSwap(CRegisterPacket* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.username_, lhs_arena,
      &other->_impl_.username_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.password_, lhs_arena,
      &other->_impl_.password_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata CRegisterPacket::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_CRegisterPacket_2eproto_getter, &descriptor_table_CRegisterPacket_2eproto_once,
      file_level_metadata_CRegisterPacket_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Auth
}  // namespace Packets
}  // namespace Network
}  // namespace Avalon
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Avalon::Network::Packets::Auth::CRegisterPacket*
Arena::CreateMaybeMessage< ::Avalon::Network::Packets::Auth::CRegisterPacket >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Avalon::Network::Packets::Auth::CRegisterPacket >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
