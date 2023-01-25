#include <iostream>
#include <fstream>
#include <TString.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstring>
#include <cerrno>

// change the dirname here to set the output dir. 
std::string get_dirName() {
    std::string dirName = "/home/users/crowley/public_html/tttt/2023_01_24_analyze_bjets_stacked";
    return dirName;
}

// Function to check if a directory exists
bool directoryExists(const std::string& dirName_in)
{
    DIR *dir;
    bool exists = false;
    dir = opendir(dirName_in.data());

    if (dir)
    {
        exists = true;
        closedir(dir);
    }

    return exists;
}

void copyFile(const std::string& srcPath, const std::string& destPath) {
    // Open the source file
    FILE *srcFile = fopen(srcPath.data(), "rb");
    if (!srcFile)
    {
        std::cout << "Error opening source file: " << std::strerror(errno) << std::endl;
        return;
    }
    
    // Open the destination file
    FILE *destFile = fopen(destPath.data(), "wb");
    if (!destFile)
    {
        std::cout << "Error opening destination file: " << std::strerror(errno) << std::endl;
        fclose(srcFile);
        return;
    }
    
    // Copy the file contents
    char buffer[1024];
    size_t n;
    while ((n = fread(buffer, 1, 1024, srcFile)) > 0)
    {
        if (fwrite(buffer, 1, n, destFile) != n)
        {
            std::cout << "Error writing to destination file: " << std::strerror(errno) << std::endl;
            break;
        }
    }
    
    // Close the files
    fclose(srcFile);
    fclose(destFile);
}

// Function to copy a directory
void copyDirectory(const std::string& src, const std::string& dest) {
  // Create the destination directory
  if (mkdir(dest.data(), 0777) != 0) {
    throw std::runtime_error("Error creating directory: " + dest);
  }

  // Open the source directory
  DIR *dir = opendir(src.data());
  if (!dir) {
    throw std::runtime_error("Error opening directory: " + src);
  }

  // Loop through all the files in the source directory
  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    // Ignore the current and parent directories
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    std::string srcPath = src + "/" + entry->d_name;
    std::string destPath = dest + "/" + entry->d_name;

    // If the entry is a directory, recursively copy it
    if (entry->d_type == DT_DIR) {
      copyDirectory(srcPath, destPath);
    } else {
      // Otherwise, copy the file
      copyFile(srcPath, destPath);
    }
  }

  closedir(dir);
}


// Function to delete the contents of a directory
void clearDirectory(const std::string& dirName)
{
    // Open the directory
    DIR *dir = opendir(dirName.data());
    if (!dir)
    {
        std::cout << "Error opening directory: " << std::strerror(errno) << std::endl;
        return;
    }

    // Loop through all the files in the directory
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        // Ignore the current and parent directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        std::string path = dirName + "/" + entry->d_name;

        // If the entry is a directory, recursively delete its contents
        if (entry->d_type == DT_DIR)
        {
            clearDirectory(path);
            rmdir(path.data());
        }
        else
        {
            // Otherwise, delete the file
            remove(path.data());
        }
    }

    closedir(dir);
}


std::string directory_tools() {
    std::string dirName = get_dirName();
    //std::cout << "Using dirName " << dirName << endl;
    //std::cout << "Change dirName in directory_tools.C"  << endl;
    if (directoryExists(dirName))
    {
        // Find the next available backup directory name
        int i = 1;
        std::string backupDirName;
        do
        {
            backupDirName = dirName + "_backup_" + std::to_string(i++);
        } while (directoryExists(backupDirName));

        // Copy the directory to the backup location
        copyDirectory(dirName, backupDirName);

        // Clear the original directory
        clearDirectory(dirName);
    }
    else
    {
        // Create the directory
        mkdir(dirName.data(), 0777);
    }

    // for distribution on UAF
    copyFile("/home/users/crowley/public_html/index_plots.php", dirName + "/index.php");

    return dirName;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Error: No directory specified." << std::endl;
        return 1;
    }

    std::string dirName = argv[1];

    if (directoryExists(dirName))
    {
        // Find the next available backup directory name
        int i = 1;
        std::string backupDirName;
        do
        {
            backupDirName = dirName + "_backup_" + std::to_string(i++);
        } while (directoryExists(backupDirName));

        // Copy the directory to the backup location
        copyDirectory(dirName, backupDirName);

        // Clear the original directory
        clearDirectory(dirName);
    }
    else
    {
        // Create the directory
        mkdir(dirName.data(), 0777);
    }

    return 0;
}

