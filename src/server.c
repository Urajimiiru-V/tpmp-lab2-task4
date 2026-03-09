#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interfaces.h"

int read_applicants_from_file(const char *filename, Applicant **applicants) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: cannot open file %s\n", filename);
        return -1;
    }
    
    int count = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strlen(buffer) > 1) count++;
    }
    
    if (count == 0) {
        printf("File %s is empty.\n", filename);
        fclose(file);
        return 0;
    }
    
    *applicants = (Applicant*)malloc(count * sizeof(Applicant));
    if (!*applicants) {
        printf("Memory allocation error.\n");
        fclose(file);
        return -1;
    }
    
    rewind(file);
    
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file) && i < count) {
        if (strlen(buffer) <= 1) continue;
        
        buffer[strcspn(buffer, "\n")] = 0;
        
        Applicant *app = &(*applicants)[i];
        
        char *token = strtok(buffer, ";");
        if (token) strcpy(app->last_name, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(app->first_name, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(app->patronymic, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(app->gender, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(app->nationality, token);
        
        token = strtok(NULL, ";");
        if (token) {
            sscanf(token, "%d %d %d", 
                   &app->birth_date.year, 
                   &app->birth_date.month, 
                   &app->birth_date.day);
        }
        
        token = strtok(NULL, ";");
        if (token) app->address.postal_code = atoi(token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(app->address.country, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(app->address.region, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(app->address.district, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(app->address.city, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(app->address.street, token);
        
        token = strtok(NULL, ";");
        if (token) app->address.house = atoi(token);
        
        token = strtok(NULL, ";");
        if (token) app->address.apartment = atoi(token);
        
        token = strtok(NULL, ";");
        if (token) app->ct_score1 = atoi(token);
        
        token = strtok(NULL, ";");
        if (token) app->ct_score2 = atoi(token);
        
        token = strtok(NULL, ";");
        if (token) app->ct_score3 = atoi(token);
        
        token = strtok(NULL, ";");
        if (token) app->passing_score = atoi(token);
        
        i++;
    }
    
    fclose(file);
    return count;
}

void filter_by_passing_score(Applicant *applicants, int count, int threshold, 
                             Applicant **results, int *result_count) {
    *result_count = 0;
    for (int i = 0; i < count; i++) {
        if (applicants[i].passing_score > threshold) {
            (*result_count)++;
        }
    }
    
    if (*result_count == 0) {
        *results = NULL;
        return;
    }
    
    *results = (Applicant*)malloc(*result_count * sizeof(Applicant));
    if (!*results) {
        printf("Memory allocation error for results.\n");
        *result_count = 0;
        return;
    }
    
    int j = 0;
    for (int i = 0; i < count; i++) {
        if (applicants[i].passing_score > threshold) {
            (*results)[j++] = applicants[i];
        }
    }
}

void write_applicants_to_file(const char *filename, Applicant *applicants, int count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: cannot create file %s\n", filename);
        return;
    }
    
    fprintf(file, "APPLICANTS SELECTION RESULTS (passing score > 225)\n");
    fprintf(file, "Total selected: %d applicants\n\n", count);
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "Applicant #%d:\n", i + 1);
        fprintf(file, "Name: %s %s %s\n", 
                applicants[i].last_name, 
                applicants[i].first_name, 
                applicants[i].patronymic);
        fprintf(file, "Gender: %s, Nationality: %s\n", 
                applicants[i].gender, 
                applicants[i].nationality);
        fprintf(file, "Birth date: %04d-%02d-%02d\n", 
                applicants[i].birth_date.year, 
                applicants[i].birth_date.month, 
                applicants[i].birth_date.day);
        fprintf(file, "Address: %d, %s, %s reg., %s distr., %s city, %s st., %d, apt %d\n",
                applicants[i].address.postal_code,
                applicants[i].address.country,
                applicants[i].address.region,
                applicants[i].address.district,
                applicants[i].address.city,
                applicants[i].address.street,
                applicants[i].address.house,
                applicants[i].address.apartment);
        fprintf(file, "CT scores: %d, %d, %d\n", 
                applicants[i].ct_score1,
                applicants[i].ct_score2,
                applicants[i].ct_score3);
        fprintf(file, "Passing score: %d\n\n", applicants[i].passing_score);
    }
    
    fclose(file);
}

void print_applicant(Applicant *app) {
    printf("  %s %s %s | score: %d\n", 
           app->last_name, app->first_name, app->patronymic, 
           app->passing_score);
}

void print_applicants_table(Applicant *applicants, int count, const char *title) {
    printf("\n%s\n", title);
    printf("----------------------------------------------------\n");
    printf(" # | Last Name      | First Name   | Patronymic    | Score\n");
    printf("----------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%2d | %-14s | %-12s | %-13s | %d\n", 
               i + 1,
               applicants[i].last_name,
               applicants[i].first_name,
               applicants[i].patronymic,
               applicants[i].passing_score);
    }
    printf("----------------------------------------------------\n");
}

void free_applicants(Applicant *applicants) {
    if (applicants) {
        free(applicants);
    }
}
