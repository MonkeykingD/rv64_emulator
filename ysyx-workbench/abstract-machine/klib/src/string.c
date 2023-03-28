#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t len=0;
  while(s[len]!='\0'){
   len++;
  }
  return len;
}

char *strcpy(char *dst, const char *src) {
  char *p=dst;
  while(*src!='\0')
  {
    *p++=*src++;
  }
  *p='\0';
  return dst; 
}

char *strncpy(char *dst, const char *src, size_t n) {
  panic("Not implemented");
}

char* strcat(char* dst, const char* src) {
    strcpy(dst + strlen(dst),src);
    return dst;
}


int strcmp(const char *s1, const char *s2) {
  int i=0;
  while(s1[i]!='\0'&&s2[i]!='\0'){
    if(s1[i]!=s2[i])
    {
      return s1[i]-s2[i];
    }
    i++;
  }
  return s1[i]-s2[i];
}

int strncmp(const char *s1, const char *s2, size_t n) {
  panic("Not implemented");
}

void *memset(void *s, int c, size_t n) {
  unsigned char *p=(unsigned char *)s;
  for(size_t i=0;i<n;i++){
   *p++=(unsigned char)c;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
    char *d = out;
    const char *s = in;

    while (n--)
        *d++ = *s++;

    return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  char * S1=(char *)s1;
  char * S2=(char *)s2;  
  for(size_t i=0;i<n;i++){
    if(S1[i]!=S2[i])
    {
      return S1[i]-S2[i];
    }
  }
  return 0;
}

#endif
