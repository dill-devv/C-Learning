#undef UNICODE
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

DWORD GetProcessID(const char* processname) {
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // first arg just does "snapshot all running processes bimbimbam" - second arg is which process but we want all so just 0, this function returns a HANDLE
	PROCESSENTRY32 pe32; // makes an empty struct for Process32First to fill with info of first process it finds
	pe32.dwSize = sizeof(PROCESSENTRY32); // this is just a formality, the struct has to know how big it is for some reason

	if (Process32First(snapshot, &pe32)) { // fills struct with info of first process found in snapshot and returns 1 if successful, this shit a bool
		do {
			if (strcmp(pe32.szExeFile, processname) == 0) { // if the exe file process name from pe32 matches the given processname, do the shit
				return pe32.th32ProcessID; // the shit being returning the processid
			}
		} while (Process32Next(snapshot, &pe32));
	}
	
	CloseHandle(snapshot); // always do thsi before return otherwise heart attack death
	return 0; // pls stop forgetting to write this me im going to kirk myself
}

int main() { // this where the shit runs
	DWORD pid = GetProcessID("Terraria.exe"); // runs GetProcessID func above and returns value as part of variable pid
	// DWORD in line above is just an unsigned long, big ass positive number in fancy terms

	HANDLE openproc = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid); // opens process using access flags and pid

	LPVOID address = (LPVOID)0x5AFE9970; // memory address that is almost definitely not fixed and will change each restart but im dumb and couldnt find the pointer
	int newamount; // declare newamount
	std::cout << "What do you want the new value to be?"; // text
	std::cin >> newamount; // input
	
	WriteProcessMemory(openproc, address, &newamount, sizeof(int), nullptr); // uses pointer of newamount to read its value and set it in terraria
	return 0;
}
