#include <stdio.h>
#include <stdlib.h>  // atoi
#include <string.h>

// C does not have a node, :( we need to create a struct (aka a class) for a
// node with length and value as its attributes
struct node {
    int original_index;
    int length;
    int value;
    float value_per_unit;
};

// Function to calculate the cost per unit of length for each pair of lengths
void calculate_value_per_unit(struct node *argument_array,
                              int argument_array_length) {
    for (int i = 0; i < argument_array_length; i++) {
        argument_array[i].value_per_unit =
            (float)argument_array[i].value / argument_array[i].length;
    }
}

// Comparison function for qsort, used at end
int compare_cost(const void *a, const void *b) {
    struct node *node_a = (struct node *)a;
    struct node *node_b = (struct node *)b;
    if (node_a->value_per_unit < node_b->value_per_unit)
        return 1;
    if (node_a->value_per_unit > node_b->value_per_unit)
        return -1;
    return 0;
}

// create a recursive function to calculate and return the total value of the
// rod. print out new cuts made after each change in cutting length
int calculate_total_value(struct node *sorted_array, int rod_length,
                          int array_length, int array_index, int cuts_made,
                          float value_of_cut) {
    if (rod_length == 0 || (rod_length < sorted_array[array_index].length &&
                            array_index == array_length - 1)) {
        printf("Remainder: %d\n", rod_length);
        return 0;
    }
    if (rod_length - sorted_array[array_index].length > 0) {
        return (sorted_array[array_index].value) +
               calculate_total_value(
                   sorted_array, rod_length - sorted_array[array_index].length,
                   array_length, array_index, cuts_made + 1,
                   value_of_cut + sorted_array[array_index].value);
        // if the cut to be made it exactly the remaning rod_length, print out
        // cuts made, remainder, and return the value of the cut. make sure to
        // incrase cuts made by 1 and add the value of the cut to the
        // value_of_cut when printing out cuts made.
    } else if (rod_length - sorted_array[array_index].length == 0) {
        printf("Cuts Made:\n%d @ %d = %f\n", cuts_made + 1,
               sorted_array[array_index].length,
               value_of_cut + sorted_array[array_index].value);
        printf("Remainder: %d\n", 0);
        return sorted_array[array_index].value;
        // else, print out cuts made for the previous length and continue onto
        // the next length by incrementing the index. reset cuts_made and
        // value_of_cut to 0
    } else {
        printf("Cuts Made:\n%d @ %d = %f\n", cuts_made,
               sorted_array[array_index].length, value_of_cut);
        return calculate_total_value(sorted_array, rod_length, array_length,
                                     array_index + 1, 0, 0);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please enter a rod length as a command lineargument\n");
        return 1;
    }
    int rod_length   = atoi(argv[1]);

    int array_length = 0;
    printf("How many length and value pairs will be inputted?: ");
    scanf("%d", &array_length);
    printf("%d pairs will be added to the array\n\n", array_length);

    // Clear the input buffer, found this idea off the internet since the data
    // was taking in reading the newline character left in the the input buffer
    // from scanf
    while (getchar() != '\n')
        ;

    struct node length_value_array[array_length];

    int index = 0;
    char temp_input[10];
    struct node temp_node = {0, 0, 0, 0};
    while ((index < array_length)) {
        printf("Enter cutting length and value in format: length, value.\n");
        // fgets found on internet, stores standard input into string until
        // return key is pressed
        fgets(temp_input, sizeof(temp_input), stdin);
        sscanf(temp_input, "%d, %d", &temp_node.length, &temp_node.value);
        if (temp_node.length <= 0 || temp_node.value < 0) {
            printf("Please enter a valid, non-negative length and value.\n");
            continue;
        }
        temp_node.original_index  = index;
        length_value_array[index] = temp_node;
        printf("Length added: %d, Value added: %d\n\n", temp_node.length,
               temp_node.value);
        index++;
    }

    printf("\nAll pairs have been added. Listing them below:\n\n");

    for (int i = 0; i < array_length; i++) {
        printf("Pair #%d:\nLength: %d, Value: %d\n\n", i,
               length_value_array[i].length, length_value_array[i].value);
    }

    printf(
        "Calculating cost per unit of length for each cutting length for each "
        "pair\n");
    calculate_value_per_unit(length_value_array, array_length);
    for (int i = 0; i < array_length; i++) {
        printf("Pair #%d:\nCost: %f\n\n", i,
               length_value_array[i].value_per_unit);
    }

    qsort(length_value_array, array_length, sizeof(struct node), compare_cost);
    printf(
        "\nSorted list of pairs from most profitable to least profitable:\n");
    for (int i = 0; i < array_length; i++) {
        printf("Pair #%d:\nLength: %d, Value: %d, Cost: %f\n\n",
               length_value_array[i].original_index,
               length_value_array[i].length, length_value_array[i].value,
               length_value_array[i].value_per_unit);
    }

    int starting_array_index    = 0;
    int starting_cuts_made      = 0;
    float starting_value_of_cut = 0.0;

    float total_value           = calculate_total_value(
        length_value_array, rod_length, array_length, starting_array_index,
        starting_cuts_made, starting_value_of_cut);
    printf("Total Value: %f\n", total_value);

    return 0;
}
