#pragma once

#include <string>
#include <vector>
#include <string_view>
#include <memory>

namespace otto::filesystem {

  enum class file_type {
    none = 0,
    not_found,
    regular,
    directory,
    symlink,
    block,
    character,
    fifo,
    socket,
    unknown
  };

  enum class copy_options {
    none = 0,
    skip_existing,
    overwrite_existing,
    update_existing,
    recursive,
    copy_symlinks,
    skip_symlinks,
    directories_only,
    create_symlinks,
    create_hard_links
  };

  enum class perms {
    none = 0,
    owner_read = 0400, // Read permission, owner
    owner_write = 0200, // Write permission, owner
    owner_exec = 0100, // Execute/search permission, owner
    owner_all = 0700, // Read, write, execute/search by owner;
    // owner_read | owner_write | owner_exec
    group_read = 040, // Read permission, group
    group_write = 020, // Write permission, group
    group_exec = 010, // Execute/search permission, group
    group_all = 070, // Read, write, execute/search by group;
    // group_read | group_write | group_exec
    others_read = 04, // Read permission, others
    others_write = 02, // Write permission, others
    others_exec = 01, // Execute/search permission, others
    others_all = 07, // Read, write, execute/search by others;
    // others_read | others_write | others_exec
    all = 0777, // owner_all | group_all | others_all
    set_uid = 04000, // Set-user-ID on execution
    set_gid = 02000, // Set-group-ID on execution
    sticky_bit = 01000, // Operating system dependent.
    mask = 07777, // all | set_uid | set_gid | sticky_bit
    unknown = 0xFFFF
  };

  enum class perm_options {
    replace,
    add,
    remove,
    nofollow
  };

  enum class directory_options {
    none,
    follow_directory_symlink,
    skip_permission_denied
  };

  class file_status {
  public:
    // 30.10.10.1, constructors and destructor

    file_status() noexcept : file_status(file_type::none) {}
    explicit file_status(file_type ft, perms prms = perms::unknown) noexcept;
    file_status(const file_status&) noexcept = default;
    file_status(file_status&&) noexcept = default;
    ~file_status();

    // assignments:

    file_status& operator=(const file_status&) noexcept = default;
    file_status& operator=(file_status&&) noexcept = default;

    // 30.10.10.3, modifiers

    void type(file_type ft) noexcept;
    void permissions(perms prms) noexcept;

    // 30.10.10.2, observers

    file_type type() const noexcept;
    perms permissions() const noexcept;
  private:
    file_type _type;
    perms _perms;
  };

  class path {
  public:

    using value_type = char;
    static constexpr value_type preferred_separator = '/';
    using string_type = std::basic_string<value_type>;

    // 30.10.9.1, enumeration format

    enum format {
      native_format,
      generic_format,
      auto_format
    };

    // 30.10.7.4.1, constructors and destructor

    path() noexcept;
    path(const path& p);
    path(path&& p) noexcept;
    path(string_type&& source, format fmt = auto_format);

    template <class Source>
    path(const Source& source, format fmt = auto_format);
    
    template <class InputIterator>
    path(InputIterator first, InputIterator last, format fmt = auto_format);

    ~path();

    // 30.10.7.4.2, assignments
    path& operator=(const path& p);
    path& operator=(path&& p) noexcept;
    path& operator=(string_type&& source);

    path& assign(string_type&& source);

    template <class Source>
    path& operator=(const Source& source);

    template <class Source>
    path& assign(const Source& source);

    template <class InputIterator>
    path& assign(InputIterator first, InputIterator last);

    // 30.10.7.4.3, appends
    path& operator/=(const path& p);

    template <class Source>
    path& operator/=(const Source& source);

    template <class Source>
    path& append(const Source& source);

    template <class InputIterator>
    path& append(InputIterator first, InputIterator last);

    // 30.10.7.4.4, concatenation
    path& operator+=(const path& x);
    path& operator+=(const string_type& x);
    path& operator+=(std::basic_string_view<value_type> x);
    path& operator+=(const value_type* x);
    path& operator+=(value_type x);

    template <class Source>
    path& operator+=(const Source& x);

    template <class EcharT>
    path& operator+=(EcharT x);

    template <class Source>
    path& concat(const Source& x);

    template <class InputIterator>
    path& concat(InputIterator first, InputIterator last);

    // 30.10.7.4.5, modifiers
    void clear() noexcept;
    path& make_preferred();
    path& remove_filename();
    path& replace_filename(const path& replacement);
    path& replace_extension(const path& replacement = path());
    void swap(path& rhs) noexcept;

    // 30.10.7.4.6, native format observers
    const string_type& native() const noexcept;
    const value_type* c_str() const noexcept;
    operator string_type() const;

    std::string string() const;

