/*
 * Reader.h
 *
 *  Created on: 2015-03-02
 *      Author: Kyle
 */

#ifndef MONITOR_H
#define MONITOR_H

#define MAX_PRESSURE 80	// Maximum allowed pressure

#include <stdio.h>
#include <pthread.h>
#include <signal.h>

#include "Pressure.h"

typedef struct Monitor {

	sig_atomic_t available;				// flag indicating the system is online/available
	volatile sig_atomic_t release;		// flag indicating that a release of pressure is needed
	int release_id;						// The ID of the corresponding sensor that needs pressure released
	int num_sensors;					// number of sensors to be created (user defined)
	int pressure_reading;				// The pressure reading of the over-pressurized sensor
	Pressure *pressures;				// Heap - array of Pressure structs
	pthread_t *sensor_threads;			// Heap - Array of sensor threads
	pthread_t *reader_threads;			// Heap - Array of reader threads

} Monitor;

typedef void * (*thread_action)(void *);

int monitor_init(Monitor *monitor, int num_sensors, thread_action sensorThread, thread_action readerThread);
int monitor_destroy(Monitor *monitor);

#endif /* MONITOR_H */
