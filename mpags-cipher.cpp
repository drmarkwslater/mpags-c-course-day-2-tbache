// Standard Library includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Our project headers
#include "TransformChar.hpp"

// For std::isalpha and std::isupper
#include <cctype>

// Function to parse the command line arguments
bool processCommandLine(const std::vector<std::string>& cmdLineArgs, bool& helpRequested, bool& versionRequested, std::string& inputFile, std::string& outputFile) {
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

  // Process command line arguments and if the function returns false, exit program. Note this line both runs the function and checks the output.
  if(!processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile)) {return 1;}

  // Handle help, if requested
  if (helpRequested) {
    // Line splitting for readability
    std::cout
      << "Usage: mpags-cipher [-i <file>] [-o <file>]\n\n"
      << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
      << "Available options:\n\n"
      << "  -h|--help        Print this help message and exit\n\n"
      << "  --version        Print version information\n\n"
      << "  -i FILE          Read text to be processed from FILE\n"
      << "                   Stdin will be used if not supplied\n\n"
      << "  -o FILE          Write processed text to FILE\n"
      << "                   Stdout will be used if not supplied\n\n";
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


