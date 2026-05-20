#include <stdio.h>

//Declaración de varias constnates con el propósito de evitar asignaciones de valores erróneos 
#define MAX_OYENTES 100
#define NUM_CANCIONES 10
#define TOP_VOTOS 3

int leerVotos(int votos[MAX_OYENTES][TOP_VOTOS]);
void calcularEstadisticasCanciones(int votos[MAX_OYENTES][TOP_VOTOS], int total_oyentes, int *primera, int *segunda);
void determinarGanador(int votos[MAX_OYENTES][TOP_VOTOS], int total_oyentes, int primera, int segunda);

int main() 
{
    int votos[MAX_OYENTES][TOP_VOTOS];
    int total_oyentes = 0;
    int primera_mas_votada = -1;
    int segunda_mas_votada = -1;

    printf("--- Concurso de radio ---\n\n");

    //Lectura y almacenamiento de datos
    total_oyentes = leerVotos(votos);
    
    if (total_oyentes == 0) 
    {
        printf("No se registraron votos.\n");
        return 0;
    }

    //Cálculo de votos por canción e identificación de la primera y segunda más votada
    calcularEstadisticasCanciones(votos, total_oyentes, &primera_mas_votada, &segunda_mas_votada);

    //Repartición de puntos entre los oyentes
    determinarGanador(votos, total_oyentes, primera_mas_votada, segunda_mas_votada);

    return 0;
}

// Inciso 1: Lectura y almacenamiento de los votos
int leerVotos(int votos[MAX_OYENTES][TOP_VOTOS]) 
{
    int i = 0;
    int c1, c2, c3;

    printf("Introduzca las votaciones en tríos (Canción 1, Canción 2, Canción 3).\n");
    printf("Para finalizar, introduzca -1 en el primer dato.\n\n");

    while (i < MAX_OYENTES) 
    {
        printf("Oyente %d: ", i);
        scanf("%d", &c1);
        
        //Condicional: donde si el primer dato es -1, se termina el ciclo
        if (c1 == -1) 
        {
            scanf("%d %d", &c2, &c3);
            break;
        }
        
        scanf("%d %d", &c2, &c3);

        //Almacenamiento de los datos dentro de una matriz
        votos[i][0] = c1;
        votos[i][1] = c2;
        votos[i][2] = c3;

        i++; //Incremento en el contador de los oyentes
    }

    printf("\n--- Fin de la recepción de datos. Total oyentes: %d ---\n\n", i);
    return i; //Se regresa la cantidad de oyentes que han participado
}

// Inciso 2: Cálculo de votos por canción junto con las dos canciones más repetidas

void calcularEstadisticasCanciones(int votos[MAX_OYENTES][TOP_VOTOS], int total_oyentes, int *primera, int *segunda) 
{
    int puntuacion_canciones[NUM_CANCIONES] = {0}; //Todos los puntajes son inicializados desde 0

    for (int i = 0; i < total_oyentes; i++) 
    {
        int c1 = votos[i][0];
        int c2 = votos[i][1];
        int c3 = votos[i][2];

        //Asignación de puntos a cada una de las canciones dependiendo de su lugar
        if (c1 >= 0 && c1 < NUM_CANCIONES) puntuacion_canciones[c1] += 3;
        if (c2 >= 0 && c2 < NUM_CANCIONES) puntuacion_canciones[c2] += 2;
        if (c3 >= 0 && c3 < NUM_CANCIONES) puntuacion_canciones[c3] += 1;
    }

    printf("Resultados por canción:\n");
    for (int c = 0; c < NUM_CANCIONES; c++) 
    {
        printf("Canción %d: %d votos\n", c, puntuacion_canciones[c]);
    }

    //Búsqueda de las 2 canciones con mayores puntajes
    int max1 = -1;
    int max2 = -1;
    int idx1 = -1;
    int idx2 = -1;

    for (int c = 0; c < NUM_CANCIONES; c++) 
    {
        if (puntuacion_canciones[c] > max1) 
        {
            max2 = max1;
            idx2 = idx1;
            
            max1 = puntuacion_canciones[c];
            idx1 = c;
        } 
        else if (puntuacion_canciones[c] > max2) 
        {
            max2 = puntuacion_canciones[c];
            idx2 = c;
        }
    }

    *primera = idx1;
    *segunda = idx2;

    printf("\n1ª canción más votada: %d\n", *primera);
    printf("2ª canción más votada: %d\n\n", *segunda);
}

// Inciso 3: Repartición de puntos, se busca al oyente ganador de la dinámica 

void determinarGanador(int votos[MAX_OYENTES][TOP_VOTOS], int total_oyentes, int primera, int segunda) 
{
    int max_puntos_oyente = -1;
    int ganador_id = 0;

    printf("Puntajes obtenidos por los oyentes:\n");

    for (int i = 0; i < total_oyentes; i++) 
    {
        int puntos_oyente = 0;
        int acerto_primera = 0;
        int acerto_segunda = 0;

        // Comprobación de cuáles de las canciones ganadoras están en el trío del oyente
        for (int j = 0; j < TOP_VOTOS; j++) 
        {
            if (votos[i][j] == primera) 
            {
                acerto_primera = 1;
            }
            if (votos[i][j] == segunda) 
            {
                acerto_segunda = 1;
            }
        }

        //Aplicación de las reglas de puntaje del inciso 3
        if (acerto_primera) 
        {
            puntos_oyente += 30;
        }
        if (acerto_segunda) 
        {
            puntos_oyente += 20;
        }
        //Puntos adicionales en caso de haber acertado lod dos títulos más votados
        if (acerto_primera && acerto_segunda) 
        {
            puntos_oyente += 10;
        }

        printf("Oyente %d: %d puntos\n", i, puntos_oyente);

        // Guardado del registro del oyente que ganó la mayor cantidad de puntos
        if (puntos_oyente > max_puntos_oyente) 
        {
            max_puntos_oyente = puntos_oyente;
            ganador_id = i;
        }
    }

    printf("\nGanador: el oyente número %d\n", ganador_id);
}
