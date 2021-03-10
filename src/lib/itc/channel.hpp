#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "lib/util/concepts.hpp"
#include "lib/util/exception.hpp"
#include "lib/util/name_of.hpp"
#include "lib/util/ranges.hpp"
#include "lib/util/serialization.hpp"

#include "event.hpp"

namespace otto::itc {

  namespace detail {
    struct SenderBase : util::ISerializable {
      virtual ~SenderBase() = default;
    };
    struct ReceiverBase {
      virtual ~ReceiverBase() = default;
    };
  } // namespace detail

  /// Helper struct to make friendship for link helper functions easier
  struct linker {
    template<AnEvent E>
    static void link(Sender<E>& s, Receiver<E>& r)
    {
      if (r.sender_ != nullptr) {
        unlink(*r.sender_, r);
      }
      s.receivers_.emplace_back(&r);
      r.sender_ = &s;
    }

    template<AnEvent E>
    static void unlink(Sender<E>& s, Receiver<E>& r)
    {
      std::erase(s.receivers_, &r);
      r.sender_ = nullptr;
    }
  };

  /// A channel tree where senders and receivers for any event type can be created and accessed
  struct Channel : util::ISerializable {
    Channel() = default;
    ~Channel() = default;

    Channel(Channel&&) = default;
    Channel& operator=(Channel&&) = default;

    Channel(const Channel&) = delete;
    Channel& operator=(const Channel&) = delete;

    /// Access or create a nested channel group by name
    Channel& operator[](std::string_view sv)
    {
      // Apparently transparent keys don't work in gcc for string_view/string
      // TODO: Look into that ^
      auto found = children_.find(std::string(sv));
      if (found == children_.end()) {
        auto [iter, inserted] = children_.emplace(sv, std::make_unique<Channel>());
        iter->second->parent_ = this;
        found = iter;
      }
      return *found->second;
    }

    void serialize_into(json::value& json) const final
    {
      using namespace std::literals;
      for (const auto& [k, v] : children_) {
        util::serialize_into(json[k], *v);
      }
      for (const auto& [k, v] : senders_) {
        util::serialize_into(json["type:"s + k.c_str()], *v);
      }
    }

    void deserialize_from(const json::value& json) final
    {
      using namespace std::literals;
      for (auto& [k, v] : children_) {
        util::deserialize_from_member(json, k, *v);
      }
      for (const auto& [k, v] : senders_) {
        util::deserialize_from_member(json, "type:"s + k.c_str(), *v);
      }
    }

    template<AnEvent E>
    Sender<E>* find_sender()
    {
      auto found = senders_.find(key_of<E>());
      if (found != senders_.end()) {
        return static_cast<Sender<E>*>(found->second);
      }
      if (parent_ != nullptr) {
        return parent_->find_sender<E>();
      }
      return nullptr;
    }

  private:
    template<AnEvent...>
    friend struct Sender;
    template<AnEvent...>
    friend struct Receiver;

    template<AnEvent E>
    static constexpr util::string_ref key_of() noexcept
    {
      return util::qualified_name_of<E>;
    }

    /// Called from Sender constructor
    template<AnEvent E>
    void register_sender(Sender<E>* sender)
    {
      auto [iter, inserted] = senders_.emplace(key_of<E>(), sender);
      if (!inserted) {
        throw util::exception("Existing sender found for event {}", key_of<E>());
      }
      register_sender_recurse(sender);
    }
    template<AnEvent E>
    void register_sender_recurse(Sender<E>* sender)
    {
      for (auto [k, r] : util::equal_range(receivers_, key_of<E>())) {
        linker::link(*sender, *static_cast<Receiver<E>*>(r));
      }
      for (auto&& [k, child] : children_) {
        child->register_sender_recurse(sender);
      }
    }

    template<AnEvent E>
    void unregister_sender(Sender<E>* sender)
    {
      auto found = std::ranges::find(senders_, sender, [](auto& pair) { return pair.second; });
      senders_.erase(found);
      for (Receiver<E>* r : sender->receivers()) {
        linker::unlink(*sender, *r);
      }
    }

    template<AnEvent E>
    void register_receiver(Receiver<E>* receiver)
    {
      receivers_.emplace(key_of<E>(), receiver);
      auto* s = find_sender<E>();
      if (s) linker::link(*s, *receiver);
    }

    template<AnEvent E>
    void unregister_receiver(Receiver<E>* receiver)
    {
      auto receivers = util::equal_range(receivers_, key_of<E>());
      auto found = std::ranges::find(receivers, receiver, [](auto& pair) { return pair.second; });
      receivers_.erase(found);
      if (receiver->sender()) {
        linker::unlink(*receiver->sender(), *receiver);
      }
    }

    Channel* parent_ = nullptr;
    std::unordered_map<std::string, std::unique_ptr<Channel>> children_;
    std::unordered_map<util::string_ref, detail::SenderBase*> senders_;
    std::unordered_multimap<util::string_ref, detail::ReceiverBase*> receivers_;
  };

} // namespace otto::itc
