// Bria Weisblat/ Section: 2

#include "myint.h"
#include <iostream>
#include <cctype>

// Sourced from Bob Myer's course website at this link: https://www.cs.fsu.edu/~myers/cop3330/hw/hw05.html
// Converts a character into an integer (returns -1 for error)
int C2I(char c) {
    if (c < '0' || c > '9')	{
        return -1;
    }
    else {
        return (c - '0');
    }
}

//Default constructor
MyInt::MyInt(int n) {
    MyIntPtr = new int[5];
    numSpaces = 5;
    arraySize = 0;

    // If the number is negative
    if (n<=0){
        arraySize = 1;
        // Set the first and only value in the array to 0
        MyIntPtr[0] = 0;
    }
    else {
        int temp = n;
        int lastNumber = 0;

        // Find the length of the array
        while (temp >= 1){
            temp = temp/10;
            arraySize++;
            //If necessary, add more memory slots without having more than 5 blank spots at once
            if (arraySize >= numSpaces){
                int * tempPtr = new int[numSpaces + 5];
                // Perform a deep copy
                for (int j = 0; j < arraySize; j++) {
                    tempPtr[j] = MyIntPtr[j];
                }
                // Deallocate
                delete [] MyIntPtr;
                //Overwrite listPtr
                MyIntPtr = tempPtr;
                //Keep track of available space
                numSpaces += 5;
            }
        }

        //Reset temp
        temp = n;
        //Store the user input using the dynamic array
        for (int i = arraySize-1; i >= 0; i--){
            if (temp < 10){
                lastNumber = temp;
            }
            else {
                MyIntPtr[i] = temp % 10;
                temp = temp/10;
            }
        }
        MyIntPtr[0] = lastNumber;
    }
}

//Second constructor- accepts a string of characters
MyInt::MyInt(const char *arr) {
    MyIntPtr = new int[5];
    numSpaces = 5;
    arraySize = 0;
    bool isValid = true;

    int i = 0;
    do{
        //Store the int conversion of each character in the dynamic array
        MyIntPtr[i] = C2I(arr[i]);
        if (MyIntPtr[i] < 0){
            isValid = false;
        }
        else {
            i++;
            arraySize++;
            //If necessary, add more memory slots without having more than 5 blank spots at once
            if (arraySize >= numSpaces){
                int * tempPtr = new int[numSpaces + 5];
                // Perform a deep copy
                for (int j = 0; j < arraySize; j++) {
                    tempPtr[j] = MyIntPtr[j];
                }
                // Deallocate
                delete [] MyIntPtr;
                //Overwrite listPtr
                MyIntPtr = tempPtr;
                //Keep track of available space
                numSpaces += 5;
            }
        }
        // While the array character is valid
    } while ((arr[i] != '\0') && (isValid) );

    //If there was an invalid character, set the dynamic array to 0
    if (!isValid){
        for (int j = 0; j < arraySize; j++){
            MyIntPtr[j] = 0;
        }
        arraySize = 1;
    }
}

//Copy constructor
MyInt::MyInt(const MyInt &x) {
    MyIntPtr = new int [x.arraySize];
    for (int i = 0; i < x.arraySize; i++)
        MyIntPtr[i] = x.MyIntPtr[i];
    arraySize = x.arraySize;
    numSpaces = x.numSpaces;
}

MyInt &MyInt::operator=(const MyInt &y) {
    if (this != &y) {
        //Delete the target of the pointer
        delete [] MyIntPtr;
        //Resize the dynamically allocated array so that it can properly fit what is being copied
        MyIntPtr = new int[y.numSpaces];
        //Perform a deep copy
        for (int i = 0; i < y.arraySize; i++) {
            MyIntPtr[i] = y.MyIntPtr[i];
        }
        arraySize = y.arraySize;
        numSpaces = y.numSpaces;
    }
    return *this;
}

//Pre-increment operator overload
MyInt &MyInt::operator++() {
    *this = *this + 1;
    return *this;
}

//Post-increment operator overload
MyInt MyInt::operator++(int){
    const MyInt temp = *this;
    *this = *this + 1;
    return temp;
}

