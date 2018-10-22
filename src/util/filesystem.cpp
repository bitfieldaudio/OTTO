#include "filesystem.hpp"

#include <cerrno>
#include <cstring>
#include <fstream>

#include "util/algorithm.hpp"
#include "util/iterator.hpp"

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

namespace otto::filesystem {

  // operator overloads for scoped enums // ////////////////////////////////////

  file_type operator&(file_type lhs, file_type rhs)
  {
    return file_type{std::underlying_type_t<file_type>(lhs) &
                     std::underlying_type_t<file_type>(rhs)};
  }
  file_type operator|(file_type lhs, file_type rhs)
  {
    return file_type{std::underlying_type_t<file_type>(lhs) |
                     std::underlying_type_t<file_type>(rhs)};
  }
  bool operator!=(file_type lhs, file_type rhs)
  {
    return std::underlying_type_t<directory_options>(lhs) !=
           std::underlying_type_t<directory_options>(rhs);
  }

  copy_options operator&(copy_options lhs, copy_options rhs)
  {
    return copy_options{std::underlying_type_t<copy_options>(lhs) &
                        std::underlying_type_t<copy_options>(rhs)};
  }
  copy_options operator|(copy_options lhs, copy_options rhs)
  {
    return copy_options{std::underlying_type_t<copy_options>(lhs) |
                        std::underlying_type_t<copy_options>(rhs)};
  }

  bool operator!=(copy_options lhs, copy_options rhs)
  {
    return std::underlying_type_t<directory_options>(lhs) !=
           std::underlying_type_t<directory_options>(rhs);
  }

  perms operator&(perms lhs, perms rhs)
  {
    return perms{std::underlying_type_t<perms>(lhs) &
                 std::underlying_type_t<perms>(rhs)};
  }

  perms operator|(perms lhs, perms rhs)
  {
    return perms{std::underlying_type_t<perms>(lhs) |
                 std::underlying_type_t<perms>(rhs)};
  }

  bool operator!=(perms lhs, perms rhs)
  {
    return std::underlying_type_t<directory_options>(lhs) !=
           std::underlying_type_t<directory_options>(rhs);
  }

  perm_options operator&(perm_options lhs, perm_options rhs)
  {
    return perm_options{std::underlying_type_t<perm_options>(lhs) &
                        std::underlying_type_t<perm_options>(rhs)};
  }
  perm_options operator|(perm_options lhs, perm_options rhs)
  {
    return perm_options{std::underlying_type_t<perm_options>(lhs) |
                        std::underlying_type_t<perm_options>(rhs)};
  }
  bool operator!=(perm_options lhs, perm_options rhs)
  {
    return std::underlying_type_t<directory_options>(lhs) !=
           std::underlying_type_t<directory_options>(rhs);
  }

  directory_options operator&(directory_options lhs, directory_options rhs)
  {
    return directory_options{std::underlying_type_t<directory_options>(lhs) &
                             std::underlying_type_t<directory_options>(rhs)};
  }
  directory_options operator|(directory_options lhs, directory_options rhs)
  {
    return directory_options{std::underlying_type_t<directory_options>(lhs) |
                             std::underlying_type_t<directory_options>(rhs)};
  }
  bool operator!=(directory_options lhs, directory_options rhs)
  {
    return std::underlying_type_t<directory_options>(lhs) !=
           std::underlying_type_t<directory_options>(rhs);
  }


  // Posix utility functions ///////////////////////////////////////////////////

  namespace px {

    const char* separators = "/\\";

    path::format detect_format(const path::string_type& s)
    {
      return path::generic_format;
    }

    bool is_separator(path::value_type c)
    {
      const char* s = separators;
      while (*s != 0) {
        if (*s++ == c) return true;
      }
      return false;
    }

    file_type to_file_type(int stat_mode)
    {
      if (S_ISBLK(stat_mode)) return file_type::block;
      if (S_ISCHR(stat_mode)) return file_type::character;
      if (S_ISDIR(stat_mode)) return file_type::directory;
      if (S_ISFIFO(stat_mode)) return file_type::fifo;
      if (S_ISLNK(stat_mode)) return file_type::symlink;
      if (S_ISREG(stat_mode)) return file_type::regular;
      if (S_ISSOCK(stat_mode)) return file_type::socket;
      return file_type::unknown;
    }

