//
// dsa is a utility library of data structures and algorithms built with C++11.
// This file (ringbuffer.hpp) is part of the dsa project.
//
// ringbuffer; a fixed-size implementation of an STL-style circular buffer for
// C++11 and later.
//
// A description of the circular buffer data structure can be found here:
//
//      https://en.wikipedia.org/wiki/Circular_buffer
//
// author: Dalton Woodard
// contact: daltonmwoodard@gmail.com
// repository: https://github.com/daltonwoodard/ringbuffer.git
// license:
//
// Copyright (c) 2016 DaltonWoodard. See the COPYRIGHT.md file at the top-level
// directory or at the listed source repository for details.
//
//      Licensed under the Apache License. Version 2.0:
//          https://www.apache.org/licenses/LICENSE-2.0
//      or the MIT License:
//          https://opensource.org/licenses/MIT
//      at the licensee's option. This file may not be copied, modified, or
//      distributed except according to those terms.
//

#ifndef DSA_RINGBUFFER_HPP
#define DSA_RINGBUFFER_HPP

#include <array>        // std::array
#include <exception>    // std::runtime_error
#include <type_traits>  // std::remove_cv, std::is_nothrow_move_assignable,
                        // std::is_nothrow_copy_assignable,
                        // std::is_nothrow_destructible
#include <utility>      // std::forward, std::move, std::swap


namespace dsa
{
namespace
{
    template <typename T>
    struct memblock
    {
        alignas (alignof (T)) unsigned char data [sizeof (T)];
    };
}   // annonymous namespace

    /*
     *  Description
     *  -----------
     *
     *  dsa::ringbuffer <> is an implementation of an STL-style circular buffer.
     *
     *  A description of the circular buffer data structure can be found here:
     *
     *      https://en.wikipedia.org/wiki/Circular_buffer
     *
     *  The size of the buffer is fixed by the template parameter N. Please see
     *  https://github.com/daltonwoodard/dynamic_ringbuffer.git for a resizeable
     *  version.
     *
     *  This implementation is NOT threadsafe. Please see
     *  https://github.com/daltonwoodard/atomic_ringbuffer.git for a thread-safe
     *  version implemented with C++ atomic primitives.
     *
     *  If and only if the stored object type T has strong exception safe
     *  constructors is the following guaranteed:
     *
     *  If this object is successful constructed, then throughout the
     *  object's lifetime:
     *
     *      i.  all view operations are guaranteed as nothrow
     *      ii. write operations provide the strong exception safety guarantee
     *
     *  Template Parameters
     *  -------------------
     *  - T: the object type to be buffered. This type does *not* have to be
     *  default constructable.
     *
     *  - N: the maximum number of elements for the buffer to hold; the number N
     *  must be nonzero.
     *
     *  Class Scoped Enumerations
     *  -------------------------
     *  - ringbuffer::overwrite_policy [default: no_overwrite]:
     *
     *      Controls behavior of the container when capacity == 0:
     *
     *          if the value is equal to overwrite, then upon a call to
     *          push/push_back or emplace/emplace_back the value held previously
     *          at the front of the buffer is overwritten;
     *
     *          if the value is equal to no_overwrite, then upon a call to
     *          push/push_back or emplace/emplace_back an exception of type
     *          std::runtime_error is emitted.
     *
     *  Member Types
     *  ------------
     *  - value_type:      T;
     *  - size_type:       std::size_t;
     *  - difference_type: std::ptrdiff_t;
     *  - pointer:         value_type *;
     *  - const_pointer:   value_type const *;
     *  - reference:       value_type &;
     *  - const_reference: value_type const &;
     *
     *  Constructors
     *  ------------
     *  ringbuffer (void):
     *      - default constructs buffer; overwrite policy is defaulted
     *      - nothrow
     *
     *  ringbuffer (ringbuffer const &)
     *      - copy constructs buffer; copies overwrite policy
     *      - nothrow if T is nothrow copy constructible
     *
     *  ringbuffer (ringbuffer &&)
     *      - move constructs buffer; copies overwrite policy
     *      - nothrow if T is nothrow move constructible
     *
     *  Assignment Operators
     *  --------------------
     *  operator= (ringbuffer const &)
     *      - copy assigns buffer; copies overwrite policy
     *      - nothrow if T is nothrow destructible and T is nothrow copy
     *        constructible
     *
     *  operator= (ringbuffer &&)
     *      - move assigns buffer; copies overwrite policy
     *      - nothrow if T is nothrow destructible and T is nothrow move
     *        constructible
     *
     *  Member Functions
     *  ----------------
     *  - front:      access the first element
     *  - back:       access the last element
     *
     *  - empty:    checks whether the buffer is empty
     *  - size:     returns the number of buffered elements
     *  - max_size: returns the maximum possible number of elements; this is
     *              equal to N by definition.
     *  - capacity: returns the number of elements that can be held in currently
     *              allocated storage; this is equal to N by definition.
     *
     *  - set_overwrite_policy: sets the overwrite policy for the container
     *  - get_overwrite_policy: returns the overwrite policy for the container
     *
     *  - clear:                clears the contents of the buffer
     *  - push/push_back:       inserts an element at the end
     *  - emplace/emplace_back: constructs an element in-place at the end
     *  - pop/pop_front:        removes the first element
     *
     *  - swap: swaps the contents. Template typename T must be Swappable.
     */
    template <typename T, std::size_t N>
    class ringbuffer
    {
        static_assert (N > 0, "empty ringbuffer is not allowed");

