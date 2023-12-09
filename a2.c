#include "a2.h"
/// @brief the main function
/// @param  void takes no parameters, the application is not configured for arguments
/// @return 0 if the application worked as concocted.
int main(void)
{
  int rsp = header();
  if(rsp == -1)
    return -1;
  else if(rsp == 0)
    return 0;
}
/// @brief takes the load from the main function, possible extension
/// @param  void no parameters
/// @return returns an integer value (0 if everything is alright.)
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

  int *dest_a_c = dest_arr;//we will change the dest array(probably)

  struct Elevator *elevator_space = build_elev(elevators, elev_cap, floors_num);
  struct Person *people_space = build_people(floors_num, people_waiting, dest_a_c);

  if(elevator_space == NULL || people_space == NULL)
  {
    printf("Out of memory! Program terminated!\n");
    return -1;
  }
  if(show_initial_state())
  {
    initial_state(hotel, floors_num, elevators, elev_cap, people_waiting, dest_arr, elevator_space, people_space);
  }
  //if false, than we do the following, if true, then we continue
  if(whether_start_simulation())
  {
    //show the final state:
    free_everything(hotel, floors_num, elevators, elev_cap, people_waiting, dest_arr);
    return 0;
  }else{
    if(show_all_steps())
    {
      main_sim(hotel, floors_num, elevators, elev_cap, people_waiting, dest_arr, elevator_space, people_space);
    } else
    {
    }
  }
  // freeing the memory
  free(elevator_space);
  free(people_space);
  free_everything(hotel, floors_num, elevators, elev_cap, people_waiting, dest_arr);
  return 0;
}
int main_sim(char *hotel, int *floors_number, int *elev, int *elev_cap,int *people_waiting, int *dest_arr,
struct Elevator *elevator_space, struct Person *people_space)
{

  int people_total = *people_waiting * *floors_number;
  //update the direction of people:
  //based on those directions, people will be assigned to the elevators, to move with them.
  update_people_direction(people_space, people_total);
  //until all the people reached their destination 
  int count = 0;
  while(!prove_destination(people_space, people_total) && count < 10)
  {
    //first people enter the elevator, then the elevators move:(on the next iteration)
    print_simulation_step();
    //assigs people to elevators, removes them from elevators, enables us to print elev_bottom and right section
    update_people(people_space,elevator_space, people_total, elev, floors_number);
    update_people_inelev(people_space, elevator_space, people_total);
    update_elevators_direction(elevator_space, elev, floors_number);
    update_elevator_floor(elevator_space, elev);//update our elevators
    //printing our hotel:
    print_hotel_name(hotel, elev);
    print_simulation_str(elevator_space, people_space, elev, people_waiting, floors_number, elev_cap);
    print_elevators_bottom(people_space,elevator_space, elev, people_total, floors_number);
    ++count;
    ++step;//update the step;
  }  
  return 0;
}
void print_simulation_str(struct Elevator *elevator_space, struct Person *people_space, int *elev, 
 int *people_waiting, int *floors_number, int *elev_cap)
{
  first_line_print(elev);
  int current_floor = 1;
  while(current_floor <= *floors_number)
  {
   print_simulation_row(elevator_space, people_space, elev, current_floor, people_waiting,
        floors_number, elev_cap);
    if(current_floor != *floors_number)
    {
      between_row(elev);
    }
    ++current_floor;
  }
  last_line_print(elev);
}
void first_line_print(int *elev_number)
{
   printf("++");
  int i = 0;
  while(*elev_number > i){
    printf("-----+");
    ++i;
  }
  printf("+\n");
}

