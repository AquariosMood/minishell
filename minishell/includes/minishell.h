/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:21:54 by bryda-si          #+#    #+#             */
/*   Updated: 2025/01/14 13:31:06 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define WITH_OPTION 1
# define WITHOUT_OPTION 0
# define FALSE 0
# define TRUE 1
// # define ERROR_COMMAND "minishell : %s: command not found\n"
// # define ERROR_SYNTAX "minishell: syntax error near unexpected token `%s'\n"
// # define ERROR_PERMISSION "minishell: %s: Permission denied\n"
// # define ERROR_FILE "minishell: %s: %s: No such file or directory\n"
// # define ERROR_DIRECTORY "minishell: %s: Is a directory\n"
// # define ERROR_HERE_STRING "minishell: here-string is not supported\n"
// # define ERROR_TOO_MANY_ARGS "minishell: %s: too many arguments\n"
# define ERROR_EXPORT "not a valid identifier"
# define CHUNK_SIZE 1024
# define INT_MAX 2147483647
# define INT_MIN -2147483648

extern char				**environ;
extern int				g_sigint_received;
extern int				g_in_command_execution;

typedef struct s_env
{
	char				*pwd;
	char				*old_pwd;
}						t_env;

typedef struct s_copy_env
{
	char				*name;
	char				*value;
	int					is_exported;
	struct s_copy_env	*next;
}						t_copy_env;

enum					e_interactive
{
	INTERACTIVE,
	NOT_INTERACTIVE
};

enum					e_token_type
{
	TOKEN_PIPE,
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_REDIRECT_INPUT,
	TOKEN_REDIRECT_OUTPUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_FILE,
	TOKEN_DELIMITER,
	TOKEN_HERE_STRING,
	NULL_TOKEN
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_redirect
{
	unsigned int		index;
	char				*file;
	enum e_token_type	type;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_command_context
{
	pid_t				*pids;
	int					**fd_pipes;
	int					number_commands;
	int					number_pipes;
}						t_command_context;

typedef struct s_command
{
	unsigned int		index;
	char				*command;
	char				**args;
	t_redirect			*redirect;
	int					in_fd;
	int					out_fd;
	struct s_command	*next;
}						t_command;

typedef struct s_minishell
{
	enum e_interactive	interactive;
	t_command			*commands;
	t_command_context	context;
	t_copy_env			*copy_env;
	t_token				*tokens;
	enum e_token_type	type;
	int					exit_code;
}						t_minishell;

typedef union u_builtins_function
{
	int					(*function)(t_minishell *, t_command *);
	int					(*function_fd)(t_minishell *, t_command *, int);
}						t_builtins_function;

typedef struct s_builtin
{
	char				*name;
	t_builtins_function	func;
	int					use_fd;
}						t_builtin;

typedef struct s_chunk
{
	char				*data;
	size_t				size;
	struct s_chunk		*next;
}						t_chunk;

enum					e_builtins
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NO_BUILTINS
};

enum					e_errors
{
	NO_ERROR,
	NO_COMMAND,
	NO_FILE,
	NO_DIRECTORY,
	NO_PERMISSION,
	NO_ENV,
	NO_HOME,
	NO_OLDPWD,
	NO_ARG,
	NO_VAR,
	NO_VALUE,
	NO_MEMORY
};

//-------------------- INIT --------------------
/**
 * @brief Initializes all structures required for the minishell program.
 *
 * This function sets up and initializes all necessary structures and variables
 * for the proper functioning of the minishell program. It ensures that all
 * components are correctly allocated and initialized before the shell starts
 * executing commands.
 *
 * @param minishell A pointer to the t_minishell structure
 * that needs to be initialized.
 * @return
 * 		- TRUE  (1) : Initialization was successful.
 *
 * 		- FALSE (0) : Error occurred during initialization.
 *
 * @note The function initializes the following structures:
 *
 * - t_minishell
 *
 * - t_env
 *
 * - t_copy_env
 *
 * - t_token
 *
 * - t_command
 *
 * - Interactive mode
 *
 * - Exit status
 *
 * - Signal handling
 */
int						init_all_struct_minishell(t_minishell *minishell);

/**
 * @brief Initializes the signal handling for the minishell.
 *
 * This function sets up the necessary signal handlers for the minishell
 * to ensure proper handling of signals such as SIGINT, SIGQUIT, etc.
 *
 * @return
 * 			- TRUE  (1) : Signal handling was successful.
 *
 * 			- FALSE (0) : Error occurred during signal handling.
 *
 * @note The signal handlers are set up using the signal() function.
 */
int						init_signal(void);

//-------------------- INIT_ENV --------------------

/**
 * @brief Initializes a copy of the environment variables.
 *
 * This function takes the environment variables provided by the system
 * and creates a copy of them for use within the minishell program.
 *
 * @param environ The environment variables provided by the system.
 * @return
 * 			- A pointer to the t_copy_env structure containing the copied
 * environment variables.
 *
 * 			- NULL if an error occurred during initialization.
 *
 * @note The returned structure should be freed when no longer needed.
 */
