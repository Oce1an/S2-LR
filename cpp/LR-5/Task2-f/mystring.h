#ifndef MYSTRING_H
#define MYSTRING_H

#include <cstddef>
#include <memory>

// ---------------------------------------------------------------------------
// MyString — dynamic string class (analogue of std::string)
// Uses std::unique_ptr for internal buffer (Rule of Three implemented).
// ---------------------------------------------------------------------------
class MyString
{
public:
    // ---- Iterators ----
    using iterator       = char*;
    using const_iterator = const char*;

    iterator       begin()        { return m_data.get(); }
    iterator       end()          { return m_data.get() + m_len; }
    const_iterator begin()  const { return m_data.get(); }
    const_iterator end()    const { return m_data.get() + m_len; }
    const_iterator cbegin() const { return begin(); }
    const_iterator cend()   const { return end();   }

    // ---- Constructors / Rule of Three ----
    MyString();                            // default: empty string
    MyString(const char* s);              // from C-string
    MyString(const MyString& other);      // copy constructor
    MyString& operator=(const MyString& other); // copy assignment
    ~MyString() = default;                // unique_ptr handles deallocation

    // ---- Element access ----
          char& operator[](size_t pos);
    const char& operator[](size_t pos) const;

    const char* c_str() const { return m_data ? m_data.get() : ""; }
    size_t      size()  const { return m_len; }
    bool        empty() const { return m_len == 0; }

    // ---- <cstring>-style static functions ----
    static void*  s_memcpy (void* s1, const void* s2, size_t n);
    static void*  s_memmove(void* s1, const void* s2, size_t n);
    static char*  s_strcpy (char* s1, const char* s2);
    static char*  s_strncpy(char* s1, const char* s2, size_t n);
    static char*  s_strcat (char* s1, const char* s2);
    static char*  s_strncat(char* s1, const char* s2, size_t n);
    static int    s_memcmp (const void* s1, const void* s2, size_t n);
    static int    s_strcmp (const char* s1, const char* s2);
    static int    s_strcoll(const char* s1, const char* s2);
    static int    s_strncmp(const char* s1, const char* s2, size_t n);
    static size_t s_strxfrm(char* s1, const char* s2, size_t n);
    static char*  s_strtok (char* s1, const char* s2);
    static void*  s_memset (void* s, int c, size_t n);
    static char*  s_strerror(int errnum);
    static size_t s_strlen (const char* s);

private:
    std::unique_ptr<char[]> m_data;
    size_t                  m_len;
    size_t                  m_cap;

    void allocate(size_t capacity);
};

#endif // MYSTRING_H
