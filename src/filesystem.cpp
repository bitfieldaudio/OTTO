#include "filesystem.hpp"

#include <cstring>
#include <cerrno>

#include "util/algorithm.hpp"
#include "util/iterator.hpp"

#if defined(_WIN32)
# include <windows.h>
#else
# include <unistd.h>
# include <dirent.h>
#endif

#if defined(__linux)
# include <linux/limits.h>
#endif

#if !defined(_WIN32)
#define IS_POSIX 1
#define IS_WIN32 0
#else
#define IS_POSIX 0
#define IS_WIN32 1
#endif

namespace otto::filesystem {

// Utility functions //////////////////////////////////////////////////////////

  namespace {

    #if IS_POSIX
    path::string_type separators = "/\\";
    #else
    path::string_type separators = "\\/";
    #endif

    path::format detect_format(const path::string_type& s)
    {
      return path::generic_format;
    }

    bool is_separator(path::value_type c)
    {
      return util::any_of(separators, [c] (char s) { return c == s; });
    }
  }

  using StringView = std::basic_string_view<path::value_type>;

// otto::filesystem::path /////////////////////////////////////////////////////

  // 30.10.7.4.1, constructors and destructor

  path::path() noexcept = default;
  
  path::path(const path& p) = default;
  
  path::path(path&& p) noexcept = default;
  
  path::path(string_type&& source, format fmt)
    : _path (std::move(source)), _format (fmt)
  {
  }

  path::~path() = default;
  

  // 30.10.7.4.2, assignments
  
  path& path::operator=(const path& p) = default;
  
  path& path::operator=(path&& p) noexcept = default;
  
  path& path::operator=(string_type&& source)
  {
    assign(std::move(source));
    return *this;
  }
  

  path& path::assign(string_type&& source)
  {
    _format = detect_format(source);
    _path = std::move(source);
    return *this;
  }
  

  // 30.10.7.4.3, appends

  path& path::operator/=(const path& p)
  {
    if (p.is_absolute() || (p.has_root_name()
        && p.root_name() != root_name())) {
      assign(p);
    } else {
      if (has_filename()) {
        _path.push_back(preferred_separator);
      }
      _path.append(p);
    }
    return *this;
  }

  // 30.10.7.4.4, concatenation
  path& path::operator+=(const path& x)
  {
    _path.append(x.native());
    return *this;
  }
  
  path& path::operator+=(const string_type& x)
  {
    _path.append(path(x).native());
    return *this;
  }
  
  path& path::operator+=(std::basic_string_view<value_type> x)
  {
    _path.append(x);
    return *this;
  }
  
  path& path::operator+=(const value_type* x)
  {
    _path.append(x);
    return *this;
  }
  
  path& path::operator+=(value_type x)
  {
    _path.push_back(x);
    return *this;
  }

  // 30.10.7.4.5, modifiers
  void path::clear() noexcept
  {
    _path.clear();
  }
  
  path& path::make_preferred()
  {
    // Nothing to do on posix
    return *this;
  }
  
  path& path::remove_filename()
  {
    make_preferred();
    if (has_filename()) {
      auto pos = _path.find_last_of(separators);
      _path.resize(pos + 1);
    }
    return *this;
  }
  
  path& path::replace_filename(const path& replacement)
  {
    remove_filename();
    append(replacement);
    return *this;
  }
  
  path& path::replace_extension(const path& replacement)
  {
    make_preferred();
    if (has_filename()) {
      // Remove extension
      auto sep = _path.find_last_of(separators);
      auto dot = _path.find_last_of(".");
      if (dot > sep || sep == _path.npos) {
        if (dot != _path.npos) {
          _path.resize(dot);
        }
      }
      // Add extension
      if (!(replacement.empty() || replacement._path.front() == '.')) {
        concat(".");
      }
      concat(replacement);
    }
    return *this;
  }
  
  void path::swap(path& rhs) noexcept
  {
    using std::swap;
    swap(_format, rhs._format);
    swap(_path, rhs._path);
  }
  
  // 30.10.7.4.6, native format observers

  const path::string_type& path::native() const noexcept
  {
    return _path;
  }
  
