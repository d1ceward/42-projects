# 42-get_next_line

The goal of this project was to write a function to return the next line of a file.

## Prototype

```C
￼int get_next_line(int const fd, char **line);
```

The first parameter is the file descriptor from which to read, and the second is a pointer to where the client would like the next line to be placed.

The function will return the next line of a file without the '\n' at the end.

The function will return 1 if successful, 0 if the file has nothing to read, and -1 if there is an error.
