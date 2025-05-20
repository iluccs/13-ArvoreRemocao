#include <iostream>
#include <cstdlib> // Para system()
using namespace std;

/* -----------------------------------------------------------
   Estrutura do nó da Árvore AVL
----------------------------------------------------------- */
struct NO {
    int valor;
    NO* esq;
    NO* dir;
    int altura;       // usado para o balanceamento
};

/* Raiz da árvore */
NO* raiz = nullptr;

/* ----------------- Protótipos ----------------------------- */
// Interface principal
void menu();
void inicializar();
void inserir();
void exibir();
void exibirQuantidade();
void buscar();
void remover();

// Funções auxiliares da árvore
NO* insereArvore(NO* no, int valor);
NO* criaNO(int valor);
int   elementosArvore(NO* no);
void  exibirElementosArvore(NO* no, int espaco, bool direita);
void  buscarElementoArvore(NO* no, int valor);
NO* removerArvore(NO* no, int valor);

// Funções auxiliares de balanceamento
int   alturaNo(NO* no);
int   fatorBalanceamento(NO* no);
NO* girarDireita(NO* no);
NO* girarEsquerda(NO* no);
int   maior(int a, int b);
NO* balancearNo(NO* no);

/* ================= IMPLEMENTAÇÃO ========================= */
// ---------- Funções de interface ---------
int main() {
    menu();
}

void menu() {
    int op = 0;
    while (op != 7) {
        system("cls");                // Limpa console (Windows)
        cout << "========== Menu Arvore AVL ==========\n\n";
        cout << "1 - Inicializar Arvore\n";
        cout << "2 - Exibir quantidade de elementos\n";
        cout << "3 - Inserir elemento\n";
        cout << "4 - Remover elemento\n";
        cout << "5 - Exibir arvore\n";
        cout << "6 - Buscar elemento\n";
        cout << "7 - Sair\n\n";
        cout << "Opcao: ";
        cin >> op;

        switch (op) {
        case 1:
            inicializar();
            break;
        case 2:
            exibirQuantidade();
            break;
        case 3:
            inserir();
            break;
        case 4:
            remover();
            break;
        case 5:
            exibir();
            break;
        case 6:
            buscar();
            break;
        }

        cout << endl;
        if (op != 7) system("pause"); // Aguarda tecla (Windows)
    }
}

void inicializar() {
    raiz = nullptr;
    cout << "Arvore inicializada!\n";
}

void inserir() {
    int v;
    cout << "Digite o elemento: ";
    cin >> v;
    raiz = insereArvore(raiz, v);
}

void remover() {
    int v;
    cout << "Digite o elemento: ";
    cin >> v;
    raiz = removerArvore(raiz, v);
}

void exibirQuantidade() {
    cout << "Quantidade de elementos: "
        << elementosArvore(raiz) << "\n";
}

void exibir() {
    if (raiz == nullptr) {
        cout << "Arvore vazia!\n";
        return;
    }
    cout << "\n===== Estrutura da Arvore (raiz no topo) =====\n\n";
    exibirElementosArvore(raiz, 0, false);
}

void buscar() {
    int v;
    cout << "Digite o elemento: ";
    cin >> v;
    buscarElementoArvore(raiz, v);
}

// ---------- Criação e inserção ----------
NO* criaNO(int valor) {
    NO* novo = new NO; // Usando new em vez de malloc
    if (novo == nullptr) return nullptr; // Falha de alocação

    novo->valor = valor;
    novo->esq = nullptr;
    novo->dir = nullptr;
    novo->altura = 0;
    return novo;
}

int alturaNo(NO* no) {
    if (no == nullptr) return -1;
    return no->altura;
}

int maior(int a, int b) {
    return (a > b) ? a : b;
}

int fatorBalanceamento(NO* no) {
    if (no == nullptr) return 0;
    return alturaNo(no->esq) - alturaNo(no->dir);
}

NO* girarDireita(NO* y) {
    NO* x = y->esq;
    NO* T2 = x->dir;

    // Realiza a rotação  
    x->dir = y;
    y->esq = T2;

    // Atualiza as alturas  
    y->altura = maior(alturaNo(y->esq), alturaNo(y->dir)) + 1;
    x->altura = maior(alturaNo(x->esq), alturaNo(x->dir)) + 1;

    return x;
}

