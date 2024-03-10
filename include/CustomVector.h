#ifndef CUSTOMVECTOR_H
#define CUSTOMVECTOR_H

#include <cmath>
#include <fstream>
#include <iostream>

class CustomVector {
private:
    int* arr;
    size_t size;
    size_t capacity;

    size_t closestPowerOfTwo(size_t num) const;
    void resize(size_t newCapacity);
public:
    CustomVector();
    CustomVector(int* int_arr, size_t& vec_size);
    CustomVector(const CustomVector& copied_vec);
    CustomVector(CustomVector&& moved_vec) noexcept;
    ~CustomVector();

    int operator[](size_t index) const;
    CustomVector& operator--();

    friend std::ostream& operator<<(std::ostream& os, const CustomVector& vec);
    friend std::istream& operator>>(std::istream& is, CustomVector& vec);

    void push_back(const int& value);
};

CustomVector::CustomVector() : arr(new int[1]), size(0), capacity(1) {}

CustomVector::CustomVector(int* int_arr, size_t& vec_size) : arr(int_arr), size(vec_size), capacity(closestPowerOfTwo(vec_size)) {}

CustomVector::CustomVector(const CustomVector& other) : arr(new int[other.capacity]), size(other.size), capacity(other.capacity) {
    for (size_t i = 0; i < other.size; ++i) {
        arr[i] = other.arr[i];
    }
}

CustomVector::CustomVector(CustomVector&& moved_vec) noexcept : arr(moved_vec.arr), size(moved_vec.size), capacity(moved_vec.capacity) {
    moved_vec.arr = nullptr;
    moved_vec.size = 0;
    moved_vec.capacity = 0;
}

CustomVector::~CustomVector() {
    delete[] arr;
}

int CustomVector::operator[](size_t index) const {
    return arr[index];
}

CustomVector& CustomVector::operator--() {
    for (size_t i = 0; i < size; ++i) {
        --arr[i];
    }
    return *this;
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
    int value;
    is >> value;
    vec.push_back(value);
    return is;
}

void CustomVector::push_back(const int& value) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    arr[size++] = value;
}

void CustomVector::resize(size_t newCapacity) {
    int* new_arr = new int[newCapacity];
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
