#pragma once

#include <p2psc/message/types.h>
#include <p2psc/version.h>
#include <spotify/json.hpp>

namespace p2psc {
namespace message {

struct AnonymousMessageFormat {
  message::MessageType type;
};
}
}

namespace spotify {
namespace json {
template <> struct default_codec_t<p2psc::message::AnonymousMessageFormat> {
  static codec::object_t<p2psc::message::AnonymousMessageFormat> codec() {
    auto codec = codec::object<p2psc::message::AnonymousMessageFormat>();
    codec.required("type", &p2psc::message::AnonymousMessageFormat::type);
    return codec;
  }
};
}
}