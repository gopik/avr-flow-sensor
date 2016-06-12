#ifndef WATER_MODBUS_MODBUS_REGISTERS_H
#define WATER_MODBUS_MODBUS_REGISTERS_H

#define COUNT 60
typedef short int16;
typedef long int64;
/**
 * MeterReading holds cumulative and current hour readings for the water consumption in liters.
 * Current hour readings are stored minute by minute. The readings array is a circular buffer
 * which holds 60 readings. The time of each reading is computed by timestamp_start and
 * num_readings.
 * The order of the readings are interpreted as follows:
 * timestamp_start to timestamp_start + num_readings - 1 => readings[0] .. readings[num_readings-1]
 * timestamp_start + num_readings - 60 to timestamp_start - 1 => 
 * readings[num_readings] .. readings[59] 
 **/
struct MeterReading {
	int64 sensor_id;
	int16 sensor_type;
	int16 unit_type;
	int64 total;
	int16 timestamp_start;
	int16 readings[COUNT];
	int16 num_readings;
	int16 current_timestamp;
};

typedef struct MeterReading MeterReading;
void initialize(MeterReading* reading);
void add_value(MeterReading* reading, int16 current_timestamp, int16 delta);
void update_timestamp(MeterReading* reading, int16 current_timestamp);
#endif // WATER_MODBUS_MODBUS_REGISTERS
