/***************************************************************************//**
  @file         main.c
  @author       Dipro Chowdhury
  @date         Tuesday, 5 April 2016
*******************************************************************************/

int main(int argc, char **argv)
{
  // Load config files Here

  // call the loop function here
  shell_loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}

//Implementation of the loop
void shell_loop(void)
{
  //To store Characters
	char *line;
  //The args are the strings passed
    char **args;
    
    bool flag;  //To hold true or false

    do {

    printf("> ");
    line = read_a_line();
    args = split_a_line(line);
    flag = execute(args);

    free(line);
    free(args);
  } while (flag);
    	
}


//Implementation of read_a_line
#define C_SHELL_BUFFERSIZE 1024
char *read_a_line(void)
{
  int bufsize = C_SHELL_BUFFERSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "c_shell: memory allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += C_SHELL_BUFFERSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "c_shell: memory allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

/*
The same function above can be implementd using getline() in stdio.h
char *read__a_line(void)
{
  char *line = NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for us
  getline(&line, &bufsize, stdin);
  return line;
}
*/

#define C_SHELL_TOK_BUFSIZE 64
#define C_SHELL_TOK_DELIM " \t\r\n\a"
char **split_a_line(char *line)
{
  int bufsize = C_SHELL_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "c_shell: memory allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, C_SHELL_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += C_SHELL_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "c_shell: memory allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, C_SHELL_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}