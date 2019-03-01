//
//  minimizim.cpp
//  Mega Automaton
//
//  Created by Leo Duro on 06/02/2019.
//  Copyright © 2019 Leo Duro. All rights reserved.
//

#include "Afd.hpp"

void Afd::vendosGjendjetSipasIndexit(const std::vector<std::vector<int> > &tabela, std::vector<Gjendje> &gjen){
    setGjendjetTotal(gjen);
    inicializoTranzicionet( int( tabela.size() ) , int( alfabet.size() ) );
    
    for ( int i = 0; i < tabela.size(); i++ ) {
        for (int j = 0; j < tabela[i].size(); j++) {
            tranzicionet[i][j] = &gjendjet[ tabela[i][j] ];
        }
    }
}


void Afd::hiqTePakapshmet(){
    std::vector <Gjendje> te_arritshme;
    te_arritshme.push_back( gjendjet[gjejIndexGjendjeFillestare()] ); // nisemi nga q0
    
    std::vector <Gjendje> perTestim = te_arritshme;
    
    while ( !perTestim.empty() ) {
        int r = int ( perTestim.size() );
        
        for (int p = 0; p < r; p++){
            
            for ( auto k : alfabet ) {
                int i = gjejIndexGjxSh( perTestim[p], k );
                if ( std::find(te_arritshme.begin(), te_arritshme.end(), gjendjet[i] ) == te_arritshme.end() ){
                    // nqs nuk gjendet te te_arritshme -t
                    // e shtojme ate dhe gjithashtu e shtojme te perTestim
                    te_arritshme.push_back(gjendjet[i]);
                    perTestim.push_back(gjendjet[i]);
                }
            }
            // pasi perfundon cikli i alfabetit
            // heqim gjendjen e fillimit nga perTestim
            perTestim.erase(perTestim.begin()); p-=1;r-=1;
        }
    }
    
    // nqs te gjitha gj jane te arritshme: return.
    if (te_arritshme.size() == gjendjet.size() ) return;
    
    // marrim indexet e tranzicioneve nga tabela e te_arritshme -ve.
    std::vector < std::vector < int > > tranz_e_arritshme (te_arritshme.size(), std::vector < int > ( alfabet.size() ) );
    for (int i = 0; i < te_arritshme.size(); i++) {
        int ind = gjejIndexGjendje(te_arritshme[i]);
        for ( int sh = 0; sh < alfabet.size(); sh++ ){
            tranz_e_arritshme[i][sh] = gjejIndexGjendjeNgaTabela( *tranzicionet[ind][sh], te_arritshme);
        }
    }
    
    vendosGjendjetSipasIndexit(tranz_e_arritshme, te_arritshme);
    
    user_printTranzicionet();
}


