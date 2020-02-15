// Copyright 2018-2020 Rene Rivera
// Copyright 2017 Two Blue Cubes Ltd. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef LYRA_LYRA_HPP
#define LYRA_LYRA_HPP


#ifndef LYRA_ARG_HPP
#define LYRA_ARG_HPP


#ifndef LYRA_PARSER_HPP
#define LYRA_PARSER_HPP


#ifndef LYRA_ARGS_HPP
#define LYRA_ARGS_HPP

#include <initializer_list>
#include <string>
#include <vector>

namespace lyra
{
/* tag::reference[]

[#lyra_args]
= `lyra::args`

Transport for raw args (copied from main args, or supplied via init list).

*/ // end::reference[]
class args
{
	public:
	args(int argc, char const* const* argv)
		: m_exeName(argv[0])
		, m_args(argv + 1, argv + argc)
	{
	}

	args(std::initializer_list<std::string> args)
		: m_exeName(*args.begin())
		, m_args(args.begin() + 1, args.end())
	{
	}

	std::string exe_name() const { return m_exeName; }

	std::vector<std::string>::const_iterator begin() const
	{
		return m_args.begin();
	}

	std::vector<std::string>::const_iterator end() const
	{
		return m_args.end();
	}

	private:
	std::string m_exeName;
	std::vector<std::string> m_args;
};
} // namespace lyra

#endif

#ifndef LYRA_DETAIL_BOUND_HPP
#define LYRA_DETAIL_BOUND_HPP


#ifndef LYRA_DETAIL_INVOKE_LAMBDA_HPP
#define LYRA_DETAIL_INVOKE_LAMBDA_HPP


#ifndef LYRA_DETAIL_PARSE_HPP
#define LYRA_DETAIL_PARSE_HPP


#ifndef LYRA_DETAIL_FROM_STRING_HPP
#define LYRA_DETAIL_FROM_STRING_HPP

#include <algorithm>
#include <sstream>
#include <string>

#ifndef LYRA_CONFIG_OPTIONAL_TYPE
#ifdef __has_include
#if __has_include(<optional>) && __cplusplus >= 201703L
#include <optional>
#define LYRA_CONFIG_OPTIONAL_TYPE std::optional
#endif
#endif
#endif

namespace lyra
{
namespace detail
{
	template <typename T>
	bool to_string(const T& source, std::string& target)
	{
		std::stringstream ss;
		ss << source;
		ss >> target;
		return !ss.fail();
	}

	inline bool to_string(const std::string& source, std::string& target)
	{
		target = source;
		return true;
	}

	inline bool to_string(const char* source, std::string& target)
	{
		target = source;
		return true;
	}

	inline bool to_string(bool source, std::string& target)
	{
		target = source ? "true" : "false";
		return true;
	}

	template <typename S, typename T>
	inline bool from_string(S const& source, T& target)
	{
		std::stringstream ss;
		ss << source;
		T temp{};
		ss >> temp;
		if (!ss.fail() && ss.eof()) { target = temp; return true; }
		return false;
	}

	template <typename S, typename... C>
	inline bool from_string(S const& source, std::basic_string<C...>& target)
	{
		to_string(source, target);
		return true;
	}

	template <typename S>
	inline bool from_string(S const& source, bool& target)
	{
		std::string srcLC;
		to_string(source, srcLC);
		std::transform(srcLC.begin(), srcLC.end(), srcLC.begin(), [](char c) {
			return static_cast<char>(::tolower(c));
		});
		if (srcLC == "y" || srcLC == "1" || srcLC == "true" || srcLC == "yes"
			|| srcLC == "on")
			target = true;
		else if (
			srcLC == "n" || srcLC == "0" || srcLC == "false" || srcLC == "no"
			|| srcLC == "off")
			target = false;
		else
			return false;
		return true;
	}

#ifdef LYRA_CONFIG_OPTIONAL_TYPE
	template <typename S, typename T>
	inline bool
	from_string(S const& source, LYRA_CONFIG_OPTIONAL_TYPE<T>& target)
	{
		T temp;
		auto result = from_string(source, temp);
		if (result) target = std::move(temp);
		return result;
	}
#endif // LYRA_CONFIG_OPTIONAL_TYPE

} // namespace detail
} // namespace lyra

#endif

#ifndef LYRA_PARSER_RESULT_HPP
#define LYRA_PARSER_RESULT_HPP


#ifndef LYRA_DETAIL_RESULT_HPP
#define LYRA_DETAIL_RESULT_HPP

#include <memory>
#include <string>

namespace lyra
{
namespace detail
{
	class result_base
	{
		public:
		enum Type
		{
			Ok,
			LogicError,
			RuntimeError
		};

		result_base const& base() const { return *this; }

		explicit operator bool() const
		{
			return this->m_type == result_base::Ok;
		}

		Type type() const { return m_type; }

		std::string errorMessage() const { return m_errorMessage; }

		protected:
		Type m_type;
		std::string m_errorMessage; // Only populated if resultType is an error

		explicit result_base(Type type, const std::string& message = "")
			: m_type(type)
			, m_errorMessage(message)
		{
		}

		virtual ~result_base() = default;
	};

	template <typename T>
	class result_value_base : public result_base
	{
		public:
		using value_type = T;

		value_type const& value() const { return *m_value; }
		bool has_value() const { return m_value; }

		protected:
		std::unique_ptr<value_type> m_value;

		explicit result_value_base(Type type, const std::string& message = "")
			: result_base(type, message)
		{
		}

		explicit result_value_base(
			Type type, const value_type& val, const std::string& message = "")
			: result_base(type, message)
		{
			m_value.reset(new value_type(val));
		}

		explicit result_value_base(result_value_base const& other)
			: result_base(other)
		{
			if (other.m_value) m_value.reset(new value_type(*other.m_value));
		}

		result_value_base& operator=(result_value_base const& other)
		{
			result_base::operator=(other);
			if (other.m_value) m_value.reset(new T(*other.m_value));
			return *this;
		}
	};

	template <>
	class result_value_base<void> : public result_base
	{
		public:
		using value_type = void;

		protected:
		using result_base::result_base;
	};

	template <typename T>
	class basic_result : public result_value_base<T>
	{
		public:
		using value_type = typename result_value_base<T>::value_type;

		explicit basic_result(result_base const& other)
			: result_value_base<T>(other.type(), other.errorMessage())
		{
		}


		static basic_result ok(value_type const& val)
		{
			return basic_result(result_base::Ok, val);
		}

		static basic_result
		logicError(value_type const& val, std::string const& message)
		{
			return basic_result(result_base::LogicError, val, message);
		}

		static basic_result
		runtimeError(value_type const& val, const std::string& message)
		{
			return basic_result(result_base::RuntimeError, val, message);
		}

		protected:
		using result_value_base<T>::result_value_base;
	};

	template <>
	class basic_result<void> : public result_value_base<void>
	{
		public:
		using value_type = typename result_value_base<void>::value_type;

