//---------------------------------------------------------------------------------------------------------------------
///
/// This is an example header comment. Here, you explain, what the
/// function does. Copypaste and adapt it!
///
/// @param numbers an array to check
/// @param length The length of the array. If this text is too long you can 
///        continue at the next line
///
/// @return the highest number
//
#include <stdio.h>
#include <stdlib.h>
enum {FALSE = 0, TRUE = 1, ST_SIZE = 100};
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
int show_sim(void);
void initial_state(char * hotel, int *floors_number, int *elev, int *elev_cap,int *people_waiting,int *dest_arr);
void print_hotel_name(char *hotel_n, int *elev_count);
struct Elevator* build_elev(int *elev);
struct Person* build_people(int *floors, int *people_waiting);
int start_sim(char *h_n, struct Elevator *elevator_space, struct Person *people_space, int *en, int *floors, int *people);
void print_top(int *elev_number);
void print_row(struct Elevator *ep, struct Person *pp, int *en, int current_floor, int *people_waiting, int *floors);
void print_middle(int *elev_number);
// int *reverse(int *arr, int* people_waiting);
int int_arr_length(int *arr);


int main(void)
{
  int rsp = header();
  if(rsp == -1)
    return -1;
  
}
int header(void)
{
  greeting();
  char *hotel = hotel_name();//return a pointer to the string hotelName;
  int *floors_num = floors(hotel);//collect the number of floors;
  int *elevators = elev_count(hotel);//collect the number of elevators;
  int *elev_cap = elevCapacity(hotel);//collect the elevator capacity;
  int *people_waiting = people_w();//collect the amount of waiting people;
  int *dest_arr = destination_f(floors_num, people_waiting);
  if(hotel == NULL || elevators == NULL || people_waiting == NULL || dest_arr == NULL || floors_num == NULL){
    free(hotel);
    free(floors_num);
    free(elevators);
    free(elev_cap);
    free(people_waiting);
    free(dest_arr);
    return -1;
  }
  //simulation:
  int show_simulation = show_sim();
  if(show_simulation == 2){
    initial_state(hotel, floors_num, elevators, elev_cap, people_waiting, dest_arr);
  }else if(show_simulation == 1){
    
  }


  //freeing the memory
  // free(hotel);
  // free(floors_num);
  // free(elevators);
  // free(elev_cap);
  // free(people_waiting);
  // free(dest_arr);
  return 0;
}
//---------------------------------------------------------------------------------------------------------------------
///function greets the user;no params;
void greeting(void)
{
  printf("____________________\n");
  printf(" ____   ____   ____ \n");
  printf("|____  |____  |____|\n");
  printf("|____   ____| |     \n");
  printf("____________________\n");
  printf("\n");
  printf("Welcome to the\n");
  printf("Elevator Simulation Program!\n");
  printf("\n");

}
//---------------------------------------------------------------------------------------------------------------------
/// dynamically allocates memory for the hotelname,gets the name through fgets and
// returns a pointer to that name
/// @param void function doesn't take any input value
/// 
/// @return the array pointer to the name of the hotel, that was dinamically allocated;
char *hotel_name(void)
{
  char *string = (char *)malloc(sizeof(size_t) * 100);//long strings will not be used;
  if(string == NULL){
    printf("Unable to allocate memory for a name of the hotel.");
  }
  printf("Enter the name of the hotel:\n > ");
  fgets(string, sizeof(size_t)* 100, stdin);
  //remove that enter:
  char *str_c = string;
  char *str_c_2 = string;
  while(*str_c  != '\n'){
    //move until it is equal
    str_c++;
  }
  //when it is equal, we just set the value to \0:
  *str_c = '\0';//yes now it is removed
  //convert all the letters to uppercase:
  up(str_c_2);
  return string;
}
//---------------------------------------------------------------------------------------------------------------------
///
/// This function collects the number of floors and returns the result in type int;
/// @param *hotel_name takes a pointer to the name of the hotel;
/// @return the pointer to the number of floors
int *floors(char *hotel_name)
{
  //dynamic memory allocation:
  int *p = (int *)malloc(sizeof(size_t));
  if(p == NULL){
    printf("Out of memory! Program terminated!\n");
    return p;
  }
  printf("Enter the number of floors in hotel %s:\n > ", hotel_name);    
  int digit  = 0;
  scanf("%d", &digit);
  while( (digit > 10 || digit < 3)){      
    printf("Wrong input, the number of floors must be between 3 and 10!\n");
    printf("Enter the number of floors in hotel %s:\n > ", hotel_name);    
    scanf("%d", &digit);
  }
  *p = digit;
  return p;
}
//---------------------------------------------------------------------------------------------------------------------
///
/// This function collects the number of elevators and returns the result in type int;
/// @param *hotel_name takes a pointer to the name of the hotel;
/// @return the pointer to the number of elevators;
int *elev_count(char *hotel_name)
{
  int *p = malloc(sizeof(size_t));
  if(p == NULL){
    printf("Out of memory! Program terminated!\n");
    return p;
  }
  printf("Enter the number of elevators in hotel %s:\n > ", hotel_name);
  int elv_num  = 0;
  scanf("%d", &elv_num);
  while( (elv_num < 1 || elv_num > 5)){
    printf("Wrong input, the number of elevators must be between 1 and 5!\n");
    printf("Enter the number of elevators in hotel %s:\n > ", hotel_name);
    scanf("%d", &elv_num);
  }
  *p = elv_num;
  return p;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function collects the elevator capacity and returns the result in type int;
/// @param *hotel_name takes a pointer to the name of the hotel;
/// @return the int pointer to the capacity of each of the elevators;
int *elevCapacity(char *hotel_name)
{
  int *elv_c_p = malloc(sizeof(size_t));
  if(elv_c_p == NULL){
    printf("Out of memory! Program terminated!\n");
    return elv_c_p;
  }
  printf("Enter the capacity of elevators in hotel %s:\n > ", hotel_name);
  int elv_cap  = 0;
  scanf("%d", &elv_cap);
  while( (elv_cap <= 0 || elv_cap > 9)){
    printf("Wrong input, the capacity of elevators must be between 1 and 9 person(s)!\n");
    printf("Enter the capacity of elevators in hotel %s:\n > ", hotel_name);
    scanf("%d", &elv_cap);
  }
  *elv_c_p = elv_cap;
  return elv_c_p;
}
//---------------------------------------------------------------------------------------------------------------------
///
/// This function collects the amount of waiting people and returns the result in type int;
/// @param void (no parameters)
/// @return the number of waiting people
int *people_w(void)
{
  int *p = malloc(sizeof(size_t));
  if(p == NULL){
    printf("Out of memory! Program terminated!\n");
    return p;
  }
  printf("Enter the number of people waiting on each floor:\n > ");
  int p_w  = 0;
  scanf("%d", &p_w);
  while( (p_w < 2 || p_w > 20)){
    printf("Wrong input, the number of people waiting on each floor must be between 2 and 20!\n");
    scanf("%d", &p_w);
  }
  *p = p_w;
  getchar();//to get that enter;
  return p;
}
//---------------------------------------------------------------------------------------------------------------------
///
/// This function collects the amount of waiting people and returns the result in type int;
/// @param int *floors takes the int pointer of the int people_w
/// @param int *people_w takes the int pointer of the int people_w
/// @return the integer pointer to the array of destinations of each person
int *destination_f(int *floors, int *people_w)
{
  /*//plan
    move through each of the floor, 
    2.get the data from the user
    3.check the data for validit
    3.1 store the data;
    4.repeat until we move through all the floors
  */
  int *arr = calloc(1, (sizeof(size_t)* (*people_w) * (*floors + 1)));//the size of our array; + our num;
  //create array of arrays:
  int a[*floors + 1][*people_w];
  
  if(arr == NULL)
  {
    printf("Out of memory! Program terminated!\n");
    return arr;
  }
  int current_floor = 1, can_proceed = FALSE, p = 0, j = 0;
  while(current_floor <= *floors){//!carefull with the floors
    printf("Enter the destination floors of the people [floor: %d]:\n > ", current_floor - 1);
    char str[50];
    fgets(str, 50, stdin);
    for(int i = 0; str[i] != '\n';i++){
      if(str[i] == ','){
        continue;
      }
      //convert the string to a number:
      int num = atoi(&str[i]);
      if((num < 0) || num > (*floors))
      {
        printf("Wrong input, the destination floor %d is out of range (0 to %d)!\n",num, *floors - 1);
        can_proceed = FALSE;
        break;
      }else if(num == current_floor)
      {
        printf("Wrong input, the destination floor cannot be the current floor!\n");
        can_proceed = FALSE;//reset our value;
        break;
      }
      //if these conditions are fulfilled:
      if((num >= 0) && (num < (*floors)))
      {
        if(num != current_floor)
        {
          a[p][j] = num;
          can_proceed = TRUE;
          // arr_c++;//now arr_c points to the next valid integer place in our memory
            j++;
          }
        }
    }
    if(can_proceed){
      ++p;
      ++current_floor;
      j = 0;
    }
  }
  for (int i = 0; i < *floors; i++)
  {
    for (int j = 0; j < *people_w; j++)
    {
      printf("%d", a[i][j]);
    }
    printf("\n>>");
  }
  int *arr_c = arr;
  for (int i = *floors; i > 0; --i)
  {
    for (int j = 0; j < *people_w; j++)
    {
      *arr_c = a[i][j];
      arr_c++;
    }
    
    
  }
  return arr;
}
//---------------------------------------------------------------------------------------------------------------------
///
/// This is an example header comment. Here, you explain, what the
/// function does. Copypaste and adapt it!
///
/// @param numbers an array to check
/// @param length The length of the array. If this text is too long you can 
///        continue at the next line
///
/// @return the highest number
int show_sim(void)
{
  int done = FALSE;
  while(done == FALSE){
    printf("Show the initial state? (\"yes\"/\"no\"):\n > ");
    char str[100];
    scanf("%s", str);
    int length = strl(str);//check the length
    if(length > 3){
      continue;
    }else if(length == 3){ //convert the string to lowercase:
    //if the length of the string is 3:
      char *str_p = low(str);
      if(str_com(str_p, "yes")){//compare the strings
        // printf("\n <yes>\n");
        return 2;
      }else if(str_com(str_p, "no ")){
        // printf("\n <no>\n");
        return 1;
      }
    }else if(length == 2){
      char *str_p = low(str);
      if(str_com(str_p, "yes")){//compare the strings
        // printf("\n <yes>\n");
        return 2;
      }else if(str_com(str_p, "no")){
        // printf("\n <no>\n");
        return 1;
      }
    }
    
  }
  return 0;
}
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




void initial_state(char *hotel, int *floors_number, int *elev, int *elev_cap,int *people_waiting, int *dest_arr)
{
  printf("\n=================\n");
  printf("  INITIAL STATE\n=================\n\n");
  //create a copy of the values:
  char *h_c = hotel;
  int *floor_n = floors_number;
  int *elev_c = elev;
  int *elev_cap_c = elev_cap;
  int *people_w_c = people_waiting;
  int *dest_a_c = dest_arr;
  //allocate memory to structs:
  struct Elevator *elevator_space = build_elev(elev);
  struct Person *people_space = build_people(floor_n, people_w_c);
  if(elevator_space == NULL || people_space == NULL){
    printf("Out of memory! Program terminated!\n");
    // return -1;
  }
  //create a copy of the pointers;
  //write to this memory:
  struct Elevator *esc = elevator_space;//copied
  struct Person *psc = people_space;//copied
  //initialize elevators:
  for(int i = 0; i < *elev; i++)
  {
    esc->cap = *elev_cap_c;
    if(i % 2 == 0)
    {//it's even
      // esc->floor = *floor_n;
      esc->floor = 0;

    }else
    {
      esc->floor = *floor_n;
    }
    // esc->cur = *elev_cap_c;
    esc->current_load = 0;
    esc->seq_n = i;
    esc++;
  }//we've written the data to the elevators;
  //initialize people:
  for(int i = 0; i <= *floor_n; i++)
  {
    //for each person on the floor:
    for(int j = 0; j < *people_waiting; j++)
    {
    psc->current_floor = i;
    psc->dest_floor = *dest_a_c;
    ++dest_a_c;
    ++psc;//update the pointer
    }

  } 
  //create another copy of dest_array because that older pointer now points to nothing;
  //print the elevators:
  // struct Elevator *esc_c = elevator_space;
  // struct Person *psc_c = people_space;

  // printf("\n\n\n");
  // for(int i = 0; i < *elev_c;i++){
  //   printf("<%d, %d, %d>", esc_c->current_load, esc_c->cap, esc_c->floor);
  //   ++esc_c;
  // }
  // printf("\n");
  // for(int i = 0; i < (*floor_n )* (*people_w_c);i++){
  //   printf("<%d, %d>", psc_c->current_floor, psc_c->dest_floor);
  //   ++psc_c;
  // }
  // printf("\n");
  struct Elevator *esc_c_1 = elevator_space;
  struct Person *psc_c_1 = people_space;
  //print the grid for elevators:

   //we need to keep track of two things: elevators and people;
    //1.find out the dest floor of each person waiting
    //2.we have to keep track of the row of each elevator
    //3.how many people there are on each floor
    //4.who wants where
    // printf("%d", *people_w_c);
  start_sim(h_c, esc_c_1, psc_c_1 , elev_c, floor_n, people_w_c);//floors from 0 to 9
  

  
  //we have to free the original data:
  free(h_c);
  free(floors_number);
  free(elev);
  free(elev_cap);
  free(people_waiting);
  free(dest_arr);
  free(elevator_space);
  free(people_space);
}
//---------------------------------------------------------------------------------------------------------------------
///
/// This function start a simulation
///
/// @param struct Elevator *elevator_space is a pointer to the allocated space for the elevators to work with them
///
/// @param struct Person *people_space is a pointer to the allocated space for the people
///       space to work with people.
/// @param int *en elevator number pointer
/// @param int *floors floors number pointer
/// @return 0;
//
int start_sim(char *hotel_n, struct Elevator *elevator_space, struct Person *people_space, int *en, int *floors, int *people)
{
  //crete a copy:
  struct Elevator *es = elevator_space;
  struct Person *ps = people_space;
  int *elev_number = en;
  int *floor = floors;
  int *p_c = people;//we need to reverse our array of people values:
  // int *people_r = reverse(people);
  int current_floor = 0;
  // printf("%d", *en);
  print_hotel_name(hotel_n, en);
  print_top(elev_number);
  while(current_floor <= *floor)
  {
    print_row(es, ps, elev_number,  current_floor, p_c, floor);//floors from 0 to 9
    if(current_floor != *floor - 1){
      print_middle(en);
    }
    
    ++current_floor;
  }
  print_top(elev_number);

  return 0;
}
void print_row(struct Elevator *ep, struct Person *pp, int *en, int current_floor, int *people_waiting, int *floors)
{
  struct Elevator *epc = ep;  
  printf("|");
  //floors will be from 0 to 9
    //move through each of the elevators:
  for(int i = 0; i < *en; i++)
  {
    // printf("<%d>", epc->floor);
    if(epc->floor == current_floor)
    {
      printf("| ");
      printf("[%d]", epc->current_load);
      printf(" ");
    }else{
      printf("|     ");
    }
    ++epc;//udpate the reference to the elevators
  }
  printf("||  ");
  //print the row:
  struct Person *ppp = pp;
  int size = 2 * *people_waiting;
  //move through eah person:
  char str[44] = "(";
  //now it points to str[1];
  //move through each person:
  int count = 1;
  for(int i = 0; i < *people_waiting * (*floors);i++){

      if(ppp->current_floor == current_floor - 1)
      {
        str[count] = '0' + ppp->dest_floor;
        str[count + 1] = ',';
        count += 2;
      }
      ++ppp;
  }
  
  str[size] = ')';
  str[size  + 1] = '\0';
  printf("%s\n",str);
}


///
///the function prints the line to separate each row
/// @return no return;
void print_top(int *elev_number)
{
  printf("++");
  int i = 0;
  while(*elev_number > i){
  printf("-----+");
  ++i;
  }
  printf("+\n");
}
/// @brief prints the middle part of the structure (the space between the rows)
/// @param elev_number accepts a number of elevators;
void print_middle(int *elev_number){
  printf("||");
  int i = 0;
  while(*elev_number > i){
    if(*elev_number == i + 1){
      printf("-   -|");
    }else{
      printf("-   -+");
    }
  ++i;
  }
  printf("|\n");
}


//---------------------------------------------------------------------------------------------------------------------
///
/// function dynamically allocates memory for an array of structures with specific 
///
/// @param *elev pointer to the number of elevators;
///
/// @return the pointer to the allocated space for all elevators structs
//
struct Elevator* build_elev(int *elev)
{
  struct Elevator* elevators = (struct Elevator*)malloc(sizeof(struct Elevator) * *elev);
  if(elevators == NULL){
    printf("Unable to allocate memory for a name of the hotel.");
    return NULL;
  }
  return elevators;
}
//---------------------------------------------------------------------------------------------------------------------
///
/// function dynamically allocates memory for an array of structures with specific type struct Person
///
/// @param floors pointer to the number of floors;
/// @param people_waiting pointer to the number of people_waiting;
/// @return the pointer to the allocated space for all elevators structs
//
struct Person* build_people(int *floors, int *people_waiting)
{
  struct Person* people = (struct Person*)malloc(sizeof(struct Person)* (*floors + 1) * (*people_waiting));
  if(people == NULL){
    printf("Unable to allocate memory for a name of the hotel.");
    return NULL;
  }
  return people;
}
//---------------------------------------------------------------------------------------------------------------------
/// @brief function prints the first part of the structure(first three rows)
/// @param hotel_n the pointer to the name of the hotel
/// @param elev_count the pointer to the number of elevators
void print_hotel_name(char *hotel_n, int *elev_count)
{
  char str[100] = {0};//initialize str
  char str_b[100] = {0};
  int length = 6;//length of each elevators;
  int total = length * *elev_count;
  int first_row_l = total;
  
  str[0] = '+';
  for(int i = 1; i < first_row_l; i++){
    str[i] = '-';
  }
  printf("+%s++\n", str);
  //second row:
  int second_row_l = (total - strl(hotel_n)) / 2;
  int i = 0;
  for(; i < second_row_l; i++){
    str_b[i] = ' ';
  }
  int j = 0;
  for(; j < strl(hotel_n);j++)
  {
    str_b[i + j] = hotel_n[j];
  }
  for(int k = 0; k < second_row_l; k++)
  {
    str_b[i + j + k] = ' ';
  }
  printf("++%s++\n", str_b);
  //third row:
  // char str3[100] = {0};
  // int p = 6;
  // //repeat for every elevator:
  // for(int a = 0; a < *elev_count; ++a){
  //   for(int x = 0; x < 5; x++){
  //     str3[x + a*p] = '-';
  //   }
  //   str3[a*p + 5] = '+';
  // }
  
  // printf("++%s+\n", str3);
}
//---------------------------------------------------------------------------------------------------------------------
///
///The function computes the length of the array through a while loop;
///
/// @param arr[] is an array;
/// @return the length of the array
int strl(char arr[])
{
  int i = 0;//length
  while(arr[i] != '\0'){
    i++;
  }

  return i;
}
//---------------------------------------------------------------------------------------------------------------------
///
///The function converts the string to its lowercase equivalent
///
/// @param char *b takes a pointer to the string, to lowercase it;
/// @return the pointer to the lowercased string.
char *low(char *b)
{
  char *b_c = b;
  while(*b != '\0')
  {
    if(*b >= 65 && *b <= 90){
      *b = *b + 32;
    }
    b++;
  }
  //add that newLine
  *b = '\0';
  return b_c;
}
///
///The function converts the string to its lowercase equivalent
///
/// @param char *b takes a pointer to the string, to uppercase it;
/// @return the pointer to the uppercased string.
char *up(char *b)
{
  char *b_c = b;
  while(*b != '\0')
  {
    if(*b >= 97 && *b <= 122){
      *b = *b - 32;
    }
    b++;
  }
  //add that newLine
  *b = '\0';
  return b_c;
}
//---------------------------------------------------------------------------------------------------------------------
///
///The function compares two strings and outputs 0 if they do not match and 1 if they match
///
/// @param char *str2[]  a pointer to the first string (for comparison)
/// @param char str1[]  a pointer to the second string
/// @return the pointer to the lowercased string.
//compare stwo strings:
int str_com(char str1[], char str2[])
{
  int same = TRUE;
  int i = 0;
  while(str1[i] != '\0' && str2[i] != '\0'){
    if(str1[i] != str2[i]){
      same = FALSE;
      break;
    }
    i++;
  }
  return same;
}
/// @brief computes the length of the integer array
/// @param arr is a pointer to the integer array 
/// @return an integer(the length of the array)
int int_arr_length(int *arr)
{
  int i = 0;
  while(*arr != '\0'){
    arr++;
    i++;
  }
  return i;
}



