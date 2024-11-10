#include "SortedList.hpp"

#include <stdexcept>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

class  SortedList{
    //NOTE: By default, list is sorted in ascending order. (i.e. smallest to largest)

	private:
        float float_array[SORTEDLIST_MAX_SIZE];     
		size_t list_size;                           
        bool verbose;                               

	public:
		SortedList (){
            // Default constructor
            list_size = 0;
            verbose = false;
        }

        SortedList(size_t list_size, bool verbose){
            // Constructor with initializations
            if (list_size > SORTEDLIST_MAX_SIZE){
                throw std::invalid_argument("Size is greater than the maximum size allowed");
            }
            this -> list_size = list_size;
            this -> verbose = verbose;
        }

        void copy(const SortedList& other){   
            if (verbose) std::cout << "Copying elements from other SortedList object" << std::endl;

            // copy the elements of other SortedList object to this object and set the list_size.
            list_size = other.list_size; // Even though list_size is private, it can be accessed from other objects of the same class.
                    
            for (size_t i = 0; i < list_size; i++){ 
                float_array[i] = other.float_array[i];
            }
        }

        float index(size_t ind) const{
            if (verbose) std::cout << "Getting element at index " << ind << std::endl;

            // Return the element at the index ind.
            if (ind >= list_size){
                throw std::out_of_range("Index out of range");
            }
            return float_array[ind];
        }

        size_t insert(float number){
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
            for (size_t i = list_size; i > insert_index; i--){
                float_array[i] = float_array[i-1];
            }

            if (verbose) std::cout << "Inserting at index " << insert_index << std::endl;
            // insert the number at the insert_index
            float_array[insert_index] = number;
   
            return insert_index;
        }

        float remove(size_t index){
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

        size_t find(float number){
            // Only 
            if (verbose) std::cout << "Finding element " << number << std::endl;

            //find by binary search
            size_t low = 0;
            size_t high = list_size - 1;
            size_t mid = 0;
            while (low < high){
                mid = (low + high) / 2; // integer division where floor is taken
                if (verbose) std::cout << "low: " << low << " mid: " << mid << " high: " << high  << "| mid_val: " << float_array[mid]  << std::endl;

                if (float_array[mid] == number  || low+1 >= high){
                    if (verbose) std::cout << "Element found at index " << mid << std::endl;
                    return mid;
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

        // Functions codded by me ========================================
        void randomly_init_list(){
            srand((unsigned) time(0)); // To ensure pseudo-random seed is changed

            // Initialize the list with random numbers ranging from 0 to 99
            size_t original_size = list_size;
            list_size = 0;    
            for (size_t i = 0; i < original_size; i++){
                insert((float) (rand() % 100));
            }
        }

        void randomly_init_list_with_new_size(size_t new_size, size_t modulo){
            srand((unsigned) time(0)); // To ensure pseudo-random seed is changed

            // Initialize the list with random numbers ranging from 0 to 99
            list_size = 0;            
            for (size_t i = 0; i < new_size; i++){
                insert((float) (rand() % modulo));
            }
        }


        void set_verbose(bool verbose){
            this -> verbose = verbose;
        }

        void print_list() const {
           std::cout << "Printing list: " << std::endl;
           for (size_t i = 0; i < list_size; i++){
                std::cout << i << " : " << float_array[i] << std::endl;
           }
        }
    
};


int main()
{
    SortedList list1;
    SortedList list2(5, false);

    list2.randomly_init_list_with_new_size(1000, 2000);
    list2.set_verbose(false);
    //list2.print_list();

    list2.find(3);

    return 0;
}