  const path::value_type* path::c_str() const noexcept
  {
    return _path.c_str();
  }
  
  path::operator string_type() const
  {
    return native();
  }
  
  std::string path::string() const
  {
    return {native()};
  }

  // 30.10.7.4.7, generic format observers
  
  std::string path::generic_string() const
  {
    return _path;
  }
  
  // 30.10.7.4.8, compare

  int path::compare(const path& p) const noexcept
  {
    for (auto [c1, c2] : util::zip(native(), p.native())) {
      if (c1 < c2) return -1;
      if (c1 > c2) return 1;
    }
    auto l1 = native().length();
    auto l2 = p.native().length();
    if (l1 < l2) return -1;
    if (l1 > l2) return 1;
    return 0;
  }
  
  int path::compare(const string_type& s) const
  {
    return compare(path(s));
  }
  
  int path::compare(std::basic_string_view<value_type> s) const
  {
    return compare(path(s));
  }
  
  int path::compare(const value_type* s) const
  {
    return compare(path(std::string(s)));
  }
  
    
  // 30.10.7.4.9, decomposition
  path path::root_name() const
  {
    // TODO: implement this;
    return path();
  }
  
  path path::root_directory() const
  {
    // TODO: implement this;
    return path();
  }
  
  path path::root_path() const
  {
    return root_name() / root_directory();
  }
  
  path path::relative_path() const
  {
    // TODO: Real implementation
    if (is_absolute()) {
      return {_path.begin() + 1, _path.end()};
    }
    return path();
  }
  
  path path::parent_path() const
  {
    if (!has_relative_path()) {
      return *this;
    }
    path res {_path};
    while (!res.has_filename()) {
      res._path.resize(res._path.size() - 1);
    }
    res.remove_filename();
    return res;
  }
  
  path path::filename() const
  {
    return has_relative_path() ? *--end() : path();
  }
  
  path path::stem() const
  {
    path f = filename();
    auto v = StringView{f.generic_string()};
    v.remove_prefix(1);
    auto dot = v.find_last_of('.');
    if (v != "." && dot != v.npos) {
      f._path.resize(dot + 1);
    }
    return f;
  }
  
  path path::extension() const
  {
    auto v = StringView{filename().generic_string()};
    v.remove_prefix(stem().generic_string().length());
    return path(v);
  }
  
    
  // 30.10.7.4.10, query
  bool path::empty() const noexcept
  {
    return _path.empty();
  }
  
  bool path::has_root_name() const
  {
    // TODO: Real implementation
    return false;
  }
  
  bool path::has_root_directory() const
  {
    // TODO: Real implementation
    return false;
  }
  
  bool path::has_root_path() const
  {
    return has_root_name() || has_root_directory();
  }
  
  bool path::has_relative_path() const
  {
    return _path.find_first_not_of(separators) != _path.npos;
  }
  
  bool path::has_parent_path() const
  {
    return _path.find_first_of(separators) != _path.npos;
  }
  
  bool path::has_filename() const
  {
    return !_path.empty() && !is_separator(_path.back());
  }
  
  bool path::has_stem() const
  {
    return has_filename();
  }
  
  bool path::has_extension() const
  {
    return !extension().empty();
  }
  
  bool path::is_absolute() const
  {
    return !_path.empty() && is_separator(_path.front());
  }
  
  bool path::is_relative() const
  {
    return !is_absolute();
  }
  
  // 30.10.7.4.11, generation
  path path::lexically_normal() const
  {
    // TODO: Implement
    return *this;
  }
  
  path path::lexically_relative(const path& base) const
  {
    // TODO: Implement
    return *this;
  }
  
  path path::lexically_proximate(const path& base) const
  {
    // TODO: Implement
    return *this;
  }
  
  path::iterator path::begin() const
  {
    return {_path.data(), _path.data()};
  }
  
  path::iterator path::end() const
  {
    return {_path.data(), _path.end().base()};
  }

  void swap(path& lhs, path& rhs) noexcept
  {
    lhs.swap(rhs);
  }
  
  size_t hash_value (const path& p) noexcept
  {
    return std::hash<path::string_type>()(p.generic_string());
  }
  