//Addition operator (+) overload
MyInt operator+(const MyInt &x, const MyInt &y) {
    // Create empty int (5 spaces, 0 spots filled)
    MyInt sum;
    int temp;
    int bigger;
    int smaller;
    //Determine which number has more digits
    if (x.arraySize > y.arraySize){
        bigger = x.arraySize;
        smaller = y.arraySize;
    }
    else{
        bigger = y.arraySize;
        smaller = x.arraySize;
    }

    //Delete the target of the pointer
    delete[] sum.MyIntPtr;
    //Resize the dynamically allocated array so that it can properly fit the max digits in the sum
    sum.MyIntPtr = new int[bigger+5];
    // Adjust variables
    sum.numSpaces = bigger+5;
    sum.arraySize = bigger+1;
    bool addExtra = false;
    // Set the entire sum MyInt to 0 before assigning
    for (int i = 0; i < sum.numSpaces; i++) {
        sum.MyIntPtr[i] = 0;
    }
    //For the number of digits in the smaller number
    for (int i = 0; i < smaller; i++){
        int tempX = x.MyIntPtr[x.arraySize -i -1];
        int tempY = y.MyIntPtr[y.arraySize -i -1];
        temp = tempX + tempY;
        //If the addition of digits does not carry over
        if (temp + sum.MyIntPtr[sum.arraySize -i -1] <= 9){
            sum.MyIntPtr[sum.arraySize -i -1] += temp;
        }
        //If the addition of digits carries over
        else{
            //Assign the second digit of the sum of the digits
            sum.MyIntPtr[sum.arraySize -i -1] += temp-10;
            if (sum.arraySize -i -2 < 0) {
                addExtra = true;
            } else {
                sum.MyIntPtr[sum.arraySize -i -2] += 1;
            }
        }
    }
    //For the remaining digits not accounted for by "smaller"
    for (int i = 0; i < bigger - smaller; i++) {
        if (smaller == y.arraySize) {
            int tempX = x.MyIntPtr[x.arraySize -i -smaller-1];
            if (tempX + sum.MyIntPtr[sum.arraySize -i -smaller-1] > 9) {
                sum.MyIntPtr[sum.arraySize -i -smaller-2] +=  1;
                sum.MyIntPtr[sum.arraySize -i -smaller-1] +=  tempX -10;
                // If you need to carry over
                if (i == (bigger - smaller -1)) {
                    addExtra = true;
                }
            }
            //Assign the correct sum digit when the sum does not require carrying over
            else {
                sum.MyIntPtr[sum.arraySize -i -smaller-1] +=  tempX;
            }
        }
        else {
            int tempY = y.MyIntPtr[y.arraySize -i -smaller-1];
            if (tempY + sum.MyIntPtr[sum.arraySize -i -smaller-1] > 9) {
                sum.MyIntPtr[sum.arraySize -i -smaller-2] +=  1;
                sum.MyIntPtr[sum.arraySize -i -smaller-1] +=  tempY -10;
                // If you need to carry over
                if (i == (bigger - smaller -1)) {
                    addExtra = true;
                }
                //Assign the correct sum digit when the sum does not require carrying over
            } else {
                sum.MyIntPtr[sum.arraySize -i -smaller-1] +=  tempY;
            }
        }
    }

    //Account for carrying over
    if (addExtra) {
        sum.MyIntPtr[0] = 1;
    } else if (sum.MyIntPtr[0] == 0){
        // Shift one left
        int hold = sum.MyIntPtr[sum.arraySize-2];
        for (int i = 0; i < sum.arraySize-1; i++) {
            sum.MyIntPtr[i] = sum.MyIntPtr[i+1];
        }
        sum.MyIntPtr[sum.arraySize-1] = 0;
        sum.MyIntPtr[sum.arraySize-3] = hold;
        sum.arraySize--;
    }
    return sum;
}


