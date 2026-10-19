// server_report prints the servers listed in a servers file, one line per
// server. Each line of the file is one record, host|environment|port, as
// in Lesson 3.13. The file's path is the program's one argument:
// .\c\server-report.exe .\servers.txt
// The report ends with a count line: Servers: and the number of servers.

// Remember, #include adds the declarations: stdio.h for files and
// printing, and string.h for strcmp and strcspn.
#include <stdio.h>
#include <string.h>

// Splits source_text at every separator into the rows of parts and returns
// the true number of parts; a part beyond max_parts is counted, not
// stored. Remember, C has no split function, so this one walks the text
// one character at a time, as in Lesson 3.13.
int split_text(const char *source_text, char separator, char parts[][256],
               int max_parts) {
    int part = 0;
    int length = 0;
    parts[0][0] = '\0';
    for (int index = 0; source_text[index] != '\0'; index = index + 1) {
        if (source_text[index] == separator) {
            part = part + 1;
            length = 0;
            if (part < max_parts) {
                parts[part][0] = '\0';
            }
        } else if (part < max_parts && length < 255) {
            parts[part][length] = source_text[index];
            length = length + 1;
            parts[part][length] = '\0';
        }
    }
    return part + 1;
}

// Remember, main starts the program; 0 = success, 1 = failure.
int main(int argc, char *argv[]) {
    // Remember, the flags arrive as a list after the program name, so the
    // one file path makes argc 2.
    if (argc < 2) {
        fprintf(stderr, "Error: use server-report <servers file>\n");
        return 1;
    }
    const char *path = argv[1];
    printf("Server Report\n");

    // Remember, fopen returns NULL when it cannot open the file.
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: could not read %s\n", path);
        return 1;
    }

    // Remember, one line at a time: fgets keeps the \n and returns NULL
    // when no line is left. line_number counts every line from 1, as an
    // editor does.
    int line_number = 0;
    char line[256];
    while (fgets(line, sizeof line, file) != NULL) {
        line_number = line_number + 1;

        // line holds 254 characters, the \n and the '\0'; a line with no \n
        // before the end of the file did not fit. Remember, feof means the
        // end was reached.
        if (line[strcspn(line, "\n")] != '\n' && feof(file) == 0) {
            fprintf(stderr, "Error: %s line %d: longer than 254 characters\n",
                    path, line_number);
            fclose(file);
            return 1;
        }

        // Remember, remove the \r first: strcspn finds the \r or the \n.
        line[strcspn(line, "\r\n")] = '\0';

        // An empty line holds no server, so only other lines are printed.
        if (strcmp(line, "") != 0) {
            // Remember, check the field count first.
            char fields[4][256];
            if (split_text(line, '|', fields, 4) != 3) {
                fprintf(stderr, "Error: %s line %d: expected 3 fields: %s\n",
                        path, line_number, line);
                fclose(file);
                return 1;
            }
            printf("%s %s %s\n", fields[0], fields[1], fields[2]);
        }
    }

    // Remember, ferror is nonzero when a read failed.
    int read_error = ferror(file);
    fclose(file);
    if (read_error != 0) {
        fprintf(stderr, "Error: could not read %s\n", path);
        return 1;
    }

    // The report ends with the count: one line of the file per server.
    printf("Servers: %d\n", line_number);
    return 0;
}
