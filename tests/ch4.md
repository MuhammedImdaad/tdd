# Chapter 4: Test Construction

how to group your tests using fixtures, as well as how to take advantage of their setup and teardown hooks.
* File Organization - Name the file based on the tests it contains
* Fixtures - a class that provides support for cross-test reuse.
* Setup and Teardown - After creating the fixture instance, Google Mock executes the code in ​SetUp ​and then executes the test itself.

A core goal of doing TDD is to obtain as much feedback as possible as often as possible. When you change a small bit of code, you want to know immediately whether your change was correct. TDD begins to diminish in power as the feedback cycle lengthens. 

Running a Subset of the Tests

* Google Mock makes it easy to run a subset of the tests by specifying what is known as a​ test filter​.
``` 	
./test --gtest_filter=test_suite_name.test_name 
```

Assertions 

Assertions turn a test into an automated test. Google Mock, like most C++ unit-testing frameworks, uses macros to implement the behavior for assertions. 
* Classic Form Assertions - ASSERT_EQ, ASSERT_TRUE
* Hamcrest Assertions - ASSERT_THAT an attempt to improve the expressiveness of tests, the flexibility of creating complex assertions, and the information supplied by failure messages. 

Comparing Floats - example provided

Exception-Based Tests
* Suppose you are testing a bit of code that throws an exception under certain circumstances. Your job as a professional is to document that case in a test.

Inspecting Privates

* When test-driving, everything flows from the public interface design of your class. To add detailed behavior, you test-drive it as if your test were a production client of the class. Tests that verify by inspecting attributes of an object are known as​ state-based tests​. 
* Exposing data solely for the purpose of testing will bother some folks, but it’s more important to know that your code works as intended. 
* Most of the time, when you feel compelled to test private behavior, instead move the code to another class or to a new class. As you start creating more single-purpose classes, each containing a small number of single-purpose methods, you’ll start to recognize more opportunities for OO reuse.

Testing vs. Test-Driving

* You create tests for five types of cases: zero, one, many, boundary, and exceptional cases.
* you stop test-driving as soon you have the confidence that you’ve built all you need, stop once you can’t think of how to write a test that would fail. 
* a good tester seeks to cover the five types of cases as exhaustively as reasonable.
* Parameterized Tests - example provided, however with these you’re no longer in the realm of TDD
