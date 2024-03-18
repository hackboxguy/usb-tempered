#include <stdbool.h>
#include <string.h>

#include "type-info.h"
#include "../tempered-internal.h"

bool tempered_type_hid_get_temperature_simple(
	tempered_device *device, struct tempered_type_hid_sensor *sensor,
	struct tempered_type_hid_query_result *group_data, float *tempC
) {
	if (
		group_data->length <= sensor->temperature_high_byte_offset ||
		group_data->length <= sensor->temperature_low_byte_offset
	) {
		tempered_set_error(
			device, strdup( "Not enough data was read from the sensor." )
		);
		return false;
	}

	int low_byte_offset = sensor->temperature_low_byte_offset;
	int high_byte_offset = sensor->temperature_high_byte_offset;
	int temp = ( group_data->data[low_byte_offset] & 0xFF )
		+ ( (signed char)group_data->data[high_byte_offset] << 8 )
	;
	
	*tempC = temp / 100.0;
	
	return true;
}

bool tempered_type_hid_get_humidity_simple(
        tempered_device *device, struct tempered_type_hid_sensor *sensor,
        struct tempered_type_hid_query_result *group_data, float *rel_hum
) {
        float tempC;
        if (
                !tempered_type_hid_get_temperature_simple(
                        device, sensor, group_data, &tempC
                )
        ) {
                return false;
        }

        if (
                group_data->length <= sensor->humidity_high_byte_offset ||
                group_data->length <= sensor->humidity_low_byte_offset
        )
        {
                tempered_set_error(
                        device, strdup( "Not enough data was read from the sensor." )
                );
                return false;
        }

        int low_byte_offset = sensor->humidity_low_byte_offset;
        int high_byte_offset = sensor->humidity_high_byte_offset;
        int rh = ( group_data->data[low_byte_offset] & 0xFF )
                + ( ( group_data->data[high_byte_offset] & 0xFF ) << 8 )
        ;

	*rel_hum = rh/100;

        return true;
}

