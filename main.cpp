#include <iostream>
#include<Diretorio.hpp>
#include<Balde.hpp>
#include<vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <time.h>
#include <random>

using namespace std;
using std::string;
std::random_device rd;
std::mt19937 gen(rd());


std::string random_string(size_t Nbits)
{
    std::uniform_int_distribution<> int1(0,1);
    string s;
    s.reserve(Nbits);
    srand (time (NULL));
    for (size_t i=0; i<Nbits; i++)
        s.push_back(int1(gen) ? '1' : '0');
    return s;
};

std::string intToBinary(size_t num , size_t b , size_t numBits)
{
    std::string r;
    size_t quant = 0;
    while(num!=0) {
        r = ( num % 2 == 0 ?"0":"1")+ r ;
        num /= 2;
        quant++;
    }
    quant = b - numBits - quant;
    for(size_t i = 0; i < quant ; i++){
        r.insert(0,"0");
    }
    return r;
}

int main()
{
    size_t m , b , n , numBits;
    size_t opcao = 1;
    size_t numBaldes=1;
    cout << "Insira o Tamanho dos Baldes : " ;
    cin >> m ;
    cout << "Insira o Numero de Bits : ";
    cin >>  b;
    for(size_t i = 0; i < b; i++){
        numBaldes=numBaldes*2;
    }


    cout <<"Escolha:\n1 - para N entradas aleatorias\n2 - para N entradas com mesmo padrao de bits\n";
    cin >> opcao;
    while(opcao == 1 || opcao == 2){
        if(opcao == 1){
            Diretorio d1(b,m);
            cout << "Escreva o numero de entradas: ";
            cin >> n;
            string pseudoChave;
            for(size_t i = 0; i < n ; i++){
                pseudoChave = random_string(b);
                while (d1.buscaPseudoChave(pseudoChave)){
                    pseudoChave = random_string(b);
                }
                cout <<"Chave" << i << " e igual a " << pseudoChave << "\n";
                d1.inserir(pseudoChave);
            }
            d1.imprimirDiretorio();
            cout<<"Para continuar aperte 1 ou 2 para repetir o procedimento em outro diretorio: ";
            cin >> opcao;
        }
        if(opcao == 2){
            Diretorio d1(b,m);
            cout << "\nEscreva o numero de entradas: ";
            cin >> n;
            cout << "Escreva o numero de bits padrao: ";
            cin >> numBits;
            string padrao = random_string(numBits);
            cout << "Padrao estabelecido como : "<< padrao <<"\n";
            for(size_t i = 0; i < n ; i++){
                string sequencia = intToBinary(i,b,numBits);
                string pseudoChave = padrao + sequencia;
                cout <<"\nChave" << i << " e igual a " << pseudoChave ;
                d1.inserir(pseudoChave);
            }
            d1.imprimirDiretorio();
            cout<<"Para continuar aperte 1 ou 2 para repetir o procedimento em outro diretorio: ";
            cin >> opcao;
        }
    }
    return 0;
}

