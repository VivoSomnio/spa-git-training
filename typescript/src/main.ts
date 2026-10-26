// server_report prints the servers listed in a servers file, one line per
// server. Each line of the file is one record, host|environment|port, as
// in Lesson 3.13. The file's path is the program's one argument:
// node .\typescript\dist\main.js .\servers.txt
// The report ends with a count line: Servers: and the number of servers.

// Remember, import { ... } names what this file uses: node:fs opens the
// file as a stream, and node:readline cuts the stream into lines.
import { createReadStream } from "node:fs";
import * as readline from "node:readline";

// Remember, an async function may wait with await.
async function main(): Promise<void> {
    // Remember, the flags arrive as a list after the program name;
    // process.argv.slice(2) keeps only the words after it.
    const flags: string[] = process.argv.slice(2);
    if (flags.length !== 1) {
        console.error("Error: use server-report <servers file>");
        process.exitCode = 1;
        return;
    }
    const path: string = flags[0];
    console.log("Server Report");

    // lineNumber counts every line from 1, as an editor does.
    let lineNumber: number = 0;
    try {
        // Remember, one line at a time: for await ... of waits for each
        // line, which readline gives without its line ending, and a
        // missing file throws from the loop.
        const reader = readline.createInterface({
            input: createReadStream(path, "utf-8"),
            crlfDelay: Infinity,
        });
        for await (const line of reader) {
            lineNumber = lineNumber + 1;

            // An empty line holds no server, so only other lines are
            // printed.
            if (line !== "") {
                // Remember, split returns the pieces; check the field
                // count first.
                const fields: string[] = line.split("|");
                if (fields.length !== 3) {
                    const problem: string =
                        `line ${lineNumber}: expected 3 fields`;
                    console.error(`Error: ${path} ${problem}: ${line}`);
                    process.exitCode = 1;
                    return;
                }
                console.log(`${fields[0]} ${fields[1]} ${fields[2]}`);
            }
        }
    } catch {
        // Remember, an unnamed catch ignores the error's details: a
        // missing file and a failed read both end up here.
        console.error(`Error: could not read ${path}`);
        process.exitCode = 1;
        return;
    }

    // The report ends with the count: one line of the file per server.
    console.log(`Servers: ${lineNumber}`);
}

// Remember, main() on the last line runs the program.
main();
