#ifndef CUSTOMVECTOR_H
#define CUSTOMVECTOR_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>

class CustomVector {
private:
    bool* arr;
    size_t size;
    size_t capacity;

    size_t closestPowerOfTwo(size_t num) const;
    void resize(size_t newCapacity);
public:
    CustomVector();
    CustomVector(bool* bool_arr, size_t& vec_size);
    CustomVector(const CustomVector& copied_vec);
    CustomVector(CustomVector&& moved_vec) noexcept;
    ~CustomVector();

    bool operator[](size_t index) const;
    friend CustomVector operator^(const CustomVector& vec1, const CustomVector& vec2);

    friend std::ostream& operator<<(std::ostream& os, const CustomVector& vec);
    friend std::istream& operator>>(std::istream& is, CustomVector& vec);

    void push_back(const bool& value);
};

CustomVector::CustomVector() : arr(new bool[1]), size(0), capacity(1) {}

CustomVector::CustomVector(bool* bool_arr, size_t& vec_size) : arr(bool_arr), size(vec_size), capacity(closestPowerOfTwo(vec_size)) {}

CustomVector::CustomVector(const CustomVector& other) : arr(new bool[other.capacity]), size(other.size), capacity(other.capacity) {
    for (size_t i = 0; i < other.size; ++i) {
        arr[i] = other.arr[i];
    }
}

CustomVector::CustomVector(CustomVector&& moved_vec) noexcept : arr(moved_vec.arr), size(moved_vec.size), capacity(moved_vec.capacity) {
    moved_vec.arr = nullptr;
    moved_vec.arr = new bool[1];
    moved_vec.size = 0;
    moved_vec.capacity = 0;
}

CustomVector::~CustomVector() {
    delete[] arr;
}

bool CustomVector::operator[](size_t index) const {
    return arr[index];
}

CustomVector operator^(const CustomVector& vec1, const CustomVector& vec2) {
    if (vec1.size != vec2.size) {
        std::cerr << "Error: Vectors of different lengths!" << std::endl;
        return CustomVector();
    }
    CustomVector res;
    for (size_t i = 0; i < vec1.size; ++i) {
        res.push_back(vec1.arr[i] ^ vec2.arr[i]);
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, const CustomVector& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size; ++i) {
        os << vec.arr[i] << " ";
    }
    os << "]";
    return os;
}

std::istream& operator>>(std::istream& is, CustomVector& vec) {
    bool value;
    is >> value;
    vec.push_back(value);
    return is;
}

void CustomVector::push_back(const bool& value) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    arr[size++] = value;
}

void CustomVector::resize(size_t newCapacity) {
    bool* new_arr = new bool[newCapacity];
    for (size_t i = 0; i < size; ++i) {
        new_arr[i] = arr[i];
    }
    delete[] arr;
    arr = new_arr;
    capacity = newCapacity;
}

size_t CustomVector::closestPowerOfTwo(size_t num) const {
    if (num == 0 || num == 1) {
        return 1;
    }
    size_t power = std::ceil(std::log2(num));
    return std::pow(2, power);
}

void customPrint(const std::string& str) {
    std::ofstream os("output.txt",std::ios::app);
    os << str;
    std::cout << str;
    os.close();
}

void customPrint(const CustomVector &vec) {
    std::ofstream os("output.txt",std::ios::app);
    os << vec;
    std::cout << vec;
    os.close();
}

#endif // CUSTOMVECTOR_H
