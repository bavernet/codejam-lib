#ifndef __INTEGER_HPP__
#define __INTEGER_HPP__

#include <type_traits>
#include <stdexcept>
#include <limits>
#include <cctype>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>

class Integer {
private:
	bool _negative;
	std::vector<uint32_t> _data;

private:
	static const uint64_t _base { std::numeric_limits<uint32_t>::max() + 1ULL };

	static int _compare(const std::vector<uint32_t> &a, const std::vector<uint32_t> &b) {
		if (a.size() != b.size())
			return a.size() < b.size()? -1: 1;

		for (int i = 0, n = a.size(); i < n; ++i) {
			if (a[i] != b[i])
				return a[i] < b[i]? -1: 1;
		}

		return 0;
	}

	static std::vector<uint32_t> _add(const std::vector<uint32_t> &a, const std::vector<uint32_t> &b) {
		if (a.size() < b.size())
			return _add(b, a);

		int max_size = a.size(), min_size = b.size();
		std::vector<uint32_t> ans;
		uint64_t val = 0;
		for (int i = 0; i < min_size; ++i) {
			val += 0ULL + a[i] + b[i];
			ans.emplace_back(val % _base);
			val /= _base;
		}
		for (int i = min_size; i < max_size; ++i) {
			val += a[i];
			ans.emplace_back(val % _base);
			val /= _base;
		}
		if (val)
			ans.emplace_back(val);
		return ans;
	}

	static std::vector<uint32_t> _sub(const std::vector<uint32_t> &a, const std::vector<uint32_t> &b) {
		int max_size = a.size(), min_size = b.size();
		std::vector<uint32_t> ans;
		uint32_t borrow = 0;
		for (int i = 0; i < min_size; ++i) {
			if (a[i] < b[i] || (a[i] == b[i] && borrow)) {
				ans.emplace_back(_base - b[i] - borrow + a[i]);
				borrow = 1;
			} else {
				ans.emplace_back(a[i] - b[i] - borrow);
				borrow = 0;
			}
		}
		for (int i = min_size; i < max_size; ++i) {
			if (!a[i] && borrow) {
				ans.emplace_back(_base - borrow);
				borrow = 1;
			} else {
				ans.emplace_back(a[i] - borrow);
				borrow = 0;
			}
		}
		while (ans.size() > 1 && !ans.back())
			ans.pop_back();
		return ans;
	}

	static std::vector<uint32_t> _mul_one(const std::vector<uint32_t> &a, uint64_t b) {
		std::vector<uint32_t> ans;
		uint64_t val = 0;
		for (int i = 0, n = a.size(); i < n; ++i) {
			val += a[i] * b;
			ans.emplace_back(val % _base);
			val /= _base;
		}
		if (val)
			ans.emplace_back(val);
		return ans;
	}

	static std::vector<uint32_t> _mul(const std::vector<uint32_t> &a, const std::vector<uint32_t> &b) {
		/*
		ab * cd;
		(a*10^n + b) + (c*10^n + d)
		= ac*10^2n + (bc + ad)*10^n + bd;
		= ac*10^2n + bd + ((a + b)(c + d) - ac - bd)*10^n;
		*/

		int max_size = a.size(), min_size = b.size();
		if (max_size < min_size)
			return _mul(b, a);
		if (min_size == 0)
			return std::vector<uint32_t>();
		if (min_size == 1)
			return _mul_one(a, b.front());

		int max_half = max_size / 2, min_half = std::min(min_size, max_half);
		std::vector<uint32_t> a0(a.begin(), a.begin() + max_half);
		std::vector<uint32_t> a1(a.begin() + max_half, a.end());
		std::vector<uint32_t> b0(b.begin(), b.begin() + min_half);
		std::vector<uint32_t> b1(b.begin() + min_half, b.end());

		std::vector<uint32_t> c2 = _mul(a1, b1);
		std::vector<uint32_t> c0 = _mul(a0, b0);

		std::vector<uint32_t> t0 = _add(a0, a1);
		std::vector<uint32_t> t1 = _add(b0, b1);
		std::vector<uint32_t> c1 = _sub(_mul(t0, t1), _add(c0, c2));

		c2.insert(c2.begin(), max_half + max_half, 0U);
		c1.insert(c1.begin(), max_half, 0U);
		return _add(c0, _add(c1, c2));
	}

public:
	Integer(void): _negative(false), _data(1, 0) { }
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

