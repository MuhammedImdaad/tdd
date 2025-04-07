# Chapter 5: Test Doubles
objects must work with other objects. such can cause pesky challenges for test-driving. they can be slow, unstable, or not even around to help you yet. first learn how to break such dependencies using handcrafted test doubles. then see how you might simplify the creation of test doubles by using a tool. 

Why do these dependency concerns create testing challenges
* a dependency on slow collaborators results in undesirably slow tests.
* a dependency on a volatile service (either unavailable or returning different answers each time) results in intermittently failing tests.