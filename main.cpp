#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <filesystem>
#include <cstdint>
#include <regex>

std::vector<std::string> extensions = { ".avi", ".mkv", ".mp4", ".flv", ".webm", ".mov", ".wmv", ".mp4", ".m4v", ".mpeg" };
std::basic_regex reg("S\\d{1,2}E\\d{1,2}", std::regex::icase | std::regex::optimize);

bool IsMediaFile(const std::string& extension)
{
    for (std::size_t i = 0; i < extensions.size(); ++i)
    {
        if (extensions[i] == extension)
        {
            return true;
        }
    }

    return false;
}

void CheckDir(const std::string& path)
{
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path))
    {
        if (entry.is_directory())
        {
            CheckDir(entry.path().string());
        }
        else if (entry.is_regular_file())
        {
            std::filesystem::path p = entry.path();
            std::string extension = p.extension().string();
            
            if (IsMediaFile(extension))
            {
                std::string filename = p.filename().string();
                std::smatch match;

                if (std::regex_search(filename, match, reg) && match.size() == 1)
                {
                    std::filesystem::path newFilename = p;
                    newFilename.replace_filename(match[0].str() + extension);

                    std::filesystem::rename(p, newFilename);
                    std::printf("Renamed \"%s\" to \"%s\".\n", filename.c_str(), newFilename.filename().string().c_str());
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false); // just in case, this might not have an effect but whatever

    if (argc != 2)
    {
        std::puts("Correct usage: mfo <parent dir>");
        return EXIT_FAILURE;
    }

    std::string parentDir(argv[1]);

    if (!std::filesystem::is_directory(parentDir))
    {
        std::printf("\"%s\" is not a directory.\n", parentDir.c_str());
        return EXIT_FAILURE;
    }

    std::printf("Searching for media files in \"%s\"...\n", parentDir.c_str());
    CheckDir(parentDir);
    return EXIT_SUCCESS;
}