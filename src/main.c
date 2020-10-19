#include <stdio.h>
#include <string.h>
#include <stdbool.h>

extern void sort(int *array, int size);

#define ARRAY_LENGTH 100
#define NOT_ENOUGH_PARAMS -1
#define TOO_MANY_PARAMS -2
#define PARAM_REDECLARATION -3
#define INCORRECT_PARAMS -4
#define INCORRECT_INPUT -5
#define CORRECT_PARAMS 1

int convert_string_to_int(char *str, int begin) {
    int n = 0;
    int sign = 1;
    for(size_t i = begin; i < strlen(str); i++) {
        if(n == 0 && str[i] == '-') {
            sign = -1;
        } else if(str[i] <='9' && str[i] >= '0') {
            n = n * 10 + str[i] - '0';
        } else {
            return n * sign;
        }
    }
    return n * sign;
}

int count_changed_positions(int *sorted_array, int *unsorted_array, int array_length) {
    int count = 0;
    for(int i = 0; i < array_length; i++) {
        if(sorted_array[i] != unsorted_array[i]) count++;
    }
    return count;
}

int get_arrays(int *first_array, int *second_array, int from, int to, bool to_is_gotten, bool from_is_gotten) {
    int array_length = 0;
    int new_number = 0;
    int reading_check = scanf("%d", &new_number);
    while(reading_check != EOF) {
        if(reading_check == 1) {
            if(new_number <= from && from_is_gotten) {
                fprintf(stdout, "%d ", new_number);
            }
            if(new_number >= to && to_is_gotten) {
                fprintf(stderr, "%d ", new_number);
            }
            if((new_number > from || !from_is_gotten) && (new_number < to || !to_is_gotten)) {
                first_array[array_length] = new_number;
                second_array[array_length] = new_number;
                array_length++;
            }
        } else {
            return INCORRECT_INPUT;
        }
        reading_check = scanf("%d", &new_number);
    }
    return array_length;
}

int get_params(int *from, int *to, int argc, char **argv, bool *to_is_gotten, bool *from_is_gotten) {
    if(argc <= 1) return NOT_ENOUGH_PARAMS;
    if(argc > 3) return TOO_MANY_PARAMS;
    char param_to[] = "--to=";
    char param_from[] = "--from=";
    int correct_params = 0;
    size_t to_length = strlen(param_to), from_length = strlen(param_from);
    for(int i = 1; i < argc; i++) {
        if(strncmp(param_from, argv[i], from_length) == 0) {
            if(!(*from_is_gotten)) {
                *from = convert_string_to_int(argv[i], from_length);
                correct_params++;
                *from_is_gotten = true;
            } else return PARAM_REDECLARATION;
        } else if(strncmp(param_to, argv[i], to_length) == 0) {
            if(!(*to_is_gotten)) {
                *to = convert_string_to_int(argv[i], to_length);
                correct_params++;
                *to_is_gotten = true;
            } else return PARAM_REDECLARATION;
        }
    }
    if(correct_params == 0) return INCORRECT_PARAMS;
    return CORRECT_PARAMS;
}

int main(int argc, char **argv) {
    int from = 0, to = 0;
    bool from_is_gotten = false, to_is_gotten = false;
    int get_params_result = get_params(&from, &to, argc, argv, &to_is_gotten, &from_is_gotten);
    if(get_params_result != CORRECT_PARAMS) {
        return get_params_result;
    }

    int array_for_sort[ARRAY_LENGTH], unchanged_array[ARRAY_LENGTH];
    int array_length = get_arrays(array_for_sort, unchanged_array, from, to, to_is_gotten, from_is_gotten);
    if(array_length == INCORRECT_INPUT) return INCORRECT_INPUT;

    sort(array_for_sort, array_length);
    return count_changed_positions(array_for_sort, unchanged_array, array_length);
}