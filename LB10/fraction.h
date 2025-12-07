#ifndef FRACTION_H
#define FRACTION_H

#include <cstdint>
#include <istream>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <exception>

class Fraction {
    private:

        int64_t numerator_;
        int64_t denominator_;
        bool to_simplify_ = true;

        Fraction& Normalize() {
            if ( this->denominator_ < 0) {
                this->denominator_ *= -1;
                this->numerator_ *= -1;
            }
            if ( (*this).to_simplify_ == true) {
                auto e = std::gcd(this->numerator_, this->denominator_);
                this->denominator_ /= e;
                this->numerator_ /= e;
            }
            return (*this);
        }

    public:
        
        Fraction() noexcept;

        Fraction( double) noexcept;
        
        Fraction(int, int, bool);
        
        Fraction(const Fraction &) noexcept;
        
        Fraction(Fraction &&) noexcept;
        
        Fraction& operator=(const Fraction&) noexcept;
        
        Fraction& operator=(Fraction&&) noexcept;
        
        ~Fraction() noexcept;
        
        Fraction& operator-();
        
        Fraction& operator++();
        
        Fraction operator++(int);
        
        Fraction& operator--();
        
        Fraction operator--(int);
        
        Fraction& operator!();
        
        bool operator==(const Fraction&);
        
        bool operator==(const double);

        friend bool operator==(const double,const Fraction&);

        Fraction operator-(const Fraction&) const noexcept;

        Fraction operator-(const double) const noexcept;

        friend Fraction operator-(const double, const Fraction&) noexcept;

        Fraction& operator-= ( const Fraction&) noexcept;

        Fraction& operator-=( const double) noexcept;

        Fraction operator+(const Fraction&) const noexcept;

        Fraction operator+(const double) const noexcept;

        friend Fraction operator+(const double, const Fraction&) noexcept;

        Fraction& operator+=( const Fraction&) noexcept;

        Fraction& operator+= ( const double) noexcept;

        Fraction operator/( const Fraction&) const noexcept;

        Fraction operator/( const double) const;

        friend Fraction operator/( const double, const Fraction&) noexcept;

        Fraction& operator/=( const Fraction&) noexcept;

        Fraction& operator/=( const double) noexcept;

        Fraction operator*( const Fraction&) const noexcept;

        Fraction operator*( const double) const noexcept;

        friend Fraction operator*( const double, const Fraction&) noexcept;

        Fraction& operator*=( const Fraction&) noexcept;

        Fraction& operator*=( const double) noexcept;
        
        bool operator<( const Fraction&) const noexcept;
        
        bool operator<(const double) const noexcept;
        
        friend bool operator<(const double, const Fraction&) noexcept;
        
        bool operator>( const Fraction&) const noexcept;
        
        bool operator>(const double) const noexcept;
        
        friend bool operator>(const double, const Fraction&) noexcept;

        friend std::istream& operator>>( std::istream&, Fraction&) noexcept;

        friend std::ostream& operator<<( std::ostream&, const Fraction&) noexcept;

        int64_t GetNum() const noexcept {
            return (*this).numerator_;
        };

        int64_t GetDen () const noexcept {
            return (*this).denominator_;
        };

        Fraction& SetNum ( const int) noexcept;

        Fraction& SetDen ( const int);

        friend double ToDouble (const Fraction&) noexcept;

        Fraction pow( int32_t ) const;

        friend Fraction abs( const Fraction&) ;

        int64_t round() const {  // округление
            return static_cast<int64_t>(ToDouble(*this) + 0.5 * (numerator_ > 0 ? 1 : -1));
        }

        int64_t floor() const { 
            return numerator_ / denominator_;
        }

        Fraction fractional() const {
            return *this - Fraction(floor());
        }

};

#endif
