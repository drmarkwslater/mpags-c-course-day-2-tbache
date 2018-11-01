// File to contain Caesar Cipher function

#include "runCaesarCipher.hpp"
#include <iostream>
#include <vector>
#include <stdlib.h>  //strtoul()

// Function to run the Caesar Cipher
std::string runCaesarCipher(const std::string& inputText, const std::string key, const bool encrypt) {
  std::cout << "Your key is " << key << ". ";
  if (encrypt) {
    std::cout << "You want to encrypt." << std::endl;
  }
  else {
    std::cout << "You want to decrypt." << std::endl;
  }
  
  // Create the alphabet container and output string
  std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
  std::string outputText{""};

  // Convert key from string to unsigned long
  unsigned long new_key {stoul(key)};

  // Add typedef
  typedef std::vector<std::string>::size_type size_type;

  // Loop over characters in inputText
  for (size_type i {0}; i < inputText.length(); ++i) {
    
    // Find the corresponding position of the input character in the alphabet
    unsigned long posInAlphabet = alphabet.find(inputText[i]);
        
    // Use key to encrypt or decrypt
    if (encrypt) {
      outputText += alphabet[(posInAlphabet + new_key)%alphabet.length()];
    }
    else {
      outputText += alphabet[(posInAlphabet - (new_key - alphabet.length()))%alphabet.length()];
    }

  }

  return outputText;

}
