// Standard Library includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Our project headers
#include "TransformChar.hpp"
#include "runCaesarCipher.hpp"

// For std::isalpha and std::isupper
#include <cctype>

// To do
// Key is currently a string, is this correct? Use function to convert to int?
// Key or Encrypt not constant atm.

// Function to parse the command line arguments
bool processCommandLine(const std::vector<std::string>& cmdLineArgs, bool& helpRequested, bool& versionRequested, std::string& inputFile, std::string& outputFile, std::string& key, bool& encrypt) {
  // Add a typedef that assigns another name for the given type for clarity
  // Will cover typedefs more later on
  typedef std::vector<std::string>::size_type size_type;
  const size_type nCmdLineArgs {cmdLineArgs.size()};

  // Process command line arguments - ignore zeroth element, as we know this to be the program name and don't need to worry about it. Note the type of i.
  for (size_type i {1}; i < nCmdLineArgs; ++i) {

    if (cmdLineArgs[i] == "-h" || cmdLineArgs[i] == "--help") {
      helpRequested = true;
    }
    else if (cmdLineArgs[i] == "--version") {
      versionRequested = true;
    }
    else if (cmdLineArgs[i] == "-i") {
      // Handle input file option
      // Next element is filename unless -i is the last argument
      if (i == nCmdLineArgs-1) {
	std::cerr << "[error] -i requires a filename argument" << std::endl;
	// exit main with non-zero return to indicate failure
	return false;
      }
      else {
	// Got filename, so assign value and advance past it
	inputFile = cmdLineArgs[i+1];
	++i;
      }
    }
    else if (cmdLineArgs[i] == "-o") {
      // Handle output file option
      // Next element is filename unless -o is the last argument
      if (i == nCmdLineArgs-1) {
	std::cerr << "[error] -o requires a filename argument" << std::endl;
	// exit main with non-zero return to indicate failure
	return false;
      }
      else {
	// Got filename, so assign value and advance past it
	outputFile = cmdLineArgs[i+1];
	++i;
      }
    }
    else if (cmdLineArgs[i] == "--key") {
      // Handle key
      // Next element is the key unless --key is the last argument
      if (i == nCmdLineArgs-1) {
	std::cerr << "[error] --key requires a key argument" << std::endl;
	// exit main with non-zero return to indicate failure
	return false;
      }
      else {
	// Got key, so assign value and advance past it
	key = cmdLineArgs[i+1];
	++i;
      }
    }
    else if (cmdLineArgs[i] == "--encrypt") {
      // Handle encrypt
      // Next element states whether to encrypt (1) or decrypt (0)
      if (i == nCmdLineArgs-1) {
	std::cerr << "[error] --encrypt requires a boolean argument" << std::endl;
	// exit main with non-zero return to indicate failure
	return false;
      }
      else {
	// Got boolean, so assign value and advance past it
	if (cmdLineArgs[i+1] == "true") {
	  // User wants to encrypt
	  encrypt = true;
	}
	else if (cmdLineArgs[i+1] == "false") {
	  // User wants to decrypt
	  encrypt = false;
	}
	++i;
      }
    }    
    else {
      // Have an unknown flag to output error message and return non-zero
      // exit status to indicate failure
      std::cerr << "[error] unknown argument '" << cmdLineArgs[i] << "'\n";
      return false;
    }
  }

  return true;
}

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
      //inputText += transformChar(inputChar);
      runCaesarCipher(key, encrypt);
    }
  }
  else {
    std::cout << "File read correctly." << std::endl;
    while(in_file >> inputChar) {
      //inputText += transformChar(inputChar);
      runCaesarCipher(key, encrypt);
    }
  }

  // Read in user input from stdin/file
  //if (!inputFile.empty()) {
  //while(std::cin >> inputChar) {
  //  inputText += transformChar(inputChar);
  //}
  //}
  //  else {
  //while(in_file >> inputChar) {
  //  inputText += transformChar(inputChar);
  //}
  //  }

  // Check file was read correctly
  //std::ifstream in_file{inputFile};
  //if (!in_file.good()) {std::cout<<"File not read."<<std::endl;return 1;}
  
  // Loop over each character from user input
  // (until Return then CTRL-D (EOF) pressed)
  //  while(std::cin >> inputChar)
  // if (!inputFile.empty())
  
  
  // Output to terminal
  std::cout << inputText << std::endl;
  // Output to file (but first check file is open)
  std::ofstream out_file{"outputFile.txt"};
  if (!out_file.good()) {return 0;}
  out_file << inputText << std::endl;

  // No requirement to return from main, but we do so for clarity
  // and for consistency with other functions
  return 0;
}