t_copy_env				*init_copy_env(char **environ);

/**
 * @brief Creates a new environment variable.
 *
 * This function allocates and initializes a new environment variable
 * with the given name and value. The variable can be marked as exported
 * or not based on the is_exported flag.
 *
 * @param name The name of the environment variable.
 * @param value The value of the environment variable.
 * @param is_exported A flag indicating whether
 * the variable is exported (1) or not (0).
 * @return
 * 				- A pointer to the newly created t_copy_env structure.
 *
 * 				- NULL if an error occurred during initialization.
 *
 * @note The returned structure should be freed when no longer needed.
 */
t_copy_env				*create_env(char *name, char *value, int is_exported);

/**
 * @brief Extracts the value of an environment variable from a given string.
 *
 * This function takes a string representing an environment variable in the
 * format "NAME=VALUE" and extracts the "VALUE" part of the string.
 *
 * @param environ The string containing the environment variable.
 * @return
 * 				- The value of the environment variable as a string.
 *
 * 				- NULL if the environment variable does not exist.
 *
 * @note The returned string is a copy of the value and should be freed
 */
char					*get_env_value(char *environ);

/**
 * @brief Extracts the name of an environment variable from a given string.
 *
 * This function takes a string representing an environment variable in the
 * format "NAME=VALUE" and extracts the "NAME" part of the string.
 *
 * @param environ The string containing the environment variable.
 * @return
 * 				- The name of the environment variable as a string.
 *
 * 				- NULL if the environment variable does not exist.
 *
 * @note The returned string is a copy of the name and should be freed
 */
char					*get_env_name(char *environ);

/**
 * @brief Adds a copy of the environment variable to the linked list.
 *
 * This function adds a new node containing a copy of the environment variable
 * to the linked list. The new node is added to the end of the list.
 *
 * @param head Pointer to the head of the linked list.
 * @param current Pointer to the current node in the linked list.
 * @return
 * 				- TRUE  (1) : The environment variable was successfully added.
 *
 * 				- FALSE (0) : An error occurred while adding
 * 								the environment variable.
 *
 * @note The function allocates memory for the new node and copies the
 * environment variable into the node.
 */
int						add_copy_env(t_copy_env **head, t_copy_env **current,
							t_copy_env *new_env);

/**
 * @brief Initializes a single environment variable node.
 *
 * This function initializes a single environment variable node and adds it to
 * the linked list of environment variables.
 *
 * @param head Pointer to the head of the linked list of environment variables.
 * @param current Pointer to the current node in the linked list.
 * @return
 * 				- TRUE  (1) : The environment variable
 * 							was successfully initialized.
 *
 * 				- FALSE (0) : An error occurred while initializing
 *
 * @note The function allocates memory for the new node and copies the
 * environment variable into the node.
 */
int						init_one_env(t_copy_env **head, t_copy_env **current,
							char *environ);

/**
 * Checks if a given environment variable is exported
 *
 * @param environ The environment variable string to check
 * @return
 * 				- TRUE  (1) : The environment variable is exported.
 *
 * 				- FALSE (0) : The environment variable is not exported.
 *
 * @note The function checks if the environment variable
 * contains an '=' character.
 */
int						check_is_exported(char *environ);

//-------------------- FREE --------------------

/**
 * @brief Frees all allocated memory within the minishell structure
 *
 * @param minishell Pointer to the minishell structure to be freed
 *
 * This function is responsible for cleaning up and deallocating all memory
 * that was allocated during the execution of the minishell program.
 * It prevents memory leaks by properly freeing all components of the
 * minishell structure.
 */
void					free_minishell(t_minishell *minishell);

// void		free_env(t_env *env);

/**
 * @brief Frees memory allocated for token list
 *
 * @param token Pointer to the first token in the list to be freed
 *
 * This function is responsible for freeing all memory allocated for the
 * token list. It iterates through the list and frees each token node
 * to prevent memory leaks.
 */
void					free_tokens(t_token *token);

/**
 * @brief Frees all memory associated with a command structure
 *
 * @param command Pointer to the command structure to be freed
 *
 * This function is responsible for freeing all memory associated with
 * a command structure. It deallocates all memory allocated for the
 * command, arguments, and redirected file.
 */
void					free_command(t_command *command);

/**
 * Frees the memory allocated for a copied environment list
 * @param head Pointer to the head node of the copied environment list
 *
 * This function deallocates all memory associated with a linked list
 * of environment variables, starting from the given head node.
 * It traverses through the list and frees each node's memory.
 */
void					free_copy_env(t_copy_env *head);

//-------------------- BUILTINS --------------------

