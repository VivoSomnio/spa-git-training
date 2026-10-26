// server_report prints the servers listed in a servers file, one line per
// server. Each line of the file is one record, host|environment|port, as
// in Lesson 3.13. The file's path is the program's one argument:
// .\go\server-report.exe .\servers.txt
// The report ends with a count line: Servers: and the number of servers.

// Remember, package main and func main make a program.
package main

// Remember, import names the packages this file uses: bufio reads a file
// one line at a time, fmt prints, os opens files and holds the flags, and
// strings splits text.
import (
    "bufio"
    "fmt"
    "os"
    "strings"
)

func main() {
    // Remember, the flags arrive as a list after the program name:
    // os.Args[0] is the program, so the one file path makes 2 entries.
    if len(os.Args) != 2 {
        fmt.Fprintln(os.Stderr, "Error: use server-report <servers file>")
        os.Exit(1)
    }
    path := os.Args[1]
    fmt.Println("Server Report")

    // Remember, os.Open opens for reading; check err != nil.
    file, err := os.Open(path)
    if err != nil {
        fmt.Fprintln(os.Stderr, "Error: could not read", path)
        os.Exit(1)
    }

    // Remember, one line at a time: Scan is false when no line is left,
    // and Text returns the line without its \n or \r\n. lineNumber counts
    // every line from 1, as an editor does.
    lineNumber := 0
    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        lineNumber = lineNumber + 1
        line := scanner.Text()

        // An empty line holds no server, so only other lines are printed.
        if line != "" {
            // Remember, split returns the pieces; check the field count
            // first. Fprintf names the stream, + at the end continues the
            // line, and os.Exit skips deferred calls, so the file is
            // closed before it.
            fields := strings.Split(line, "|")
            if len(fields) != 3 {
                fmt.Fprintf(os.Stderr, "Error: %s line %d: expected 3 "+
                    "fields: %s\n", path, lineNumber, line)
                file.Close()
                os.Exit(1)
            }
            fmt.Println(fields[0], fields[1], fields[2])
        }
    }

    // Remember, Err is not nil when a read failed.
    file.Close()
    if scanner.Err() != nil {
        fmt.Fprintln(os.Stderr, "Error: could not read", path)
        os.Exit(1)
    }

    // The report ends with the count: one line of the file per server.
    fmt.Println("Servers:", lineNumber)
}
