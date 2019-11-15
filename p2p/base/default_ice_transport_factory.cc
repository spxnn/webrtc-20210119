/*
 *  Copyright 2019 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "p2p/base/default_ice_transport_factory.h"

#include <utility>

namespace webrtc {

DefaultIceTransport::DefaultIceTransport(
    std::unique_ptr<cricket::P2PTransportChannel> internal)
    : internal_(std::move(internal)) {}

DefaultIceTransport::~DefaultIceTransport() {
  RTC_DCHECK_RUN_ON(&thread_checker_);
}

rtc::scoped_refptr<IceTransportInterface>
DefaultIceTransportFactory::CreateIceTransport(
    const std::string& transport_name,
    int component,
    IceTransportInit init) {
  return new rtc::RefCountedObject<DefaultIceTransport>(
      std::make_unique<cricket::P2PTransportChannel>(
          transport_name, component, init.port_allocator(),
          init.async_resolver_factory(), init.event_log()));
}

}  // namespace webrtc