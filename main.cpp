#include "data_perpustakaan.h"
#include <limits>
#include <vector>

using namespace std;

void menuUtama() {
    cout << "\n=========================================" << endl;
    cout << "      APLIKASI DATA PERPUSTAKAAN (M:N)   " << endl;
    cout << "=========================================" << endl;
    cout << "1. Tambah Data Buku (a)" << endl;
    cout << "2. Tambah Data Peminjam (b)" << endl;
    cout << "3. Hubungkan Relasi Pinjam (c)" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "4. Tampilkan Semua Peminjam Beserta Pinjamannya (f)" << endl;
    cout << "5. Tampilkan Buku yang Dipinjam oleh Peminjam Tertentu (g)" << endl;
    cout << "6. Tampilkan Peminjam yang Meminjam Buku Tertentu (h)" << endl;
    cout << "7. Hapus Data Buku (Beserta Relasinya) (d)" << endl;
    cout << "8. Hapus Data Peminjam (Beserta Relasinya) (e)" << endl;
    cout << "9. Tampilkan Buku Paling Favorit (i)" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilih menu: ";
}

int main() {
    MultiLinkedList L;
    createList(L); 

    int pilihan;
    string inputID, inputJudul;

    insertFirstBuku(L, {"Data Structures", "Smith", 2023});
    insertLastBuku(L, {"Algoritma", "Budi", 2021});
    insertLastBuku(L, {"Dasar Pemrograman", "John", 2020});
    
    insertLastPeminjam(L, {"P001", "Ani", 0});
    insertLastPeminjam(L, {"P002", "Budi", 0});
    insertFirstPeminjam(L, {"P003", "Citra", 0});

    hubungkanPinjam(L, "P001", "Data Structures");
    hubungkanPinjam(L, "P001", "Algoritma");
    hubungkanPinjam(L, "P002", "Data Structures");
    hubungkanPinjam(L, "P003", "Algoritma");
    hubungkanPinjam(L, "P003", "Dasar Pemrograman");


    do {
        menuUtama();
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            pilihan = -1; 
            continue;
        }
        cin.ignore();
        switch (pilihan) {
            case 1: { 
                DataBuku newBuku;
                cout << "Masukkan Judul Buku: ";
                getline(cin, newBuku.judul);
                cout << "Masukkan Penulis: ";
                getline(cin, newBuku.penulis);
                cout << "Masukkan Tahun Terbit (Angka): ";
                cin >> newBuku.tahunTerbit;
                insertFirstBuku(L, newBuku); 
                cout << "Buku berhasil ditambahkan." << endl;
                break;
            }
            case 2: { 
                DataPeminjam newPeminjam;
                cout << "Masukkan ID Peminjam (contoh: P004): ";
                getline(cin, newPeminjam.id_peminjam);
                cout << "Masukkan Nama Peminjam: ";
                getline(cin, newPeminjam.nama);
                newPeminjam.jumlahPinjaman = 0; 
                insertLastPeminjam(L, newPeminjam); 
                cout << "Peminjam berhasil ditambahkan." << endl;
                break;
            }
            case 3: { 
                cout << "Masukkan ID Peminjam: ";
                getline(cin, inputID);
                cout << "Masukkan Judul Buku yang dipinjam: ";
                getline(cin, inputJudul);
                hubungkanPinjam(L, inputID, inputJudul);
                break;
            }
            case 4: { 
                showAllData(L);
                break;
            }
            case 5: { 
                cout << "Masukkan ID Peminjam: ";
                getline(cin, inputID);
                tampilkanPinjamanPeminjam(L, inputID);
                break;
            }
            case 6: { 
                cout << "Masukkan Judul Buku: ";
                getline(cin, inputJudul);
                tampilkanPeminjamBuku(L, inputJudul);
                break;
            }
            case 7: { 
                cout << "Masukkan Judul Buku yang akan dihapus: ";
                getline(cin, inputJudul);
                deleteBuku(L, inputJudul);
                break;
            }
            case 8: { 
                cout << "Masukkan ID Peminjam yang akan dihapus: ";
                getline(cin, inputID);
                deletePeminjam(L, inputID);
                break;
            }
            case 9: {
                bukuPalingFavorit(L);
                break;
            }
            case 0: {
                cout << "Program selesai. Terima kasih." << endl;
                break;
            }
            default: {
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            }
        }

    } while (pilihan != 0);

    return 0;
}
