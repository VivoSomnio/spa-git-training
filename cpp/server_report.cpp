// server_report prints the servers listed in a servers file, one line per
// server. Each line of the file is one record, host|environment|port, as
// in Lesson 3.13. The file's path is the program's one argument:
// .\cpp\server-report.exe .\servers.txt
// The report ends with a count line: Servers: and the number of servers.

// Remember, #include adds the declarations: fstream for files, iostream
// for printing, string for text, and vector for the list of fields.
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Splits sourceText at every separator and returns the parts in order.
// Remember, split returns the pieces: find(separator, start) searches from
// start, and substr cuts one part out, as in Lesson 3.13.
std::vector<std::string> splitText(const std::string &sourceText,
                                   char separator) {
    std::vector<std::string> parts;
    std::size_t start = 0;
    std::size_t found = sourceText.find(separator);
    while (found != std::string::npos) {
        parts.push_back(sourceText.substr(start, found - start));
        start = found + 1;
        found = sourceText.find(separator, start);
    }
    parts.push_back(sourceText.substr(start));
    return parts;
}

// Remember, main starts the program; 0 = success, 1 = failure.
int main(int argc, char *argv[]) {
    // Remember, the flags arrive as a list after the program name, so the
    // one file path makes argc 2.
    if (argc < 2) {
        std::cerr << "Error: use server-report <servers file>\n";
        return 1;
    }
    const std::string path = argv[1];
    std::cout << "Server Report\n";

    // Remember, is_open is false when the file could not be opened; the
    // ifstream closes the file itself when main ends.
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: could not read " << path << '\n';
        return 1;
    }

    // Remember, one line at a time: std::getline reads one line without
    // its \n, and the loop ends when no line is left. lineNumber counts
    // every line from 1, as an editor does.
    int lineNumber = 0;
    std::string line;
    while (std::getline(file, line)) {
        lineNumber = lineNumber + 1;

        // Remember, remove the \r first; npos keeps the whole line.
        line = line.substr(0, line.find('\r'));

        // An empty line holds no server, so only other lines are printed.
        if (line != "") {
            // Remember, check the field count first.
            const std::vector<std::string> fields = splitText(line, '|');
            if (fields.size() != 3) {
                std::cerr << "Error: " << path << " line " << lineNumber
                          << ": expected 3 fields: " << line << '\n';
                return 1;
            }
            std::cout << fields[0] << ' ' << fields[1] << ' ' << fields[2]
                      << '\n';
        }
    }

    // Remember, bad() means a read failed.
    if (file.bad()) {
        std::cerr << "Error: could not read " << path << '\n';
        return 1;
    }

    // The report ends with the count: one line of the file per server.
    std::cout << "Servers: " << lineNumber << '\n';
    return 0;
}
