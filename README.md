# Server Report

server_report reads servers.txt and prints a report of the servers it
lists. The same program is written in six languages: C, C++, C#, Go,
Python, and TypeScript, and every one of them prints the same report.

This is the training repository of the Systems Programming Academy,
Volume 1, Chapter 12. Its history never changes, so every clone shows
the same commits, with the same ids, as the lessons.

## The Servers File

servers.txt holds one server per line in the form host|environment|port,
such as web-01|production|443. The report prints the title Server
Report, one line per server with its three fields separated by spaces,
and a last line, Servers:, with the number of servers.

## Files

- servers.txt: the list of servers that every program reads.
- c/server_report.c: the C program.
- cpp/server_report.cpp: the C++ program.
- csharp/ServerReport/: the C# project, Program.cs and
  ServerReport.csproj.
- go/: the Go module, main.go and go.mod.
- python/server_report.py: the Python program.
- typescript/: the TypeScript project, src/main.ts, tsconfig.json,
  package.json, and package-lock.json.
- .gitignore: the build outputs that Git never adds.

## Build and Run in Windows PowerShell

Run every command in the folder that holds this README. Each program
takes one argument, the path of the servers file. The builds turn every
warning into an error, so a build that warns stops.

C:

```powershell
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror .\c\server_report.c `
    -o .\c\server-report.exe
.\c\server-report.exe .\servers.txt
```

C++:

```powershell
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror .\cpp\server_report.cpp `
    -o .\cpp\server-report.exe
.\cpp\server-report.exe .\servers.txt
```

C#:

```powershell
dotnet build .\csharp\ServerReport --nologo --warnaserror
dotnet run --no-build --project .\csharp\ServerReport -- .\servers.txt
```

Go:

```powershell
go -C .\go build -o server-report.exe .
.\go\server-report.exe .\servers.txt
```

Python:

```powershell
py .\python\server_report.py .\servers.txt
```

TypeScript: npm ci installs the exact compiler versions that
package-lock.json records into typescript\node_modules. Run it once
after you clone.

```powershell
npm --prefix .\typescript ci --ignore-scripts --no-audit --no-fund
npm --prefix .\typescript run check
npm --prefix .\typescript run build
node .\typescript\dist\main.js .\servers.txt
```

## Build and Run in Linux or macOS

Use the same commands with / in place of \ in every path, \ in place of
` at the end of a continued line, and python3 in place of py. Programs
built on Linux or macOS have no .exe ending: build them with
-o ./c/server-report, -o ./cpp/server-report, and -o server-report for
Go, and run them as ./c/server-report ./servers.txt.

## License

The programs in this repository are printed in the Systems Programming
Academy lessons, so the course's MIT license for lesson code covers them:
https://github.com/VivoSomnio/systems-programming-academy/blob/main/LICENSE-CODE
