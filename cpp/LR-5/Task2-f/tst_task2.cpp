#include <QtTest/QtTest>
#include "mystring.h"
#include <cstring>

class TestTask2 : public QObject
{
    Q_OBJECT

private slots:

    // ===== Constructor / copy =====

    void defaultConstructor_empty()
    {
        MyString s;
        QCOMPARE(s.size(), size_t(0));
        QVERIFY(s.empty());
        QCOMPARE(std::strcmp(s.c_str(), ""), 0);
    }

    void cstringConstructor()
    {
        MyString s("hello");
        QCOMPARE(s.size(), size_t(5));
        QCOMPARE(std::strcmp(s.c_str(), "hello"), 0);
    }

    void copyConstructor()
    {
        MyString a("world");
        MyString b(a);
        QCOMPARE(std::strcmp(b.c_str(), "world"), 0);
        // Ensure deep copy — modifying a doesn't affect b
        a[0] = 'X';
        QCOMPARE(std::strcmp(b.c_str(), "world"), 0);
    }

    void copyAssignment()
    {
        MyString a("foo");
        MyString b;
        b = a;
        QCOMPARE(std::strcmp(b.c_str(), "foo"), 0);
    }

    void selfAssignment()
    {
        MyString a("test");
        a = a;
        QCOMPARE(std::strcmp(a.c_str(), "test"), 0);
    }

    // ===== Iterator =====

    void iterator_range()
    {
        MyString s("abc");
        std::string collected(s.begin(), s.end());
        QCOMPARE(collected, std::string("abc"));
    }

    // ===== s_strlen =====

    void strlen_empty()   { QCOMPARE(MyString::s_strlen(""),     size_t(0)); }
    void strlen_hello()   { QCOMPARE(MyString::s_strlen("hello"),size_t(5)); }
    void strlen_spaces()  { QCOMPARE(MyString::s_strlen("a b"),  size_t(3)); }

    // ===== s_strcpy =====

    void strcpy_basic()
    {
        char dst[32] = {0};
        MyString::s_strcpy(dst, "hello");
        QCOMPARE(std::strcmp(dst, "hello"), 0);
    }

    void strcpy_empty()
    {
        char dst[32] = {'X','X','\0'};
        MyString::s_strcpy(dst, "");
        QCOMPARE(std::strcmp(dst, ""), 0);
    }

    // ===== s_strncpy =====

    void strncpy_partial()
    {
        char dst[32] = {0};
        MyString::s_strncpy(dst, "hello", 3);
        QCOMPARE(std::strncmp(dst, "hel", 3), 0);
    }

    void strncpy_padsZeros()
    {
        char dst[8];
        std::memset(dst, 'X', 8);
        MyString::s_strncpy(dst, "hi", 5);
        QCOMPARE(dst[2], '\0');
        QCOMPARE(dst[4], '\0');
    }

    // ===== s_strcat =====

    void strcat_basic()
    {
        char dst[32] = "hello";
        MyString::s_strcat(dst, " world");
        QCOMPARE(std::strcmp(dst, "hello world"), 0);
    }

    void strcat_emptyS1()
    {
        char dst[32] = "";
        MyString::s_strcat(dst, "abc");
        QCOMPARE(std::strcmp(dst, "abc"), 0);
    }

    // ===== s_strncat =====

    void strncat_partial()
    {
        char dst[32] = "foo";
        MyString::s_strncat(dst, "bar", 2);
        QCOMPARE(std::strcmp(dst, "fooba"), 0);
    }

    void strncat_fullAppend()
    {
        char dst[32] = "a";
        MyString::s_strncat(dst, "bcd", 10);
        QCOMPARE(std::strcmp(dst, "abcd"), 0);
    }

    // ===== s_strcmp =====

