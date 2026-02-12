#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>

#include "../include/stationmapper.h"


int main(int argc, char *argv[])
{
    printf("--------------------------------------------------------------------------\n");
    printf("This is example for stationmapper library.\n");
    printf("The application loads map and a list of stations related to this map,\n");
    printf("asks user for location, performs the nearest station search\n");
    printf("and generates the output image file with\n");
    printf("all maps (red), user's location (blue) and the nearest station (orange).\n");
    printf("--------------------------------------------------------------------------\n\n");


    // Get library version;
    version_t version = get_library_version();
    printf("Using stationmapper %d.%d.%d\n", version.major, version.minor, version.patch);

    if(3 == argc) {
        printf("EINVAL\r\n");
        return -EINVAL;
    }

    // Load map and stations list
    peace_of_map_t map;
    printf("try load bmp %s\n", argv[1]);
    if(load_map(argv[1], argv[2], &map)) {
        printf("load_map error\r\n");
        return -EINVAL;
    }

    stations_list_t stations;
    if(load_stations(argv[3], &stations)) {
        printf("load_stations error\r\n");
        return -EINVAL;
    }

    // Get user's location
    float user_lat = 55.66323099;
    float user_lon = 37.244983000000005;
    // printf("Enter your latitude (example: 55.655)\n");
    // scanf("%f", &user_lat);
    // printf("Enter your longitude (example: 37.252)\n");
    // scanf("%f", &user_lon);

    // Draw user's location
    draw_point_by_lat_lon(&map, user_lat, user_lon, 0, 0, 255);

    // Draw all stations
    for (int i = 0; i < stations.num_stations; i++) {
        draw_point_by_lat_lon(&map, stations.stations[i].lat, stations.stations[i].lon, 0, 0, 255);
    }

    // Nearest station search
    station_t nearest_station = get_nearest_station(&stations, user_lat, user_lon);
    draw_point_by_lat_lon(&map, nearest_station.lat, nearest_station.lon, 255, 0, 0);
    printf("The nearest station: %s (lat: %4f, lon: %.4f)\n", nearest_station.name, nearest_station.lat, nearest_station.lon);
    printf("Distance to the station: %.2f km\n", get_distance_in_km(nearest_station.lat, nearest_station.lon, user_lat, user_lon));

    // Generate output map image
    const char output_map_name[] = "build/map_out.bmp";
    int err = save_map(&map, output_map_name);
	if (err)
		printf("Failed to save %s, error code: %u\n", output_map_name, err);
    else
        printf("Output map image %s generated\n", output_map_name);

    // Cleanup
    free(map.image);
    
    return 0;
}