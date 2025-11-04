#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <algorithm>

struct Palavra {
    std::string dica;
    std::string palavra;
};

struct Jogador {
    std::string nome;
    int pontos;
};

// Lista de palavras com dicas (substitui o "palavras.txt")
std::vector<Palavra> listaPalavras = {
    {"Fruta vermelha", "morango"},
    {"Animal terrestre", "elefante"},
    {"Objeto escolar", "caderno"},
    {"Animal marinho", "tubarão"},
    {"Cor primária", "vermelho"},
    {"Planeta do sistema solar", "saturno"},
    {"País da América do Sul", "brasil"},
    {"Tecnologia da informação", "computador"},
    {"Parte do corpo", "joelho"},
    {"Elemento químico gasoso", "oxigenio"}
};

// Salva o ranking no arquivo
void salvarRanking(std::string nome, int pontos) {
    std::ofstream file("ranking.txt", std::ios::app);
    file << nome << " " << pontos << "\n";
    file.close();
}

// Mostra o ranking do arquivo
void mostrarRanking() {
    std::ifstream file("ranking.txt");
    std::vector<Jogador> lista;
    std::string nome;
    int pontos;

    while (file >> nome >> pontos) {
        lista.push_back({nome, pontos});
    }

    std::sort(lista.begin(), lista.end(), [](Jogador a, Jogador b) {
        return a.pontos > b.pontos;
    });

    std::cout << "\n=== RANKING ===\n";
    for (auto &j : lista) {
        std::cout << j.nome << ": " << j.pontos << " pontos\n";
    }
    std::cout << "=================\n\n";
}

// Desenha o estado da forca em ASCII
void desenharForca(int erros) {
    std::string partes[7] = {
        "  _______\n |/      |\n |\n |\n |\n |\n_|___",
        "  _______\n |/      |\n |      (_)\n |\n |\n |\n_|___",
        "  _______\n |/      |\n |      (_)\n |       |\n |\n |\n_|___",
        "  _______\n |/      |\n |      (_)\n |      \\|\n |\n |\n_|___",
        "  _______\n |/      |\n |      (_)\n |      \\|/\n |\n |\n_|___",
        "  _______\n |/      |\n |      (_)\n |      \\|/\n |       |\n |\n_|___",
        "  _______\n |/      |\n |      (_)\n |      \\|/\n |       |\n |      / \\\n_|___"
    };
    std::cout << partes[erros] << "\n";
}

// Função principal do jogo
void novoJogo() {
    srand(time(0));
    Palavra sorteada = listaPalavras[rand() % listaPalavras.size()];
    std::string dica = sorteada.dica;
    std::string palavra = sorteada.palavra;
    std::string palavraDescoberta(palavra.size(), '_');
    std::vector<char> letrasErradas;
    int erros = 0;

    std::cout << "\nDica: " << dica << "\n";

    while (erros < 6 && palavraDescoberta != palavra) {
        desenharForca(erros);
        std::cout << "Palavra: " << palavraDescoberta << "\n";
        std::cout << "Erros: " << erros << " | Letras erradas: ";
        for (char c : letrasErradas) std::cout << c << ' ';
        std::cout << "\nDigite uma letra: ";
        char tentativa;
        std::cin >> tentativa;

        bool acertou = false;
        for (size_t i = 0; i < palavra.size(); ++i) {
            if (tolower(palavra[i]) == tolower(tentativa) && palavraDescoberta[i] == '_') {
                palavraDescoberta[i] = palavra[i];
                acertou = true;
            }
        }

        if (!acertou) {
            if (std::find(letrasErradas.begin(), letrasErradas.end(), tentativa) == letrasErradas.end()) {
                letrasErradas.push_back(tentativa);
                erros++;
            } else {
                std::cout << "Letra já errada anteriormente.\n";
            }
        }
    }

    desenharForca(erros);

    if (palavraDescoberta == palavra) {
        std::cout << "\nParabéns! Você acertou: " << palavra << "\n";
        int pontos = (palavra.size() * 10) - (erros * 5);
        std::string nome;
        std::cout << "Digite seu nome para o ranking: ";
        std::cin >> nome;
        salvarRanking(nome, pontos);
        std::cout << "Pontuação: " << pontos << "\n";
    } else {
        std::cout << "\nVocê perdeu! A palavra era: " << palavra << "\n";
    }
}

int main() {
    int escolha;
    do {
        std::cout << "=== JOGO DA FORCA ===\n";
        std::cout << "1. Novo Jogo\n2. Ver Ranking\n3. Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> escolha;

        switch (escolha) {
            case 1:
                novoJogo();
                break;
            case 2:
                mostrarRanking();
                break;
            case 3:
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "Opção inválida!\n";
        }
    } while (escolha != 3);

    return 0;
}
