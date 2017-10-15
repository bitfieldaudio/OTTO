// Use the c++17 filesystem, with the TS as fallback
#if __has_include(<filesystem>)

#include <filesystem>
namespace filesystem = std::filesystem;

#elif __has_include(<experimental/filesystem>)

#include <experimental/filesystem>
namespace filesystem = std::experimental::filesystem;

#else

#error "stdlib has no filesystem implementation"

#endif

namespace otto {
  namespace fs = filesystem;
}
