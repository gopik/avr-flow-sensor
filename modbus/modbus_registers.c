#include "modbus_registers.h"

struct MeterReading gMeterReading;

void initialize(struct MeterReading* reading) {
	reading->sensor_id = 0x1a;
	reading->sensor_type = 1;
	reading->unit_type = 1;
}

void add_value(struct MeterReading* reading, int16 current_timestamp, int16 delta) {
	// Update total
	reading->total += delta;

	int minutes_since_start = (current_timestamp - reading->timestamp_start) / 60;
	if (minutes_since_start == reading->num_readings - 1) {
		reading->readings[reading->num_readings - 1] += delta;
	} else {
		reading->readings[reading->num_readings] = delta;
	}
}

void update_timestamp(struct MeterReading* reading, int16 current_timestamp) {
	// Update readings table (adds 0s to readings for the minutes when there is no consumption)
	add_value(reading, current_timestamp, 0);
}
