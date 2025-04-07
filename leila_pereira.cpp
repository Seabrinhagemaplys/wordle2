#include <iostream>
#include <string>
#include <tuple>
#include <fstream>
#include <cctype>

std::string ler_arquivo_ate_linha(std::string nome_do_arquivo, int num_linha);
std::tuple<std::string, std::string> gerar_comparacao_de_strings(std::string chave, std::string string_de_tentativa, std::string letras_nao_presentes);
bool checar_letra_na_string(char letra, std::string string_a_checar);

int main() {
    //declarações
    std::string chave;
    std::string tentativa;
    std::string letras_nao_presentes;
    int num_linha;
    int vidas = 5;
    bool ganhou = false;

    //pegar a linha correta para leitura
    std::cin >> num_linha;

    //ler arquivo e salvar em chave
    chave = ler_arquivo_ate_linha("palavras.txt", num_linha);

    //saindo do código caso o usuário quiser uma linha que não exista ou seja inválida
    if(chave == ""){
        return 1;
    }

    while(vidas > 0){
        //pegar a tentativa
        std::cin >> tentativa;

        //converter string tentativa para letras maiúsculas
        for(unsigned i = 0; i < tentativa.size(); i++){
            tentativa[i] = std::toupper(tentativa[i]);
        }

        //checar se a string já é igual
        if(tentativa == chave){
            ganhou = true;
        }

        //lógica de comparação e impressão
        std::tuple<std::string, std::string> resultado_e_letras_erradas = gerar_comparacao_de_strings(chave, tentativa, letras_nao_presentes);
        std::string resultado = std::get<0>(resultado_e_letras_erradas);
        letras_nao_presentes = std::get<1>(resultado_e_letras_erradas);
        std::cout << resultado << " " << "(" << letras_nao_presentes << ")" << "\n";
        
        //diminuíndo as vidas
        vidas--;

        if(ganhou == true){
            break;
        }
    } 

    if(ganhou == false){
        std::cout << "PERDEU!" << " " << chave;
    } else {
        std::cout << "GANHOU!";
    }

    return 0;
}

std::string ler_arquivo_ate_linha(std::string nome_do_arquivo, int num_linha){
    //ajustar num_linha pois a contagem do arquivo começa em 0
    num_linha--;

    //declarações
    int numero_de_linhas_do_arq;
    std::string linha_lida;
    std::ifstream arq(nome_do_arquivo);

    //checagem
    if(!arq.is_open()){
        std::cerr << "Erro ao abrir arquivo";
        return "";
    }

    //número de linhas do arquivo
    std::getline(arq, linha_lida);
    numero_de_linhas_do_arq = stoi(linha_lida);

    if(num_linha > numero_de_linhas_do_arq || num_linha < 0){
        std::cerr << "Essa linha não existe";
        return "";
    }

    //chegando na linha correta
    for(int i = 0; i < numero_de_linhas_do_arq; i++){
        std::getline(arq, linha_lida);

        if(i == num_linha){
            return linha_lida;
        }
    }

    //fechando o arquivo
    arq.close();

    return "";
}

std::tuple<std::string, std::string> gerar_comparacao_de_strings(std::string chave, std::string string_de_tentativa, std::string letras_nao_presentes){
    //declaração
    std::string base = "*****";

    //analisando as strings
    for(unsigned i = 0; i < base.size(); i++){
        if(chave[i] == string_de_tentativa[i]){
            //caso 1: a letra está na posição correta
            base[i] = chave[i];
        } else if(chave.find(string_de_tentativa[i]) != std::string::npos){
            //caso 2: a letra está na posção incorreta
            base[i] = std::tolower(string_de_tentativa[i]);
        } else if(letras_nao_presentes.find(string_de_tentativa[i]) == std::string::npos){
            //caso 3: a letra não está na palavra
            letras_nao_presentes += string_de_tentativa[i];
        }
    }

    //criando o tuple com as duas strings
    std::tuple<std::string, std::string> tuple_resultado = std::make_tuple(base, letras_nao_presentes);

    return tuple_resultado;
}