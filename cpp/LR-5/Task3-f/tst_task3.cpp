#include <QtTest/QtTest>
#include "mybitset.h"
#include <stdexcept>

class TestTask3 : public QObject
{
    Q_OBJECT

private slots:

    // ===== Constructor =====

    void defaultConstructor_zero()
    {
        MyBitSet bs(8);
        QCOMPARE(bs.size(), size_t(8));
        QVERIFY(bs.none());
    }

    void intConstructor()
    {
        MyBitSet bs(8, 0b10110011u);
        QVERIFY(bs.test(0));
        QVERIFY(bs.test(1));
        QVERIFY(!bs.test(2));
        QVERIFY(!bs.test(3));
        QVERIFY(bs.test(4));
        QVERIFY(bs.test(5));
        QVERIFY(!bs.test(6));
        QVERIFY(bs.test(7));
    }

    void emptyBitset()
    {
        MyBitSet bs(0);
        QCOMPARE(bs.size(), size_t(0));
        QVERIFY(bs.empty());
        QVERIFY(bs.none());
        QVERIFY(bs.all());  // vacuously true
    }

    // ===== test / operator[] =====

    void test_outOfRange_throws()
    {
        MyBitSet bs(4);
        QVERIFY_THROWS_EXCEPTION(std::out_of_range, bs.test(4));
    }

    void operatorBracket_read()
    {
        MyBitSet bs(8, 0b00000001u);
        QVERIFY(static_cast<bool>(bs[0]));
        QVERIFY(!static_cast<bool>(bs[1]));
    }

    void operatorBracket_write()
    {
        MyBitSet bs(8);
        bs[3] = true;
        QVERIFY(bs.test(3));
        bs[3] = false;
        QVERIFY(!bs.test(3));
    }

    // ===== set / reset / flip — single bit =====

    void set_single()
    {
        MyBitSet bs(8);
        bs.set(2);
        QVERIFY(bs.test(2));
        QVERIFY(!bs.test(1));
    }

    void reset_single()
    {
        MyBitSet bs(8, 0xFF);
        bs.reset(5);
        QVERIFY(!bs.test(5));
        QVERIFY(bs.test(4));
    }

    void flip_single()
    {
        MyBitSet bs(8);
        bs.flip(0);
        QVERIFY(bs.test(0));
        bs.flip(0);
        QVERIFY(!bs.test(0));
    }

    void set_outOfRange_throws()
    {
        MyBitSet bs(4);
        QVERIFY_THROWS_EXCEPTION(std::out_of_range, bs.set(4));
    }

    void reset_outOfRange_throws()
    {
        MyBitSet bs(4);
        QVERIFY_THROWS_EXCEPTION(std::out_of_range, bs.reset(10));
    }

    // ===== set / reset / flip — bulk =====

    void setAll()
    {
        MyBitSet bs(10);
        bs.set();
        QVERIFY(bs.all());
        QCOMPARE(bs.count(), size_t(10));
    }

    void resetAll()
    {
        MyBitSet bs(10, 0xFFFFu);
        bs.reset();
        QVERIFY(bs.none());
        QCOMPARE(bs.count(), size_t(0));
    }

    void flipAll()
    {
        MyBitSet bs(4);
        bs.flip();
        QCOMPARE(bs.count(), size_t(4));
        bs.flip();
        QCOMPARE(bs.count(), size_t(0));
    }

    // ===== all / any / none / count =====

    void all_trueWhenAllSet()
    {
        MyBitSet bs(5);
        bs.set();
        QVERIFY(bs.all());
    }

    void all_falseWhenOneMissing()
    {
        MyBitSet bs(5);
        bs.set();
        bs.reset(2);
        QVERIFY(!bs.all());
    }

    void any_falseWhenNone()
    {
        MyBitSet bs(5);
        QVERIFY(!bs.any());
    }

    void any_trueWhenOneBit()
    {
        MyBitSet bs(5);
        bs.set(3);
        QVERIFY(bs.any());
    }

    void none_true()
    {
        MyBitSet bs(5);
        QVERIFY(bs.none());
    }

    void none_false()
    {
        MyBitSet bs(5);
        bs.set(1);
        QVERIFY(!bs.none());
    }

    void count_zero()     { MyBitSet bs(8); QCOMPARE(bs.count(), size_t(0)); }
    void count_one()      { MyBitSet bs(8); bs.set(4); QCOMPARE(bs.count(), size_t(1)); }
    void count_all()      { MyBitSet bs(8); bs.set(); QCOMPARE(bs.count(), size_t(8)); }
    void count_pattern()  {
        MyBitSet bs(8, 0b10101010u);
        QCOMPARE(bs.count(), size_t(4));
    }

    // ===== Bitwise operators =====

    void op_not()
    {
        MyBitSet bs(8, 0b11001100u);
        MyBitSet r = ~bs;
        QCOMPARE(r.count(), size_t(4));
        QVERIFY(!r.test(7)); // bit 7 was 1 → now 0
        QVERIFY(r.test(6));  // bit 6 was 0 → now 1
    }

    void op_and()
    {
        MyBitSet a(8, 0b11001100u);
        MyBitSet b(8, 0b10101010u);
        MyBitSet r = a & b;
        // 11001100 & 10101010 = 10001000
        QVERIFY(r.test(3));
        QVERIFY(r.test(7));
        QVERIFY(!r.test(1));
        QVERIFY(!r.test(5));
    }

    void op_or()
    {
        MyBitSet a(8, 0b11001100u);
        MyBitSet b(8, 0b00110011u);
        MyBitSet r = a | b;
        // 11001100 | 00110011 = 11111111
        QVERIFY(r.all());
    }

    // ===== Conversions =====

    void to_string_zero()
    {
        MyBitSet bs(4);
        QCOMPARE(bs.to_string(), std::string("0000"));
    }

    void to_string_all()
    {
        MyBitSet bs(4);
        bs.set();
        QCOMPARE(bs.to_string(), std::string("1111"));
    }

    void to_string_pattern()
    {
        MyBitSet bs(8, 0b10110010u);
        // to_string is MSB-first: bit7..bit0
        std::string s = bs.to_string();
        QCOMPARE(s.length(), size_t(8));
        QCOMPARE(s[0], '1'); // bit 7
        QCOMPARE(s[7], '0'); // bit 0
    }

    void to_ulong_basic()
    {
        MyBitSet bs(8, 42u);
        QCOMPARE(bs.to_ulong(), static_cast<unsigned long>(42));
    }

    void to_ullong_basic()
    {
        MyBitSet bs(8, 255u);
        QCOMPARE(bs.to_ullong(), static_cast<unsigned long long>(255));
    }

    void to_ulong_zero()
    {
        MyBitSet bs(8);
        QCOMPARE(bs.to_ulong(), static_cast<unsigned long>(0));
    }

    // ===== Large BitSet (tests O(N/32) ops) =====

    void large_setAndCount()
    {
        const size_t N = 1000;
        MyBitSet bs(N);
        bs.set();
        QVERIFY(bs.all());
        QCOMPARE(bs.count(), N);
        bs.reset();
        QVERIFY(bs.none());
    }

    void large_flipAndCount()
    {
        const size_t N = 64;
        MyBitSet bs(N);
        bs.flip();
        QCOMPARE(bs.count(), N);
    }
};

QTEST_APPLESS_MAIN(TestTask3)
#include "tst_task3.moc"
