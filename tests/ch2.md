# Chapter 2: Test-Driven Development: A First Example

test-drive a Soundex class that can improve the search capability in an application.

The cycle of TDD, is to write a small test, ensure it fails, get it to pass, review and clean up the design (including that of the tests), and ensure the tests all still pass. 

Three Rules of TDD:

* Write production code only to make a failing test pass.

* Write no more of a unit test than sufficient to fail. Compilation failures are failures.

* Write only the production code needed to pass the one failing test.

At any given point, your complete set of tests declares the behaviors you intend your system to have. The rule of thumb for TDD is one assert per test. TDD is a technique for driving the design of the code. Your tests primarily serve the purpose of specifying the behavior of what you will build. The tests in TDD are almost a by-product of the process. 