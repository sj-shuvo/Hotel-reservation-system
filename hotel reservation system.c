#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    int id;
    char name[100];
    char phoneNumber[15];
    int roomNumber;
    int days;
    float rate;
    char room_type[20];
    char arrivalDate[12];
    int parking;
    char carNumber[20];
} Reservation;

Reservation reservations[100];
int reservationCount = 0;


int standardRooms[30];
int deluxeRooms[15];
int suiteRooms[5];


void initializeRooms() {
    for (int i = 0; i < 30; i++) standardRooms[i] = 101 + i;
    for (int i = 0; i < 15; i++) deluxeRooms[i] = 201 + i;
    for (int i = 0; i < 5; i++) suiteRooms[i] = 301 + i;
}

void login();
void bookRoom();
void checkRoomAvailability();
void viewAllReservations();
void cancelReservation();
void searchCustomerRecord();
void editRecord();
void checkout();
void revenueGenerator();
void parkingManagement();
void clearScreen();
void exitProgram();

int main() {
    initializeRooms();
    int i = 0;
    int choice;

    time_t t;
    time(&t);
    system("cls");
    printf("\t\t*********************************************\n");
    printf("\t\t*                                           *\n");
    printf("\t\t*       ----------------------------        *\n");
    printf("\t\t*         HOTEL MANAGEMENT SYSTEM           *\n");
    printf("\t\t*       ----------------------------        *\n");
    printf("\t\t*                                           *\n");
    printf("\t\t*                                           *\n");
    printf("\t\t*                                           *\n");
    printf("\t\t*********************************************\n\n\n");
    for (i = 0; i < 80; i++)
        printf("-");
    printf("\nCurrent date and time : %s", ctime(&t));
    for (i = 0; i < 80; i++)
        printf("-");
    printf(" \n Press any key to continue:");

    getchar();
    system("cls");
    login();
    system("cls");

    while (1) {
        clearScreen();
        printf("*****************************************\n");
        printf("*          HOTEL RESERVATION SYSTEM     *\n");
        printf("*****************************************\n\n\n");
        printf("1. Book a Room\n");
        printf("2. Check Room Availability\n");
        printf("3. View All Reservations\n");
        printf("4. Cancel Reservation\n");
        printf("5. Search Customer Record\n");
        printf("6. Edit Record\n");
        printf("7. Checkout\n");
        printf("8. Revenue Report\n");
        printf("9. Parking Management\n");
        printf("10. Exit\n");
        printf("***************\n");
        printf("\n");
		for(i=0;i<80;i++)
		printf("-");
	    printf("\nCurrent date and time : %s",ctime(&t));
	    for(i=0;i<80;i++)
		printf("-");
		printf("\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookRoom();
                break;
            case 2:
                checkRoomAvailability();
                break;
            case 3:
                viewAllReservations();
                break;
            case 4:
                cancelReservation();
                break;
            case 5:
                searchCustomerRecord();
                break;
            case 6:
                editRecord();
                break;
            case 7:
                checkout();
                break;
            case 8:
                revenueGenerator();
                break;
            case 9:
                parkingManagement();
                break;
            case 10:
                exitProgram();
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }

    return 0;
}

void clearScreen() {
    system("cls");
}

void login() {
    char username[50], password[50];
    clearScreen();
    printf("*****************************************\n");
    printf("*         LOGIN TO HOTEL SYSTEM         *\n");
    printf("*****************************************\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        printf("  \n\n\n       WELCOME !!!! LOGIN IS SUCCESSFUL\n\n\n");
    } else {
        printf("Invalid credentials! Exiting...\n");
        exit(1);
    }
    printf("Loading");
    for (int i = 0; i < 3; i++) {
        printf(".");
        sleep(1);
    }
    printf("\n");
}

void bookRoom() {
    clearScreen();
    Reservation newReservation;
    printf("*****************************************\n");
    printf("*            ROOM BOOKING               *\n");
    printf("*****************************************\n");
    printf("Enter Customer ID: ");
    scanf("%d", &newReservation.id);
    printf("Enter Customer Name: ");
    scanf(" %[^\n]%*c", newReservation.name);
    printf("Enter Customer Phone No: ");
    scanf("%s", newReservation.phoneNumber);
    printf("Enter Arrival Date (DD-MM-YYYY): ");
    scanf("%s", newReservation.arrivalDate);
    int room_choice, room_available = 0;
    printf("Select room type:\n1. Standard ($50/night)\n2. Deluxe ($100/night)\n3. Suite ($150/night)\nEnter choice: ");
    scanf("%d", &room_choice);


    switch (room_choice) {
        case 1:
            strcpy(newReservation.room_type, "Standard");
            newReservation.rate = 50.0;
            for (int i = 0; i < 30; i++) {
                if (standardRooms[i] != 0) {
                    newReservation.roomNumber = standardRooms[i];
                    standardRooms[i] = 0;
                    room_available = 1;
                    break;
                }
            }
            break;
        case 2:
            strcpy(newReservation.room_type, "Deluxe");
            newReservation.rate = 100.0;
            for (int i = 0; i < 15; i++) {
                if (deluxeRooms[i] != 0) {
                    newReservation.roomNumber = deluxeRooms[i];
                    deluxeRooms[i] = 0;
                    room_available = 1;
                    break;
                }
            }
            break;
        case 3:
            strcpy(newReservation.room_type, "Suite");
            newReservation.rate = 150.0;
            for (int i = 0; i < 5; i++) {
                if (suiteRooms[i] != 0) {
                    newReservation.roomNumber = suiteRooms[i];
                    suiteRooms[i] = 0;
                    room_available = 1;
                    break;
                }
            }
            break;
        default:
            printf("Invalid choice! Returning to main menu.\n");
            system("pause");
            return;
    }

    if (!room_available) {
        printf("No available rooms in the selected type. Returning to main menu.\n");
        system("pause");
        return;
    }

    printf("Enter Number of Nights: ");
    scanf("%d", &newReservation.days);
    printf("Do you require parking? (1 for Yes, 0 for No): ");
    scanf("%d", &newReservation.parking);
    if (newReservation.parking == 1) {
        printf("Enter Car Number: ");
        scanf("%s", newReservation.carNumber);
    }

    reservations[reservationCount++] = newReservation;
    printf("Room %d booked successfully!\n", newReservation.roomNumber);
    system("pause");
}

void checkRoomAvailability() {
    clearScreen();
    int roomNumber, isAvailable = 1, choice;

    printf("*****************************************\n");
    printf("*        CHECK ROOM AVAILABILITY        *\n");
    printf("*****************************************\n\n");

    printf("1. Display all available rooms by type\n");
    printf("2. Check availability of a specific room number\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    clearScreen();

    if (choice == 2) {
        printf("Enter Room Number to Check Availability: ");
        scanf("%d", &roomNumber);


        isAvailable = 1;


        for (int i = 0; i < reservationCount; i++) {
            if (reservations[i].roomNumber == roomNumber) {
                isAvailable = 0;
                printf("\nRoom %d is already booked by %s.\n", roomNumber, reservations[i].name);
                break;
            }
        }

        if (isAvailable) {

            printf("\nRoom %d is available.\n", roomNumber);


            for (int i = 0; i < 30; i++) {
                if (standardRooms[i] == roomNumber) {
                    printf("Room %d is an available Standard room.\n", roomNumber);
                    break;
                }
            }


            for (int i = 0; i < 15; i++) {
                if (deluxeRooms[i] == roomNumber) {
                    printf("Room %d is an available Deluxe room.\n", roomNumber);
                    break;
                }
            }


            for (int i = 0; i < 5; i++) {
                if (suiteRooms[i] == roomNumber) {
                    printf("Room %d is an available Suite room.\n", roomNumber);
                    break;
                }
            }
        }
    } else {
        printf("Available Standard Rooms:\n");
        printf("------------------------\n");
        for (int i = 0; i < 30; i++) {
            if (standardRooms[i] != 0) {
                printf("| Room %d ", standardRooms[i]);
            }
        }
        printf("\n\n");

        printf("Available Deluxe Rooms:\n");
        printf("-----------------------\n");
        for (int i = 0; i < 15; i++) {
            if (deluxeRooms[i] != 0) {
                printf("| Room %d ", deluxeRooms[i]);
            }
        }
        printf("\n\n");

        printf("Available Suite Rooms:\n");
        printf("----------------------\n");
        for (int i = 0; i < 5; i++) {
            if (suiteRooms[i] != 0) {
                printf("| Room %d ", suiteRooms[i]);
            }
        }
        printf("\n");
    }

    printf("\n-----------------------------------------\n");
    system("pause");
}




void viewAllReservations() {
    clearScreen();
    printf("*****************************************\n");
    printf("*          ALL RESERVATIONS             *\n");
    printf("*****************************************\n");
    for (int i = 0; i < reservationCount; i++)
        {
        printf("===============================================================\n");
        printf("ID: %d||Name: %s||Room: %d||Nights: %d||Rate: $%.2f/Night\n",
               reservations[i].id, reservations[i].name,
               reservations[i].roomNumber, reservations[i].days,
               reservations[i].rate);
        printf("===============================================================\n");
    }
    system("pause");
}


void cancelReservation() {
    clearScreen();
    int id;
    printf("*****************************************\n");
    printf("*        CANCEL RESERVATION             *\n");
    printf("*****************************************\n");
    printf("Enter Customer ID to Cancel Reservation: ");
    scanf("%d", &id);

    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].id == id) {
            for (int j = i; j < reservationCount - 1; j++) {
                reservations[j] = reservations[j + 1];
            }
            reservationCount--;
            printf("Reservation cancelled successfully!\n");
            system("pause");
            return;
        }
    }
    printf("Reservation not found!\n");
    system("pause");
}

