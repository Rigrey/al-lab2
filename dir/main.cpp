#include "../include/CustomVector.h"

int main() {
    // Clearing output.txt file
    std::ofstream os("output.txt");
    os.close();

    // Reading input from input.txt file
    std::ifstream is("input.txt");
    if (!is.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }

    // Creating a vector object using the default constructor
    CustomVector vec1;

    // Creating a vector object based on data from input.txt
    size_t size;
    is >> size;
    int* arr = new int[size];
    for (size_t i = 0; i < size; ++i) {
        is >> arr[i];
    }
    CustomVector vec2(arr, size);

    customPrint("Outputting elements of the vector:\n");
    customPrint("Vector 1 (created using the default constructor): ");
    customPrint(vec1);
    customPrint("\n");
    customPrint("Vector 2 (created using data from input.txt): ");
    customPrint(vec2);
    customPrint("\n\n");

    customPrint("Filling vector 1 with data from the input.txt but data coming in Vector 1 directly:\n");
    is >> size;
    for (size_t i = 0; i < size; ++i) {
        is >> vec1;
    }
    is.close();
    customPrint(vec1);
    customPrint("\n\n");

    customPrint("Example of the prefix-decrement operation on Vector 2:\n");
    customPrint(--vec2);
    customPrint("\n\n");

    customPrint("Example of assignment operation with copying:\n"); 
    CustomVector vec3 = vec1;
    customPrint("Vector 3 (copied from Vector 1): ");
    customPrint(vec3);
    customPrint("\n\n");

    customPrint("Example of assignment operation with moving:\n"); 
    CustomVector vec4 = std::move(vec2);
    customPrint("Vector 4 (moved from Vector 2): ");
    customPrint(vec4);
    customPrint("\n");
    
    customPrint("Vector 2 after move: ");
    customPrint(vec2); // Vector 2 is now empty
    customPrint("\n");

    return 0;
}