/**
 * Retrieves the value of a specific environment variable
 * from the copy environment
 *
 * @param copy_env Pointer to the structure containing
 * the copied environment variables
 * @param name_env Name of the environment variable to retrieve
 * @return
 * 				- The value of the environment variable as a string
 *
 * 				- NULL if the environment variable does not exist
 */
char					*get_env_uniq(t_copy_env *copy_env, char *name_env);

/**
 * @brief Adds or modifies environment variables in the shell
 *
 * @param minishell Pointer to the minishell structure containing
 * environment and state information
 * @param fd_out write into the file descriptor if it is not -1
 * else write into stdout
 * @return
 * 				- TRUE  (1) : The export command was successful
 *
 * 				- FALSE (0) : An error occurred during the export command
 */
int						ft_export(t_minishell *minishell, t_command *command,
							int fd_out);

/**
 * @brief Removes one or more environment variables
 *
 * Deletes environment variables specified as arguments from the shell's
 * environment. If a variable doesn't exist, it's silently ignored.
 *
 * @param minishell Pointer to the minishell structure containing shell data
 * @return
 * 				- TRUE  (1) : The unset command was successful
 *
 * 				- FALSE (0) : An error occurred during the unset command
 *
 * @note The function removes the specified environment variables from the
 * copy environment.
 */
int						ft_unset(t_minishell *minishell, t_command *command);

/**
 * @brief Changes the current working directory
 *
 * Implements the 'cd' (change directory) builtin command. Handles directory
 * navigation and updates environment variables PWD and OLDPWD accordingly.
 *
 * @param minishell Pointer to the main minishell structure containing
 *                  environment variables and command information
 *
 * @return
 * 				- TRUE  (1) : The cd command was successful
 *
 * 				- FALSE (0) : An error occurred during the cd command
 *
 * @note The function changes the current working directory based on the
 * arguments provided. It updates the PWD and OLDPWD environment variables
 * accordingly.
 */
int						ft_cd(t_minishell *minishell, t_command *command);

/**
 * @brief Displays the current environment variables
 *
 * This function prints all environment variables stored in the minishell
 * structure to the specified file descriptor.
 *
 * @param minishell Pointer to the minishell structure containing
 * environment variables
 * @param fd_out File descriptor where the output should be written
 * @return
 * 				- TRUE  (1) : The env command was successful
 *
 * 				- FALSE (0) : An error occurred during the env command
 *
 * @note The function prints the environment variables to
 * the specified file descriptor.
 */
int						ft_env(t_minishell *minishell, t_command *command,
							int fd_out);

int						ft_exit(t_minishell *minishell, t_command *command);

/**
 * @brief Displays the current working directory
 *
 * Prints the absolute path of the current working directory to the specified
 * file descriptor.
 *
 * @param minishell Pointer to the minishell structure containing program state
 * @param fd_out File descriptor where the output should be written
 * @return
 * 				- TRUE  (1) : The pwd command was successful
 *
 * 				- FALSE (0) : An error occurred during the pwd command
 *
 * @note The function prints the current working directory to the specified
 * file descriptor.
 */
int						ft_pwd(t_minishell *minishell, t_command *command,
							int fd_out);

/**
 * @brief Implements the echo command, displaying text to specified output
 *
 * Simulates the behavior of the shell's echo command. Handles the -n option
 * and writes the output to the specified file descriptor.
 *
 * @param minishell Pointer to the main minishell structure containing
 * command data
 * @param fd_out File descriptor where the output should be written
 * @return
 * 				- TRUE  (1) : The echo command was successful
 *
 * 				- FALSE (0) : An error occurred during the echo command
 *
 * @note The function writes the output of the echo command to the specified
 * file descriptor.
 */
int						ft_echo(t_minishell *minishell, t_command *command,
							int fd_out);
// int			export(t_copy_env *copy_env, char *arg);

/**
 * Checks if an environment variable already exists in the copied environment
 * list.
 *
 * @param copy_env Pointer to the copied environment list structure
 * @param value String to search for in the environment list
 * @return
 * 				- TRUE  (1) : The environment variable already exists
 *
 * 				- FALSE (0) : The environment variable does not exist
 *
 * @note The function checks if the environment variable already exists
 * in the copied environment list.
 */
int						check_existing_env(t_copy_env *copy_env, char *value);

//-------------------- UTILS_BUILTINS --------------------

/**
 * @brief Concatenates two strings into a new string
 *
 * @param s1 First string to be joined
 * @param s2 Second string to be joined
 * @return
 * 				- A new string containing the concatenated strings
 *
 * 				- NULL if an error occurred during concatenation
 *
 * @note The function allocates memory for the new string and copies
 * the contents of the input strings into it.
 */
char					*ft_strjoin(char *s1, char *s2);

