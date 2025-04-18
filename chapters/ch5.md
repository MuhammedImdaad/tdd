# Chapter 5: Test Doubles
objects must work with other objects. such can cause pesky challenges for test-driving. they can be slow, unstable, or not even around to help you yet. first learn how to break such dependencies using handcrafted test doubles. then see how you might simplify the creation of test doubles by using a tool. 

Why do these dependency concerns create testing challenges
* a dependency on slow collaborators results in undesirably slow tests.
* a dependency on a volatile service (either unavailable or returning different answers each time) results in intermittently failing tests.

test3.cpp contain a Hand-Crafted Test Double to test drive PlaceDescriptionService.h. So someone has to implement the mocks. The job is usually tedious and error-prone. No wonder people go great distance to avoid it.

test4.cpp contain same test-driven design using google mock. https://google.github.io/googletest/gmock_for_dummies.html is a great place to start. Google Mock is a general-purpose unit testing tool that supports mocking for just about any convolution that you can code. Google Mock has solid support for side-effect actions, including the ability to throw exceptions, set variable values, delete arguments, and invoke functions or functors. 

in google mock, Where’s the assertion? Google Mock does its verification when the mock object goes out of scope. don’t use wildcard matchers unless you truly don’t care about the arguments or if you already have other tests that do care. Ignoring the Google Mock warning is unacceptable; we must eliminate it. The NiceMock template effectively tells Google Mock to track interactions only for methods on which expectations exist. In contrast, wrapping a mock in StrictMock turns the uninteresting mock call warning into an error.
Google Mock doesn’t concern itself with verifying the order in which expectations are met. If you’re concerned about order, you can tell Google Mock (and many other C++ mocking tools) to verify it. 

Just because you can doesn’t necessarily mean you should, though. Most of the time, the basic Google Mock mechanisms you learned earlier will suffice. When test-driving, if you find yourself seeking esoteric mock tool features frequently, stop and take a look at your design. Are you testing a method that’s doing too much? Can you restructure your design in a manner so that you don’t need such complex mocking? More often than not, you can.

You have two jobs when introducing a test double. First, code the test double. Second, get the target to use an instance of it. Certain techniques for doing so are known as​ dependency injection​(DI). Do not use setter or constructor injection to avoid clients take on the responsibility of creating Http objects and passing them in (to make it private). 

* via a constructor
* using a setter member function
* Override Factory Method
* Override Getter Method
* Introduce via Template Parameter
* Injection Tools

Your first reaction to test doubles may be that using them will change your approach to design. however your code will look better, because you will seek cohesive, decoupled designs as you practice TDD. Test doubles are like any tool; the bigger challenge is not in learning how to use them but in knowing when to use them. At some point, you or someone else will implement the collaborator. You have a choice: remove the mocks so that the code under test uses the production collaborator or keep the mocks in place. therefore use Test Doubles Wisely.