  bool operator< (const path& lhs, const path& rhs) noexcept
  {
    return lhs.compare(rhs) < 0;
  }
  
  bool operator<=(const path& lhs, const path& rhs) noexcept
  {
    return !(rhs < lhs);
  }
  
  bool operator> (const path& lhs, const path& rhs) noexcept
  {
    return rhs < lhs;
  }
  
  bool operator>=(const path& lhs, const path& rhs) noexcept
  {
    return !(lhs < rhs);
  }
  
  bool operator==(const path& lhs, const path& rhs) noexcept
  {
    return !(lhs < rhs) && !(rhs < lhs);
  }
  
  bool operator!=(const path& lhs, const path& rhs) noexcept
  {
    return !(lhs == rhs);
  }
  
  path operator/ (const path& lhs, const path& rhs) noexcept
  {
    return path(lhs) /= rhs;
  }

// otto::filesystem::path::iterator ///////////////////////////////////////////
  
  path::iterator::iterator(const iterator&) = default;
  
  path::iterator::iterator(iterator&&) noexcept = default;

  path::iterator::iterator(const path::value_type* first,
    const path::value_type* ptr)
    : _first (first),
      _ptr (ptr),
      _len (0)
  {
    refresh();
  }

  path::iterator& path::iterator::operator=(const iterator&) = default;
  
  path::iterator& path::iterator::operator=(iterator&&) noexcept = default;
  

  bool path::iterator::operator==(const iterator& rhs) const noexcept
  {
    return _ptr == rhs._ptr;
  }
  
  bool path::iterator::operator!=(const iterator& rhs) const noexcept
  {
    return _ptr != rhs._ptr;
  }
  

  path path::iterator::operator*() const
  {
    return path(StringView{_ptr, _len});
  }
  

  path::iterator& path::iterator::operator++()
  {
    _ptr += _len;
    refresh();
    return *this;
  }
  
  path::iterator path::iterator::operator++(int)
  {
    auto tmp = *this;
    operator++();
    return tmp;
  }
  

  path::iterator& path::iterator::operator--()
  {
    if (_ptr != _first) {
      while (--_ptr != _first && !is_separator(*_ptr));
      refresh();
    }
    return *this;
  }
  
  path::iterator path::iterator::operator--(int)
  {
    auto tmp = *this;
    operator--();
    return tmp;
  }

  void path::iterator::refresh()
  {
    _len = 0;
    auto tmp = _ptr;
    // skip multiple separators
    if (is_separator(*_ptr)) {
      // check if at root
      if (_ptr == _first) {
        _len = 1;
        return;
      }
      while (is_separator(*(_ptr + 1))) _ptr++;
      tmp++;
    }
    // calculate length
    while (*tmp != 0 && !is_separator(*++tmp)) {
      _len++;
    }
    return;
  }

// otto::filesystem::file_status //////////////////////////////////////////////

  file_status::file_status(file_type ft, perms prms) noexcept
    : _type (ft), _perms (prms)
  {}
  
  file_status::~file_status()
  {}

  // 30.10.10.3, modifiers

  void file_status::type(file_type ft) noexcept
  {
    _type = ft;
  }
  
  void file_status::permissions(perms prms) noexcept
  {
    _perms = prms;
  }
  

  // 30.10.10.2, observers

  file_type file_status::type() const noexcept
  {
    return _type;
  }
  
  perms file_status::permissions() const noexcept
  {
    return _perms;
  }

// otto::filesystem::directory_entry //////////////////////////////////////////

  // shorthand
  using DEntr = directory_entry;

  DEntr::directory_entry(const class path& p)
  {
    refresh();
  }
  
  DEntr::~directory_entry()
  {}
  
  // 30.10.11.2, modifiers
  void DEntr::assign(const class path& p)
  {
    pathobject = p;
    refresh();
  }
  
