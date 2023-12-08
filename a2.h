#include <stdio.h>
#include <stdlib.h>
enum {FALSE = 0, TRUE = 1, ST_SIZE = 100};
static int steps = 0;
//structs

struct Elevator{
  int floor;
  int cap;
  int current_load;
  int seq_n;
};
struct Person{
  int current_floor;
  int dest_floor;
};

//function prototyping
int strl(char arr[]);//string length

char *low(char *p);//string to lowercase

int str_com(char str1[], char str2[]);//compares two strings

char *up(char *b);//string to uppercase

int header(void);
void greeting(void);
char *hotel_name(void);
int *floors(char *hotel_name);
int *elev_count(char *totel_name);
int *elevCapacity(char *hotel_name);
int *people_w(void);
int *destination_f(int *floors, int *people_w);
int show_initial_state(void);

void initial_state( char *h_c, int *floor_n,  int *elev,int *elev_cap, int *people_waiting, 
int *dest_arr, struct Elevator *elevator_space, struct Person *people_space);

void print_hotel_name(char *hotel_n, int *elev_count);
struct Elevator* build_elev(const int *elev, const int *elev_cap_c,const int *floor_n);
struct Person* build_people(const int *floors, const int *people_waiting, int *dest_a_c);

int show_simulation(char *h_n, struct Elevator *elevator_space, struct Person *people_space, int *en, int *floors, int *people);
void print_top(int *elev_number);

void print_row(struct Elevator *ep, struct Person *pp, int *en, int current_floor, int *people_waiting, int *floors);

void between_row(int *elev_number);

int int_arr_length(int *arr);

int whether_start_simulation(void);

void last_line_print(int *elev_number);

int main_sim(char *hotel, int *floors_number, int *elev, int *elev_cap,int *people_waiting, int *dest_arr,
struct Elevator *elevator_space, struct Person *people_space);

int show_all_steps(void);

void str_copy(char str1[], char str2[]);

void free_everything(char *hotel, int *floors_num, int * elevators, int *elev_cap, 
int *people_waiting, int *dest_arr);


