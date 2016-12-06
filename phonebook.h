/*
 ============================================================================
 Name        : phonebook.h
 Author      : Maximov V.K.
 Version     : 0.1
 Description : Contains all functions that you need to work with PhoneBook struct
 ============================================================================
 */

#ifndef PHONEBOOK_H_
#define PHONEBOOK_H_
#include <string.h>
#include <stdio.h>
#include "stringtools.h"

typedef struct PhoneBook PhoneBook;

// adds subscriber to the list
void AddSubscriber(PhoneBook **phone_book_head);

// deletes subscriber by id
void DeleteSubscriberByID(PhoneBook **phone_book_head);

// deletes all subscribers
void DeleteAllSubscribers(PhoneBook **phone_book_head);

// search subscriber by id
void FindSubscriberByID(PhoneBook *phone_book_head);

// search subscriber by name
void FindSubscriberByName(PhoneBook *phone_book_head);

// print all subscribers from list to the console
void PrintAllSubscribers(PhoneBook *phone_book_head);

#endif
