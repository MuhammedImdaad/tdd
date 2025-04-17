# Chapter 3: Test-Driven Development Foundations
A single unit test consists of a descriptive name and a series of code statements, conceptually divided into four (ordered) parts.

1. (Optional) statements that set up a context for execution
2. One or more statements to invoke the behavior you want to verify
3. One or more statements to verify the expected outcome
4. (Optional) cleanup statements

When doing TDD, you write the tests first, you strive to keep the granularity of tests small and consistent, and you seek myriad other benefits—most importantly the ability to safely change existing code. unit tests allow you to verify units in isolation from other code. Integration tests verify code that must ​integrate​ with other code or with external entities. 

When doing TDD, you repeat a short cycle of the following:

1. Write a test (“red”)
2. Get the test to pass (“green”)
3. Optimize the design (“refactor”)

The cycle of TDD is simple, but the reality of building production-quality code rarely is. Doing TDD is not a mindless exercise.

Robert C. Martin (“Uncle Bob”) provides a concise set of rules for practicing TDD.

1. Write production code only to pass a failing unit test.
2. Write no more of a unit test than sufficient to fail (compilation failures are failures).
3. Write no more production code than necessary to pass the one failing unit test.

you’ll find yourself sometimes writing tests that pass right off the bat. refer to these undesired events as​ premature passes​. You might experience a premature pass for one of many reasons:

* Running the wrong tests
* Testing the wrong code
* Unfortunate test specification
* Invalid assumptions about the system
* Suboptimal test order
* Linked production code
* Overcoding
* Testing for confidence

Here are a half-dozen useful mind-sets to adopt when doing TDD.
* Incrementalism - Anything not tested is not implemented, and anything tested is implemented correctly and completely.
* Test Behavior, Not Methods
* Using Tests to Describe Behavior - The documentation aspect of the tests is a by-product of doing TDD. 
* Keeping It Simple
* Sticking to the Cycle

various specific techniques that will help keep you on track.
* What’s the Next Test? - categorize each increment as a transformation form. All transformations are prioritized from simplest (highest priority) to most complex (lowest priority). Incrementing in transformation priority order will produce an ideal ordering of tests. 
* Ten-Minute Limit - If the time limit hits, discard your current effort and start over. A good version control tool like git makes reverting easy. 
* Defects - Once you think you’ve pinpointed the problem source, don’t simply fix it and move on. This is TDD!
* Disabling Tests - Don’t check in code with disabled (or commented-out) tests unless you have a really good reason. 