		explicit basic_result(result_base const& other)
			: result_value_base<void>(other.type(), other.errorMessage())
		{
		}


		static basic_result ok() { return basic_result(result_base::Ok); }

		static basic_result logicError(std::string const& message)
		{
			return basic_result(result_base::LogicError, message);
		}

		static basic_result runtimeError(std::string const& message)
		{
			return basic_result(result_base::RuntimeError, message);
		}

		protected:
		using result_value_base<void>::result_value_base;
	};
} // namespace detail
} // namespace lyra

#endif

namespace lyra
{

enum class parser_result_type
{
	matched,
	no_match,
	short_circuit_all,
	short_circuit_same
};

using result = detail::basic_result<void>;

using parser_result = detail::basic_result<parser_result_type>;

} // namespace lyra

#endif

#include <string>

namespace lyra
{
namespace detail
{
	template <typename S, typename T>
	parser_result parse_string(S const& source, T& target)
	{
		if (from_string(source, target))
			return parser_result::ok(parser_result_type::matched);
		else
			return parser_result::runtimeError(
				parser_result_type::no_match,
				"Unable to convert '" + source + "' to destination type");
	}
} // namespace detail
} // namespace lyra

#endif

#ifndef LYRA_DETAIL_UNARY_LAMBDA_TRAITS_HPP
#define LYRA_DETAIL_UNARY_LAMBDA_TRAITS_HPP

#include <type_traits>

namespace lyra
{
namespace detail
{
	template <typename L>
	struct unary_lambda_traits : unary_lambda_traits<decltype(&L::operator())>
	{
	};

	template <typename ClassT, typename ReturnT, typename... Args>
	struct unary_lambda_traits<ReturnT (ClassT::*)(Args...) const>
	{
		static const bool isValid = false;
	};

	template <typename ClassT, typename ReturnT, typename ArgT>
	struct unary_lambda_traits<ReturnT (ClassT::*)(ArgT) const>
	{
		static const bool isValid = true;
		using ArgType = typename std::remove_const<
			typename std::remove_reference<ArgT>::type>::type;
		using ReturnType = ReturnT;
	};

} // namespace detail
} // namespace lyra

#endif

namespace lyra
{
namespace detail
{
	template <typename ReturnType>
	struct LambdaInvoker
	{
		template <typename L, typename ArgType>
		static parser_result invoke(L const& lambda, ArgType const& arg)
		{
			return lambda(arg);
		}
	};

	template <>
	struct LambdaInvoker<void>
	{
		template <typename L, typename ArgType>
		static parser_result invoke(L const& lambda, ArgType const& arg)
		{
			lambda(arg);
			return parser_result::ok(parser_result_type::matched);
		}
	};

	template <typename ArgType, typename L>
	inline parser_result invokeLambda(L const& lambda, std::string const& arg)
	{
		ArgType temp{};
		auto result = parse_string(arg, temp);
		return !result
			? result
			: LambdaInvoker<typename unary_lambda_traits<L>::ReturnType>::
				  invoke(lambda, temp);
	}
} // namespace detail
} // namespace lyra

#endif
#include <string>

namespace lyra
{
namespace detail
{
	struct NonCopyable
	{
		NonCopyable() = default;
		NonCopyable(NonCopyable const&) = delete;
		NonCopyable(NonCopyable&&) = delete;
		NonCopyable& operator=(NonCopyable const&) = delete;
		NonCopyable& operator=(NonCopyable&&) = delete;
	};

	struct BoundRef : NonCopyable
	{
		virtual ~BoundRef() = default;
		virtual auto isContainer() const -> bool { return false; }
		virtual auto isFlag() const -> bool { return false; }
	};
	struct BoundValueRefBase : BoundRef
	{
		virtual auto setValue(std::string const& arg) -> parser_result = 0;
	};
	struct BoundFlagRefBase : BoundRef
	{
		virtual auto setFlag(bool flag) -> parser_result = 0;
		virtual auto isFlag() const -> bool { return true; }
	};

	template <typename T>
	struct BoundValueRef : BoundValueRefBase
	{
		T& m_ref;

		explicit BoundValueRef(T& ref)
			: m_ref(ref)
		{
		}

		auto setValue(std::string const& arg) -> parser_result override
		{
			return parse_string(arg, m_ref);
		}
	};

	template <typename T>
	struct BoundValueRef<std::vector<T>> : BoundValueRefBase
	{
		std::vector<T>& m_ref;

		explicit BoundValueRef(std::vector<T>& ref)
			: m_ref(ref)
		{
		}

		auto isContainer() const -> bool override { return true; }

		auto setValue(std::string const& arg) -> parser_result override
		{
			T temp;
			auto result = parse_string(arg, temp);
			if (result) m_ref.push_back(temp);
			return result;
		}
	};

	struct BoundFlagRef : BoundFlagRefBase
	{
		bool& m_ref;

		explicit BoundFlagRef(bool& ref)
			: m_ref(ref)
		{
		}

		auto setFlag(bool flag) -> parser_result override
		{
			m_ref = flag;
			return parser_result::ok(parser_result_type::matched);
		}
	};

	template <typename L>
	struct BoundLambda : BoundValueRefBase
	{
		L m_lambda;

		static_assert(
			unary_lambda_traits<L>::isValid,
			"Supplied lambda must take exactly one argument");
		explicit BoundLambda(L const& lambda)
			: m_lambda(lambda)
		{
		}

		auto setValue(std::string const& arg) -> parser_result override
		{
			return invokeLambda<typename unary_lambda_traits<L>::ArgType>(
				m_lambda, arg);
		}
	};

	template <typename L>
	struct BoundFlagLambda : BoundFlagRefBase
	{
		L m_lambda;

		static_assert(
			unary_lambda_traits<L>::isValid,
			"Supplied lambda must take exactly one argument");
		static_assert(
			std::is_same<typename unary_lambda_traits<L>::ArgType, bool>::value,
			"flags must be boolean");

		explicit BoundFlagLambda(L const& lambda)
			: m_lambda(lambda)
		{
		}

		auto setFlag(bool flag) -> parser_result override
		{
			return LambdaInvoker<typename unary_lambda_traits<L>::ReturnType>::
				invoke(m_lambda, flag);
		}
	};
} // namespace detail
} // namespace lyra

#endif

#ifndef LYRA_DETAIL_CHOICES_HPP
#define LYRA_DETAIL_CHOICES_HPP

#include <algorithm>
#include <initializer_list>
#include <string>
#include <type_traits>
#include <vector>

namespace lyra
{
namespace detail
{
	/*
	Type erased base for set of choices. I.e. it's an "interface".
	*/
	struct choices_base
	{
		virtual ~choices_base() = default;
		virtual parser_result contains_value(std::string const& val) const = 0;
	};

	/*
	Stores a set of choice values and provides checking if a given parsed
	string value is one of the choices.
	*/
	template <typename T>
	struct choices_set : choices_base
	{
		std::vector<T> values;