    // 30.10.7.4.7, generic format observers
    std::string generic_string() const;

    // 30.10.7.4.8, compare
    int compare(const path& p) const noexcept;
    int compare(const string_type& s) const;
    int compare(std::basic_string_view<value_type> s) const;
    int compare(const value_type* s) const;
    
    // 30.10.7.4.9, decomposition
    path root_name() const;
    path root_directory() const;
    path root_path() const;
    path relative_path() const;
    path parent_path() const;
    path filename() const;
    path stem() const;
    path extension() const;
    
    // 30.10.7.4.10, query
    bool empty() const noexcept;
    bool has_root_name() const;
    bool has_root_directory() const;
    bool has_root_path() const;
    bool has_relative_path() const;
    bool has_parent_path() const;
    bool has_filename() const;
    bool has_stem() const;
    bool has_extension() const;
    bool is_absolute() const;
    bool is_relative() const;
    
    // 30.10.7.4.11, generation
    path lexically_normal() const;
    path lexically_relative(const path& base) const;
    path lexically_proximate(const path& base) const;

    // 30.10.7.5, iterators
    class iterator {
    public:
      using iterator_category = std::bidirectional_iterator_tag;
      using value_type = path;
      using difference_type = ptrdiff_t;
      using pointer = const path*;
      using reference = const path&;

      iterator(const iterator&);
      iterator(iterator&&) noexcept;

      iterator(const path::value_type* first, const path::value_type* ptr);

      iterator& operator=(const iterator&);
      iterator& operator=(iterator&&) noexcept;

      bool operator==(const iterator& rhs) const noexcept;
      bool operator!=(const iterator& rhs) const noexcept;

      path operator*() const;

      iterator& operator++();
      iterator operator++(int);

      iterator& operator--();
      iterator operator--(int);

    private:

      void refresh();
      const path::value_type* _first;
      const path::value_type* _ptr;
      mutable std::size_t _len;
    };

    using const_iterator = iterator;
    iterator begin() const;
    iterator end() const;
    
  protected:
    format _format;
    std::string _path;
  };

  void swap(path& lhs, path& rhs) noexcept;
  size_t hash_value (const path& p) noexcept;
  bool operator< (const path& lhs, const path& rhs) noexcept;
  bool operator<=(const path& lhs, const path& rhs) noexcept;
  bool operator> (const path& lhs, const path& rhs) noexcept;
  bool operator>=(const path& lhs, const path& rhs) noexcept;
  bool operator==(const path& lhs, const path& rhs) noexcept;
  bool operator!=(const path& lhs, const path& rhs) noexcept;
  path operator/ (const path& lhs, const path& rhs) noexcept;

  class directory_entry;

  class directory_iterator {
  public:
    using iterator_category = std::input_iterator_tag;
    using value_type = directory_entry;
    using difference_type = ptrdiff_t;
    using pointer = const directory_entry*;
    using reference = const directory_entry&;

    // 30.10.12.1, member functions
    directory_iterator() noexcept;
    explicit directory_iterator(const path& p);
    directory_iterator(const directory_iterator& rhs);
    directory_iterator(directory_iterator&& rhs) noexcept;

    ~directory_iterator();

    directory_iterator& operator=(const directory_iterator& rhs);
    directory_iterator& operator=(directory_iterator&& rhs) noexcept;

    const directory_entry& operator*() const;
    const directory_entry* operator->() const;
    directory_iterator& operator++();

    // other members as required by 27.2.3, input iterators
    bool operator==(const directory_iterator& other) const;
    bool operator!=(const directory_iterator& other) const;
    directory_iterator operator++(int);

  private:

    directory_entry* _ptr;
    std::shared_ptr<std::vector<directory_entry>> _entries;
  };

  directory_iterator begin(directory_iterator iter) noexcept;
  directory_iterator end(const directory_iterator& iter) noexcept;

  class recursive_directory_iterator {
  public:
    using iterator_category = std::input_iterator_tag;
    using value_type = directory_entry;
    using difference_type = ptrdiff_t;
    using pointer = const directory_entry*;
    using reference = const directory_entry&;

    // 30.10.13.1, constructors and destructor
    recursive_directory_iterator() noexcept;
    explicit recursive_directory_iterator(const path& p);

    recursive_directory_iterator(const recursive_directory_iterator& rhs);
    recursive_directory_iterator(recursive_directory_iterator&& rhs) noexcept;

    ~recursive_directory_iterator();

    // 30.10.13.1, observers
    // directory_options options() const;
    int depth() const;

    const directory_entry& operator*() const;
    const directory_entry* operator->() const;

    // 30.10.13.1, modifiers
    recursive_directory_iterator&
    operator=(const recursive_directory_iterator& rhs);

    recursive_directory_iterator&
    operator=(recursive_directory_iterator&& rhs) noexcept;

