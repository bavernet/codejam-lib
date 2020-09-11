#ifndef __INTEGER_HPP__
#define __INTEGER_HPP__

#include <type_traits>
#include <stdexcept>
#include <limits>
#include <cctype>
#include <vector>
#include <string>

class Integer {
private:
	static const unsigned long long _base { std::numeric_limits<unsigned long>::max() };

	bool _negative;
	std::vector<unsigned long> _data;

	int _compare(const std::vector<unsigned long> &a, const std::vector<unsigned long> &b) const {
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
		long long v = i;
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

				unsigned long long val = *it - '0';
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

	bool operator ==(const Integer &rhs) const {
		return _negative == rhs._negative && _compare(_data, rhs._data) == 0;
	}

	bool operator !=(const Integer &rhs) const {
		return !(*this == rhs);
	}

	bool operator <(const Integer &rhs) const {
		if (_negative && !rhs._negative)
			return true;
		if (_negative)
			return _compare(_data, rhs._data) > 0;
		return _compare(_data, rhs._data) < 0;
	}

	bool operator >(const Integer &rhs) const {
		return rhs < *this;
	}
};

#endif