  void DEntr::refresh()
  {
    struct stat buf;
    if(stat(pathobject.c_str(), &buf)) {
      _exists = false;
      _block_file = false;
      _character_file = false;
      _directory = false;
      _fifo = false;
      _regular_file = false;
      _socket = false;
      _symlink = false;
      _other = false;
      _file_size = 0;
      _hard_link_count = 0;
    } else {
      _exists = true;
      _block_file = S_ISBLK(buf.st_mode);
      _character_file = S_ISCHR(buf.st_mode);
      _directory = S_ISDIR(buf.st_mode);
      _fifo = S_ISFIFO(buf.st_mode);
      _regular_file = S_ISREG(buf.st_mode);
      _socket = S_ISSOCK(buf.st_mode);
      _symlink = S_ISLNK(buf.st_mode);
      _other = !(_block_file || _character_file || _directory
        || _fifo || _regular_file || _socket || _symlink);
      _file_size = buf.st_size;
      _hard_link_count = buf.st_nlink;
    }
  }
  
  // 30.10.11.3, observers
  const path& DEntr::path() const
  {
    return pathobject;
  }
  
  DEntr::operator const class path&() const
  {
    return path();
  }
  
  bool DEntr::exists() const
  {
    return _exists;
  }
  
  bool DEntr::is_block_file() const
  {
    return _block_file;
  }
  
  bool DEntr::is_character_file() const
  {
    return _character_file;
  }
  
  bool DEntr::is_directory() const
  {
    return _directory;
  }
  
  bool DEntr::is_fifo() const
  {
    return _fifo;
  }
  
  bool DEntr::is_other() const
  {
    return _other;
  }
  
  bool DEntr::is_regular_file() const
  {
    return _regular_file;
  }
  
  bool DEntr::is_socket() const
  {
    return _socket;
  }
  
  bool DEntr::is_symlink() const
  {
    return _symlink;
  }
  
  uintmax_t DEntr::file_size() const
  {
    return _file_size;
  }
  
  uintmax_t DEntr::hard_link_count() const
  {
    return _hard_link_count;
  }
  
  bool DEntr::operator==(const directory_entry& rhs) const noexcept
  {
    return pathobject == rhs.pathobject;
  }
  
  bool DEntr::operator!=(const directory_entry& rhs) const noexcept
  {
    return pathobject != rhs.pathobject;
  }
  

// otto::filesystem::directory_iterator ///////////////////////////////////////

  // shorthand
  using DIter = directory_iterator;

  DIter::directory_iterator() noexcept
    : _ptr (nullptr)
  {}

  DIter::directory_iterator(const path& p)
  {
    _entries = std::make_shared<std::vector<DEntr>>();
#if IS_POSIX
    DIR *dir;
    struct dirent *de;

    dir = opendir(p.c_str());
    while(dir)
    {
        de = readdir(dir);
        if (!de) break;
        _entries->emplace_back(de->d_name);
    }
    closedir(dir);
#else
#error "Only implemented for posix"
#endif
    if (_entries->size() == 0) {
      _ptr = nullptr;
    } else {
      _ptr = _entries->data();
    }
  }

  DIter::directory_iterator(const DIter& rhs) = default;

  DIter::directory_iterator(DIter&& rhs) noexcept = default;

  DIter::~directory_iterator() = default;

  DIter& DIter::operator=(const DIter& rhs) = default;

  DIter& DIter::operator=(DIter&& rhs) noexcept = default;

  const DEntr& DIter::operator*() const
  {
    return *_ptr;
  }

  const DEntr* DIter::operator->() const
  {
    return _ptr;
  }

  DIter& DIter::operator++()
  {
    ++_ptr;
    if (_ptr == _entries->end().base()) 
      _ptr = nullptr;
    return *this;
  }

  bool DIter::operator==(const DIter& other) const
  {
    return _ptr == other._ptr;
  }

  bool DIter::operator!=(const DIter& other) const
  {
    return _ptr != other._ptr;
  }

  directory_iterator DIter::operator++(int)
  {
    auto tmp = *this;
    ++(*this);
    return tmp;
  }

  directory_iterator begin(directory_iterator iter) noexcept
  {
    return iter;
  }

  directory_iterator end(const directory_iterator& iter) noexcept
  {
    return {};
  }


// otto::fs::recursive_directory_iterator /////////////////////////////////////

  using RDIter = recursive_directory_iterator;

