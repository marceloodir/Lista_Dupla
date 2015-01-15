#include <stdlib.h>
#include <stdio.h>

struct ListaDuplaNo {
    int x;
    struct ListaDuplaNo *proximo,*anterior;
};
struct ListaDupla {
    struct ListaDuplaNo *inicio,*fim;
};

//Ordenado Crescente
void inserirOrdenado(struct ListaDupla * lista, int n) {
	struct ListaDupla *minhasListas;
	struct ListaDuplaNo *umaLista, *eachLista;
	int valor = n;
	minhasListas = lista;

	//criando celula
	umaLista = malloc(sizeof(struct ListaDuplaNo));
	umaLista->x = valor;
	umaLista->anterior = 0;
	umaLista->proximo = 0;

	//se a lista estiver vazia...
	if(minhasListas->inicio == 0 && minhasListas->fim == 0) {
		minhasListas->inicio = umaLista;
		minhasListas->fim = umaLista;
	}else{
		for(eachLista = minhasListas->inicio; eachLista != 0; eachLista = eachLista->proximo) {

			if(umaLista->x <= eachLista->x) {
				if(eachLista == minhasListas->inicio) {
					eachLista->anterior = umaLista;
					umaLista->proximo = eachLista;
					umaLista->anterior = 0;
					minhasListas->inicio = umaLista;
					break;
				}else{
					umaLista->proximo = eachLista;
					umaLista->anterior = eachLista->anterior;
					eachLista->anterior->proximo = umaLista;
					eachLista->anterior = umaLista;
					break;
				}
			}else{
				if(eachLista == minhasListas->fim) {
					eachLista->proximo = umaLista;
					umaLista->anterior = eachLista;
					umaLista->proximo = 0;
					minhasListas->fim = umaLista;
					break;
				}
			}
		}
	}
}

void inverter(struct ListaDupla * lista) {
	struct ListaDupla *minhasListas;
	struct ListaDuplaNo *eachLista;
	struct ListaDuplaNo *tmp;
	minhasListas = lista;

	for(eachLista = minhasListas->inicio;eachLista != 0;) {

		if(eachLista == minhasListas->inicio && eachLista == minhasListas->fim) {
			//lista de único elemento, nada a fazer;
			break;
		}else{
			tmp = eachLista->proximo;
			eachLista->proximo = eachLista->anterior;
			eachLista->anterior = tmp;
			eachLista = eachLista->anterior;
		}
	}

	tmp = minhasListas->inicio;
	minhasListas->inicio = minhasListas->fim;
	minhasListas->fim = tmp;
}

void removerDuplicados(struct ListaDupla * lista) {

	struct ListaDupla *minhasListas;
	struct ListaDuplaNo *eachLista;
	struct ListaDuplaNo *otherEachLista;
	minhasListas = lista;

	for(eachLista = minhasListas->inicio;eachLista != 0; eachLista = eachLista->proximo)  {
		if(eachLista == minhasListas->inicio && eachLista == minhasListas->fim) {
			//lista de único elemento, nada a fazer;
			break;
		}else{
			for(otherEachLista = eachLista->proximo;otherEachLista != 0;otherEachLista = otherEachLista->proximo) {
				if(eachLista->x == otherEachLista->x) {
					if(otherEachLista == minhasListas->fim) {
						//se tiver no fim
						otherEachLista->anterior->proximo = 0;
						minhasListas->fim = otherEachLista->anterior;
						free(otherEachLista);
						break;
					}else{
						otherEachLista->anterior->proximo = otherEachLista->proximo;
						otherEachLista->proximo->anterior = otherEachLista->anterior;
						free(otherEachLista);
					}
				}
			}
		}
	}
}

struct ListaDupla * moverNumerosMaioresQueN(struct ListaDupla * original, int n) {
	struct ListaDupla *minhasListas;
	struct ListaDupla *minhasListasModificada;
	struct ListaDuplaNo *eachLista;
	int valor = n;
	minhasListas = original;

	minhasListasModificada = malloc(sizeof(struct ListaDupla));
	minhasListasModificada->inicio = 0;
	minhasListasModificada->fim = 0;

	for(eachLista = minhasListas->inicio;eachLista != 0; eachLista = eachLista->proximo) {
		if(eachLista->x > valor) {
			inserirOrdenado(minhasListasModificada,eachLista->x);
		}
	}
	return minhasListasModificada;
}

void listar(struct ListaDupla * lista) {
	struct ListaDupla *minhasListas;
	struct ListaDuplaNo *eachLista;
	int i = 1;
	minhasListas = lista;

	printf("\n********************************************\n");
	for(eachLista = minhasListas->inicio;eachLista != 0; eachLista = eachLista->proximo,i++) {
		printf("lista%d - valor %d\n",i,eachLista->x);
	}
	printf("\n********************************************\n");
}


int main(int argc, char **argv) {
	struct ListaDupla *minhasListas;

	minhasListas = malloc(sizeof(struct ListaDupla));
	minhasListas->inicio = 0;
	minhasListas->fim = 0;

	inserirOrdenado(minhasListas,10);
	inserirOrdenado(minhasListas,5);
	inserirOrdenado(minhasListas,2);
	inserirOrdenado(minhasListas,9);
	inserirOrdenado(minhasListas,5);
	inserirOrdenado(minhasListas,100);
	inserirOrdenado(minhasListas,1);
	listar(minhasListas);

	inverter(minhasListas);
	listar(minhasListas);

	removerDuplicados(minhasListas);
	listar(minhasListas);

	listar(moverNumerosMaioresQueN(minhasListas,90));


	return EXIT_SUCCESS;
}