void print_simulation_row(struct Elevator *elevator_space, struct Person *people_space, int *elev, 
int current_floor, int *people_waiting, int *floors_number, int *elev_cap)
{
  //both for people and elevators the floors start from 1
  printf("|");
  //floors will be from 0 to 9
    //move through each of the elevators:
  for(int i = 0; i < *elev; i++)//it is an index in our pointer array
  {
    if(elevator_space[i].floor == current_floor)//elevators are printed normally
    {
      printf("| ");
      printf("[%d]", *elev_cap - elevator_space[i].available);//elevator capacity -epc->available
      printf(" ");
    }else{
      printf("|     ");
    }
  }
  printf("||  ");
  //print the row:
  int size = 2 * *people_waiting;
  //move through eah person:
  char str[44] = "(";
  //move through each person:
  int count = 1;
  int lowest_current_floor = 1;
  while(lowest_current_floor <= *floors_number)//it is going to work
  {
    for(int i = 0; i < *people_waiting * (*floors_number);i++)
    {
      //we don't print based on the current floor, we print based on the initial floor of each person:
      if((people_space[i].original_floor == *floors_number - current_floor + 1) //reverse our floors
        && people_space[i].dest_floor == lowest_current_floor)
      //we will have to print it in ascending order:(in accordance with the destination floor)
        {
          //if person has reached it's destination, then we're going to print 0:
          if(people_space[i].dest_floor == -1)//because if the person reached its destination floor
          //then we set it's dest_floor to -1;
          {
            str[count] = '0';
            str[count + 1] = ',';
            count += 2;
          }else if(people_space[i].in_elevator == 1)//if person is in elevator:
          {
            str[count] = '-';
            str[count + 1] = ',';
            count += 2;
          }else if(people_space[i].in_elevator == 0)//if person is not in elevator and has not reached the 
          //destination yet
          {
            str[count] = '0' + people_space[i].dest_floor;
            str[count + 1] = ',';
            count += 2;
          }
        }
    }
    lowest_current_floor++;//now the lowest current floor will be updated
  }
  str[size] = ')';
  str[size  + 1] = '\0';
  printf("%s\n",str);
}

