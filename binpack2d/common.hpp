#ifndef BP2D_CONFIG_HPP
#define BP2D_CONFIG_HPP

#if defined(_MSC_VER) &&  _MSC_VER <= 1800 || __cplusplus < 201103L
    #define BP2D_NOEXCEPT
    #define BP2D_CONSTEXPR
#elif __cplusplus >= 201103L
    #define BP2D_NOEXCEPT noexcept
    #define BP2D_CONSTEXPR constexpr
#endif

#include <stdexcept>
#include <string>
#include <cmath>

namespace binpack2d {

template< class T >
struct remove_cvref {
    typedef std::remove_cv_t<std::remove_reference_t<T>> type;
};

template< class T >
using remove_cvref_t = typename remove_cvref<T>::type;

const auto BP2D_CONSTEXPR Pi = 2*acos(0);

/**
 * @brief The Double class
 */
class Double {
  double val_;
public:
  Double(): val_(double{}) { }
  Double(double d) : val_(d) { }

  operator double() const BP2D_NOEXCEPT { return val_; }
  operator double&() BP2D_NOEXCEPT { return val_; }
};

class Degrees;

/**
 * @brief Data type representing radians. It supports conversion to degrees.
 */
class Radians: public Double {
public:

    Radians(double rads = Double() ): Double(rads) {}
    Radians(const Degrees& degs);

    operator Degrees();
};

/**
 * @brief Data type representing degrees. It supports conversion to radians.
 */
class Degrees: public Double {
public:
    Degrees(double deg = Double()): Double(deg) {}
    Degrees(const Radians& rads): Double( rads * 180/Pi ) {}
};

inline bool operator==(const Degrees& deg, const Radians& rads) {
    Degrees deg2 = rads;
    auto diff = std::abs(deg - deg2);
    return diff < 0.0001;
}

inline bool operator==(const Radians& rads, const Degrees& deg) {
    return deg == rads;
}

class UnimplementedException : public std::exception
{
    std::string info_;
    mutable std::string basic_txt_;
public:

    UnimplementedException(const std::string& info = ""): info_(info) {}

    virtual char const * what() const BP2D_NOEXCEPT;
};



}
#endif // BP2D_CONFIG_HPP
