#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ==========================================================
 * 1. DOUBLY LINKED LIST: TRAIN COACHES
 * Har coach ke paas do pointers hote hain:
 *  - prev: aage wale coach (Engine ki taraf) ke liye
 *  - next: peeche wale coach (Guard ki taraf) ke liye
 * ========================================================== */
struct Coach {
    int coachNo;
    char coachType[30];     // AC, Sleeper, General, etc.
    int seats;
    struct Coach* prev;
    struct Coach* next;
};

// Global pointers train ke liye
struct Coach* head = NULL;  // Engine side (Start)
struct Coach* tail = NULL;  // Guard side (End)

/* Naya coach banane ka simple function */
struct Coach* createCoach(int coachNo, char type[], int seats) {
    struct Coach* newCoach = (struct Coach*)malloc(sizeof(struct Coach));
    newCoach->coachNo = coachNo;
    strcpy(newCoach->coachType, type);
    newCoach->seats = seats;
    newCoach->prev = NULL;
    newCoach->next = NULL;
    return newCoach;
}

/* Engine ke paas (Beginning) me coach add karna */
void addCoachAtBeginning(int coachNo, char type[], int seats) {
    struct Coach* newCoach = createCoach(coachNo, type, seats);
    
    if (head == NULL) {
        head = tail = newCoach;
    } else {
        newCoach->next = head;
        head->prev = newCoach;
        head = newCoach;
    }
    printf("Coach %d (%s) Engine ke paas add ho gaya!\n", coachNo, type);
}

/* Guard ke paas (End) me coach add karna */
void addCoachAtEnd(int coachNo, char type[], int seats) {
    struct Coach* newCoach = createCoach(coachNo, type, seats);
    
    if (head == NULL) {
        head = tail = newCoach;
    } else {
        tail->next = newCoach;
        newCoach->prev = tail;
        tail = newCoach;
    }
    printf("Coach %d (%s) peeche add ho gaya!\n", coachNo, type);
}

/* Coach remove karna (Coach Number ke basis par) */
void removeCoach(int coachNo) {
    if (head == NULL) {
        printf("Train khali hai! Koi coach nahi hai.\n");
        return;
    }

    struct Coach* temp = head;

    // Coach dhundhna
    while (temp != NULL && temp->coachNo != coachNo) {
        temp = temp->next;
    }

    // Agar coach nahi mila
    if (temp == NULL) {
        printf("Coach number %d nahi mila!\n", coachNo);
        return;
    }

    // Agar ek hi coach tha
    if (head == tail) {
        head = tail = NULL;
    }
    // Agar pehla coach delete karna hai
    else if (temp == head) {
        head = head->next;
        head->prev = NULL;
    }
    // Agar aakhri coach delete karna hai
    else if (temp == tail) {
        tail = tail->prev;
        tail->next = NULL;
    }
    // Beech ka coach delete karna hai
    else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }

    free(temp);
    printf("Coach %d train se hata diya gaya.\n", coachNo);
}

/* Train display karna: Engine se Guard (Forward traversal using next) */
void displayTrainForward() {
    if (head == NULL) {
        printf("\nTrain me koi coach nahi hai!\n");
        return;
    }

    struct Coach* temp = head;
    printf("\n--- TRAIN (ENGINE TO GUARD) ---\n");
    printf("[ENGINE] <-> ");
    while (temp != NULL) {
        printf("[No: %d | %s | Seats: %d] <-> ", temp->coachNo, temp->coachType, temp->seats);
        temp = temp->next;
    }
    printf("[GUARD]\n");
}

/* Train display karna: Guard se Engine (Backward traversal using prev) */
void displayTrainBackward() {
    if (tail == NULL) {
        printf("\nTrain me koi coach nahi hai!\n");
        return;
    }

    struct Coach* temp = tail;
    printf("\n--- TRAIN (GUARD TO ENGINE - REVERSE) ---\n");
    printf("[GUARD] <-> ");
    while (temp != NULL) {
        printf("[No: %d | %s | Seats: %d] <-> ", temp->coachNo, temp->coachType, temp->seats);
        temp = temp->prev;
    }
    printf("[ENGINE]\n");
}

/* Coach search karna */
void searchCoach(int coachNo) {
    struct Coach* temp = head;
    while (temp != NULL) {
        if (temp->coachNo == coachNo) {
            printf("\nCoach Mil Gaya!\n");
            printf("Coach No: %d\n", temp->coachNo);
            printf("Type    : %s\n", temp->coachType);
            printf("Seats   : %d\n", temp->seats);
            return;
        }
        temp = temp->next;
    }
    printf("Coach No %d nahi mila!\n", coachNo);
}


/* ==========================================================
 * 2. CIRCULAR LINKED LIST: TRAIN ROUTE / STATIONS
 * Last station ka next pointer wapas pehle station par
 * point karta hai (Loop track)
 * ========================================================== */