/**
 * Compares up to n characters of two strings lexicographically
 *
 * @param s1 First string to compare
 * @param s2 Second string to compare
 * @param n Maximum number of characters to compare
 *
 * @return
 * 				- An integer less than, equal to, or greater than zero
 *
 * 				- If s1 is found, respectively, to be less than, to match,
 * 				or be greater than s2
 *
 * @note The function compares the first n characters of the two strings
 * and returns the result of the comparison.
 */
int						ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Calculates the length of a string
 *
 * @param str Pointer to the string to measure
 * @return
 * 				- The length of the string
 *
 * @note The function calculates the length of the string by counting
 */
int						ft_strlen(char *str);

//-------------------- SIGNAL --------------------

/**
 * @brief Handles signal interrupts during program execution
 *
 * This function manages the program's response to system signals.
 * It processes the signal specified by the signum parameter and
 * executes appropriate actions based on the signal type.
 *
 * @param signum The signal number to be handled
 */
void					handle_signal(int signum);

//----------------COMMAND--------------------

/**
 * Creates a new command structure with the specified parameters
 * @param command The command to be executed
 * @param args Array of command arguments
 * @param index_command Index of the command in the command list
 * @return
 * 				- A pointer to the newly created t_command structure
 *
 * 				- NULL if an error occurred during initialization
 *
 * @note The function allocates memory for the new command structure
 * and copies the command, arguments, and redirected file into it.
 * The new command is initialized with the specified parameters.
 */
t_command				*create_command(char *command, char **args,
							int index_command);

/**
 * @brief Converts a linked list of tokens into a command structure
 *

 * Takes a linked list of tokens and processes them to create a command
 structure
 * that can be executed by the shell. This includes parsing arguments, handling
 * redirections, and organizing command components.
 *
 * @param tokens Pointer to the first token in the linked list
 * @return
 * 				- A pointer to the t_command structure created from the tokens
 *
 * 				- NULL if an error occurred during conversion
 *
 * @note The function processes the tokens to create a command structure
 * that can be executed by the shell. It handles arguments, redirections,
 * and other command components.
 */
t_command				*convert_token_to_command(t_token *tokens);

/**
 * @brief Adds a new command node to the command linked list
 *
 * This function adds a new command node to the linked list of commands.
 * It appends the new command to the end of the list and updates the
 * head and current pointers accordingly.
 *
 * @param head Pointer to pointer to the head of the command list
 * @param current Pointer to pointer to the current command node
 * @param new_command Pointer to the new command node to be added
 *
 *
 * @note The function allocates memory for the new command node and
 * adds it to the end of the linked list.
 */
void					add_command(t_command **head, t_command **current,
							t_command *new_command);

// void					execute_command(t_minishell *minishell, int fd_out);

/**
 * @brief Prints the content of a command structure
 *
 * @param command Pointer to the command structure to be printed
 *
 * This function prints the contents of a t_command structure for debugging
 * or display purposes. The specific format and elements printed depend on
 * the structure's implementation.
 */
void					print_command(t_command *command);

/**
 * @brief Converts a linked list of tokens into an array of strings (argv)
 *
 * This function traverses the linked list of tokens and creates an array
 * of strings suitable for use as command arguments (argv). Each token's
 * content is copied into the new array.
 *
 * @param tokens Pointer to the first token in the linked list
 * @return
 * 				- An array of strings containing the token values
 *
 * 				- NULL if an error occurred during conversion
 *
 * @note The function allocates memory for the new array and copies the
 * token values into it. The array is terminated with a NULL pointer.
 */
char					**convert_token_argument_to_argv(t_token *tokens);

/**
 * @brief Executes built-in shell commands
 *
 * @param minishell Pointer to the main minishell structure containing
 * shell state
 *
 * @return
 * 				- TRUE  (1) : The built-in command was executed successfully
 *
 * 				- FALSE (0) : An error occurred during execution
 * 							or the command is not built-in
 *
 * @note The function checks if the command is a built-in shell command
 * and executes it if it is. It returns TRUE if the command was executed
 * successfully and FALSE if an error occurred or the command is not built-in.
 */
int						execute_builtins(t_minishell *minishell,
							t_command *current, enum e_builtins index_built,
							int fd_out);

/**
 * Allocates memory for the echo command structure.
 *
 * @param command   Pointer to the command structure to be allocated
 * @param len_option Length of the option string
 *
 * @return
 * 				- TRUE  (1) : Memory allocation was successful
 *
 * 				- FALSE (0) : An error occurred during memory allocation
 *
 * @note The function allocates memory for the echo command structure
 * based on the length of the option string.
 */
int						malloc_echo(t_command *command, int len_option);

/**
 * Calculates the size needed for malloc allocation of arguments array
 * based on the token list.
 *
 * @param tokens Pointer to the first token in the linked list
 * @return
 * 				- The size needed for malloc allocation
 *
 * 				- FALSE (0) : An error occurred during calculation
 *
 * @note The function calculates the size needed for malloc allocation
 * of the arguments array based on the number of tokens in the list.
 */
