#include <iostream>
#include <string>
#include <fstream>
#include<map>

using namespace ::std;

string descubrapalavra(int listnumber){
    ifstream entrada("palavras.txt");
    int conta = 0;
    string linha;
    string palavra;
    
    while(getline(entrada, linha)){
        if(conta == listnumber){
            palavra = linha;
        }
        conta ++;
    }
    return palavra;

}
int checarpalavra(string coronho, string letra, string& palavramisterio){
    if(coronho == letra){
        palavramisterio = letra;
        return 5;
    }
     return 0;
}
string checarpalavra2(string coronho, string letra, string& palavramisterio, string& exc){
    for(int i = 0; i<5; i++){
        if(coronho[i] == letra[i]){
            palavramisterio[i] = coronho[i];
        }else{
            size_t index = coronho.find(letra[i]);
            if (index == std::string::npos){
                size_t comp = exc.find(letra[i]);
                if (comp == std::string::npos){
                  exc.push_back(letra[i]);  
                }
            }else{
                palavramisterio[i] = tolower(letra[i]);
            }
        }
    }
    return exc;
}

int main() {
    int listnumber;
    int vidas = 5;
    string palavra;
    string letra;
    string extra;
    string palavramisterio = "*****";
    string exc ="";
    
    cout << "Escolha um numero de 1 a 40 analogo a sua palavra:"<< endl;
    cin >> listnumber;
   
    if(listnumber < 0 || listnumber > 40){
        cout << "Temos somente 40 palavras!"<< endl;
    }
    palavra = descubrapalavra(listnumber);
    cout<< palavramisterio<<endl;
    while(vidas >0){
        cin >> letra;
        int resultado = checarpalavra(palavra,letra, palavramisterio);
        extra = checarpalavra2(palavra,letra, palavramisterio, exc);
            if(resultado == 0){
                cout << palavramisterio << "("<< extra<< ")" <<endl;
                    palavramisterio = "*****";
                    vidas --;
    }else if(resultado == 5){
        cout <<palavra<< "("<< extra<< ")" << endl<< "GANHOU!"<<endl;   
        return 0;
       }else{
        continue;
       }
       if(vidas == 0){
           cout << "PERDEU!"<< palavra;
       }
    }

    
    
    return 0;
}