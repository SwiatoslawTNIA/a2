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
void greeting(void);
char *low(char *p);//string to lowercase
int str_com(char str1[], char str2[]);//compares two strings
char *up(char *b);//string to uppercase



int header(void);
char *hotel_name(void);
int *floors(char *hotel_name);
int *elev_count(char *totel_name);
int *elevCapacity(char *hotel_name);
int *people_w(void);
int *destination_f(int *floors, int *people_w);
int show_sim(void);
void initial_state(char *hotel);
void print_hotel_name(char *hotel_n);


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
  // printf("%s, %d, %d, %d, %d\n", hotel, *floors_num, *elevators, *elev_cap, *people_waiting);
  //check for available memory
  
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
    initial_state(hotel);
  }else if(show_simulation == 1){
    
  }


  //freeing the memory
  free(hotel);
  free(floors_num);
  free(elevators);
  free(elev_cap);
  free(people_waiting);
  free(dest_arr);
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
  int *p = (int *)malloc(sizeof(int));
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
  int *p = malloc(sizeof(int));
  if(p == NULL){
    printf("Out of memory! Program terminated!\n");
    return p;
  }
  printf("Enter the number of elevators in hotel %s:\n > ", hotel_name);
  int elv_num  = 0;
  scanf("%d", &elv_num);
  while( (elv_num < 1 || elv_num > 5)){
    printf("Wrong input, the number of elevators must be between 1 and 5!\n");
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
  int *elv_c_p = malloc(sizeof(int));
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
  int *p = malloc(sizeof(int));
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
  //plan
  /*
    move through each of the floor, 
    2.get the data from the user
    3.check the data for validit
    3.1 store the data;
    4.repeat until we move through all the floors

  */
  int *arr = malloc((sizeof(int)* (*people_w) * (*floors)));//the size of our array; + our num;
  //create a pointer copy:
  if(arr == NULL){
    printf("Out of memory! Program terminated!\n");
    return arr;
  }
  int *arr_c = arr;
  int current_floor = 0, can_proceed = FALSE;
  while(current_floor < *floors){
    printf("Enter the destination floors of the people [floor: %d]:\n > ", current_floor);
    /*2.How to get the data and check it:
    a comma separated list
    -0 <= dest_floor <= floors - 1
    -current floor;
    */
    char str[50];
    fgets(str, 50, stdin);
    for(int i = 0; str[i] != '\n';i++){
      if(str[i] == ','){
        continue;
      }
      //convert the string to a number:
      int num = atoi(&str[i]);
      if((num < 0) || num > (*floors - 1)){
        printf("Wrong input, the destination floor %d is out of range (0 to %d)!\n",num, *floors - 1);
        can_proceed = FALSE;
        break;
      }else if(num == current_floor){
        printf("Wrong input, the destination floor cannot be the current floor!\n");
        can_proceed = FALSE;//reset our value;
        break;
      }
      //if these conditions are fulfilled:
      if((num >= 0) && (num <= (*floors - 1))){
        if(num != current_floor){
          //write the value:
          *arr_c = num;
          can_proceed = TRUE;
          arr_c++;//now arr_c points to the next valid integer place in our memory
        }
      }
      
    }
    if(can_proceed){
      ++current_floor;
    }
  }
  *arr_c = -1;
  // ++arr_c;
  // arr_c = NULL;//nullify our pointer
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

void initial_state(char * hotel){
  printf("\n=================\n");
  printf("  INITIAL STATE\n=================\n\n ");
  print_hotel_name(hotel);
}


void print_hotel_name(char *hotel_n){
  printf("++-----------------++\n");
  printf("++  <%s>   ++\n", hotel_n);
  printf("++-----+-----+-----++\n");
}

















// int destination_floors(int floors, int p_w)
// {
//   // char *pointer = (char  *)malloc(sizeof(char)*floors*p_w*2);//10 floors, each at max 10 characters(a little bit more)
//   // if(pointer == NULL){
//   //   printf("Could not allocate memory for the arrays of values.");
//   // }
//   //array of pointers:
//   //allocate:
//   char *arr = (char *)malloc(sizeof(char)*p_w*2);
//   if(arr == NULL){
//     printf("Could not allocate memory for string storage.");
//   }
//   // char *temp = (char *)malloc(sizeof(char)*p_w*2);
//   // for(int current_floor = 1; current_floor <= floors; current_floor++){
//     int current_floor = 1;
//     while(current_floor <= floors){//
//     //each value of the row must be less or equal to the number of the floors;
//     //the number of numbers will be from 2 to twenty(we must specify for each person):
//     const size_t size = sizeof(char) * floors * 2;
//     int done = 0;
//       while(!done){
//         done = 1;
//         printf("Enter the destination floors of the people [floor: %d]:\n > ", current_floor);
//         fgets(arr, size, stdin);
//         printf("%s", arr);
//         //assess the validity of our array:
//         char c = 0;
//         while((c != ',') && (c = *arr++) != '\0')//move through each character
//         {
//           if(c == '\n' || c == EOF){//skip the enters that are entered each time
//             continue;
//           }
//           if((c + '0') > (floors))//(c + '0') is converting c to a number
//           {
//             printf("Wrong input, the destination floor %c ", c);
//             printf("is out of range (0 to %d)!\n", floors - 1);
//             done = 0;
//           }else if((c + '0') == current_floor){
//             printf("Wrong input, the destination floor cannot be the current floor!\n");
//             done = 0;
//           }
          
          
//         }
//         // arr++;
//       }
//     ++current_floor;
//   }
//   //free the memory:
//   free(arr);
//   return 0;
// }
// //---------------------------------------------------------------------------------------------------------------------
// ///
// /// This function parses the line:
// /// @param *arr pointer to the line of the input of the destination_floors function
// /// @param floors is the number of floors, type int
// /// @param current_floor is the current floor, type int


/// @return the truth value;(-1 if the element's value is out of range);
// int parse(char *arr, int floors, int current_floor)
// {
  
// }


//---------------------------------------------------------------------------------------------------------------------
///
///The function computes the length of the array through a while loop;
///
/// @param arr[] is an array;
/// @return the length of the array
int strl(char arr[])
{
  int i = 0;//length
  while(arr[i] != '\0')
    i++;
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
int str_com(char str1[], char str2[]){
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





