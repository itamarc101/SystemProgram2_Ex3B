#include "Fraction.hpp"
#include <math.h>

using namespace std;

namespace ariel
{
    int Fraction::gcd(int a, int b)     // gcd calculation 
    {
        if(b ==0) return a;
        return gcd(b, a% b);
    }

    void Fraction::reduce()             // reduces the fraction the most possible
    {
        /* simplifies the fraction to the lowest form by dividing the numerator and denominator by their GCD
        dividing by the GCD ensures that the fraction is reduced to its lowers form since it cant be simplified further than that
         */
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
        // check if its max int or min int value
        if ((_numerator > 0 && other._numerator > numeric_limits<int>::max() - _numerator) ||
            (_numerator < 0 && other._numerator < numeric_limits<int>::min() - _numerator)) {
            throw overflow_error("Overflow detected in addition");
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
    const Fraction Fraction::operator-(const Fraction& other) const
    {
        // check for overflow
        // since numerator and denominator are int we convert to long long
        long long numSubCalc = static_cast<long long>(_numerator) * other._denominator -
                    static_cast<long long>(other._numerator) * _denominator;
        
        // cast back long long to int
        if (numSubCalc < numeric_limits<int>::min() || numSubCalc > numeric_limits<int>::max()) {
            throw overflow_error("Overflow detected in subtraction");
        }
        int den = _denominator * other._denominator;

        return Fraction(static_cast<int>(numSubCalc), den);
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
        // Check if numerator of either fraction is 0, and return 0 if yes
        if (_numerator == 0 || other._numerator == 0) return Fraction(0);

        // Calculate the new numerator and denominator after multiplication
        int num = _numerator * other._numerator;
        int den = _denominator * other._denominator;

        // Check for integer overflow
        if (num / other._numerator != _numerator || num / _numerator != other._numerator || den / other._denominator != _denominator) {
            throw overflow_error("Overflow detected in multiplication");
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
        if (other._numerator == 0){ 
            throw runtime_error("Division by zero");
        }

        if ((_numerator > 0 && other._numerator > numeric_limits<int>::max() / _denominator) ||
        (_numerator < 0 && other._numerator < numeric_limits<int>::min() / _denominator))
        {
            throw overflow_error("Overflow detected in division");
        }

        if ((_numerator > numeric_limits<int>::max() / other._denominator) ||
            (_numerator < numeric_limits<int>::min() / other._denominator)) {
            throw overflow_error("Overflow detected in division");
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

    /* = operator assigns value of another fraction to this fraction.
        constant reference to the fraction that will be assigned 
        reference to the modified fraction object
    */ 
    Fraction& Fraction::operator=(const Fraction& frac)
    {
        // checks if the current object is not equal to the parameter to avoid duplicating duplicants

        if(this == &frac) return (*this);
        // assign variable of object to this
        _numerator = frac._numerator;
        _denominator = frac._denominator;
    
        // return the reference to the modified fraction
        return (*this);
    }
    
    /* move operator
    moves content of other to the current
    other fraction to be moved
    Fraction& reference to current object after move
    */    
    Fraction& Fraction::operator=(Fraction&& other) noexcept 
    {
        // check if the objects are not same
        if (this != &other) {
            // moves variables from other
            _numerator = other._numerator;
            _denominator = other._denominator;
        }

        // return reference to current
        return (*this);
    }

    //ALL bool functions

    // compates fraction == fraction in range of 0.001
    // tolerance 0.001, fractions are equal if their difference is in the range of tolerance(3 decimal)
    // calculate float without round.
    bool Fraction::operator==(const Fraction& other) const
    {
        // converts the fraction to float
        float frac1 = (float)_numerator / _denominator;
        float frac2 = (float)other._numerator / other._denominator;
        
        // compate the difference between the fractions
        float tolerance = 0.001;

        return abs(frac1 - frac2) < tolerance;
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
        return frac > Fraction(other);
    }

    bool operator>=(const Fraction& frac, const float& other)
    {
        return frac >= Fraction(other);
    }

    // inc ++ and dec -- operations
    Fraction& Fraction::operator++() // prefix ++a
    {
        _numerator += _denominator;
        reduce();
        return (*this);
    }

    Fraction Fraction::operator++(int) // postfix a++
    {
        Fraction frac = (*this);
        _numerator += _denominator;
        reduce();
        return frac;

    }

    Fraction& Fraction::operator--() // --a
    {
        _numerator -= _denominator;
        reduce();
        return (*this);
    }

    Fraction Fraction::operator--(int)  // a++
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
        if (!(ist >> num >> den)) throw runtime_error("Invalid input for Fraction");
        if( den == 0) throw runtime_error("demon cant be 0!");

        frac = Fraction(num, den);
        return ist;
    }
}
