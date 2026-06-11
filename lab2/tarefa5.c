/* Sistemas Operacionais - Laboratorio 2 - Tarefa 5
 * Eduardo Ferraz - 2024203033 */

#include <stdio.h>
#include <unistd.h>   // For the syscall functions.
#include <sys/wait.h> // For wait and related macros.

int main()
{
    pid_t pid = fork(); // Fork a child process.
    if (pid < 0)
    { // Error occurred.
        fprintf(stderr, "Fork failed!\n");
        return 1;
    }
    else if (pid == 0)
    { // Child process.
        printf("[CHILD]: PID %ld. Mande: kill -SIGUSR1 %ld\n",
               (long)getpid(), (long)getpid());
        pause(); // fica bloqueado ate chegar um sinal
    }
    else
    { // Parent process.
        int wstatus;
        wait(&wstatus);
        if (WIFSIGNALED(wstatus)) // o filho foi terminado por um sinal
            printf("[PARENT]: Child terminated by signal %d.\n", WTERMSIG(wstatus));
    }
    return 0;
}
