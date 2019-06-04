/***************************************************************************//**
  @file         main.c
  @author       Stephen Brennan
  @date         Thursday,  8 January 2015
  @brief        LSH (Libstephen SHell)
*******************************************************************************/

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <limits.h>
#include <unistd.h>

char home[45] = "/home/";

#define MAX_LINE_HISTORY 10
#define LSH_RL_BUFSIZE 1024
#define USERNAME getenv("USER")
#define ROOT_HISTFILE "/root/.bash_history_simpleshell"
#define USER_HISTFILE strcat(home, strcat(USERNAME, "/.bash_history_simpleshell"))
#define HISTORY_FILE (strcmp(USERNAME, "root") == 0) ? ROOT_HISTFILE : USER_HISTFILE
/*
  Function Declarations for builtin shell commands:
 */
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_history(char **args);
int lsh_cat(char **args);
int lsh_echo(char **args);
//char *home = "/home/";

int save_cmd_history(char *args);
struct Queue *queue = NULL;


/*
 * Implement queue for storing history
 */
struct Queue
{
  int front, rear, size;
  unsigned capacity;
  char array[MAX_LINE_HISTORY][LSH_RL_BUFSIZE];
};

struct Queue *createQueue(unsigned capacity)
{
  struct Queue *queue = (struct Queue*) malloc(sizeof(struct Queue));
  queue->capacity = capacity;
  queue->front = queue->size = 0;
  queue->rear = capacity - 1;
  //queue->array = (char**) malloc(queue->capacity * sizeof(char*));
  return queue;
}

int isFull(struct Queue* queue)
{
  return (queue->size == queue->capacity);
}

int isEmpty(struct Queue *queue)
{
  return (queue->size == 0);
}

void enqueue(struct Queue *queue, char *item)
{
  if (isFull(queue)){
    printf("%s\n", "Queue full!" );
    return;
  }
  queue->rear = (queue->rear + 1) % queue->capacity;
  strcpy(queue->array[queue->rear], item);
  queue->size = queue->size + 1;
  //printf("rear: %d\n", queue->rear);
}

char *dequeue(struct Queue *queue)
{
  if (isEmpty(queue)){
    printf("%s\n", "Queue empty");
    return NULL;
  }
  char *item = queue->array[queue->front];
  queue->front = (queue->front + 1) % queue->capacity;
  queue->size = queue->size - 1;
  //printf("front: %d\n", queue->front);
  return item;
}

char *front(struct Queue *queue)
{
  if (isEmpty(queue))
    return NULL;
  return queue->array[queue->front];
}

char *rear(struct Queue *queue)
{
  if (isEmpty(queue))
    return NULL;
  return queue->array[queue->rear];
}


/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
  "cd",
  "help",
  "exit",
  "history",
  "cat",
  "echo"
};

int (*builtin_func[]) (char **) = {
  &lsh_cd,
  &lsh_help,
  &lsh_exit,
  &lsh_history,
  &lsh_cat,
  &lsh_echo
};

int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/

/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

/*
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
int lsh_help(char **args)
{
  int i;
  printf("Stephen Brennan's LSH\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < lsh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
int lsh_exit(char **args)
{
  return 0;
}

int lsh_history(char **args)
{
    //printf("%d %d\n", queue->front, queue->rear);
    int i = queue->front;
    do
    {
      printf("%s\n", queue->array[i]);
      i++;
      i = i % MAX_LINE_HISTORY;
    } while (i != queue->rear);{
   }
   printf("%s\n", queue->array[queue->rear]);
  // STORING TO FILE
  // int fd;
  // char buf[10000];
  // ssize_t nr, nw;
  
  // if ((fd = open(HISTORY_FILE, O_RDONLY, 0)) == -1){
  //   perror("lsh");
  //   return 1;
  // }
  // if ((nr = read(fd, buf, sizeof(buf))) == -1){
  //   perror("lsh");
  //   return 1;
  // }
  // if ((nw = write(STDOUT_FILENO, buf, nr)) == -1){
  //   perror("lsh");
  //   return 1;
  // }
  // close(fd);
  // return 1;
}

/**
CAT(1)                             User Commands                             CAT(1)

NAME
       cat - concatenate files and print on the standard output

SYNOPSIS
       cat [OPTION]... [FILE]...

        @always return 1 for continuing execution
 */
int lsh_cat(char **args)
{
  int fd;
  char buf[10000];
  ssize_t nr, nw;
  
  if ((fd = open(*++args, O_RDONLY, 0)) == -1){
    perror("lsh");
    return 1;
  }
  if ((nr = read(fd, buf, sizeof(buf))) == -1){
    perror("lsh");
    return 1;
  }
  if ((nw = write(STDOUT_FILENO, buf, nr)) == -1){
    perror("lsh");
    return 1;
  }
  close(fd);
  return 1;
}


/**
   ECHO(1)                            User Commands                            ECHO(1)

NAME
       echo - display a line of text

SYNOPSIS
       echo [SHORT-OPTION]... [STRING]...
       echo LONG-OPTION

DESCRIPTION
       Echo the STRING(s) to standard output.

       -n     do not output the trailing newline

       -e     enable interpretation of backslash escapes

       -E     disable interpretation of backslash escapes (default)

       --help display this help and exit

       --version
              output version information and exit

       If -e is in effect, the following sequences are recognized:

       \\     backslash

       \a     alert (BEL)

       \b     backspace

       \e     escape

       \f     form feed

       \n     new line

       \r     carriage return

       \t     horizontal tab

       \v     vertical tab
   @return Always returns 1, to continue execution.
 */
