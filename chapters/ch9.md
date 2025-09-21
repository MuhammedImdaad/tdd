# Chapter 9: TDD and Threading
Building multithreaded code is perhaps the most difficult task in software development. writing tests that cope with multiple threads!!!

few core concepts around test-driving threads.
* Separate threading logic from application logic
* ​Sleep is bad
* Throttle down to single-threaded for application-specific tests. To override threading control, you can either design hooks into your application or introduce test doubles.
* Demonstrate concurrency issues before introducing concurrency controls. add only the concurrency control that makes the test pass.

Consistent failure when dealing with threads is a great step toward a solution.

    TEST_F(AThreadPoolExtended, PullsWorkInAThread)
    Thread 808 started
    160 Work added to queue
    160 Notified worker threads
    808 Thread waiting...1
    808 pulling out 1
    808 pulled out
    808 Executing work...
    808 Thread waiting...0
    160 Notified worker threads to stop
    808 Thread exiting...
    160 going off
