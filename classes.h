#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Voo;

class Astronauta {
public:
    string nome;
    string cpf;
    int idade;
    bool disponivel;
    vector<Voo*> voosParticipados;

    Astronauta(string nome, string cpf, int idade);

    void mostrarDetalhes() const;
    bool estaDisponivel() const;
    void setDisponibilidade(bool disponibilidade);
    void adicionarVoo(Voo* voo);
    void mostrarVoosParticipados() const;
};

class Voo {
public:
    int codigo;
    vector<Astronauta*> passageiros;
    bool lancado;
    bool concluido;
    bool explodiu;

    Voo(int codigo);

    void adicionarPassageiro(Astronauta* astronauta);
    void mostrarPassageiros() const;
    bool podeSerLancado() const;
    void removerPassageiro(const string& cpfPassageiro);
    void lancarVoo();
    void concluirVoo();
    bool explosao() const;
};

#endif // CLASSES_H
