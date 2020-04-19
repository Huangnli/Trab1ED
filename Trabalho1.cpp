/**************************************************
*
* Julio Huang
* Trabalho 1
* Professor: Diego Padilha Rubert
*
*/
#include <cstdio>
#include <cctype>
#include <cstring>

#define MIN 3
#define MAX 20


/* Célula de uma lista encadeada de ocorrências, armazena um inteiro */
class Ocorrencia {
  friend class ListaO;

public:
  Ocorrencia(int linha); // Construtor padrão
  ~Ocorrencia();         // Destrutor padrão

private:
  int linha;
  Ocorrencia *prox;
};


/* Lista encadeada de ocorrências, inserção realizada no fim da lista.
   Tenha o cuidado de não inserir duplicatas */
class ListaO {
public:
  ListaO();               // Construtor padrão
  ~ListaO();              // Destrutor padrão
  void insere(int linha); // Recebe um inteiro e insere na lista
  void escreve();         // Escreve os elementos da lista

private:
  Ocorrencia *inicio; // Início da lista
  Ocorrencia *fim;    // Fim da lista
};


/* Célula de uma lista encadeada de palavras, armazena uma cadeia de caracteres */
class Palavra {
  friend class ListaP;

public:
  Palavra(char p[]);      // Construtor padrão
  ~Palavra();             // Destrutor padrão
  void insere(int linha); // Insere uma ocorrência na lista de ocorrências
  void escreve();         // Escreve a palavra e suas ocorrências

private:
  char p[MAX];        // A palavra em si
  ListaO ocorrencias; // Lista de ocorrências
  Palavra *prox;      // Próxima Palavra na lista
};


/* Lista encadeada de palavras, inserção realizada no fim da lista.
   Tenha o cuidado de não inserir duplicatas */
class ListaP {
public:
  ListaP();                  // Construtor padrão
  ~ListaP();                 // Destrutor padrão
  Palavra *insere(char p[]); // Recebe uma palavra e insere na lista, devolvendo um ponteiro para o objeto inserido
  Palavra *busca(char p[]);  // Busca e devolve o objeto de uma palavra na lista
  void escreve();            // Escreve os elementos da lista

private:
  Palavra *inicio; // Início da lista
  Palavra *fim;    // Fim da lista
};


/* Tabela de dispersão que guarda um índice de palavras */
class TabelaDispersao {
public:
  TabelaDispersao();  // Construtor padrão
  ~TabelaDispersao(); // Destrutor padrão
  void escreve();     // Escreve a tabela (incluindo fator de carga)
  void novaOcorrencia(char p[], int linha); // Registra uma nova ocorrência de uma palavra
  
private:
  static const int TAMANHO = 47; // Tamanho da tabela
  ListaP tabela[TAMANHO];        // Listas da tabela

  int valor(char p[]){
    int v = 0;
    int i = 0;
    while(p[i] != '\0'){
      v = v + p[i];
      i++;
    }
    return v;
  } // Valor da palavra p
  int h(char p[]){
    return valor(p) % TAMANHO;
  }     // Função de hash
};

int main(int argc, char *argv[]){
  
  FILE *arq;
  char linha[100];
  char word[MAX] = {'\0'};
  TabelaDispersao TD;

  //Palavra palavra = new Palavra();

  int line = 1;
  int i = 0;
  int j = 0;
  
  arq = fopen(argv[1], "rt");
  while(fgets(linha, sizeof(linha), arq) != NULL){
    i = 0;
    //printf("%d\n", line);
    linha[strlen(linha) - 1] = '\0';
    while(linha[i] != '\0'){ 
      if((linha[i] >= 'A' && linha[i] <= 'Z') || (linha[i] >= 'a' && linha[i] <= 'z')){
        word[j] = tolower(linha[i]);
        i++;
        j++;
      }else{
        if(j >= MIN){
          TD.novaOcorrencia(word, line);
          //printf("%s\n", word);
        }
        for(int i = 0; i < j; i++){
          word[i] = '\0';
        }
        i++;
        j = 0;
      }
    }
    line++;
  }
  TD.escreve();
  fclose(arq);
}

Ocorrencia::Ocorrencia(int linha){
  this->linha = linha;
  prox = NULL;
}

Ocorrencia::~Ocorrencia(){
}

ListaO::ListaO(){
  inicio = NULL;
  fim = NULL;
}

ListaO::~ListaO(){
}

void ListaO::insere(int linha){
  Ocorrencia *n = new Ocorrencia(linha);
  if(inicio == NULL){
    inicio = n;
    fim = n;
  }
  else {
    n->prox = fim->prox;
    fim->prox = n;
    fim = n;
  }
}

void ListaO::escreve(){
  fim = inicio;
  while(fim != NULL){
    if(fim->prox == NULL){
      printf("%d) ", fim->linha);
      fim = fim->prox;
    }
    else{
      printf("%d, ", fim->linha);
      fim = fim->prox;
    }
  }
}

Palavra::Palavra(char p[]){
  int i = 0;
  while(p[i] != '\0'){
    this->p[i] = p[i];
    i++;
  }
  prox = NULL; 
  for(int j = 0; j < i; j++){
    this->p[i] = '\0';
  }
}

Palavra::~Palavra(){
}

void Palavra::insere(int linha){
  ocorrencias.insere(linha);
}

ListaP::ListaP(){
  inicio = NULL;
  fim = NULL;
}

void Palavra::escreve(){
  printf("%s(", p);
  ocorrencias.escreve();
}

Palavra* ListaP::insere(char p[]){
  Palavra *pal = new Palavra(p);
  if(inicio == NULL){
    inicio = pal;
    fim = pal;
    return pal;
  }
  else {
    pal->prox = fim->prox;
    fim->prox = pal;
    fim = pal;
    return pal;
  }
}

Palavra* ListaP::busca(char p[]){
  Palavra *pal = new Palavra(p);
  Palavra *inic;

  if(inicio == NULL){
    return inicio;
  }
  else{     
    inic = inicio;
    while(inic){
      if(*inic->p == *pal->p){
        //printf("%s1\n", inic->p);
        return inic;
      }
      else{
        inic = inic->prox;
      }
    }
    return NULL;
  }
}

void ListaP::escreve(){
  if(inicio == NULL){
    printf("\n");
  }
  fim = inicio;
  while(fim){
    fim->escreve();
    fim = fim->prox;
    if(fim == NULL)
      printf("\n");
  }
}

ListaP::~ListaP(){
}

TabelaDispersao::TabelaDispersao(){
}

TabelaDispersao::~TabelaDispersao(){
}

void TabelaDispersao::escreve(){
  int i = 0;
  while(i < TAMANHO){
    printf("%d: ", i);
    tabela[i].escreve();
    i++;
  }
}

void TabelaDispersao::novaOcorrencia(char p[], int linha){
  int hash;
  Palavra *pa;
  Palavra *busc;

  hash = h(p);
  busc = tabela[hash].busca(p);
  if(busc == NULL){
    pa = tabela[hash].insere(p);
    pa->insere(linha);
  }
  else{
    busc->insere(linha);
  }
}