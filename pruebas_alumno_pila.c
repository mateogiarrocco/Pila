#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define VALOR_DE_PRUEBA 2
#define VALOR_VOLUMEN 10000
#define VALOR_DE_PRUEBA_VOLUMEN 10

void** invertir_arr(void** arreglo){
	pila_t* pila = pila_crear();
	if (!pila) return NULL;
	int i = 0;
	while(arreglo[i] != NULL){
		pila_apilar(pila, arreglo[i]);
		i++;
	}
	int j = 0;
	while(!pila_esta_vacia(pila)){
		arreglo[j] = pila_desapilar(pila);
		j++;
	}
	pila_destruir(pila);
	return *arreglo;
}

int* crear_valor_prueba(int valor){
	int* dato = malloc(sizeof(int));
	*dato = valor;
	return dato;
}

void pruebas_crear_y_destruir(){
	printf("PRUEBAS CREAR Y DESTRUIR\n");
	pila_t* pila = pila_crear();
	print_test("Pila creada correctamente", pila != NULL);
	pila_destruir(pila);
    print_test("Pila destruida correctamente", pila);
}

void pruebas_pila_vacia() {
    printf("PRUEBAS PILA VACIA\n");
    pila_t* ejemplo = NULL;

    print_test("Puntero inicializado a NULL", ejemplo == NULL);

    pila_t* pila = pila_crear();
    print_test("Pila creada correctamente", pila != NULL);
    print_test("El tope de la pila vacia es 0", pila_ver_tope(pila) == NULL);
    print_test("La pila esta vacia", pila_esta_vacia(pila));
    print_test("Pila no se puede desapilar", !pila_desapilar(pila));
    pila_destruir(pila);
    print_test("Pila destruida correctamente", pila);
}

void pruebas_pila_con_elementos(){
	printf("PRUEBAS PILA CON ELEMENTOS\n");
	void* valor = (int*)VALOR_DE_PRUEBA;

	//destruyo la pila sin elementos
	pila_t* pila1 = pila_crear();
	print_test("Pila creada correctamente", pila1 != NULL);
	pila_apilar(pila1, valor);
	print_test("El tope de la pila es el valor que apilé", pila_ver_tope(pila1) == valor);
	print_test("Pila tiene elementos", !pila_esta_vacia(pila1));
	pila_desapilar(pila1);
	print_test("El tope de la pila vacia es NULL", pila_ver_tope(pila1) == NULL);
	pila_destruir(pila1);

	pila_t* pila2 = pila_crear();
	//destruyo la pila con un elemento adentro
	pila_apilar(pila2, valor);
	print_test("El tope de la pila vacia es valor", pila_ver_tope(pila2) == valor);
	print_test("Pila tiene elementos", !pila_esta_vacia(pila2));
	pila_destruir(pila2);
    print_test("Pila destruida correctamente", pila2);
}

void pruebas_apilando_null(){
	printf("PRUEBAS APILANDO NULL\n");
	void* valor = NULL;
	pila_t* pila1 = pila_crear();
	//destruyo la pila sin elementos
	for(int i = 0; i < 30; i ++) pila_apilar(pila1, valor);
	print_test("El tope de la pila es null", pila_ver_tope(pila1) == NULL);
	print_test("la pila tiene elementos", !pila_esta_vacia(pila1));
	for(int i = 0; i < 20; i ++) pila_desapilar(pila1);
	print_test("La pila no esta del todo vacia", !pila_esta_vacia(pila1));
	for(int i = 0; i < 10; i ++) pila_desapilar(pila1);
	print_test("La pila esta vacia", pila_esta_vacia(pila1));
	pila_destruir(pila1);

	pila_t* pila2 = pila_crear();
	//destruyo la pila con NULLs adentro
	pila_apilar(pila2, valor);
	for(int i = 0; i < 30; i ++) pila_apilar(pila2, valor);
	for(int i = 0; i < 20; i ++) pila_desapilar(pila2);
	print_test("La pila no esta del todo vacia", !pila_esta_vacia(pila2));
	pila_destruir(pila2);
    print_test("Pila destruida correctamente", pila2);
}

void pruebas_volumen(){
	printf("PRUEBAS VOLUMEN\n");
	int valor = VALOR_DE_PRUEBA_VOLUMEN;
	int* valor_nuevo;
	pila_t* pila = pila_crear();
	print_test("No se puede desapilar", !pila_desapilar(pila));
	print_test("No se puede ver tope", !pila_ver_tope(pila));
	print_test("La pila esta vacia", pila_esta_vacia(pila));
	
	bool ok = true;
	int a_apilar[VALOR_VOLUMEN];
	for (int i = 0; i< VALOR_VOLUMEN; i++) a_apilar[i] = i;
	for (int i = 0; i< VALOR_VOLUMEN; i++){
		ok = ok && pila_apilar(pila, &a_apilar[i]);	   
	    ok = ok && (pila_ver_tope(pila) == &a_apilar[i]);
	}
	print_test("Se cumple la invariante de la pila", ok);
	
	for (int i = 0; i< VALOR_VOLUMEN; i++){
		ok = (pila_ver_tope(pila) == pila_desapilar(pila));  
	}
	print_test("Se cumple la invariante de la pila", ok);
	print_test("No se puede desapilar", !pila_desapilar(pila));
	print_test("La pila esta vacia", pila_esta_vacia(pila));
	print_test("El tope de la pila es NULL", (!pila_ver_tope(pila)));

	valor_nuevo = crear_valor_prueba(valor);
	pila_apilar(pila, valor_nuevo);
	print_test("La pila no esta vacia", !pila_esta_vacia(pila));
	print_test("El tope de la pila es valor_nuevo", (pila_ver_tope(pila)) == valor_nuevo);
	free(valor_nuevo);
	pila_destruir(pila);
}

void pruebas_pila_alumno(){
	void** arreglo = malloc(sizeof(void**));
	if(!arreglo) return;
	for(int i = 0; i < 10; i ++){
		arreglo[(void*)i] = i; 
	}
	invertir_arr(arreglo);
	for(int i = 0; i < 10; i ++){
		free(arreglo[i]);
	}
	free(arreglo);
	pruebas_crear_y_destruir();
	pruebas_pila_vacia();
	pruebas_pila_con_elementos();
	pruebas_apilando_null();
	pruebas_volumen();
}