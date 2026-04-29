#include "mystring.h"
#include <cstring>
#include <cerrno>
#include <stdexcept>
#include <locale>

// ---------------------------------------------------------------------------
// Private helper
// ---------------------------------------------------------------------------
void MyString::allocate(size_t capacity)
{
    m_cap  = capacity + 1; // +1 for null terminator
    m_data = std::make_unique<char[]>(m_cap);
    m_data[0] = '\0';
}

// ---------------------------------------------------------------------------
// Constructors / Rule of Three
// ---------------------------------------------------------------------------
MyString::MyString()
    : m_len(0)
{
    allocate(0);
}

MyString::MyString(const char* s)
{
    if (!s) s = "";
    m_len = std::strlen(s);
    allocate(m_len);
    std::memcpy(m_data.get(), s, m_len + 1);
}

MyString::MyString(const MyString& other)
    : m_len(other.m_len)
{
    allocate(m_len);
    std::memcpy(m_data.get(), other.m_data.get(), m_len + 1);
}

MyString& MyString::operator=(const MyString& other)
{
    if (this == &other) return *this;
    m_len = other.m_len;
    allocate(m_len);
    std::memcpy(m_data.get(), other.m_data.get(), m_len + 1);
    return *this;
}

// ---------------------------------------------------------------------------
// Element access
// ---------------------------------------------------------------------------
char& MyString::operator[](size_t pos)
{
    if (pos >= m_len) throw std::out_of_range("MyString::operator[]");
    return m_data[pos];
}

const char& MyString::operator[](size_t pos) const
{
    if (pos >= m_len) throw std::out_of_range("MyString::operator[] const");
    return m_data[pos];
}

// ---------------------------------------------------------------------------
// Static <cstring> implementations
// ---------------------------------------------------------------------------
void* MyString::s_memcpy(void* s1, const void* s2, size_t n)
{
    // Copy n bytes from s2 to s1 (non-overlapping)
    unsigned char*       dst = static_cast<unsigned char*>(s1);
    const unsigned char* src = static_cast<const unsigned char*>(s2);
    for (size_t i = 0; i < n; ++i)
        dst[i] = src[i];
    return s1;
}

void* MyString::s_memmove(void* s1, const void* s2, size_t n)
{
    // Safe even for overlapping regions
    unsigned char*       dst = static_cast<unsigned char*>(s1);
    const unsigned char* src = static_cast<const unsigned char*>(s2);
    if (dst < src) {
        for (size_t i = 0; i < n; ++i) dst[i] = src[i];
    } else if (dst > src) {
        for (size_t i = n; i > 0; --i) dst[i-1] = src[i-1];
    }
    return s1;
}

char* MyString::s_strcpy(char* s1, const char* s2)
{
    char* ret = s1;
    while ((*s1++ = *s2++) != '\0') {}
    return ret;
}

char* MyString::s_strncpy(char* s1, const char* s2, size_t n)
{
    char* ret = s1;
    size_t i = 0;
    while (i < n && s2[i] != '\0') { s1[i] = s2[i]; ++i; }
    while (i < n) { s1[i++] = '\0'; }
    return ret;
}

char* MyString::s_strcat(char* s1, const char* s2)
{
    char* ret = s1;
    while (*s1) ++s1;
    while ((*s1++ = *s2++) != '\0') {}
    return ret;
}

char* MyString::s_strncat(char* s1, const char* s2, size_t n)
{
    char* ret = s1;
    while (*s1) ++s1;
    size_t i = 0;
    while (i < n && s2[i] != '\0') { s1[i] = s2[i]; ++i; }
    s1[i] = '\0';
    return ret;
}

int MyString::s_memcmp(const void* s1, const void* s2, size_t n)
{
    const unsigned char* a = static_cast<const unsigned char*>(s1);
    const unsigned char* b = static_cast<const unsigned char*>(s2);
    for (size_t i = 0; i < n; ++i) {
        if (a[i] != b[i]) return static_cast<int>(a[i]) - static_cast<int>(b[i]);
    }
    return 0;
}

int MyString::s_strcmp(const char* s1, const char* s2)
{
    while (*s1 && (*s1 == *s2)) { ++s1; ++s2; }
    return static_cast<int>(static_cast<unsigned char>(*s1))
         - static_cast<int>(static_cast<unsigned char>(*s2));
}

int MyString::s_strcoll(const char* s1, const char* s2)
{
    // Locale-aware comparison — delegate to std::strcoll
    return std::strcoll(s1, s2);
}

int MyString::s_strncmp(const char* s1, const char* s2, size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        unsigned char a = static_cast<unsigned char>(s1[i]);
        unsigned char b = static_cast<unsigned char>(s2[i]);
        if (a != b) return static_cast<int>(a) - static_cast<int>(b);
        if (a == '\0') return 0;
    }
    return 0;
}

size_t MyString::s_strxfrm(char* s1, const char* s2, size_t n)
{
    return std::strxfrm(s1, s2, n);
}

char* MyString::s_strtok(char* s1, const char* s2)
{
    return std::strtok(s1, s2);
}

void* MyString::s_memset(void* s, int c, size_t n)
{
    unsigned char* p = static_cast<unsigned char*>(s);
    for (size_t i = 0; i < n; ++i) p[i] = static_cast<unsigned char>(c);
    return s;
}

char* MyString::s_strerror(int errnum)
{
    return std::strerror(errnum);
}

size_t MyString::s_strlen(const char* s)
{
    size_t n = 0;
    while (s[n]) ++n;
    return n;
}
