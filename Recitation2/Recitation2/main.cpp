//
//  main.cpp
//  Recitation2
//
//  Created by Student on 2/26/16.
//  Copyright © 2016 Ting-Che Lin. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

int sumDigits (int x){
    if (x/10 == 0) {
        return x%10;
    }
    return sumDigits(x/10) + x% 10;
}

int sumToN (int n){
    if (n == 1) {
        return n;
    }
    return sumToN(n-1) + n;
}

int fibonacci (int n){
    if (n == 1 || n == 0) {
        return n;
    }
    return fibonacci(n-1) + fibonacci(n-2);
}

int findLargest (vector<int> vec, int low, int high){
    if (low == high){
        
    }
    int center = (low + high)/2;
    int leftMax = findLargest(vec, low, center);
    int rightMax = findLargest(vec, center+1, high);
}

int findLargest ( vector<int> vec){
    return findLargest(vec, 0, vec.size());
}

int main(int argc, const char * argv[]) {
    // insert code here...

    std::cout << sumDigits(123) << std::endl;
    std::cout << sumToN(4) << std::endl;
    std::cout << fibonacci(6) << std::endl;
    return 0;
}