  struct RDIter::SharedData {
    int depth = 0;
    directory_entry* entry = nullptr;
    std::shared_ptr<SharedData> parent = nullptr;
    std::vector<directory_entry> entries = {};

    void populate_entries(const path& p)
    {
#if IS_POSIX
      DIR *dir;
      struct dirent *de;

      dir = opendir(p.c_str());
      while(dir)
      {
        de = readdir(dir);
        if (!de) break;
        entries.emplace_back(de->d_name);
      }
      closedir(dir);
#else
#error "Only implemented for posix"
#endif
      if (entries.size() == 0) {
        entry = nullptr;
      } else {
        entry = entries.data();
      }
    }
  };

  RDIter::recursive_directory_iterator() noexcept
  {}
  
  RDIter::recursive_directory_iterator(const path& p)
  {
    if (fs::is_directory(p)) {
      _data = std::make_shared<SharedData>();
      _data->populate_entries(p);
    }
  }
  
  RDIter::recursive_directory_iterator(const RDIter& rhs) = default;
  
  RDIter::recursive_directory_iterator(RDIter&& rhs) noexcept = default;

  RDIter::~recursive_directory_iterator()
  {}
  
  // 30.10.13.1, observers

  int RDIter::depth() const
  {
    return _data->depth;
  }
  

  const directory_entry& RDIter::operator*() const
  {
    return *_data->entry;
  }
  
  const directory_entry* RDIter::operator->() const
  {
    return _data->entry;
  }
  

  // 30.10.13.1, modifiers

  RDIter& RDIter::operator=(const RDIter& rhs) = default;

  RDIter& RDIter::operator=(RDIter&& rhs) noexcept = default;

  RDIter& RDIter::operator++()
  {
    if (_data != nullptr) {
      if (_data->entry->is_directory()) {
        auto new_data = std::make_shared<SharedData>(*_data);
        new_data->depth++;
        new_data->parent = _data;
        new_data->populate_entries(_data->entry->path());
      } else {
        ++_data->entry;
        if (_data->entry == _data->entries.end().base()) {
          pop();
        }
      }
    }
    return *this;
  }
  
  void RDIter::pop()
  {
    _data = _data->parent;
  }

  bool RDIter::operator==(const RDIter& other) const
  {
    return (_data == other._data)
      || (_data != nullptr
        && other._data != nullptr
        && _data->entry == other._data->entry);
  }
  
  bool RDIter::operator!=(const RDIter& other) const
  {
    return !(*this == other);
  }
  
  RDIter RDIter::operator++(int)
  {
    auto tmp = *this;
    ++(*this);
    return tmp;
  }

  RDIter begin(RDIter iter) noexcept
  {
    return iter;
  }

  RDIter end(const RDIter& iter) noexcept
  {
    return {};
  }

  // FREE FUNCTIONS /////////////////////////////////////////////////////////////

  bool remove_file(const path& p)
  {
    printf("Deleting file: %s", p.c_str());
    return true;
#if false
    return std::remove(p.c_str()) == 0;
//#else
    return DeleteFileW(p.wstr().c_str()) != 0;
#endif
  }

