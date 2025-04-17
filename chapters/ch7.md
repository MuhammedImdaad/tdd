# Chapter 7: Quality Tests
learn how to design your ​tests​ well to extend their return on value and keep them from becoming a maintenance burden.

Tests Come FIRST
* ​F​ for Fast
    * Build times in C++ present a hefty challenge. lion’s share of the build time directly relates to the dependency structure of your code. You can introduce an interface—a pure virtual void class—that your concrete class realizes. consider using the “pointer to implementation” (PIMPL) idiom too. 
* ​I​ for Isolated
    * You want your tests to be isolated—failing for a single reason. Small and focused tests. each test should verify a small bit of logic independent from external concerns. they should also be independent from other tests. 
* ​R​ for Repeatable
    * Quality unit tests are​ repeatable​—you can run them time after time and always obtain the same results, regardless of which other tests (if any) ran first. Intermittent test failures are bad news. They indicate some level of nondeterministic or otherwise varying behavior in your test runs.  
* ​S​ for Self-verifying
    * You automate tests to get your human self out of the picture—to eliminate slow and risky manual testing.
* ​T​ for Timely
    * you write them first. you write one test at a time, and even within that one test you write one assertion at a time. Your approach is as incremental as it can be. 


your test must clearly state intent. The most important declaration of intent is the test’s name, which should clarify the context and goal. With proper names, you don’t have to read a test to understand what it does.  assert per test? Strive hard to have only one. Sometimes it makes sense to have more, though. You might also choose to have multiple assertions to verify a bunch of data elements. you might combine assertions where the description of behavior doesn’t vary but the implementation is getting more specialized. The key thing to remember is to have one behavior per test. One Assert per Test isn’t a hard rule, but it’s usually a better choice.

 Abstraction is as important in your tests as it is in object-oriented design. Since you want to be able to read your tests as documentation, they must cut to the chase, declaring their intent as clearly and simply as possible. identifying different test smells and cleaning up test code accordingly.
 1.  Bloated Construction - cut through unnecessary test setup details
 2. Irrelevant Details - make use of fixture class, take advantage of the SetUp and ​TearDown ​hook
 3. Missing Abstractions - amplifies your code’s expressiveness, promotes reuse of those small chunks of code, makes subsequent tests easier to write
 4. Multiple Assertions
 5. Irrelevant Data - Data used in a test should help tell its story, even a function argument
 6. Unnecessary Test Code
    * Assert Not Null - Seg faults are no fun
    * Exception Handling -  test-drive a case that documents how exception happens
    * Assertion Failure Comments - no need
    * Comments - no need
    * Implicit Meaning -  be careful not to hide too much details from tests
    * Misleading Organization - Your time to understand existing code is one of the larger expenses in software development
    * Obscure or Missing Name
