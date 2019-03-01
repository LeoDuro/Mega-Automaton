//
//  Automat.hpp
//  Mega Automaton
//
//  Created by Leo Duro on 12/02/2019.
//  Copyright © 2019 Leo Duro. All rights reserved.
//

// Kjo klase nuk krijon objekte por perdoret si klase baze
//
// Cdo Automat ka:
// 1. Gjendjet (Q,q0,F) ku q0,F perfshihen ne Q.
// 2.Alfabetin.
// Ajo qe i dallon ata eshte funksioni i tranzicionit.

#ifndef Automat_hpp
#define Automat_hpp

#include <iostream>
#include <vector>
#include <string>

#include "Gjendje.hpp"
#include "Karakter.hpp"

class Automat {
protected:
    std::vector < Gjendje > gjendjet;
    std::vector < Karakter > alfabet;
    Automat(){}
public:
    void setGjendjet( const std::string &emri, bool finale, bool fillestare ){
        Gjendje gjendje;
        gjendje.setAtributet(emri, finale, fillestare);
        this -> gjendjet.push_back(gjendje);
    }
    void setAlfabet( const std::string &emer ){
        Karakter shkronje;
        shkronje.setEmri_i_shkronjes(emer);
        this -> alfabet.push_back(shkronje);
    }
    
    // get/set parametrat ne total
    void setAlfabetTotal( const std::vector < Karakter > &alfabet){
        this-> alfabet = alfabet;
    }
    void setGjendjetTotal( const std::vector < Gjendje > &gjendjet){
        this-> gjendjet = gjendjet;
    }
    std::vector < Karakter > getAlfabet(){
        return this -> alfabet;
    }
    std::vector < Gjendje > getGjendjet(){
        return this -> gjendjet;
    }
    
    // userActions
    void user_setGjendjet( const int &numri_i_gjendjeve ) {
        std::cout << "\n\nFilloi marrja e gjendjeve.\n\n";
        
        std::cout << "\n\nJep emrat e gjendjeve te Automatit\nNe formatin:  emer:string finale?:bool fillestare?:bool\n";
        std::cout << "Nje linje per cdo emer\n";
        std::cout << "Kujdes! mund te vendosesh vetem nje gjendje fillestare me pas formati do te ndryshoje ne: \n -- emer:strinfinal?:bool\n";
        std::cout << "Perdor 0 ose 1 per bool\n\n";
        std::cout << "nje shembull: Emer  finale fillestare\n";
        std::cout << "nje shembull:  A      0        0\n";
        std::cout << "nje shembull:  B      1        0\n";
        std::cout << "nje shembull:  C      0        1\n";
        std::cout << "nje shembull:  D      1\n";
        std::cout << "nje shembull:  E      1\n\n";
        std::cout << "Fillo: \n";
        
        std::string emri = ""; bool finale = false; bool fillestare = false;
        
        for (int i = 0; i < numri_i_gjendjeve; i++) {
            if (!fillestare) {
                std::cout << "Emri Finale Fillestare :\n";
                std::cin >> emri >> finale >> fillestare;
                this->setGjendjet(emri, finale, fillestare);
            }else{
                std::cout << "Emri Finale :\n";
                std::cin >> emri >> finale;
                this->setGjendjet(emri, finale, false);
            }
        }
        
        std::cout << "\nPerfundoi marrja e gjendjeve.\n\n";
    }
    void user_printGjendjet() {
        std::cout << "Gjendjet : \n          ";
        for ( int i = 0; i < gjendjet.size(); i++ ) {
            if ( gjendjet[i].isFinal() && gjendjet[i].isInitial() ) std::cout << "->!F!";
            else if ( gjendjet[i].isFinal() ) std::cout << "!F!";
            else if ( gjendjet[i].isInitial() ) std::cout << "->";
            std::cout << "[" + gjendjet[i].getname() + "]" + "  ";
        }
        std::cout <<"    \n";
    }
    void user_setAlfabet( const int &numri_i_shkronjave ) {
        std::cout<< "\n\nJepni alfabetin e automatit shkronje pas shkronje duke shtypur Enter\n\n";
        int i = 0;
        while ( i < numri_i_shkronjave ) {
            std::string emri = "";
            std::cout << "Shkruaj shkronjen e " << i+1 << " : ";
            std::cin >> emri;
            this->setAlfabet(emri);
            i++;
        }
        std::cout<<"\nPerfundoi marrja e shkronjave.\n\n";
    }
    void user_printAlfabet() {
        std::cout << "Alfabeti : \n      ";
        for ( int i = 0; i < alfabet.size(); i++ ) {
            std::cout << "["+ alfabet[i].getEmri_i_shkronjes() + "]"+"  ";
        }
        std::cout <<"   \n";
    }
    
    // metoda ndihmese te perbashketa
    int gjejIndexGjendjeFillestare(){
        for (int i = 0; i < gjendjet.size(); i++){
            if ( gjendjet[i].isInitial() ){ return i; }
        }
        return -1;
    }
    int gjejIndexShkronje( const std::string &shkronje ){
        int shkronje_index = -1; // gjejme indexin e shkronjes
        for ( int j = 0 ; j < alfabet.size(); j++ ){
            if ( alfabet[j].getEmri_i_shkronjes() == shkronje ){
                shkronje_index = j;
                break;
            }
        }
        
        if (shkronje_index == -1){
            std::cout <<"\nU gjet nje karakter qe nuk eshte pjese e alfabetit : "<< shkronje <<"\n";
            std::cout <<"Jepni nje string tjeter : \n";}
        return shkronje_index;
    }
    int gjejIndexShkronje( const Karakter &shkronje ){
        int shkronje_index = -1;
        for ( int j = 0 ; j < alfabet.size(); j++ ){
            if ( alfabet[j] == shkronje ){
                shkronje_index = j;
                break;
            }
        }
        return shkronje_index;
    }
    int gjejIndexGjendje( Gjendje &gj ){
        for (int i = 0; i < gjendjet.size(); i++) {
            if ( gj == gjendjet[i] ) return i;
        }
        return -1;
    }
    int gjejIndexGjendjeNgaTabela( const Gjendje &gj, const std::vector <Gjendje> &gjendjet ){
        for (int i = 0; i < gjendjet.size(); i++) {
            if ( gj == gjendjet[i] ) return i;
        }
        return -1;
    }
};

#endif /* Automat_hpp */
