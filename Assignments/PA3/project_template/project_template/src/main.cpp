#include <iostream>
#include <cassert>
#include <stdexcept>
#include "sudoku.hpp"
#include "memory.hpp"
#include "list.hpp"

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

/// Helper function to print the graph’s vertices, their colors, and neighbors.
/// Uses the Graph::Vertex's __neighbor_count() / __neighbor_at() for demonstration.
static void printGraph(const Graph &g, const std::string &prefix = "")
{

    size_t numVertices = g.__size(); // or your own approach if .size() doesn't exist
    std::cout << prefix << "Graph has " << numVertices << " vertices:\n";
    for (size_t i = 0; i < numVertices; ++i)
    {
        Graph temp = g; // Copy the graph to avoid modifying the original
        // Attempt to get the Vertex pointer. We'll wrap it in a try block
        // in case operator[](i) throws std::domain_error for invalid ID.
        try
        {
            auto v = temp[i];
            std::cout << prefix << "  Vertex " << i
                      << " (color=" << v->color() << "): [ neighbors: ";
            for (size_t n = 0; n < v->__neighbor_count(); ++n)
            {
                std::cout << v->__neighbor_at(n)->id();
                if (n + 1 < v->__neighbor_count())
                    std::cout << ", ";
            }
            std::cout << " ]\n";
        }
        catch (const std::exception &e)
        {
            std::cout << prefix << "  (Could not access vertex " << i
                      << " => " << e.what() << ")\n";
        }
    }
    std::cout << std::endl;
}