		template <typename... Vals>
		explicit choices_set(Vals... vals)
			: choices_set({ vals... })
		{
		}

		parser_result contains_value(std::string const& val) const override
		{
			T value;
			auto parse = parse_string(val, value);
			if (!parse)
			{
				return parser_result::runtimeError(
					parser_result_type::no_match, parse.errorMessage());
			}
			bool result = std::count(values.begin(), values.end(), value) > 0;
			if (result)
			{
				return parser_result::ok(parser_result_type::matched);
			}
			return parser_result::runtimeError(
				parser_result_type::no_match,
				"Value '" + val + "' not expected. Allowed values are: "
					+ this->to_string());
		}

		std::string to_string() const
		{
			std::string result;
			for (const T& val : values)
			{
				if (!result.empty()) result += ", ";
				std::string val_string;
				if (detail::to_string(val, val_string))
				{
					result += val_string;
				}
				else
				{
					result += "<value error>";
				}
			}
			return result;
		}

		protected:
		explicit choices_set(std::initializer_list<T> const& vals)
			: values(vals)
		{
		}
	};

	template <>
	struct choices_set<const char*> : choices_set<std::string>
	{
		template <typename... Vals>
		explicit choices_set(Vals... vals)
			: choices_set<std::string>(vals...)
		{
		}
	};

	/*
	Calls a designated function to check if the choice is valid.
	*/
	template <typename Lambda>
	struct choices_check : choices_base
	{
		static_assert(
			unary_lambda_traits<Lambda>::isValid,
			"Supplied lambda must take exactly one argument");
		static_assert(
			std::is_same<
				bool, typename unary_lambda_traits<Lambda>::ReturnType>::value,
			"Supplied lambda must return bool");

		Lambda checker;
		using value_type = typename unary_lambda_traits<Lambda>::ArgType;

		explicit choices_check(Lambda const& checker)
			: checker(checker)
		{
		}

		parser_result contains_value(std::string const& val) const override
		{
			value_type value;
			auto parse = parse_string(val, value);
			if (!parse)
			{
				return parser_result::runtimeError(
					parser_result_type::no_match, parse.errorMessage());
			}
			if (checker(value))
			{
				return parser_result::ok(parser_result_type::matched);
			}
			return parser_result::runtimeError(
				parser_result_type::no_match,
				"Value '" + val + "' not expected.");
		}
	};
} // namespace detail
} // namespace lyra

#endif

#ifndef LYRA_DETAIL_TOKENS_HPP
#define LYRA_DETAIL_TOKENS_HPP

#include <string>
#include <vector>

namespace lyra
{
namespace detail
{
	enum class token_type
	{
		unknown,
		option,
		argument
	};

	template <typename Char, class Traits = std::char_traits<Char>>
	class basic_token_name
	{
		public:
		using traits_type = Traits;
		using value_type = Char;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using const_iterator = const_pointer;
		using iterator = const_iterator;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;
		using reverse_iterator = const_reverse_iterator;
		using string_type = std::basic_string<value_type, traits_type>;

		basic_token_name() noexcept
			: str { nullptr }
			, len { 0 }
		{
		}

		basic_token_name(const basic_token_name&) noexcept = default;

		basic_token_name(const_pointer s) noexcept
			: str { s }
			, len { traits_type::length(s) }
		{
		}

		basic_token_name(const_pointer s, size_type count) noexcept
			: str { s }
			, len { count }
		{
		}

		basic_token_name& operator=(const basic_token_name&) noexcept = default;

		void swap(basic_token_name& other) noexcept
		{
			auto tmp = *this;
			*this = other;
			other = tmp;
		}

		const_iterator begin() const noexcept { return this->str; }
		const_iterator end() const noexcept { return this->str + this->len; }
		const_iterator cbegin() const noexcept { return this->str; }
		const_iterator cend() const noexcept { return this->str + this->len; }

		size_type size() const noexcept { return this->len; }
		size_type length() const noexcept { return this->len; }
		bool empty() const noexcept { return this->len == 0; }

		friend string_type to_string(const basic_token_name& t)
		{
			return { t.str, t.len };
		}

		friend string_type
		operator+(const_pointer lhs, const basic_token_name& rhs)
		{
			return lhs + to_string(rhs);
		}

		private:
		const_pointer str;
		size_type len;
	};

	using token_name = std::string;

	struct token
	{
		token_type type;
		token_name name;

		token()
			: type(token_type::unknown)
		{
		}
		token(const token& other) = default;
		token(token_type t, const token_name& n)
			: type(t)
			, name(n)
		{
		}

		explicit operator bool() const { return type != token_type::unknown; }
	};

	class token_iterator
	{
		public:
		template <typename Span>
		explicit token_iterator(
			Span const& args, std::string const& dels,
			std::string const& opt_prefix)
			: delimiters(dels)
			, option_prefix(opt_prefix)
			, args_i(args.begin())
			, args_e(args.end())
			, args_i_sub(1)
		{
		}

		explicit operator bool() const noexcept { return args_i != args_e; }

		token_iterator& pop(const token& arg_or_opt)
		{
			if (arg_or_opt.type == token_type::option
				&& has_short_option_prefix())
			{
				if (++args_i_sub >= args_i->size())
				{
					++args_i;
					args_i_sub = 1;
				}
			}
			else
			{
				++args_i;
				args_i_sub = 1;
			}
			return *this;
		}

		token_iterator& pop(const token& /* opt */, const token& /* val */)
		{
			if (has_short_option_prefix() && args_i->size() > 2)
				++args_i;
			else if (!has_value_delimiter())
				args_i += 2;
			else
				++args_i;
			args_i_sub = 1;
			return *this;
		}

		bool has_option_prefix() const noexcept
		{
			return (args_i != args_e) && is_opt_prefix((*args_i)[0]);
		}

		bool has_short_option_prefix() const noexcept
		{
			return (args_i != args_e) && is_opt_prefix((*args_i)[0])
				&& !is_opt_prefix((*args_i)[1]);
		}

		bool has_long_option_prefix() const noexcept
		{
			return (args_i != args_e) && is_opt_prefix((*args_i)[0])
				&& is_opt_prefix((*args_i)[1]);
		}

		bool has_value_delimiter() const noexcept
		{
			return (args_i != args_e)
				&& (args_i->find_first_of(delimiters) != std::string::npos);
		}

		token option() const
		{
			if (has_long_option_prefix())
			{
				if (has_value_delimiter())
					return token(
						token_type::option,
						args_i->substr(0, args_i->find_first_of(delimiters)));
				else
					return token(token_type::option, *args_i);
			}
			else if (has_short_option_prefix())
			{
				token t { token_type::option, option_prefix.substr(0, 1) };
				t.name += (*args_i)[args_i_sub];
				return t;
			}
			return token();
		}