NO* girarEsquerda(NO* x) {
    NO* y = x->dir;
    NO* T2 = y->esq;

    x->dir = T2;
    y->esq = x;

    x->altura = maior(alturaNo(x->esq), alturaNo(x->dir)) + 1;
    y->altura = maior(alturaNo(y->esq), alturaNo(y->dir)) + 1;

    return y;
}

// Função auxiliar para balancear um nó AVL
NO* balancearNo(NO* no) {
    if (no == nullptr) return no;
    int fb = fatorBalanceamento(no);
    // Caso Esquerda-Esquerda
    if (fb > 1 && fatorBalanceamento(no->esq) >= 0)
        return girarDireita(no);
    // Caso Esquerda-Direita
    if (fb > 1 && fatorBalanceamento(no->esq) < 0) {
        no->esq = girarEsquerda(no->esq);
        return girarDireita(no);
    }
    // Caso Direita-Direita
    if (fb < -1 && fatorBalanceamento(no->dir) <= 0)
        return girarEsquerda(no);
    // Caso Direita-Esquerda
    if (fb < -1 && fatorBalanceamento(no->dir) > 0) {
        no->dir = girarDireita(no->dir);
        return girarEsquerda(no);
    }
    return no;
}

NO* insereArvore(NO* no, int valor) {
    if (no == nullptr) {
        return criaNO(valor);
    }
    if (valor < no->valor) {
        no->esq = insereArvore(no->esq, valor);
    }
    else if (valor > no->valor) {
        no->dir = insereArvore(no->dir, valor);
    }
    else {
        return no; // Valor já existe – não insere duplicado
    }
    no->altura = maior(alturaNo(no->esq), alturaNo(no->dir)) + 1;
    return balancearNo(no);
}

NO* removerArvore(NO* no, int valor) {
    if (no == nullptr) {
        cout << "Elemento NAO encontrado.\n";
        return no;
    }
    if (valor < no->valor) {
        no->esq = removerArvore(no->esq, valor);
    }
    else if (valor > no->valor) {
        no->dir = removerArvore(no->dir, valor);
    }
    else {
        // Caso 1: Nó sem filhos
        if (no->esq == nullptr && no->dir == nullptr) {
            delete no;
            return nullptr;
        }
        // Caso 2: Nó com apenas um filho
        else if (no->esq == nullptr) {
            NO* temp = no->dir;
            delete no;
            return temp;
        }
        else if (no->dir == nullptr) {
            NO* temp = no->esq;
            delete no;
            return temp;
        }
        // Caso 3: Nó com dois filhos
        else {
            NO* temp = no->dir;
            while (temp->esq != nullptr) {
                temp = temp->esq;
            }
            no->valor = temp->valor;
            no->dir = removerArvore(no->dir, temp->valor);
        }
    }
    no->altura = maior(alturaNo(no->esq), alturaNo(no->dir)) + 1;
    return balancearNo(no);
}

// ---------- Utilidades ----------
int elementosArvore(NO* no) {
    if (no == nullptr) return 0;
    return 1 + elementosArvore(no->esq) + elementosArvore(no->dir);
}

void exibirElementosArvore(NO* no, int espaco, bool direita) {
    if (no == nullptr) return;

    const int DIST = 6; // deslocamento entre níveis
    espaco += DIST;

    exibirElementosArvore(no->dir, espaco, true);

    cout << endl;
    for (int i = DIST; i < espaco; i++) cout << " ";

    if (direita)
        cout << "/-- ";
    else
        cout << "\\-- ";

    cout << no->valor << endl;

    exibirElementosArvore(no->esq, espaco, false);
}

void buscarElementoArvore(NO* no, int valor) {
    if (no == nullptr) {
        cout << "Elemento NAO encontrado.\n";
        return;
    }

    if (valor == no->valor) {
        cout << "Elemento encontrado!\n";
        return;
    }

    if (valor < no->valor)
        buscarElementoArvore(no->esq, valor);
    else
        buscarElementoArvore(no->dir, valor);
}
