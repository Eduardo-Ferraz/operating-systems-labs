/* Sistemas Operacionais - Laboratorio 2 - Tarefa 9
 * Eduardo Ferraz - 2024203033
 * Uso: ./tarefa9 <executavel> [parametro]   (ex.: ./tarefa9 ls -l) */

#include <stdio.h>
#include <unistd.h>   // For the syscall functions.
#include <sys/wait.h> // For wait and related macros.

int main(int argc, char *argv[])
{
    pid_t pid = fork(); // Fork a child process.
    if (pid < 0)
    { // Error occurred.
        fprintf(stderr, "Fork failed!\n");
        return 1;
    }
    else if (pid == 0)
    { // Child process.
        // argv[1] e o executavel; &argv[1] ja e a lista de argumentos
        // terminada em NULL (pois argv[argc] == NULL).
        execvp(argv[1], &argv[1]);
        perror("execvp"); // so executa se o exec falhar
        return 1;
    }
    else
    { // Parent process.
        wait(NULL);
        printf("[PARENT]: Child finished.\n");
    }
    return 0;
}
