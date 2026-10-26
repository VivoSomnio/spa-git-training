// server_report prints the servers listed in a servers file, one line per
// server. Each line of the file is one record, host|environment|port, as
// in Lesson 3.13. The file's path is the program's one argument, typed
// after the -- of dotnet run.
// The report ends with a count line: Servers: and the number of servers.

// Remember, using System; lets the program use Console, and using
// System.IO; adds StreamReader and IOException.
using System;
using System.IO;

internal static class Program
{
    // Remember, Main starts the program; 0 = success, 1 = failure.
    private static int Main(string[] args)
    {
        // Remember, the flags arrive as a list after the program name; in
        // C# args holds only the words after it.
        if (args.Length != 1)
        {
            Console.Error.WriteLine("Error: use server-report <servers file>");
            return 1;
        }
        string path = args[0];
        Console.WriteLine("Server Report");

        // lineNumber counts every line from 1, as an editor does.
        int lineNumber = 0;
        try
        {
            // Remember, StreamReader reads a file, and using closes it when
            // the try block ends. One line at a time: ReadLine returns the
            // next line without its line ending, or null when none is left.
            using StreamReader reader = new StreamReader(path);
            string? line = reader.ReadLine();
            while (line != null)
            {
                lineNumber = lineNumber + 1;

                // An empty line holds no server, so only other lines are
                // printed.
                if (line != "")
                {
                    // Remember, split returns the pieces; check the field
                    // count first.
                    string[] fields = line.Split('|');
                    if (fields.Length != 3)
                    {
                        Console.Error.WriteLine("Error: " + path + " line "
                            + lineNumber + ": expected 3 fields: " + line);
                        return 1;
                    }
                    Console.WriteLine(fields[0] + " " + fields[1] + " "
                        + fields[2]);
                }
                line = reader.ReadLine();
            }
        }
        catch (IOException)
        {
            // Remember, an unnamed catch ignores the error's details: a
            // missing file and a failed read are both IOExceptions.
            Console.Error.WriteLine("Error: could not read " + path);
            return 1;
        }
        catch (UnauthorizedAccessException)
        {
            // Remember, a folder, or a file you may not read, throws
            // UnauthorizedAccessException, which is not an IOException, so
            // it needs its own catch.
            Console.Error.WriteLine("Error: could not read " + path);
            return 1;
        }

        // The report ends with the count: one line of the file per server.
        Console.WriteLine("Servers: " + lineNumber);
        return 0;
    }
}
