// FileParser.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <filesystem>
#include <future>
#include <queue>

namespace fs = std::filesystem;
#include "Program.h"
#include "FileParser.h"
#include "FileProcessor.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Hello FileParser." << endl;

  if (argc < 3)
  {
    std::cerr << "Usage: FileParser <inputdir> <outputfile>" << endl;
    return 1;
  }

  fs::path dirPath = argv[1];
  if (!fs::exists(dirPath)) 
  {
    std::cerr << "dir " << dirPath << " doesn't exist" << endl;
    return 0;
  }

  std::string outputFileName = argv[2];
  std::remove(outputFileName.c_str());

  FileProcessor fileProc(outputFileName);

  for (const auto& entry : fs::directory_iterator(dirPath)) 
  {
    if (entry.is_regular_file()) 
    {
      fileProc.AddFileToParse(entry.path());      
    }
  }

  fileProc.WaitForComplete();

	return 0;
}