		token value() const
		{
			if (has_option_prefix() && has_value_delimiter())
				return token(
					token_type::argument,
					args_i->substr(args_i->find_first_of(delimiters) + 1));
			else if (has_long_option_prefix())
			{
				if (args_i + 1 != args_e)
					return token(token_type::argument, *(args_i + 1));
			}
			else if (has_short_option_prefix())
			{
				if (args_i_sub + 1 < args_i->size())
					return token(
						token_type::argument, args_i->substr(args_i_sub + 1));
				else if (args_i + 1 != args_e)
					return token(token_type::argument, *(args_i + 1));
			}
			return token();
		}

		token argument() const { return token(token_type::argument, *args_i); }

		private:
		std::string delimiters;
		std::string option_prefix;

		std::vector<std::string>::const_iterator args_i;
		std::vector<std::string>::const_iterator args_e;
		std::string::size_type args_i_sub;

		inline bool is_opt_prefix(char c) const noexcept
		{
			auto r = option_prefix.find(c) != std::string::npos;
			return r;
		}
	};
} // namespace detail
} // namespace lyra

#endif

#ifndef LYRA_DETAIL_TRAIT_UTILS_HPP
#define LYRA_DETAIL_TRAIT_UTILS_HPP

#include <type_traits>
#include <utility>

namespace lyra
{
namespace detail
{
	template <class F, class... Args>
	struct is_callable
	{
		template <class U>
		static auto test(U* p) -> decltype(
			(*p)(std::declval<Args>()...), void(), std::true_type());

		template <class U>
		static auto test(...) -> decltype(std::false_type());

		static constexpr bool value = decltype(test<F>(0))::value;
	};

	template <class F>
	struct is_invocable
	{
		template <class U>
		static auto test(U* p) -> decltype(
			(&U::operator()), void(), std::true_type());

		template <class U>
		static auto test(...) -> decltype(std::false_type());

		static constexpr bool value = decltype(test<F>(0))::value;
	};
} // namespace detail
} // namespace lyra

#endif

#include <memory>
#include <string>
#include <type_traits>

namespace lyra
{

/* tag::reference[]

[#lyra_parser_customization]
= `lyra::parser_customization`

Customization interface for parsing of options.

[source]
----
virtual std::string token_delimiters() const = 0;
----

Specifies the characters to use for splitting a cli argument into the option
and its value (if any).

[source]
----
virtual std::string option_prefix() const = 0;
----

Specifies the characters to use as possible prefix, either single or double,
for all options.

end::reference[] */
struct parser_customization
{
	virtual std::string token_delimiters() const = 0;
	virtual std::string option_prefix() const = 0;
};

/* tag::reference[]

[#lyra_default_parser_customization]
= `lyra::default_parser_customization`

Is-a `lyra::parser_customization` that defines token delimiters as space (" ")
or equal ("="). And specifies the option prefix character as dash ("-")
resulting in long options with `--` and short options with `-`.

This customization is used as the default if none is given.

end::reference[] */
struct default_parser_customization : parser_customization
{
	std::string token_delimiters() const override { return " ="; }
	std::string option_prefix() const override { return "-"; }
};

namespace detail
{
	class parse_state
	{
		public:
		parse_state(
			parser_result_type type, token_iterator const& remainingTokens)
			: m_type(type)
			, m_remainingTokens(remainingTokens)
		{
		}

		auto type() const -> parser_result_type { return m_type; }
		auto remainingTokens() const -> token_iterator
		{
			return m_remainingTokens;
		}

		private:
		parser_result_type m_type;
		token_iterator m_remainingTokens;
	};

	struct parser_cardinality
	{
		size_t minimum = 0;
		size_t maximum = 0;

		parser_cardinality() = default;

		parser_cardinality(size_t a, size_t b)
			: minimum(a)
			, maximum(b)
		{
		}

		bool is_optional() const { return (minimum == 0); }

		bool is_unbounded() const { return (maximum == 0); }

		bool is_bounded() const { return !is_unbounded(); }

		bool is_required() const { return (minimum > 0); }
	};
} // namespace detail

/* tag::reference[]

[#lyra_parser_result]
= `lyra::parser_result`

The result of parsing arguments.

end::reference[] */
class parse_result : public detail::basic_result<detail::parse_state>
{
	public:
	using base = detail::basic_result<detail::parse_state>;
	using base::basic_result;
	using base::logicError;
	using base::ok;
	using base::runtimeError;

	parse_result(const base& other)
		: base(other)
	{
	}
};

/* tag::reference[]

[#lyra_parser_base]
= `lyra::parser_base`

Base for all argument parser types.

end::reference[] */
class parser_base
{
	public:
	struct help_text_item
	{
		std::string option;
		std::string description;
	};

	using help_text = std::vector<help_text_item>;

	virtual ~parser_base() = default;

	virtual auto validate() const -> result { return result::ok(); }

	virtual parse_result parse(
		std::string const& exe_name, detail::token_iterator const& tokens,
		parser_customization const& customize) const = 0;

	virtual detail::parser_cardinality cardinality() const { return { 0, 1 }; }

	auto is_optional() const -> bool { return cardinality().is_optional(); }

	virtual std::string get_usage_text() const { return ""; }

	virtual help_text get_help_text() const { return {}; }

	virtual std::string get_description_text() const { return ""; }

	virtual std::unique_ptr<parser_base> clone() const { return nullptr; }
};

/* tag::reference[]

[#lyra_composable_parser]
= `lyra::composable_parser`

A parser that can be composed with other parsers using `operator|`.

end::reference[] */
template <typename DerivedT>
class composable_parser : public parser_base
{
};

/* tag::reference[]

[#lyra_bound_parser]
= `lyra::bound_parser`

Parser that binds a variable reference or callback to the value of an argument.

end::reference[] */
template <typename Derived>
class bound_parser : public composable_parser<Derived>
{
	protected:
	std::shared_ptr<detail::BoundRef> m_ref;
	std::string m_hint;
	std::string m_description;
	detail::parser_cardinality m_cardinality;
	std::shared_ptr<detail::choices_base> value_choices;

	explicit bound_parser(std::shared_ptr<detail::BoundRef> const& ref)
		: m_ref(ref)
	{
		if (m_ref->isContainer())
			m_cardinality = { 0, 0 };
		else
			m_cardinality = { 0, 1 };
	}

	public:
	template <typename Reference>
	bound_parser(Reference& ref, std::string const& hint);

	template <typename Lambda>
	bound_parser(Lambda const& ref, std::string const& hint);

	Derived& help(const std::string& text);
	Derived& operator()(std::string const& description);
	Derived& optional();
	Derived& required(size_t n = 1);
	Derived& cardinality(size_t n);
	Derived& cardinality(size_t n, size_t m);
	detail::parser_cardinality cardinality() const override
	{
		return m_cardinality;
	}
	std::string hint() const { return m_hint; }

