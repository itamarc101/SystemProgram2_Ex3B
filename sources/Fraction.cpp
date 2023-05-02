#include "Fraction.hpp"
#include <math.h>

using namespace std;

namespace ariel
{
    int Fraction::gcd(int a, int b)     // gcd 
    {
        if(b ==0) return a;
        return gcd(b, a% b);
    }

    void Fraction::reduce()             // reduces the fraction the most possible
    {
        if(_denominator == 0) throw invalid_argument("Invalid: division by zero"); // denom cant be 0
        if(_numerator == 0) _denominator = 1;   // default setting if num is 0 0/1 is the most reduced form
        else    // num != 0
        {
            int gcdd = gcd(abs(_numerator), abs(_denominator));
            _numerator /= gcdd;
            _denominator /= gcdd;
        }

        if(_denominator < 0)    // if fraction is negative mention that
        {
            _numerator = -_numerator;
            _denominator = -_denominator;
        }
    }

    // constructor
    Fraction::Fraction(int num, int den): _numerator(num), _denominator(den)
    {
        if (den == 0) throw invalid_argument("Denom cant be zero");
        reduce();
    }

    // constructor of num float, supposed to be 3 numbers after dot
    Fraction::Fraction(float num)
    {
        int n = (int)num; // int
        int nume = round((num - n) * 1000); // 3 decimal
        int deno = 1000;
        if( nume == 0)
        {
            _numerator = (int) num;
            _denominator = 1;
        } else
        {
            int gcdd = Fraction::gcd(nume, deno);
            _numerator = (n * deno + nume) / gcdd;
            _denominator = deno / gcdd;
        }
        reduce();
    }

    Fraction::Fraction(const Fraction& other): _numerator(other._numerator), _denominator(other._denominator) {}

    Fraction::Fraction(Fraction&& other) noexcept: _numerator(other._numerator), _denominator(other._denominator) {}

    // constructor
    Fraction::Fraction(): _numerator(0), _denominator(1) { }

    int Fraction::getNumerator() const
    {
        return _numerator;
    }

    int Fraction::getDenominator() const
    {
        return _denominator;
    }

    // ALL operator+ functions
    // fraction + fraction
    const Fraction Fraction::operator+(const Fraction& other) const
    {
    if ((_numerator > 0 && other._numerator > std::numeric_limits<int>::max() - _numerator) ||
        (_numerator < 0 && other._numerator < std::numeric_limits<int>::min() - _numerator)) {
        throw std::overflow_error("Overflow detected in addition");
    }
    int num = _numerator * other._denominator + other._numerator * _denominator;
    int den = _denominator * other._denominator;

    return Fraction(num, den);
    }

    // fraction + float
    const Fraction Fraction::operator+(const float& other) const
    {
        return (*this) + Fraction(other);
    }    

    // float + fraction 
    const Fraction operator+(const float& num, const Fraction& other)
    {
        return Fraction(num) + other;
    }

    // ALL operator- functions
    // fraction - fraction
    // const Fraction Fraction::operator-(const Fraction& other) const
    // {
    //     if (_denominator == 0 || other._denominator == 0) {
    //         throw std::invalid_argument("Invalid Fraction: denominator cannot be zero");
    //     }

    //     // calculate the common denominator
    //     int common_denominator = _denominator * other._denominator;

    //     // calculate the new numerators
    //     int this_numerator = _numerator * other._denominator;
    //     int other_numerator = other._numerator * _denominator;

    //     // check for overflow
    //     if ((this_numerator > 0 && other_numerator < std::numeric_limits<int>::min() + this_numerator) ||
    //         (this_numerator < 0 && other_numerator > std::numeric_limits<int>::max() + this_numerator)) {
    //         throw std::overflow_error("Overflow detected in subtraction");
    //     }

    //     // subtract the numerators
    //     int result_numerator = this_numerator - other_numerator;
    //     int result_denominator = common_denominator;

    //     // reduce the fraction
    //     if (result_numerator != 0) {
    //         // find the gcd of the numerator and denominator
    //         int gcd_result = 1;
    //         int smaller = (result_numerator > 0) ? result_numerator : -result_numerator;
    //         if (smaller < result_denominator) {
    //             smaller = result_denominator;
    //         }
    //         for (int i = smaller; i >= 2; i--) {
    //             if ((result_numerator % i == 0) && (result_denominator % i == 0)) {
    //                 gcd_result = i;
    //                 break;
    //             }
    //         }
    //         result_numerator /= gcd_result;
    //         result_denominator /= gcd_result;
    //     }

