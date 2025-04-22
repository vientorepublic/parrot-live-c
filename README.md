# parrot.live C version

Parrot Live C is a terminal application that streams animated frames with color effects. It replicates the functionality of the [original TypeScript project](https://github.com/vientorepublic/parrot.live) in C, allowing users to experience animated visuals directly in their terminal.

## Project Structure

```
parrot-live-c
├── src
│   ├── main.c        # Entry point of the application
│   ├── frames.c      # Implementation of frame loading and streaming
│   └── frames.h      # Header file for frame functions
├── Makefile          # Build instructions
└── README.md         # Project documentation
```

## Requirements

- POSIX Compatible environment
- A C compiler (e.g., GCC)
- Standard C library

## Building the Project

To compile the project, navigate to the project directory and run:

```
make
```

This will generate the executable file.

## Running the Application

After building the project, you can run the application using:

```
./parrot-live
```

You can customize the behavior of the application by modifying the source code in `src/main.c` and `src/frames.c`.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.
