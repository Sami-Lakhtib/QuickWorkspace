# QuickWorkspace

A tiny Command Line Interface tool meant to speed up the setup of workspace folders for different types of projects!

## Current commands:
-**create**: creates a simple file the name of which is passed as an argument.
Takes an optional "-t" flag for a test message inside the file.

-**new**: builds a workspace folder depending on the project type: "c, cpp, or c++" for C/C++ projects and "web" for web development projects.
Takes an optional -d flag to have some files filled with default content.

## Usage:
```bash
qws create -t file.txt
qws new -d project cpp
qws new project_2 web
```