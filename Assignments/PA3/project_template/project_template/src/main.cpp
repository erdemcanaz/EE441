#include <iostream>
#include <cassert>
#include "sudoku.hpp"
#include "memory.hpp"
#include "list.hpp"
#include <stdexcept>

/// Utility function to print a given list and its size
template <typename T>
void printList(const List<T> &list, const std::string &prefix = "")
{
    std::cout << prefix << "List contents [size=" << list.size() << "]: ";
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void testListFunctionality()
{
    std::cout << "\n===============================\n";
    std::cout << "   Starting List Tests...\n";
    std::cout << "===============================\n\n";

    // 1. Test default constructor
    {
        std::cout << "(1) Testing default constructor...\n";

        List<int> list;
        std::cout << "  - Created an empty List<int>.\n";
        printList(list, "  - ");

        assert(list.size() == 0 && "Newly constructed list should have size 0.");
        std::cout << "  => Default constructor OK\n\n";
    }

    // 2. Test push_back, push_front, pop_back, pop_front
    {
        std::cout << "(2) Testing push_back, push_front, pop_back, pop_front...\n";

        List<int> list;
        std::cout << "  - Initially created an empty list.\n";
        printList(list, "    ");

        // push_back
        std::cout << "  - Pushing back 10, 20, 30...\n";
        list.push_back(10);
        list.push_back(20);
        list.push_back(30);
        printList(list, "    ");

        assert(list.size() == 3 &&
               "List size should be 3 after pushing 3 elements at the back.");

        // push_front
        std::cout << "  - Pushing front 5, then 2...\n";
        list.push_front(5);
        list.push_front(2);
        printList(list, "    ");

        assert(list.size() == 5 &&
               "List size should be 5 after also pushing 2 elements at the front.");

        std::cout << "  - Popping from the front...\n";
        int val = list.pop_front();
        printList(list, "    ");
        assert(val == 2 && "pop_front should remove the first element, which is 2.");

        val = list.pop_front();
        printList(list, "    ");
        assert(val == 5 && "pop_front should remove the next element, which is 5.");

        std::cout << "  - Popping from the back...\n";
        val = list.pop_back();
        printList(list, "    ");
        assert(val == 30 && "pop_back should remove the last element, which is 30.");

        val = list.pop_back();
        printList(list, "    ");
        assert(val == 20 && "pop_back should remove the next-last element, which is 20.");

        // Now the list should be: 10
        assert(list.size() == 1 && "List size should be 1 now.");
        std::cout << "  - Popping the last element...\n";
        val = list.pop_back(); // remove the last element
        printList(list, "    ");
        assert(val == 10 && "pop_back should remove the last remaining element, which is 10.");
        assert(list.size() == 0 && "List size should be 0 after removing all elements.");

        // Test popping from empty list exceptions
        bool threw = false;
        std::cout << "  - Testing pop_front() exception on empty list...\n";
        try
        {
            list.pop_front();
        }
        catch (const std::runtime_error &e)
        {
            std::cout << "    Caught expected exception: " << e.what() << std::endl;
            threw = true;
        }
        assert(threw && "pop_front on empty list should throw std::runtime_error.");

        threw = false;
        std::cout << "  - Testing pop_back() exception on empty list...\n";
        try
        {
            list.pop_back();
        }
        catch (const std::runtime_error &e)
        {
            std::cout << "    Caught expected exception: " << e.what() << std::endl;
            threw = true;
        }
        assert(threw && "pop_back on empty list should throw std::runtime_error.");

        std::cout << "  => push_* and pop_* methods OK\n\n";
    }

    // 3. Test copy constructor and copy assignment
    {
        std::cout << "(3) Testing copy constructor and copy assignment...\n";

        // Create and populate a list
        List<int> list1;
        list1.push_back(1);
        list1.push_back(2);
        list1.push_back(3);
        std::cout << "  - Original list1:\n";
        printList(list1, "    ");

        // Copy constructor
        std::cout << "  - Creating list2 by copy-constructing from list1...\n";
        List<int> list2(list1);
        printList(list2, "    ");

        assert(list1.size() == 3 && "Original list should still have size 3.");
        assert(list2.size() == 3 && "Copied list should have size 3.");

        // Check that the data is the same
        auto it1 = list1.begin();
        auto it2 = list2.begin();
        for (; it1 != list1.end() && it2 != list2.end(); ++it1, ++it2)
        {
            assert(*it1 == *it2 && "Elements should match after copy construction.");
        }

        // Copy assignment
        std::cout << "  - Creating list3 and copying list1 into it...\n";
        List<int> list3;
        list3.push_back(99); // just to give it some data
        std::cout << "    list3 before copy-assignment:\n";
        printList(list3, "    ");

        list3 = list1; // copy assignment
        std::cout << "    list3 after copy-assignment:\n";
        printList(list3, "    ");

        assert(list3.size() == 3 && "List3 should have size 3 after copy-assignment.");
        it1 = list1.begin();
        auto it3 = list3.begin();
        for (; it1 != list1.end() && it3 != list3.end(); ++it1, ++it3)
        {
            assert(*it1 == *it3 && "Elements should match after copy assignment.");
        }

        std::cout << "  => Copy constructor and copy assignment operator OK\n\n";
    }

    // 4. Test move constructor and move assignment
    {
        std::cout << "(4) Testing move constructor and move assignment...\n";

        // Move constructor
        List<int> list1;
        list1.push_back(10);
        list1.push_back(20);
        list1.push_back(30);
        std::cout << "  - list1 before move-construction:\n";
        printList(list1, "    ");

        std::cout << "  - Creating list2 by std::move(list1)...\n";
        List<int> list2(std::move(list1));
        std::cout << "    list1 (moved-from):\n";
        printList(list1, "    ");
        std::cout << "    list2 (moved-to):\n";
        printList(list2, "    ");

        // After move, list1 is empty
        assert(list1.size() == 0 && "Moved-from list should have size 0.");
        // list2 should contain the 3 elements
        assert(list2.size() == 3 && "Moved-to list should have size 3.");

        // Move assignment
        List<int> list3;
        list3.push_back(100);
        list3.push_back(200);
        std::cout << "  - list3 before move-assignment:\n";
        printList(list3, "    ");

        std::cout << "  - Performing list3 = std::move(list2)...\n";
        list3 = std::move(list2);
        std::cout << "    list2 (moved-from):\n";
        printList(list2, "    ");
        std::cout << "    list3 (moved-to):\n";
        printList(list3, "    ");

        // After move, list2 is empty
        assert(list2.size() == 0 && "Moved-from list should have size 0 after move assignment.");
        // list3 should now have the 3 elements (10,20,30)
        assert(list3.size() == 3 && "Moved-to list should have size 3 after move assignment.");

        std::cout << "  => Move constructor and move assignment operator OK\n\n";
    }

    // 5. Test iterators (Iterator and ConstIterator) thoroughly
    {
        std::cout << "(5) Testing Iterator and ConstIterator...\n";

        List<int> list;
        for (int i = 0; i < 5; ++i)
        {
            list.push_back(i); // 0,1,2,3,4
        }
        printList(list, "  - ");

        assert(list.size() == 5);

        // Test forward iteration with Iterator
        std::cout << "  - Verifying forward iteration...\n";
        {
            int expected = 0;
            for (auto it = list.begin(); it != list.end(); ++it)
            {
                assert(*it == expected && "Iterator should return elements in correct order.");
                expected++;
            }
            assert(expected == 5 && "We should have iterated over 5 elements.");
        }

        // Test next() on an iterator
        std::cout << "  - Testing it.next()...\n";
        {
            auto it = list.begin();
            auto itNext = it.next();
            std::cout << "    *it = " << *it << ", *itNext = " << *itNext << "\n";
            assert(*it == 0 && *itNext == 1 &&
                   "it.next() should point to the next node (0->1).");
        }

        // Test prefix and postfix increments
        std::cout << "  - Testing prefix and postfix ++...\n";
        {
            auto it = list.begin();
            assert(*it == 0);
            ++it; // prefix
            assert(*it == 1);
            it++; // postfix
            assert(*it == 2);
        }

        // Test ConstIterator
        std::cout << "  - Testing ConstIterator...\n";
        {
            const List<int> &constRef = list;
            auto cbegin = constRef.begin();
            auto cend = constRef.end();
            int expected = 0;
            for (; cbegin != cend; ++cbegin)
            {
                assert(*cbegin == expected &&
                       "ConstIterator should read elements in correct order.");
                expected++;
            }
            assert(expected == 5 && "ConstIterator should have iterated 5 elements.");
        }

        std::cout << "  => Iterator and ConstIterator tests OK\n\n";
    }

    // 6. Test insert
    {
        std::cout << "(6) Testing insert function...\n";

        List<int> list;
        list.push_back(1);
        list.push_back(3);
        list.push_back(5);
        std::cout << "  - Starting list:\n";
        printList(list, "    ");

        // insert at begin (equivalent to push_front)
        std::cout << "  - Inserting 0 at the beginning...\n";
        list.insert(list.begin(), 0);
        printList(list, "    ");

        // insert at end (equivalent to push_back)
        std::cout << "  - Inserting 6 at the end...\n";
        list.insert(list.end(), 6);
        printList(list, "    ");

        // insert in the middle
        std::cout << "  - Inserting 2 before the '3'...\n";
        auto it = list.begin();
        ++it; // points to 1
        ++it; // points to 3
        list.insert(it, 2);
        printList(list, "    ");

        // Validate contents: 0,1,2,3,5,6
        int expected[] = {0, 1, 2, 3, 5, 6};
        int idx = 0;
        for (auto iter = list.begin(); iter != list.end(); ++iter)
        {
            assert(*iter == expected[idx] && "Inserted sequence should match expected data.");
            ++idx;
        }
        std::cout << "  => insert method OK\n\n";
    }

    // 7. Test remove
    {
        std::cout << "(7) Testing remove function...\n";
        List<int> list;
        list.push_back(0);
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(4);
        std::cout << "  - Starting list:\n";
        printList(list, "    ");

        // Remove from middle (remove '2')
        std::cout << "  - Removing '2' from the list...\n";
        auto it = list.begin();
        ++it; // '1'
        ++it; // '2'
        auto afterRemoved = list.remove(it);
        printList(list, "    ");
        assert(afterRemoved != list.end() &&
               "remove should return an iterator to the element after the removed one.");
        assert(*afterRemoved == 3 &&
               "afterRemoved should point to '3' after removing '2'.");

        // Remove from front (remove '0')
        std::cout << "  - Removing front element ('0')...\n";
        auto frontIt = list.begin();
        assert(*frontIt == 0);
        afterRemoved = list.remove(frontIt);
        printList(list, "    ");
        assert(*afterRemoved == 1 &&
               "After removing front, returned iterator should point to the new front (1).");

        // Remove from back (remove '4')
        std::cout << "  - Removing last element ('4')...\n";
        auto tailIt = list.begin();
        ++tailIt; // '3'
        ++tailIt; // '4'
        auto endIt = list.remove(tailIt);
        printList(list, "    ");
        assert(endIt == list.end() &&
               "After removing the tail, remove should return end() iterator.");

        std::cout << "  - Removing remaining elements...\n";
        // Now list has: 1,3
        // Remove everything else
        auto it1 = list.begin(); // '1'
        list.remove(it1);        // remove '1', list: 3
        printList(list, "    ");

        auto it2 = list.begin(); // '3'
        list.remove(it2);        // remove '3', list: (empty)
        printList(list, "    ");

        assert(list.size() == 0 && "All elements removed, list should be empty.");

        // Removing from empty list should throw logic_error
        bool threw = false;
        std::cout << "  - Testing remove on empty list...\n";
        try
        {
            list.remove(list.begin()); // remove on empty list
        }
        catch (const std::logic_error &e)
        {
            std::cout << "    Caught expected exception: " << e.what() << std::endl;
            threw = true;
        }
        assert(threw && "Removing from empty list must throw std::logic_error.");

        // Pushing something again
        std::cout << "  - Pushing back 42...\n";
        list.push_back(42);
        printList(list, "    ");

        // Removing end() iterator should throw logic_error
        threw = false;
        std::cout << "  - Testing remove on end() iterator...\n";
        try
        {
            list.remove(list.end()); // removing end()
        }
        catch (const std::logic_error &e)
        {
            std::cout << "    Caught expected exception: " << e.what() << std::endl;
            threw = true;
        }
        assert(threw && "Removing end() iterator must throw std::logic_error.");

        // Clean up that final element
        std::cout << "  - Removing last element (42)...\n";
        list.remove(list.begin());
        printList(list, "    ");
        assert(list.size() == 0 && "Finally removed the element, so size should be 0.");

        std::cout << "  => remove method OK\n\n";
    }

    std::cout << "=====================================\n";
    std::cout << " All List Tests Passed Successfully!\n";
    std::cout << "=====================================\n\n";
}

// Include your graph header here
#include "graph.hpp"

void testGraphFunctionality()
{
    using namespace std;

    cout << "Starting Graph tests..." << endl;

    // 1) Test add_vertex (IDs should start from 1, but the provided code uses size() as ID which starts from 0).
    //    Adjust the following tests depending on how you've finally implemented 'add_vertex'.
    {
        Graph g;
        size_t id1 = g.add_vertex();
        size_t id2 = g.add_vertex();
        size_t id3 = g.add_vertex();

        // Expect IDs: 0, 1, 2 (given the posted code)
        // or 1, 2, 3 (if you adjusted to requirement #5).
        assert(id1 == 0);
        assert(id2 == 1);
        assert(id3 == 2);

        // 2) Test operator[](size_t id): check we can retrieve the correct vertex pointer
        Graph::Vertex *v1 = g[id1];
        Graph::Vertex *v2 = g[id2];
        Graph::Vertex *v3 = g[id3];
        assert(v1->id() == id1);
        assert(v2->id() == id2);
        assert(v3->id() == id3);

        // Negative test: Ensure we throw std::domain_error if vertex does not exist
        bool exceptionCaught = false;
        try
        {
            g[999]; // This should throw
        }
        catch (const domain_error &)
        {
            exceptionCaught = true;
        }
        assert(exceptionCaught && "Accessing invalid vertex ID did not throw domain_error");

        // 3) Test connect(size_t id1, size_t id2)
        g.connect(id1, id2);
        // For an undirected graph, v1 should have v2 as neighbor and v2 should have v1
        assert(v1->__neighbor_count() == 1);
        assert(v2->__neighbor_count() == 1);
        assert(v1->__neighbor_at(0) == v2);
        assert(v2->__neighbor_at(0) == v1);

        // Another connection
        g.connect(id2, id3);
        // Now v2 should have both v1 and v3
        assert(v2->__neighbor_count() == 2);
        // v3 should have v2 as neighbor
        assert(v3->__neighbor_count() == 1);

        // Negative test: connecting a vertex to itself
        exceptionCaught = false;
        try
        {
            g.connect(id1, id1);
        }
        catch (const invalid_argument &)
        {
            exceptionCaught = true;
        }
        assert(exceptionCaught && "Connecting vertex to itself did not throw invalid_argument");

        // Negative test: connecting two non-existent vertices
        exceptionCaught = false;
        try
        {
            g.connect(100, 200);
        }
        catch (const domain_error &)
        {
            exceptionCaught = true;
        }
        assert(exceptionCaught && "Connecting invalid IDs did not throw domain_error");

        // 4) Test Vertex::color(int color) for a single vertex (requirement #1)
        //    color(0) should always succeed (reset color)
        assert(v1->color() == 0); // default
        bool colored = v1->color(2);
        assert(colored && v1->color() == 2);
        // Now v1 has color=2; if v2 tries to color with color=2, it should fail
        colored = v2->color(2);
        assert(!colored && "Neighbor already has color=2, so v2->color(2) should fail");
        // But color(3) should succeed
        colored = v2->color(3);
        assert(colored && v2->color() == 3);

        // 5) Test Vertex::add_neighbor (already tested via Graph::connect, but let's do direct test)
        //    We expect that add_neighbor is idempotent (adding same neighbor again does nothing).
        v1->add_neighbor(v2);
        // Should still have exactly one neighbor
        assert(v1->__neighbor_count() == 1 && "add_neighbor repeated the same neighbor incorrectly");

        // 6) Test Vertex::remove_neighbor
        //    Remove v3 from v2's neighbor list.
        //    Before removal, v2's neighbor list has v1 and v3
        assert(v2->__neighbor_count() == 2);
        v2->remove_neighbor(v3);
        // Now v2 has only v1
        assert(v2->__neighbor_count() == 1);
        // Also v3 should no longer have v2
        assert(v3->__neighbor_count() == 0);

        // 7) Test max_color()
        //    The highest degree is with v2 (which has v1 as neighbor, degree=1).
        //    Actually, v2 used to have degree=2, but we removed v3 from its list, so now max_degree is 1
        //    So max_color() == max_degree + 1 == 2
        int mc = g.max_color();
        assert(mc == 2 && "max_color() should return (max_degree + 1) = 2");

        // 8) Test the full graph coloring (recursive)
        //    Let's reconnect v2 <-> v3 for a small chain: v1 -- v2 -- v3
        g.connect(id2, id3);
        // Clear existing colors
        v1->color(0);
        v2->color(0);
        v3->color(0);
        bool isColored = g.color();
        assert(isColored && "Graph coloring failed on a simple chain");
        // After a successful 2-coloring, we expect something like v1=1, v2=2, v3=1 or similar.
        // Let's just ensure none of them is 0
        assert(v1->color() != 0);
        assert(v2->color() != 0);
        assert(v3->color() != 0);
    }

    // 9) Test copy constructor / copy assignment
    {
        Graph g1;
        size_t a = g1.add_vertex();
        size_t b = g1.add_vertex();
        g1.connect(a, b);
        // color them:
        g1[a]->color(1);
        g1[b]->color(2);

        // Copy constructor
        Graph g2(g1);
        // They should have distinct Vertex* pointers, but same IDs and colors
        assert(g2[a] != g1[a]);
        assert(g2[b] != g1[b]);
        assert(g2[a]->id() == a && g2[b]->id() == b);
        assert(g2[a]->color() == 1 && g2[b]->color() == 2);

        // Copy assignment
        Graph g3;
        g3 = g1; // operator=
        assert(g3[a] != g1[a]);
        assert(g3[b] != g1[b]);
        assert(g3[a]->id() == a && g3[b]->id() == b);
        assert(g3[a]->color() == 1 && g3[b]->color() == 2);
    }

    // 10) Test move constructor / move assignment
    {
        Graph g1;
        size_t a = g1.add_vertex();
        size_t b = g1.add_vertex();
        g1.connect(a, b);

        // Move constructor
        Graph g2(std::move(g1));
        // g1 should no longer have vertices; g2 took them.
        bool exceptionCaught = false;
        try
        {
            // This should fail because g1 should not have any vertices after the move
            g1[a];
        }
        catch (const std::domain_error &)
        {
            exceptionCaught = true;
        }
        assert(exceptionCaught && "After move, g1 should not contain any vertices.");

        // Check that g2 has them
        assert(g2[a]->id() == a);
        assert(g2[b]->id() == b);

        // Move assignment
        Graph g3;
        g3 = std::move(g2);
        // Now g2 has no vertices, while g3 has them
        exceptionCaught = false;
        try
        {
            g2[a];
        }
        catch (const std::domain_error &)
        {
            exceptionCaught = true;
        }
        assert(exceptionCaught && "After move assignment, g2 should not contain any vertices.");
        // g3 has them
        assert(g3[a]->id() == a);
        assert(g3[b]->id() == b);
    }

    cout << "All Graph tests passed successfully!" << endl;
}

void play(const char *filename)
{
    std::cout << "AAA:" << std::endl;
    Sudoku sudoku;
    try
    {
        sudoku.set_clues(filename);
        std::cout << "Initial board:" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    sudoku.print();
    if (sudoku.solve())
    {
        sudoku.print();
    }
    else
    {
        std::cout << "No solution available!\n"
                  << std::endl;
    }
}

bool isTest = true;
int main()
{
    testListFunctionality();
    testGraphFunctionality();
}
