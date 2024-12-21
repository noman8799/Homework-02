#include <iostream>
#include <vector>
#include <stdexcept>

class Vector {
private:
    std::vector<double> components;

public:
    // Constructor
    Vector(std::initializer_list<double> list) : components(list) {}

    // Copy Constructor
    Vector(const Vector& other) : components(other.components) {}

    // Assignment Operator
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            components = other.components;
        }
        return *this;
    }

    // Getters
    const std::vector<double>& getComponents() const { return components; }

    // Setters
    void setComponents(const std::vector<double>& newComponents) { components = newComponents; }

    // Arithmetic Operators
    Vector operator+(const Vector& other) const {
        if (components.size() != other.components.size()) {
            throw std::invalid_argument("Vectors must be of the same dimension.");
        }
        Vector result(*this);
        for (size_t i = 0; i < components.size(); ++i) {
            result.components[i] += other.components[i];
        }
        return result;
    }

    Vector operator-(const Vector& other) const {
        if (components.size() != other.components.size()) {
            throw std::invalid_argument("Vectors must be of the same dimension.");
        }
        Vector result(*this);
        for (size_t i = 0; i < components.size(); ++i) {
            result.components[i] -= other.components[i];
        }
        return result;
    }

    // Scalar Multiplication
    Vector operator*(double scalar) const {
        Vector result(*this);
        for (double& component : result.components) {
            component *= scalar;
        }
        return result;
    }

    // Dot Product
    double operator*(const Vector& other) const {
        if (components.size() != other.components.size()) {
            throw std::invalid_argument("Vectors must be of the same dimension.");
        }
        double dotProduct = 0.0;
        for (size_t i = 0; i < components.size(); ++i) {
            dotProduct += components[i] * other.components[i];
        }
        return dotProduct;
    }

    // Compound Assignment Operators
    Vector& operator+=(const Vector& other) {
        *this = *this + other;
        return *this;
    }

    Vector& operator-=(const Vector& other) {
        *this = *this - other;
        return *this;
    }

    Vector& operator*=(double scalar) {
        *this = *this * scalar;
        return *this;
    }

    // Stream Operators
    friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
        os << "[";
        for (size_t i = 0; i < vec.components.size(); ++i) {
            os << vec.components[i];
            if (i < vec.components.size() - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Vector& vec) {
        std::vector<double> newComponents;
        double value;
        char comma;
        is >> std::ws; // Ignore leading whitespace
        if (is.peek() == '[') {
            is.ignore(); // Ignore the opening bracket
        }
        while (is >> value) {
            newComponents.push_back(value);
            if (is.peek() == ',') {
                is >> comma; // Consume the comma
            }
            if (is.peek() == ']') {
                is.ignore(); // Ignore the closing bracket
                break; // Stop reading if we reach the end of the vector
            }
        }
        vec.setComponents(newComponents);
        return is;
    }
};

// Example usage
int main() {
    Vector vec1 = {1.0, 2.0, 3.0};
    Vector vec2 = {4.0, 5.0, 6.0};

    std::cout << "Vector 1: " << vec1 << std::endl; // Output: [1, 2, 3]
    std::cout << "Vector 2: " << vec2 << std::endl; // Output: [4, 5, 6]

    Vector vec3 = vec1 + vec2;
    std::cout << "Addition: " << vec3 << std::endl; // Output: [5, 7, 9]

    Vector vec4 = vec1 - vec2