    //     return Fraction(result_numerator, result_denominator);
    // }


//     const Fraction Fraction::operator-(const Fraction& other) const {
//     if ((_numerator < 0 && other._numerator > std::numeric_limits<int>::max() + _numerator) ||
//         (_numerator > 0 && other._numerator < std::numeric_limits<int>::min() + _numerator)) {
//         throw std::overflow_error("Overflow detected in subtraction");
//     }
//     int num = _numerator * other._denominator - other._numerator * _denominator;
//     int den = _denominator * other._denominator;
//     return Fraction(num, den);
// }
// const Fraction Fraction::operator-(const Fraction& other) const
// {
//     // check for integer overflow
//     if ((_numerator > 0 && other._numerator < std::numeric_limits<int>::min() + _numerator) ||
//         (_numerator < 0 && other._numerator > std::numeric_limits<int>::max() + _numerator)) {
//         throw std::overflow_error("Overflow detected in sub");
//     }

//     // calculate the common denominator
//     int common_denominator = _denominator * other._denominator;

//     // calculate the new numerators
//     int this_numerator = _numerator * other._denominator;
//     int other_numerator = other._numerator * _denominator;

//     // check for integer overflow again
//     if ((this_numerator > 0 && other_numerator < std::numeric_limits<int>::min() + this_numerator) ||
//         (this_numerator < 0 && other_numerator > std::numeric_limits<int>::max() + this_numerator)) {
//         throw std::overflow_error("Overflow detected in sub");
//     }

//     // subtract the numerators
//     int result_numerator = this_numerator - other_numerator;
//     int result_denominator = common_denominator;

//     // create a new fraction with the result
//     return Fraction(result_numerator, result_denominator);
// }

    const Fraction Fraction::operator-(const Fraction& other) const
    {
        // check for overflow
        long long num = static_cast<long long>(_numerator) * other._denominator -
                    static_cast<long long>(other._numerator) * _denominator;
        if (num < std::numeric_limits<int>::min() || num > std::numeric_limits<int>::max()) {
            throw std::overflow_error("Overflow detected in subtraction");
        }

        int den = _denominator * other._denominator;

        return Fraction(static_cast<int>(num), den);
    }

    // fraction - float
    const Fraction Fraction::operator-(const float& other) const
    {
        return (*this) - Fraction(other);
    }    

    // float - fraction
    const Fraction operator-(const float& num, const Fraction& other)
    {
        return Fraction(num) - other;
    }

    // ALL operator* functions
    // fraction * fraction
    const Fraction Fraction::operator*(const Fraction& other) const
    {
        // Check if numerator or denominator of either fraction is 0, and return 0 if so
        if (_numerator == 0 || other._numerator == 0 || _denominator == 0 || other._denominator == 0) {
            return Fraction(0);
        }

        // Calculate the new numerator and denominator after multiplication
        int num = _numerator * other._numerator;
        int den = _denominator * other._denominator;

        // Check for integer overflow
        if (num / other._numerator != _numerator || num / _numerator != other._numerator || den / other._denominator != _denominator) {
            throw std::overflow_error("Overflow detected in multiplication");
        }
        return Fraction(num, den);
    }

    // fraction * float
    const Fraction Fraction::operator*(const float& num) const
    {
        return (*this) * Fraction(num);
    }

    // float * fraction
    const Fraction operator*(const float& num, const Fraction& other)
    {
        return Fraction(num) * other;
    }

    // ALL operator/ functions
    // fraction / fraction
    const Fraction Fraction::operator/(const Fraction& other) const
    {
        //(a/b) / (c/d) => (a*d)/(b*c)
        // if num is 0 then cant divide 
        if (other._numerator == 0 || _denominator == 0) {
            throw std::runtime_error("Division by zero");
        }

        if ((_numerator > 0 && other._numerator > std::numeric_limits<int>::max() / _denominator) ||
        (_numerator < 0 && other._numerator < std::numeric_limits<int>::min() / _denominator))
        {
            throw std::overflow_error("Overflow detected in division");
        }


        if ((_numerator > std::numeric_limits<int>::max() / other._denominator) ||
            (_numerator < std::numeric_limits<int>::min() / other._denominator)) {
            throw std::overflow_error("Overflow detected in division");
        }

        
        int num = _numerator * other._denominator;
        int den = _denominator * other._numerator;

        return Fraction(num, den);

    }


