#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "serveur_controleur.h"

// Function to relaunch the program
void relaunchProgram() {
    char *programPath = "./build-and-run"; // Change this to the correct path of your program
    char *args[] = {programPath, NULL};

    printf("Relaunching the program...\n");

    // Replace the current process with a new one
    if (execv(programPath, args) == -1) {
        perror("Error in execv");
        exit(EXIT_FAILURE);
    }
}

// Global variable to check if a segmentation fault occurred
int segmentationFaultOccurred = 0;

// Signal handler for segmentation fault
void segmentationFaultHandler(int __attribute__((unused)) signum) {
    printf("Error: Segmentation fault occurred. The program will now exit.\n");
    segmentationFaultOccurred = 1;

    if (segmentationFaultOccurred) {
        // Prompt the user to relaunch
        printf("Do you want to relaunch the program? (Y/N): ");
        char response;
        scanf(" %c", &response);

        if (response == 'Y' || response == 'y') {
            // Relaunch the program
            relaunchProgram();
        } else {
            printf("Program terminated.\n");
            exit(EXIT_FAILURE);
        }
    }
}

int main() {
    // Set up the segmentation fault signal handler
    signal(SIGSEGV, segmentationFaultHandler);

    // Initialiser les carrefours en leur passant le pointeur vers le serveur de contrôle
    ServeurControleur serveur;
    initialiserServeurControleur(&serveur);
    arreterSimulation();

    return 0;
}
