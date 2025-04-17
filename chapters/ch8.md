# Chapter 8: Legacy Challenges

most of the time you’re slogging through vast amounts of existing code that was not built using TDD —​ legacy code. Working on a legacy codebase demands a choice. Are you willing to let the cost of maintenance steadily increase, or are you willing to start fixing the problem? learn a handful of specific techniques, each tailored to the specific legacy challenge at hand.

Tests still come first in your approach to legacy code. You really only need tests around code you will change, a baseline that tells you when you’ve broken existing behavior. You do not need to test code leading up to that area of change. to Safe Refactoring to Support Testing, Method extract is the simplest approach we have. Third-party libraries can create no end of headaches for testing. One possible solution is to dummy-out a third-party library via​ linker substitution​. it sounds a lot harder than it is, but it’s a fairly quick process to set up.
* start by commenting out the line in the makefile that links library into the test executable. 
* supply stubs for each of those attempts to hook into library.
* add a makefile that builds new stub library.
* update test build to incorporate the stub library

do not stick to one dependency-breaking technique, familiarize yourself with all of them so that you can choose the most appropriate to your situation. From time to time, you’ll need to make a large-scale sweeping changes to the codebase. The Mikado Method, provides a disciplined approach. The complete process follows an initially daunting nine-step cycle. With the Mikado Method, you separate the refactor analysis from time spent applying code changes based on that analysis. Where the Mikado Method really shines is with a larger refactoring that might take several days or more to accomplish.

at the end of the day, Your team must make a choice: either dispense with legacy system salvaging techniques and let the codebase continue to degrade (it will) or put a stake in the ground and decide to change direction for the better. You don’t need to test everything, just the stuff you need to change!
