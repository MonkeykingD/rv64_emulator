#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
    va_list args;
    char buffer[10000];
    va_start(args, fmt);
    int len=vsprintf(buffer, fmt, args);
    va_end(args);
    int i = 0;
    while (i<len) {
        putch(buffer[i++]);
    }
    return len;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  int d;
  char *s;
  char *p=out;
  char c;
  char ch;
  unsigned long hex;
  int len=0;
  char buf[64];
  int width;
  while ((ch = *fmt++) != '\0') { 
    if (ch == '%') {
      ch = *fmt++;
      if(ch=='%')//"%%"
      {
        *p++=ch;
        len++;
        continue;
      }      
      width = 0;
      while (ch >= '0' && ch <= '9') {
        width = width * 10 + (ch - '0');
        ch = *fmt++;
      }
      switch (ch) { 
        case 'x':
        hex = va_arg(ap, unsigned long);
        int l=0;

      do {
        if(hex % 16>9)
        {
          buf[l++] =(hex % 16) - 10 + 'A';
        }
        else{
          buf[l++] = (hex % 16) + '0';
        }
        hex /= 16;
      } while (hex > 0);
      while(l<width)
      {
        *p++='0';
        len++;
        width--;
      }
      if(l==width){
        width--;
      }
      while (l > 0) {
        len++;
        *p++ = buf[--l];
      }
        break;
        case 'c':
        c = va_arg(ap, int);
        *p++=c;
        len++;
        break;
        case 's':
        s = va_arg(ap, char *);
        while(*s!='\0')
        {
          *p++=*s++;
          len++;
        }
        break;
        case 'd':
        l=0;
        d = va_arg(ap, int);
        if(d<0){
          *p++='-';
          len++;
          d=-d;
        }
        do {
          buf[l++] = (d % 10) + '0';
          d /= 10;
        } while (d > 0);
        while(l<width)
        {
          *p++='0';
          len++;
          width--;
        }
        if(l==width){
          width--;
        }
        while (l > 0) {
          len++;
          *p++ = buf[--l];
        }
        break;
      }
    }else
    {
      *p++=ch; 
      len++;
      continue;
    }
  }
  *p='\0';
  return len;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int len=vsprintf(out,fmt,ap);
  va_end(ap);
  return len;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