struct Station {
    char name[40];
    struct Station* next;
};

// Global pointer circular route ke liye
struct Station* routeHead = NULL;
struct Station* currentStation = NULL;

/* Route me naya station add karna (Circular Linked List) */
void addStation(char name[]) {
    struct Station* newStation = (struct Station*)malloc(sizeof(struct Station));
    strcpy(newStation->name, name);
    newStation->next = NULL;

    if (routeHead == NULL) {
        routeHead = newStation;
        newStation->next = routeHead; // khud ko point karega (1st node)
        currentStation = routeHead;
    } else {
        struct Station* temp = routeHead;
        // aakhri station tak jana
        while (temp->next != routeHead) {
            temp = temp->next;
        }
        temp->next = newStation;
        newStation->next = routeHead; // aakhri wala wapas pehle ko point karega
    }
    printf("Station '%s' circular route me add ho gaya.\n", name);
}

/* Saare stations circular order me dikhana */
void displayRoute() {
    if (routeHead == NULL) {
        printf("\nRoute me koi station nahi hai!\n");
        return;
    }

    struct Station* temp = routeHead;
    printf("\n--- CIRCULAR ROUTE (STATIONS LOOP) ---\n");
    do {
        if (temp == currentStation) {
            printf("[%s (TRAIN HERE)] -> ", temp->name);
        } else {
            printf("[%s] -> ", temp->name);
        }
        temp = temp->next;
    } while (temp != routeHead);
    printf("(Wapas: %s)\n", routeHead->name);
}

/* Train ko agle station par le jana */
void moveToNextStation() {
    if (currentStation == NULL) {
        printf("\nRoute khali hai!\n");
        return;
    }
    currentStation = currentStation->next;
    printf("\nTrain ab station '%s' par pahunch gayi hai!\n", currentStation->name);
}


/* ==========================================================
 * MAIN FUNCTION: MENU DRIVEN PROGRAM
 * ========================================================== */
int main() {
    int choice, coachNo, seats;
    char type[30], stationName[40];

    // Shuruat me kuch default coaches aur stations daal dete hain taaki direct run karke dekh sakein
    addCoachAtEnd(101, "AC First Class", 24);
    addCoachAtEnd(102, "AC 2-Tier", 48);
    addCoachAtEnd(103, "Sleeper", 72);
    addCoachAtEnd(104, "General", 90);

    addStation("Delhi");
    addStation("Kanpur");
    addStation("Prayagraj");
    addStation("Varanasi");

    while (1) {
        printf("\n=========================================\n");
        printf("      TRAIN COACH MANAGEMENT SYSTEM      \n");
        printf("=========================================\n");
        printf("--- DOUBLY LINKED LIST (COACHES) ---\n");
        printf("1. Add Coach at Front (Engine side)\n");
        printf("2. Add Coach at End (Guard side)\n");
        printf("3. Remove Coach by Number\n");
        printf("4. Display Train Forward (Engine -> Guard)\n");
        printf("5. Display Train Backward (Guard -> Engine)\n");
        printf("6. Search Coach Details\n");
        printf("\n--- CIRCULAR LINKED LIST (ROUTE) ---\n");
        printf("7. Add Station to Route\n");
        printf("8. Display Circular Route\n");
        printf("9. Move Train to Next Station\n");
        printf("\n0. Exit\n");
        printf("=========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Coach Number: ");
                scanf("%d", &coachNo);
                printf("Coach Type (AC/Sleeper/General): ");
                scanf("%s", type);
                printf("Total Seats: ");
                scanf("%d", &seats);
                addCoachAtBeginning(coachNo, type, seats);
                break;

            case 2:
                printf("Coach Number: ");
                scanf("%d", &coachNo);
                printf("Coach Type (AC/Sleeper/General): ");
                scanf("%s", type);
                printf("Total Seats: ");
                scanf("%d", &seats);
                addCoachAtEnd(coachNo, type, seats);
                break;

            case 3:
                printf("Enter Coach Number to Remove: ");
                scanf("%d", &coachNo);
                removeCoach(coachNo);
                break;

            case 4:
                displayTrainForward();
                break;

            case 5:
                displayTrainBackward();
                break;

            case 6:
                printf("Enter Coach Number to Search: ");
                scanf("%d", &coachNo);
                searchCoach(coachNo);
                break;

            case 7:
                printf("Enter Station Name: ");
                scanf("%s", stationName);
                addStation(stationName);
                break;

            case 8:
                displayRoute();
                break;

            case 9:
                moveToNextStation();
                break;

            case 0:
                printf("\nExiting program. Thank you!\n");
                return 0;

            default:
                printf("Galat option! Dobara try karein.\n");
        }
    }

    return 0;
}
