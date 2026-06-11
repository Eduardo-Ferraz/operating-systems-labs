#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) 
{
	if (argc != 2) 
		exit(1); //not enough arguments

	int nProcesses = atoi(argv[1]);

	if (nProcesses > 0) 
    {
        printf("Processo pai PID = %d cria %d filhos.\n", getpid(), nProcesses);
        for (int i = 0; i < nProcesses; i++) 
        {
            pid_t pid = fork();
            if (pid < 0) 
                perror("fork falhou");
            else 
                if (pid == 0) 
                {
                    printf("Novo filho: %d, PID = %d, PPID = %d\n", (i + 1), getpid(), getppid());
                    break;
                }
        
            // Processo pai continua criando filhos
            sleep(5); 
        }
    }
	return 0;
}
