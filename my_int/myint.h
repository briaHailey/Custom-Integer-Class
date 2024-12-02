// Bria Weisblat/ Section: 2

#include <iostream>

class MyInt {

    //Addition operator overload
    friend MyInt operator+(const MyInt& x, const MyInt& y);

    //Subtraction operator overload
    friend MyInt operator-(const MyInt& x, const MyInt& y);

    //Multiplication operator overload
    friend MyInt operator*(const MyInt& x, const MyInt& y);

    //Less than (<) operator overload
    friend bool operator<(const MyInt& x, const MyInt& y);

    //Less than or equal to (<=) operator overload
    friend bool operator<=(const MyInt& x, const MyInt& y);

    //Greater than (>) operator overload
    friend bool operator>(const MyInt& x, const MyInt& y);

    //Greater than or equal to (>=) operator overload
    friend bool operator>=(const MyInt& x, const MyInt& y);

    //Equal to (==) operator overload
    friend bool operator==(const MyInt& x, const MyInt& y);

    //Not equal to (!=) operator overload
    friend bool operator!=(const MyInt& x, const MyInt& y);

    // Insertion operator (<<) overload
    friend std::ostream& operator<<(std::ostream& output, const MyInt& x);

    // Extraction operator (>>) overload
    friend std::istream& operator>>(std::istream& input, MyInt& x);

public:
    void TestFunction();

    //Default constructor
    MyInt(int n = 0);

    //Second constructor- accepts a string of characters
    MyInt(const char *arr);

    //Copy constructor
    MyInt(const MyInt& x);

    //Assignment operator (=)
    MyInt &operator=(const MyInt& y);

    //Pre-increment operator overload
    MyInt& operator++();

    //Post-increment operator overload
    MyInt operator++(int);

    //Destructor
    ~MyInt();

private:

    // Pointer for the dynamic array
    int * MyIntPtr;

    // Keep track of the amount of numbers in the array
    int arraySize;

    // Keeps track of the number of available slots in the array
    int numSpaces;

};

