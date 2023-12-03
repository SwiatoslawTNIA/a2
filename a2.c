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
enum {FALSE = 0, TRUE = 1};
//function prototyping
// long int strl(char arr[]);

void greeting(void);




void header(void);
char *hotel_name(void);
int *floors(char *hotel_name);
int *elev_count(char *totel_name);
int *elevCapacity(char *hotel_name);
int *people_w(void);
int *destination_f(int *floors, int *people_w);


int main(void)
{
  header();
}
void header(void)
{
   greeting();
  char *hotel = hotel_name();//return a pointer to the string hotelName;
  int *floors_num = floors(hotel);//collect the number of floors;
  int *elevators = elev_count(hotel);//collect the number of elevators;
  int *elev_cap = elevCapacity(hotel);//collect the elevator capacity;
  int *people_waiting = people_w();//collect the amount of waiting people;
  int *dest_arr = destination_f(floors_num, people_waiting);
  printf("%s, %d, %d, %d, %d\n", hotel, *floors_num, *elevators, *elev_cap, *people_waiting);
  // for(; *dest_arr != -1; dest_arr++){
  //   printf("<%d>", *dest_arr);
  // }
  //freeing the memory
  free(hotel);
  free(floors_num);
  free(elevators);
  free(elev_cap);
  free(people_waiting);
  free(dest_arr);
  
}
//---------------------------------------------------------------------------------------------------------------------
///function greets the user;no params;
void greeting(void)
{
  printf("____________________\n");
  printf("____   ____   ____ \n");
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
//
char *hotel_name(void)
{
  char *string = (char *)malloc(sizeof(size_t) * 100);//long strings will not be used;
  if(string == NULL){
    printf("Unable to allocate memory for a name of the hotel.");
  }
  printf("Enter the name of the hotel:\n >");
  fgets(string, sizeof(size_t)* 100, stdin);
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
  printf("Enter the number of floors in hotel %s:\n > ", hotel_name);    int digit  = 0;
  scanf("%d", &digit);
  while( (digit > 10 || digit < 3)){      
    printf("Wrong input, the number of floors must be between 3 and 10!\n");
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
  printf("Enter the capacity of elevators in hotel %s:\n > ", hotel_name);
  int elv_cap  = 0;
  scanf("%d", &elv_cap);
  while( (elv_cap < 0 || elv_cap > 9)){
    printf("Wrong input, the capacity of elevators must be between 1 and 9 person(s)!\n");
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
/// @param void (no parameters)
/// @return the number of waiting people
int *destination_f(int *floors, int *people_w){
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
  // arr_c = NULL;//nullify our pointer
  return arr;
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
/// @return tthe length of the array
// long int strl(char arr[])
// {
//   int i = 0;//length
//   while(arr[i] != '\0')
//     i++;
//   return i;
// }






