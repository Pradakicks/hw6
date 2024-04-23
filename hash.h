#ifndef HASH_H
#define HASH_H

#include <chrono>
#include <cmath>
#include <iostream>
#include <random>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
  HASH_INDEX_T rValues[5]{983132572, 1468777056, 552714139, 984953261,
                          261934300};
  MyStringHash(bool debug = true) {
    if (false == debug) {
      generateRValues();
    }
  }
  // hash function entry point (i.e. this is h(k))
  HASH_INDEX_T operator()(const std::string& k) const {
    // Check if this works

    size_t numOfSubStr = std::ceil(k.length() / 6.0);
    unsigned long long w[5];
    for (size_t i = 0; i < 5; i++) {
      w[i] = 0;
    }
    // std::cout << "Num of SubStrings: " << numOfSubStr << std::endl;

    for (size_t i = 1; i <= numOfSubStr; i++) {
      std::string currentString;
      std::string leadingZeroes = "";
      int letters = 6;
      if (i == numOfSubStr) {
        letters = k.length() % 6;
        if (letters == 0) {
          letters = 6;
        } else {
          for (int j = 0; j < 6 - letters; j++) {
            leadingZeroes.append("0");
          }
        }
        currentString = leadingZeroes + k.substr(0, letters);
      } else {
        currentString = k.substr(k.length() - (6 * i), 6);
      }

    //   std::cout << "Current String: " << currentString << std::endl;
      int currentPow = 1;
      for (int j = currentString.length() - 1; j >= 6 - letters; --j) {
        // std::cout << letterDigitToNumber(currentString[j]) << std::endl;
        w[5 - i] += letterDigitToNumber(currentString[j]) * currentPow;
        currentPow *= 36;
      }

    //   std::cout << "Conversion " << w[5 - i] << std::endl;
    }

    unsigned long long h =
        (rValues[0] * w[0] + rValues[1] * w[1] + rValues[2] * w[2] +
         rValues[3] * w[3] + rValues[4] * w[4]);
    return h;
  }

  // A likely helperValues function is to convert a-z,0-9 to an integral value
  // 0-35
  HASH_INDEX_T letterDigitToNumber(char letter) const {
    // Check if uppercase character
    if ('A' <= letter && letter <= 'Z') {
      letter = letter + 32;
    }

    if ('a' <= letter && letter <= 'z') {
      return letter - 97;
    }

    return letter + 26 - 48;  // This should only run if the char is a digit
  }

  // Code to generate the random R values
  void generateRValues() {
    // obtain a seed from the system clock:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(
        seed);  // mt19937 is a standard random number generator

    // Simply call generator() [it has an operator()] to get another random
    // number
    for (int i{0}; i < 5; ++i) {
      rValues[i] = generator();
    }
  }
};

#endif