    file_type to_file_type(struct stat st, std::error_code& ec)
    {
      if (ec != std::error_code()) {
        switch (ec.value()) {
        case ENOENT: return file_type::not_found;
        default: return file_type::none;
        }
      }
      return to_file_type(st.st_mode);
    }

    uintmax_t file_size(struct stat st, std::error_code& ec)
    {
      if (ec.value() == 0) {
        ec.clear();
      } else {
        return 0;
      }
      return st.st_size;
    }

    uintmax_t hard_link_count(struct stat st, std::error_code& ec)
    {
      if (ec.value() == 0) {
        ec.clear();
      } else {
        return 0;
      }
      return st.st_nlink;
    }

    file_time_type last_write_time(struct stat st, std::error_code& ec)
    {
      if (ec.value() == 0) {
        ec.clear();
      } else {
        return {};
      }
#if __APPLE__
      return file_time_type() +
             std::chrono::duration_cast<file_time_type::duration>(
               std::chrono::nanoseconds(st.st_mtimespec.tv_nsec));
#else
      return file_time_type() +
             std::chrono::duration_cast<file_time_type::duration>(
               std::chrono::nanoseconds(st.st_mtim.tv_nsec));
#endif
    }

    struct stat stat(path p, std::error_code& ec)
    {
      struct stat st;
      if (::stat(p.c_str(), &st) != 0) {
        ec = {errno, std::system_category()};
      } else {
        ec.clear();
      }
      return st;
    }

    struct stat lstat(path p, std::error_code& ec)
    {
      struct stat st;
      if (::lstat(p.c_str(), &st) != 0) {
        ec = {errno, std::system_category()};
      } else {
        ec.clear();
      }
      return st;
    }

    file_status status(path p, struct stat& st, std::error_code& ec)
    {
      if (::stat(p.c_str(), &st) != 0) {
        if (errno == ENOENT) {
          ec.clear();
          return file_status{file_type::not_found, perms::none};
        } else {
          ec = {errno, std::system_category()};
          return {};
        }
      }
      ec.clear();
      file_type type = to_file_type(st, ec);
      perms prms     = static_cast<perms>(st.st_mode) & perms::mask;
      return file_status{type, prms};
    }

    file_status link_status(path p, struct stat& st, std::error_code& ec)
    {
      if (::stat(p.c_str(), &st) != 0) {
        if (errno == ENOENT) {
          ec.clear();
          return file_status{file_type::not_found, perms::none};
        } else {
          ec = {errno, std::system_category()};
          return {};
        }
      }
      ec.clear();
      file_type type = to_file_type(st, ec);
      perms prms     = static_cast<perms>(st.st_mode) & perms::mask;
      return file_status{type, prms};
    }

  } // namespace px

  using StringView = std::basic_string_view<path::value_type>;

  // otto::filesystem::path ////////////////////////////////////////////////////

  // 30.10.7.4.1, constructors and destructor

  path::path() noexcept {}

  path::path(const path& p) = default;

  path::path(path&& p) noexcept : _format(p._format), _path(std::move(p._path))
  {}

  path::path(string_type&& source, format fmt)
    : _format(fmt),
      _path(std::move(source))
  {}

  path::path(const string_type& source, format fmt)
    : _format(fmt),
      _path(source)
  {}

  path::path(std::basic_string_view<value_type> source, format fmt)
    : _format(fmt),
      _path(source)
  {}

  path::path(const value_type* source, format fmt)
    : _format(fmt),
       _path(source)
  {}

  path::~path() = default;

  // 30.10.7.4.2, assignments

  path& path::operator=(const path& p) = default;

  path& path::operator=(path&& p) = default;

  path& path::operator=(string_type&& source)
  {
    assign(std::move(source));
    return *this;
  }

  path& path::assign(string_type&& source)
  {
    _format = px::detect_format(source);
    _path   = std::move(source);
    return *this;
  }


  // 30.10.7.4.3, appends