	template <
		typename T,
		typename... Rest,
		typename std::enable_if<
			!detail::is_invocable<T>::value,
			int>::type = 0>
	Derived& choices(T val0, Rest... rest);
	template <
		typename Lambda,
		typename std::enable_if<
			detail::is_invocable<Lambda>::value,
			int>::type = 1>
	Derived& choices(Lambda const& check_choice);
};

/* tag::reference[]

[#lyra_bound_parser_ctor]
== Construction

end::reference[] */

/* tag::reference[]
[source]
----
template <typename Derived>
template <typename Reference>
bound_parser<Derived>::bound_parser(Reference& ref, std::string const& hint);

template <typename Derived>
template <typename Lambda>
bound_parser<Derived>::bound_parser(Lambda const& ref, std::string const& hint);
----

Constructs a value option with a target typed variable or callback. These are
options that take a value as in `--opt=value`. In the first form the given
`ref` receives the value of the option after parsing. The second form the
callback is called during the parse with the given value. Both take a
`hint` that is used in the help text. When the option can be specified
multiple times the callback will be called consecutively for each option value
given. And if a container is given as a reference on the first form it will
contain all the specified values.

end::reference[] */
template <typename Derived>
template <typename Reference>
bound_parser<Derived>::bound_parser(Reference& ref, std::string const& hint)
	: bound_parser(std::make_shared<detail::BoundValueRef<Reference>>(ref))
{
	m_hint = hint;
}

template <typename Derived>
template <typename Lambda>
bound_parser<Derived>::bound_parser(Lambda const& ref, std::string const& hint)
	: bound_parser(std::make_shared<detail::BoundLambda<Lambda>>(ref))
{
	m_hint = hint;
}

/* tag::reference[]

[#lyra_bound_parser_specification]
== Specification

end::reference[] */

/* tag::reference[]

[#lyra_bound_parser_help]
=== `lyra::bound_parser::help`, `lyra::bound_parser::operator(help)`

[source]
----
template <typename Derived>
Derived& bound_parser<Derived>::help(std::string const& text);
template <typename Derived>
Derived& bound_parser<Derived>::operator()(std::string const& help);
----

Defines the help description of an argument.

end::reference[] */
template <typename Derived>
Derived& bound_parser<Derived>::help(const std::string& text)
{
	m_description = text;
	return static_cast<Derived&>(*this);
}
template <typename Derived>
Derived& bound_parser<Derived>::operator()(std::string const& help_text)
{
	return this->help(help_text);
}

/* tag::reference[]

[#lyra_bound_parser_optional]
=== `lyra::bound_parser::optional`

[source]
----
template <typename Derived>
Derived& bound_parser<Derived>::optional();
----

Indicates that the argument is optional. This is equivalent to specifying
`cardinality(0, 1)`.

end::reference[] */
template <typename Derived>
Derived& bound_parser<Derived>::optional()
{
	return this->cardinality(0, 1);
}

/* tag::reference[]

[#lyra_bound_parser_required]
=== `lyra::bound_parser::required(n)`

[source]
----
template <typename Derived>
Derived& bound_parser<Derived>::required(size_t n);
----

Specifies that the argument needs to given the number of `n` times
(defaults to *1*).

end::reference[] */
template <typename Derived>
Derived& bound_parser<Derived>::required(size_t n)
{
	if (m_ref->isContainer())
		return this->cardinality(1, 0);
	else
		return this->cardinality(n);
}

/* tag::reference[]

[#lyra_bound_parser_cardinality]
=== `lyra::bound_parser::cardinality(n, m)`

[source]
----
template <typename Derived>
Derived& bound_parser<Derived>::cardinality(size_t n);

template <typename Derived>
Derived& bound_parser<Derived>::cardinality(size_t n, size_t m);
----

Specifies the number of times the argument can and needs to appear in the list
of arguments. In the first form the argument can appear exactly `n` times. In
the second form it specifies that the argument can appear from `n` to `m` times
inclusive.

end::reference[] */
template <typename Derived>
Derived& bound_parser<Derived>::cardinality(size_t n)
{
	m_cardinality = { n, n };
	return static_cast<Derived&>(*this);
}

template <typename Derived>
Derived& bound_parser<Derived>::cardinality(size_t n, size_t m)
{
	m_cardinality = { n, m };
	return static_cast<Derived&>(*this);
}

/* tag::reference[]

[#lyra_bound_parser_choices]
=== `lyra::bound_parser::choices`

[source]
----
template <typename Derived>
template <typename T, typename... Rest>
lyra::opt& lyra::bound_parser<Derived>::choices(T val0, Rest... rest)

template <typename Derived>
template <typename Lambda>
lyra::opt& lyra::bound_parser<Derived>::choices(Lambda const &check_choice)
----

Limit the allowed values of an argument. In the first form the value is
limited to the ones listed in the call (two or more values). In the second
form the `check_choice` function is called with the parsed value and returns
`true` if it's an allowed value.

end::reference[] */
template <typename Derived>
template <
	typename T,
	typename... Rest,
	typename std::enable_if<
		!detail::is_invocable<T>::value,
		int>::type>
Derived& bound_parser<Derived>::choices(T val0, Rest... rest)
{
	value_choices
		= std::make_shared<detail::choices_set<T>>(val0, rest...);
	return static_cast<Derived&>(*this);
}

template <typename Derived>
template <
	typename Lambda,
	typename std::enable_if<
		detail::is_invocable<Lambda>::value,
		int>::type>
Derived& bound_parser<Derived>::choices(Lambda const& check_choice)
{
	value_choices
		= std::make_shared<detail::choices_check<Lambda>>(check_choice);
	return static_cast<Derived&>(*this);
}

} // namespace lyra

#endif

namespace lyra
{
/* tag::reference[]

[#lyra_arg]
= `lyra::arg`

A parser for regular arguments, i.e. not `--` or `-` prefixed. This is simply
a way to get values of arguments directly specified in the cli.

Is-a <<lyra_bound_parser>>.

*/ // end::reference[]
class arg : public bound_parser<arg>
{
	public:
	using bound_parser::bound_parser;

	virtual std::string get_usage_text() const override
	{
		std::ostringstream oss;
		if (!m_hint.empty())
		{
			auto c = cardinality();
			if (c.is_required())
			{
				for (size_t i = 0; i < c.minimum; ++i)
					oss << (i > 0 ? " " : "") << "<" << m_hint << ">";
				if (c.is_unbounded())
					oss << (c.is_required() ? " " : "") << "[<" << m_hint << ">" << "...]";
			}
			else if (c.is_unbounded())
			{
				oss << "[<" << m_hint << ">" << "...]";
			}
		}
		return oss.str();
	}

	virtual help_text get_help_text() const override
	{
		return { { get_usage_text(), m_description } };
	}

	using parser_base::parse;

	auto parse(
		std::string const&, detail::token_iterator const& tokens,
		parser_customization const&) const -> parse_result override
	{
		auto validationResult = validate();
		if (!validationResult) return parse_result(validationResult);

		auto const& token = tokens.argument();

		auto valueRef = static_cast<detail::BoundValueRefBase*>(m_ref.get());

		if (value_choices)
		{
			auto choice_result = value_choices->contains_value(token.name);
			if (!choice_result) return parse_result(choice_result);
		}

		auto result = valueRef->setValue(token.name);
		if (!result)
			return parse_result(result);
		else
		{
			auto remainingTokens = tokens;
			remainingTokens.pop(token);
			return parse_result::ok(detail::parse_state(
				parser_result_type::matched, remainingTokens));
		}
	}

