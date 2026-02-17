#ifndef TEMPLATECLASS_H
#define TEMPLATECLASS_H

#include <vector>
#include <algorithm>

template<typename T>
class DynamicArray {

    private:

        std::vector<T> data_;

    public:

        DynamicArray() = default;
        ~DynamicArray() = default;
        DynamicArray(const DynamicArray& other) : data_(other.data_) {}
        DynamicArray(DynamicArray&& other) noexcept : data_(std::move(other.data_)) {}
        DynamicArray<T>(const std::vector<T>& vec) : data_(vec) {};

        T& operator[](size_t i)       { return data_[i]; }
        const T& operator[](size_t i) const { return data_[i]; }

        auto begin()       { return data_.begin(); }
        auto end()         { return data_.end(); }
        auto begin() const { return data_.begin(); }
        auto end()   const { return data_.end(); }

        size_t size() const { return data_.size(); }
};

class DynamicArrayFactory {

    public:
    template< typename T>
    DynamicArray<T> createArray(const std::vector<T>& vec) {
        std::vector<T> result;
        for (size_t i = 0; i < vec.size(); ++i)
            result.push_back(vec[i] + static_cast<T>(i + 1));
        DynamicArray<T> arr(result);
        return arr;
    }
};

#endif