#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_EVENTS 10000

// Estructura para eventos
typedef struct {
    double time;       // Tiempo del evento
    int type;         // 0: llegada OMA, 1: llegada NOMA, 2: muerte/salida
    int channel;      // Canal asignado
} Event;

// Función para generar tiempo exponencial
double exponential_time(double rate) {
    double u = rand() / (RAND_MAX + 1.0);
    return -log(1-u) / rate;
}

int main() {
    // Parámetros del sistema
    double lambda1 = 0.5;    // Tasa de llegada OMA
    double lambda2 = 0.5;    // Tasa de llegada NOMA
    double mu = 1.0;         // Tasa de servicio
    int S = 5;               // Número de servidores
    double simulation_time = 1000.0; // Tiempo total de simulación
    
    // Variables de estado
    int arrivals = 0;
    int blocked_arrivals = 0;
    int system_status = 0;    // Número de usuarios en el sistema
    double T = 0.0;           // Tiempo actual
    
    // Lista de eventos (implementación simple)
    Event event_list[MAX_EVENTS];
    int event_count = 0;
    
    // Semilla para números aleatorios
    srand(time(NULL));
    
    // Programar primera llegada OMA en T=0
    event_list[event_count].time = 0.0;
    event_list[event_count].type = 0; // OMA
    event_list[event_count].channel = -1; // Sin canal asignado aún
    event_count++;
    
    // Bucle principal de simulación
    while (T < simulation_time && event_count > 0) {
        // Paso 1: Encontrar el próximo evento en la lista ordenada
        int next_event_index = 0;
        for (int i = 1; i < event_count; i++) {
            if (event_list[i].time < event_list[next_event_index].time) {
                next_event_index = i;
            }
        }
        
        // Paso 2: Actualizar tiempo al del próximo evento
        Event next_event = event_list[next_event_index];
        T = next_event.time;
        
        // Eliminar el evento procesado (mover el último evento a esta posición)
        event_list[next_event_index] = event_list[event_count-1];
        event_count--;
        
        // Paso 3: Procesar el evento
        if (next_event.type == 0 || next_event.type == 1) { 
            // Evento de llegada (OMA o NOMA)
            arrivals++;
            
            // Generar números aleatorios para próximas llegadas
            double X1 = exponential_time(lambda1);
            double X2 = exponential_time(lambda2);
            
            if (next_event.type == 0 || (next_event.type == 1 && X1 <= X2)) {
                // Llegada OMA o decisión de procesar como OMA
                
                // Verificar si hay capacidad
                if (system_status < S) {
                    system_status++; // Ocupa un canal
                    
                    // Programar muerte/salida
                    double Y1 = exponential_time(mu);
                    event_list[event_count].time = T + Y1;
                    event_list[event_count].type = 2; // Muerte
                    event_list[event_count].channel = 0; // Canal OMA
                    event_count++;
                    
                    // Programar próxima llegada OMA
                    event_list[event_count].time = T + X1;
                    event_list[event_count].type = 0; // OMA
                    event_list[event_count].channel = -1;
                    event_count++;
                } else {
                    blocked_arrivals++;
                }
            } else {
                // Llegada NOMA
                if (system_status <= S-1) { // NOMA ocupa 2 canales?
                    system_status += 2; // Asume que NOMA ocupa 2 canales
                    
                    // Programar muerte/salida
                    double Y1 = exponential_time(mu);
                    double Y2 = exponential_time(mu);
                    event_list[event_count].time = T + Y1;
                    event_list[event_count].type = 2; // Muerte
                    event_list[event_count].channel = 1; // Canal NOMA 1
                    event_count++;
                    
                    event_list[event_count].time = T + Y2;
                    event_list[event_count].type = 2; // Muerte
                    event_list[event_count].channel = 1; // Canal NOMA 2
                    event_count++;
                    
                    // Programar próxima llegada NOMA
                    event_list[event_count].time = T + X2;
                    event_list[event_count].type = 1; // NOMA
                    event_list[event_count].channel = -1;
                    event_count++;
                } else {
                    blocked_arrivals++;
                }
            }
        } else { 
            // Evento de muerte/salida
            if (next_event.channel == 0) {
                system_status--; // Libera canal OMA
            } else {
                system_status -= 2; // Libera 2 canales NOMA
            }
        }
    }
    
    // Resultados de la simulación
    printf("Resultados de la simulación:\n");
    printf("Tiempo total de simulación: %.2f\n", T);
    printf("Total de llegadas: %d\n", arrivals);
    printf("Llegadas bloqueadas: %d\n", blocked_arrivals);
    printf("Porcentaje de bloqueo: %.2f%%\n", (blocked_arrivals * 100.0) / arrivals);
    printf("Ocupación promedio del sistema: %.2f\n", system_status / (double)S);
    
    return 0;
}