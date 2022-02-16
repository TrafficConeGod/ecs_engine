#pragma once
#include <array>
#include <cmath>
#include <fmt/core.h>
#include <fmt/ranges.h>

namespace newt::lib {
    template<typename T, std::size_t dim>
    class vector {
        std::array<T, dim> data{};
        public:
            inline vector() = default;
            inline vector(const std::array<T, dim>& data_) : data(data_) {}
            inline vector(std::initializer_list<T> list) {
                std::copy(list.begin(), list.end(), data.begin());
            }

            inline T at(std::size_t index) const { return data.at(index); }
            inline T x() const { return data.at(0); }
            inline T y() const { return data.at(1); }
            inline T z() const { return data.at(2); }
            inline T w() const { return data.at(3); }

            template<typename format_context>
            constexpr auto format(format_context& ctx) const {
                return fmt::format_to(ctx.out(), "{}", data);
            }

            template<typename U>
            U magnitude() const {
                U sum = 0;
                for (auto val : data) {
                    sum += val * val;
                }
                return std::sqrt(sum);
            }

            template<typename U>
            operator vector<U, dim>() const {
                std::array<U, dim> arr;
                for (std::size_t i = 0; i < dim; ++i) {
                    arr[i] = static_cast<U>(data[i]);
                }
                return vector<U, dim>(arr);
            }

            // All vector operators
            vector<T, dim>& operator +=(const vector<T, dim>& other) { for (std::size_t i = 0; i < dim; ++i) { data[i] += other.data[i]; } return *this; }
            vector<T, dim>& operator -=(const vector<T, dim>& other) { for (std::size_t i = 0; i < dim; ++i) { data[i] -= other.data[i]; } return *this; }
            vector<T, dim>& operator *=(const vector<T, dim>& other) { for (std::size_t i = 0; i < dim; ++i) { data[i] *= other.data[i]; } return *this; }
            vector<T, dim>& operator /=(const vector<T, dim>& other) { for (std::size_t i = 0; i < dim; ++i) { data[i] /= other.data[i]; } return *this; }
            vector<T, dim>& operator *=(T scalar) { for (auto& val : data) { val *= scalar; } return *this; }
            vector<T, dim>& operator /=(T scalar) { for (auto& val : data) { val /= scalar; } return *this; }
            vector<T, dim> operator +(const vector<T, dim>& other) const { auto copy = *this; for (std::size_t i = 0; i < dim; ++i) { copy.data[i] += other.data[i]; } return copy; }
            vector<T, dim> operator -(const vector<T, dim>& other) const { auto copy = *this; for (std::size_t i = 0; i < dim; ++i) { copy.data[i] -= other.data[i]; } return copy; }
            vector<T, dim> operator *(const vector<T, dim>& other) const { auto copy = *this; for (std::size_t i = 0; i < dim; ++i) { copy.data[i] *= other.data[i]; } return copy; }
            vector<T, dim> operator /(const vector<T, dim>& other) const { auto copy = *this; for (std::size_t i = 0; i < dim; ++i) { copy.data[i] /= other.data[i]; } return copy; }
            vector<T, dim> operator *(T scalar) const { auto copy = *this; for (auto& val : copy.data) { val *= scalar; } return copy; }
            vector<T, dim> operator /(T scalar) const { auto copy = *this; for (auto& val : copy.data) { val /= scalar; } return copy; }
    };
}

template<typename T, std::size_t dim>
struct fmt::formatter<newt::lib::vector<T, dim>> {
    template<typename parse_context>
    constexpr auto parse(parse_context& ctx) { return ctx.begin(); }
    
    template<typename format_context>
    constexpr auto format(const newt::lib::vector<T, dim>& vec, format_context& ctx) {
        return vec.format(ctx);
    }
};