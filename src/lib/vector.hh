#pragma once
#include <array>
#include <iostream>

namespace newt::lib {
    template<typename T, std::size_t dim>
    class vector {
        std::array<T, dim> data{};
        public:
            inline vector() = default;
            inline vector(const std::initializer_list<T> list) {
                std::copy(list.begin(), list.end(), data.begin());
            }

            inline T at(std::size_t index) const { return data.at(index); }
            inline T x() const { return data.at(0); }
            inline T y() const { return data.at(1); }
            inline T z() const { return data.at(2); }
            inline T w() const { return data.at(3); }

            inline void print() const {
                for (auto val : data) {
                    std::cout << val << " ";
                }
                std::printf("\n");
            }

            inline vector<T, dim>& operator +=(const vector<T, dim>& other) { for (std::size_t i = 0; i < dim; ++i) { data[i] += other.data[i]; } return *this; }
            inline vector<T, dim>& operator -=(const vector<T, dim>& other) { for (std::size_t i = 0; i < dim; ++i) { data[i] -= other.data[i]; } return *this; }
            inline vector<T, dim>& operator *=(const vector<T, dim>& other) { for (std::size_t i = 0; i < dim; ++i) { data[i] *= other.data[i]; } return *this; }
            inline vector<T, dim>& operator /=(const vector<T, dim>& other) { for (std::size_t i = 0; i < dim; ++i) { data[i] /= other.data[i]; } return *this; }
            inline vector<T, dim>& operator *=(T scalar) { for (auto& val : data) { val *= scalar; } return *this; }
            inline vector<T, dim>& operator /=(T scalar) { for (auto& val : data) { val /= scalar; } return *this; }
            inline vector<T, dim> operator +(const vector<T, dim>& other) const { auto copy = *this; for (std::size_t i = 0; i < dim; ++i) { copy.data[i] += other.data[i]; } return copy; }
            inline vector<T, dim> operator -(const vector<T, dim>& other) const { auto copy = *this; for (std::size_t i = 0; i < dim; ++i) { copy.data[i] -= other.data[i]; } return copy; }
            inline vector<T, dim> operator *(const vector<T, dim>& other) const { auto copy = *this; for (std::size_t i = 0; i < dim; ++i) { copy.data[i] *= other.data[i]; } return copy; }
            inline vector<T, dim> operator /(const vector<T, dim>& other) const { auto copy = *this; for (std::size_t i = 0; i < dim; ++i) { copy.data[i] /= other.data[i]; } return copy; }
            inline vector<T, dim> operator *(T scalar) const { auto copy = *this; for (auto& val : copy.data) { val *= scalar; } return copy; }
            inline vector<T, dim> operator /(T scalar) const { auto copy = *this; for (auto& val : copy.data) { val /= scalar; } return copy; }
    };
}