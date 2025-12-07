#include "fraction.h"
#include <exception>

Fraction::Fraction() noexcept : numerator_(0), denominator_(1){
}

Fraction::Fraction( double a) noexcept {
    this->denominator_ = (1e+16);
    this->numerator_ = (a * this->denominator_);
    (*this).Normalize();
}

Fraction::Fraction(int a, int b, bool to_simplified = true) : numerator_(a), denominator_(b) {
    (*this).to_simplify_ = to_simplified;
    if ( b == 0) {
        throw std::exception();
    }
    (*this).Normalize();
}

Fraction::Fraction( const Fraction& a) noexcept {
    this->numerator_ = a.numerator_;
    this->denominator_ = a.denominator_;
    this->to_simplify_ = a.to_simplify_;
}

Fraction::Fraction(Fraction&& other) noexcept {
    (*this).numerator_ = other.numerator_;
    (*this).denominator_ = other.denominator_;
    (*this).to_simplify_ = other.to_simplify_;
    other.numerator_ = 0;
    other.denominator_ = 0;
}

Fraction& Fraction::operator=(const Fraction& a) noexcept{
    this->numerator_ = a.numerator_;
    this->denominator_ = a.denominator_;
    this->to_simplify_ = a.to_simplify_;
    return (*this);
};
        
Fraction& Fraction::operator=(Fraction&& a) noexcept {
    this->numerator_ = a.numerator_;
    this->denominator_ = a.denominator_;
    this->to_simplify_ = a.to_simplify_;
    a.numerator_ = 0;
    a.denominator_ = 0;
    return (*this);
};
        
Fraction::~Fraction() noexcept {
    this->numerator_ = 0;
    this->denominator_ = 0;
};

Fraction& Fraction::operator-() {
    (*this).numerator_ *= -1;
    return (*this);
}

Fraction& Fraction::operator++() {
    (*this).numerator_ += (*this).denominator_;
    (*this).Normalize();
    return (*this);
}

Fraction Fraction::operator++(int k) {
    Fraction copy((*this));
    (*this).numerator_ += (*this).denominator_;
    (*this).Normalize();
    return copy;
}

Fraction& Fraction::operator--() {
    (*this).numerator_ -= (*this).denominator_;
    (*this).Normalize();
    return (*this);
}

Fraction Fraction::operator--(int k) {
    Fraction copy(*this);
    (*this).numerator_ -= (*this).denominator_;
    (*this).Normalize();
    return copy;
}

Fraction& Fraction::operator!() {
    int copy_d((*this).denominator_);
    int copy_n((*this).numerator_);
    (*this).numerator_ = copy_d;
    (*this).denominator_ = copy_n;
    return (*this);
}

bool Fraction::operator==(const Fraction& other) {
    if ((other.numerator_ == (*this).numerator_) && (other.denominator_ == (*this).denominator_))
    return true;
    else 
    return false;
}

bool Fraction::operator==(const double a) {
    if (static_cast<double>(((*this).numerator_*1.0 / (*this).denominator_)) == a) {
        return true;
    } else {
        return false;
    }
}

bool operator==(const double a, const Fraction& b) {
    if ( static_cast<double>((b.numerator_*1.0 / b.denominator_)) == a  ) {
        return true;
    } else {
        return false;
    }
}

Fraction Fraction::operator-(const Fraction& a) const noexcept {
    Fraction result;
    result.denominator_ = denominator_ * a.denominator_;
    result.numerator_ = numerator_ * a.denominator_ - a.numerator_ * denominator_;   
    result.Normalize();
    return result;
}

Fraction Fraction::operator-( const double a) const noexcept{
    Fraction result ( numerator_ - a*denominator_, denominator_ );
    result.Normalize();
    return result;
}

Fraction operator-(const double a, const Fraction& b) noexcept {
    Fraction result = (b - a);
    return result;
}

Fraction Fraction::operator+( const Fraction& a) const noexcept {
    Fraction copy_a(a);
    Fraction result = ( (*this) - (-copy_a));
    result.Normalize();
    return result;
}

Fraction Fraction::operator+( const double a) const noexcept {
    double copy_a(a);
    Fraction result = ( (*this) - (-copy_a));
    result.Normalize();
    return result;
}

Fraction operator+( const double a, const Fraction& b) noexcept {
    Fraction copy_b (b);
    double copy_a(a);
    Fraction result = ( copy_b - (-copy_a));
    result.Normalize();
    return  result;;
}

Fraction& Fraction::operator+=( const Fraction& a) noexcept {
    (*this) = (*this) + a;
    return (*this);
}

Fraction& Fraction::operator+=( const double a ) noexcept {
    (*this) = (*this) + a;
    return (*this);
}