    public:
        enum class overwrite_policy
        {
            no_overwrite = 0,
            overwrite
        };

    private:
        using backing_type            = std::array <memblock <T>, N>;
        using backing_pointer         = typename backing_type::pointer;
        using backing_const_pointer   = typename backing_type::const_pointer;
        using backing_reference       = typename backing_type::reference;
        using backing_const_reference = typename backing_type::const_reference;

        backing_type _buffer;
        std::size_t _buffered;

        backing_pointer const _first = &_buffer [0];
        backing_pointer const _last  = &_buffer [N - 1];

        enum overwrite_policy _owpolicy;

        template <typename U, std::size_t BuffSize>
        class iterator_impl;

        /*
         * The iterators _tail and _head are privileged in
         * that the logical space they work in is the whole buffer. They are
         * later used to represent the bounding logical regions when creating
         * iterators to the buffer.
         */
        iterator_impl <T, N> _tail {
            reinterpret_cast <T *> (&_buffer [0]),
            reinterpret_cast <T *> (_first),
            reinterpret_cast <T *> (_last),
            reinterpret_cast <T *> (_first),
            reinterpret_cast <T *> (_last)
        };

        iterator_impl <T, N> _head  {
            reinterpret_cast <T *> (&_buffer [0]),
            reinterpret_cast <T *> (_first),
            reinterpret_cast <T *> (_last),
            reinterpret_cast <T *> (_first),
            reinterpret_cast <T *> (_last)
        };