  path& path::operator/=(const path& p)
  {
    if (p.is_absolute() ||
        (p.has_root_name() && p.root_name() != root_name())) {
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
      auto pos = _path.find_last_of(px::separators);
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
      auto sep = _path.find_last_of(px::separators);
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
      exists(replacement);
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
    return native() < p.native();
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
    return compare(path(s));
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
    path res{_path};
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
    return _path.find_first_not_of(px::separators) != _path.npos;
  }

  bool path::has_parent_path() const
  {
    return _path.find_first_of(px::separators) != _path.npos;
  }

  bool path::has_filename() const
  {
    return !_path.empty() && !px::is_separator(_path.back());
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
    return !_path.empty() && px::is_separator(_path.front());
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

  size_t hash_value(const path& p) noexcept
  {
    return std::hash<path::string_type>()(p.generic_string());
  }

  bool operator<(const path& lhs, const path& rhs) noexcept
  {
    return lhs.compare(rhs) < 0;
  }

  bool operator<=(const path& lhs, const path& rhs) noexcept
  {
    return !(rhs < lhs);
  }

  bool operator>(const path& lhs, const path& rhs) noexcept
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

  path operator/(const path& lhs, const path& rhs) noexcept
  {
    return path(lhs) /= rhs;
  }

  // otto::filesystem::path::iterator //////////////////////////////////////////

  path::iterator::iterator(const iterator&) = default;

  path::iterator::iterator(iterator&&) noexcept = default;

  path::iterator::iterator(const path::value_type* first,
                           const path::value_type* ptr)
    : _first(first), _ptr(ptr), _len(0)
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
    while (--_ptr != _first && !px::is_separator(*(_ptr - 1)))
      ;
    refresh();
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
    auto tmp = _ptr;
    // calculate length
    while (*tmp != 0 && !px::is_separator(*tmp++))
      ;
    // skip multiple separators
    while (px::is_separator(*(tmp))) tmp++;
    _len = tmp - _ptr;
  }

  // otto::filesystem::file_status /////////////////////////////////////////////

  file_status::file_status(file_type ft, perms prms) noexcept
    : _type(ft), _perms(prms)
  {}

  file_status::~file_status() {}

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

  // otto::filesystem::filesystem_error ////////////////////////////////////////

  filesystem_error::filesystem_error(const std::string& what_arg,
                                     std::error_code ec)
    : system_error(ec), _code(ec)
  {
    _what = std::string("Filesystem error: ") + ec.message();
    if (!what_arg.empty()) {
      _what += "\nNote: ";
      _what += what_arg;
    }
  }

  filesystem_error::filesystem_error(const std::string& what_arg,
                                     const path& p1,
                                     std::error_code ec)
    : filesystem_error(what_arg, ec)
  {
    _path1 = p1;
    _what += "\nPath: ";
    _what += _path1;
  }

  filesystem_error::filesystem_error(const std::string& what_arg,
                                     const path& p1,
                                     const path& p2,
                                     std::error_code ec)
    : filesystem_error(what_arg, ec)
  {
    _path1 = p1;
    _what += "\nPath 1: ";
    _what += _path1;
    _path2 = p2;
    _what += "\nPath 2: ";
    _what += _path2;
  }

  const path& filesystem_error::path1() const noexcept
  {
    return _path1;
  }

  const path& filesystem_error::path2() const noexcept
  {
    return _path2;
  }

  const char* filesystem_error::what() const noexcept
  {
    return _what.c_str();
  }

  // otto::filesystem::directory_entry /////////////////////////////////////////

  // shorthand
  using DEntr = directory_entry;

  DEntr::directory_entry(const class path& p) : pathobject(p)
  {
    refresh();
  }

  DEntr::directory_entry(const class path& p, std::error_code& ec)
    : pathobject(p)
  {
    refresh(ec);
  }

  DEntr::~directory_entry() {}

  // 30.10.11.2, modifiers
  void DEntr::assign(const class path& p)
  {
    pathobject = p;
    refresh();
  }

  void DEntr::assign(const class path& p, std::error_code& ec)
  {
    pathobject = p;
    refresh(ec);
  }

  void DEntr::replace_filename(const class path& p)
  {
    pathobject.replace_filename(p);
    refresh();
  }

  void DEntr::replace_filename(const class path& p, std::error_code& ec)
  {
    pathobject.replace_filename(p);
    refresh(ec);
  }

  void DEntr::refresh()
  {
    std::error_code ec;
    refresh(ec);
    if (ec != std::error_code()) {
      throw filesystem_error("While refreshing directory entry", pathobject,
                             ec);
    }
  }

  void DEntr::refresh(std::error_code& ec) noexcept
  {
    struct stat st;
    _status = px::status(pathobject, st, ec);
    if (filesystem::exists(_status)) {
      _file_size       = px::file_size(st, ec);
      _hard_link_count = px::hard_link_count(st, ec);
    } else {
      _file_size       = 0;
      _hard_link_count = 0;
    }
    _symlink_status = filesystem::symlink_status(pathobject, ec);
  }

  // 30.10.11.3, observers
  const class path& DEntr::path() const
  {
    return pathobject;
  }

  DEntr::operator const class path&() const
  {
    return path();
  }

  bool DEntr::exists(std::error_code& ec) const noexcept
  {
    return filesystem::exists(_status);
  }

  bool DEntr::exists() const
  {
    return filesystem::exists(_status);
  }

  bool DEntr::is_block_file(std::error_code& ec) const noexcept
  {
    return filesystem::is_block_file(_status);
  }

  bool DEntr::is_block_file() const
  {
    return filesystem::is_block_file(_status);
  }

  bool DEntr::is_character_file(std::error_code& ec) const noexcept
  {
    return filesystem::is_character_file(_status);
  }

  bool DEntr::is_character_file() const
  {
    return filesystem::is_character_file(_status);
  }

  bool DEntr::is_directory(std::error_code& ec) const noexcept
  {
    return filesystem::is_directory(_status);
  }

  bool DEntr::is_directory() const
  {
    return filesystem::is_directory(_status);
  }

  bool DEntr::is_fifo(std::error_code& ec) const noexcept
  {
    return filesystem::is_fifo(_status);
  }

  bool DEntr::is_fifo() const
  {
    return filesystem::is_fifo(_status);
  }

  bool DEntr::is_other(std::error_code& ec) const noexcept
  {
    return filesystem::is_other(_status);
  }

  bool DEntr::is_other() const
  {
    return filesystem::is_other(_status);
  }

  bool DEntr::is_regular_file(std::error_code& ec) const noexcept
  {
    return filesystem::is_regular_file(_status);
  }

  bool DEntr::is_regular_file() const
  {
    return filesystem::is_regular_file(_status);
  }

  bool DEntr::is_socket(std::error_code& ec) const noexcept
  {
    return filesystem::is_socket(_status);
  }

  bool DEntr::is_socket() const
  {
    return filesystem::is_socket(_status);
  }

  bool DEntr::is_symlink(std::error_code& ec) const noexcept
  {
    return filesystem::is_symlink(_status);
  }

  bool DEntr::is_symlink() const
  {
    return filesystem::is_symlink(_status);
  }

  uintmax_t DEntr::file_size(std::error_code& ec) const noexcept
  {
    return _file_size;
  }

  uintmax_t DEntr::file_size() const
  {
    return _file_size;
  }

  uintmax_t DEntr::hard_link_count(std::error_code& ec) const noexcept
  {
    return _hard_link_count;
  }

  uintmax_t DEntr::hard_link_count() const
  {
    return _hard_link_count;
  }

  file_time_type DEntr::last_write_time(std::error_code& ec) const noexcept
  {
    return filesystem::last_write_time(pathobject, ec);
  }

  file_time_type DEntr::last_write_time() const
  {
    return filesystem::last_write_time(pathobject);
  }

  file_status DEntr::status(std::error_code& ec) const noexcept
  {
    return _status;
  }

  file_status DEntr::status() const
  {
    return _status;
  }

  file_status DEntr::symlink_status(std::error_code& ec) const noexcept
  {
    return _symlink_status;
  }

  file_status DEntr::symlink_status() const
  {
    return _symlink_status;
  }

  bool DEntr::operator==(const directory_entry& rhs) const noexcept
  {
    return pathobject == rhs.pathobject;
  }

  bool DEntr::operator!=(const directory_entry& rhs) const noexcept
  {
    return pathobject != rhs.pathobject;
  }


  // otto::filesystem::directory_iterator //////////////////////////////////////

  // shorthand
  using DIter = directory_iterator;

  DIter::directory_iterator() noexcept : _ptr(nullptr) {}

  DIter::directory_iterator(const path& p)
  {
    std::error_code ec;
    read_dir(p, {}, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("While constructing directory_iterator", p, ec);
    }
  }

  DIter::directory_iterator(const path& p, directory_options options)
  {
    std::error_code ec;
    read_dir(p, options, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("While constructing directory_iterator", p, ec);
    }
  }

  DIter::directory_iterator(const path& p, std::error_code& ec)
  {
    read_dir(p, {}, ec);
  }

  DIter::directory_iterator(const path& p,
                            directory_options options,
                            std::error_code& ec)
  {
    read_dir(p, options, ec);
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
    if (_ptr == _entries->end().base()) _ptr = nullptr;
    return *this;
  }

  directory_iterator& DIter::increment(std::error_code& ec) noexcept
  {
    operator++();
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

  void DIter::read_dir(const path& p,
                       directory_options options,
                       std::error_code& ec)
  {
    _entries = std::make_shared<std::vector<DEntr>>();

    bool skip_denied = (options & directory_options::skip_permission_denied) !=
                       directory_options::none;

    errno = 0;
    auto* dir = opendir(p.c_str());
    if (dir == nullptr) {
      ec.assign(errno, std::system_category());
      return;
    }

    std::string name;
    dirent* de;
    do {
      errno = 0;
      de = readdir(dir);
      if (errno == EACCES && skip_denied) {
        continue;
      }
      if (!de) continue;
      name = de->d_name;
      if (name == "." || name == "..") continue;
      _entries->emplace_back(p / de->d_name);
    } while (de != nullptr);

    closedir(dir);

    if (errno != 0) {
      ec.assign(errno, std::system_category());
    }

    if (_entries->size() == 0) {
      _ptr = nullptr;
    } else {
      _ptr = _entries->data();
    }
  }

  directory_iterator begin(directory_iterator iter) noexcept
  {
    return iter;
  }

  directory_iterator end(const directory_iterator& iter) noexcept
  {
    return {};
  }


  // otto::fs::recursive_directory_iterator ////////////////////////////////////

  using RDIter = recursive_directory_iterator;

  RDIter::recursive_directory_iterator() noexcept {}

  RDIter::recursive_directory_iterator(const path& p)
  {
    if (fs::is_directory(p)) {
      _data = std::make_shared<std::vector<DIter>>();
      std::error_code ec;
      _data->emplace_back(p, ec);
      if (_data->front() == DIter()) {
        _data = nullptr;
      }
      if (ec.value() != 0) {
        throw filesystem_error("Error constructing recursive_directory_iterator", p, ec);
      }
    }
  }

  RDIter::recursive_directory_iterator(const RDIter& rhs) = default;

  RDIter::recursive_directory_iterator(RDIter&& rhs) noexcept = default;

  RDIter::~recursive_directory_iterator() {}

  // 30.10.13.1, observers

  int RDIter::depth() const
  {
    return _data->size();
  }


  const directory_entry& RDIter::operator*() const
  {
    return *_data->back();
  }

  const directory_entry* RDIter::operator->() const
  {
    return _data->back().operator->();
  }


  // 30.10.13.1, modifiers

  RDIter& RDIter::operator=(const RDIter& rhs) = default;

  RDIter& RDIter::operator=(RDIter&& rhs) noexcept = default;

  RDIter& RDIter::operator++()
  {
    if (_data != nullptr) {
      if (_data->back()->is_directory()) {
        std::error_code ec;
        _data->emplace_back(_data->back()->path(), ec);
        if (ec.value() != 0) {
          throw filesystem_error("", ec);
        }
      } else {
        ++_data->back();
        if (_data->back() == end(_data->back())) {
          pop();
        }
      }
    }
    return *this;
  }

  void RDIter::pop()
  {
    if (_data != nullptr) {
      _data->pop_back();
      if (_data->size() == 0) {
        _data = nullptr; 
      } else {
        ++(_data->back());
        if (_data->back() == end(_data->back())) {
          pop();
        }
      }
    }
  }

  bool RDIter::operator==(const RDIter& other) const
  {
    return (_data == other._data) ||
           (_data != nullptr && other._data != nullptr &&
             _data->back() == other._data->back());
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

  // 30.10.14, filesystem operations /////////////////////////////////////////

  path absolute(const path& p)
  {
    std::error_code ec;
    auto tmp = absolute(p, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::absolute", p, ec);
    }
    return tmp;
  }

  path absolute(const path& p, std::error_code& ec)
  {
    return current_path() / p;
  }

  path canonical(const path& p)
  {
    std::error_code ec;
    auto tmp = canonical(p, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::canonical", p, ec);
    }
    return tmp;
  }

  path canonical(const path& p, std::error_code& ec)
  {
    char tmp[PATH_MAX];
    if (realpath(p.c_str(), tmp) == nullptr) {
      ec = {errno, std::system_category()};
    } else {
      ec.clear();
    }
    return path(tmp);
  }

  /*
    void copy(const path& from, const path& to);
    void copy(const path& from, const path& to, std::error_code& ec) noexcept;

    void copy(const path& from, const path& to, copy_options options);
    void copy(const path& from, const path& to, copy_options options,
    std::error_code& ec) noexcept
    {
    auto f = status(from);
    auto t = status(to);
    if ((options & copy_options::create_symlinks) != copy_options::none
    || (options & copy_options::skip_symlinks) != copy_options::none) {
    auto f = symlink_status(from);
    auto t = symlink_status(to);
    } else if ((options & copy_options::copy_symlinks) != copy_options::none) {
    auto f = symlink_status(from);
    auto t = status(to);
    } else {
    auto f = status(from);
    auto t = status(to);
    }
    if (f.type() == file_type::not_found) {
    f.type();
    }
    }
  */

  bool copy_file(const path& from, const path& to)
  {
    std::error_code ec;
    auto tmp = copy_file(from, to, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::copy_file", from, to, ec);
    }
    return tmp;
  }

  bool copy_file(const path& from, const path& to, std::error_code& ec) noexcept
  {
    return copy_file(from, to, copy_options::none);
  }

  bool copy_file(const path& from, const path& to, copy_options options)
  {
    std::error_code ec;
    auto tmp = copy_file(from, to, options, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::copy_file", from, to, ec);
    }
    return tmp;
  }

  bool copy_file(const path& from,
                 const path& to,
                 copy_options options,
                 std::error_code& ec) noexcept
  {
    auto t = status(to, ec);
    if (!is_regular_file(from) ||
        (t.type() != file_type::not_found &&
         (t.type() != file_type::regular || equivalent(from, to) ||
          (options &
           (copy_options::skip_existing | copy_options::overwrite_existing |
            copy_options::update_existing)) == copy_options::none))) {
      ec.assign(EEXIST, std::system_category());
    } else {
      if (t.type() == file_type::not_found ||
          (options & copy_options::overwrite_existing) != copy_options::none ||
          ((options & copy_options::update_existing) != copy_options::none &&
           last_write_time(from) > last_write_time(to))) {
        std::ifstream src(from, std::ios::binary);
        std::ofstream dst(to, std::ios::binary | std::ios::trunc);

        dst << src.rdbuf();
        if (errno != 0) {
          ec = {errno, std::system_category()};
        } else {
          ec.clear();
          return true;
        }
      }
    }
    return false;
  }

  /*
    void copy_symlink(const path& existing_symlink, const path& new_symlink);
    void copy_symlink(const path& existing_symlink, const path& new_symlink,
    std::error_code& ec) noexcept;
  */

  bool create_directories(const path& p)
  {
    std::error_code ec;
    auto tmp = create_directories(p, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::create_directories", p, ec);
    }
    return tmp;
  }

  bool create_directories(const path& p, std::error_code& ec) noexcept
  {
    path abs = absolute(p, ec);
    if (ec != std::error_code()) return false;
    path part;
    for (const auto& d : p) {
      part /= d;
      if (!is_directory(part, ec)) {
        if (!create_directory(part, ec)) {
          return false;
        }
      }
      if (ec != std::error_code()) return false;
    }
    return true;
  }

  bool create_directory(const path& p)
  {
    std::error_code ec;
    auto tmp = create_directory(p, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::create_directory", p, ec);
    }
    return tmp;
  }

  bool create_directory(const path& p, std::error_code& ec) noexcept
  {
    auto error = mkdir(p.c_str(), static_cast<int>(perms::all));
    if (error && !is_directory(p)) {
      ec = {errno, std::system_category()};
    } else {
      ec.clear();
    }
    return !error;
  }

  /*
    bool create_directory(const path& p, const path& attributes);
    bool create_directory(const path& p, const path& attributes,
    std::error_code& ec) noexcept;

    void create_directory_symlink(const path& to, const path& new_symlink);
    void create_directory_symlink(const path& to, const path& new_symlink,
    std::error_code& ec) noexcept;

    void create_hard_link(const path& to, const path& new_hard_link);
    void create_hard_link(const path& to, const path& new_hard_link,
    std::error_code& ec) noexcept;

    void create_symlink(const path& to, const path& new_symlink);
    void create_symlink(const path& to, const path& new_symlink,
    std::error_code& ec) noexcept;
  */

  path current_path()
  {
    std::error_code ec;
    auto tmp = current_path(ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::current_path", ec);
    }
    return tmp;
  }

  path current_path(std::error_code& ec)
  {
    char temp[PATH_MAX];
    if (::getcwd(temp, PATH_MAX) == nullptr) {
      ec = {errno, std::system_category()};
    } else {
      ec.clear();
    }
    return path(temp);
  }

  void current_path(const path& p)
  {
    std::error_code ec;
    current_path(p, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::current_path", p, ec);
    }
  }

  void current_path(const path& p, std::error_code& ec) noexcept
  {
    if (chdir(p.c_str()) == 0) {
      ec = {errno, std::system_category()};
    } else {
      ec.clear();
    }
  }

  bool equivalent(const path& p1, const path& p2)
  {
    std::error_code ec;
    auto tmp = equivalent(p1, p2, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::equivalent", p1, p2, ec);
    }
    return tmp;
  }

  bool equivalent(const path& p1, const path& p2, std::error_code& ec) noexcept
  {
    struct stat st1;
    struct stat st2;
    if (::stat(p1.c_str(), &st1) || ::stat(p2.c_str(), &st2)) {
      ec = {errno, std::system_category()};
      return false;
    } else {
      ec.clear();
      return st1.st_dev == st2.st_dev && st1.st_ino == st2.st_ino;
    }
  }

  bool exists(file_status status) noexcept
  {
    return status.type() != file_type::not_found;
  }

  bool exists(const path& p)
  {
    return exists(status(p));
  }

  bool exists(const path& p, std::error_code& ec) noexcept
  {
    return exists(status(p, ec));
  }

  bool is_block_file(file_status status) noexcept
  {
    return status.type() == file_type::block;
  }

  bool is_block_file(const path& p)
  {
    return is_block_file(status(p));
  }

  bool is_block_file(const path& p, std::error_code& ec) noexcept
  {
    return is_block_file(status(p, ec));
  }

  bool is_character_file(file_status status) noexcept
  {
    return status.type() == file_type::character;
  }

  bool is_character_file(const path& p)
  {
    return is_character_file(status(p));
  }

  bool is_character_file(const path& p, std::error_code& ec) noexcept
  {
    return is_character_file(status(p, ec));
  }

  bool is_directory(file_status status) noexcept
  {
    return status.type() == file_type::directory;
  }

  bool is_directory(const path& p)
  {
    return is_directory(status(p));
  }

  bool is_directory(const path& p, std::error_code& ec) noexcept
  {
    return is_directory(status(p, ec));
  }

  bool is_fifo(file_status status) noexcept
  {
    return status.type() == file_type::fifo;
  }

  bool is_fifo(const path& p)
  {
    return is_fifo(status(p));
  }

  bool is_fifo(const path& p, std::error_code& ec) noexcept
  {
    return is_fifo(status(p, ec));
  }

  bool is_other(file_status status) noexcept
  {
    return exists(status) && !is_regular_file(status) &&
           !is_directory(status) && !is_symlink(status);
  }

  bool is_other(const path& p)
  {
    return is_other(status(p));
  }

  bool is_other(const path& p, std::error_code& ec) noexcept
  {
    return is_other(status(p, ec));
  }

  bool is_regular_file(file_status status) noexcept
  {
    return status.type() == file_type::regular;
  }

  bool is_regular_file(const path& p)
  {
    return is_regular_file(status(p));
  }

  bool is_regular_file(const path& p, std::error_code& ec) noexcept
  {
    return is_regular_file(status(p, ec));
  }

  bool is_socket(file_status status) noexcept
  {
    return status.type() == file_type::socket;
  }

  bool is_socket(const path& p)
  {
    return is_socket(status(p));
  }

  bool is_socket(const path& p, std::error_code& ec) noexcept
  {
    return is_socket(status(p, ec));
  }

  bool is_symlink(file_status status) noexcept
  {
    return status.type() == file_type::symlink;
  }

  bool is_symlink(const path& p)
  {
    return is_symlink(status(p));
  }

  bool is_symlink(const path& p, std::error_code& ec) noexcept
  {
    return is_symlink(status(p, ec));
  }

  uintmax_t file_size(const path& p)
  {
    std::error_code ec;
    auto res = file_size(p, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::file_size", p, ec);
    }
    return res;
  }

  uintmax_t file_size(const path& p, std::error_code& ec) noexcept
  {
    auto st = px::stat(p, ec);
    return px::file_size(st, ec);
  }

  uintmax_t hard_link_count(const path& p)
  {
    std::error_code ec;
    auto res = hard_link_count(p, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::hard_link_count", p, ec);
    }
    return res;
  }

  uintmax_t hard_link_count(const path& p, std::error_code& ec) noexcept
  {
    auto st = px::stat(p, ec);
    return px::hard_link_count(st, ec);
  }

  file_time_type last_write_time(const path& p)
  {
    std::error_code ec;
    auto res = last_write_time(p, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::last_write_time", p, ec);
    }
    return res;
  }

  file_time_type last_write_time(const path& p, std::error_code& ec) noexcept
  {
    auto st = px::stat(p, ec);
    return px::last_write_time(st, ec);
  }

  file_status status(const path& p)
  {
    std::error_code ec;
    auto res = status(p, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::status", p, ec);
    }
    return res;
  }

  file_status status(const path& p, std::error_code& ec) noexcept
  {
    struct stat st;
    return px::status(p, st, ec);
  }

  file_status symlink_status(const path& p)
  {
    std::error_code ec;
    auto res = symlink_status(p, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::symlink_status", p, ec);
    }
    return res;
  }

  file_status symlink_status(const path& p, std::error_code& ec) noexcept
  {
    struct stat st;
    return px::status(p, st, ec);
  }

  /*
    void permissions(const path& p, perms prms,
    perm_options opts);
    void permissions(const path& p, perms prms, std::error_code& ec) noexcept;
    void permissions(const path& p, perms prms, perm_options opts,
    std::error_code& ec);

    path proximate(const path& p, std::error_code& ec);
    path proximate(const path& p, const path& base = current_path());
    path proximate(const path& p, const path& base, std::error_code& ec);

    path read_symlink(const path& p);
    path read_symlink(const path& p, std::error_code& ec);

    path relative(const path& p, std::error_code& ec);
    path relative(const path& p, const path& base);
    path relative(const path& p, const path& base, std::error_code& ec);
  */

  bool remove(const path& p)
  {
    std::error_code ec;
    auto tmp = remove(p, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::remove", p, ec);
    }
    return tmp;
  }

  bool remove(const path& p, std::error_code& ec) noexcept
  {
    if (!exists(p, ec)) return false;
    if (::remove(p.c_str())) {
      ec = {errno, std::system_category()};
      return false;
    } else {
      ec.clear();
      return true;
    }
  }

  uintmax_t remove_all(const path& p)
  {
    std::error_code ec;
    auto tmp = remove_all(p, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::remove_all", p, ec);
    }
    return tmp;
  }

  uintmax_t remove_all(const path& p, std::error_code& ec) noexcept
  {
    uintmax_t n = 0;
    if (is_directory(p, ec)) {
      if (ec) return -1;
      for (auto&& de : recursive_directory_iterator(p)) {
        remove(de, ec);
        if (ec) return -1;
        n++;
      }
      n += static_cast<uintmax_t>(remove(p, ec));
    }
    if (ec) return -1;
    return n;
  }


  void rename(const path& from, const path& to)
  {
    std::error_code ec;
    rename(from, to, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::rename", from, to, ec);
    }
  }

  void rename(const path& from, const path& to, std::error_code& ec) noexcept
  {
    if (::rename(from.c_str(), to.c_str())) {
      ec = {errno, std::system_category()};
    } else {
      ec.clear();
    }
  }

  void resize_file(const path& p, uintmax_t size)
  {
    std::error_code ec;
    resize_file(p, size, ec);
    if (ec != std::error_code()) {
      throw filesystem_error("In filesystem::resize_file", p, ec);
    }
  }

  void resize_file(const path& p, uintmax_t size, std::error_code& ec) noexcept
  {
    if (::truncate(p.c_str(), static_cast<off_t>(size))) {
      ec = {errno, std::system_category()};
    } else {
      ec.clear();
    }
  }

  /*
    space_info space(const path& p);
    space_info space(const path& p, std::error_code& ec) noexcept;

    file_status status(const path& p);
    file_status status(const path& p, std::error_code& ec) noexcept;

    bool status_known(file_status s) noexcept;

    file_status symlink_status(const path& p);
    file_status symlink_status(const path& p, std::error_code& ec) noexcept;

    path temp_directory_path();
    path temp_directory_path(std::error_code& ec);

    path weakly_canonical(const path& p);
    path weakly_canonical(const path& p, std::error_code& ec);
  */

} // namespace otto::filesystem
