#include <stddef.h>

void debug_print(const char *msg) {}
void *dtb_load(const char *path) { return NULL; }
int dtb_set_property(void *dtb, const char *prop, const void *val, size_t len) { return 0; }
size_t strlen(const char *s) { size_t n = 0; while (s && *s++) n++; return n; }
void jump_to_kernel(void *entry, void *dtb) {}
int main(void) { while (1); return 0; } 