    void strcmp_equal()    { QCOMPARE(MyString::s_strcmp("abc","abc"), 0); }
    void strcmp_less()     { QVERIFY(MyString::s_strcmp("abc","abd") < 0); }
    void strcmp_greater()  { QVERIFY(MyString::s_strcmp("abd","abc") > 0); }
    void strcmp_empty()    { QCOMPARE(MyString::s_strcmp("",""), 0); }

    // ===== s_strncmp =====

    void strncmp_equal_n()
    {
        QCOMPARE(MyString::s_strncmp("abcX","abcY",3), 0);
    }

    void strncmp_differ_n()
    {
        QVERIFY(MyString::s_strncmp("abcX","abcY",4) != 0);
    }

    // ===== s_memcpy =====

    void memcpy_basic()
    {
        char src[] = "hello";
        char dst[8] = {0};
        MyString::s_memcpy(dst, src, 5);
        QCOMPARE(std::memcmp(dst, "hello", 5), 0);
    }

    void memcpy_zero()
    {
        char dst[4] = {'A','B','C','\0'};
        MyString::s_memcpy(dst, "XYZ", 0);
        QCOMPARE(dst[0], 'A'); // unchanged
    }

    // ===== s_memmove =====

    void memmove_noOverlap()
    {
        char src[] = "12345";
        char dst[8] = {0};
        MyString::s_memmove(dst, src, 5);
        QCOMPARE(std::memcmp(dst, "12345", 5), 0);
    }

    void memmove_overlap_right()
    {
        char buf[] = "abcde";
        MyString::s_memmove(buf + 2, buf, 3); // "abc" → positions 2-4
        QCOMPARE(buf[2], 'a');
        QCOMPARE(buf[3], 'b');
        QCOMPARE(buf[4], 'c');
    }

    // ===== s_memcmp =====

    void memcmp_equal()
    {
        QCOMPARE(MyString::s_memcmp("abc","abc",3), 0);
    }

    void memcmp_differ()
    {
        QVERIFY(MyString::s_memcmp("abc","abd",3) != 0);
    }

    void memcmp_zero_n()
    {
        QCOMPARE(MyString::s_memcmp("X","Y",0), 0);
    }

    // ===== s_memset =====

    void memset_basic()
    {
        char buf[6] = "hello";
        MyString::s_memset(buf, '*', 3);
        QCOMPARE(buf[0], '*');
        QCOMPARE(buf[1], '*');
        QCOMPARE(buf[2], '*');
        QCOMPARE(buf[3], 'l'); // unchanged
    }

    void memset_zero()
    {
        char buf[4] = "abc";
        MyString::s_memset(buf, 0, 3);
        QCOMPARE(buf[0], '\0');
        QCOMPARE(buf[1], '\0');
        QCOMPARE(buf[2], '\0');
    }

    // ===== s_strerror =====

    void strerror_returnsString()
    {
        char* msg = MyString::s_strerror(0);
        QVERIFY(msg != nullptr);
        QVERIFY(std::strlen(msg) > 0);
    }

    // ===== s_strtok =====

    void strtok_basic()
    {
        char buf[] = "one two three";
        char* tok = MyString::s_strtok(buf, " ");
        QCOMPARE(std::strcmp(tok, "one"), 0);
        tok = MyString::s_strtok(nullptr, " ");
        QCOMPARE(std::strcmp(tok, "two"), 0);
        tok = MyString::s_strtok(nullptr, " ");
        QCOMPARE(std::strcmp(tok, "three"), 0);
        tok = MyString::s_strtok(nullptr, " ");
        QVERIFY(tok == nullptr);
    }

    void strtok_multiDelim()
    {
        char buf[] = "a,b;c";
        char* tok = MyString::s_strtok(buf, ",;");
        QCOMPARE(std::strcmp(tok, "a"), 0);
        tok = MyString::s_strtok(nullptr, ",;");
        QCOMPARE(std::strcmp(tok, "b"), 0);
    }
};

QTEST_APPLESS_MAIN(TestTask2)
#include "tst_task2.moc"
