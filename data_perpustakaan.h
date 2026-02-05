#ifndef DATA_PERPUSTAKAAN_H
#define DATA_PERPUSTAKAAN_H

#include <iostream>
#include <string>

using namespace std;

struct DataBuku {
    string judul;
    string penulis;
    int tahunTerbit; 
};

struct DataPeminjam {
    string id_peminjam;
    string nama;
    int jumlahPinjaman;
};

struct NodeBuku;
struct NodePeminjam;

struct NodeRelasi {
    NodeRelasi *next;
    NodeBuku *targetBuku; 
    NodePeminjam *targetPeminjam; 
};

struct NodeBuku {
    DataBuku info;
    NodeBuku *next;
    NodeBuku *prev; 
    NodeRelasi *listPeminjam;
};

struct NodePeminjam {
    DataPeminjam info;
    NodePeminjam *next;
    NodeRelasi *listBuku;
};

struct MultiLinkedList {
    NodeBuku *firstBuku;
    NodePeminjam *firstPeminjam;
};


void createList(MultiLinkedList &L);

void insertFirstBuku(MultiLinkedList &L, DataBuku dataBaru);
void insertLastBuku(MultiLinkedList &L, DataBuku dataBaru);
NodeBuku *findBuku(MultiLinkedList L, string judulBuku);
void deleteBuku(MultiLinkedList &L, string judulBuku); 

void insertFirstPeminjam(MultiLinkedList &L, DataPeminjam dataBaru);
void insertLastPeminjam(MultiLinkedList &L, DataPeminjam dataBaru);
NodePeminjam *findPeminjam(MultiLinkedList L, string idPeminjam);
void deletePeminjam(MultiLinkedList &L, string idPeminjam);

void hubungkanPinjam(MultiLinkedList &L, string idPeminjam, string judulBuku);
void hapusRelasi(MultiLinkedList &L, string idPeminjam, string judulBuku);

void showAllData(MultiLinkedList L); 
void tampilkanPinjamanPeminjam(MultiLinkedList L, string idPeminjam); 
void tampilkanPeminjamBuku(MultiLinkedList L, string judulBuku); 

void bukuPalingFavorit(MultiLinkedList L); 

#endif