        template <typename U, std::size_t BuffSize>
        class iterator_impl : public std::iterator <
            std::random_access_iterator_tag, U, std::ptrdiff_t, U *, U &
        >
        {
        private:
            using iter_type = std::iterator <
                std::random_access_iterator_tag, U, std::ptrdiff_t, U *, U &
            >;

            U * _iter;

            /*
             * these pointers bound the logical region with the current state of
             * the circular buffer.
             */
            U * _lfirst;
            U * _llast;

            /* these pointers bound the address space of the backing buffer */
            U * _rfirst;
            U * _rlast;

            /* checks whether the logical region is actually contiguous */
            bool logical_region_is_contiguous (void) const noexcept
            {
                return _lfirst <= _llast;
            }

        public:
            using difference_type   = typename iter_type::difference_type;
            using value_type        = typename iter_type::value_type;
            using pointer           = typename iter_type::pointer;
            using reference         = typename iter_type::reference;
            using iterator_category = typename iter_type::iterator_category;

            iterator_impl (void) = delete;

            iterator_impl (pointer p,
                           pointer logical_first,
                           pointer logical_last,
                           pointer real_first,
                           pointer real_last)
                noexcept
                : _iter   {p}
                , _lfirst {logical_first}
                , _llast  {logical_last}
                , _rfirst {real_first}
                , _rlast  {real_last}
            {}

            iterator_impl & operator= (iterator_impl const & other) noexcept
                = default;

            void swap (iterator_impl & other) noexcept
            {
                std::swap (this->_iter, other._iter);
                std::swap (this->_first, other._first);
                std::swap (this->_last, other._last);
            }

            iterator_impl & operator++ (void)
            {
                if (_iter == _llast) {
                    _iter = _lfirst;
                } else {
                    _iter += 1;
                }

                return *this;
            }

            iterator_impl & operator-- (void)
            {
                if (_iter == _lfirst) {
                    _iter = _llast;
                } else {
                    _iter -= 1;
                }

                return *this;
            }

            iterator_impl operator++ (int)
            {
                auto const tmp {*this};

                if (_iter == _llast) {
                    _iter = _lfirst;
                } else {
                    _iter += 1;
                }

                return tmp;
            }

            iterator_impl operator-- (int)
            {
                auto const tmp {*this};

                if (_iter == _lfirst) {
                    _iter = _llast;
                } else {
                    _iter -= 1;
                }

                return tmp;
            }

            /*
             * the parameter n is assumed to be valid; that is, such that
             * the resulting pointer after [_iter += n] remains logically
             * bound between _lfirst and _llast.
             */
            iterator_impl & operator+= (difference_type n)
            {
                /*
                 * two cases:
                 *  i.  _lfirst <= _llast in the address space (non-wraparound)
                 *  ii. _llast < _lfirst in the address space (wraparound)
                 *      a. this is above _lfirst
                 *      b. this is below _llast
                 */

                /* case i. */
                if (this->logical_region_is_contiguous ()) {
                    _iter += n;
                /* cast ii.a. */
                } else if (_lfirst <= _iter) {
                    /* stays in-bounds */
                    if (_iter + n <= _rlast) {
                        _iter += n;
                    /* overflow past-the-end (note: n > 0) */
                    } else {
                        _iter = _rfirst + (n - 1 - (_rlast - _iter));
                    }
                /* cast ii.b. */
                } else {
                    /* stays in-bounds */
                    if (_iter + n >= _rfirst) {
                        _iter += n;
                    /* underflows before-the-beginning (note: n < 0) */
                    } else {
                        auto const m {-n};
                        _iter = _rlast - (m - 1 - (_iter - _rfirst));
                    }
                }

                return *this;
            }

            iterator_impl & operator-= (difference_type n)
            {
                return this->operator+= (-n);
            }

            iterator_impl operator+ (difference_type n) const
            {
                auto tmp = *this;
                return (tmp += n); 
            }

            iterator_impl operator- (difference_type n) const
            {
                auto tmp = *this;
                return (tmp -= n);
            }

            difference_type operator- (iterator_impl const & rhs) const
            {
                /* normal configuration -- non-wraparound case */
                if (_lfirst < _llast) {
                    return this->_iter - rhs._iter;
                /*
                 * _last is behind _first (in the address space) --
                 * wraparound case, so the space from _last to _first
                 * is uninitialized.
                 */
                } else {
                    /*
                     * three cases:
                     *  i.    both iters are above _lfirst
                     *  ii.   both iters are below _llast
                     *  iii.  iters are split above _lfirst and below _llast
                     *      a. this is above _lfirst and rhs is below _llast
                     *      b. rhs is above _lfirst and this is below _llast
                     */
                    if (_lfirst <= this->_iter && _lfirst <= rhs._iter) {
                        return this->_iter - rhs._iter;
                    } else if (this->_iter <= _llast && rhs._iter <= _llast) {
                        return this->_iter - rhs._iter;
                    } else if (_lfirst <= this->_iter && rhs._iter <= _llast) {
                        return (this->_iter - rhs._iter) -
                            static_cast <difference_type> (BuffSize);
                    /* if (_first <= rhs._iter && this->_iter <= _last) */
                    } else {
                        return static_cast <difference_type> (BuffSize) -
                            (rhs._iter - this->_iter);
                    }
                }
            }

            bool operator== (iterator_impl const & rhs) const
            {
                return this->_iter == rhs._iter;
            }

            bool operator!= (iterator_impl const & rhs) const
            {
                return this->_iter != rhs._iter;
            }

            bool operator< (iterator_impl const & rhs) const
            {
                /* logical: return this->_iter < rhs._iter; */
                return rhs - *this > 0;
            }

            bool operator> (iterator_impl const & rhs) const
            {
                /* logical: return _iter > rhs._iter; */
                return *this - rhs > 0;
            }

            bool operator<= (iterator_impl const & rhs) const
            {
                /* logical: return _iter <= rhs._iter; */
                if (*this == rhs) {
                    return true;
                } else {
                    return *this < rhs;
                }
            }

            bool operator>= (iterator_impl const & rhs) const
            {
                /* logical: return _iter >= rhs._iter; */
                if (*this == rhs) {
                    return true;
                } else {
                    return *this > rhs;
                }
            }

            reference operator* (void) const
            {
                return *_iter;
            }

            reference operator[] (difference_type n) const
            {
                return *(*this + n);
            }

            pointer addressof (void) const
            {
                return _iter;
            }
        };

