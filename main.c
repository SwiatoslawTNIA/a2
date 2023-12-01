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

//function prototyping
long int strl(char arr[]);

void greeting(void);
char *nameHotel(void);
int numFloors(char *hotel_name);
int numElevators(char *totel_name);
int elevCapacity(char *hotel_name);
int people_w(void);

int main(void)
{
  greeting();
  char *p = nameHotel();//return a pointer to the string hotelName;
  int floors = numFloors(p);//collect the number of floors;
  int elevators = numElevators(p);//collect the number of elevators;
  int elev_cap = elevCapacity(p);//collect the elevator capacity;
  int people_waiting = people_w();//collect the amount of waiting people;
  printf("%s, %d, %d, %d, %d", p, floors, elevators, elev_cap, people_waiting);

  //freeing the memory
  free(p);
  return 0;
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
char *nameHotel(void)
{
  char *string = (char *)malloc(sizeof(size_t) * 100);//long strings will not be used;
  if(string == NULL){
    printf("Unable to allocate memory for a name of the hotel.");
  }
  printf("Enter the name of the hotel:\n >");
  char *str_p = string;
  fgets(str_p, sizeof(size_t)* 100, stdin);
  return string;
}
//---------------------------------------------------------------------------------------------------------------------
///
/// This function collects the number of floors and returns the result in type int;
/// @param *hotel_name takes a pointer to the name of the hotel;
/// @return the number of floors
int numFloors(char *hotel_name)
{
    //dynamic memory allocation:
    // int *p = (int *)malloc(sizeof(int));
    printf("Enter the number of floors in hotel %s:\n > ", hotel_name);
    int digit  = 0;
    scanf("%d", &digit);
    while( (digit > 10 || digit < 3)){
      printf("Wrong input, the number of floors must be between 3 and 10!\n");
      scanf("%d", &digit);
    }
  return digit;
}
//---------------------------------------------------------------------------------------------------------------------
///
/// This function collects the number of elevators and returns the result in type int;
/// @param *hotel_name takes a pointer to the name of the hotel;
/// @return the number of elevators
int numElevators(char *hotel_name)
{
    printf("Enter the number of elevators in hotel %s:\n > ", hotel_name);
    int elv_num  = 0;
    scanf("%d", &elv_num);
    while( (elv_num < 1 || elv_num > 5)){
      printf("Wrong input, the number of elevators must be between 1 and 5!\n");
      scanf("%d", &elv_num);
    }
  return elv_num;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function collects the elevator capacity and returns the result in type int;
/// @param *hotel_name takes a pointer to the name of the hotel;
/// @return the capacity of each elevator
int elevCapacity(char *hotel_name)
{
    printf("Enter the capacity of elevators in hotel %s:\n > ", hotel_name);
    int elv_cap  = 0;
    scanf("%d", &elv_cap);
    while( (elv_cap < 0 || elv_cap > 9)){
      printf("Wrong input, the capacity of elevators must be between 1 and 9 person(s)!\n");
      scanf("%d", &elv_cap);
    }
  return elv_cap;
}
//---------------------------------------------------------------------------------------------------------------------
///
/// This function collects the amount of waiting people and returns the result in type int;
/// @param void (no parameters)
/// @return the number of waiting people
int people_w(void)
{
    printf("Enter the number of people waiting on each floor:\n > ");
    int p_w  = 0;
    scanf("%d", &p_w);
    while( (p_w < 2 || p_w > 20)){
      printf("Wrong input, the number of people waiting on each floor must be between 2 and 20!\n");
      scanf("%d", &p_w);
    }
  return p_w;
}
//---------------------------------------------------------------------------------------------------------------------
///
/// This function collects the amount of waiting people and returns the result in type int;
/// @param void (no parameters)
/// @return the number of waiting people
int destination_floors(int floors)
{
    printf("Enter the number of people waiting on each floor:\n > ");
    int p_w  = 0;
    scanf("%d", &p_w);
    while( (p_w < 2 || p_w > 20)){
      printf("Wrong input, the number of people waiting on each floor must be between 2 and 20!\n");
      scanf("%d", &p_w);
    }
  return p_w;
}



//---------------------------------------------------------------------------------------------------------------------
///
///The function computes the length of the array through a while loop;
///
/// @param arr[] is an array;
/// @return tthe length of the array
long int strl(char arr[])
{
  int i = 0;//length
  while(arr[i] != '\0')
    i++;
  return i;
}