Fraction& Fraction::operator-=( const Fraction& a) noexcept {
    (*this) = (*this) - a;
    return (*this);
}

Fraction& Fraction::operator-=( const double a ) noexcept {
    (*this) = (*this) - a;
    return (*this);
}

Fraction Fraction::operator/(const Fraction& a) const noexcept {
    Fraction result;
    result.numerator_ = numerator_ * a.denominator_;
    result.denominator_ = denominator_ * a.numerator_;
    result.Normalize();
    return result;
}

Fraction Fraction::operator/(const double a) const {
    Fraction result;
    if ( a == 0) {
        throw std::exception();
    }
    result.numerator_ = numerator_;
    result.denominator_ = denominator_ * a;
    result.Normalize();
    return result;
}

Fraction operator/(const double a, const Fraction& b) noexcept {
    Fraction result;
    result.numerator_ = a * b.denominator_;
    result.denominator_ = b.numerator_;
    result.Normalize();
    return result;
}

Fraction& Fraction::operator/=(const Fraction& a) noexcept {
    numerator_ = numerator_ * a.denominator_;
    denominator_ = denominator_ * a.numerator_;
    Normalize();
    return (*this);
}

Fraction& Fraction::operator/=(const double a) noexcept {
    denominator_ = denominator_ * a;
    Normalize();
    return (*this);
}

Fraction Fraction::operator*(const Fraction& a) const noexcept {
    Fraction result;
    result.numerator_ = numerator_ * a.numerator_;
    result.denominator_ = denominator_ * a.denominator_;
    result.Normalize();
    return result;
}

Fraction Fraction::operator*(const double a) const noexcept {
    Fraction result;
    result.numerator_ = numerator_ * a;
    result.denominator_ = denominator_;
    result.Normalize();
    return result;
}

Fraction operator*(const double a, const Fraction& b) noexcept {
    Fraction result;
    result.numerator_ = a * b.numerator_;
    result.denominator_ = b.denominator_;
    result.Normalize();
    return result;
}

Fraction& Fraction::operator*=(const Fraction& a) noexcept {
    numerator_ = numerator_ * a.numerator_;
    denominator_ = denominator_ * a.denominator_;
    Normalize();
    return (*this);
}

Fraction& Fraction::operator*=(const double a) noexcept {
    numerator_ = numerator_ * a;
    Normalize();
    return (*this);
}

bool Fraction::operator<(const Fraction& a) const noexcept {
    Fraction temp = ((*this) - a);
    if (temp.numerator_ < 0) {
        return true;
    } else {
        return false;
    }
}

bool Fraction::operator<(const double a) const noexcept {
    Fraction temp = ((*this) - a);
    if (temp.numerator_ < 0) {
        return true;
    } else {
        return false;
    }
}

bool operator<(const double a, const Fraction& b) noexcept {
    Fraction temp = (a - b);
    if (temp.numerator_ < 0) {
        return true;
    } else {
        return false;
    }
}

bool Fraction::operator>(const Fraction& a) const noexcept {
    Fraction temp = ((*this) - a);
    if (temp.numerator_ > 0) {
        return true;
    } else {
        return false;
    }
}

bool Fraction::operator>(const double a) const noexcept {
    Fraction temp = ((*this) - a);
    if (temp.numerator_ > 0) {
        return true;
    } else {
        return false;
    }
}

bool operator>(const double a, const Fraction& b) noexcept {
    Fraction temp = (a - b);
    if (temp.numerator_ > 0) {
        return true;
    } else {
        return false;
    }
}

std::istream& operator>>( std::istream& in,  Fraction& a) noexcept {
    in >> a.numerator_ >> a.denominator_;
    a.Normalize();
    return in;
}

std::ostream& operator<<( std::ostream& out, const Fraction& a) noexcept {
    if ( a.numerator_ != 0) {
    out << a.numerator_ << "/" << a.denominator_;
    } else {
        out << 0;
    }
    return out;
};

Fraction& Fraction::SetNum ( const int a) noexcept {
    this->numerator_ = a;
    (*this).Normalize();
    return (*this);
}

Fraction& Fraction::SetDen ( const int a) {
    if ( a == 0) {
        throw std::exception();
    }
    this->denominator_ = a;
    (*this).Normalize();
    return (*this);
};

double ToDouble ( const Fraction& a) noexcept {
    double result = (1.0*a.GetNum() / a.GetDen());
    return result;
}

Fraction abs( const Fraction& a) {
    return Fraction(std::abs(a.GetNum()), std::abs(a.GetDen()));
}

Fraction Fraction::pow(int exponent) const {
    if (exponent == 0) return Fraction(1);
    Fraction result(*this);
    for (int i = 1; i < std::abs(exponent); ++i) {
        result *= *this;
    }
    return exponent > 0 ? result : !result;
}
