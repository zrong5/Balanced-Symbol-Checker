#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
int DebugMode;

typedef struct Stack{
  char *arr;
  int size;
  int top;
}Stack;

//--------------------------------------------------------------
//this function initialize the stack
void initialize_stack(struct Stack *a){
  //sets stack size to 2
  a -> size = 2;
  //dynamically allocate space for the stack
  a -> arr = (char*)malloc (a -> size * sizeof(char));
  //predefine the top position of the stack
  a -> top = -1;
}

//--------------------------------------------------------------
//this function will grow the stack linearly
void grow_stack(struct Stack *a){
  char *temp;
  int i;

  /*dynamically allocate a new temporary stack with
  2 additional spaces to hold the original stack*/
  if(DebugMode == TRUE){
    printf("growing the array.....\n");
    printf("current size is: %d, current top value is: %d\n", a->size, a->top);
  }
  temp = (char*)malloc ((a -> size + 2) * sizeof(char));
  //copys all the element into new stack
  for(i = 0; i < a -> size; i++){
    temp[i] = a -> arr[i];
  }
  if(DebugMode == TRUE){
    printf("number of element being copied: %d\n", i);
  }
  //frees up the old Stack
  free(a -> arr);
  //assign old stack to temporary stack
  a -> arr = temp;
  //increment stack size by 2
  a -> size += 2;
  if(DebugMode == TRUE){
    printf("the size is now: %d, top element is: %c\n", a->size, a->arr[a->top]);
  }
}

char top(Stack *a){
  return a -> arr[a -> top];
}

//--------------------------------------------------------------
//this function pushes a character onto the stack
void push(struct Stack *a, char c){
  if(DebugMode == TRUE){
    printf("pushing onto the stack....\n");
    printf("symbol being pushed: %c, top value was: %d\n", c, a->top);
  }
  //if the top position is >= to current size, grows stack
  if( a -> top + 1 >= a -> size){
    //calls the grow stack function
    grow_stack(a);
  }
  //increment top position by 1
  (a -> top) += 1;
  //set top value to character passed in
  a -> arr[a -> top] = c;
  if(DebugMode == TRUE){
    printf("top symbol is now: %c, top value is now: %d\n\n",  a->arr[a->top], a->top);
  }
}

//--------------------------------------------------------------
//this function pops the top of the stack
void pop(struct Stack *a){
  if(DebugMode == TRUE){
    printf("popping off the stack....\n");
    printf("symbol being popped: %c, top value was: %d\n", a->arr[a->top], a->top);
  }
  //pops if the array is not empty
  if(a -> top > -1){
    //change previous top element to null
    a->arr[a->top] = '\0';
    //decrement the top value by one
    a -> top -= 1;
  }
  else{
    //error message is user is trying to pop an empty array
    printf("the array is already empty...pop failed...\n");
  }

  if(DebugMode == TRUE){
    if(a->top < 0){
      printf("list is empty, top value is now: %d\n\n", a->top);
    }
    else{
      printf("top symbol is now: %c, top value is now: %d\n\n", a->arr[a->top], a->top);
    }
  }
}

//--------------------------------------------------------------
//checks if array is empty
int is_empty(struct Stack *a){
  //if top position is -1 or less, array is empty
  if(a -> top < 0)
    return TRUE;
  else
    return FALSE;
}

//--------------------------------------------------------------
//checks if char is a closing symbol true or false is returned
int is_closing_symbol(char ch){
  switch(ch){
    case '}': return TRUE; break;
    case ')': return TRUE; break;
    case ']': return TRUE; break;
    case '>': return TRUE; break;
    default: return FALSE;
  };
}

//--------------------------------------------------------------
//checks if char is an opening symbol true or false is returned
int is_opening_symbol(char ch){
 switch(ch){
   case '{': return TRUE; break;
   case '(': return TRUE; break;
   case '[': return TRUE; break;
   case '<': return TRUE; break;
   default: return FALSE;
 };
}

//--------------------------------------------------------------
/* If expression is not balanced, this function is called.
The first parameter will receive the symbol that needed to
be matched, and the second parameter will take an integer
indicating if a closing or opening symbol is needed to be
returned. */
char get_matching_symbol(char ch){
  switch(ch){
    case '{': return '}'; break;
    case '(': return ')'; break;
    case '[': return ']'; break;
    case '<': return '>'; break;
    case '}': return '{'; break;
    case ')': return '('; break;
    case ']': return '['; break;
    case '>': return '<'; break;
    default: return '*';
  };
}

