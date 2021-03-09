#pragma once

#include <memory>
#include <type_traits>

namespace otto::util {

  template<typename Interface, std::size_t SBOsize = std::min(std::size_t(24), sizeof(Interface))>
  requires(SBOsize >= sizeof(std::unique_ptr<Interface>)) //
    struct Component {
    using deleter = std::default_delete<Interface>;
    constexpr static std::size_t small_buffer_size = SBOsize;
    enum struct StorageKind : std::uint8_t { pointer, small_buffer, unique_ptr };

    template<std::derived_from<Interface> T, typename... Args>
    requires std::is_constructible_v<T, Args...> Component(std::in_place_type_t<T>, Args&&... args)
    {
      if constexpr (sizeof(T) <= SBOsize) {
        storage_kind_ = StorageKind::small_buffer;
        std::construct_at<T>(static_cast<T*>(get_storage_as<StorageKind::small_buffer>()), std::forward<Args>(args)...);
      } else {
        storage_kind_ = StorageKind::unique_ptr;
        std::construct_at<std::unique_ptr<Interface>>(get_storage_as<StorageKind::unique_ptr>(),
                                                      std::make_unique<T>(std::forward<Args>(args)...));
      }
    }

    Component(std::unique_ptr<Interface>&& ptr) : storage_kind_(StorageKind::unique_ptr)
    {
      std::construct_at<std::unique_ptr<Interface>>(get_storage_as<StorageKind::unique_ptr>(), std::move(ptr));
    }

    template<std::derived_from<Interface> T>
    Component(std::reference_wrapper<T> ptr) : storage_kind_(StorageKind::pointer)
    {
      std::construct_at<Interface*>(get_storage_as<StorageKind::pointer>(), &ptr.get());
    }

    ~Component() noexcept
    {
      if (storage_kind_ == StorageKind::small_buffer) {
        std::destroy_at(get_storage_as<StorageKind::small_buffer>());
      } else if (storage_kind_ == StorageKind::unique_ptr) {
        std::destroy_at(get_storage_as<StorageKind::unique_ptr>());
      }
    }

    Component(const Component& rhs) = delete;
    Component(Component&& rhs) = delete;
    Component& operator=(const Component& rhs) = delete;
    Component& operator=(Component&& rhs) = delete;

    Interface* get() noexcept
    {
      if (storage_kind_ == StorageKind::pointer) {
        return *get_storage_as<StorageKind::pointer>();
      }
      if (storage_kind_ == StorageKind::small_buffer) {
        return get_storage_as<StorageKind::small_buffer>();
      }
      if (storage_kind_ == StorageKind::unique_ptr) {
        return get_storage_as<StorageKind::unique_ptr>()->get();
      }
    }

    const Interface* get() const noexcept
    {
      if (storage_kind_ == StorageKind::pointer) {
        return *get_storage_as<StorageKind::pointer>();
      }
      if (storage_kind_ == StorageKind::small_buffer) {
        return get_storage_as<StorageKind::small_buffer>();
      }
      if (storage_kind_ == StorageKind::unique_ptr) {
        return get_storage_as<StorageKind::unique_ptr>()->get();
      }
    }

    Interface* operator->() noexcept
    {
      return get();
    }

    const Interface* operator->() const noexcept
    {
      return get();
    }

    Interface& operator*() noexcept
    {
      return get();
    }

    const Interface& operator*() const noexcept
    {
      return get();
    }

  private:
    template<StorageKind SK>
    auto* get_storage_as()
    {
      if constexpr (SK == StorageKind::pointer) {
        return std::launder(reinterpret_cast<Interface**>(&storage_)); // NOLINT
      } else if constexpr (SK == StorageKind::small_buffer) {
        return std::launder(reinterpret_cast<Interface*>(&storage_)); // NOLINT
      } else if constexpr (SK == StorageKind::unique_ptr) {
        return std::launder(reinterpret_cast<std::unique_ptr<Interface>*>(&storage_)); // NOLINT
      }
    }

    template<StorageKind SK>
    auto* get_storage_as() const
    {
      if constexpr (SK == StorageKind::pointer) {
        return std::launder(reinterpret_cast<Interface** const>(&storage_)); // NOLINT
      } else if constexpr (SK == StorageKind::small_buffer) {
        return std::launder(reinterpret_cast<Interface* const>(&storage_)); // NOLINT
      } else if constexpr (SK == StorageKind::unique_ptr) {
        return std::launder(reinterpret_cast<std::unique_ptr<Interface>* const>(&storage_)); // NOLINT
      }
    }

    StorageKind storage_kind_;
    std::aligned_storage<SBOsize> storage_;
  };

} // namespace otto::util