int						malloc_size_argv(t_token *tokens);

//-------------------- UTILS --------------------

/**
 * Duplicates a portion of a string
 * @param str The string to duplicate
 * @param end The index until which to copy (exclusive)
 * @return
 * 				- A new string containing the copied portion
 *
 * 				- NULL if an error occurred during duplication
 *
 * @note The returned string is null-terminated.
 */
char					*ft_strndup(char *str, unsigned int end);

char					**ft_split(char const *s, char c);

/**
 * @brief Extracts a substring from the given string starting at specified index
 *
 * @param str The source string to extract from
 * @param i The starting index position for extraction
 * @return
 * 				- A new string containing the extracted substring
 *
 * 				- NULL if an error occurred during extraction
 *
 * @note The function allocates memory for the new string and copies
 * the extracted substring into it.
 */
char					*ft_substr(char *str, int i);

/**
 * @brief Duplicates a string by allocating new memory
 *
 * Creates a new string by allocating memory and copying
 * the content of the source string into the new memory location
 *
 * @param s The string to duplicate
 * @return
 * 				- A new string containing the duplicated content
 *
 * 				- NULL if an error occurred during duplication
 *
 * @note The function allocates memory for the new string and copies
 * the content of the source string into it.
 */
char					*ft_strdup(char *s);

/**
 * @brief Prints all tokens in a linked list of tokens
 *
 * @param tokens Pointer to the first token in the linked list
 *

 * This function iterates through a linked list of
	tokens and prints each token's
 * content and type for debugging purposes.
 */
void					print_tokens(t_token *tokens);

/**
 * @brief Frees memory allocated for an array of strings
 *
 * This function deallocates memory for an array of strings (argv).
 * It first frees each individual string in the array, then frees
 * the array pointer itself.
 *
 * @param argv Array of strings to be freed
 */
void					free_argv(char **argv);

/**
 * @brief Prints all environment variables in export format
 * @param head Pointer to the head of the environment variables linked list
 * @return

 * 				- TRUE  (1) : The environment variables were printed successfully
 *
 * 				- FALSE (0) : An error occurred during printing
 *
 * This function prints all environment variables in the format:
 * "export VARIABLE_NAME=VALUE"
 */
int						print_env_export(t_copy_env *head, int fd_out);

int						check_one_char_value_env(char c);

/**
 * @brief Compares two strings lexicographically
 *
 * @param s1 First string to compare
 * @param s2 Second string to compare
 * @return
 * 				- An integer less than, equal to, or greater than zero
 *
 * 				- If s1 is found, respectively, to be less than, to match,
 * 				or be greater than s2
 *
 * @note The function compares the two strings lexicographically
 * and returns the result of the comparison.
 */
int						ft_strcmp(char *s1, char *s2);

//-------------------- TOKENIZER --------------------

/**
 * Creates a new token node with specified type and value
 * @param type The type classification of the token (enum e_token_type)
 * @param value String value of the token
 * @return
 * 				- A pointer to the newly created t_token structure
 *
 * 				- NULL if an error occurred during creation
 *
 * @note The function allocates memory for the new token node and
 * initializes it with the specified type and value.
 */
t_token					*create_token(enum e_token_type type, char *value);

/**
 * Breaks down the input string into a linked list of tokens
 *
 * @param input The input string to be tokenised
 * @return
 * 				- A pointer to the first token in the linked list
 *
 * 				- NULL if an error occurred during tokenisation
 *
 * @note The function analyses the input string and separates it into
 * individual tokens based on shell syntax rules. It handles quotes,
 * spaces, and shell special characters. Each token contains information
 * about its type and content.
 */
t_token					*tokenise(char *input, t_minishell *minishell);

/**
 * @brief Takes quoted or unquoted token and processes it accordingly
 * @param head Pointer to pointer of the first token in the linked list
 * @param current Pointer to pointer of the current token being processed
 * @param ptr Current position in the input string being parsed
 * @param type The type of the token being processed
 * @return
 * 				- A pointer to the next token in the linked list
 *
 * 				- NULL if an error occurred during processing
 *
 * @note The function processes a quoted or unquoted token and
 * creates a new token node based on the content and type.
 */
char					*token_quote_or_no_quote(t_token **head,
							t_token **current, char *ptr,
							t_minishell *minishell);

// /**
//  * @brief Processes token content without quotes
//  * @param ptr Pointer to the current position in the input string
//  * @param head Pointer to the head of token list
//  * @param current Pointer to the current token node
//  * @param type The type of the token being processed
//  * @return
//  * 				- A pointer to the next token in the linked list
//  *
//  * 				- NULL if an error occurred during processing
//  *
//  * @note The function processes token content without quotes and
//  * creates a new token node based on the content and type.
//  */
// char		*token_no_quote(char *ptr, t_token **head, t_token **current,
// 				enum e_token_type type);

