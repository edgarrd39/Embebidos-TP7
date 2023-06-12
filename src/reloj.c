/*Copyright 2023, Edgardo Rodrigo Díaz <rodrigo.09tuc@gmail.com>
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

/** \brief Brief description of the file
 **
 ** Full file description
 **
 ** \addtogroup name Module denomination
 ** \brief Brief description of the module
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "reloj.h"
#include <string.h>

/* === Macros definitions ====================================================================== */

#define TIME_SIZE 6

#define SEGUNDOS_UNIDADES 5
#define SEGUNDOS_DECENAS 4
#define MINUTOS_UNIDADES 3
#define MINUTOS_DECENAS 2
#define HORA_UNIDADES 1
#define HORA_DECENAS 0
#define MAX_HR_UNI 4 // Unidad maxima de hora
#define MAX_HR_DEC 2 // Decena maxima de hora

/* === Private data type declarations ========================================================== */

struct clock_s {
    uint8_t hora_actual[TIME_SIZE];
    uint8_t hora_alarma[TIME_SIZE];
    uint8_t hora_pospuesta[TIME_SIZE];
    uint8_t ticks_por_segundo;
    uint8_t ticks;
    bool valida;
    bool tiene_alarma;
    bool posponer;
};

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================= */

clock_t ClockCreate(int ticks_por_segundo) {
    static struct clock_s self[1];
    memset(self, 0, sizeof(self));
    self->ticks_por_segundo = ticks_por_segundo;
    return self;
}

bool ClockGetTime(clock_t reloj, uint8_t * hora, int size) {
    memcpy(hora, reloj->hora_actual, size);
    return reloj->valida;
}

bool ClockSetTime(clock_t reloj, const uint8_t * hora, int size) {
    memcpy(reloj->hora_actual, hora, size);
    reloj->valida = true;
    return true;
}

void ClockTick(clock_t reloj) {
    reloj->ticks++;
    if (reloj->ticks == reloj->ticks_por_segundo) {
        reloj->ticks = 0;
        reloj->hora_actual[SEGUNDOS_UNIDADES]++;
    }

    if (reloj->hora_actual[SEGUNDOS_UNIDADES] == 10) {
        reloj->hora_actual[SEGUNDOS_UNIDADES] = 0;
        reloj->hora_actual[SEGUNDOS_DECENAS]++;
    }
    if (reloj->hora_actual[SEGUNDOS_DECENAS] == 6) {
        reloj->hora_actual[SEGUNDOS_DECENAS] = 0;
        reloj->hora_actual[MINUTOS_UNIDADES]++;
    }
    if (reloj->hora_actual[MINUTOS_UNIDADES] == 10) {
        reloj->hora_actual[MINUTOS_UNIDADES] = 0;
        reloj->hora_actual[MINUTOS_DECENAS]++;
    }
    if (reloj->hora_actual[MINUTOS_DECENAS] == 6) {
        reloj->hora_actual[MINUTOS_DECENAS] = 0;
        reloj->hora_actual[HORA_UNIDADES]++;
    }

    if (reloj->hora_actual[HORA_UNIDADES] == 10) {
        reloj->hora_actual[HORA_UNIDADES] = 0;
        reloj->hora_actual[HORA_DECENAS]++;
    }
    if (reloj->hora_actual[HORA_DECENAS] == MAX_HR_DEC && reloj->hora_actual[HORA_UNIDADES] == MAX_HR_UNI) {
        memset(reloj->hora_actual, 0, sizeof(reloj->hora_actual));
    }
}

bool ClockSetAlarma(clock_t reloj, const uint8_t * hora, int size) {
    memcpy(reloj->hora_alarma, hora, size);
    reloj->tiene_alarma = true;
    return true;
}

bool ClockGetAlarma(clock_t reloj, uint8_t * hora, int size) {
    memcpy(hora, reloj->hora_alarma, size);
    return reloj->tiene_alarma;
}

bool ClockActivarAlarma(clock_t reloj) {

    if (reloj->posponer) {
        if (memcmp(reloj->hora_pospuesta, reloj->hora_actual, 6) == 0) {
            return true;
        }
        return false;
    }
    if (memcmp(reloj->hora_alarma, reloj->hora_actual, TIME_SIZE) == 0 && (reloj->tiene_alarma == true)) {
        return true;
    } else
        return false;
}

void ClockDesactivarAlarma(clock_t reloj) {
    reloj->tiene_alarma = false;
}

bool ClockPosponerAlarma(clock_t reloj) {
    mempcpy(reloj->hora_pospuesta, reloj->hora_alarma, 6);
    reloj->hora_pospuesta[3] += 5;
    reloj->posponer = true;
    return reloj->posponer;
}
/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
