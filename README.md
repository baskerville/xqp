# Description

*xqp* (*X* *Q*uery *P*ointer) is an X.Org utility that prints the ID of the window under the pointer.

# Synopsis

    xqp [-h|-v] [WID ...]

# Options

- `-h` — Print the synopsis to standard output and exit.
- `-v` — Print the version to standard output and exit.

If window IDs are given as arguments, *xqp* won't print anything but will return (via the exit code) whether or not the window under the pointer is in the list of given windows.