/**
 * Processes input redirection or heredoc tokens in the command
 *
 * @param head Pointer to pointer of the first token in the list
 * @param current Pointer to pointer of the current token being processed
 * @param ptr Current position in the input string being parsed
 * @return
 * 				- A pointer to the next token in the linked list
 *
 * 				- NULL if an error occurred during processing
 *
 * @note The function processes input redirection or heredoc tokens
 * in the command and creates a new token node based on the content
 * and type.
 */
char					*redirect_input_or_heredoc(t_token **head,
							t_token **current, char *ptr);

/**
 * Handles output redirection or append redirection tokens
 *
 * @param head Pointer to pointer of the first token in the list
 * @param current Pointer to pointer of the current token being processed
 * @param ptr Current position in the input string being parsed
 *
 * @return
 * 				- A pointer to the next token in the linked list
 *
 * 				- NULL if an error occurred during processing
 *
 * @note The function processes output redirection or append redirection
 * tokens in the command and creates a new token node based on the content
 * and type.
 */
char					*redirect_output_or_append(t_token **head,
							t_token **current, char *ptr);

/**
 * Handles the redirection output token ('>') in the command line
 *
 * @param head Pointer to the pointer of the first token in the list
 * @param current Pointer to the pointer of the current token being processed
 * @param ptr Current position in the input string being parsed
 * @return
 * 				- A pointer to the next token in the linked list
 *
 * 				- NULL if an error occurred during processing
 *
 * @note The function processes the redirection output token ('>') in the
 * command line and creates a new token node based on the content and type.
 */
char					*token_redirect_output(t_token **head,
							t_token **current, char *ptr);

/**
 * @brief Handles redirection append (>>) token in the command parsing
 *
 * @param head Pointer to the pointer of the first token in the list
 * @param current Pointer to the pointer of the current token being processed
 * @param ptr Current position in the input string being parsed
 * @return
 * 				- A pointer to the next token in the linked list
 *
 * 				- NULL if an error occurred during processing
 *
 * @note The function processes the redirection append (>>) token in the
 * command line and creates a new token node based on the content and type.
 */
char					*token_redirect_append(t_token **head,
							t_token **current, char *ptr);

/**
 * @brief Handles a redirection input token in the command line parsing
 *
 * Processes the input redirection token '<' and updates
 * the token list accordingly.

 * Creates a new token for the redirection operation
	and updates the token chain.
 *
 * @param head Pointer to pointer to the head of token list
 * @param current Pointer to pointer to the current token being processed
 * @param ptr Current position in the input string being parsed
 * @return
 * 				- A pointer to the next token in the linked list
 *
 * 				- NULL if an error occurred during processing
 *
 * @note The function processes the input redirection token '<' in the
 * command line and creates a new token node based on the content and type.
 */
char					*token_redirect_input(t_token **head, t_token **current,
							char *ptr);

/**
 * @brief Handles heredoc token generation for command parsing
 *
 * This function processes input string to create a heredoc token,
 * which represents redirection for reading input from a delimited heredoc.
 *
 * @param head Pointer to pointer of the first token in the token list
 * @param current Pointer to pointer of the current token being processed
 * @param ptr Current position in the input string being parsed
 *
 * @return
 * 				- A pointer to the next token in the linked list
 *
 * 				- NULL if an error occurred during processing
 *
 * @note The function processes the heredoc token in the command line
 * and creates a new token node based on the content and type.
 */
char					*token_heredoc(t_token **head, t_token **current,
							char *ptr);

/**
 * @brief Processes and creates a token for other token type
 *
 * @param head Pointer to pointer of the first token in the linked list
 * @param current Pointer to pointer of the current token being processed
 * @param ptr Pointer to the current position in the input string
 *
 * @return
 * 				- A pointer to the next token in the linked list
 *
 * 				- NULL if an error occurred during processing
 *
 * @note The function processes the token content and type and creates
 * a new token node based on the content and type.
 */
char					*token_other(t_token **head, t_token **current,
							char *ptr, t_minishell *minishell);

/**
 * Tokenizes a pipe character ('|') in the input string.
 * Creates a new token node and adds it to the token list.
 *
 * @param head     Pointer to the head of the token list
 * @param current  Pointer to the current token being processed
 * @param ptr      Current position in the input string being tokenized
 *
 * @return
 * 				- A pointer to the next token in the linked list
 *
 * 				- NULL if an error occurred during processing
 *
 * @note The function processes the pipe character ('|') in the input
 * string and creates a new token node based on the content and type.
 */
char					*token_pipe(t_token **head, t_token **current,
							char *ptr);

