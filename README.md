# Media File Organiser

This tool simplifies media file names for organisation. Useful for preparing files for applications such as Plex Media Server.

For example: turns "Family.Guy.S20E01.AZMN.WEB-DL.x264.mkv" into "S20E01"

# Compile

Requires C++17 or above. Compiles on Windows, Linux, and (not tested) macOS.

Unix/MinGW example: ```g++ -std=c++17 main.cpp -o mfo```

Windows example: ```cl /EHsc /std:c++17 /MT /Fe:mfo main.cpp```

# Usage

To use, run `mfo <parent-dir>` where `<parent-dir>` is a directory containing media files similar to this:

```
Family Guy/
    Season 1/
        Family.Guy.S01E01.AZMN.WEB-DL.x264.mkv
        etc.
    Season 2/
        etc.
    etc.
```

MFO will go through all files in the folder (including sub-directories) and formats any media files found that contains a season & episode specifier.

WARNING: I'm not responsible for if the program incorrectly formats a file. If it does submit an issue and I'll do my best to fix it.