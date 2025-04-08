# Chapter 6: Incremental Design

The primary reason to practice TDD is to support the ability to add or change features at a sustained, stable maintenance cost.​ Without TDD, you don’t have the rapid feedback to allow you to safely and easily make incremental code changes. Without making incremental code changes, your codebase will steadily degrade. learn what sorts of things you want to do when in the refactoring step.

Simple Design

consider following three simple rules when practicing TDD.

* Ensure your code is always highly readable and expressive.
* Eliminate all duplication, as long as doing so doesn’t interfere with the first rule.
* Ensure that you don’t introduce unnecessary complexity into your system. Avoid speculative constructs (“I just know we’re gonna have to support many-to-many someday”) and abstractions that don’t add to your system’s expressiveness.

Duplication is perhaps the biggest cost in maintaining a codebase over time. Algorithmic duplication (an indirect duplication) which produce different ways of solving the same problem, or pieces of a problem becomes a significant problem as your system grows.You have the potential to stave off this systematic degradation by incrementally refactoring as part of the TDD cycle. 

We’ve been taking an incremental approach with very small steps. Does it cost us? It often requires introducing small bits of code that we later remove—tiny bits of waste product. In return, we get the ability to make continual forward progress on creating well-designed, correct code incorporate them as a similar series of small steps. The more we keep our code clean, the easier it is to make our changes. It also helps to refactor to make sure design is a SRP-compliant design. 

 Where Is the Up-Front Design?

 the Agile principles suggest that the software must be valuable to the customer, that it can accommodate changing requirements at any time, that it works, that it has a good design, and that it is no more complex than need be. The challenge with Agile is that you are expected to respond to change. therefore extensive up-front design does no good. sketch an initial design, given what you know about what the system must do. But it’s not worthwhile to expend substantial effort in detailing the initial design. TDD is a means of addressing design on a continual basis. An up-front design is a good starting road map. but don’t sweat the low-level details:  These will come out in the test-driving. 

 know about coupling, cohesion, single responsibility principle and the other SOLID design principles, dependency structures, code smells, law of Demeter, patterns, encapsulation, composition vs. inheritance. When you’re in the refactoring step of TDD, you want to have all the knowledge you possibly can about what constitutes a good design. Most of the time, the classic design concepts are in alignment with the notion of simple design. however there are a few places where classic design clash with modern, incremental design ideas. Accessibility (private vs public) and Timeliness (better to learn how to continually accommodate changes via simple, incremental design). 

 Refactoring Inhibitors

 With the notion of using simple, incremental design as your primary design driver, the refactoring step is where much of the real work gets done. Anything that keeps you from refactoring easily, or even from wanting to refactor, is bad.
 Be on guard for the following inhibitors to refactoring:
 * Insufficient tests​ - when you have fewer fast unit tests and thus lower test coverage, your interest and ability to refactor shrinks dramatically
 * Long-lived branches​ - If you must sustain branches over long periods of time, seek to continually integrate from mainline. Otherwise, avoid long-lived branches.
 * ​Implementation-specific tests​ - refactoring is changing design without changing externally recognized (public) behavior.
 * Crushing technical debt​ - sheer volume of difficult code may be enough to cause many developers to give up.
 * ​No know-how - If you don’t have a solid grounding in good design, odds are you won’t refactor enough.
 * Short-sighted infatuation with speed​ - “Just ship it. Stop spending time on refactoring.”

 Everything you learn about good design will help you succeed with growing your system.