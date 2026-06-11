/* Sistemas Operacionais - Laboratorio 2 - Tarefa 6
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
        printf("[CHILD]: PID %ld. Teste: kill -SIGSTOP / -SIGCONT / -SIGUSR1 %ld\n",
               (long)getpid(), (long)getpid());
        pause();
    }
    else
    { // Parent process.
        int wstatus;
        // WUNTRACED faz o waitpid retornar tambem quando o filho e suspenso.
        do
        {
            waitpid(pid, &wstatus, WUNTRACED);
            if (WIFSIGNALED(wstatus))
                printf("[PARENT]: Child terminated by signal %d.\n", WTERMSIG(wstatus));
            else if (WIFSTOPPED(wstatus))
                printf("[PARENT]: Child stopped by signal %d.\n", WSTOPSIG(wstatus));
        } while (!WIFSIGNALED(wstatus)); // repete ate o filho ser terminado
    }
    return 0;
}
