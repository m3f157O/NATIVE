//see picture for properties config

#include <Windows.h>
#include <winternl.h>

extern "C" {
	NTSTATUS NTAPI NtTerminateProcess(_In_opt_ HANDLE ProcessHandle, _In_ NTSTATUS ExitStatus);
	NTSTATUS NTAPI NtDelayExecution(_In_ BOOLEAN Alertable, _In_opt_ PLARGE_INTEGER DelayInterval);
	NTSTATUS NTAPI NtDrawText(_In_ PUNICODE_STRING Text);
}

//above are the prototypes for ntdll function that we will use


#define NtCurrentProcess() ((HANDLE)(LONG_PTR)-1);  //this is a reference to the process' PID (-1 if referenced inside the process) but its broken for some reason
//neet to write (HANDLE)(LONG_PTR)-1 everytime

extern "C" void NTAPI NtProcessStartup(PPEB peb) {
	PROCESS_BASIC_INFORMATION info;
	NtQueryInformationProcess( (HANDLE)(LONG_PTR)-1 , ProcessBasicInformation, &info, sizeof(info), nullptr); //not used here, get process info from PEB 


	UNICODE_STRING text;
	RtlInitUnicodeString(&text, L"WELCOME TO HELL");
	NtDrawText(&text);							//instantiate and draw string with ntdll methods

	LARGE_INTEGER interval;
	interval.QuadPart = -10000 * 5000;
	NtDelayExecution(FALSE, &interval);
	NtTerminateProcess((HANDLE)(LONG_PTR)-1,0); //synchronous wait to see the text, and then close process

}