MyInt operator-(const MyInt &x, const MyInt &y) {
    MyInt difference;

    if (y >= x){
        difference = 0;
    }
    else {
        //Delete the target of the pointer
        delete [] difference.MyIntPtr;
        //Resize the dynamically allocated array so that it can properly fit the max digits in the sum
        difference.MyIntPtr = new int[x.arraySize+5];
        // Adjust variables
        difference.numSpaces = x.arraySize + 5;
        difference.arraySize = x.arraySize + 1;
        // Set the entire sum MyInt to 0 before assigning
        for (int i = 0; i <difference.numSpaces; i++) {
            difference.MyIntPtr[i] = 0;
        }
        //For the number of digits in the smaller number
        for (int i = 0; i < y.arraySize; i++){
            int tempX = x.MyIntPtr[x.arraySize -i -1];
            int tempY = y.MyIntPtr[y.arraySize -i -1];
            int temp;
            temp = tempX - tempY;
            //If the subtraction of the digits results in a negative number
            if (temp < 0){
                difference.MyIntPtr[difference.arraySize -i -1] += temp + 10;
                difference.MyIntPtr[difference.arraySize -i -2] -= 1;
            }
            else{
                //Assign the second digit of the sum of the digits
                difference.MyIntPtr[difference.arraySize -i -1] += temp;
                if (difference.MyIntPtr[difference.arraySize -i -1] < 0) {
                    difference.MyIntPtr[difference.arraySize -i -1] = 9;
                    difference.MyIntPtr[difference.arraySize -i -2] = -1;
                }
            }
        }

        for (int i = 0; i < x.arraySize - y.arraySize; i++) {
            int tempX = x.MyIntPtr[x.arraySize -i -y.arraySize-1];
            difference.MyIntPtr[difference.arraySize -i -y.arraySize -1] += tempX;
            if (difference.MyIntPtr[difference.arraySize -i -1] < 0) {
                difference.MyIntPtr[difference.arraySize -i -1] = 9;
                if (difference.arraySize -i -2 <= 1) {
                    difference.MyIntPtr[difference.arraySize -i -2] = 0;
                } else {
                    difference.MyIntPtr[difference.arraySize -i -2] = -1;
                }
            }
        }
        while (difference.MyIntPtr[0] == 0){
            //Overwrite any leading zeros
            for (int i = 0; i < difference.arraySize; i++){
                difference.MyIntPtr[i] = difference.MyIntPtr[i+1];
            }
            difference.arraySize--;
        }
    }
    return difference;
}


// Multiplication operator (*) overload
MyInt operator*(const MyInt& x, const MyInt& y) {
    //Account for multiplication by 0
    if ( (x == 0) || (y == 0) ){
        return 0;
    }

    MyInt temporaryX = x;
    MyInt temporaryY = y;

    // Find the smaller MyInt and assign a POINTER to it
    MyInt *small;
    MyInt *large;
    // Compare lengths and assign pointers to the numbers depending on how many digits they have comparatively
    if (x.arraySize < y.arraySize) {
        small = &temporaryX;
        large = &temporaryY;
    }
    if (x.arraySize > y.arraySize) {
        large = &temporaryX;
        small = &temporaryY;
    }
    if (x.arraySize == y.arraySize) {
        small = &temporaryX;
        large = &temporaryY;
    }
    // Assign values for the numbers with more and fewer digits
    int smallerSize = small->arraySize;
    int largerSize = large->arraySize;

    //Create a MyInt object for the product
    MyInt myIntProduct;
    delete [] myIntProduct.MyIntPtr;
    myIntProduct.MyIntPtr = new int [smallerSize+largerSize+5];
    myIntProduct.numSpaces = smallerSize+largerSize+5;
    myIntProduct.arraySize = smallerSize+largerSize;
    // Allows us to use the plus-equals sign later on
    for (int i = 0; i < myIntProduct.arraySize; i++) {
        myIntProduct.MyIntPtr[i] = 0;
    }

    for (int i = 0; i < smallerSize; i++) {
        // Find the current digit of the smaller number
        int tempSmaller = small->MyIntPtr[smallerSize-1-i];
        // Create a temporary sum object
        MyInt myIntTemp1;
        delete [] myIntTemp1.MyIntPtr;
        myIntTemp1.MyIntPtr = new int [largerSize+5+i];
        myIntTemp1.numSpaces = largerSize+5+i;
        myIntTemp1.arraySize = largerSize+1+i;
        // Allows us to use the plus-equals sign later on
        for (int k = 0; k < myIntTemp1.arraySize; k++) {
            myIntTemp1.MyIntPtr[k] = 0;
        }

        for (int j = 0; j < largerSize; j++) {
            // Find the current digit of the larger number here
            int tempLarger = large->MyIntPtr[largerSize - 1 - j];
            // Multiply the numbers
            int intTempProd = tempSmaller * tempLarger;
            // Add the ones place of the product to the current position
            myIntTemp1.MyIntPtr[myIntTemp1.arraySize - 1 - i - j] += intTempProd % 10;
            if (myIntTemp1.MyIntPtr[myIntTemp1.arraySize - 1 - i - j] >= 10) {
                myIntTemp1.MyIntPtr[myIntTemp1.arraySize - 1 - i - j] -= 10;
                myIntTemp1.MyIntPtr[myIntTemp1.arraySize - 2 - i - j] += 1;
            }
            // Divide by ten
            intTempProd /= 10;
            // Add it to the next place over
            myIntTemp1.MyIntPtr[myIntTemp1.arraySize - 2 - i - j] += intTempProd;
        }
        myIntProduct = myIntProduct + myIntTemp1;
    }
    //Make sure there are no leading zeros
    while (myIntProduct.MyIntPtr[0] == 0){
        //Overwrite any leading zeros
        for (int i = 0; i < myIntProduct.arraySize; i++){
            myIntProduct.MyIntPtr[i] = myIntProduct.MyIntPtr[i+1];
        }
        myIntProduct.arraySize--;
    }
    return myIntProduct;
}

