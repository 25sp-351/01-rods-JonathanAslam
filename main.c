#include <stdio.h>
#include <stdlib.h>

#include "rod.h"

#define BUFFER_LENGTH 256
#define CAPACITY 10

// Reference to globals from rod.c
extern int global_best_value;
extern int *global_best_cuts;
extern int global_rod_length;
extern cut_information *global_length_value_array;
extern int global_array_length;

int main(int argc, char *argv[]) {
    // Check command line arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <rod_length>\n", argv[0]);
        return 1;
    }

    // Parse rod length from command line, check for negative values, return
    // error if negative
    int rod_length;
    sscanf(argv[1], "%d", &rod_length);

    if (rod_length <= 0) {
        fprintf(stderr, "Rod length must be a positive integer\n");
        return 1;
    }

    // Variables for reading input
    char buffer[BUFFER_LENGTH];
    int length   = 0;
    int value    = 0;
    int capacity = CAPACITY;  // Initial capacity
    int count    = 0;         // Actual number of elements

    // Allocate memory for cut_information array
    cut_information *length_value_array =
        malloc(capacity * sizeof(cut_information));
    if (length_value_array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Read piece prices from standard input
    printf(
        "Please input cutting pairs in format: length, value. Enter `ctrl + d` "
        "when finished\n");
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (sscanf(buffer, "%d, %d", &length, &value) == 2) {
            //make sure length and value are non-negative values
            if (length < 0 || value < 0) {
                fprintf(stderr, "Cannot compute a negative, please try again\n");
                continue;
            }

            // Resize array if needed, figured this out with the help of some AI
            if (count >= capacity) {
                capacity *= 2;
                cut_information *temp = realloc(
                    length_value_array, capacity * sizeof(cut_information));
                if (temp == NULL) {
                    fprintf(stderr, "Memory allocation failed\n");
                    free(length_value_array);
                    return 1;
                }
                length_value_array = temp;
            }

            // Store the piece information
            length_value_array[count].count  = count;
            length_value_array[count].length = length;
            length_value_array[count].value  = value;
            count++;
        } else {
            fprintf(stderr,
                    "Invalid input format. Expected: <length>, <value>\n");
            free(length_value_array);
            return 1;
        }
    }

    // Allocate memory for cuts_made and cut_lengths
    int *cuts_made   = (int *)calloc(rod_length + 1, sizeof(int));
    int *cut_lengths = (int *)calloc(count, sizeof(int));

    if (cuts_made == NULL || cut_lengths == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(length_value_array);
        return 1;
    }

    // Find the best solution
    calculate_and_store_max_value(length_value_array, rod_length, count,
                                  cuts_made, cut_lengths);

    // Print the solution
    print_best_cut();

    // Clean up
    free(cuts_made);
    free(cut_lengths);
    free(length_value_array);

    if (global_best_cuts != NULL) {
        free(global_best_cuts);
        global_best_cuts = NULL;
    }

    return 0;
}
