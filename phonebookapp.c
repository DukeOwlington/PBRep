#include "phonebookapp.h"

// constant strings definitions
const static char *const menuChoice = "1: Add subscriber\n"
    "2: Delete subscriber by name\n"
    "3: Find subscriber by ID\n"
    "4: Find subscriber by name\n"
    "5: Print all subscribers\n"
    "6: Quit";

const static char *const incorrectMessage = "Incorrect choice";

enum MenuPoints {
  ADD_SUBSCRIBER = 1,
  DELETE_SUBSCRIBER,
  FIND_BY_ID,
  FIND_BY_NAME,
  PRINT_SUBSCRIBERS,
  QUIT
};

// print menu points string
inline void printMenu(void) {
  puts(menuChoice);
}

int main(void) {
  MenuPoints menu_point;
  PhoneBook *phone_book = NULL;
  while (menu_point != QUIT) {
    printMenu();
    scanf("%d", (int*) &menu_point);
    getchar();
    switch (menu_point) {
      case ADD_SUBSCRIBER:
        AddSubscriber(&phone_book);
        break;
      case DELETE_SUBSCRIBER:
        DeleteSubscriberByID(&phone_book);
        break;
      case FIND_BY_ID:
        FindSubscriberByID(phone_book);
        break;
      case FIND_BY_NAME:
        FindSubscriberByName(phone_book);
        break;
      case PRINT_SUBSCRIBERS:
        PrintAllSubscribers(phone_book);
        break;
      case QUIT:
        DeleteAllSubscribers(&phone_book);
        break;
      default:
        puts(incorrectMessage);
        break;
    }
  }
  return EXIT_SUCCESS;
}