        using iterator        = iterator_impl <T, N>;
        using const_iterator  = iterator_impl <T const, N>;

    public:
        using value_type      = T;
        using size_type       = std::size_t;
        using difference_type = std::ptrdiff_t;
        using pointer         = value_type *;
        using const_pointer   = value_type const *;
        using reference       = value_type &;
        using const_reference = value_type const &;

        ringbuffer (void) noexcept
            : _buffer   {}
            , _buffered {0}
            , _owpolicy {overwrite_policy::no_overwrite}
        {}

        ringbuffer (ringbuffer const & other)
            noexcept (std::is_nothrow_copy_constructible <value_type>::value)
            : _buffer   {}
            , _buffered {other._buffered}
            , _owpolicy {other._owpolicy}
        {
            auto ti {this->_tail};
            auto oi {other.cbegin ()};
            auto ob {other._buffered};

            while (ob) {
                auto const addr {ti.addressof ()};
                new (addr) value_type {*oi};
                ti += 1;
                oi += 1;
                ob -= 1;
            }

            this->_tail += this->_buffered;
        }

        ringbuffer (ringbuffer && other)
            noexcept (std::is_nothrow_move_constructible <value_type>::value)
            : _buffer   {}
            , _buffered {other._buffered}
            , _owpolicy {other._owpolicy}
        {
            auto ti {this->_tail};
            auto oi {other.cbegin ()};
            auto ob {other._buffered};

            while (ob) {
                auto const addr {ti.addressof ()};
                new (addr) value_type {std::move (*oi)};
                ti += 1;
                oi += 1;
                ob -= 1;
            }

            this->_tail += this->_buffered;
        }

        ringbuffer & operator= (ringbuffer const & other)
            noexcept (
                std::is_nothrow_copy_constructible <value_type>::value &&
                std::is_nothrow_destructible <value_type>::value
            )
        {
            this->clear ();
            this->_owpolicy = other._owpolicy;

            auto oi {other.cbegin ()};
            auto ob {other._buffered};

            while (ob) {
                auto const addr {this->_tail.addressof ()};
                new (addr) value_type {*oi};
                oi += 1;
                ob -= 1;

                /*
                 * we leave this here in the case that T is not nothrow copy
                 * constructible, so that in the case of an exception being
                 * thrown the container remains in a consistent state.
                 */
                this->_buffered += 1;
                this->_tail += 1;
            }

            return *this;
        }

        ringbuffer & operator= (ringbuffer && other)
            noexcept (
                std::is_nothrow_move_constructible <value_type>::value &&
                std::is_nothrow_destructible <value_type>::value
            )
        {
            this->clear ();
            this->_owpolicy = other._owpolicy;

            auto oi {other.cbegin ()};
            auto ob {other._buffered};

            while (ob) {
                auto const addr {this->_tail.addressof ()};
                new (addr) value_type {std::move (*oi)};
                oi += 1;
                ob -= 1;

                /*
                 * we leave this here in the case that T is not nothrow move
                 * constructible, so that in the case of an exception being
                 * thrown the container remains in a consistent state.
                 */
                this->_buffered += 1;
                this->_tail += 1;
            }

            return *this;
        }

    private:
        static void destruct (pointer p)
            noexcept (std::is_nothrow_destructible <value_type>::value)
        {
            p->~value_type ();
        }

    public:
        ~ringbuffer (void)
            noexcept (std::is_nothrow_destructible <value_type>::value)
        {
            auto it {this->end ()};

            while (_buffered > 0) {
                it -= 1;
                _buffered -= 1;
                destruct (it.addressof ());
            }
        }

