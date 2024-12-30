#include <iostream>
#include <cassert>
#include "sudoku.hpp"
#include "memory.hpp"
#include "list.hpp"
#include <stdexcept>

void testListFunctionality()
{
    std::cout << "Starting List Tests...\n";

    // 1. Test default constructor
    {
        List<int> list;
        assert(list.size() == 0 && "Newly constructed list should have size 0.");
        std::cout << "  Default constructor OK\n";
    }

    // 2. Test push_back, push_front, pop_back, pop_front
    {
        List<int> list;
        // push_back
        list.push_back(10);
        list.push_back(20);
        list.push_back(30);
        assert(list.size() == 3 && "List size should be 3 after pushing 3 elements at the back.");

        // push_front
        list.push_front(5);
        list.push_front(2);
        assert(list.size() == 5 && "List size should be 5 after also pushing 2 elements at the front.");

        // Now the list should be: 2, 5, 10, 20, 30
        int val = list.pop_front();
        assert(val == 2 && "pop_front should remove the first element, which is 2.");
        val = list.pop_front();
        assert(val == 5 && "pop_front should remove the next element, which is 5.");

        // Now the list should be: 10, 20, 30
        val = list.pop_back();
        assert(val == 30 && "pop_back should remove the last element, which is 30.");
        val = list.pop_back();
        assert(val == 20 && "pop_back should remove the next-last element, which is 20.");

        // Now the list should be: 10
        assert(list.size() == 1 && "List size should be 1 now.");
        val = list.pop_back(); // remove the last element
        assert(val == 10 && "pop_back should remove the last remaining element, which is 10.");
        assert(list.size() == 0 && "List size should be 0 after removing all elements.");

        // Test popping from empty list exceptions
        bool threw = false;
        try
        {
            list.pop_front();
        }
        catch (const std::runtime_error &e)
        {
            threw = true;
        }
        assert(threw && "pop_front on empty list should throw std::runtime_error.");

        threw = false;
        try
        {
            list.pop_back();
        }
        catch (const std::runtime_error &e)
        {
            threw = true;
        }
        assert(threw && "pop_back on empty list should throw std::runtime_error.");

        std::cout << "  push_* and pop_* methods OK\n";
    }

    // 3. Test copy constructor and copy assignment
    {
        // Create and populate a list
        List<int> list1;
        list1.push_back(1);
        list1.push_back(2);
        list1.push_back(3);

        // Copy constructor
        List<int> list2(list1);
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
        List<int> list3;
        list3.push_back(99); // just to give it some data
        list3 = list1;       // copy assignment
        assert(list3.size() == 3 && "List3 should have size 3 after copy-assignment.");
        // Check data again
        it1 = list1.begin();
        auto it3 = list3.begin();
        for (; it1 != list1.end() && it3 != list3.end(); ++it1, ++it3)
        {
            assert(*it1 == *it3 && "Elements should match after copy assignment.");
        }

        std::cout << "  Copy constructor and copy assignment operator OK\n";
    }

    // 4. Test move constructor and move assignment
    {
        // Move constructor
        List<int> list1;
        list1.push_back(10);
        list1.push_back(20);
        list1.push_back(30);
        List<int> list2(std::move(list1));
        // After move, list1 is empty
        assert(list1.size() == 0 && "Moved-from list should have size 0.");
        // list2 should contain the 3 elements
        assert(list2.size() == 3 && "Moved-to list should have size 3.");

        // Move assignment
        List<int> list3;
        list3.push_back(100);
        list3.push_back(200);

        list3 = std::move(list2);
        // After move, list2 is empty
        assert(list2.size() == 0 && "Moved-from list should have size 0 after move assignment.");
        // list3 should now have the 3 elements (10,20,30)
        assert(list3.size() == 3 && "Moved-to list should have size 3 after move assignment.");

        std::cout << "  Move constructor and move assignment operator OK\n";
    }

    // 5. Test iterators (Iterator and ConstIterator) thoroughly
    {
        List<int> list;
        for (int i = 0; i < 5; ++i)
        {
            list.push_back(i); // 0,1,2,3,4
        }
        assert(list.size() == 5);

        // Test forward iteration with Iterator
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
        {
            auto it = list.begin();
            auto itNext = it.next();
            assert(*it == 0 && *itNext == 1 && "it.next() should point to the next node (0->1).");
        }

        // Test prefix and postfix increments
        {
            auto it = list.begin();
            assert(*it == 0);
            ++it; // prefix
            assert(*it == 1);
            it++; // postfix
            assert(*it == 2);
        }

        // Test ConstIterator
        {
            const List<int> &constRef = list;
            auto cbegin = constRef.begin();
            auto cend = constRef.end();
            int expected = 0;
            for (; cbegin != cend; ++cbegin)
            {
                assert(*cbegin == expected && "ConstIterator should read elements in correct order.");
                expected++;
            }
            assert(expected == 5 && "ConstIterator should have iterated 5 elements.");
        }

        std::cout << "  Iterator and ConstIterator tests OK\n";
    }

    // 6. Test insert
    {
        List<int> list;
        list.push_back(1);
        list.push_back(3);
        list.push_back(5);
        // list: 1,3,5

        // insert at begin (equivalent to push_front)
        list.insert(list.begin(), 0);
        // list: 0,1,3,5

        // insert at end (equivalent to push_back)
        list.insert(list.end(), 6);
        // list: 0,1,3,5,6

        // insert in the middle
        auto it = list.begin();
        ++it; // points to 1
        ++it; // points to 3
        list.insert(it, 2);
        // list: 0,1,2,3,5,6

        // Validate contents: 0,1,2,3,5,6
        int expected[] = {0, 1, 2, 3, 5, 6};
        int idx = 0;
        for (auto iter = list.begin(); iter != list.end(); ++iter)
        {
            assert(*iter == expected[idx] && "Inserted sequence should match expected data.");
            ++idx;
        }
        std::cout << "  insert method OK\n";
    }

    // 7. Test remove
    {
        List<int> list;
        // Will test removing from front, middle, back
        // and also test exception cases
        list.push_back(0);
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(4);
        // list: 0,1,2,3,4

        // Remove from middle (remove '2')
        auto it = list.begin();
        ++it; // '1'
        ++it; // '2'
        auto afterRemoved = list.remove(it);
        // list: 0,1,3,4  (removed '2')
        assert(afterRemoved != list.end() && "remove should return an iterator to the element after the removed one.");
        assert(*afterRemoved == 3 && "afterRemoved should point to '3' after removing '2'.");

        // Remove from front (remove '0')
        auto frontIt = list.begin();
        assert(*frontIt == 0);
        afterRemoved = list.remove(frontIt);
        // list: 1,3,4
        assert(*afterRemoved == 1 && "After removing front, returned iterator should point to the new front (1).");

        // Remove from back (remove '4')
        auto tailIt = list.begin();
        ++tailIt; // '3'
        ++tailIt; // '4'
        auto endIt = list.remove(tailIt);
        // list: 1,3
        assert(endIt == list.end() && "After removing the tail, remove should return end() iterator.");

        // Now list has: 1,3
        // Remove everything else
        auto it1 = list.begin(); // '1'
        list.remove(it1);        // remove '1', list: 3
        auto it2 = list.begin(); // '3'
        list.remove(it2);        // remove '3', list: (empty)
        assert(list.size() == 0 && "All elements removed, list should be empty.");

        // Removing from empty list should throw logic_error
        bool threw = false;
        try
        {
            list.remove(list.begin()); // remove on empty list
        }
        catch (const std::logic_error &e)
        {
            threw = true;
        }
        assert(threw && "Removing from empty list must throw std::logic_error.");

        // Pushing something again
        list.push_back(42);
        // Removing end() iterator should throw logic_error
        threw = false;
        try
        {
            list.remove(list.end()); // removing end()
        }
        catch (const std::logic_error &e)
        {
            threw = true;
        }
        assert(threw && "Removing end() iterator must throw std::logic_error.");

        // Clean up that final element
        list.remove(list.begin());
        assert(list.size() == 0 && "Finally removed the element, so size should be 0.");

        std::cout << "  remove method OK\n";
    }

    std::cout << "All List Tests Passed!\n";
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
    Sudoku sudoku;
    sudoku.set_clues(filename);
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
    if (isTest)
    {
        testListFunctionality();
        testGraphFunctionality();
    }
    else
    {
        std::cout << "Sudoku 1:" << std::endl;
        play("data/s1.txt");
        std::cout << "Sudoku 2:" << std::endl;
        play("data/s2.txt");
        std::cout << "Sudoku 3:" << std::endl;
        play("data/s3.txt"); // No solution
    }
}
