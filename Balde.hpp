#pragma once
#include <vector>
#include <string>
using namespace std;

class Balde{
private:
    std::vector<string> _balde; //vetor de strings representando o balde
    size_t tamanho; //numero maximo de pseudoChaves dentro do Balde
    size_t pLocal; // Profundidade Local
public:
    Balde(size_t tamanho){
        this->tamanho = tamanho;
        this->pLocal = 1;
    }
 ///////////////////////////////
    size_t getPLocal(){
        return this->pLocal;
    }

    size_t getTamanho(){
        return this->tamanho;
    }

    string getPseudoChave(size_t i){
        return this->_balde[i];
    }

    bool baldeCheio(){
        if(this->_balde.size()<this->getTamanho()){
            return false;
        }
        return true;
    }
////////////////////////////////
    void inserirPseudoChave(string pseudoChave){
        if(!this->buscarPseudoChave(pseudoChave)){
            this->_balde.push_back(pseudoChave);
        }
        else
            cout <<"Essa chave ja existe!!!";
    }

    void apagarPseudoChave(string pseudoChave){ //apagando chave pela sua String
        cout << "Procurando pseudoChave '" << pseudoChave << "' dentro do balde\n";
        for(size_t i=0 ; i<this->getTamanho() ; i++){
            if(pseudoChave == _balde[i]){
                //cout<<"achei \n";
                _balde.erase(_balde.begin()+i);
                return;
            }
        }
        cout << "PseudoChave não encontrada\n";
    }

    void apagarPseudoChave(size_t i){   //apagando chave pela sua posição
        _balde.erase(_balde.begin()+i);
    }

    void imprimirBalde(){
        size_t i=0;
        for(string pChave : _balde){
            cout <<i<<"º: " << pChave << "\n";
            i += 1;
        }
        while(i < tamanho){
            cout <<i<<"º: ------" << "\n";
            i += 1;
        }
    }

    bool buscarPseudoChave(string pseudoChave){
        for(string pChave : _balde){
            if(pChave == pseudoChave){
                return true;
            }
        }
        return false;
    }

    void atualizaProfundidade(size_t novaProfundidade){
        this->pLocal = novaProfundidade;
    }
};