        /* swaps the contents of the buffer */
        void swap (ringbuffer & other)
            noexcept (
                std::is_nothrow_destructible <value_type>::value &&
                std::is_nothrow_move_constructible <value_type>::value &&
                // TODO: replace this with a portable custom implementation
                std::__is_nothrow_swappable <value_type>::value
            )
        {
            /* swap elements */
            {
                auto ti {this->begin ()};
                auto oi {other.begin ()};

                auto tb {this->_buffered};
                auto ob {other._buffered};

                /*
                 * past-the-end iterators in this implementation point at
                 * uninitialized memory, and so once we have swapped as many
                 * valid objects as possible we must revert to performing
                 * in-place construction of elements into the correct locations.
                 */
                if (tb <= ob) {
                    while (tb) {
                        using std::swap;
                        swap (*ti, *oi);
                        ti += 1;
                        oi += 1;
                        tb -= 1;
                        ob -= 1;
                    }

                    while (ob) {
                        auto const addr {ti.addressof ()};
                        new (addr) value_type {std::move (*oi)};
                        destruct (oi.addressof ());
                        ti += 1;
                        oi += 1;
                        ob -= 1;
                    }
                } else {
                    while (ob) {
                        using std::swap;
                        swap (*oi, *ti);
                        oi += 1;
                        ti += 1;
                        ob -= 1;
                        tb -= 1;
                    }

                    while (tb) {
                        auto const addr {oi.addressof ()};
                        new (addr) value_type {std::move (*ti)};
                        destruct (ti.addressof ());
                        oi += 1;
                        ti += 1;
                        tb -= 1;
                    }
                }
            }

            /*
             * adjust iterators for this and other:
             * - read locations for each stay the same
             * - write locations are adjusted by the difference between
             *   buffered elements of each.
             */
            {
                auto const td {this->_tail - this->_head};
                auto const od {other._tail - other._head};

                this->_tail += (od - td);
                other._tail += (td - od);

                std::swap (this->_buffered, other._buffered);
                std::swap (this->_owpolicy, other._owpolicy);
            }
        }

        /* checks whether the buffer is empty */
        bool empty (void) const noexcept
        {
            return _buffered == 0;
        }

        /* returns the number of elements stored in the buffer */
        std::size_t size (void) const noexcept
        {
            return _buffered;
        }

        /* returns the maximum possible number of elements */
        constexpr std::size_t max_size (void) const noexcept
        {
            return N;
        }

        /*
         * returns the number of elements that can be held in the current
         * storage
         */
        constexpr std::size_t capacity (void) const noexcept
        {
            return N;
        }

        /* set the overwrite policy for the buffer */
        void set_overwrite_policy (enum overwrite_policy pol) noexcept
        {
            this->_owpolicy = pol;
        }

        /* returns the overwrite policy for the buffer */
        enum overwrite_policy get_overwrite_policy (void) const noexcept
        {
            return this->_owpolicy;
        }

    private:
        /* returns an iterator the start of the buffer */
        iterator begin (void) noexcept
        {
            return iterator {
                _head.addressof (),
                _head.addressof (),
                _tail == _head ? _tail.addressof ()
                               : (_tail - 1).addressof (),
                reinterpret_cast <pointer> (_first),
                reinterpret_cast <pointer> (_last)
            };
        }

        /* returns an iterator the end of the buffer */
        iterator end (void) noexcept
        {
            return iterator {
                _tail.addressof (),
                _head.addressof (),
                _tail == _head ? _tail.addressof ()
                               : (_tail - 1).addressof (),
                reinterpret_cast <pointer> (_first),
                reinterpret_cast <pointer> (_last)
            };
        }

        /* returns a const iterator the start of the buffer */
        const_iterator begin (void) const noexcept
        {
            return this->cbegin ();
        }

        /* returns a const iterator the end of the buffer */
        const_iterator end (void) const noexcept
        {
            return this->cend ();
        }

        /* returns a const iterator the start of the buffer */
        const_iterator cbegin (void) const noexcept
        {
            return const_iterator {
                _head.addressof (),
                _head.addressof (),
                _tail == _head ? _tail.addressof ()
                               : (_tail - 1).addressof (),
                reinterpret_cast <pointer> (_first),
                reinterpret_cast <pointer> (_last)
            };
        }

        /* returns a const iterator the end of the buffer */
        const_iterator cend (void) const noexcept
        {
            return const_iterator {
                _tail.addressof (),
                _head.addressof (),
                _tail == _head ? _tail.addressof ()
                               : (_tail - 1).addressof (),
                reinterpret_cast <pointer> (_first),
                reinterpret_cast <pointer> (_last)
            };
        }
    public:

