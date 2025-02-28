#ifndef ROD_H
#define ROD_H

// both structs built off explination from the zoom meeting with prof
typedef struct {
    int count;
    int length;
    int value;
} cut_information;

typedef struct {
    int total_value;
    char *output_text;
} best_cut_pairs;

void find_best_cut(cut_information *length_value_array, int rod_length,
                   int argument_array_length, int *current_cuts,
                   int current_value);

int calculate_and_store_max_value(cut_information *length_value_array,
                                  int rod_length, int argument_array_length,
                                  int *cuts_made, int *cut_lengths);

int store_max_value(best_cut_pairs *output_values,
                    cut_information *length_value_array, int rod_length,
                    int argument_array_length);

void print_best_cut();
#endif  // ROD_H
