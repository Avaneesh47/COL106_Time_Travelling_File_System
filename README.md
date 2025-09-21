# Time-Travelling File System
## Overview

This project implements a simplified file management system, with in-version memory control. The system manages versioned files with support for branching and historical inspection.

## System Architecture
- `FileManager` class for creating files and perform their related functions.
- `File` class which is the description of the `File` objects that we are managing.
- `HashMap` class has been implemented to store files according to their filenames, and to facilitate O(1) lookup times.
- `Heap` class for implementing efficient system-wide analytics, such as most recent or frequently edited files.

## Features
### 1. Versioned Files:
- Each `File` maintains a version tree, allowing tracking of changes over time.

### 2. Command Interface:
#### 2.1. Core File Operations: 
- `CREATE <filename>` :  Creates a file with a root version (ID 0), empty content, and an initial snapshot
message. Note that the root is marked as a snapshot.

- `READ <filename>` : Displays the content of the file’s currently active version.

- `INSERT <filename> <content>` : Appends content to the file. This creates a new version if the active
version is already a snapshot; otherwise, it modifies the active version in place. The content is appended in a space-seperated manner.

- `UPDATE <filename> <content>` : Replaces the file’s content. Follows the same versioning logic as
INSERT.

- `SNAPSHOT <filename> <message>` : Marks the active version as a snapshot, making its content immutable. It stores the provided message and the current time.

- `ROLLBACK <filename> [versionID]` : Sets the active version pointer to the specified versionID. If
no ID is provided, it rolls back to the parent of the current active version.

- `HISTORY <filename>` : Lists all snapshotted versions of the file chronologically, which lie on the path
from active node to the root in the file tree, showing their ID, timestamp, and message.

#### 2.2. System-Wide Analytics:
- `RECENT FILES [num]` : Lists files in descending order of their last modification time restricted to the
first num entries. If num is not provided, lists all files in descending order of their last modification time.

- `BIGGEST TREES [num]` : Lists files in descending order of their total version count restricted to the first
num entries. If num is not provided, lists all files in descending order of their total version count.

- `EXIT` : To cleanly exit the program.

### 3. Memory Safety:
- All dynamically allocated memory is freed systematically, preventing leaks.

## Directory Structure

```
project/
-   include/
    - File.hpp
    - FileManager.hpp
    - HashMap.hpp
    - Heap.hpp

-   src/
    - File.cpp
    - FileManager.cpp
    - HashMap.cpp
    - Heap.cpp
    - main.cpp

-   Makefile
-   README.md
```

## Build Instructions
### WSL/Linux
```
make        # compile
./program   # run
make clean  # remove objects and executable
```
### Windows (cmd.exe or Git Bash)
```
mingw32-make  # compile
.\program.exe # run
make clean    # remove objects and executable
```

## Command Usage Examples
- Input is given line by line, each line consisting of not more than one command.
```
CREATE myFile
File successfully created.

INSERT myFile Hello World
Created a new version (version ID 1) with appended content.

READ myFile
 Hello World

SNAPSHOT myFile Snap-1
Current version (version ID 1) snapshotted with given message.

UPDATE myFile Hello Earth
Created a new version (version ID 2) with updated content.

ROLLBACK myFile
Reverting to parent (version ID 1).

HISTORY myFile
ID: 1
Timestamp: Thu Sep 11 02:35:07 2025
Message:  Snap-1
ID: 0
Timestamp: Thu Sep 11 02:35:01 2025
Message: Root

RECENT_FILES 2
File Name: myFile1 | Last modified time: Thu Sep 11 02:45:36 2025
File Name: myFile2 | Last modified time: Thu Sep 11 02:35:46 2025

BIGGEST_TREES 3
File Name: myFile2 | Total versions: 7
File Name: myFile1 | Total versions: 5
File Name: myFile3 | Total versions: 2

EXIT
Exiting.
```

## Input Handling
- `CREATE` : Assumed that filename does not contain any spaces. Error is thrown if no filename is given or filename contains spaces. If the files already exists, error is thrown.

- `READ` : Same error handling as `CREATE`. If file does not exist, error is thrown.

- `INSERT` : Throws an error if any of the arguments `<filename>` and `<content>` is not given, or if given file does not exist.

- `UPDATE` : Same error handling as `INSERT`.

- `SNAPSHOT` : Throws error if file does not exist or if message is not provided.

- `ROLLBACK` : Throws an error if file does not exist. Throws error if `[versionID]` provided is not an integer or if the integer given does not correspond to a valid version. Reverts to parent if not provided with `[versionID]`.

- `HISTORY` : Throws error if file does not exist or if filename is not provided.

- `RECENT_FILES` : Throws error if num is not an integer or is negative. If num is greater than the number of files, outputs all files in descending order of modification time.

- `BIGGEST_TREES` : Throws error if num is not an integer or is negative. If num is greater than the number of files, outputs all files in descending order of total version count.

## Key Semantics
- **Immutability** : Only snapshotted versions are immutable. Non-snapshotted versions can be edited in place.
- **Versioning** : Version IDs are unique per file and are assigned sequentially, starting from 0. 

## Dependencies
- C++17 compatible compiler (`g++`)
- `Make` utility
- Works on both Windows and Linux systems/subsystems.

## Author
Avaneesh Kurade