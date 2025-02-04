#pragma once

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int __wrap_printf(const char* format, ...);
int __wrap_vsnprintf(char* str, size_t size, const char* format, va_list args);
int __wrap_puts(const char* str);
int __wrap_putchar(int ch);
int __wrap_putc(int ch, FILE* stream);
int __wrap_snprintf(char* str, size_t size, const char* format, ...);
int __wrap_fflush(FILE* stream);

int __wrap_fgetc(FILE* stream);
int __wrap_getc(FILE* stream);
int __wrap_getchar(void);
char* __wrap_fgets(char* str, size_t n, FILE* stream);
int __wrap_ungetc(int ch, FILE* stream);

__attribute__((__noreturn__)) void __wrap___assert(const char* file, int line, const char* e);

__attribute__((__noreturn__)) void
    __wrap___assert_func(const char* file, int line, const char* func, const char* e);

#ifdef __cplusplus
}
#endif
