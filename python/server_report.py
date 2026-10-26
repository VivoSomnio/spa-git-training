# server_report prints the servers listed in a servers file, one line per
# server. Each line of the file is one record, host|environment|port, as
# in Lesson 3.13. The file's path is the program's one argument:
# py .\python\server_report.py .\servers.txt
# The report ends with a count line: Servers: and the number of servers.

# Remember, sys.name after import sys.
import sys


# Remember, main returns the exit code: 0 for success, 1 for failure.
def main() -> int:
    # Remember, the flags arrive as a list after the program name.
    if len(sys.argv) != 2:
        print("Error: use server-report <servers file>", file=sys.stderr)
        return 1
    path = sys.argv[1]
    print("Server Report")

    # line_number counts every line from 1, as an editor does.
    line_number = 0
    try:
        # Remember, with closes the file even after an error. One line at
        # a time: a for loop over the file gives each line, ending in \n
        # (text mode reads \r\n as \n).
        with open(path, encoding="utf-8") as file:
            for line in file:
                line_number = line_number + 1
                line = line.replace("\n", "")

                # An empty line holds no server, so only other lines are
                # printed.
                if line != "":
                    # Remember, split returns the pieces; check the field
                    # count first.
                    fields = line.split("|")
                    if len(fields) != 3:
                        problem = f"line {line_number}: expected 3 fields"
                        print(f"Error: {path} {problem}: {line}",
                              file=sys.stderr)
                        return 1
                    print(f"{fields[0]} {fields[1]} {fields[2]}")
    except (OSError, ValueError):
        # Remember, except (A, B) catches either, and this one ignores the
        # error's details: a missing file or a failed read is an OSError,
        # and a file that is not UTF-8 is a ValueError.
        print(f"Error: could not read {path}", file=sys.stderr)
        return 1

    # The report ends with the count: one line of the file per server.
    print(f"Servers: {line_number}")
    return 0


# Remember, sys.exit turns main's return value into the exit code.
if __name__ == "__main__":
    sys.exit(main())
