#ifndef __INTEGER_HPP__
#define __INTEGER_HPP__

#include <type_traits>
#include <stdexcept>
#include <limits>
#include <cctype>
#include <vector>
#include <string>
#include <cstdint>

class Integer {
private:
	bool _negative;
	std::vector<uint32_t> _data;

private:
	static const uint64_t _base { std::numeric_limits<uint32_t>::max() };

	static int _compare(const std::vector<uint32_t> &a, const std::vector<uint32_t> &b) {
		if (a.size() != b.size())
			return a.size() < b.size()? -1: 1;

		for (int i = 0, n = a.size(); i < n; ++i) {
			if (a[i] != b[i])
				return a[i] < b[i]? -1: 1;
		}

		return 0;
	}

public:
	Integer(void): _negative(false) { }
	virtual ~Integer(void) { }

	template <typename T, typename=typename std::enable_if<std::is_arithmetic<T>::value>::type>
	Integer(const T &i): _negative(false) {
		int64_t v = i;
		if (v < 0LL)
			_negative = true, v = -v;

		_data.emplace_back(v % _base);
		v /= _base;

		if (v)
			_data.emplace_back(v);
	}

	Integer(const std::string &s): _negative(false) {
		if (!s.empty()) {
			auto it = s.begin(), end = s.end();

			if (*it == '-')
				_negative = true, ++it;
			else if (*it == '+')
				++it;

			for ( ; it != end; ++it) {
				if (!isdigit(*it))
					throw std::runtime_error("Integer cannot be initialized from a non-number string: " + s);

				uint64_t val = *it - '0';
				for (auto &d : _data) {
					val += 10ULL * d;
					d = val % _base;
					val /= _base;
				}
				if (val)
					_data.emplace_back(val);
			}
		}
	}

	friend bool operator ==(const Integer &lhs, const Integer &rhs) {
		return lhs._negative == rhs._negative && _compare(lhs._data, rhs._data) == 0;
	}

	friend bool operator !=(const Integer &lhs, const Integer &rhs) {
		return !(lhs == rhs);
	}

	friend bool operator <(const Integer &lhs, const Integer &rhs) {
		if (lhs._negative && !rhs._negative)
			return true;
		if (lhs._negative)
			return _compare(lhs._data, rhs._data) > 0;
		return _compare(lhs._data, rhs._data) < 0;
	}

	friend bool operator >(const Integer &lhs, const Integer &rhs) {
		return rhs < lhs;
	}

	friend bool operator <=(const Integer &lhs, const Integer &rhs) {
		return lhs == rhs || lhs < rhs;
	}

	friend bool operator >=(const Integer &lhs, const Integer &rhs) {
		return lhs == rhs || lhs > rhs;
	}
};

#endif