  bool resize_file(const path& p, size_t target_length)
  {
#if !defined(_WIN32)
    return ::truncate(p.c_str(), (off_t) target_length) == 0;
#else
    HANDLE handle = CreateFileW(p.wstr().c_str(), GENERIC_WRITE, 0, nullptr, 0, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (handle == INVALID_HANDLE_VALUE)
      return false;
    LARGE_INTEGER size;
    size.QuadPart = (LONGLONG) target_length;
    if (SetFilePointerEx(handle, size, NULL, FILE_BEGIN) == 0) {
      CloseHandle(handle);
      return false;
    }
    if (SetEndOfFile(handle) == 0) {
      CloseHandle(handle);
      return false;
    }
    CloseHandle(handle);
    return true;
#endif
  }

  path current_path()
  {
#if !defined(_WIN32)
    char temp[PATH_MAX];
    if (::getcwd(temp, PATH_MAX) == NULL)
      throw std::runtime_error("Internal error in getcwd(): " + std::string(strerror(errno)));
    return path(temp);
#else
    std::wstring temp(MAX_PATH, '\0');
    if (!_wgetcwd(&temp[0], MAX_PATH))
      throw std::runtime_error("Internal error in getcwd(): " + std::to_string(GetLastError()));
    return path(temp.c_str());
#endif
  }

  path absolute(const path& p)
  {
#if !defined(_WIN32)
    char temp[PATH_MAX];
    if (realpath(p.c_str(), temp) == NULL)
      throw std::runtime_error("Internal error in realpath(): " + std::string(strerror(errno)));
    return path(temp);
#else
    std::wstring value = p.wstr(), out(MAX_PATH, '\0');
    DWORD length = GetFullPathNameW(value.c_str(), MAX_PATH, &out[0], NULL);
    if (length == 0)
      throw std::runtime_error("Internal error in realpath(): " + std::to_string(GetLastError()));
    return path(out.substr(0, length));
#endif
  }

  bool exists(const path& p)
  {
#if defined(_WIN32)
    return GetFileAttributesW(p.wstr().c_str()) != INVALID_FILE_ATTRIBUTES;
#else
    struct stat sb;
    return stat(p.c_str(), &sb) == 0;
#endif
  }

  bool is_block_file(const path& p)
  {
    struct stat buf;
    if(stat(p.c_str(), &buf)) return false;
    return S_ISBLK(buf.st_mode);
  }

  bool is_character_file(const path& p)
  {
    struct stat buf;
    if(stat(p.c_str(), &buf)) return false;
    return S_ISCHR(buf.st_mode);
  }

  bool is_directory(const path& p)
  {
    struct stat buf;
    if(stat(p.c_str(), &buf)) return false;
    return S_ISDIR(buf.st_mode);
  }

  bool is_fifo(const path& p)
  {
    struct stat buf;
    if(stat(p.c_str(), &buf)) return false;
    return S_ISFIFO(buf.st_mode);
  }

  bool is_other(const path& p)
  {
    struct stat buf;
    if(stat(p.c_str(), &buf)) return false;
    return !(S_ISBLK(buf.st_mode)
      || S_ISCHR(buf.st_mode)
      || S_ISDIR(buf.st_mode)
      || S_ISFIFO(buf.st_mode)
      || S_ISLNK(buf.st_mode)
      || S_ISREG(buf.st_mode)
      || S_ISSOCK(buf.st_mode));
  }

  bool is_regular_file(const path& p)
  {
    struct stat buf;
    if(stat(p.c_str(), &buf)) return false;
    return S_ISREG(buf.st_mode);
  }

  bool is_socket(const path& p)
  {
    struct stat buf;
    if(stat(p.c_str(), &buf)) return false;
    return S_ISSOCK(buf.st_mode);
  }

  bool is_symlink(const path& p)
  {
    struct stat buf;
    if(stat(p.c_str(), &buf)) return false;
    return S_ISLNK(buf.st_mode);
  }

  size_t file_size(const path& p)
  {
#if defined(_WIN32)
    struct _stati64 sb;
    if (_wstati64(p.c_str(), &sb) != 0)
      throw std::runtime_error("path::file_size(): cannot stat file \"" + p.string() + "\"!");
#else
    struct stat sb;
    if (stat(p.c_str(), &sb) != 0)
      throw std::runtime_error("path::file_size(): cannot stat file \"" + p.string() + "\"!");
#endif
    return (size_t) sb.st_size;
  }

  bool create_directory(const path& p)
  {
#if defined(_WIN32)
    return CreateDirectoryW(p.wstr().c_str(), NULL) != 0;
#else
    return mkdir(p.c_str(), S_IRUSR | S_IWUSR | S_IXUSR) == 0;
#endif
  }

  bool create_directories(const path& p)
  {
    path abs = absolute(p);
    path part;
    for (const auto& d : p) {
      part /= d;
      if (!exists(part)) {
        if (!create_directory(part)) {
          return false;
        }
      }
    }
    return true;
  }

  bool remove_all(const path& p)
  {
    if (is_directory(p)) {
      bool res = true;
      for (auto&& de : recursive_directory_iterator(p)) {
        res = remove_file(de);
      }
      return res;
    } else {
      return remove_file(p);
    }
  }


}