        /* returns a reference to the first element in the buffer */
        reference front (void) noexcept
        {
            return _head [0];
        }

        /* returns a reference to the first element in the buffer */
        const_reference front (void) const noexcept
        {
            return _head [0];
        }

        /* returns a reference to the last element in the buffer */
        reference back (void) noexcept
        {
            return _tail == _head ? _tail [0] : _tail [-1];
        }

        /* returns a reference to the last element in the buffer */
        const_reference back (void) const noexcept
        {
            return _tail == _head ? _tail [0] : _tail [-1];
        }

        /*
         * clears the contents of the buffer; the elements are guaranteed to be
         * destructed in the reverse-order they were added.
         */
        void clear (void)
            noexcept (noexcept (destruct (std::declval <pointer> ())))
        {
            auto it {this->end ()};

            while (_buffered > 0) {
                it -= 1;
                _buffered -= 1;
                destruct (it.addressof ());
            }

            _tail = _head;
        }

        /*
         * Adds an object to the buffer if room is available.
         *
         * If no capacity is available, then:
         *      If the overwrite policy is set to no_overwrite this method
         *      throws an exception of type std::runtime_error.
         *
         *      If the overwrite policy is set to overwrite, this method
         *      overwrites the first element of the buffer.
         */
        void push (value_type const & v)
        {
            if (_buffered < N) {
                auto const addr {_tail.addressof ()};
                new (addr) value_type {v};
                _tail += 1;
                _buffered += 1;
            } else if (_owpolicy == overwrite_policy::overwrite) {
                auto const addr {_tail.addressof ()};
                destruct (addr);
                new (addr) value_type {v};
                _tail += 1;
                _head += 1;
            } else {
                throw std::runtime_error {"push back on full buffer"};
            }
        }

        /*
         * Adds an object to the buffer if room is available.
         *
         * If no capacity is available, then:
         *      If the overwrite policy is set to no_overwrite this method
         *      throws an exception of type std::runtime_error.
         *
         *      If the overwrite policy is set to overwrite, this method
         *      overwrites the first element of the buffer.
         */
        void push (value_type && v)
        {
            if (_buffered < N) {
                auto const addr {_tail.addressof ()};
                new (addr) value_type {std::move (v)};
                _tail += 1;
                _buffered += 1;
            } else if (_owpolicy == overwrite_policy::overwrite) {
                auto const addr {_tail.addressof ()};
                destruct (addr);
                new (addr) value_type {std::move (v)};
                _tail += 1;
                _head += 1;
            } else {
                throw std::runtime_error {"push back on full buffer"};
            }
        }

        void push_back (value_type const & v)
        {
            this->push (v);
        }

        void push_back (value_type && v)
        {
            this->push (std::move (v));
        }

        /*
         * Adds an object to the buffer if room is available using in-place
         * construction.
         *
         * If no capacity is available, then:
         *      If the overwrite policy is set to no_overwrite this method
         *      throws an exception of type std::runtime_error.
         *
         *      If the overwrite policy is set to overwrite, this method
         *      overwrites the first element of the buffer.
         */
        template <typename ... Args>
        void emplace (Args && ... args)
        {
            if (_buffered < N) {
                auto const addr {_tail.addressof ()};
                new (addr) value_type {std::forward <Args> (args)...};
                _tail += 1;
                _buffered += 1;
            } else if (_owpolicy == overwrite_policy::overwrite) {
                auto const addr {_tail.addressof ()};
                destruct (addr);
                new (addr) value_type {std::forward <Args> (args)...};
                _tail += 1;
                _head += 1;
            } else {
                throw std::runtime_error {"emplace back on full buffer"};
            }
        }

        template <typename ... Args>
        void emplace_back (Args && ... args)
        {
            this->emplace (std::forward <Args> (args)...);
        }

        /*
         * removes the first element from buffer if such an element exists, and
         * otherwise does nothing.
         */
        void pop (void)
            noexcept (std::is_nothrow_destructible <value_type>::value)
        {
            if (_buffered > 0) {
                destruct (_head.addressof ());
                _head += 1;
                _buffered -= 1;
            }
        }
    };
}   // namespace dsa

#endif // ifndef DSA_RINGBUFFER_HPP
