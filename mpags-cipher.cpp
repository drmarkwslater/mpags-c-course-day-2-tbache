// Standard Library includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Our project headers
#include "TransformChar.hpp"
#include "runCaesarCipher.hpp"
#include "processCommandLine.hpp"

// For std::isalpha and std::isupper
#include <cctype>

// Main function of the mpags-cipher program
int main(int argc, char* argv[])
{
  // Convert the command-line arguments into a more easily usable form
  const std::vector<std::string> cmdLineArgs {argv, argv+argc};

  // Options that might be set by the command-line arguments (these can be changed when the processCommandLine function is run.
  bool helpRequested {false};
  bool versionRequested {false};
  std::string inputFile {""};
  std::string outputFile {""};
  std::string key {""};
  bool encrypt {true}; // Encrypt by default

  // Process command line arguments and if the function returns false, exit program. Note this line both runs the function and checks the output.
  if(!processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile, key, encrypt)) {return 1;}

  // Handle help, if requested
  if (helpRequested) {
    // Line splitting for readability
    std::cout
      << "Usage: mpags-cipher [-i <file>] [-o <file>] [--key <key>] [--encrypt <true or false>]\n\n"
      << "Encrypts/Decrypts input alphanumeric text using the Caesar cipher\n\n"
      << "Available options:\n\n"
      << "  -h|--help        Print this help message and exit\n\n"
      << "  --version        Print version information\n\n"
      << "  -i FILE          Read text to be processed from FILE\n"
      << "                   Stdin will be used if not supplied\n\n"
      << "  -o FILE          Write processed text to FILE\n"
      << "                   Stdout will be used if not supplied\n\n"
      << "  --key KEY        Use KEY as the key in the Caesar cipher\n\n"
      << "  --encrypt TRUE or FALSE     Enter whether to encrypt or decrypt\n\n";
    // Help requires no further action, so return from main
    // with 0 used to indicate success
    return 0;
  }

  // Handle version, if requested
  // Like help, requires no further action,
  // so return from main with zero to indicate success
  if (versionRequested) {
    std::cout << "0.1.0" << std::endl;
    return 0;
  }

  // Initialise variables for processing input text
  char inputChar {'x'};
  std::string inputText {""};

  // Check file was read correctly, if not use keyboard input. 
  std::ifstream in_file{inputFile};
  if (!in_file.good()) {
    std::cout<<"File not read. Using keyboard input instead."<<std::endl;
    while(std::cin >> inputChar) {
      inputText += transformChar(inputChar);
      
    }
  }
  else {
    std::cout << "File read correctly." << std::endl;
    while(in_file >> inputChar) {
      inputText += transformChar(inputChar);
    }
  }

  std::string outputText {runCaesarCipher(inputText, key, encrypt)};

  // Output to terminal
  std::cout << "Your input was " << inputText << std::endl;
  std::cout << "Your output is " << outputText <<std::endl;
  
  // Output to file (but first check file is open)
  std::ofstream out_file{"outputFile.txt"};
  if (!out_file.good()) {return 0;}
  out_file << outputText << std::endl;

  // No requirement to return from main, but we do so for clarity
  // and for consistency with other functions
  return 0;
}


