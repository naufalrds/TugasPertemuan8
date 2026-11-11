#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;

enum Status { KOSONG, TERISI, DIHAPUS };

struct Slot {
    long long nim;
    string nama;
    Status status;
    Slot() : nim(0), nama(""), status(KOSONG) {}
};

class HashTable {
private:
    Slot tabel[SIZE];

    int hash1(long long key) const {
        return (int)(key % SIZE);
    }

    int hash2(long long key) const {
        return 7 - (int)(key % 7);
    }

    int indeks(long long key, int i) const {
        return (hash1(key) + i * hash2(key)) % SIZE;
    }

public:
    bool insert(long long nim, const string& nama) {
        int slotBebas = -1;
        for (int i = 0; i < SIZE; i++) {
            int idx = indeks(nim, i);
            if (tabel[idx].status == TERISI) {
                if (tabel[idx].nim == nim) {
                    cout << "[GAGAL] NIM " << nim << " sudah ada.\n";
                    return false;
                }
                cout << "  (collision di indeks " << idx << ", probing ke-" << i + 1 << ")\n";
            } else if (tabel[idx].status == DIHAPUS) {
                if (slotBebas == -1) slotBebas = idx;
            } else {
                if (slotBebas == -1) slotBebas = idx;
                break;
            }
        }
        if (slotBebas == -1) {
            cout << "[GAGAL] Tabel penuh / tidak ada slot terjangkau untuk NIM " << nim << ".\n";
            return false;
        }
        tabel[slotBebas].nim = nim;
        tabel[slotBebas].nama = nama;
        tabel[slotBebas].status = TERISI;
        cout << "[OK] Insert " << nim << " (" << nama << ") di indeks " << slotBebas << "\n";
        return true;
    }

    int cari(long long nim) const {
        for (int i = 0; i < SIZE; i++) {
            int idx = indeks(nim, i);
            if (tabel[idx].status == KOSONG) return -1;
            if (tabel[idx].status == TERISI && tabel[idx].nim == nim) return idx;
        }
        return -1;
    }

    void search(long long nim) const {
        int idx = cari(nim);
        if (idx == -1)
            cout << "[TIDAK DITEMUKAN] NIM " << nim << "\n";
        else
            cout << "[DITEMUKAN] NIM " << nim << " -> " << tabel[idx].nama
                 << " (indeks " << idx << ")\n";
    }

    bool remove(long long nim) {
        int idx = cari(nim);
        if (idx == -1) {
            cout << "[GAGAL] NIM " << nim << " tidak ditemukan, tidak bisa dihapus.\n";
            return false;
        }
        tabel[idx].status = DIHAPUS;
        cout << "[OK] Remove NIM " << nim << " dari indeks " << idx << "\n";
        return true;
    }

    void tampil() const {
        cout << "\n=== ISI HASH TABLE ===\n";
        for (int i = 0; i < SIZE; i++) {
            cout << "[" << i << "] ";
            if (tabel[i].status == TERISI)
                cout << tabel[i].nim << " | " << tabel[i].nama;
            else if (tabel[i].status == DIHAPUS)
                cout << "(dihapus)";
            else
                cout << "(kosong)";
            cout << "\n";
        }
    }
};

int main() {
    HashTable ht;

    cout << "--- INSERT ---\n";
    ht.insert(251401001, "Andi");
    ht.insert(251401002, "Naufal");
    ht.insert(251401011, "Budi");
    ht.insert(251401003, "Citra");
    ht.insert(251401021, "Dewi");
    ht.insert(251401005, "Eka");

    cout << "\n--- SEARCH ---\n";
    ht.search(251401002);
    ht.search(251401011);
    ht.search(251401099);

    cout << "\n--- REMOVE ---\n";
    ht.remove(251401001);
    ht.remove(251401099);
    ht.search(251401011);

    ht.tampil();
    return 0;
}
