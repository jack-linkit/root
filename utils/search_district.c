#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <search_term>\n", argv[0]);
        return 1;
    }

    char *search_term = argv[1];
    char line[MAX_LINE_LENGTH];
    char district[MAX_FIELD_LENGTH];
    char districtID[MAX_FIELD_LENGTH];
    int found = 0;

    // Open the file for reading
    FILE *file = fopen("/home/jackoc/utils/districts.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    for (int i = 0; search_term[i]; i++) {
        search_term[i] = tolower(search_term[i]);
    }

    // Read each line in the file
    while (fgets(line, sizeof(line), file) != NULL) {
        // Parse the line into district and districtID
        if (sscanf(line, "\"%[^\"]\" %s", district, districtID) == 2) {
            // Check if the district name starts with the search termi
	    for (int i = 0; district[i]; i++) {
		    district[i] = tolower(district[i]);
	    }
            if (strstr(district, search_term) == district) {
                printf("%s\n", districtID);
                found = 1;
                break;
            }
        }
    }

    // Close the file
    fclose(file);

    if (!found) {
        printf("No matching district found for search term: %s\n", search_term);
    }

    return 0;
}

