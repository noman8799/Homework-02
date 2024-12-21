#include <iostream>
#include <numeric> // for std::gcd

class Fraction {
private:
    int numerator;
    int denominator;

    void simplify() {
        int gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
        if (denominator < 0) { // Keep denominator positive
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    // Constructors
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        simplify();
    }

    // Getters
    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

    // Setters
    void setNumerator(int num) { numerator = num; simplify(); }
    void setDenominator(int denom) {
        if (denom == 0) {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        denominator = denom; 
        simplify();
    }

    // Arithmetic Operators
    Fraction operator+(const Fraction& other) const {
        return Fraction(numerator * other.denominator + other.numerator * denominator,
                        denominator * other.denominator);
    }

    Fraction operator-(const Fraction& other) const {
        return Fraction(numerator * other.denominator - other.numerator * denominator,
                        denominator * other.denominator);
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Cannot divide by zero.");
        }
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }

    // Compound Assignment Operators
    Fraction& operator+=(const Fraction& other) {
        *this = *this + other;
        return *this;
    }

    Fraction& operator-=(const Fraction& other) {
        *this = *this - other;
        return *this;
    }

    Fraction& operator*=(const Fraction& other) {
        *this = *this * other;
        return *this;
    }

    Fraction& operator/=(const Fraction& other) {
        *this = *this / other;
        return *this;
    }

    // Conversion to double
    double toDouble() const {
        return static_cast<double>(numerator) / denominator;
    }

    // Stream Operators
    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
        os << frac.numerator << "/" << frac.denominator;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Fraction& frac) {
        char slash; // to consume the '/' character
        is >> frac.numerator >> slash >> frac.denominator;
        frac.simplify();
        return is;
    }
};

// Example usage
int main() {
    Fraction frac1(1, 2);
    Fraction frac2(3, 4);
    
    std::cout << "Fraction 1: " << frac1 << std::endl; // Output: 1/2
    std::cout << "Fraction 2: " << frac2 << std::endl; // Output: 3/4

    std::cout << "Addition: " << (frac1 + frac2) << std::endl; // Output: 5/4
    std::cout << "Subtraction: " << (frac1 - frac2) << std::endl; // Output: -1/4
    std::cout << "Multiplication: " << (frac1 * frac2) << std::endl; // Output: 3/8
    std::cout << "Division: " << (frac1 / frac2) << std::endl; // Output: 2/3
    std::cout << "Fraction 1 as double: " << frac1.toDouble() << std::endl; // Output: 0.5

    return 0;
}