//--------------------------------------------------------------
/*this function will print the missing that symbol corresponds
*to the symbol being passed in*/
void print_missing_symbol(char b, int pos){
  int i;
  //prints empty spaces corresponding to position of missing symbol
  for(i = 0; i < pos; i++){
    printf(" ");
  }
  /*if symbol is a closing symbol, print missing and calls
  *get_matching_symbol function to return the corresponding symbol*/
  if(is_closing_symbol(b)){
    printf("^missing %c\n", get_matching_symbol(b));
  }
  //else if symbol is an opening symbol, do the same as above
  else if(is_opening_symbol(b)){
    printf("^expecting %c\n", get_matching_symbol(b));
  }
}

//--------------------------------------------------------------
/*this function checks if user input expression is balanced
*if not balanced, the function will invoke print_missing_symbol
*function to print out the missing symbol*/
void check_balance(struct Stack *a, char b[]){
  int i = 0;
  //loops through user input array until '\0' is reached
  while(b[i] != '\0'){
    //if element is an opening symbol, push onto stack
    if(is_opening_symbol(b[i])){
      push(a, b[i]);
      i++;
      continue;
    }
    //if element is a closing symbol checks for following conditions
    if(is_closing_symbol(b[i])){
      /*if stack is not empty, checks if closing symbol matches
      the symbol on top of the stack*/
      if(!is_empty(a)){
        //if symbols match, pop the top of the stack
        if(get_matching_symbol(b[i]) == a->arr[a->top]){
          pop(a);
          i++;
          continue;
        }
        //if no match, prints error by calling print_missing_symbol
        else{
          print_missing_symbol(a->arr[a->top], i);
          return;
        }
      }
      //if the list is empty, call the print_missing_symbol function
      else{
        print_missing_symbol(b[i], i);
        return;
      }
    }
    i++;
  }

  //if the list is empty means the expression is balanced
  if(is_empty(a)){
    printf("This expression is balanced.\n\n");
  }
  //if not, print error using print_missing_symbol
  else{
    print_missing_symbol(a->arr[a->top], i - (a -> top + 1));
  }
}

//--------------------------------------------------------------
//this function reset the stack and user input array for reuse
void reset(struct Stack *a, char input[]){
  int i = 0;
  //frees the stack for reuse
  free((*a).arr);
  //set all elements in user input into null
  while (input[i] != '\0' ){
    input[i] = '\0';
    i++;
  }
  //reinitialize the stack
  initialize_stack(a);
}

//--------------------------------------------------------------
//this function prints out the instructions of the program
void print_instructions(){
  printf("Author:                   Zhilang Rong\n");
  printf("Date:                     02/04/2018\n");
  printf("NetID:                    zrong5\n");
  printf("Program:                  Balanced Symbol Checker\n\n");
  printf("This program will allow you to check rather or not\n");
  printf("a set of expression is balanced and will output the\n");
  printf("spot at which what symbol is missing if not balanced\n");
  printf("To end this program, simply enter 'Q' or 'q'\n\n");
}

int main(int argc, char *argv[]){
  struct Stack a;
  int i;
  DebugMode = FALSE;

  for(i = 0 ; i < argc ; i++ ){
    if(strcmp(argv[i], "-d") == 0){
      DebugMode = TRUE;
    }
  }
  //initialize user input array with size of 300
  char input[300];
  //sets all 300 elements to null
  i = 0;
  while (input[i] != '\0' ){
    input[i] = '\0';
    i++;
  }
  //initialize the stack with size 2 allocated
  initialize_stack(&a);
  //prints instructions on how the program works
  print_instructions();
  //continuously read in user input until 'q' or 'Q' is entered
  while(1){
    //instructs user to enter a line of input
    printf("Please enter a set of expressions: \n");
    //stores the line of input into user input array
    fgets(input, 300, stdin);
    //if user enters q or Q, quits the program
    if(input[0] == 'q' || input[0] == 'Q'){
      printf("Quitting...\n");
      return 1;
    }
    //checks if expression is balanced and prints out error if need be
    check_balance(&a, input);
    //resets the stack ones operations are performed
    reset(&a, input);
  }
  return 0;
}
