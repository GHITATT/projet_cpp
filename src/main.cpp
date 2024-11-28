#include <proj.h>
#include <iostream>
#include <fstream>
#include "pos.h"

using namespace std;

std::string mnt_brest = "src/mnt_brest.txt";
std::string mnt_brest_proj = "src/mnt_brest_proj.txt";

int read_mnt(std::string& mnt_brest, std::string& mnt_brest_proj) {
    std::ifstream fin(mnt_brest);
    std::ofstream fout(mnt_brest_proj);

    if (!fin.is_open()){
        cout << "Erreur d’ouverture de " << mnt_brest << endl;
        return 1;
    }
    if (!fout.is_open()){
        cout << "Erreur d’ouverture de " << mnt_brest_proj << endl;
        return 1;
    }

    else{
        while (!fin.eof()){
            Pos* p = new Pos();
            fin >> *p;
            fout << *p;
            delete p;
        }
    }
    fin.close();
    fout.close();
    return 0;
}

int main() {
    bool read = read_mnt(mnt_brest, mnt_brest_proj);
    if (read == 1){
        return 1;
    }
    return 0;
}
