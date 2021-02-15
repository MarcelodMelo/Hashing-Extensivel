#include <vector>
#include<Balde.hpp>
#include <string>
#include <bitset>

using namespace std;

class Diretorio{
private:
    std::vector<Balde*> _diretorio;
    size_t tamBalde;
    size_t pGlobal;
    size_t numBits;
public:

    Diretorio(size_t numBits,size_t tamBalde){
        this->tamBalde=tamBalde;
        this->numBits=numBits;
        this->pGlobal=1;
        for(size_t i = 0; i < 2; i++){
            Balde* newBalde = new Balde(tamBalde);
            this->_diretorio.push_back(newBalde);
        }
    }

    size_t getTamDiretorio(){
        return this->_diretorio.size();
    }

    size_t getTotalBaldes(){
        return this->_diretorio.size();
    }

    void imprimirDiretorio(){
        cout << "\n\nProfundidade do Diretorio = " << pGlobal<< "\n";
        cout << "Imprimindo Diretorio\n";
        size_t indice=0;
        int proGlobal = this->pGlobal;
        for(Balde* b : _diretorio){
            cout << "Balde de indice: " << indice<<" , pLocal: "<< b->getPLocal()<< " e endereco: "<< _diretorio.at(indice)<< "\n";
            b->imprimirBalde();
            cout<< "\n";
            indice++;
        }
    }

    void inserir(string pseudoChave){
        size_t indice = stoi(pseudoChave.substr(0,this->pGlobal),0,2);
        size_t pLocal = this->_diretorio[indice]->getPLocal();
        if(!this->_diretorio[indice]->baldeCheio()){
            this->_diretorio[indice]->inserirPseudoChave(pseudoChave);
        }
        else{
            if(pLocal> pGlobal){
                cout << "Tem parada errada no morro \n";
                return ;
            }
            if(pLocal == pGlobal){
                if(pGlobal <= this->numBits){
                        this->duplicarDiretorio();
                }
                else{
                    cout<< "Acabou irmão";
                    return;
                }
            }
            indice = stoi(pseudoChave.substr(0,this->pGlobal),0,2);
            this->dividirBaldes(indice);
            this->inserir(pseudoChave);
        }
    }

    void duplicarDiretorio(){
        this->pGlobal +=1;
        size_t tamDiretorio =this->getTamDiretorio();
        std::vector<Balde*> _novoDiretorio {2*tamDiretorio};
        for(size_t i = 0; i< tamDiretorio; i++){
            _novoDiretorio[2*i] = std::move(this->_diretorio[i]);
            _novoDiretorio[2*i+1] = std::move(this->_diretorio[i]);
        }
        this->_diretorio = _novoDiretorio;
    }



    void dividirBaldes(size_t indiceBalde){
        size_t newProfundidade = this->_diretorio[indiceBalde]->getPLocal() + 1;
        size_t newTamanho = this->_diretorio[indiceBalde]->getTamanho();
        Balde* newBalde = new Balde(newTamanho);

        this->_diretorio[indiceBalde]->atualizaProfundidade(newProfundidade);
        newBalde->atualizaProfundidade(newProfundidade);
        size_t tempNovoIndicePraDelecao;

        for (size_t i = 0; i < newTamanho; i++){
            std::string pseudoChaveAtual = this->_diretorio[indiceBalde]->getPseudoChave(i);
            size_t novoIndice = std::stoi(pseudoChaveAtual.substr(0, this->pGlobal), 0, 2);
            if(novoIndice != indiceBalde){
                tempNovoIndicePraDelecao = novoIndice;
                newBalde->inserirPseudoChave(std::move(pseudoChaveAtual));
                this->_diretorio[novoIndice] = newBalde;
            }
        }
        for (size_t i = 0, delecoes = 0; i < newTamanho - delecoes;){
            std::string pseudoChaveAtual = this->_diretorio[indiceBalde]->getPseudoChave(i);
            size_t novoIndice = std::stoi(pseudoChaveAtual.substr(0, this->pGlobal), nullptr, 2);
            if(novoIndice == tempNovoIndicePraDelecao){
                _diretorio[indiceBalde]->apagarPseudoChave(i);
                delecoes++;
            }
            else
                i++;
    }
}

    bool buscaPseudoChave(string pseudoChave){
        size_t indice = stoi(pseudoChave.substr(0,this->pGlobal), 0, 2);
        return this->_diretorio[indice]->buscarPseudoChave(pseudoChave);
    }

};
