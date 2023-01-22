#pragma once

#include <concepts>

#include "lib/util/crtp.hpp"
#include "lib/util/serialization.hpp"

#include "lib/itc/domain.hpp"
#include "lib/itc/executor.hpp"
#include "lib/itc/persistance/persistance.hpp"
#include "lib/itc/services/context.hpp"
#include "lib/itc/services/service.hpp"

namespace otto::itc {
  /// The concept that state types need to fulfill.
  ///
  /// Semiregular means copyable and default constructible
  template<typename T>
  concept AState = std::semiregular<T>;

  // Forward Declarations

  template<AState State>
  struct StateProvider;

  template<AState State>
  struct StateAccessor;

  /// Sends state to multiple Consumers through a Channel
  template<AState... States>
  struct Producer;

  /// Receives state from a single producer through a Channel
  template<AState... States>
  struct Consumer;

  template<AState State>
  struct state_service {
    using provider_t = StateProvider<State>;
    using accessor_t = StateAccessor<State>;
  };

  /// The global maximum number of domains
  constexpr std::size_t max_domains = 4;

  namespace details {
    template<typename Derived, AState State>
    struct CondPersistent {
      CondPersistent(Context&) noexcept {}
    };

    template<typename Derived, AState State>
    requires(util::ASerializable<State>) struct CondPersistent<Derived, State>
      : util::crtp<Derived, CondPersistent<Derived, State>>, Persistant {
      CondPersistent(Context& ctx) noexcept : Persistant(ctx, util::qualified_name_of<State>) {}

      void serialize_into(json::value& json) const override
      {
        const auto& e = this->derived().producer_entry_;
        // TODO: Should be locked. cannot because of const. Should we const cast, or what are the options?
        util::serialize_into(json, e.state);
      }

      void deserialize_from(const json::value& json) override
      {
        auto& e = this->derived().producer_entry_;
        auto l = std::scoped_lock(e.lock);
        util::deserialize_from(json, e.state);
        this->derived().commit();
      }
    };
  } // namespace details

  template<AState State>
  struct StateProvider final : Provider<state_service<State>>, details::CondPersistent<StateProvider<State>, State> {
    StateProvider(Context& context)
      : Provider<state_service<State>>(context), details::CondPersistent<StateProvider<State>, State>(context)
    {}

    void register_producer(Producer<State>& producer)
    {
      if (producer_entry_.executor == nullptr) {
        producer_entry_.executor = &producer.executor();
      } else {
        OTTO_ASSERT(&producer.executor() == producer_entry_.executor);
      }
      producer.state_ = &producer_entry_.state;
    }

    void register_consumer(Consumer<State>& consumer)
    {
      consumer.state_ = &entry(&consumer.executor()).state;
    }

    void commit()
    {
      for (Entry& e : state_copies_) {
        {
          auto l = std::scoped_lock(e.lock);
          e.tmp_state = producer_entry_.state;
        }
      }
      for (Entry& e : state_copies_) {
        e.executor.load()->execute([&e] {
          {
            auto l = std::scoped_lock(e.lock);
            e.state = std::move(e.tmp_state);
          }
        });
      }

      for (StateAccessor<State>* acc : Provider<state_service<State>>::accessors()) {
        acc->executor().execute([acc] { acc->on_state_change(acc->state()); });
      }
    }

  private:
    struct Entry {
      Entry(IExecutor* e) : executor(e) {}
      std::atomic<IExecutor*> executor;
      std::mutex lock = {};
      State state = {};
      State tmp_state = {};
    };

    Entry& entry(IExecutor* exec)
    {
      if (exec == producer_entry_.executor) return producer_entry_;
      auto found =
        std::find_if(state_copies_.begin(), state_copies_.end(), [exec](Entry& e) { return e.executor == exec; });
      if (found == state_copies_.end()) {
        auto x = state_copies_.emplace_back(exec);
        if (!x) {
          LOGC("Tried to add state copy with full vector. Are there more than {} domains?", max_domains);
          std::terminate();
        }
        (*x)->state = producer_entry_.state;
      }
      return *found;
    }

    friend StateAccessor<State>;
    friend details::CondPersistent<StateProvider<State>, State>;
    std::atomic_int ref_count = 0;

    util::local_vector<Entry, max_domains> state_copies_;
    Entry producer_entry_ = Entry(nullptr);
  };

  template<AState State>
  struct StateAccessor : virtual IDomain, Accessor<state_service<State>> {
    StateAccessor(Context& ctx) : Accessor<state_service<State>>(ensure_provider(ctx)) {}

    ~StateAccessor() noexcept override
    {
      auto* prov = this->provider();
      if (prov) {
        prov->ref_count--;
        if (prov->ref_count <= 0) {
          LOGD("Destructing provider for state {}", util::qualified_name_of<State>);
          delete prov;
        }
      }
    };
    StateAccessor(const StateAccessor&) = delete;
    StateAccessor& operator=(const StateAccessor&) = delete;

    const State& state() const noexcept
    {
      const_cast<StateAccessor<State>*>(this)->ensure_state();
      return *state_;
    }

    /// Hook called immediately after the state is updated.
    ///
    /// The parameter is the same as `this->state()`
    ///
    /// Override in subclass if needed
    virtual void on_state_change(const State& state) noexcept {}

  private:
    static Context& ensure_provider(Context& ctx) noexcept
    {
      auto* prov = ctx.provider_of<state_service<State>>();
      if (!prov) {
        LOGD("Constructing new provider for state {}", util::qualified_name_of<State>);
        prov = new StateProvider<State>(ctx);
      }
      prov->ref_count++;
      return ctx;
    }

    void ensure_state() noexcept
    {
      // These should be called in the constructor, but since domains use virtual inheritance, the domain is not yet
      // available on construction
      if (state_ == nullptr) {
        if (this->provider() == nullptr) {
          LOGE("ensure_state called on a state accessor for {} with no provider available. This is a logic error.",
               util::qualified_name_of<State>);
        }
        if (auto* p = dynamic_cast<Producer<State>*>(this); p) {
          this->provider()->register_producer(*p);
        } else {
          this->provider()->register_consumer(*static_cast<Consumer<State>*>(this));
        }
      }
    }

    friend StateProvider<State>;
    friend Producer<State>;
    State* state_ = nullptr;
  };


} // namespace otto::itc