void testGraphFunctionality()
{
    using namespace std;

    cout << "\n=====================================\n";
    cout << "   Starting Graph tests...\n";
    cout << "=====================================\n\n";

    // (1) Test add_vertex
    {
        cout << "[1] Testing add_vertex...\n";

        Graph g;
        cout << "  - Creating a new Graph and adding 3 vertices...\n";
        size_t id1 = g.add_vertex();
        size_t id2 = g.add_vertex();
        size_t id3 = g.add_vertex();
        cout << "  - Expecting IDs: 0, 1, 2 (based on given code). Got: "
             << id1 << ", " << id2 << ", " << id3 << "\n";

        assert(id1 == 0);
        assert(id2 == 1);
        assert(id3 == 2);

        printGraph(g, "    ");
        cout << "  => add_vertex test OK\n\n";

        cout << "[2] Testing operator[](size_t)...\n";
        Graph::Vertex *v1 = g[id1];
        Graph::Vertex *v2 = g[id2];
        Graph::Vertex *v3 = g[id3];
        cout << "  - Checking ID retrieval: v1->id()=" << v1->id()
             << ", v2->id()=" << v2->id() << ", v3->id()=" << v3->id() << "\n";
        assert(v1->id() == id1);
        assert(v2->id() == id2);
        assert(v3->id() == id3);

        // Negative test for invalid IDs
        cout << "  - Testing operator[] with invalid ID (should throw domain_error)...\n";
        bool exceptionCaught = false;
        try
        {
            g[999]; // invalid
        }
        catch (const domain_error &)
        {
            cout << "    Caught expected domain_error for invalid ID.\n";
            exceptionCaught = true;
        }
        assert(exceptionCaught && "Accessing invalid vertex ID did not throw domain_error");

        cout << "  => operator[](size_t) test OK\n\n";

        cout << "[3] Testing connect(size_t, size_t)...\n";
        g.connect(id1, id2);
        cout << "  - Connected vertex " << id1 << " and " << id2 << ".\n";
        printGraph(g, "    ");

        // For undirected graph, v1 <-> v2
        assert(v1->__neighbor_count() == 1);
        assert(v2->__neighbor_count() == 1);
        assert(v1->__neighbor_at(0) == v2);
        assert(v2->__neighbor_at(0) == v1);

        cout << "  - Connecting vertex " << id2 << " and " << id3 << "...\n";
        g.connect(id2, id3);
        printGraph(g, "    ");
        // v2 should have v1 and v3; v3 should have v2
        assert(v2->__neighbor_count() == 2);
        assert(v3->__neighbor_count() == 1);

        // Negative test: connecting a vertex to itself
        cout << "  - Trying to connect a vertex to itself...\n";
        exceptionCaught = false;
        try
        {
            g.connect(id1, id1);
        }
        catch (const invalid_argument &)
        {
            cout << "    Caught expected invalid_argument for self-connection.\n";
            exceptionCaught = true;
        }
        assert(exceptionCaught && "Connecting vertex to itself did not throw invalid_argument");

        // Negative test: connecting invalid IDs
        cout << "  - Trying to connect invalid IDs (100, 200)...\n";
        exceptionCaught = false;
        try
        {
            g.connect(100, 200);
        }
        catch (const domain_error &)
        {
            cout << "    Caught expected domain_error for invalid IDs.\n";
            exceptionCaught = true;
        }
        assert(exceptionCaught && "Connecting invalid IDs did not throw domain_error");

        cout << "  => connect test OK\n\n";

        cout << "[4] Testing Vertex::color(int)...\n";
        cout << "  - Initially, v1->color() = " << v1->color() << " (expected 0)\n";
        assert(v1->color() == 0);

        // Try coloring v1 with color=2
        cout << "  - Coloring v1 with color=2...\n";
        bool colored = v1->color(2);
        printGraph(g, "    ");
        assert(colored && v1->color() == 2);

        // v2 coloring with color=2 should fail because its neighbor v1 is color=2
        cout << "  - Attempting to color v2 with color=2...\n";
        colored = v2->color(2);
        printGraph(g, "    ");
        assert(!colored && "v2->color(2) should fail since v1 is already 2");

        // But coloring with color=3 should succeed
        cout << "  - Coloring v2 with color=3...\n";
        colored = v2->color(3);
        printGraph(g, "    ");
        assert(colored && v2->color() == 3);

        cout << "  => Vertex::color(int) test OK\n\n";

        cout << "[5] Testing Vertex::add_neighbor(...) (idempotency check)...\n";
        size_t neighborCountBefore = v1->__neighbor_count();
        cout << "  - v1 has " << neighborCountBefore << " neighbor(s). Adding v2 again...\n";
        v1->add_neighbor(v2);
        size_t neighborCountAfter = v1->__neighbor_count();
        cout << "  - v1 now has " << neighborCountAfter << " neighbor(s).\n";
        assert(neighborCountBefore == neighborCountAfter && "add_neighbor repeated the same neighbor incorrectly");
        cout << "  => add_neighbor test OK\n\n";

        cout << "[6] Testing Vertex::remove_neighbor(...)\n";
        // v2 currently has neighbors { v1, v3 }. We'll remove v3:
        cout << "  - Removing v3 from v2’s neighbor list...\n";
        assert(v2->__neighbor_count() == 2);
        v2->remove_neighbor(v3);
        printGraph(g, "    ");

        // Now v2 has only v1
        assert(v2->__neighbor_count() == 1);
        // v3 should no longer have v2
        assert(v3->__neighbor_count() == 0);

        cout << "  => remove_neighbor test OK\n\n";

        cout << "[7] Testing max_color()...\n";
        int mc = g.max_color();
        cout << "  - g.max_color() returned: " << mc
             << " (expected max_degree+1). Current max_degree=1 => max_color=2\n";
        assert(mc == 2);

        cout << "  => max_color test OK\n\n";

        cout << "[8] Testing full recursive coloring...\n";
        cout << "  - Reconnecting v2 <-> v3 to form a chain v1--v2--v3\n";
        g.connect(id2, id3);
        // Reset colors
        v1->color(0);
        v2->color(0);
        v3->color(0);
        printGraph(g, "    ");

        bool isColored = g.color(); // the full graph coloring
        cout << "  - Called g.color() => " << (isColored ? "success" : "failure") << "\n";
        printGraph(g, "    ");
        assert(isColored && "Graph coloring failed on a simple chain");
        // Ensure none ended up with color 0
        assert(v1->color() != 0);
        assert(v2->color() != 0);
        assert(v3->color() != 0);

        cout << "  => recursive coloring test OK\n\n";
    }

    cout << "[9] Testing copy constructor / copy assignment...\n";
    {
        Graph g1;
        size_t a = g1.add_vertex();
        size_t b = g1.add_vertex();
        g1.connect(a, b);

        // Color them
        g1[a]->color(1);
        g1[b]->color(2);

        cout << "  - Original g1:\n";
        printGraph(g1, "    ");

        cout << "  - Copy constructing g2 from g1...\n";
        Graph g2(g1);
        printGraph(g2, "    ");

        // They should have distinct Vertex pointers, same ID and color
        assert(g2[a] != g1[a]);
        assert(g2[b] != g1[b]);
        assert(g2[a]->id() == a && g2[b]->id() == b);
        assert(g2[a]->color() == 1 && g2[b]->color() == 2);

        cout << "  - Copy assigning g3 from g1...\n";
        Graph g3;
        g3 = g1;
        printGraph(g3, "    ");
        assert(g3[a] != g1[a]);
        assert(g3[b] != g1[b]);
        assert(g3[a]->id() == a && g3[b]->id() == b);
        assert(g3[a]->color() == 1 && g3[b]->color() == 2);

        cout << "  => copy constructor / assignment tests OK\n\n";
    }

    cout << "[10] Testing move constructor / move assignment...\n";
    {
        Graph g1;
        size_t a = g1.add_vertex();
        size_t b = g1.add_vertex();
        g1.connect(a, b);

        cout << "  - Move constructing g2 from g1...\n";
        Graph g2(std::move(g1));
        cout << "  - After std::move, g1 should have no vertices.\n";

        bool exceptionCaught = false;
        try
        {
            // g1[a] should fail
            g1[a];
        }
        catch (const domain_error &)
        {
            cout << "    Caught expected domain_error (g1 is empty after move).\n";
            exceptionCaught = true;
        }
        assert(exceptionCaught && "After move, g1 should not contain any vertices.");
        cout << "  - g2 now has them:\n";
        printGraph(g2, "    ");

        // Check that g2 has them
        assert(g2[a]->id() == a);
        assert(g2[b]->id() == b);

        cout << "  - Move assigning g3 = std::move(g2)...\n";
        Graph g3;
        g3 = std::move(g2);
        printGraph(g3, "    ");

        exceptionCaught = false;
        try
        {
            // g2[a] should fail
            g2[a];
        }
        catch (const domain_error &)
        {
            cout << "    Caught expected domain_error (g2 is empty after move).\n";
            exceptionCaught = true;
        }
        assert(exceptionCaught && "After move assignment, g2 should not contain any vertices.");

        // g3 has them
        assert(g3[a]->id() == a);
        assert(g3[b]->id() == b);

        cout << "  => move constructor / assignment tests OK\n\n";
    }

    cout << "==============================================\n";
    cout << " All Graph tests passed successfully!\n";
    cout << "==============================================\n\n";
}

int main()
{
    // I could not implement the sudoku class. I am sorry for that. I will stick with the directive:
    // DIRECTIVE ->'If your implementation is incomplete, modify the main function so that it can demonstrate all the features you have implemented.'
    // I have added some testing functions to acces private members of the classes. They are not used in any of the usefull functions.
    testListFunctionality();
    testGraphFunctionality();
}