void shfaq_tab( const std::vector < std::vector<int> > &tabela ){
    std::cout<<"\n";
    for ( int i = 0; i < tabela.size(); i++ ) {
        for ( int j = 0; j < tabela.size(); j++ ) {
            if ( tabela[i][j] == -1 ) std::cout << "*" <<" ";
            else std::cout << tabela[i][j]<< " ";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}


std::vector < std::vector <int> > Afd::getTabelaEMinimizuar(){
    // variabla
    std::vector < std::vector <int> > tabela;
    std::vector < Gjendje > gjendjet = getGjendjet();
    std::vector < Karakter > alfabet = getAlfabet();
    std::vector < std::vector < Gjendje* > > tranzicionet = getTranzicionet();

    // inicializo tab
    for ( int i = 0; i < gjendjet.size(); i++ ) {
        std::vector<int> rresht;
        for ( int j = 0; j < gjendjet.size(); j++ ) {
            if ( i > j ) rresht.push_back(0);
            else  rresht.push_back(-1);
        }
        tabela.push_back(rresht);
    }

    // marko gjendjet final dhe !final
    for ( int i = 0; i < gjendjet.size(); i++ ) {
        for ( int j = 0; j < gjendjet.size(); j++ ) {
            if ( i > j ) {
                if ( ( gjendjet[i].isFinal() && !gjendjet[j].isFinal() ) ||
                    ( !gjendjet[i].isFinal() && gjendjet[j].isFinal() ) ) tabela[i][j] = 1;
            }
        }
    }
    
    bool flag = true;
    while (flag){

        flag = false;

        for ( int i = 0; i < gjendjet.size(); i++ ) {
            for ( int j = 0; j < gjendjet.size(); j++ ) {
                if ( i > j ) {
                    if ( tabela[i][j] == 0) {
                        for (int k = 0; k < alfabet.size(); k++) {
                            int a = gjejIndexGjxSh( gjendjet[i], alfabet[k] );
                            int b = gjejIndexGjxSh( gjendjet[j], alfabet[k] );
                            if ( tabela[a][b] == 1 || tabela[b][a] == 1 ) { tabela[i][j] = 1; flag = true; }
                        }
                    }
                }
            }
        }
        // ketu mbase mund te printojme klasat e ekuivalences
    }
    return tabela;
}


std::vector <Gjendje> Afd::getDyshet(const std::vector < std::vector <int> > &tabela ){
    std::vector <Gjendje> dyshet;
    std::vector <Gjendje> gjendjet = getGjendjet();

    for (int i = 0 ; i < tabela.size(); i++) {
        for (int j = 0; j < tabela.size(); j++) {
            if (i > j) {
                if ( tabela[i][j] == 0 ){
                    Gjendje dy;
                    dy = Gjendje::bashko(gjendjet[i], gjendjet[j]);
                    dyshet.push_back(dy);
                    dy.clearGjendje();
                }
            }
        }
    }
    
    return dyshet;
}


std::vector < Gjendje > Afd::bashkoEkuivalentet( const std::vector < Gjendje > &gjendjet_e_reja ) {
        std::vector <Karakter> alfabet = getAlfabet();
        std::vector <Gjendje> gjendjet_min = gjendjet_e_reja;
        int a = int( gjendjet_min.size() );
        int b = int( gjendjet_min.size() );
        bool flag = false;

        for ( int k = 0; k < a - 1; k++ ) {
            std::vector<Gjendje> gj1Sub = gjendjet_min[k].getSubGjendje();
            flag = false;
            for (int i = k + 1; i < b; i++) {
                std::vector<Gjendje> gj2Sub = gjendjet_min[i].getSubGjendje();

                for ( int q = 0; q < gj1Sub.size(); q++ ) {
                    for ( int w = 0; w < gj2Sub.size(); w++ ) {
                        if ( gj1Sub[q] == gj2Sub[w] ){
                            gjendjet_min.insert( gjendjet_min.begin() + k+1, Gjendje::bashko(gjendjet_min[k], gjendjet_min[i]) );
                            gjendjet_min.erase(  gjendjet_min.begin() + k );
                            gjendjet_min.erase(  gjendjet_min.begin() + i );
                            a-=1; b-=1; k-=1;
                            flag = true; break;
                        }
                    }
                    if (flag) break;
                }
                if (flag) break;
            }
        }

        return gjendjet_min;
    }


std::vector <Gjendje> Afd::shtoEkuivalentet( const std::vector < std::vector <int> > &tabela ){
    
    std::vector <Gjendje> gjendjet_e_vjetra = getGjendjet();
    
    std::vector <Gjendje> gjendjet_e_reja = bashkoEkuivalentet( getDyshet( tabela ) );
    
    // fshijme gjendjet qe jane bashkuar
    int index = int ( gjendjet_e_vjetra.size() );
    for (int i = 0 ; i < gjendjet_e_reja.size(); i++) {
        std::vector <Gjendje> subGjendjet = gjendjet_e_reja[i].getSubGjendje();
        for (int j = 0; j < subGjendjet.size(); j++) {
            for (int k = 0; k < index; k++) {
                if ( subGjendjet[j] == gjendjet_e_vjetra[k] ){
                    gjendjet_e_vjetra.erase(gjendjet_e_vjetra.begin()+k);
                    index-=1; k-=1;
                }
            }
        }
    }
    
    std::vector <Gjendje> ekuivalentet = gjendjet_e_reja;
    
    for (auto i : gjendjet_e_vjetra) {
        gjendjet_e_reja.push_back(i);
    }
    
    if ( gjendjet_e_reja.size() == getGjendjet().size() ){
        std::cout << "\nAutomati eshte unik dhe NUK MUND TE MINIMIZOHET.\n";
        return getGjendjet();
    }
    
    shfaq_tab(tabela);
    
    std::cout<< "Gjendjet ekuivalente :\n";
    for (int i = 0 ; i < ekuivalentet.size(); i++) {
        std::cout << i+1 << ". " << ekuivalentet[i].getname()<<"\n";
    }
    std::cout<<"\n";
    
    std::cout<<"Gjendjet e automatit te minimizuar jane :\n";
    for (int i = 0 ; i < gjendjet_e_reja.size(); i++) {
        std::cout << i+1 << ". "  << gjendjet_e_reja[i].getname()<<"\n";
    }
    
    return gjendjet_e_reja;
}


int Afd::gjejTranzicionetESubgjendjes( Gjendje &gjendje_n, Karakter &karakter, std::vector <Gjendje> &gjendjet_new){
    // kjo Gjendje x shkronje =  Gjendje'
    // marrim subgj nga 1 gjend_new
    // shikojme se ku shkojne keto subgj me nje karakter te caktuar ne vektorin e gjendjeve te vjetra
    // i ruajme ne nje vektor me pointera
    // kontrollojme te gjitha subgj e gjendjeve vektorit gjend_new
    // ajo gj nga gj_new qe i ka te gjitha keto subgj eshte ajo e cila kthehet si pointer
    // kthejme index te gjendja me te cilen shkon kjo gjendje me x karakter
    
    std::vector <Gjendje*> shkojne_te;
    std::vector <Gjendje> subGjendjet;
    
    if (gjendje_n.kaSubgjendje()){
        subGjendjet = gjendje_n.getSubGjendje();
    }else {
        subGjendjet.push_back(gjendje_n);
    }
    
    for ( Gjendje subGj : subGjendjet ) {
        shkojne_te.push_back( &gjendjet[ gjejIndexGjxSh( subGj, karakter.getEmri_i_shkronjes() )] );
    }
    
    bool flag = false;
    
    for ( auto g : gjendjet_new ) {
        std::vector <Gjendje> subgj;
        if (g.kaSubgjendje()){  subgj = g.getSubGjendje();}
        else { subgj.push_back(g); }
        
        for ( auto mberritese : shkojne_te ) {
            for ( auto sgj: subgj ) {
                flag = false;
                if ( *mberritese == sgj ) {
                    flag = true;
                    break; // u gjet, mos kerko me
                }
                // nqs ka 1 gjendje qe nuk eshte te sgj e gjendjet_new[x] atehere kerko te gjendjet_new[x+1]
            }
            if (!flag) break; // nqs pas iterimit  te plote nuk eshte gjetur asnje gjendje korresponduese atehere dil nga cikli
        }
        if (flag) return gjejIndexGjendjeNgaTabela(g,gjendjet_new);
        // nqs u gjet atehere ktheje , ne te kundert vazhdo iterimet
    }
//    mqs nuk u gjet asnje kthe -1
    return -1;
}


void Afd::rregTranzicionet() {
    hiqTePakapshmet();
    std::vector <Gjendje> gjendjet_new = shtoEkuivalentet( getTabelaEMinimizuar() );
    if ( gjendjet_new.size() == gjendjet.size() ) return;
    
    std::vector < std::vector <int> > tranzicionet_new( gjendjet_new.size(), std::vector<int>(alfabet.size()) );
    
    for (int i = 0; i < gjendjet_new.size(); i++){
        for (int j = 0; j < alfabet.size(); j++) {
            tranzicionet_new[i][j] = gjejTranzicionetESubgjendjes( gjendjet_new[i], alfabet[j], gjendjet_new );
        }
    }
    vendosGjendjetSipasIndexit(tranzicionet_new, gjendjet_new);
}


void Afd::minimizo() {
    this->rregTranzicionet();
    this->user_printTranzicionet();
}