/**
 * Processes and creates a here-string token from the input string
 *
 * @param head Double pointer to the head of the token list
 * @param current Double pointer to the current token being processed
 * @param ptr Pointer to the current position in the input string
 *
 * @return
 * 				- A pointer to the next token in the linked list
 *
 * 				- NULL if an error occurred during processing
 *
 * @note The function processes the here-string token in the input string
 * and creates a new token node based on the content and type.
 */
char					*token_here_string(t_token **head, t_token **current,
							char *ptr);

/**
 * @brief Adds a new token to the linked list of tokens
 *
 * @param head Pointer to the pointer of the first token in the list
 * @param current Pointer to the pointer of the current token in the list
 * @param new_token Pointer to the new token to be added
 *
 * This function adds a new token to a linked list of tokens.
 */
void					add_token(t_token **head, t_token **current,
							t_token *new_token);

/**
 * @brief Processes and creates a token for command arguments
 *
 * This function handles the creation of tokens
 * for command arguments in the shell.
 * It processes the input string pointed by ptr and creates or updates tokens
 * accordingly.
 *
 * @param head Pointer to pointer of the first token in the linked list
 * @param current Pointer to pointer of the current token being processed
 * @param ptr String containing the argument to be tokenized
 */
void					token_argument(t_token **head, t_token **current,
							char *ptr);

/**
 * @brief Creates a new command token and adds it to the token list
 *
 * @param head Pointer to the head of the token list
 * @param current Pointer to the current token in the list
 * @param ptr String containing the command to be tokenized
 *
 * Processes the string pointed by ptr to create a new command token.
 * The token is then added to the linked list of tokens.
 * The head pointer may be updated if the list is empty.
 * The current pointer will be updated to point to the newly created token.
 */
void					token_command(t_token **head, t_token **current,
							char *ptr);

/**
 * Checks the formatting of tokens for output append operations
 * @param head The head of the token list
 * @param tokens The current token being processed
 * @return
 * 				- TRUE  (1) : The token formatting is correct
 *
 * 				- FALSE (0) : The token formatting is incorrect
 *
 * @note The function checks the formatting of tokens for output append
 * operations and returns TRUE if the formatting is correct.
 */
int						check_formats_tokens_output_append(t_token *head,
							t_token *tokens);

/**
 * Validates and checks formatting of tokens specifically for input
 * and heredoc operations
 *
 * @param head Pointer to the first token in the linked list
 * @param tokens Pointer to the current token being processed
 *
 * @return
 * 				- TRUE  (1) : The token formatting is correct
 *
 * 				- FALSE (0) : The token formatting is incorrect
 *
 * @note This function ensures proper token formatting and syntax
 * specifically for input redirection (<) and heredoc (<<)
 * operations in the shell
 */
int						check_formats_tokens_input_heredoc(t_token *head,
							t_token *tokens);

/**
 * Checks if the pipe tokens in the command line are correctly formatted
 *
 * @param head The head of the token list
 * @param tokens The current token being checked
 * @return
 * 				- TRUE  (1) : The token formatting is correct
 *
 * 				- FALSE (0) : The token formatting is incorrect
 *
 * @note The function checks the formatting of pipe tokens in the command
 * line and returns TRUE if the formatting is correct.
 */
int						check_format_tokens_pipe(t_token *head,
							t_token *tokens);

/**
 * Validates the token sequence starting from the given head node
 * by checking for correct token syntax and relationships
 *
 * @param head The first token in the linked list
 * @param tokens The current token being checked
 * @return
 * 				- TRUE  (1) : The token sequence is correct
 *
 * 				- FALSE (0) : The token sequence is incorrect
 *
 * @note The function validates the token sequence by checking for
 * correct token syntax and relationships between tokens.
 */
int						check_token(t_token *head, t_token *tokens);
int						check_special_char(char c);
size_t					size_content_dollar(char **ptr, t_copy_env *env);
size_t					size_convert_in_quote(char *ptr, char quote);
char					*tmp_content_dollar(char *ptr, char quote);
size_t					convert_in_quote(t_minishell *minishell, char *buffer,
							char *ptr, char quote);
size_t					handle_exit_status(char **ptr, char *buffer,
							int exit_status);
int						print_exit_status(int exit_status);
size_t					handle_exit_status(char **ptr, char *buffer,
							int exit_status);
size_t					size_exit_status(int exit_status);
int						is_alpha(char *str);
char					**convert_copy_env_to_env(t_copy_env *copy_env);
int						exec(t_minishell *minishell, t_command *current);
void					execute_command(t_minishell *minishell, int fd_out);
int						free_array(char **array);
void					print_env(char **env);
void					print_copy_env(t_copy_env *copy_env);
int						ft_isalnum(int c);
size_t					handle_dollar_quoted(char **ptr,
							t_minishell *minishell);
size_t					handle_quoted_size(char *ptr, char initial_quote,
							t_minishell *minishell);
size_t					handle_dollar_unquoted(char **ptr,
							t_minishell *minishell);
