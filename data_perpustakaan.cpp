#include "data_perpustakaan.h"
#include <algorithm> 
#include <vector> 
#include <iostream> 
#include <string> 

using namespace std;

void createList(MultiLinkedList &L) {
    L.firstBuku = nullptr;
    L.firstPeminjam = nullptr;
}

void insertFirstBuku(MultiLinkedList &L, DataBuku dataBaru) {
    NodeBuku *newNode = new NodeBuku;
    newNode->info = dataBaru;
    newNode->listPeminjam = nullptr; 

    if (L.firstBuku == nullptr) {
        L.firstBuku = newNode;
        newNode->next = nullptr;
        newNode->prev = nullptr;
    } else {
        newNode->next = L.firstBuku;
        L.firstBuku->prev = newNode;
        newNode->prev = nullptr;
        L.firstBuku = newNode;
    }
}

void insertLastBuku(MultiLinkedList &L, DataBuku dataBaru) {
    NodeBuku *newNode = new NodeBuku;
    newNode->info = dataBaru;
    newNode->listPeminjam = nullptr;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (L.firstBuku == nullptr) {
        L.firstBuku = newNode;
    } else {
        NodeBuku *P = L.firstBuku;
        while (P->next != nullptr) {
            P = P->next;
        }
        P->next = newNode;
        newNode->prev = P;
    }
}