//Less than (<) operator overload
bool operator<(const MyInt &x, const MyInt &y) {
    bool isLess = false;

    //If the first MyInt has fewer digits than the second MyInt
    if (x.arraySize < y.arraySize){
        return true;
    }

    //If the first MyInt has more digits than the second MyInt or they contain the exact same number
    else if (x.arraySize > y.arraySize || x == y) {
        return false;
    }
    int i =0;
    //Find a digit that is different between the two MyInts
    while (x.MyIntPtr[i] == y.MyIntPtr[i]) {
        i++;
    }
    //If the differing digit of the first MyInt is greater than the differing digit of the second MyInt
    if (x.MyIntPtr[i] > y.MyIntPtr[i]){
        isLess = false;
    }
    else {
        isLess = true;
    }
    return isLess;
}

//Less than or equal to (<=) operator overload
bool operator<=(const MyInt &x, const MyInt &y) {
    bool isLessEqual;
    if ( (x < y) || (x==y)){
        isLessEqual = true;
    }
    else{
        isLessEqual = false;
    }
    return isLessEqual;
}

//Greater than (>) operator overload
bool operator>(const MyInt &x, const MyInt &y) {
    bool isGreater;
    if ((x<y) || (x==y)){
        isGreater=false;
    }
    else{
        isGreater=true;
    }
    return isGreater;
}

//Greater than or equal to (>=) operator overload
bool operator>=(const MyInt &x, const MyInt &y) {
   bool isGreaterEqual;
   if ( (x>y) || (x==y)){
       isGreaterEqual = true;
   }
   else{
       isGreaterEqual = false;
   }
   return isGreaterEqual;
}

//Equal to (==) operator overload
bool operator==(const MyInt &x, const MyInt &y) {
    bool isEqual = true;
    int i =0;
    do {
        if (x.MyIntPtr[i] != y.MyIntPtr[i]) {
            isEqual = false;
        }
        i++;
    } while ( (isEqual) && ((i < x.arraySize) || (i < y.arraySize)) );

    return isEqual;
}

//Not equal to (!=) operator overload
bool operator!=(const MyInt &x, const MyInt &y) {
    bool isNotEqual = false;
    if (!(x == y)) {
        isNotEqual = true;
    }
    return isNotEqual;
}

// Insertion operator (<<) overload
std::ostream &operator<<(std::ostream &output, const MyInt &x) {
    for (int i = 0; i < x.arraySize; i++){
        output << x.MyIntPtr[i];
    }
    return output;
}

//Extraction operator (>>) overload
std::istream &operator>>(std::istream &input, MyInt &x){

    // Delete array
    delete [] x.MyIntPtr;
    x.MyIntPtr = new int [5];
    x.arraySize = 0;
    x.numSpaces = 5;

    int i = 0;

    while (isspace(input.peek())) {
        input.ignore(1);
    }

    while (isdigit(input.peek())) {
        // Resize if needed
        if (x.arraySize + 1 == x.numSpaces){
               int *temp = new int[x.numSpaces+5];
               for (int j = 0; j < x.arraySize; j++){
                   temp[j] = x.MyIntPtr[j];
               }
               char tempChar;
               std::cin.get(tempChar);
               int tempInt = C2I(tempChar);
               temp[x.arraySize] = tempInt;
               delete [] x.MyIntPtr;
               x.MyIntPtr = temp;
               x.arraySize = x.arraySize+1;
               x.numSpaces = x.numSpaces+5;
        } else {
            char tempChar;
            std::cin.get(tempChar);
            int tempInt = C2I(tempChar);
            x.MyIntPtr[i] = tempInt;
            x.arraySize++;
        }
        i++;

    }
    return input;
}

//Destructor
MyInt::~MyInt() {
    delete [] MyIntPtr;
}
