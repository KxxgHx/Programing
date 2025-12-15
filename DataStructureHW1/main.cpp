#include <iostream>
#include "ourset.h"

using namespace std;

void test_insert_and_show();
void test_copy_constructor();
void test_erase();
void test_count();
void test_union_operators();
void test_equality_operators();
void test_assignment_operator();
void test_sort();
void test_sort_with_iterator();

int main()
{
    cout << "Test all" << endl;
    
    test_insert_and_show();
    test_copy_constructor();
    test_erase();
    test_count();
    test_union_operators();
    test_equality_operators();
    test_assignment_operator();
    test_sort();
    test_sort_with_iterator();
    
    
    return 0;
}

void test_insert_and_show()
{
    cout << "TEST 1: Insert and Show" << endl;
    
    OurSet<int> set1;
    cout << "Created empty set1" << endl;
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl << endl;
    
    cout << "Inserting 5" << endl;
    set1.insert(5);
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl << endl;
    
    cout << "Inserting 3" << endl;
    set1.insert(3);
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl << endl;
    
    cout << "Inserting 8" << endl;
    set1.insert(8);
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl << endl;
    
    cout << "Inserting 1" << endl;
    set1.insert(1);
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl << endl;
    
    cout << "Inserting 9" << endl;
    set1.insert(9);
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl << endl;
    
    cout << "insert duplicate 5" << endl;
    bool result = set1.insert(5);
    cout << "Insert result: " << (result ? "Success" : "Failed (duplicate)") << endl;
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl << endl;
    
    cout << endl;
}

void test_copy_constructor()
{
    cout << "TEST 2: Copy Constructor" << endl;
    
    OurSet<int> set1;
    set1.insert(10);
    set1.insert(20);
    set1.insert(30);
    
    cout << "Created set1 10, 20, 30" << endl;
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl << endl;
    
    cout << "Creating set2 copy set1" << endl;
    OurSet<int> set2(set1);
    cout << "set2: "; 
    set2.show_contents(); 
    cout << " (size: " << set2.size() << ")" << endl << endl;
    
    cout << "set2 insert 40" << endl;
    set2.insert(40);
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl;
    cout << "set2: "; 
    set2.show_contents(); 
    cout << " (size: " << set2.size() << ")" << endl << endl;
    
    cout << endl;
}

void test_erase()
{
    cout << "TEST 3: Erase Function" << endl;
    
    OurSet<int> set1;
    set1.insert(5);
    set1.insert(3);
    set1.insert(8);
    set1.insert(1);
    set1.insert(9);
    
    cout << "Created set1 5, 3, 8, 1, 9" << endl;
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl << endl;
    
    cout << "Erasing 3" << endl;
    bool result = set1.erase(3);
    cout << "Erase result: " << (result ? "Success" : "Failed (not found)") << endl;
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl << endl;
    
    cout << "Erasing 1" << endl;
    result = set1.erase(1);
    cout << "Erase result: " << (result ? "Success" : "Failed (not found)") << endl;
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl << endl;
    
    cout << "erase  100" << endl;
    result = set1.erase(100);
    cout << "Erase result: " << (result ? "Success" : "Failed (not found)") << endl;
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl << endl;
    
    cout << endl;
}

void test_count()
{
    cout << "TEST 4: Count Function" << endl;
    
    OurSet<int> set1;
    set1.insert(5);
    set1.insert(3);
    set1.insert(8);
    
    cout << "Created set1 5, 3, 8" << endl;
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl << endl;
    
    cout << "count(5): " << set1.count(5) << endl;
    cout << "count(3): " << set1.count(3) << endl;
    cout << "count(8): " << set1.count(8) << endl;
    cout << "count(100): " << set1.count(100) << endl << endl;
    
    cout << endl;
}

