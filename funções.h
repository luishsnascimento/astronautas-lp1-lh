#ifndef FUNCOES_H
#define FUNCOES_H

#include "classes.h"

Astronauta::Astronauta(string nome, string cpf, int idade)
    : nome(nome), cpf(cpf), idade(idade), disponivel(true) {}

void Astronauta::mostrarDetalhes() const {
    cout << "Nome: " << nome << ", CPF: " << cpf << ", Idade: " << idade;
    if (disponivel) {
        cout << " (Disponível)" << endl;
    } else {
        cout << " (Indisponível)" << endl;
    }
}

bool Astronauta::estaDisponivel() const {
    return disponivel;
}

void Astronauta::setDisponibilidade(bool disponibilidade) {
    disponivel = disponibilidade;
}

void Astronauta::adicionarVoo(Voo* voo) {
    voosParticipados.push_back(voo);
}

void Astronauta::mostrarVoosParticipados() const {
    cout << "Voos que participou: ";
    if (voosParticipados.empty()) {
        cout << "Nenhum" << endl;
    } else {
        for (const auto& voo : voosParticipados) {
            cout << voo->codigo << " ";
        }
        cout << endl;
    }
}

Voo::Voo(int codigo)
    : codigo(codigo), lancado(false), concluido(false), explodiu(false) {}

void Voo::adicionarPassageiro(Astronauta* astronauta) {
    if (concluido) {
        cout << "O voo já foi concluído. Não é possível adicionar passageiros." << endl;
        return;
    }

    if (!lancado) {
        if (astronauta->estaDisponivel()) {
            passageiros.push_back(astronauta);
            astronauta->setDisponibilidade(false);
            astronauta->adicionarVoo(this);
            cout << "Passageiro " << astronauta->nome << " adicionado ao voo com sucesso!" << endl;
        } else {
            cout << "Astronauta com CPF " << astronauta->cpf << " está em outro voo ou indisponível." << endl;
        }
    } else {
        cout << "Não é possível adicionar passageiros a um voo lançado." << endl;
    }
}

void Voo::mostrarPassageiros() const {
    cout << "Passageiros do voo:" << endl;
    if (passageiros.empty()) {
        cout << "Nenhum passageiro neste voo." << endl;
    } else {
        for (const auto& passageiro : passageiros) {
            passageiro->mostrarDetalhes();
        }
    }

    if (!lancado) {
        cout << "Situação: Em planejamento" << endl;
    } else {
        cout << "Situação: ";
        if (concluido) {
            if (explodiu) {
                cout << "Explodiu" << endl;
            } else {
                cout << "Finalizado com sucesso" << endl;
            }
        } else {
            cout << "Em curso" << endl;
        }
    }
}

bool Voo::podeSerLancado() const {
    return !lancado && !passageiros.empty();
}

void Voo::removerPassageiro(const string& cpfPassageiro) {
    if (concluido) {
        cout << "O voo já foi concluído. Não é possível remover passageiros." << endl;
        return;
    }

    if (!lancado) {
        for (auto it = passageiros.begin(); it != passageiros.end(); ++it) {
            if ((*it)->cpf == cpfPassageiro) {
                (*it)->setDisponibilidade(true);
                passageiros.erase(it);
                cout << "Passageiro com CPF " << cpfPassageiro << " removido do voo com sucesso!" << endl;
                return;
            }
        }
        cout << "CPF do passageiro não encontrado neste voo." << endl;
    } else {
        cout << "Não é possível remover passageiros de um voo lançado." << endl;
    }
}

void Voo::lancarVoo() {
    if (concluido) {
        cout << "O voo já foi concluído. Não é possível lançar novamente." << endl;
        return;
    }

    if (podeSerLancado()) {
        lancado = true;
        cout << "Voo " << codigo << " foi lançado com sucesso!" << endl;
    } else {
        cout << "Não é possível lançar o voo." << endl;
    }
}

void Voo::concluirVoo() {
    if (lancado && !concluido) {
        concluido = true;
        explodiu = explosao();
        if (explodiu) {
            for (auto passageiro : passageiros) {
                passageiro->setDisponibilidade(false);
            }
        } else {
            for (auto passageiro : passageiros) {
                passageiro->setDisponibilidade(true);
            }
        }

        mostrarPassageiros();
        cout << "Voo " << codigo << " concluído!" << endl;
    } else {
        cout << "Não é possível concluir o voo." << endl;
    }
}

bool Voo::explosao() const {
    int resultado = rand() % 2 + 1;
    return resultado == 1;
}

vector<Astronauta*> cadastrarAstronautas() {
    vector<Astronauta*> astronautas;
    string nome, cpf;
    int idade;

    cout << "Sistema de cadastro de astronautas" << endl;
    cout << endl;

    int quantidade;
    cout << "Quantos astronautas deseja cadastrar? ";
    cin >> quantidade;

    for (int i = 0; i < quantidade; ++i) {
        cout << "Digite o nome do astronauta " << i + 1 << ": ";
        cin >> nome;
        cout << "Digite o CPF do astronauta " << i + 1 << ": ";
        cin >> cpf;
        cout << "Digite a idade do astronauta " << i + 1 << ": ";
        cin >> idade;

        Astronauta* novoAstronauta = new Astronauta(nome, cpf, idade);
        astronautas.push_back(novoAstronauta);
        cout << "Astronauta cadastrado com sucesso!" << endl;
        cout << endl;
    }

    return astronautas;
}

vector<Voo> cadastrarVoos() {
    vector<Voo> voos;
    int codigo;

    cout << "Sistema de cadastro de voos" << endl;
    cout << endl;

    int quantidade;
    cout << "Quantos voos deseja cadastrar? ";
    cin >> quantidade;

    for (int i = 0; i < quantidade; ++i) {
        cout << "Digite o código do voo " << i + 1 << ": ";
        cin >> codigo;

        Voo novoVoo(codigo);
        voos.push_back(novoVoo);
        cout << "Voo cadastrado com sucesso!" << endl;
        cout << endl;
    }

    return voos;
}

void listarAstronautasMortos(const vector<Astronauta*>& astronautas) {
    cout << "Astronautas mortos:" << endl;
    bool nenhumMorto = true;
    for (const auto& astronauta : astronautas) {
        if (!astronauta->estaDisponivel()) {
            nenhumMorto = false;
            cout << "CPF: " << astronauta->cpf << ", Nome: " << astronauta->nome << endl;
            astronauta->mostrarVoosParticipados();
        }
    }
    if (nenhumMorto) {
        cout << "Nenhum astronauta morto." << endl;
    }
}

#endif // FUNCOES_H
