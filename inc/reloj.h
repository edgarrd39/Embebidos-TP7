/* Copyright 2023, Edgardo Rodrigo Díaz <rodrigo.09tuc@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef reloj_H
#define reloj_H

/** \brief Libreria para gestion un reloj
 **
 ** Conjunto de funciones y metodos para hacer funcionar un reloj despertador
 ** Desde configurar hora, ver hora, configurar alarma, y posponer alarma
 ** \addtogroup reloj RELOJ
 ** \brief Libreria para gestionar un reloj
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include <stdbool.h>
#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */

//!< Referencia a un descriptor para gestionar un reloj
typedef struct clock_s * clock_t;

//!< Funcion de callback para eventos de alarma
typedef void (*alarma_evento_t)(void);

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief  Metodo para crear un reloj
 *
 * @param ticks_por_segundo Cantidad de pulsos que debe recibir para contar un segundo.
 * @param evento            Funcion de callback para evento de alarma.
 * @return clock_t          Puntero con el descriptor del nuevo reloj creado.
 */
clock_t ClockCreate(int ticks_por_segundo, alarma_evento_t evento);

/**
 * @brief Funcion para obtener la hora actual del reloj
 *
 * @param reloj     Puntero al descriptor obtenido al crear el reloj
 * @param hora      Vector donde se devuelve la hora, minutos y segundos en formato BCD
 * @param size      Cantidad de elementos del vector
 * @return true     La hora del reloj es valida
 * @return false    La hora del reloj es invalida
 */
bool ClockGetTime(clock_t reloj, uint8_t hora[], int size);

/**
 * @brief Funcion para poner en hora el reloj
 *
 * @param reloj     Puntero al descriptor obtenido al crear el reloj
 * @param hora      Vector donde se devuelve la hora, minutos y segundos en formato BCD
 * @param size      Cantidad de elementos del vector
 * @return true
 * @return false
 */
bool ClockSetTime(clock_t reloj, const uint8_t * hora, int size);

/**
 * @brief Funcion para contar un nuevo tick de reloj, actualizar hora y verificar alarma
 *
 * @param reloj  Puntero al descriptor obtenido al crear el reloj
 */
void ClockTick(clock_t reloj);

/**
 * @brief Funcion para setear la alarma del reloj
 *
 * @param reloj  Puntero al descriptor obtenido para crear el reloj
 * @param hora   Vector donde se devuelve la hora, minutos y segundos en formato BCD de la alarma
 * @param size   Cantidad de elementos del vector
 * @return true
 * @return false
 */
bool ClockSetAlarma(clock_t reloj, const uint8_t * hora, int size);

/**
 * @brief  Funcion que obtiene la hora de la alarma
 *
 * @param reloj  Puntero al descriptor obtenido al crear el reloj
 * @param hora   Vector donde se devuelve la hora, minutos y segundos en formato BCD de la alarma
 * @param size   Cantidad de elementos del vector
 * @return true
 * @return false
 */
bool ClockGetAlarma(clock_t reloj, uint8_t * hora, int size);

/**
 * @brief Funcion que desactiva la alarma
 *
 * @param reloj Puntero al descriptor obtenido al crear el reloj
 */
void ClockDesactivarAlarma(clock_t reloj);

/**
 * @brief Funcion que pospone la alarma una cantidad arbitraria de minutos
 *
 * @param reloj  Puntero al descriptor obtenido al crear el reloj
 * @param minutos Cantidad de minutos que se desea posponer
 * @return true
 * @return false
 */
bool ClockPosponerAlarma(clock_t reloj, uint8_t minutos);

/**
 * @brief  Funcion que obtiene el estado de la alarma
 *
 * @param reloj Puntero al descriptor obtenido al crear el reloj
 * @return true
 * @return false
 */
bool ClockGetStateAlarm(clock_t reloj);
/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* TEMPLATE_H */