#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

int main(int argc, char *argv[]) {
    int print_all = 0;
    int found = 0;
    char *search_term;
    if (argc == 1) {
	print_all = 1;
	found = 1;
	search_term = malloc(sizeof(char));
	search_term[0] = '\0';
    }
    else {
	search_term = argv[1];
    }

    char line[MAX_LINE_LENGTH];
    char district[MAX_FIELD_LENGTH];
    char districtID[MAX_FIELD_LENGTH];

    // Open the file for reading
    FILE *file = fopen("/Users/jackoconnor/WorkRoot/utils/districts.txt", "r");
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
            // Check if the district name starts with the search term
	    if (print_all == 1){
		printf("%s\n", districtID);
	    }
	    else {
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
    }

    // Close the file
    fclose(file);

    if (!found) {
        printf("No matching district found for search term: %s\n", search_term);
    }

    return 0;
}