void searchCustomerRecord() {
    clearScreen();
    int id;
    printf("*****************************************\n");
    printf("*        SEARCH CUSTOMER RECORD         *\n");
    printf("*****************************************\n");
    printf("Enter Customer ID to Search: ");
    scanf("%d", &id);

    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].id == id) {
            printf("ID: %d, Name: %s, Room: %d, Nights: %d, Rate: %.2f\n",
                   reservations[i].id, reservations[i].name,
                   reservations[i].roomNumber, reservations[i].days,
                   reservations[i].rate);
            system("pause");
            return;
        }
    }
    printf("Customer record not found!\n");
    system("pause");
}


void editRecord() {
    clearScreen();
    int id;
    printf("*****************************************\n");
    printf("*            EDIT RECORD                *\n");
    printf("*****************************************\n");
    printf("Enter Customer ID to Edit Record: ");
    scanf("%d", &id);

    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].id == id) {
            printf("Enter new customer name: ");
            scanf(" %[^\n]%*c", reservations[i].name);
            int room_choice;
            printf("Select new room type:\n1. Standard ($50/night)\n2. Deluxe ($100/night)\n3. Suite ($150/night)\nEnter choice: ");
            scanf("%d", &room_choice);
            switch (room_choice) {
                case 1:
                    strcpy(reservations[i].room_type, "Standard");
                    reservations[i].rate = 50.0;
                    break;
                case 2:
                    strcpy(reservations[i].room_type, "Deluxe");
                    reservations[i].rate = 100.0;
                    break;
                case 3:
                    strcpy(reservations[i].room_type, "Suite");
                    reservations[i].rate = 150.0;
                    break;
                default:
                    printf("Invalid choice! Defaulting to Standard.\n");
                    strcpy(reservations[i].room_type, "Standard");
                    reservations[i].rate = 50.0;
                    break;
            }
            printf("Enter New Room Number: ");
            scanf("%d", &reservations[i].roomNumber);
            printf("Enter New Number of Nights: ");
            scanf("%d", &reservations[i].days);
            printf("Record updated successfully!\n");
            system("pause");
            return;
        }
    }
    printf("Customer record not found!\n");
    system("pause");
}