size_t					handle_unquoted_size(char *ptr, t_minishell *minishell);
size_t					convert_exit_status(char *buffer, int exit_status);
size_t					handle_dollar_in_quotes(char **ptr, char *buffer,
							t_minishell *minishell, char quote);
size_t					handle_token_in_buffer(char **ptr, char *buffer,
							t_minishell *minishell);
size_t					handle_dollar_in_buffer(char **ptr, char *buffer,
							t_minishell *minishell);
int						is_valid_token(enum e_token_type type);
int						is_redirection(enum e_token_type type);
t_command				*handle_command_tok(t_token **tmp, t_command **head,
							t_command **current, int index_command);
t_redirect				*handle_redirect_tok(t_token **tmp,
							t_command *current, int index_redirect);
int						check_name_export(t_minishell *minishell, char *str);
int						add_new_env(t_copy_env *copy_env, char *value);
int						update_env_existing(t_copy_env *copy_env, char *value,
							int is_exported);
void					print_error_builtins(char *command,
							char *error_command);
int						ft_isdigit(int c);
char					*extract_var_name(char *ptr);
char					*ft_itoa(int n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					add_chunk(t_chunk **head, t_chunk **current,
							t_chunk *new_chunk);
t_chunk					*create_chunk(char *data, ssize_t rd_bytes);
int						check_isatty(t_minishell *minishell);
int						minishell_v1(t_minishell *minishell, char *input);
int						loop_readline(t_minishell *minishell);
void					setup_fork_signals(void);
void					restore_input_signals(void);
void					heredoc_signal_handler(int signum);
void					setup_heredoc_signals(struct sigaction *act,
							struct sigaction *act2);
int						write_line_to_fd(int fd, char *line,
							t_minishell *minishell);
int						handle_heredoc_cleanup(struct sigaction *act2,
							int original_stdin, char *line);
t_command				*create_empty_command(int index_command,
							t_token **tokens);
void					normalize_commands(t_command *commands);
size_t					expand_heredoc_length(t_minishell *minishell,
							char *line);
size_t					fill_expanded_heredoc(t_minishell *minishell,
							char *line, char *res);
char					*read_line_from_fd(int fd);
void					disable_echoctl(void);
int						check_input_quote(char *input);
void					enable_echoctl(void);
void					*ft_memset(void *b, int c, size_t len);

//----------------- EXEC------------------------------
// void					free_command(t_minishell *minishell);
int						check_signum(int status);
char					*return_name_builtins(enum e_builtins index_built);
char					*join_full_path(char *path, t_command *commands);
char					*get_path(t_minishell *minishell);
char					**split_path(char *path);
int						init_pipe(t_minishell *minishell,
							t_command_context *context);
int						return_index_builtins(t_command *commands);
int						exec_pipeline(t_minishell *minishell);
void					print_error_redirection(char *name_file);
t_redirect				*create_redirect_in_command(char *name_file,
							enum e_token_type type, int index_redirect);
int						redirection_output(t_minishell *minishell,
							t_redirect *redirect, int fd_out);
int						redirect_input(t_minishell *minishell,
							t_redirect *redirect, int index_builtin);
void					pipe_redirection(t_command_context *context,
							int index);
int						execute_pipeline_with_redirects(t_minishell *minishell);
int						execute_piped_command(t_minishell *minishell,
							t_command *current);
int						execute_command_with_redirects(t_minishell *minishell,
							t_command *command, t_command_context *context,
							int index);
int						execute_single_command_with_redirects(
							t_minishell *minishell, t_command *command);
void					handle_directory_error(t_minishell *minishell,
							char *arg);
void					handle_permission_error(t_minishell *minishell,
							char *arg);
void					handle_not_found_error(t_minishell *minishell,
							char *arg);
void					handle_command_not_found(t_minishell *minishell,
							char *arg);
void					handle_builtin_execution(t_minishell *minishell,
							t_command *current, int index_builtins);
void					handle_command_search(t_minishell *minishell,
							t_command *current, char **paths);
int						handle_child_process(t_minishell *minishell,
							t_command *current, t_command_context *context,
							int i);
int						create_processes(t_minishell *minishell,
							t_command_context *context);
void					close_fd_unused(t_command_context *context, int index);
int						wait_for_children(t_command_context *context);
void					close_last_pipe(t_command_context *context);
void					close_pipe_fds(t_command_context *context, int i);
int						handle_redirections(t_minishell *minishell,
							t_command *command, int index_builtin);
int						try_path_execution(char *path, t_command *current,
							t_minishell *minishell);
int						handle_absolute_path(t_command *current,
							t_minishell *minishell);
void					free_pipe(t_command_context *context);
int						init_heredoc(t_command *command,
							t_minishell *minishell);
int						count_heredocs(t_command *command);
void					free_pipe_only(t_command_context *context);
int						execute_pipeline_commands(t_minishell *minishell,
							t_command_context *context);
#endif