void test_union_operators()
{
    cout << "TEST 5: Union Operators (+ and +=)" << endl;
    
    OurSet<int> set1, set2;
    set1.insert(1);
    set1.insert(3);
    set1.insert(5);
    
    set2.insert(2);
    set2.insert(4);
    set2.insert(5);
    
    cout << "Created two sets:" << endl;
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl;
    cout << "set2: "; 
    set2.show_contents(); 
    cout << " (size: " << set2.size() << ")" << endl << endl;
    
    cout << "Testing operator+: set3 = set1 + set2" << endl;
    OurSet<int> set3 = set1 + set2;
    cout << "set3: "; 
    set3.show_contents(); 
    cout << " (size: " << set3.size() << ")" << endl << endl;
    
    cout << "Testing operator+=: set1 += set2" << endl;
    cout << "Before: set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl;
    set1 += set2;
    cout << "After:  set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl << endl;
    
    cout << endl;
}

void test_equality_operators()
{
    cout << "TEST 6: Equality Operators (== and !=)" << endl;
    
    OurSet<int> set1, set2, set3;
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    
    set2.insert(1);
    set2.insert(2);
    set2.insert(3);
    
    set3.insert(1);
    set3.insert(2);
    set3.insert(4);
    
    cout << "Created three sets:" << endl;
    cout << "set1: "; 
    set1.show_contents(); 
    cout << endl;
    cout << "set2: "; 
    set2.show_contents(); 
    cout << endl;
    cout << "set3: "; 
    set3.show_contents(); 
    cout << endl << endl;
    
    cout << "set1 == set2: " << (set1 == set2 ? "true" : "false") << endl;
    cout << "set1 != set2: " << (set1 != set2 ? "true" : "false") << endl;
    cout << "set1 == set3: " << (set1 == set3 ? "true" : "false") << endl;
    cout << "set1 != set3: " << (set1 != set3 ? "true" : "false") << endl << endl;
    
    cout << endl;
}

void test_assignment_operator()
{
    cout << "TEST 7: Assignment Operator (=)" << endl;
    
    OurSet<int> set1, set2;
    set1.insert(10);
    set1.insert(20);
    set1.insert(30);
    
    set2.insert(40);
    set2.insert(50);
    
    cout << "Before assignment:" << endl;
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl;
    cout << "set2: "; 
    set2.show_contents(); 
    cout << " (size: " << set2.size() << ")" << endl << endl;
    
    cout << "Performing: set2 = set1" << endl;
    set2 = set1;
    
    cout << "After assignment:" << endl;
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl;
    cout << "set2: "; 
    set2.show_contents(); 
    cout << " (size: " << set2.size() << ")" << endl << endl;
    
    cout << "Testing self-assignment: set1 = set1" << endl;
    set1 = set1;
    cout << "set1: "; 
    set1.show_contents(); 
    cout << " (size: " << set1.size() << ")" << endl << endl;
    
    cout << endl;
}

void test_sort()
{
    cout << "TEST 8: Sort Function (Extra Credit)" << endl;
    
    OurSet<int> set1;
    set1.insert(7);
    set1.insert(2);
    set1.insert(9);
    set1.insert(1);
    set1.insert(5);
    set1.insert(3);
    
    cout << "Created set1 with unsorted values" << endl;
    cout << "Before sort: "; 
    set1.show_contents(); 
    cout << endl;
    
    set1.sort();
    
    cout << "After sort:  "; 
    set1.show_contents(); 
    cout << endl << endl;
    
    cout << endl;
}

void test_sort_with_iterator()
{
    cout << "TEST 9: Sort with Iterator (Extra Credit)" << endl;
    
    OurSet<int> set1;
    set1.insert(8);
    set1.insert(3);
    set1.insert(6);
    set1.insert(1);
    set1.insert(4);
    set1.insert(9);
    
    cout << "Created set1 not sort" << endl;
    cout << "Before sort_with_iterator: "; 
    set1.show_contents(); 
    cout << endl;
    
    set1.sort_with_iterator();
    
    cout << "After sort_with_iterator:  "; 
    set1.show_contents(); 
    cout << endl << endl;
    
    cout << endl;
}