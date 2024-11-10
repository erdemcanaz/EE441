
#define SORTEDLIST_MAX_SIZE 10000                                               // Maximum size of the list to ensure user does not set a very large size mistakenly

class SortedList {                                                              // ASCENDING ORDER FLOAT LIST 
    private:
        float float_array[SORTEDLIST_MAX_SIZE];                                 // Array to store the elements of the list. No dynamic allocation is needed.
        size_t list_size;                                                       // Number of active elements in the list. Starting from index 0 to list_size-1 elements are active.
        bool verbose;                                                           // Flag to print debug messages.
    public:
        SortedList();                                                           // Default constructor
        SortedList(size_t list_size, bool verbose);                             // Constructor with initializations
        void copy(const SortedList& other);                                     // Deep-Copy the elements of other SortedList object to this object
        float index(size_t ind) const;                                          // Get the element at index ind, raise out_of_range exception if ind is out of range
        size_t insert(float number);                                            // Insert the number in the list and return the index where it was inserted, raise length_error if list is full
        float remove(size_t index);                                             // Remove the element at index and return it's value, raise out_of_range exception if index is out of range
        size_t find(float number);                                              // Find the index of the number in the list by binary search, raise domain_error if number is not found

        void randomly_init_list(size_t modulo);                                 // Initialize the list with random numbers ranging from 0 to 99
        void randomly_init_list_with_new_size(size_t new_size, size_t modulo);  // Initialize the list with random numbers ranging from 0 to 99 and set the list_size to new_size
        void set_verbose(bool verbose);                                         // Set the verbose flag
        void print_list() const;                                                // Print the list
};