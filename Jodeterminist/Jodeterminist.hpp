//
//  Jodeterminist.hpp
//  Mega Automaton
//
//  Created by Leo Duro on 19/02/2019.
//  Copyright © 2019 Leo Duro. All rights reserved.
//
// Kjo klase nuk krijon objekte por
// perdoret si nje klase plotesuese
// per automatet jo determinist.

#ifndef JoDeterminist_hpp
#define JoDeterminist_hpp

#include "../Automat.hpp"

class Jodeterminist : public Automat {
protected:
    std::vector< std::vector< std::vector< Gjendje* > > > tranzicionet;
    Jodeterminist(){}
public:
    // tranzicionet
    void inicializoTranzicionet(const int &nr_gjendje, const int &nr_shkronja){
        std::vector< std::vector< std::vector< Gjendje* > > > tmp(nr_gjendje, std::vector< std::vector< Gjendje* > >(nr_shkronja, std::vector< Gjendje* >(NULL) ) );
        this->tranzicionet = tmp;
    }
    void setTranzicionetTotal(std::vector< std::vector< std::vector< Gjendje* > > > &tranzicionet){
        this->tranzicionet = tranzicionet;
    }
    std::vector< std::vector< std::vector< Gjendje* > > > getTranzicionetTotal(){
        return this->tranzicionet;
    }

    // metoda ndihmese
    std::vector<Gjendje*> gjejIndexGjxSh( Gjendje &gj, const std::string &shkronje ){
        int gjendje_index  = gjejIndexGjendje(gj);
        int shkronje_index = gjejIndexShkronje(shkronje);
        
        return tranzicionet[gjendje_index][shkronje_index];
    }
    std::vector<Gjendje*> gjejIndexGjxSh( Gjendje &gj, Karakter &k ){
        int gjendje_index  = gjejIndexGjendje(gj);
        int shkronje_index = gjejIndexShkronje(k);
        
        return tranzicionet[gjendje_index][shkronje_index];
    }
    Gjendje bashkoji ( std::vector<Gjendje*> &set_gjendjesh ){
        Gjendje tmp;
        
        if (set_gjendjesh.empty()) {
            tmp.setAtributet("", false, false);
            return tmp;
        }
        tmp = *set_gjendjesh[0];
        
        for (int i = 1; i<set_gjendjesh.size(); i++) {
            tmp = Gjendje::bashko( tmp, *set_gjendjesh[i] );
        }
        
        return tmp;
    }
    void vendosTranzicionetNgaTabela( const std::vector < std::vector < std::vector<int> > > &tranzicionet_ ){
        inicializoTranzicionet( int(gjendjet.size()), int (alfabet.size()) );
        
        for (int i = 0; i< tranzicionet_.size(); i++) {
            for (int j = 0; j < tranzicionet_[i].size(); j++) {
                for (int k = 0; k < tranzicionet_[i][j].size(); k++) {
                     tranzicionet[i][j].push_back( &gjendjet[ tranzicionet_[i][j][k] ] );
                }
            }
        }
        
    }
    
    // user actions
    void user_setTranzicionet(const int &nr_gjendje, const int &nr_shkronja){
        std::cout << "Ju lutem jepni funksionin e tranzicionit per Afjd-ne.\n";
        std::cout << "Pas cdo rreshti vendosni emrin e gjendjes ku kalon automati me ate shkronje.\n";
        std::cout << "Shkruaj '-' (minus) per te perfunduar inputin me ate shkronje.\n";
        user_printGjendjet();
        inicializoTranzicionet( nr_gjendje , nr_shkronja );
        
        std::string em_tr = "";
        std::vector <Gjendje*> tmp;
        for (int i = 0 ; i < nr_gjendje; i++) {
            for (int j = 0 ; j < nr_shkronja; j++) {
                em_tr = "";
                
                while (true){
                    std::cout << gjendjet[i].getname() << " x " << alfabet[j].getEmri_i_shkronjes() << " = ";
                    std::cin >> em_tr; bool flag = false;
                    if ( em_tr == "-" ) { flag = true; break; }
                    
                    for (int k = 0; k < nr_gjendje; k++) {
                        if ( em_tr == gjendjet[k].getname() ) {
                            if ( std::find( tmp.begin(), tmp.end(), &gjendjet[k] ) == tmp.end() ){
                                tmp.push_back( &gjendjet[k] );  flag = true; break;
                            }else {
                                std::cout<< "Gjendja eshte e vendosur, vendos gjendje tjeter ose 'STP'.\n";
                                flag = true;
                                break;
                            }
                        }
                    }
                    
                    if (!flag ) { std::cout <<"Gjendja nuk ndodhet te gjendjet kujdes inputin.\n"; }
                }
                // nqs jemi ne fillim te marrjes se gjendjeve me karakter dhe user jep stp atehere push_back NULL
                //            if (tmp.empty()) tmp.push_back(NULL);
                tranzicionet[i][j] = tmp;
                tmp.clear();
            }
        }
        std::cout << "\n----------------\n";
        std::cout << "Fund tranzicionet\n";
    }
    void user_printTranzicionet(){
        std::cout << "\nTranzicionet jane: \n\n";
        user_printGjendjet();
        user_printAlfabet();
        
        for (int i = 0; i < gjendjet.size(); i++) {
            std::cout << "[" + gjendjet[i].getname() + "]";
            for (int j = 0; j < alfabet.size(); j++) {
                std::cout<< "    ";
                if ( tranzicionet[i][j].empty() ) { std::cout<< "∅"; }
                for (auto p : tranzicionet[i][j]){
                    std::cout << p->getname();
                }
                std::cout<< " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    void user_Run( const int &celes ){
        // celes 0 per afjd, 1 per e-afjd
        int nr_gjendje = 0 , nr_shkronja = 0;
        
        std::cout << "Jepni NUMRIN e gjendjeve te automatit:  ";  std::cin >> nr_gjendje;
        user_setGjendjet(nr_gjendje);
        std::cout << "Jepni NUMRIN e shkronjave:  "; std::cin >> nr_shkronja;
        user_setAlfabet(nr_shkronja);
        
        if (celes >= 1) {
            Karakter epsilon;
            epsilon.setEmri_i_shkronjes("Ɛ");
            alfabet.push_back(epsilon);
            nr_shkronja+=1;
        }
        
        user_setTranzicionet( nr_gjendje, nr_shkronja );
        user_printTranzicionet();
    }
};

#endif /* JoDeterminist_hpp */
