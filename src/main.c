#include <stdio.h>
#include <stdlib.h>
#include "interfaces.h"

#define INPUT_FILE "data/abiturients.txt"
#define OUTPUT_FILE "data/result.txt"
#define THRESHOLD 225

int main() {
    Applicant *all_applicants = NULL;
    Applicant *filtered_applicants = NULL;
    int total_count = 0;
    int filtered_count = 0;
    
    printf("\nReading data from file: %s\n", INPUT_FILE);
    total_count = read_applicants_from_file(INPUT_FILE, &all_applicants);
    
    if (total_count <= 0) {
        printf("Error: cannot read data or file is empty.\n");
        return 1;
    }
    
    printf("Records read: %d\n", total_count);
    
    print_applicants_table(all_applicants, total_count, "ORIGINAL DATA");
    
    printf("\nFiltering: passing score > %d...\n", THRESHOLD);
    filter_by_passing_score(all_applicants, total_count, THRESHOLD, 
                           &filtered_applicants, &filtered_count);
    
    if (filtered_count == 0) {
        printf("Applicants with score > %d not found.\n", THRESHOLD);
    } else {
        printf("Applicants found: %d\n", filtered_count);
        print_applicants_table(filtered_applicants, filtered_count, "SELECTED APPLICANTS");
        
        printf("\nSaving results to file: %s\n", OUTPUT_FILE);
        write_applicants_to_file(OUTPUT_FILE, filtered_applicants, filtered_count);
        printf("Results saved successfully.\n");
    }
    
    free_applicants(all_applicants);
    free_applicants(filtered_applicants);
    
    printf("\nprogram finished\n");
    
    return 0;
}
