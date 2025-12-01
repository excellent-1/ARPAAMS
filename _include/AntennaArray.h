#pragma once
#include <vector>
#include <complex>

/**
 * @brief Represents a physical antenna array with multiple elements.
 *        Stores element positions and signal samples.
 */
class AntennaArray
{
public:
    using Complex = std::complex<double>;

    AntennaArray() = default;
    explicit AntennaArray(size_t numElements)
        : elements(numElements, Complex(0.0, 0.0)) {}

    /// Get number of antenna elements
    size_t size() const { return elements.size(); }

    /// Set signal value for an element
    void setElement(size_t index, Complex value)
    {
        elements.at(index) = value;
    }

    /// Access signal value at an element
    Complex getElement(size_t index) const
    {
        return elements.at(index);
    }

    /// Get raw array reference
    const std::vector<Complex>& data() const { return elements; }

private:
    std::vector<Complex> elements;
};