/// @brief updates the direction of each person, executes just once
/// @param people_space 
/// @param people_total 
void update_people_direction(struct Person *people_space, int people_total)
{
  for(int i = 0; i < people_total;++i)
  {
    //compute the direction of each person:
    if(people_space[i].current_floor > people_space[i].dest_floor)
    {
      people_space[i].direction = 1;//they need to move upwards
    }else if(people_space[i].current_floor < people_space[i].dest_floor)
    {
      people_space[i].direction = 0;//they need to move downwards
    }
  }
}
void update_elevators_direction(struct Elevator *elevator_space, int *elev, int *floors_number)
{
  for(int i = 0; i < *elev;++i)//move through each of the elevators:
  {
    //it changes the direction only at the top or at the bottom:
    if(elevator_space[i].floor == 1)
    {
      elevator_space[i].direction = 0;//downwards 0, upwards 1;
    }else if(elevator_space[i].floor == *floors_number)
    {
      elevator_space[i].direction = 1;
    }
  }
}
void update_people_inelev(struct Person *people_space, struct Elevator *elevator_space, int people_total)
{
  for(int i = 0; i < people_total;++i)
  {
    //what if people have reached their destination?
    if(people_space[i].dest_floor == people_space[i].current_floor)
    {
      //print the message:
      people_message(people_space[i].elev, people_space[i].dest_floor);
      people_space[i].dest_floor = -1;
      //we will also have to increase the capacity of our elevator:

      elevator_space[people_space[i].elev].available++;//increment(elev_cap) the elevator load of that person's 
      //elevator
      people_space[i].in_elevator = 0;//the person is no more in elevator
      people_space[i].elev = -1;//essentially expel that person from that elevator
    }
  }
  
}
/// @brief assign people to elevators, and remove people from elevators
/// @param people_space the pointer to the location on the heap with structs Person
/// @param elevator_space the pointer to the location on the heap with structs Elevator
/// @param people_total the total amount of people
/// @param elev the amount of elevators
/// @param floors_number the number of floors (of type integer pointer)
void update_people(struct Person *people_space, struct Elevator *elevator_space, int people_total,
 int *elev, int *floors_number)
{
    for(int i = 0; i < people_total;++i)
    {
      //if the person hasn't reached is destination floor:
      if(people_space[i].dest_floor != -1)
      {
        //move through each of the elevators, if it's current floor is people[i]'s current floor, and
        //it is not full, assign the person to the elevator;
        for(int j = 0; j < *elev; ++j)
        {
          if((elevator_space[j].available > 0 )
          && ((*floors_number - (elevator_space[j].floor) + 1) == people_space[i].current_floor)
          && people_space[i].in_elevator == 0)//we need to check if that person is not in another elevator
          //the upper condition checks if the elevator is on the same floor and is still "available"
          {
            if(elevator_space[j].direction == people_space[i].direction){
              //the direction of the elevator == the direction of person
              people_space[i].elev = elevator_space[i].index;
              people_space[i].in_elevator = 1;//true;
              elevator_space[i].available--;//decrement the load of the elevator
            }
          }
        }
      }
      
    }
  //if a person is assigned to an elevator, then in_elevator is changed, she will be displayed only in the bottom
  //not in the list of people on the right.
  //update the floor of each person:
  for(int i = 0; i < people_total;++i)
  {
    //move through each of the people and update their floor:
    //for that we need to determinte if the person is in elevator + determine the direction of each 
    //person's movement:
    if(people_space[i].in_elevator == 1)
    {
      //if it is in elevator
      if(people_space[i].direction == 1)//if person is moving upwards
      {
        people_space[i].current_floor++; 
      }
      if(people_space[i].direction == 0)
      {
        people_space[i].current_floor--;
      }
    }
  }
} 
void people_message(int elev, int dest_floor)
{
  printf("A person reached their destination floor %d with elevator %d.\n", dest_floor, elev);
}
/// @brief function proves if each person has reached it's destination
/// @param people_space a pointer to the people space
/// @param people_waiting a pointer to the number of people waiting
/// @param floors_number a pointer to the number of floors
/// @return false if anyone hasn't reached it's destination, true otherwise
int prove_destination(struct Person *people_space, int people_total)
{
  int value = TRUE;
  for(int i = 0; i < people_total;++i)
  {
    if(people_space[i].dest_floor != -1)
    {
      value = FALSE;
    }
  }
  return value;
}
/// @brief updates the elevators(for each simulation step)
/// @param elevator_space a pointer to the elevator space with elevator structures
/// @param elev a pointer to the number of elevators
void update_elevator_floor(struct Elevator *elevator_space, int *elev)
{
  for(int i = 0; i < *elev;++i)
  {
    if(elevator_space[i].direction == 1)
    {
      elevator_space[i].floor--;//move it up one floor(since we have to move in opposite direction)
    }else if(elevator_space[i].direction == 0)
    {
      elevator_space[i].floor++;//move it downwards, increase the floors;
    }
  }
}
/// @brief prints the elevators below each hotel structure
/// @param elevator_space is the pointer to the allocated elevators on the heap
/// @param elev_number pointer to number of elevators 
/// @param people pointer to the number of people 
void print_elevators_bottom(struct Person *people_space,struct Elevator *elevator_space, 
 int *elev_number, int people_total, int *floors_number)
{
  printf("Elevators:\n");
  //print the people with the lowest to the highest dest_floor first:
  int highest_dest_floor = 1;//it mustn't be one, not every person is starting from the first floor;
 
  for(int i = 0; i < *elev_number; i++)//we move through each of the elevators
  {
      //move through each of the people, if people[i] is in this elevator, print it, otherwise not;
    printf("%d: (",i);
    while(highest_dest_floor <= *floors_number)
    {
      for(int j = 0; j < people_total; ++j)
      {
        if(people_space[j].elev == elevator_space[i].index)
        {
        //if person is in this elevator:

        // if(pos(people_space[j].dest_floor - people_space[j].current_floor) == highest_dest_floor)
        // {
        //   //we have also to check if the person is in this elevator:
        //   if(people_space[j].elev == elevator_space[i].index)
        //   {
        //     printf("%d,", people_space[j].dest_floor);
        //   }
        }
      } 
      highest_dest_floor++;
    }
    printf("\b)\n");
  }
}
/// @brief prints the step of the function
/// @param  void no parameters;
void print_simulation_step(void)
{
  printf("=== Simulation Step <%d> ===\n", step);
}
/// @brief free the  allocated data
/// @param hotel pointer to the hotel name
/// @param floors_num pointer to the number of floors
/// @param elevators pointer to the elevators
/// @param elev_cap pointer to the capacity of elevators
/// @param people_waiting pointer to the people waiting
/// @param dest_arr pointer to the array with destination values
void free_everything(char *hotel, int *floors_num, int * elevators, int *elev_cap, int * 
  people_waiting, int *dest_arr)
{
  free(hotel);
  free(floors_num);
  free(elevators);
  free(elev_cap);
  free(people_waiting);
  free(dest_arr);
}
/// @brief asks the user for data
/// @param  void takes no values in
/// @return returns 1 if user selected end result, and 2 if user selected all steps
int show_all_steps(void)
{
  char str[20];
  int valid_input = -1;
  int count = 0; 
  //clear the buffer:
  char c ;
  while((c  = getchar()) != '\n')
  {
    continue;
  }
  getchar();//get that new line
  while(valid_input == -1 && count < 10)
  {
    printf("Show all steps of the simulation? (\"all steps\"/\"end result\"):\n > ");
    fgets(str, 19, stdin);
    if(str[strl(str) - 1] == '\n')
    {
      str[strl(str) - 1] = '\0';
    }
    if(str_com(str, "all steps"))
    {//compare the strings
      valid_input = 1;
    }else if(str_com(str, "end result"))
    {
      valid_input = 0;
    }    
    ++count;
  }
  return valid_input;
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
/// returns a pointer to that name
/// @param void function doesn't take any input value
/// 
/// @return the array pointer to the name of the hotel, that was dinamically allocated;
char *hotel_name(void)
{
  char *string = (char *)malloc(sizeof(size_t) * 100);//long strings will not be used;
  if(string == NULL)
  {
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
  // hotel1.name = string;
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
  if(p == NULL)
  {
    printf("Out of memory! Program terminated!\n");
    return p;
  }
  printf("Enter the number of floors in hotel %s:\n > ", hotel_name);    
  int digit  = 0;
  scanf("%d", &digit);
  while( (digit > 10 || digit < 3))
  {      
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
  if(elv_c_p == NULL)
  {
    printf("Out of memory! Program terminated!\n");
    return elv_c_p;
  }
  printf("Enter the capacity of elevators in hotel %s:\n > ", hotel_name);
  int elv_cap  = 0;
  scanf("%d", &elv_cap);
  while( (elv_cap <= 0 || elv_cap > 9))
  {
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
  if(p == NULL)
  {
    printf("Out of memory! Program terminated!\n");
    return p;
  }
  printf("Enter the number of people waiting on each floor:\n > ");
  int p_w  = 0;
  scanf("%d", &p_w);
  while( (p_w < 2 || p_w > 20))
  {
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
  int a[*floors][*people_w];
  if(arr == NULL)
  {
    printf("Out of memory! Program terminated!\n");
    return arr;
  }
  int current_floor = 0, can_proceed = FALSE, p = 0, j = 0;
  while(current_floor < *floors){//!carefull with the floors
    printf("Enter the destination floors of the people [floor: %d]:\n > ", current_floor);
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
        printf("Wrong input, the destination floor %d is out of range (0 to %d)!\n",num, *floors);
        can_proceed = FALSE;
        break;
      }else if(num == current_floor)
      {
        printf("Wrong input, the destination floor cannot be the current floor!\n");
        can_proceed = FALSE;//reset our value;
        break;
      }//if these conditions are fulfilled:
      if((num >= 0) && (num <= (*floors)))
      {
        if(num != current_floor)
        {
          a[p][j] = num;
          can_proceed = TRUE;
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
  int *arr_c = arr;
  for (int i = *floors - 1; i >= 0; i--)//we had to start with floor - 1;
  {
    for (int j = 0; j < *people_w; j++)
    {
      *arr_c = a[i][j];
      arr_c++;
    }    
  }
  return arr;
}
/// @brief This function asks to show the initial state
/// @param  void no parameters
/// @return int if show the initial state == true, then returns 1, else returns 0
int show_initial_state(void)
{
  int done = FALSE;
  int show = 0;
  while(done == FALSE)
  {
    printf("Show the initial state? (\"yes\"/\"no\"):\n > ");
    char str[100];
    scanf("%s", str);
    int length = strl(str);//check the length
    if(length > 3)
    {
      continue;
    }else if(length == 3)
    { //convert the string to lowercase:
    //if the length of the string is 3:
      char *str_p = low(str);
      if(str_com(str_p, "yes"))
      {//compare the strings
        // printf("\n <yes>\n");
        show = 1;
        return show;
      }else if(str_com(str_p, "no "))
      {
        show = 0; 
        return show;
      }
    }else if(length == 2)
    {
      char *str_p = low(str);
      if(str_com(str_p, "yes"))
      {//compare the strings
        // printf("\n <yes>\n");
        show = 1;
        return show;
      }else if(str_com(str_p, "no"))
      {
        // printf("\n <no>\n");
        show = 0;
        return show;
      }
    }
    
  }
  return show;
}
/// @brief prompts and ask about the continuation of the simulation
/// @param  void no parameters
/// @return returns 0 if start otherwise returns 1
int whether_start_simulation(void)
{
  int done = FALSE;
  int start = 0;
  while(done == FALSE)
  {
    printf("Start the simulation? (\"start\"/\"skip\"):\n > ");
    char str[10];
    scanf("%6s", str);
    char *str_p = low(str);
    if(str_com(str_p, "start")){//compare the strings
      done = TRUE;
      start = 0;
      return start;
    }else if(str_com(str_p, "skip"))
    {  
      done = TRUE; 
      start = 1;
      return start;
    }    
  }
  puts("The whether function executed correctly.");
  return start;
}
/// @brief controls the initial state of the simulation show(the first display of the hotel)
/// @param hotel a pointer to the hotel name
/// @param floors_number a pointer to the number of floors
/// @param elev a pointer to the number of elevators
/// @param elev_cap a pointer to the number of elevator capacity
/// @param people_waiting a pointer to the number of people waiting
/// @param dest_arr a pointer to the array of all people's destinations
/// @param struct Elevator *elevator_space a pointer to the elevator_space
/// @param struct Person *people_space a pointer to the people_space
void initial_state(char *hotel,int *floor_n,  int *elev, int *elev_cap, int *people_waiting,
 int *dest_arr, struct Elevator *elevator_space, struct Person *people_space)
{
  printf("\n=================\n");
  printf("  INITIAL STATE\n=================\n\n");
  struct Elevator *esc_c_1 = elevator_space;
  struct Person *psc_c_1 = people_space;//any changes that we make, we still have reference to them
  show_simulation(hotel, esc_c_1, psc_c_1 , elev, floor_n, people_waiting);//floors from 0 to 9
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
int show_simulation(char *hotel_n, struct Elevator *elevator_space, struct Person *people_space, int *en, int *floors, int *people)
{
  //crete a copy:
  struct Elevator *es = elevator_space;
  struct Person *ps = people_space;
  int *elev_number = en;
  int *floor = floors;
  int *p_c = people;
  int current_floor = 1;
  print_hotel_name(hotel_n, en);
  print_top(elev_number);
  while(current_floor <= *floor)
  {
    print_row(es, ps, elev_number,  current_floor, p_c, floor);//floors from 0 to 9
    if(current_floor != *floor)
    {
      between_row(en);
    }
    ++current_floor;
  }
  last_line_print(elev_number);
  return 0;
}

/// @brief prints the row of the hotel
/// @param ep elevator pointer of type Elevator structure
/// @param pp person pointer of type Person structure
/// @param en pointer to the number of elevators
/// @param current_floor the current floor
/// @param people_waiting pointer to the amount of people waiting
/// @param floors pointer to the array of all people's destinations
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
      printf("[%d]", epc->available);//elevator capacity -epc->available
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
  for(int i = 1; i <= *people_waiting * (*floors);i++)
  {
    if(ppp->current_floor == current_floor)//here we print the people in any order!!
    {
      // printf("%d", ppp->dest_floor);
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


///the function prints the line to separate each row
/// @return no return;
void print_top(int *elev_number)
{
  printf("++");
  int i = 0;
  while(*elev_number > i)
  {
    printf("-----+");
    ++i;
  }
  printf("+\n");
}
///
///the function prints the last line of the hotel
/// @return no return;
void last_line_print(int *elev_number)
{
  printf("++");
  int i = 0;
  while(*elev_number > i){
    printf("-----+");
    ++i;
  }
  printf("+\n\n");
}

/// @brief prints the middle part of the structure (the space between the rows)
/// @param elev_number accepts a number of elevators;
void between_row(int *elev_number)
{
  printf("||");
  int i = 0;
  while(*elev_number > i)
  {
    if(*elev_number == i + 1)
    {
      printf("-   -|");
    }else{
      printf("-   -+");
    }
  ++i;
  }
  printf("|\n");
}


/// @brief function creates elevator space on the heap;
/// @param elev pointer to the number of elevators
/// @param elev_cap pointer to the capacity of elevators
/// @param floor_n pointer to the number of floors
/// @return the pointer to the elevator space
struct Elevator* build_elev(const int *elev, const int *elev_cap,const int *floor_n)
{
  //initialize elevators:
  struct Elevator* elevators = (struct Elevator*)malloc(sizeof(struct Elevator) * *elev);
  if(elevators == NULL)
  {
    printf("Unable to allocate memory for a name of the hotel.");
    return NULL;
  }
  struct Elevator *esc = elevators;//create a copy of the pointers;
  for(int i = 0; i < *elev; i++)
  {
    esc->cap = *elev_cap;
    
    if(i % 2 == 0)
    {//it's even
      esc->floor = *floor_n;//standard notation
      esc->direction = 1;
    }else
    {
      esc->floor = 1;//we start from floor 1
      esc->direction = 0;
    }
    // esc->cur = *elev_cap;
    esc->available = *elev_cap;
    //this is how we keep track of each elevator
    esc->index = i;
    esc++;
  }
  return elevators;
}
//---------------------------------------------------------------------------------------------------------------------
///
/// function creates people space on the heap
///
/// @param floors pointer to the number of floors;
/// @param people_waiting pointer to the number of people_waiting;
/// @param dest_a_c pointer to the array of destinations;
/// @return the pointer to the allocated space for all elevators structs
struct Person* build_people(const int *floors,const int *people_waiting, int *dest_a_c)
{
  struct Person* people = (struct Person*)malloc(sizeof(struct Person) * (*floors) * (*people_waiting));
  if(people == NULL)
  {
    printf("Unable to allocate memory for a name of the hotel.");
    return NULL;
  }
  struct Person *psc = people;//copied
  for(int i = 1; i <= *floors; i++)
  {
    //for each person on the floor:
    for(int j = 0; j < *people_waiting; j++)
    {
    psc->current_floor = i;
    psc->original_floor = i;
    psc->dest_floor = *dest_a_c;
    psc->in_elevator = 0;
    psc->elev = -1;//from the beginning the each person's elevator will be -1
    ++dest_a_c;
    ++psc;//update the pointer
    }
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

  int second_row_l = (total - strl(hotel_n));

  if(second_row_l % 2 == 0)
  {
    int i = 0;
    for(; i < second_row_l / 2 - 1; i++)
    {//odd if string is even
      str_b[i] = ' ';
    }
    int j = 0;
    for(; j < strl(hotel_n);j++)
    {
      str_b[i + j] = hotel_n[j];
    }
    for(int k = 0; k < second_row_l / 2; k++)
    {
      str_b[i + j + k] = ' ';
    }
    printf("++%s++\n", str_b);
  }else{
    int i = 0;
    for(; i < second_row_l / 2; i++)
    {
      str_b[i] = ' ';
    }
    int j = 0;
    for(; j < strl(hotel_n);j++)
    {
      str_b[i + j] = hotel_n[j];
    }
    for(int k = 0; k < second_row_l / 2; k++)
    {
      str_b[i + j + k] = ' ';
    }
    printf("++%s++\n", str_b);
  }
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
    if(*b >= 65 && *b <= 90)
    {
      *b = *b + 32;
    }
    b++;
  }//add that newLine
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
  if(strl(str1) != strl(str2)){
    same = FALSE;
  }
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
/// @brief copies the elements of the second string to the first string
/// @param arr1 is the char array, where str2 will be copied
/// @param arr2 is the char array, from where the data  will be copied to str2
/// @return void
void str_copy(char str1[], char str2[])
{
  for(int i = 0; str2[i] != '\0';++i)
  {
    str1[i] = str2[i];
  }
}
/// @brief function strips the string of the newLine characters;
/// @param arr array to be striped
void strip(char arr[])
{
  char *c = arr;
  for(; *c != '\n'; ++c)
    ;
  //move to the end of the array;
  *c = '\0';//strip the string;
}
/// @brief returns an absolute value of the object
/// @param n a number
int pos(int n)
{
  if(n >= 0)
    return n;
  else 
    return -n;
}