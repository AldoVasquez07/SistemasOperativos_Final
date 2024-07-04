#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;  // Declarandop una variable mutex para la sincronización de los hilos
int c = 0;  // Variable global compartida entre hilos para contar

void* funcion(void* p1);  // Realizando prototipo de función para el hilo hijo
void printResult(const char* threadName, int value);  // Realizando prototipo de función para imprimir resultados

int main() {
    pthread_t hilo;  // Identificador del hilo
    pthread_attr_t attr;  // Atributos del hilo
    int error;  // Variable para almacenar errores de pthread

    pthread_mutex_init(&mutex, NULL);  // Inicialización del mutex
    pthread_attr_init(&attr);  // Inicialización de los atributos del hilo

    error = pthread_create(&hilo, &attr, funcion, NULL);  // Creación del hilo hijo
    if (error != 0) {  // Manejo de errores en la creación del hilo
        perror("error");
        return -1;
    }

    printResult("proceso Padre", 1);  // Llamada a la función para imprimir resultados desde el proceso padre

    pthread_join(hilo, NULL);  // Esperando a que el hilo hijo termine

    return 0;
}

void* funcion(void* p1) {
    printResult("Proceso Hijo:", -1);  // Llamada a la función para imprimir resultados desde el hilo hijo
    pthread_exit(NULL);  // Terminando con el hilo hijo
}

void printResult(const char* threadName, int v) {
    int i = 0;  // Variable de iteración
    while (i < 300) {  // Bucle que itera 300 veces
        c += v;  // Operación sobre la variable compartida c
        pthread_mutex_lock(&mutex);  // Bloqueo del mutex para asegurar la exclusión mutua
        for
        printf("%s c = %d\n", threadName, c);  // Impresión de los resultados
        pthread_mutex_unlock(&mutex);  // Desbloqueo del mutex
        i++;  // Incrementando el contador en uno
    }
}
