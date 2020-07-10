#include <iostream>
#include <unordered_set>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream &stream, const std::unordered_set<T> set) {
    stream << "std::unordered_set{ ";
    for(const T &el : set) {
        stream << el << " ";
    }
    stream << "}\n";
    return stream;
}

template<typename T>
std::ostream& operator<<(std::ostream &stream, const std::vector<T> set) {
    stream << "std::vector{ ";
    for(const T &el : set) {
        stream << el << " ";
    }
    stream << "}\n";
    return stream;
}
template <typename T>
bool assertEq(const T& expected, const T& actual, const std::string &testName) {
    if(expected != actual) {
        std::cout << "Test  ERROR: " << testName <<  "\n"
                  << "-- Expected value: " << expected << "\n"
                  << "-- Actual value: " << actual << std::endl;
        return false;
    }
    std::cout << "Test OK: " << testName << std::endl;
    return true;
}

template <typename T>
bool assertEq(const std::vector<T>& expected, const std::vector<T>& actual, const std::string &testName) {
    if(expected.size() != actual.size()) {
        std::cout << "Test  ERROR: " << testName <<  "\n"
                  << "-- size of actual vector don't equal with size of expected vector" << std::endl;
    }
    for(auto eItr = expected.begin(), aItr = actual.begin(); eItr != expected.end(); ++eItr, ++aItr) {
        if(*eItr != *aItr) {
            std::cout << "Test  ERROR: " << testName <<  "\n"
                      << "-- Expected value: " << *eItr << "\n"
                      << "-- Actual value: " << *aItr << std::endl;
            return false;
        }
    }

    std::cout << "Test OK: " << testName << std::endl;
    return true;
}