NodeBuku *findBuku(MultiLinkedList L, string judulBuku) {
    NodeBuku *P = L.firstBuku;
    while (P != nullptr) {
        if (P->info.judul == judulBuku) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}


void deleteBuku(MultiLinkedList &L, string judulBuku) {
    NodeBuku *PBuku = L.firstBuku;
    NodeBuku *prevBuku = nullptr;


    while (PBuku != nullptr && PBuku->info.judul != judulBuku) {
        prevBuku = PBuku;
        PBuku = PBuku->next;
    }

    if (PBuku == nullptr) {
        cout << "Buku dengan judul " << judulBuku << " tidak ditemukan." << endl;
        return;
    }

    NodeRelasi *R = PBuku->listPeminjam;
    while (R != nullptr) {
        NodePeminjam *PPeminjam = R->targetPeminjam;

        NodeRelasi *RinPeminjam = PPeminjam->listBuku;
        NodeRelasi *prevRinPeminjam = nullptr;
        
        while (RinPeminjam != nullptr) {
            if (RinPeminjam->targetBuku == PBuku) {
                if (prevRinPeminjam == nullptr) {
                    PPeminjam->listBuku = RinPeminjam->next;
                } else {
                    prevRinPeminjam->next = RinPeminjam->next;
                }

                PPeminjam->info.jumlahPinjaman--;
                break; 
            }
            prevRinPeminjam = RinPeminjam;
            RinPeminjam = RinPeminjam->next;
        }

        NodeRelasi *tempR = R;
        R = R->next;
        delete tempR;
    }
    PBuku->listPeminjam = nullptr;

    if (prevBuku == nullptr) {
        L.firstBuku = PBuku->next;
        if (L.firstBuku != nullptr) L.firstBuku->prev = nullptr;
    } else {
        prevBuku->next = PBuku->next;
        if (PBuku->next != nullptr) PBuku->next->prev = prevBuku;
    }
    delete PBuku;
    cout << "SUKSES: Buku '" << judulBuku << "' dan semua pinjamannya telah dihapus." << endl;
}

void insertFirstPeminjam(MultiLinkedList &L, DataPeminjam dataBaru) {
    NodePeminjam *newNode = new NodePeminjam;
    newNode->info = dataBaru;
    newNode->listBuku = nullptr;

    newNode->next = L.firstPeminjam;
    L.firstPeminjam = newNode;
}

void insertLastPeminjam(MultiLinkedList &L, DataPeminjam dataBaru) {
    NodePeminjam *newNode = new NodePeminjam;
    newNode->info = dataBaru;
    newNode->listBuku = nullptr;
    newNode->next = nullptr;

    if (L.firstPeminjam == nullptr) {
        L.firstPeminjam = newNode;
    } else {
        NodePeminjam *P = L.firstPeminjam;
        while (P->next != nullptr) {
            P = P->next;
        }
        P->next = newNode;
    }
}

NodePeminjam *findPeminjam(MultiLinkedList L, string idPeminjam) {
    NodePeminjam *P = L.firstPeminjam;
    while (P != nullptr) {
        if (P->info.id_peminjam == idPeminjam) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

void deletePeminjam(MultiLinkedList &L, string idPeminjam) {
    NodePeminjam *PPeminjam = L.firstPeminjam;
    NodePeminjam *prevPeminjam = nullptr;

    while (PPeminjam != nullptr && PPeminjam->info.id_peminjam != idPeminjam) {
        prevPeminjam = PPeminjam;
        PPeminjam = PPeminjam->next;
    }

    if (PPeminjam == nullptr) {
        cout << "Peminjam dengan ID " << idPeminjam << " tidak ditemukan." << endl;
        return;
    }

    NodeRelasi *R = PPeminjam->listBuku;
    while (R != nullptr) {
        NodeBuku *PBuku = R->targetBuku;

        NodeRelasi *RinBuku = PBuku->listPeminjam;
        NodeRelasi *prevRinBuku = nullptr;

        while (RinBuku != nullptr) {
            if (RinBuku->targetPeminjam == PPeminjam) {
                if (prevRinBuku == nullptr) {
                    PBuku->listPeminjam = RinBuku->next;
                } else {
                    prevRinBuku->next = RinBuku->next;
                }
                break;
            }
            prevRinBuku = RinBuku;
            RinBuku = RinBuku->next;
        }
        
        NodeRelasi *tempR = R;
        R = R->next;
        delete tempR;
    }

    if (prevPeminjam == nullptr) {
        L.firstPeminjam = PPeminjam->next;
    } else {
        prevPeminjam->next = PPeminjam->next;
    }
    delete PPeminjam;

    cout << "SUKSES: Peminjam dengan ID " << idPeminjam << " dan semua pinjamannya telah dihapus." << endl;
}

void hubungkanPinjam(MultiLinkedList &L, string idPeminjam, string judulBuku) {

    NodeBuku *PBuku = findBuku(L, judulBuku);
    NodePeminjam *PPeminjam = findPeminjam(L, idPeminjam);

    if (PBuku == nullptr || PPeminjam == nullptr) {
        cout << "Data Buku atau Peminjam tidak ditemukan." << endl;
        return;
    }

    if (PPeminjam->info.jumlahPinjaman >= 5) {
        cout << "GAGAL: Peminjam " << PPeminjam->info.nama << " sudah meminjam maksimal 5 buku." << endl;
        return;
    }

    NodeRelasi *check = PPeminjam->listBuku;
    while (check != nullptr) {
        if (check->targetBuku->info.judul == judulBuku) {
            cout << "GAGAL: Peminjam " << PPeminjam->info.nama << " sudah meminjam buku berjudul " << judulBuku << "." << endl;
            return;
        }
        check = check->next;
    }

    NodeRelasi *newRelasiBuku = new NodeRelasi;
    newRelasiBuku->targetBuku = PBuku;
    newRelasiBuku->targetPeminjam = PPeminjam;
    newRelasiBuku->next = PBuku->listPeminjam;
    PBuku->listPeminjam = newRelasiBuku;

    NodeRelasi *newRelasiPeminjam = new NodeRelasi;
    newRelasiPeminjam->targetBuku = PBuku;
    newRelasiPeminjam->targetPeminjam = PPeminjam;
    newRelasiPeminjam->next = PPeminjam->listBuku;
    PPeminjam->listBuku = newRelasiPeminjam;

    PPeminjam->info.jumlahPinjaman++;
    cout << "SUKSES: " << PPeminjam->info.nama << " meminjam buku " << PBuku->info.judul << endl;
}

void showAllData(MultiLinkedList L) {
    NodePeminjam *P = L.firstPeminjam;
    cout << "\n--- DATA KESELURUHAN PEMINJAM DAN BUKU PINJAMAN (f) ---" << endl;
    while (P != nullptr) {
        cout << "---------------------------------------------------" << endl;
        cout << "ID: " << P->info.id_peminjam << ", Nama: " << P->info.nama << " (Pinjaman: " << P->info.jumlahPinjaman << ")" << endl;
        
        NodeRelasi *R = P->listBuku;
        if (R != nullptr) {
            cout << "  -> Buku yang Dipinjam:" << endl;
            while (R != nullptr) {
                cout << "     - " << R->targetBuku->info.judul << " (Penulis: " << R->targetBuku->info.penulis << ", Tahun: " << R->targetBuku->info.tahunTerbit << ")" << endl;
                R = R->next;
            }
        } else {
            cout << "  -> Tidak meminjam buku." << endl;
        }
        P = P->next;
    }
    cout << "---------------------------------------------------" << endl;
}

void tampilkanPinjamanPeminjam(MultiLinkedList L, string idPeminjam) {
    NodePeminjam *P = findPeminjam(L, idPeminjam);

    if (P == nullptr) {
        cout << "Peminjam dengan ID " << idPeminjam << " tidak ditemukan." << endl;
        return;
    }

    cout << "\n--- DATA PINJAMAN PEMINJAM '" << P->info.nama << "' (g) ---" << endl;
    NodeRelasi *R = P->listBuku;
    if (R != nullptr) {
        while (R != nullptr) {
            cout << "- " << R->targetBuku->info.judul << " oleh " << R->targetBuku->info.penulis << endl;
            R = R->next;
        }
    } else {
        cout << P->info.nama << " tidak sedang meminjam buku." << endl;
    }
}


void tampilkanPeminjamBuku(MultiLinkedList L, string judulBuku) {
    NodeBuku *B = findBuku(L, judulBuku);

    if (B == nullptr) {
        cout << "Buku dengan judul '" << judulBuku << "' tidak ditemukan." << endl;
        return;
    }

    cout << "\n--- PEMINJAM BUKU '" << B->info.judul << "' (h) ---" << endl;
    NodeRelasi *R = B->listPeminjam;
    if (R != nullptr) {
        while (R != nullptr) {
            cout << "- " << R->targetPeminjam->info.nama << " (ID: " << R->targetPeminjam->info.id_peminjam << ")" << endl;
            R = R->next;
        }
    } else {
        cout << "Buku '" << B->info.judul << "' tidak sedang dipinjam oleh siapapun." << endl;
    }
}

void bukuPalingFavorit(MultiLinkedList L) {
    if (L.firstBuku == nullptr) {
        cout << "Tidak ada data buku di perpustakaan." << endl;
        return;
    }

    struct BukuStatistik {
        string judul;
        int count;
    };

    vector<BukuStatistik> statistik;
    NodeBuku *P = L.firstBuku;

    while (P != nullptr) {
        int count = 0;
        NodeRelasi *R = P->listPeminjam;
        while (R != nullptr) {
            count++;
            R = R->next;
        }
        statistik.push_back({P->info.judul, count});
        P = P->next;
    }

    if (statistik.empty()) return;

    sort(statistik.begin(), statistik.end(), [](const BukuStatistik& a, const BukuStatistik& b) {
        return a.count > b.count;
    });

    cout << "\n--- DATA BUKU PALING FAVORIT & TIDAK (i) ---" << endl;

    cout << "1. Buku Paling Favorit (Paling Banyak Dipinjam):" << endl;
    cout << "   -> " << statistik[0].judul << " (" << statistik[0].count << " Peminjam)" << endl;

    cout << "2. Buku Paling Tidak Favorit (Paling Sedikit Dipinjam):" << endl;
    cout << "   -> " << statistik.back().judul << " (" << statistik.back().count << " Peminjam)" << endl;
}
