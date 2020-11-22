#pragma once

#include "channel.hpp"
#include "consumer.hpp"
#include "producer.hpp"
#include "state.hpp"

/// A State-based inter-thread communication library.
///
/// A single `Producer` can send a new `State` object to multiple `Channels`, which in
/// turn pass it on to multiple `Consumers` which receive the state on some `Executor`
///
/// State is intended to be little more than a simple `POD`-style struct, and it is up
/// to the individual consumers to determine which members have actually changed if they
/// require so.
namespace otto::itc {} // namespace otto::itc
