#include <iostream>
#include <windows.h>
#include <tlhelp32.h> // https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/


using namespace std;


void PrintProcesses() {
    // Function that creates a snapshot of the current processes
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot == INVALID_HANDLE_VALUE) {
        cout << "Error creating process snapshot!" << endl;
        return;
    }

    PROCESSENTRY32 processEntry; // Storing information about the process
    processEntry.dwSize = sizeof(PROCESSENTRY32); // Set the size of the 'PROCESSENTRY32' structure in the 'dwSize' member

    // Getting information about the first process in the image
    if (Process32First(snapshot, &processEntry)) {
       cout << "Running processes:" << endl;
        do {
            cout << "ID: " << processEntry.th32ProcessID << "\tName: " << processEntry.szExeFile << endl;
        } while (Process32Next(snapshot, &processEntry));
    }

    // Close the process snapshot descriptor
    CloseHandle(snapshot);
}

void KillProcess (DWORD processId) {
    HANDLE processHandle = OpenProcess(PROCESS_TERMINATE, FALSE, processId);
    if (processHandle == nullptr) {
        cout << &"Error when opening a file!" [processId] << endl;
    }
    if (TerminateProcess(processHandle, 0)) {
        cout << "Process successful stopped!" << endl;
    } else {
        cout << "Error with stopping process!" << endl;
    }
}

void menu() {
    cout << "NOSIKOV TASK COMMANDER / 11.07.23" << endl;
    cout << "1. Display running processes." << endl;
    cout << "2. Stop a process." << endl;
}

int main() {
    menu();

    while (true) {
        int choice;
        cin >> choice;

        if (choice == 1) {
            PrintProcesses();
        } else if (choice == 2) {
            cout << "Enter the process ID to stop:";
            DWORD processId;
            cin >> processId;
            KillProcess(processId);
        } else {
            cout << "Invalid choice. Please try again." << endl;
            return (0);
        }

        return (0);
    }
}