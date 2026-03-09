#ifndef INTERFACES_H
#define INTERFACES_H

typedef struct {
    int year;
    int month;
    int day;
} BirthDate;

typedef struct {
    int postal_code;
    char country[30];
    char region[30];
    char district[30];
    char city[30];
    char street[30];
    int house;
    int apartment;
} Address;

typedef struct {
    char last_name[30];
    char first_name[30];
    char patronymic[30];
    char gender[2];
    char nationality[20];
    BirthDate birth_date;
    Address address;
    int ct_score1;
    int ct_score2;
    int ct_score3;
    int passing_score;
} Applicant;

int read_applicants_from_file(const char *filename, Applicant **applicants);
void filter_by_passing_score(Applicant *applicants, int count, int threshold, 
                             Applicant **results, int *result_count);
void write_applicants_to_file(const char *filename, Applicant *applicants, int count);
void print_applicant(Applicant *app);
void print_applicants_table(Applicant *applicants, int count, const char *title);
void free_applicants(Applicant *applicants);

#endif
