#include "event_manager.hpp"

namespace otto::services {
  EventManager& EventManager::get()
  {
    static EventManager* pInstance;

    if (!pInstance) {
      pInstance = new EventManager();
    }

    return *pInstance;
  }
} // namespace otto::events