#include <iostream>
using namespace std;

namespace ariel
{
    class Fraction
    {
        private:
        int _numerator;      // mone
        int _denominator;    // shever

        void reduce() ;  // reduce the fraction as much as possible
        int gcd(int numa, int numb);  // greatest common divisor

        public:
        Fraction(); // default constructor for 0/1
        Fraction(float num);    // make float as fraction a/b form
        Fraction(int numerator, int denominator);   // fraction constructor
        
        /* copy constructor makes shallow copy of object copies the variables of the original object to a new one */
        Fraction(const Fraction& other);    // copy constructor
        
        /* we use move construtor to transfer resources (memory) from temp object to new object without copying the data
        improving performance and reducing memory usage*/
        Fraction(Fraction&& other) noexcept;     // move constructor
        
        /* destructor to ensure any dynamically allocated resources(memory) used is properly freed when an object is destroyed*/
        ~Fraction() = default;  // destructor


        int getNumerator() const;
        int getDenominator() const;


        const Fraction operator+(const Fraction& other) const;                      // Fraction + Fraction
        const Fraction operator+(const float& num) const;                           // Fraction + flaot
        friend const Fraction operator+(const float& num, const Fraction& other);   // float + Fraction
        // friend - non-member function and need to be declared as friend inside Fraction.
        // to allow access to private members of Fraction to perform operations

        const Fraction operator-(const Fraction& other) const;                      // Fraction - Fraction
        const Fraction operator-(const float& num) const;                           // Fraction - flaot
        friend const Fraction operator-(const float& num, const Fraction& other);   // float - Fraction

        const Fraction operator*(const Fraction& other) const;                      // Fraction * Fraction
        const Fraction operator*(const float& num) const;                           // Fraction * flaot
        friend const Fraction operator*(const float& num, const Fraction& other);   // float * Fraction

        const Fraction operator/(const Fraction& other) const;                      // Fraction / Fraction
        const Fraction operator/(const float& num) const;                           // Fraction / flaot
        friend const Fraction operator/(const float& num, const Fraction& other);   // float / Fraction

        Fraction& operator=(const Fraction& frac);                                    // = to set frac val as frac
        Fraction& operator=(Fraction&& other) noexcept;

        // BOOL FRACTION FRACTION OPERATIONS
        bool operator==(const Fraction& other) const;       // fraction fraction
        bool operator>(const Fraction& other) const;
        bool operator<(const Fraction& other) const;
        bool operator>=(const Fraction& other) const;
        bool operator<=(const Fraction& other) const;

        // BOOL FLOAT FRACTION OPERATIONS
        friend bool operator ==(const float& other, const Fraction& frac);
        friend bool operator >(const float& other, const Fraction& frac);
        friend bool operator >=(const float& other, const Fraction& frac);
        friend bool operator <=(const float& other, const Fraction& frac);
        friend bool operator <(const float& other, const Fraction& frac);
        
        // BOOL FRACTION FLOAT OPERATIONS
        friend bool operator ==(const Fraction& frac, const float& other);
        friend bool operator >(const Fraction& frac, const float& other);
        friend bool operator >=(const Fraction& frac, const float& other);
        friend bool operator <(const Fraction& frac, const float& other);
        friend bool operator <=(const Fraction& frac, const float& other);

        // INC , DEC OPERATIONS
        Fraction& operator++();
        Fraction operator++(int);
        Fraction& operator--();
        Fraction operator--(int);

        friend std::ostream& operator<<(std::ostream& ost, const Fraction& frac); // input stream
        friend std::istream& operator>>(std::istream& ist, Fraction& frac);        // output stream
        
    };
}