void checkout() {
    clearScreen();
    int id;
    printf("*****************************************\n");
    printf("*               CHECK OUT                 *\n");
    printf("*****************************************\n");
    printf("Enter customer ID for checkout: ");
    scanf("%d", &id);

    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].id == id) {
            float roomCharge = reservations[i].days * reservations[i].rate;
            float parkingCharge = reservations[i].parking ? (10 * reservations[i].days) : 0;
            float totalBill = roomCharge + parkingCharge;

            printf("----- Invoice -----\n");
            printf("Customer Name: %s\n", reservations[i].name);
            printf("Room Number: %d\n", reservations[i].roomNumber);
            printf("Room Type: %s\n", reservations[i].room_type);
            printf("Days Stayed: %d\n", reservations[i].days);
            printf("Room Charge: $%.2f\n", roomCharge);


            if (reservations[i].parking) {
                printf("Parking Charge: $%.2f\n", parkingCharge);
            }

            printf("Total Bill: $%.2f\n", totalBill);
            printf("-------------------\n\n\n");
            printf(" THANK YOU FOR STAYING WITH US \n\n");
            system("pause");
            return;
        }
    }

    printf("Customer record not found!\n");
    system("pause");
}



void revenueGenerator() {
    clearScreen();
    float totalRevenue = 0;
    printf("*****************************************\n");
    printf("*            REVENUE REPORT             *\n");
    printf("*****************************************\n");

    for (int i = 0; i < reservationCount; i++) {
        float roomRevenue = reservations[i].rate * reservations[i].days;
        float parkingRevenue = reservations[i].parking ? (10 * reservations[i].days) : 0;
        totalRevenue += roomRevenue + parkingRevenue;
    }

    printf("Total Revenue Generated: $%.2f\n", totalRevenue);
    system("pause");
}


void parkingManagement() {
    clearScreen();
    int occupiedSlots = 0;

    printf("*****************************************\n");
    printf("*          PARKING MANAGEMENT           *\n");
    printf("*****************************************\n");
    printf("Total Parking Slots: 20\n");

    for (int i = 0; i < reservationCount; i++)
        {
        if (reservations[i].parking == 1)
         {
            occupiedSlots++;
          printf("Slot Number: %d | Customer Name: %s | Room: %d | Car Number: %s\n",
                   occupiedSlots, reservations[i].name, reservations[i].roomNumber, reservations[i].carNumber);
        }
    }

    printf("Occupied Slots: %d\n", occupiedSlots);
    printf("Available Slots: %d\n", 20 - occupiedSlots);
    printf("Parking rate: $10/night\n");
    system("pause");
}

void exitProgram() {
    clearScreen();
    printf("*****************************************\n");
    printf("*         THANK YOU FOR USING           *\n");
    printf("*     HOTEL RESERVATION SYSTEM          *\n");
    printf("*          HAVE A NICE DAY!             *\n");
    printf("*****************************************\n");
    exit(0);
}