	virtual std::unique_ptr<parser_base> clone() const override
	{
		return std::unique_ptr<parser_base>(new arg(*this));
	}
};
} // namespace lyra

#endif

#ifndef LYRA_CLI_PARSER_HPP
#define LYRA_CLI_PARSER_HPP


#ifndef LYRA_EXE_NAME_HPP
#define LYRA_EXE_NAME_HPP


namespace lyra
{
/* tag::reference[]

[#lyra_exe_name]
= `lyra::exe_name`

Specifies the name of the executable.

Is-a <<lyra_composable_parser>>.

end::reference[] */
class exe_name : public composable_parser<exe_name>
{
	public:
	exe_name()
		: m_name(std::make_shared<std::string>("<executable>"))
	{
	}

	explicit exe_name(std::string& ref);

	template <typename LambdaT>
	explicit exe_name(LambdaT const& lambda);

	std::string name() const;
	parser_result set(std::string const& newName);

	virtual parse_result parse(
		std::string const&, detail::token_iterator const& tokens,
		parser_customization const&) const override
	{
		return parse_result::ok(
			detail::parse_state(parser_result_type::no_match, tokens));
	}

	virtual std::unique_ptr<parser_base> clone() const override
	{
		return std::unique_ptr<parser_base>(new exe_name(*this));
	}

	private:
	std::shared_ptr<std::string> m_name;
	std::shared_ptr<detail::BoundValueRefBase> m_ref;
};

/* tag::reference[]

[#lyra_exe_name_ctor]
== Construction

end::reference[] */

/* tag::reference[]
[source]
----
exe_name::exe_name(std::string& ref)
----

Constructs with a target string to receive the name of the executable. When
the `cli_parser` is run the target string will contain the exec name.

end::reference[] */
inline exe_name::exe_name(std::string& ref)
	: exe_name()
{
	m_ref = std::make_shared<detail::BoundValueRef<std::string>>(ref);
}

/* tag::reference[]
[source]
----
template <typename LambdaT>
exe_name::exe_name(LambdaT const& lambda)
----

Construct with a callback that is called with the value of the executable name
when the `cli_parser` runs.

end::reference[] */
template <typename LambdaT>
exe_name::exe_name(LambdaT const& lambda)
	: exe_name()
{
	m_ref = std::make_shared<detail::BoundLambda<LambdaT>>(lambda);
}

/* tag::reference[]

[#lyra_exe_name_accessors]
== Accessors

end::reference[] */

/* tag::reference[]

[#lyra_exe_name_name]
=== `lyra::exe_name::name`

[source]
----
std::string exe_name::name() const
----

Returns the executable name when available. Otherwise it returns a default
value.

end::reference[] */
inline std::string exe_name::name() const { return *m_name; }

/* tag::reference[]

[#lyra_exe_name_set]
=== `lyra::exe_name::set`

[source]
----
parser_result exe_name::set(std::string const& newName)
----

Sets the executable name with the `newName` value. The new value is reflected
in the bound string reference or callback.

end::reference[] */
inline parser_result exe_name::set(std::string const& newName)
{
	auto lastSlash = newName.find_last_of("\\/");
	auto filename = (lastSlash == std::string::npos)
		? newName
		: newName.substr(lastSlash + 1);

	*m_name = filename;
	if (m_ref)
		return m_ref->setValue(filename);
	else
		return parser_result::ok(parser_result_type::matched);
}

} // namespace lyra

#endif

namespace lyra
{
/* tag::reference[]

[#lyra_cli_parser]
= `lyra::cli_parser`

A Combined parser made up of any two or more other parsers. Creating and using
one of these as a basis one can incrementally compose other parsers into this
one. For example:

[source]
----
auto cli = lyra::cli_parser();
std::string what;
float when = 0;
std::string where;
cli |= lyra::opt(what, "what")["--make-it-so"]("Make it so.").required();
cli |= lyra::opt(when. "when")["--time"]("When to do <what>.").optional();
cli.add_argument(lyra::opt(where, "where").name("--where")
	.help("There you are.").optional());
----

*/ // end::reference[]
class cli_parser : parser_base
{
	public:
	cli_parser() = default;

	cli_parser(const cli_parser& other);

	cli_parser& add_argument(exe_name const& exe_name);
	cli_parser& operator|=(exe_name const& exe_name);

	cli_parser& add_argument(parser_base const& p);
	cli_parser& operator|=(parser_base const& p);

	cli_parser& add_argument(cli_parser const& other);
	cli_parser& operator|=(cli_parser const& other);

	template <typename T>
	cli_parser operator|(T const& other) const
	{
		return cli_parser(*this) |= other;
	}

	friend auto operator<<(std::ostream& os, cli_parser const& parser)
		-> std::ostream&
	{
		parser.writeToStream(os);
		return os;
	}

	parse_result parse(
		args const& args,
		parser_customization const& customize
		= default_parser_customization()) const;


	virtual help_text get_help_text() const override
	{
		help_text text;
		for (auto const& p : m_parsers)
		{
			auto child_help = p->get_help_text();
			text.insert(text.end(), child_help.begin(), child_help.end());
		}
		return text;
	}

	auto validate() const -> result override
	{
		for (auto const& p : m_parsers)
		{
			auto result = p->validate();
			if (!result) return result;
		}
		return result::ok();
	}

	parse_result parse(
		std::string const& exe_name, detail::token_iterator const& tokens,
		parser_customization const& customize) const override
	{
		struct ParserInfo
		{
			parser_base const* parser = nullptr;
			size_t count = 0;
		};
		std::vector<ParserInfo> parseInfos(m_parsers.size());
		{
			size_t i = 0;
			for (auto const& p : m_parsers) parseInfos[i++].parser = p.get();
		}

		m_exeName.set(exe_name);

		auto result = parse_result::ok(
			detail::parse_state(parser_result_type::no_match, tokens));
		while (result.value().remainingTokens())
		{
			bool tokenParsed = false;

			for (auto& parseInfo : parseInfos)
			{
				auto parser_cardinality = parseInfo.parser->cardinality();
				if (parser_cardinality.is_unbounded()
					|| parseInfo.count < parser_cardinality.maximum)
				{
					result = parseInfo.parser->parse(
						exe_name, result.value().remainingTokens(), customize);
					if (!result) return result;
					if (result.value().type() != parser_result_type::no_match)
					{
						tokenParsed = true;
						++parseInfo.count;
						break;
					}
				}
			}

			if (result.value().type() == parser_result_type::short_circuit_all)
				return result;
			if (!tokenParsed)
				return parse_result::runtimeError(
					result.value(),
					"Unrecognized token: "
						+ result.value().remainingTokens().argument().name);
		}
		for (auto& parseInfo : parseInfos)
		{
			auto parser_cardinality = parseInfo.parser->cardinality();
			if ((parser_cardinality.is_bounded()
				 && (parseInfo.count < parser_cardinality.minimum
					 || parser_cardinality.maximum < parseInfo.count))
				|| (parser_cardinality.is_required()
					&& (parseInfo.count < parser_cardinality.minimum)))
			{
				return parse_result::runtimeError(
					result.value(),
					"Expected: " + parseInfo.parser->get_usage_text());
			}
		}
		return result;
	}

