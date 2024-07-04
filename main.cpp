#include "classes.h"
#include "funções.h"

int main() {
    vector<Astronauta*> astronautas;
    vector<Voo> voos;

    int opcao;

    do {
        cout << "### Menu ###" << endl;
        cout << "1. Cadastrar astronautas" << endl;
        cout << "2. Cadastrar voos" << endl;
        cout << "3. Adicionar passageiro a voo" << endl;
        cout << "4. Remover passageiro de voo" << endl;
        cout << "5. Lançar voo" << endl;
        cout << "6. Concluir voo" << endl;
        cout << "7. Mostrar astronautas cadastrados" << endl;
        cout << "8. Mostrar voos cadastrados" << endl;
        cout << "9. Listar astronautas mortos" << endl;
        cout << "0. Sair do programa" << endl;
        cout << "Escolha uma opção: ";
        cin >> opcao;
        cout << endl;

        switch (opcao) {
            case 1:
                astronautas = cadastrarAstronautas();
                break;
            case 2:
                voos = cadastrarVoos();
                break;
            case 3: {
                if (!voos.empty()) {
                    int numVoo;
                    cout << "Voos disponíveis:" << endl;
                    for (size_t i = 0; i < voos.size(); ++i) {
                        cout << i + 1 << ". Voo " << voos[i].codigo << endl;
                    }
                    cout << "Selecione o número do voo: ";
                    cin >> numVoo;

                    if (numVoo >= 1 && numVoo <= voos.size()) {
                        string cpf;
                        cout << "Digite o CPF do passageiro: ";
                        cin >> cpf;

                        for (auto& astronauta : astronautas) {
                            if (astronauta->cpf == cpf) {
                                voos[numVoo - 1].adicionarPassageiro(astronauta);
                                break;
                            }
                        }
                    } else {
                        cout << "Opção inválida." << endl;
                    }
                } else {
                    cout << "Não há voos cadastrados." << endl;
                }
                break;
            }
            case 4: {
                if (!voos.empty()) {
                    int numVoo;
                    cout << "Voos disponíveis:" << endl;
                    for (size_t i = 0; i < voos.size(); ++i) {
                        cout << i + 1 << ". Voo " << voos[i].codigo << endl;
                    }
                    cout << "Selecione o número do voo: ";
                    cin >> numVoo;

                    if (numVoo >= 1 && numVoo <= voos.size()) {
                        string cpf;
                        cout << "Digite o CPF do passageiro a remover: ";
                        cin >> cpf;
                        voos[numVoo - 1].removerPassageiro(cpf);
                    } else {
                        cout << "Opção inválida." << endl;
                    }
                } else {
                    cout << "Não há voos cadastrados." << endl;
                }
                break;
            }
            case 5: {
                if (!voos.empty()) {
                    int numVoo;
                    cout << "Voos disponíveis para lançar:" << endl;
                    for (size_t i = 0; i < voos.size(); ++i) {
                        if (voos[i].podeSerLancado()) {
                            cout << i + 1 << ". Voo " << voos[i].codigo << endl;
                        }
                    }
                    cout << "Selecione o número do voo para lançar: ";
                    cin >> numVoo;

                    if (numVoo >= 1 && numVoo <= voos.size()) {
                        voos[numVoo - 1].lancarVoo();
                    } else {
                        cout << "Opção inválida ou nenhum voo disponível para lançar." << endl;
                    }
                } else {
                    cout << "Não há voos cadastrados." << endl;
                }
                break;
            }
            case 6: {
                if (!voos.empty()) {
                    int numVoo;
                    cout << "Voos disponíveis para concluir:" << endl;
                    for (size_t i = 0; i < voos.size(); ++i) {
                        if (voos[i].lancado && !voos[i].concluido) {
                            cout << i + 1 << ". Voo " << voos[i].codigo << endl;
                        }
                    }
                    cout << "Selecione o número do voo para concluir: ";
                    cin >> numVoo;

                    if (numVoo >= 1 && numVoo <= voos.size()) {
                        voos[numVoo - 1].concluirVoo();
                    } else {
                        cout << "Opção inválida ou nenhum voo disponível para concluir." << endl;
                    }
                } else {
                    cout << "Não há voos cadastrados." << endl;
                }
                break;
            }
            case 7:
                cout << "Astronautas cadastrados:" << endl;
                for (const auto& astronauta : astronautas) {
                    astronauta->mostrarDetalhes();
                }
                break;
            case 8:
                cout << "Voos cadastrados:" << endl;
                for (const auto& voo : voos) {
                    cout << "Código do voo: " << voo.codigo << endl;
                    voo.mostrarPassageiros();
                    cout << endl;
                }
                break;
            case 9:
                listarAstronautasMortos(astronautas);
                break;
            case 0:
                cout << "Encerrando o programa..." << endl;
                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
                break;
        }

        cout << endl;
    } while (opcao != 0);

    for (auto astronauta : astronautas) {
        delete astronauta;
    }

    return 0;
}