int lsh_echo(char **args)
{
  bool flag_n = false;
  bool flag_e = false;
  bool flag_E = false;

  while(**++args == '-'){
    if (strcmp(*args, "-n") == 0)
      flag_n = true;
    else if (strcmp(*args, "-e") == 0)
      flag_e = true;
    else if (strcmp(*args, "-E") == 0)
      flag_E = true;
  }

  while(*args != NULL){
    // write(STDOUT_FILENO, *args, strlen(*args));
    // write(STDOUT_FILENO, " ", 1);
    // args++;
    char *s = *args;
    int state = 0;
    while(*s != '\0'){
      if(*s == '\\' && state == 0){
        state = 1;
        s++;
        continue;
      }
      else if (state == 1){
        switch(*s){
        case 'a':
          write(STDOUT_FILENO, "\a", 1);
          break;
        case 'b':
          write(STDOUT_FILENO, " ", 1);
          break;
        case '\\':
          write(STDOUT_FILENO, "\\", 1);
          break;
        case 'e':
          write(STDOUT_FILENO, "\e", 1);
          break;
        case 'f':
          write(STDOUT_FILENO, "\f", 1);
          break;
        case 'n':
          write(STDOUT_FILENO, "\n", 1);
          break;
        case 'r':
          write(STDOUT_FILENO, "\r", 1);
          break;
        case 't':
          write(STDOUT_FILENO, "\t", 1);
          break;
        case 'v':
          write(STDOUT_FILENO, "\v", 1);
          break;
        default:
          state = 0;
          break;
        }
        state = 0;
        s++;
        continue;
      }
      write(STDOUT_FILENO, s, 1);
      s++;
    }
    write(STDOUT_FILENO, " ", 1);
    args++;
  }
  if(flag_n == false)
    write(STDOUT_FILENO, "\n", 1);
  return 1;
}





/**
  @brief Launch a program and wait for it to terminate.
  @param args Null terminated list of arguments (including program).
  @return Always returns 1, to continue execution.
 */
int lsh_launch(char **args)
{
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
  } else {
    // Parent process
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int lsh_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < lsh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return lsh_launch(args);
}

/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *lsh_read_line(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    if (c == EOF) {
      exit(EXIT_SUCCESS);
    } else if (c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}


int save_cmd_history(char *args)
{
  if (isFull(queue))
    dequeue(queue);
  enqueue(queue, args);
  return 1;
  // STORING TO FILE
  // int fd;
  // ssize_t nw;
  // fd = open(HISTORY_FILE, O_CREAT, S_IRWXU);
  // close(fd);


  // if ((fd = open(HISTORY_FILE, O_WRONLY|O_APPEND)) == -1){
  //   perror("lsh.save_cmd_history.open file");
  //   return 1;
  // }
  // //printf(" %d %d %d %d\n", fd, O_WRONLY, O_APPEND, S_IRWXU);
  // if ((nw = write(fd, args, strlen(args))) == -1){
  //   perror("lsh.save_cmd_history.write file");
  //   return 1;
  // }
  // write(fd, "\n", 1);
  // close(fd);
  // return 1;
}

int append_history()
{
  int fd;
  ssize_t nw;
  fd = open(HISTORY_FILE, O_CREAT, S_IRWXU);
  close(fd);


  if ((fd = open(HISTORY_FILE, O_WRONLY|O_APPEND)) == -1){
    perror("lsh.save_cmd_history.open file");
    return EXIT_FAILURE;
  }
  //printf(" %d %d %d %d\n", fd, O_WRONLY, O_APPEND, S_IRWXU);
  int i = queue->front;
  do{
    if ((nw = write(fd, queue->array[i], strlen(queue->array[i]))) == -1){
      perror("lsh.save_cmd_history.write file");
      return EXIT_FAILURE;
    }
    write(fd, "\n", 1);
    i++;
    i = i % MAX_LINE_HISTORY;
  }while (i != queue->rear);
  if ((nw = write(fd, queue->array[i], strlen(queue->array[i]))) == -1){
      perror("lsh.save_cmd_history.write file");
      return EXIT_FAILURE;
    }
  write(fd, "\n", 1);
  close(fd);
  return EXIT_SUCCESS;
}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **lsh_split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
		free(tokens_backup);
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

/**
   @brief Loop getting input and executing it.
 */
void lsh_loop(void)
{
  char *line;
  char **args;
  int status;

  int i = 0;
  do {
    printf("> ");
    line = lsh_read_line();
    save_cmd_history(line);
    // printf("%d, %d\n", queue->front, queue->rear);
    // printf("%s\n",queue->array[queue->front]);
    // printf("%s\n",queue->array[queue->rear]);
    args = lsh_split_line(line);
    // printf("%s\n",queue->array[queue->front]);
    // printf("%s\n",queue->array[queue->rear]);
    status = lsh_execute(args);
    // printf("%s\n",queue->array[queue->front]);
    // printf("%s\n",queue->array[queue->rear]);
    free(line);
    free(args);
    // printf("%s\n",queue->array[queue->front]);
    // printf("%s\n",queue->array[queue->rear]);
  } while (status);
  // printf("%d, %d\n", queue->front, queue->rear);
  // for (int i = queue->front; i <= queue->rear; i++)
  //   printf("%s\n", queue->array[i]);
  append_history();
}

/**
   @brief Main entry point.
   @param argc Argument count.
   @param argv Argument vector.
   @return status code
 */
int main(int argc, char **argv)
{
  queue = createQueue(MAX_LINE_HISTORY);
  printf("%s\n", HISTORY_FILE);
  // Load config files, if any.

  // Run command loop.
  lsh_loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}