	virtual std::unique_ptr<parser_base> clone() const override
	{
		return std::unique_ptr<parser_base>(new cli_parser(*this));
	}

	private:
	mutable exe_name m_exeName;
	std::vector<std::unique_ptr<parser_base>> m_parsers;

	void writeToStream(std::ostream& os) const
	{
		if (!m_exeName.name().empty())
		{
			os << "Usage:\n"
			   << "  " << m_exeName.name();
			for (auto const& p : m_parsers)
			{
				std::string usage_test = p->get_usage_text();
				if (usage_test.size() > 0)
				{
					os << " ";
					if (p->is_optional()) os << "[";
					os << usage_test;
					if (p->is_optional()) os << "]";
				}
			}
			os << "\n\n";
		}

		for (auto const& p : m_parsers)
		{
			auto child_description = p->get_description_text();
			if (!child_description.empty()) os << child_description << "\n\n";
		}

		os << "Options, arguments:";
		for (auto const& cols : get_help_text())
		{
			os << "\n  " << cols.option << "\n\n  " << cols.description << "\n";
		}
	}
};

/* tag::reference[]

[#lyra_cli_parser_ctor]
== Construction

end::reference[] */

/* tag::reference[]

[#lyra_cli_parser_ctor_default]
=== Default

[source]
----
cli_parser() = default;
----

Default constructing a `cli_parser` is the starting point to adding arguments
and options for parsing a command line.

end::reference[] */

/* tag::reference[]

[#lyra_cli_parser_ctor_copy]
=== Copy

[source]
----
cli_parser::cli_parser(const cli_parser& other);
----

end::reference[] */
inline cli_parser::cli_parser(const cli_parser& other)
	: m_exeName(other.m_exeName)
{
	for (auto& other_parser : other.m_parsers)
	{
		m_parsers.push_back(other_parser->clone());
	}
}

/* tag::reference[]

[#lyra_cli_parser_specification]
== Specification

end::reference[] */


/* tag::reference[]
[#lyra_cli_parser_add_argument]
=== `lyra::cli_parser::add_argument`

[source]
----
cli_parser& cli_parser::add_argument(exe_name const& exe_name);
cli_parser& cli_parser::operator|=(exe_name const& exe_name);
cli_parser& cli_parser::add_argument(parser_base const& p);
cli_parser& cli_parser::operator|=(parser_base const& p);
cli_parser& cli_parser::add_argument(cli_parser const& other);
cli_parser& cli_parser::operator|=(cli_parser const& other);
----

Adds the given argument parser to the considered arguments for this
`cli_parser`. Depending on the parser given it will be: recorded as the exe
name (for `exe_name` parser), directly added as an argument (for
`parser_base`), or add the parsers from another `cli_parser` to this one.

end::reference[] */
inline cli_parser& cli_parser::add_argument(exe_name const& exe_name)
{
	m_exeName = exe_name;
	return *this;
}
inline cli_parser& cli_parser::operator|=(exe_name const& exe_name)
{
	return this->add_argument(exe_name);
}
inline cli_parser& cli_parser::add_argument(parser_base const& p)
{
	m_parsers.push_back(p.clone());
	return *this;
}
inline cli_parser& cli_parser::operator|=(parser_base const& p)
{
	return this->add_argument(p);
}
inline cli_parser& cli_parser::add_argument(cli_parser const& other)
{
	for (auto& p : other.m_parsers)
	{
		m_parsers.push_back(p->clone());
	}
	return *this;
}
inline cli_parser& cli_parser::operator|=(cli_parser const& other)
{
	return this->add_argument(other);
}

template <typename DerivedT, typename T>
cli_parser operator|(composable_parser<DerivedT> const& thing, T const& other)
{
	return cli_parser() | static_cast<DerivedT const&>(thing) | other;
}

/* tag::reference[]
[#lyra_cli_parser_parse]
=== `lyra::cli_parser::parse`

[source]
----
parse_result cli_parser::parse(
	args const& args, parser_customization const& customize) const;
----

Parses given arguments `args` and optional parser customization `customize`.
The result indicates success or failure, and if failure what kind of failure
it was. The state of variables bound to options is unspecified and any bound
callbacks may have been called.

end::reference[] */
inline parse_result
cli_parser::parse(args const& args, parser_customization const& customize) const
{
	return parse(
		args.exe_name(),
		detail::token_iterator(
			args, customize.token_delimiters(), customize.option_prefix()),
		customize);
}

} // namespace lyra

#endif

#ifndef LYRA_HELP_HPP
#define LYRA_HELP_HPP


#ifndef LYRA_OPT_HPP
#define LYRA_OPT_HPP

#include <memory>

namespace lyra
{
/* tag::reference[]

[#lyra_opt]
= `lyra::opt`

A parser for one option with multiple possible names. The option value(s) are
communicated through a reference to a variable, a container, or a callback.

Is-a <<lyra_bound_parser>>.

end::reference[] */
class opt : public bound_parser<opt>
{
	protected:
	std::vector<std::string> opt_names;

	public:

	explicit opt(bool& ref);

	template <typename LambdaT>
	explicit opt(LambdaT const& ref);


	template <typename T>
	opt(T& ref, std::string const& hint);

	template <typename LambdaT>
	opt(LambdaT const& ref, std::string const& hint);


	opt& name(const std::string& opt_name);
	opt& operator[](std::string const& opt_name);


	virtual std::string get_usage_text() const override
	{
		std::string result;
		for (std::size_t o = 0; o < opt_names.size(); ++o)
		{
			if (o > 0) result += "|";
			result += opt_names[o];
		}
		return result;
	}

	virtual help_text get_help_text() const override
	{
		std::ostringstream oss;
		bool first = true;
		for (auto const& opt : opt_names)
		{
			if (first)
				first = false;
			else
				oss << ", ";
			oss << opt;
		}
		if (!m_hint.empty()) oss << " <" << m_hint << ">";
		return { { oss.str(), m_description } };
	}

	bool isMatch(
		std::string const& optToken,
		parser_customization const& customize) const
	{
		auto normalisedToken = normaliseOpt(optToken, customize);
		for (auto const& name : opt_names)
		{
			if (normaliseOpt(name, customize) == normalisedToken) return true;
		}
		return false;
	}

