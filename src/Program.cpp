// FileParser.cpp : Defines the entry point for the application.
//
#include <filesystem>

#include "Program.h"
#include "FileParser.h"
#include "FileProcessor.h"

int main(int argc, char* argv[])
{
	std::cout << "Hello FileParser." << std::endl;

  if (argc < 3)
  {
    std::cerr << "Usage: FileParser <inputdir> <outputfile>" << std::endl;
    return 1;
  }

  std::filesystem::path dirPath = argv[1];

  if (!std::filesystem::exists(dirPath))
  {
    std::cerr << "dir " << dirPath << " doesn't exist" << std::endl;
    return 0;
  }

  std::string outputFileName = argv[2];
  std::remove(outputFileName.c_str());

  // This class is designed to be used from a single thread.
  FileProcessor fileProc(outputFileName);

  for (const auto& entry : std::filesystem::directory_iterator(dirPath))
  {
    if (entry.is_regular_file()) 
    {
      // This function starts a thread.
      // Since it's std::async it uses thread pool.
      fileProc.AddFileToParse(entry.path());      
    }
  }

  fileProc.WaitForComplete();

	return 0;
}
