#include "SortedList.hpp" 
#include <chrono>

int main()
{

    // NOTE:
    std::cout << "NOTE: You can test functions simply by changing the parameters given at the beginning of the each question related block  " << std::endl;
    std::cout << "Press any key to continue..."<< std::endl;
    std::cin.get();

    //Q1 - SortedList class is implemented.  ==================================================
    std::cout << "\nQ1 - SortedList class is implemented (#include 'SortedList.hpp')." << std::endl;
    std::cout << "Press any key to continue..."<< std::endl;
    std::cin.get();

    //Q2 - Two different constructors are implemented. ========================================
    const size_t Q2_SECOND_LIST_SIZE = 10;

    std::cout << "\nQ2 - Two different constructors are implemented." << std::endl;
    SortedList list_by_default_constructor; // Default constructor: list_size = 0, verbose = false
    std::cout << "(created by default constructor)       List size : " << list_by_default_constructor.get_list_size() << std::endl;
    SortedList list_by_parameterized_constructor(Q2_SECOND_LIST_SIZE, false); // Parameterized constructor: list_size = SECOND_LIST_SIZE, verbose = true
    std::cout << "(created by parameterized constructor) List size : " << list_by_parameterized_constructor.get_list_size() << std::endl;

    std::cout << "Press any key to continue..."<< std::endl;
    std::cin.get();

    //Q3 - Copy function is implemented. =======================================================  
    const size_t Q3_MODULO_VALUE = 100;  
    const size_t Q3_MAIN_LIST_SIZE = 0; // (< SORTEDLIST_MAX_SIZE) By changing this value, you can test the copy function with different list sizes
    const size_t Q3_SECOND_LIST_SIZE = 5; // (< SORTEDLIST_MAX_SIZE) By changing this value, you can test the copy function with different list sizes

    std::cout << "\nQ3 - Copy function is implemented." << std::endl;
    std::cout << "# Main and Second SortedList objects are created with list_sizes " << Q3_MAIN_LIST_SIZE << " and " << Q3_SECOND_LIST_SIZE << std::endl;
    SortedList main_list(Q3_MAIN_LIST_SIZE, false);
    SortedList second_list(Q3_SECOND_LIST_SIZE, false);

    std::cout << "# second list is randomly initialized" << std::endl;
    second_list.randomly_init_list(Q3_MODULO_VALUE);

    std::cout << "Elements of the second list:" << std::endl;
    second_list.print_list();  

    std::cout << "Elements of the main list before copy:" << std::endl;
    main_list.print_list();

    main_list.copy(second_list);

    std::cout << "Elements of the main list after copy:" << std::endl;
    main_list.print_list();

    std::cout << "Press any key to continue..."<< std::endl;
    std::cin.get();

    //Q4 - index function is implemented. =====================================================
    const size_t Q4_TEST_INDEXES_UPPER_BOUND = 20; // (< SORTEDLIST_MAX_SIZE) By changing this value, you can test the index function with different indexes 
    const size_t Q4_MODULO = 100; 
    const size_t Q4_MAIN_LIST_SIZE = 10; // (< SORTEDLIST_MAX_SIZE) 

    std::cout << "\nQ4 - index function is implemented." << std::endl;
    std::cout << "# main list is randomly initialized with " << Q4_MAIN_LIST_SIZE << " number of elements" << std::endl;
    main_list.randomly_init_list_with_new_size(Q4_MAIN_LIST_SIZE, Q4_MODULO);

    std::cout << "Elements of the main list:" << std::endl;
    main_list.print_list();

    std::cout << "# Printing all of the elements" << std::endl;
    for (size_t i = 0; i < Q4_TEST_INDEXES_UPPER_BOUND; i++){

        try {
            std::cout << "Element at index " << i << ": " << main_list.index(i) << std::endl;
        } catch (const std::out_of_range& e) {
            std::cout << "Element at index " << i << ": " << "Error: " << e.what() << std::endl;
        }
    }

    std::cout << "Press any key to continue..."<< std::endl;
    std::cin.get();

    //Q5 - insert function is implemented. ====================================================
    const size_t Q5_MAIN_LIST_SIZE = 3; // (< SORTEDLIST_MAX_SIZE) By changing this value, you can test the insert function with different list sizes
    const size_t Q5_MODULO_VALUE = 100;
    const size_t Q5_INSERTED_ELEMENT = 50; // By changing this value, you can test the insert function with different inserted elements

    std::cout << "\nQ5 - insert function is implemented." << std::endl;
    std::cout << "# main list is randomly initialized with " << Q5_MAIN_LIST_SIZE << " number of elements" << std::endl;
    main_list.randomly_init_list_with_new_size(Q5_MAIN_LIST_SIZE, Q5_MODULO_VALUE);
    
    std::cout << "Elements of the main list:" << std::endl;
    main_list.print_list();

    std::cout << "# Inserting element " << Q5_INSERTED_ELEMENT << " to the main list" << std::endl;  
    size_t insert_index = main_list.insert(Q5_INSERTED_ELEMENT);
    std::cout << "Element " << Q5_INSERTED_ELEMENT << " is inserted to index " << insert_index << std::endl;

    std::cout << "Elements of the main list after insertion:" << std::endl;
    main_list.print_list();

    std::cout << "Press any key to continue..."<< std::endl;
    std::cin.get();

    //Q6 - Insert Function Time Complexity ===================================================
    //NOTE: to test this function, SORTEDLIST_MAX_SIZE should be greater than the maximum value of Q6_MAIN_LIST_SIZE
    const size_t Q6_MAIN_LIST_SIZE[] = {256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536}; //NOTE: Never edit this array
    const size_t Q6_NUMBER_OF_TRIALS = 30000; // Please ensure that this value is comparable to maximum value of Q8_MAIN_LIST_SIZE

    size_t main_list_sizes_count = sizeof(Q6_MAIN_LIST_SIZE)/sizeof(Q6_MAIN_LIST_SIZE[0]);
    size_t Q6_MODULO_VALUE = Q6_MAIN_LIST_SIZE[main_list_sizes_count-1];

    if (Q6_MAIN_LIST_SIZE[main_list_sizes_count-1] >= SORTEDLIST_MAX_SIZE-1){
        std::cout << "Q6 - Insert Function Time Complexity is not tested since the (main list size + 1) is greater than the maximum size allowed" << std::endl;
    }else{        
        // Test the time complexity of the insert function (Linear search & Binary search)
        std::cout << "\nQ6 - Insert Function Time Complexity." << std::endl;        
        std::cout << "Note That the shifting operation is the main cause of the theoritical and practical difference." << std::endl;
        std::cout << "We can assume that shifting takes same time for both binary and linear insertions since same value is insterted." << std::endl;
        std::cout << "In other words, T_linear = T_shift + T_linear and T_binary = T_shift + T_binary" << std::endl;
        std::cout << "We can simply get rid of the shifting operation to compare the time complexity of the binary and linear insertions." << std::endl;
        std::cout << "T_linear(n) - T_binary O(logn) ~ O(n)\n"<< std::endl;

        // Reset seed to ensure pseudo-random seed is changed             
        srand(static_cast<unsigned>(time(0)));

        for (size_t i = 0; i < main_list_sizes_count; i++){

            std::cout << "# main list is randomly initialized with " << Q6_MAIN_LIST_SIZE[i] << " number of elements" << std::endl;
            main_list.randomly_init_list_with_new_size(Q6_MAIN_LIST_SIZE[i], Q6_MODULO_VALUE);
           
            size_t total_time_linear = 0;
            size_t total_time_binary = 0;            
            for (size_t j = 0; j < Q6_NUMBER_OF_TRIALS; j++){  

                // Randomly select a value to insert in the min and max range
                float value_to_insert = static_cast<float>(rand() % Q6_MODULO_VALUE);
        
                // Insert the value using linear search
                auto start_time = std::chrono::high_resolution_clock::now();             
                size_t inserted_index = main_list.insert(value_to_insert); 
                auto end_time = std::chrono::high_resolution_clock::now();                  
                total_time_linear += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();    
                main_list.remove(inserted_index); // Remove the inserted element to keep the list size constant

                // Insert the value using binary search
                start_time = std::chrono::high_resolution_clock::now();             
                inserted_index = main_list.insert_binary_search(value_to_insert); 
                end_time = std::chrono::high_resolution_clock::now();                  
                total_time_binary += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();    
                main_list.remove(inserted_index); // Remove the inserted element to keep the list size constant
            }

            std::cout << "Main list size: " << Q6_MAIN_LIST_SIZE[i] <<  " and total number of trials is: "<< Q6_NUMBER_OF_TRIALS <<std::endl;
            std::cout << "\tTiming for linear search: " << total_time_linear/1000.0f << " ms" << std::endl;
            std::cout << "\tTiming for binary search: " << total_time_binary/1000.0f << " ms" << std::endl;

            if (total_time_linear - total_time_binary > 0 ){
                std::cout << "\tDifference between (linear-binary) search: " << (total_time_linear - total_time_binary)/1000.0f << " ms" << std::endl;
            }else{
                std::cout << "\tDifference between (linear-binary) search: -" << (total_time_binary - total_time_linear)/1000.0f << " ms" << std::endl;

            }

        }

        std::cout << "Please note the linear fashion and how fast binary seach is compared to linear search"<< std::endl;
    }

    std::cout << "Press any key to continue..."<< std::endl;
    std::cin.get();

    //Q7 - remove function is implemented. ====================================================
    const size_t Q7_MAIN_LIST_SIZE = 10; // (< SORTEDLIST_MAX_SIZE) By changing this value, you can test the remove function with different list sizes
    const size_t Q7_MODULO_VALUE = 100; // By changing this value, max value of the elements in the list can be changed
    const size_t Q7_REMOVE_INDEX = 5; // By changing this value, you can test the remove function with different removed indexes

    std::cout << "\nQ7 - remove function is implemented." << std::endl;
    std::cout << "# main list is randomly initialized with " << Q7_MAIN_LIST_SIZE << " number of elements" << std::endl;

    main_list.randomly_init_list_with_new_size(Q7_MAIN_LIST_SIZE, Q7_MODULO_VALUE);
    std::cout << "Elements of the main list:" << std::endl;
    main_list.print_list();

    std::cout << "# Removing element at index " << Q7_REMOVE_INDEX << " from the main list" << std::endl;
    float removed_element = main_list.remove(Q7_REMOVE_INDEX);
    std::cout << "Element " << removed_element << " is removed from index " << Q7_REMOVE_INDEX << std::endl;

    std::cout << "Elements of the main list after removal:" << std::endl;
    main_list.print_list();

    std::cout << "Press any key to continue..."<< std::endl;
    std::cin.get();

    //Q8 -Remove function time complexity ======================================================
    //NOTE: to test this function, SORTEDLIST_MAX_SIZE should be greater than the maximum value of Q8_MAIN_LIST_SIZE

    const size_t Q8_MAIN_LIST_SIZE[] = {256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};; //NOTE: Never edit this array
    const size_t Q8_NUMBER_OF_TRIALS = 10000; // Please ensure that this value is comparable to maximum value of Q8_MAIN_LIST_SIZE

    main_list_sizes_count = sizeof(Q8_MAIN_LIST_SIZE)/sizeof(Q8_MAIN_LIST_SIZE[0]);
    size_t Q8_MODULO_VALUE = Q8_MAIN_LIST_SIZE[main_list_sizes_count-1];

    if (Q8_MAIN_LIST_SIZE[main_list_sizes_count-1] >= SORTEDLIST_MAX_SIZE-1){
        std::cout << "Q8 - Remove Function Time Complexity is not tested since the (main list size + 1) is greater than the maximum size allowed" << std::endl;
    }else{    
        // Test the time complexity of the remove function
        std::cout << "\nQ8 - Remove Function Time Complexity." << std::endl;

        // Reset seed to ensure pseudo-random seed is changed             
        srand(static_cast<unsigned>(time(0)));

        for (size_t i = 0; i < main_list_sizes_count; i++){

            std::cout << "# main list is randomly initialized with " << Q8_MAIN_LIST_SIZE[i] << " number of elements" << std::endl;
            main_list.randomly_init_list_with_new_size(Q8_MAIN_LIST_SIZE[i], Q8_MODULO_VALUE);
           
            size_t total_time = 0;
            for (size_t j = 0; j < Q8_NUMBER_OF_TRIALS; j++){  

                // Randomly select a value to insert in the min and max range
                size_t index_to_remove = (size_t)(rand() % Q8_MAIN_LIST_SIZE[i]);        
          
                // Remove the value using linear search
                auto start_time = std::chrono::high_resolution_clock::now();             
                float removed_value = main_list.remove(index_to_remove); 
                auto end_time = std::chrono::high_resolution_clock::now();                  
                total_time += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();    

                // Insert the value using binary search
                main_list.insert_binary_search(removed_value); // Insert the removed value back to the list to keep the list size constant

            }

            std::cout << "Main list size: " << Q8_MAIN_LIST_SIZE[i] <<  " and total number of trials is: "<< Q8_NUMBER_OF_TRIALS <<std::endl;
            std::cout << "\tTiming for remove: " << total_time/1000.0f << " ms" << std::endl;

        }
        
    }

    std::cout << "Press any key to continue..."<< std::endl;
    std::cin.get();

    //Q9 - find function is implemented. ======================================================
    const size_t Q9_MAIN_LIST_SIZE = (size_t)(SORTEDLIST_MAX_SIZE-1); // (< SORTEDLIST_MAX_SIZE) By changing this value, you can test the find function with different list sizes
    const size_t Q9_MODULO_VALUE = 10000; // By changing this value, max value of the elements in the list can be changed
    const size_t Q9_FIND_ELEMENT = 50; // By changing this value, you can test the find function with different find elements

    std::cout << "\nQ9 - find function is implemented." << std::endl;
    std::cout << "# main list is randomly initialized with " << Q9_MAIN_LIST_SIZE << " number of elements" << std::endl;
    main_list.randomly_init_list_with_new_size(Q9_MAIN_LIST_SIZE, Q9_MODULO_VALUE);
    std::cout << "Element: " << Q9_FIND_ELEMENT << " is inserted" << std::endl;
    main_list.insert(Q9_FIND_ELEMENT);

    std::cout << "Elements of the main list:" <<  main_list.get_list_size() << std::endl;

    main_list.set_verbose(true);
    size_t find_index = main_list.find(Q9_FIND_ELEMENT);
    std::cout << "Element " << Q9_FIND_ELEMENT << " is found at index " << find_index << std::endl;
    main_list.set_verbose(false);  

    //Q10 - Time complexity of the find function =================================================
    //NOTE: to test this function, SORTEDLIST_MAX_SIZE should be greater than the maximum value of Q10_MAIN_LIST_SIZE

    const size_t Q10_MAIN_LIST_SIZE[] = {256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};; //NOTE: Never edit this array
    const size_t Q10_NUMBER_OF_TRIALS = 10000; // Please ensure that this value is comparable to maximum value of Q10_MAIN_LIST_SIZE

    main_list_sizes_count = sizeof(Q10_MAIN_LIST_SIZE)/sizeof(Q10_MAIN_LIST_SIZE[0]);
    size_t Q10_MODULO_VALUE = Q10_MAIN_LIST_SIZE[main_list_sizes_count-1];

    if (Q10_MAIN_LIST_SIZE[main_list_sizes_count-1] >= SORTEDLIST_MAX_SIZE-1){
        std::cout << "Q10 - Find Function Time Complexity is not tested since the (main list size + 1) is greater than the maximum size allowed" << std::endl;
    }else{

        // Test the time complexity of the find function
        std::cout << "\nQ10 - Find Function Time Complexity." << std::endl;

        // Reset seed to ensure pseudo-random seed is changed             
        srand(static_cast<unsigned>(time(0)));

        for (size_t i = 0; i < main_list_sizes_count; i++){

            std::cout << "# main list is randomly initialized with " << Q10_MAIN_LIST_SIZE[i] << " number of elements" << std::endl;
            main_list.randomly_init_list_with_new_size(Q10_MAIN_LIST_SIZE[i], Q10_MODULO_VALUE);
           
            size_t total_time = 0;
            for (size_t j = 0; j < Q10_NUMBER_OF_TRIALS; j++){  

                // Randomly select a value to insert in the min and max range
                float value_to_find = static_cast<float>(rand() % Q10_MODULO_VALUE);
                insert_index = main_list.insert(value_to_find); // Insert the value to the list to ensure the value is in the list              
                // Find the value using linear search
                auto start_time = std::chrono::high_resolution_clock::now();             
                size_t find_index = main_list.find(value_to_find); 
                auto end_time = std::chrono::high_resolution_clock::now();                  
                total_time += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();    

                // Remove the value to keep the list size constant
                main_list.remove(find_index);
                
            }

            std::cout << "Main list size: " << Q10_MAIN_LIST_SIZE[i] <<  " and total number of trials is: "<< Q10_NUMBER_OF_TRIALS <<std::endl;
            std::cout << "\tTiming for find: " << total_time/1000.0f << " ms" << std::endl;

        }
        
    }

    return 0;
}