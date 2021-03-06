/*
 * Sensor.h
 *
 *  Created on: 2015-03-02
 *      Author: Kyle
 */

#ifndef PRESSURE_H
#define PRESSURE_H

#include <pthread.h>

typedef struct Pressure
{
	int id;						// the ID of the pressure and corresponding sensor/reader
	int pressure;				// amount of pressure (assuming PSI)
	pthread_mutex_t mutex;		// Mutex to lock this struct during read/write
} Pressure;
int pressure_init(Pressure *pressure, int id);
int pressure_destroy(Pressure *pressure);
int get_pressure(Pressure *pressure);
int set_pressure(Pressure *pressure, int pressure_value);

#endif /* PRESSURE_H */