    // fraction / float
    const Fraction Fraction::operator/(const float& num) const
    {
        if( num == 0) throw runtime_error("Division by zero ERROR");
        return (*this) / Fraction(num);
    }

    // float / fraction
    const Fraction operator/(const float& num, const Fraction& other)
    {
        if(other._numerator == 0) throw runtime_error("Division by zero ERROR)");
        return Fraction(num) / other;
    }

    // = operator to set a fraction 
    Fraction& Fraction::operator=(const Fraction& frac)
    {
        if(this == &frac) return (*this);
        
        _numerator = frac._numerator;
        _denominator = frac._denominator;
    
        return (*this);
    }

    Fraction& Fraction::operator=(Fraction&& other) noexcept {
    if (this != &other) {
        _numerator = other._numerator;
        _denominator = other._denominator;
    }
    return (*this);
}


    //ALL bool functions

    // fraction == fraction
    // tolerance 0.001, fractions are equal if their difference is in the range of tolerance(3 decimal)
    // calculate float without round.
    bool Fraction::operator==(const Fraction& other) const
    {
        float frac1 = (float)_numerator / _denominator;
        float frac2 = (float)other._numerator / other._denominator;
        float tolerance = 0.001;

        return std::abs(frac1 - frac2) < tolerance;
    }

    // fraction != fraction by using == 
    bool Fraction::operator!=(const Fraction& other) const 
    {
        return !(*this == other);
    }

    // fraction > fraction
    bool Fraction::operator>(const Fraction& other) const
    {
     return _numerator * other._denominator > other._numerator * _denominator;   
    }
    
    // fraction >= fraction
    bool Fraction::operator>=(const Fraction& other) const
    {
     return _numerator * other._denominator >= other._numerator * _denominator;   
    }

    // fraction <= fraction
    bool Fraction::operator<=(const Fraction& other) const
    {
     return _numerator * other._denominator <= other._numerator * _denominator;   
    }

    // fraction < fraction
    bool Fraction::operator<(const Fraction& other) const
    {
        return _numerator * other._denominator < other._numerator * _denominator;
    }

    // bool float fraction operations

    bool operator==(const float& other, const Fraction& frac)
    {
        return Fraction(other) == frac;
    }

    bool operator!=(const float& other, const Fraction& frac)
    {
        return Fraction(other) != frac;
    }

    bool operator<(const float& other, const Fraction& frac)
    {
        return Fraction(other) < frac;
    }

    bool operator<=(const float& other, const Fraction& frac)
    {
        return Fraction(other) <= frac;
    }

    bool operator>(const float& other, const Fraction& frac)
    {
        return Fraction(other) > frac;
    }

    bool operator>=(const float& other, const Fraction& frac)
    {
        return Fraction(other) >= frac;
    }

    // fraction and float
    bool operator==(const Fraction& frac, const float& other)
    {
        return frac == Fraction(other);
    }

    bool operator!=(const Fraction& frac, const float& other)
    {
        return frac != Fraction(other);
    }

    bool operator<(const Fraction& frac, const float& other)
    {
        return frac < Fraction(other);
    }

    bool operator<=(const Fraction& frac, const float& other)
    {
        return frac <= Fraction(other);
    }

    bool operator>(const Fraction& frac, const float& other)
    {
        return frac > Fraction(other) ;
    }

    bool operator>=(const Fraction& frac, const float& other)
    {
        return frac >= Fraction(other) ;
    }

    // inc ++ and dec -- operations

    Fraction& Fraction::operator++()
    {
        _numerator += _denominator;
        reduce();
        return (*this);
    }

    Fraction Fraction::operator++(int)
    {
        Fraction frac = (*this);
        _numerator += _denominator;
        reduce();
        return frac;
    }

    Fraction& Fraction::operator--()
    {
        _numerator -= _denominator;
        reduce();
        return (*this);
    }

    Fraction Fraction::operator--(int)
    {
        Fraction frac= (*this);
        _numerator -= _denominator;
        reduce();
        return frac;
    }
    // input and output stream
    ostream& operator<<(ostream &ost, const Fraction& frac)
    {
        ost << frac._numerator << "/" << frac._denominator;
        return ost;
    }

    istream& operator>>(istream &ist, Fraction& frac) {
    int num, den;
    //char ch;
    if (!(ist >> num >> den)) throw runtime_error("Invalid input for Fraction");
    if( den == 0) throw runtime_error("demon cant be 0!");

    frac = Fraction(num, den);
    return ist;
}

}