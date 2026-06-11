/* Sistemas Operacionais - Laboratorio 2 - Tarefa 7
 * Eduardo Ferraz - 2024203033 */

#include <stdio.h>
#include <unistd.h>   // For the syscall functions.
#include <sys/wait.h> // For wait and related macros.
#include <stdlib.h>

int main()
{
    for (int i = 0; i < 3; i++) // o pai cria 3 filhos
        if (fork() == 0)
        { // filho: dorme 2s e termina
            sleep(2);
            exit(0);
        }

    int vivos = 3;
    while (vivos > 0)
    {
        sleep(2);
        pid_t pid = waitpid(-1, NULL, WNOHANG);
        if (pid > 0)
        {
            printf("Meu filho pid=%ld terminou\n", (long)pid);
            vivos--;
        }
        else
        {
            printf("Nenhum filho terminou\n");
        }
    }
    return 0;
}
