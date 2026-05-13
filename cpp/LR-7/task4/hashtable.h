	#ifndef HASHTABLE_OPENADDR_H
#define HASHTABLE_OPENADDR_H

#include <QString>
#include <cstdlib>

struct HashEntry {
    int key;
    int originalHash;   // h'(key) — первичный хеш
    bool occupied;
    bool deleted;        // для корректного удаления (не используется в исследовании)
    HashEntry() : key(0), originalHash(0), occupied(false), deleted(false) {}
};

class OpenAddrHashTable {
public:
    OpenAddrHashTable(int size);
    ~OpenAddrHashTable();

    bool insert(int key);
    bool search(int key) const;
    void print(QString &out) const;   // вывод таблицы с пометками коллизий

private:
    int hash(int key) const;          // универсальная хеш-функция

    int m;
    HashEntry *table;
    long long a, b, p;                // параметры универсального хеширования
};

// Реализация
inline OpenAddrHashTable::OpenAddrHashTable(int size) : m(size) {
    table = new HashEntry[m];
    p = 2147483647LL;                 // большое простое число (2^31-1)
    // Случайные параметры a ∈ [1, p-1], b ∈ [0, p-1]
    a = 1 + rand() % (p - 1);
    b = rand() % p;
}

inline OpenAddrHashTable::~OpenAddrHashTable() { delete[] table; }

inline int OpenAddrHashTable::hash(int key) const {
    // Универсальная хеш-функция: ((a * key + b) mod p) mod m
    long long h = (a * key + b) % p;
    return static_cast<int>(h % m);
}

inline bool OpenAddrHashTable::insert(int key) {
    int h = hash(key);
    int idx = h;
    int attempts = 0;
    while (table[idx].occupied && !table[idx].deleted) {
        if (table[idx].key == key) return false;   // дубликат
        idx = (idx + 1) % m;                        // линейное пробирование
        if (++attempts >= m) return false;          // таблица заполнена
    }
    table[idx].key = key;
    table[idx].originalHash = h;                    // запоминаем исходный хеш
    table[idx].occupied = true;
    table[idx].deleted = false;
    return true;
}

inline bool OpenAddrHashTable::search(int key) const {
    int h = hash(key);
    int idx = h;
    int attempts = 0;
    while (table[idx].occupied) {
        if (!table[idx].deleted && table[idx].key == key)
            return true;
        idx = (idx + 1) % m;
        if (++attempts >= m) break;
    }
    return false;
}

inline void OpenAddrHashTable::print(QString &out) const {
    for (int i = 0; i < m; ++i) {
        if (table[i].occupied && !table[i].deleted) {
            bool collision = (table[i].originalHash != i);
            out += QString("idx %1: key=%2, h'=%3%4\n")
                       .arg(i)
                       .arg(table[i].key)
                       .arg(table[i].originalHash)
                       .arg(collision ? " (коллизия)" : "");
        } else {
            out += QString("idx %1: пусто\n").arg(i);
        }
    }
}
#endif // HASHTABLE_OPENADDR_H