#include "phonebook.h"

// constant strings definitions
const static char *const headerInformation =
    "ID\tNAME\tSECOND NAME\tPHONE NUMBER";

const static char *const recordNotFound = "No such record";

const static char *const incorrectInput = "Incorrect input";

const static char *const successMessage = "Success!";

// static functions declarations
// requests subscribers ID from keyboard
static int RequestID(void);

// requests subscribers name from keyboard
static char* RequestName(void);

// requests subscribers second name from keyboard
static char* RequestSecondName(void);

// requests subscribers phone number from keyboard
static char* RequestPhoneNumber(void);

// returns true if some requested information was left empty
static bool IsEmptyInput(PhoneBook *subscriber);

// returns true if passed subscriber exists in the list
static bool IsExist(PhoneBook *phone_book_head, PhoneBook *subscriber);

// creates a new subscriber node and returns pointer to it.
inline static PhoneBook *CreateNewSubscriber(void);

struct PhoneBook {
  unsigned int id;
  char *name;
  char *second_name;
  char *phone_number;
  struct PhoneBook *next;
  struct PhoneBook *prev;
};

inline static PhoneBook *CreateNewSubscriber(void) {
  PhoneBook *new_subscriber = (PhoneBook *) malloc(sizeof(PhoneBook));
  new_subscriber->name = RequestName();
  new_subscriber->second_name = RequestSecondName();
  new_subscriber->phone_number = RequestPhoneNumber();
  new_subscriber->next = NULL;
  new_subscriber->prev = NULL;
  return new_subscriber;
}

static bool IsEmptyInput(PhoneBook *subscriber) {
  if (isEmpty(subscriber->name) || isEmpty(subscriber->name)
      || isEmpty(subscriber->phone_number))
    return true;
  else
    return false;
}

static bool IsExist(PhoneBook *phone_book_head, PhoneBook *subscriber) {
  while (phone_book_head != NULL) {
    if (strcmp(phone_book_head->name, subscriber->name) == 0
        && strcmp(phone_book_head->second_name, subscriber->second_name) == 0
        && strcmp(phone_book_head->phone_number, subscriber->phone_number) == 0) {
      return true;
    }
    phone_book_head = phone_book_head->next;
  }
  return false;
}

inline void DeleteSubscriber(PhoneBook **subscriber) {
  free((*subscriber)->name);
  free((*subscriber)->second_name);
  free((*subscriber)->phone_number);
  free(*subscriber);
}

void DeleteAllSubscribers(PhoneBook **phone_book_head) {
  PhoneBook *subscriber;
  while (phone_book_head != NULL) {
    subscriber = *phone_book_head;
    *phone_book_head = (*phone_book_head)->next;
    DeleteSubscriber(&subscriber);
  }
}

static int RequestID(void) {
  unsigned int id = 0;
  int id_length = 2;
  const char * const idMessage = "Enter the ID: ";
  printf(idMessage);
  char *id_string = CreateString(id_length);
  id = strtol(id_string, NULL, 10);
  return id;
}

static char* RequestName(void) {
  unsigned int name_length = 32;
  const char * const nameMessage = "Enter the name: ";
  printf(nameMessage);
  char *name = CreateString(name_length);
  return name;
}

static char* RequestSecondName(void) {
  unsigned int second_name_length = 32;
  const char * const second_nameMessage = "Enter the second name: ";
  printf(second_nameMessage);
  char *second_name = CreateString(second_name_length);

  return second_name;
}

static char* RequestPhoneNumber(void) {
  unsigned int phone_number_length = 10;
  const char * const phone_numberMessage = "Enter the phone_number: ";
  printf(phone_numberMessage);
  char *phone_number = CreateString(phone_number_length);

  return phone_number;
}

void DeleteSubscriberByID(PhoneBook **phone_book_head) {
  PhoneBook *subscriber = *phone_book_head;
  unsigned int id = RequestID();
  //search for  subscriber
  while (subscriber != NULL) {
    if (subscriber->id == id) {
      break;
    }
    subscriber = subscriber->next;
  }
  // base case
  if (*phone_book_head == NULL || subscriber == NULL) {
    puts(recordNotFound);
    return;
  }
  // if node to be deleted is phone_book_head node
  if (*phone_book_head == subscriber)
    *phone_book_head = subscriber->next;
  // change next only if node to be deleted is NOT the last node
  if (subscriber->next != NULL)
    subscriber->next->prev = subscriber->prev;
  // change prev only if node to be deleted is NOT the first node
  if (subscriber->prev != NULL)
    subscriber->prev->next = subscriber->next;
  // finally, free the memory occupied by subscriber
  DeleteSubscriber(&subscriber);
  puts(successMessage);
  return;
}

void AddSubscriber(PhoneBook **phone_book_head) {
  PhoneBook *temp = *phone_book_head;
  PhoneBook *new_subscriber = CreateNewSubscriber();

  // if entered strings are empty or entered subscriber already exists in the list
  if (IsEmptyInput(new_subscriber) || IsExist(*phone_book_head, new_subscriber)) {
    puts(incorrectInput);
    return;
  }

  // if it's the first subscriber
  if (*phone_book_head == NULL) {
    new_subscriber->id = 1;
    *phone_book_head = new_subscriber;
  } else {
    while (temp->next != NULL) {
      temp = temp->next;  // Go To last Node
    }
    new_subscriber->id = temp->id + 1;
    temp->next = new_subscriber;
    new_subscriber->prev = temp;
  }
  puts(successMessage);
}

void FindSubscriberByName(PhoneBook *phone_book_head) {
  PhoneBook *subscriber = phone_book_head;
  char *name = RequestName();
  bool record_exists = false;
  puts(headerInformation);
  while (subscriber != NULL) {
    if (strcmp(subscriber->name, name) == 0) {
      PrintSubscriber(subscriber);
      record_exists = true;
      puts("");
    }
    subscriber = subscriber->next;
  }
  if (!record_exists) {
    puts(recordNotFound);
  }
  puts("");
  free(name);
}

void FindSubscriberByID(PhoneBook *phone_book_head) {
  PhoneBook *subscriber = phone_book_head;
  unsigned int id = RequestID();
  if(id == 0) {
    puts(incorrectInput);
    return;
  }
  bool record_exists = false;
  puts(headerInformation);
  while (subscriber != NULL) {
    if (subscriber->id == id) {
      PrintSubscriber(subscriber);
      record_exists = true;
      puts("");
    }
    subscriber = subscriber->next;
  }
  if (!record_exists) {
    puts(recordNotFound);
  }
  puts("");
}

inline void PrintSubscriber(PhoneBook *phoneBook) {
  printf("%d\t", phoneBook->id);
  printf("%s\t", phoneBook->name);
  printf("%s\t", phoneBook->second_name);
  printf("\t%s", phoneBook->phone_number);
}

void PrintAllSubscribers(PhoneBook *phone_book_head) {
  PhoneBook *subscriber = phone_book_head;
  puts(headerInformation);
  while (subscriber != NULL) {
    PrintSubscriber(subscriber);
    subscriber = subscriber->next;
    puts("");
  }
  puts("");
}
