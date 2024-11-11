#include "SortedList.hpp"

SortedList::SortedList (){
    // Default constructor
    list_size = 0;
    verbose = false;
}

SortedList::SortedList(size_t list_size, bool verbose){
    // Constructor with initializations
    if (list_size > SORTEDLIST_MAX_SIZE){
        throw std::invalid_argument("Size is greater than the maximum size allowed");
    }
    this -> list_size = list_size;
    this -> verbose = verbose;
}

void SortedList::copy(const SortedList& other){   
    if (verbose) std::cout << "Copying elements from other SortedList object" << std::endl;

    // copy the elements of other SortedList object to this object and set the list_size.
    list_size = other.list_size; // Even though list_size is private, it can be accessed from other objects of the same class.
            
    for (size_t i = 0; i < list_size; i++){ 
        float_array[i] = other.float_array[i];
    }
}

float SortedList::index(size_t ind) const{
    if (verbose) std::cout << "Getting element at index " << ind << std::endl;

    // Return the element at the index ind.
    if (ind >= list_size){
        throw std::out_of_range("Index out of range");
    }
    return float_array[ind];
}

size_t SortedList::insert(float number){
    if (verbose) std::cout << "Inserting number " << number << std::endl;
    // check if there is space in the list
    if (list_size >= SORTEDLIST_MAX_SIZE){
        throw std::length_error("List is full, cannot insert more elements");
    }

    // find the index where the number should be inserted
    size_t insert_index = 0;
    for(; insert_index < list_size; insert_index++){
        if (number < float_array[insert_index])break;               
    }

    // increment the list_size 
    list_size ++;

    // shift elements to the right starting from the end of the list
    for (size_t i = list_size-1; i > insert_index; i--){
        float_array[i] = float_array[i-1];
    }

    if (verbose) std::cout << "Inserting at index " << insert_index << std::endl;
    // insert the number at the insert_index
    float_array[insert_index] = number;

    return insert_index;
}

float SortedList::remove(size_t index){
    if (verbose) std::cout << "Removing element at index " << index << std::endl;

    // remove the element at the index and return it's value
    if (index >= list_size){
        throw std::out_of_range("Index out of range");
    }

    float removed_element = float_array[index];

    // shift elements to the left starting from the index
    for (size_t i = index; i < list_size; i++){
        float_array[i] = float_array[i+1];
    }

    // decrement the list_size
    list_size --;

    return removed_element;
}

size_t SortedList::find(float number){
    // Only 
    if (verbose) std::cout << "Finding element " << number << std::endl;

    //find by binary search
    size_t low = 0;
    size_t high = list_size - 1;
    size_t mid = 0;
    while (low < high){
        mid = (low + high) / 2; // integer division where floor is taken
        if (verbose) std::cout << "low: " << low << " mid: " << mid << " high: " << high  << "| mid_val: " << float_array[mid]  << std::endl;

        if (float_array[mid] == number || low+1 >= high ){
            if (float_array[low] == number){
                if (verbose) std::cout << "Element found at index " << low << std::endl;
                return low;
            }
            else if (float_array[mid] == number){
                if (verbose) std::cout << "Element found at index " << mid << std::endl;
                return mid;
            }
            else if (float_array[high] == number){
                if (verbose) std::cout << "Element found at index " << high << std::endl;
                return high;
            }else{
                throw std::domain_error("Element not found");
            }
            
        }
        else if (float_array[mid] < number){
            low = mid;
        }
        else{
            high = mid;
        }
        
    }

    throw std::domain_error("Element not found");

}

void SortedList::print_list_Q11() const{
    if (list_size == 0){
        std::cout << "\tThe list is empty" << std::endl;
        return;
    }
    for (size_t i = 0; i < list_size; i++){
        std::cout << float_array[i] << " ";
    }
}
// Functions codded by me ========================================
size_t SortedList::get_list_size() const{
    return list_size;
};

size_t SortedList::insert_binary_search(float number){
    if (verbose) std::cout << "Inserting number " << number << std::endl;
    // check if there is space in the list
    if (list_size >= SORTEDLIST_MAX_SIZE){
        throw std::length_error("List is full, cannot insert more elements");
    }

    // find the index where the number should be inserted using binary search
    size_t low = 0;
    size_t high = list_size;
    size_t insert_index = 0;
    while (low < high) {
        size_t mid = (low + high) / 2;
        if (float_array[mid] < number) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    insert_index = low;

    // increment the list_size 
    list_size ++;

    // shift elements to the right starting from the end of the list
    for (size_t i = list_size-1; i > insert_index; i--){
        float_array[i] = float_array[i-1];
    }

    if (verbose) std::cout << "Inserting at index " << insert_index << std::endl;
    // insert the number at the insert_index
    float_array[insert_index] = number;

    return insert_index;
}

void SortedList::randomly_init_list(size_t modulo){
    // To ensure pseudo-random seed is changed
    srand((unsigned) time(0)); 

    // Initialize the list with random numbers ranging from 0 to modulo-1
    for (size_t i = 0; i < list_size; i++){
        float_array[i] = (float) (rand() % modulo);
    }

    // Apply buble sort to sort the list (ascending order - smallest to largest)
    for (size_t i = 0; i < list_size; i++){
        for (size_t j = 0; j < list_size - i - 1; j++){
            if (float_array[j] > float_array[j+1]){
                float temp = float_array[j];
                float_array[j] = float_array[j+1];
                float_array[j+1] = temp;
            }
        }
    }

}

void SortedList::randomly_init_list_with_new_size(size_t new_size, size_t modulo){
    // To ensure pseudo-random seed is changed
    srand((unsigned) time(0)); 

    // Check if the new size is greater than the maximum size allowed
    if (new_size > SORTEDLIST_MAX_SIZE){
        throw std::invalid_argument("Size is greater than the maximum size allowed");
    }

    // Initialize the list with random numbers ranging from 0 to modulo-1
    list_size = new_size;      
    for (size_t i = 0; i < list_size; i++){
        float_array[i] = (float) (rand() % modulo);
    }

    // Apply buble sort to sort the list (ascending order - smallest to largest)
    for (size_t i = 0; i < list_size; i++){
        for (size_t j = 0; j < list_size - i - 1; j++){
            if (float_array[j] > float_array[j+1]){
                float temp = float_array[j];
                float_array[j] = float_array[j+1];
                float_array[j+1] = temp;
            }
        }
    }
}

void SortedList::set_verbose(bool verbose){
    this -> verbose = verbose;
}

void SortedList::print_list() const {
    if (list_size == 0){
        std::cout << "\tList is empty" << std::endl;
        return;
    }
    for (size_t i = 0; i < list_size; i++){
        std::cout <<"\t" << i << " : " << float_array[i] << std::endl;
    }
}
