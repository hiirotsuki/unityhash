unsigned long calculate_hash(const char *str)
{
    unsigned long hash = 5381;
    int c;
    
    while((c = *str++))
	{
        hash = ((hash << 5) + hash) ^ c;
        hash &= 0xFFFFFFFF;
    }
    
    return hash;
}

#ifdef _WIN32
#include <windows.h>

void mainCRTStartup(void) 
{
    char buffer[256];
    char output[256];
    DWORD written;
    int argc;
    LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (argc != 2)
	{
        const char *usage = "Usage: program <input string>\n";
        WriteFile(hStdOut, usage, lstrlenA(usage), &written, NULL);
        ExitProcess(1);
    }

    WideCharToMultiByte(CP_ACP, 0, argv[1], -1, buffer, sizeof(buffer), NULL, NULL);
    
    unsigned long hash = calculate_hash(buffer);
    wsprintfA(output, "%s_h%lu", buffer, hash);
    WriteFile(hStdOut, output, lstrlenA(output), &written, NULL);
    WriteFile(hStdOut, "\n", 1, &written, NULL);
    
    ExitProcess(0);
}

#else
#include <stdio.h>

int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        fprintf(stderr, "Usage: program <input string>\n");
        return 1;
    }

    unsigned long hash = calculate_hash(argv[1]);
    char output[256];
    snprintf(output, sizeof(output), "%s_h%lu", argv[1], hash);
    printf("%s\n", output);

    return 0;
}
#endif