    recursive_directory_iterator& operator++();
    void pop();

    // other members as required by 27.2.3, input iterators
    bool operator==(const recursive_directory_iterator& other) const;
    bool operator!=(const recursive_directory_iterator& other) const;
    recursive_directory_iterator operator++(int);
    
  private:
    struct SharedData;

    std::shared_ptr<SharedData> _data;
  };

  recursive_directory_iterator begin(recursive_directory_iterator iter) noexcept;
  recursive_directory_iterator end(const recursive_directory_iterator& iter) noexcept;

  class directory_entry {
  public:
    // 30.10.11.1, constructors and destructor
    directory_entry() noexcept = default;
    directory_entry(const directory_entry&) = default;
    directory_entry(directory_entry&&) noexcept = default;
    explicit directory_entry(const path& p);
    ~directory_entry();
    // assignments:
    directory_entry& operator=(const directory_entry&) = default;
    directory_entry& operator=(directory_entry&&) = default;
    // 30.10.11.2, modifiers
    void assign(const path& p);
    void refresh();
    // 30.10.11.3, observers
    const path& path() const;
    operator const class path&() const;
    bool exists() const;
    bool is_block_file() const;
    bool is_character_file() const;
    bool is_directory() const;
    bool is_fifo() const;
    bool is_other() const;
    bool is_regular_file() const;
    bool is_socket() const;
    bool is_symlink() const;
    uintmax_t file_size() const;
    uintmax_t hard_link_count() const;
    //file_time_type last_write_time() const;
    //file_status status() const;
    //file_status symlink_status() const;
    bool operator< (const directory_entry& rhs) const noexcept;
    bool operator==(const directory_entry& rhs) const noexcept;
    bool operator!=(const directory_entry& rhs) const noexcept;
    bool operator<=(const directory_entry& rhs) const noexcept;
    bool operator> (const directory_entry& rhs) const noexcept;
    bool operator>=(const directory_entry& rhs) const noexcept;
  private:
    class path pathobject; // exposition only
    friend class directory_iterator; // exposition only

    mutable bool _exists;
    mutable bool _block_file;
    mutable bool _character_file;
    mutable bool _directory;
    mutable bool _fifo;
    mutable bool _other;
    mutable bool _regular_file;
    mutable bool _socket;
    mutable bool _symlink;
    mutable uintmax_t _file_size;
    mutable uintmax_t _hard_link_count;
  };

  path current_path();

  path absolute(const path& p);

  bool exists(const path& p);
  bool is_block_file(const path& p);
  bool is_character_file(const path& p);
  bool is_directory(const path& p);
  bool is_fifo(const path& p);
  bool is_other(const path& p);
  bool is_regular_file(const path& p);
  bool is_socket(const path& p);
  bool is_symlink(const path& p);

  size_t file_size(const path& p);
  size_t hard_link_count(const path& p);

  bool create_directory(const path& p);

  bool create_directories(const path& p);
  
  bool remove_file(const path& p);
  bool remove_all(const path& p);

  bool resize_file(const path& p, size_t target_length);

} // namespace otto::filesystem

namespace otto {
  namespace fs = otto::filesystem;
}

// Template definitions ///////////////////////////////////////////////////////

namespace otto::filesystem {
   
  template <class Source>
  path::path(const Source& source, format fmt)
    : path(string_type(source), fmt)
  {}
  
    
  template <class InputIterator>
  path::path(InputIterator first, InputIterator last, format fmt)
    : path(string_type(first, last), fmt)
  {}

  template <class Source>
  path& path::operator=(const Source& source)
  {
    return assign(source);
  }
  
  template <class Source>
  path& path::assign(const Source& source)
  {
    return assign(string_type(source));
  }
  

  template <class InputIterator>
  path& path::assign(InputIterator first, InputIterator last)
  {
    return assign(string_type{first, last});
  }
  
  template <class Source>
  path& path::operator/=(const Source& source)
  {
    return operator/=(path(source));
  }
  
  template <class Source>
  path& path::append(const Source& source)
  {
    return operator/=(path(source));
  }
  
  template <class InputIterator>
  path& path::append(InputIterator first, InputIterator last)
  {
    return operator/=(path(first, last));
  }
   
  template <class Source>
  path& path::operator+=(const Source& x)
  {
    _path.append(path(x).native());
    return *this;
  }
  
  template <class EcharT>
  path& path::operator+=(EcharT x)
  {
    _path.append(path(x).native());
    return *this;
  }
  
  template <class Source>
  path& path::concat(const Source& x)
  {
    _path.append(path(x).native());
    return *this;
  }
  
  template <class InputIterator>
  path& path::concat(InputIterator first, InputIterator last)
  {
    return *this += path(first, last);
  }
  
 
}
