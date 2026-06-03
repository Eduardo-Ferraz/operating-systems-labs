#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Lmcons.h> // Necessário para a constante UNLEN (Tamanho máximo do nome de usuário)

int glob = 6;

/* Função auxiliar para imprimir as informações do processo */
void print_process_info(const char *label, int glob_val, int var_val)
{
	char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	DWORD pid = GetCurrentProcessId();

	/* Busca o nome do usuário rodando o processo atual */
	if (!GetUserName(username, &username_len))
	{
		strcpy(username, "Desconhecido");
	}

	/* Imprime o rótulo (Pai/Filho), PID, Usuário e as variáveis */
	printf("[%s] PID = %lu, User = %s, glob = %d, var = %d\n",
		   label, pid, username, glob_val, var_val);
}

int main(int argc, char *argv[])
{
	int var = 88;

	/* Verifica se é o processo filho */
	if (argc > 1 && strcmp(argv[1], "child") == 0)
	{
		/* ***child*** */
		glob++;
		var++;
		print_process_info("CHILD ", glob, var);
		return 0;
	}

	/* Processo Pai */
	printf("before CreateProcess (simulating fork)\n");

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	char cmdLine[256];
	snprintf(cmdLine, sizeof(cmdLine), "\"%s\" child", argv[0]);

	/* Cria o processo filho */
	if (!CreateProcess(
			NULL, cmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		fprintf(stderr, "CreateProcess error: %lu\n", GetLastError());
		return -1;
	}

	/* ***parent*** */
	Sleep(15000);

	print_process_info("PARENT", glob, var);

	/* Aguarda o filho terminar e limpa a memória */
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;
}