	std::string normaliseOpt(
		std::string const& optName, parser_customization const& customize) const
	{
		auto is_prefix_char_0
			= customize.option_prefix().find(optName[0]) != std::string::npos;
		auto is_prefix_char_1
			= customize.option_prefix().find(optName[1]) != std::string::npos;
		if (is_prefix_char_0)
		{
			if (is_prefix_char_1)
				return "--" + optName.substr(2);
			else
				return "-" + optName.substr(1);
		}
		else
			return optName;
	}

	using parser_base::parse;

	parse_result parse(
		std::string const&, detail::token_iterator const& tokens,
		parser_customization const& customize) const override
	{
		auto validationResult = validate();
		if (!validationResult) return parse_result(validationResult);

		auto remainingTokens = tokens;
		if (remainingTokens && remainingTokens.has_option_prefix())
		{
			auto const& token = remainingTokens.option();
			if (isMatch(token.name, customize))
			{
				if (m_ref->isFlag())
				{
					remainingTokens.pop(token);
					auto flagRef
						= static_cast<detail::BoundFlagRefBase*>(m_ref.get());
					auto result = flagRef->setFlag(true);
					if (!result) return parse_result(result);
					if (result.value() == parser_result_type::short_circuit_all)
						return parse_result::ok(detail::parse_state(
							result.value(), remainingTokens));
				}
				else
				{
					auto const& argToken = remainingTokens.value();
					if (argToken.type == detail::token_type::unknown)
						return parse_result::runtimeError(
							{ parser_result_type::no_match, remainingTokens },
							"Expected argument following " + token.name);
					remainingTokens.pop(token, argToken);
					auto valueRef
						= static_cast<detail::BoundValueRefBase*>(m_ref.get());
					if (value_choices)
					{
						auto choice_result
							= value_choices->contains_value(argToken.name);
						if (!choice_result) return parse_result(choice_result);
					}
					auto result = valueRef->setValue(argToken.name);
					if (!result) return parse_result(result);
					if (result.value() == parser_result_type::short_circuit_all)
						return parse_result::ok(detail::parse_state(
							result.value(), remainingTokens));
				}
				return parse_result::ok(detail::parse_state(
					parser_result_type::matched, remainingTokens));
			}
		}
		return parse_result::ok(
			detail::parse_state(parser_result_type::no_match, remainingTokens));
	}

	result validate() const override
	{
		if (opt_names.empty())
			return result::logicError("No options supplied to opt");
		for (auto const& name : opt_names)
		{
			if (name.empty())
				return result::logicError("Option name cannot be empty");
			if (name[0] != '-')
				return result::logicError("Option name must begin with '-'");
		}
		return bound_parser::validate();
	}

	std::unique_ptr<parser_base> clone() const override
	{
		return std::unique_ptr<parser_base>(new opt(*this));
	}
};

/* tag::reference[]

[#lyra_opt_ctor]
== Construction

end::reference[] */

/* tag::reference[]

[#lyra_opt_ctor_flags]
=== Flags

[source]
----
lyra::opt::opt(bool& ref);

template <typename LambdaT>
lyra::opt::opt(LambdaT const& ref);

template <typename LambdaT>
lyra::opt::opt(LambdaT const& ref, std::string const& hint)
----

Constructs a flag option with a target `bool` to indicate if the flag is
present. The first form takes a reference to a variable to receive the
`bool`. The second takes a callback that is called with `true` when the
option is present.

end::reference[] */
inline opt::opt(bool& ref)
	: bound_parser(std::make_shared<detail::BoundFlagRef>(ref))
{
}
template <typename LambdaT>
opt::opt(LambdaT const& ref)
	: bound_parser(std::make_shared<detail::BoundFlagLambda<LambdaT>>(ref))
{
}

/* tag::reference[]

[#lyra_opt_ctor_values]
=== Values

[source]
----
template <typename T>
lyra::opt::opt(T& ref, std::string const& hint);

template <typename LambdaT>
lyra::opt::opt(LambdaT const& ref, std::string const& hint)
----

Constructs a value option with a target `ref`. The first form takes a reference
to a variable to receive the value. The second takes a callback that is called
with the value when the option is present.

end::reference[] */
template <typename T>
opt::opt(T& ref, std::string const& hint)
	: bound_parser(ref, hint)
{
}
template <typename LambdaT>
opt::opt(LambdaT const& ref, std::string const& hint)
	: bound_parser(ref, hint)
{
}

/* tag::reference[]

[#lyra_opt_specification]
== Specification

end::reference[] */

/* tag::reference[]

[#lyra_opt_name]
=== `lyra::opt::name`

[source]
----
lyra::opt& lyra::opt::name(const std::string &opt_name)
lyra::opt& lyra::opt::operator[](const std::string &optName)
----

Add a spelling for the option of the form `--<name>` or `-n`.
One can add multiple short spellings at once with `-abc`.

end::reference[] */
inline opt& opt::name(const std::string& opt_name)
{
	if (opt_name.size() > 2 && opt_name[0] != opt_name[1])
		for (auto o : opt_name.substr(1))
			opt_names.push_back(std::string(1, opt_name[0]) + o);
	else
		opt_names.push_back(opt_name);
	return *this;
}
inline opt& opt::operator[](const std::string& opt_name)
{
	return this->name(opt_name);
}

} // namespace lyra

#endif

namespace lyra
{
/* tag::reference[]

[#lyra_help]
= `lyra::help`

Utility function that defines a default `--help` option. You can specify a
`bool` flag to indicate if the help option was specified and that you could
display a help message.

The option accepts `-?`, `-h`, and `--help` as allowed option names.

*/ // end::reference[]
class help : public opt
{
	public:
	help(bool& showHelpFlag)
		: opt([&](bool flag) {
			showHelpFlag = flag;
			return parser_result::ok(parser_result_type::short_circuit_all);
		})
	{
		static_cast<opt&> (*this)(
			"Display usage information.")["-?"]["-h"]["--help"]
			.optional();
	}

	help & description(const std::string &text);

	virtual std::string get_description_text() const override
	{
		return description_text;
	}

	virtual std::unique_ptr<parser_base> clone() const override
	{
		return std::unique_ptr<parser_base>(new help(*this));
	}

	private:
	std::string description_text;
};

/* tag::reference[]
[source]
----
help & help::description(const std::string &text)
----

Sets the given `text` as the general description to show with the help and
usage output for CLI parser. This text is displayed between the "Usage"
and "Options, arguments" sections.

end::reference[] */
inline help & help::description(const std::string &text)
{
	description_text = text;
	return *this;
}
} // namespace lyra


#endif

#ifndef LYRA_VERSION_HPP
#define LYRA_VERSION_HPP

#define LYRA_VERSION_MAJOR 1
#define LYRA_VERSION_MINOR 4
#define LYRA_VERSION_PATCH 0

#define LYRA_VERSION \
	(((LYRA_VERSION_MAJOR)*10000000) + ((LYRA_VERSION_MINOR)*100000) \
	 + (LYRA_VERSION_PATCH))

#endif // LYRA_VERSION_HPP

#endif // LYRA_HPP_INCLUDED