	Integer(const std::string &s, uint32_t base=10U): _negative(false) {
		if (base > 36U)
			throw std::runtime_error("Integer does not support conversions beyond base 36: current base=" + base);

		if (!s.empty()) {
			auto it = s.begin(), end = s.end();

			if (*it == '-')
				_negative = true, ++it;
			else if (*it == '+')
				++it;

			for ( ; it != end; ++it) {
				char c = isalpha(*it)? toupper(*it): *it;
				uint64_t val = c;
				if (isdigit(c) && val - '0' < base)
					val = val - '0';
				else if (isalpha(c) && base > 10 && val - 'A' < base - 10)
					val = val - 'A' + 10;
				else
					throw std::runtime_error("Integer cannot be initialized from a invalid string: " + s);

				for (auto &d : _data) {
					val += 1ULL * base * d;
					d = val % _base;
					val /= _base;
				}
				if (val)
					_data.emplace_back(val);
			}
		}

		if (_data.empty())
			_negative = false, _data.emplace_back(0);
	}

	std::string toString(uint32_t base=10U) const {
		if (base > 36U)
			throw std::runtime_error("Integer.toString does not support conversions beyond base 36: current base=" + base);

		std::string ans;
		std::vector<uint32_t> v { _data };
		while (!v.empty()) {
			uint64_t r = 0;
			for (auto it = v.rbegin(), end = v.rend(); it != end; ++it) {
				r = r * _base + *it;
				*it = r / base;
				r %= base;
			}

			if (r < 10)
				ans.push_back(r + '0');
			else if (r < 36)
				ans.push_back(r - 10 + 'A');

			if (!v.back())
				v.pop_back();
		}
		if (_negative)
			ans.push_back('-');
		std::reverse(ans.begin(), ans.end());
		return ans;
	}

	operator std::string() const {
		return toString();
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

	friend Integer operator +(const Integer &lhs, const Integer &rhs) {
		Integer ans;
		if (lhs._negative == rhs._negative) {
			ans._negative = lhs._negative;
			ans._data = _add(lhs._data, rhs._data);
		} else {
			int cmp = _compare(lhs._data, rhs._data);
			if (cmp > 0) {
				ans._negative = lhs._negative;
				ans._data = _sub(lhs._data, rhs._data);
			} else if (cmp < 0) {
				ans._negative = rhs._negative;
				ans._data = _sub(rhs._data, lhs._data);
			}
		}
		return ans;
	}

	friend Integer operator -(const Integer &lhs, const Integer &rhs) {
		Integer ans;
		if (lhs._negative != rhs._negative) {
			ans._negative = lhs._negative;
			ans._data = _add(lhs._data, rhs._data);
		} else {
			int cmp = _compare(lhs._data, rhs._data);
			if (cmp > 0) {
				ans._negative = lhs._negative;
				ans._data = _sub(lhs._data, rhs._data);
			} else if (cmp < 0) {
				ans._negative = !rhs._negative;
				ans._data = _sub(rhs._data, lhs._data);
			}
		}
		return ans;
	}

	friend Integer operator *(const Integer &lhs, const Integer &rhs) {
		Integer ans;
		ans._negative = lhs._negative != rhs._negative;
		ans._data = _mul(lhs._data, rhs._data);
		if (ans._data.empty() || (ans._data.size() == 1 && ans._data[0] == 0))
			ans._negative = false;
		return ans;
	}
};

#endif
