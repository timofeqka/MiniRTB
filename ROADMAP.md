# MiniRTB Learning + Implementation Plan

## Phase 0 — Project Setup Mindset
- [ ] Create a folder named `MiniRTB`
- [ ] Create a file `todo.md`
- [ ] Decide that this project is both:
  - [ ] a C++ learning project
  - [ ] a microservices learning project
  - [ ] a networking learning project
  - [ ] a system design learning project
- [ ] Accept that the goal is not “write everything fast”
- [ ] Accept that the real goal is “understand every layer step by step”
- [ ] Keep a notebook or markdown file for concepts you do not understand yet
- [ ] Create a `notes/` folder for personal study notes
- [ ] Create separate note files:
  - [ ] `notes/cpp_basics.md`
  - [ ] `notes/oop.md`
  - [ ] `notes/memory.md`
  - [ ] `notes/concurrency.md`
  - [ ] `notes/networking.md`
  - [ ] `notes/cmake.md`
  - [ ] `notes/testing.md`
  - [ ] `notes/system_design.md`
  - [ ] `notes/rtb.md`

---

# Phase 1 — Understand the Big Picture First
- [ ] Read what RTB (Real-Time Bidding) is
- [ ] Understand the business goal of RTB
- [ ] Understand why latency matters in RTB
- [ ] Understand why 50–100 ms is a strict deadline
- [ ] Understand the role of the `Bidder`
- [ ] Understand the role of the `Profile Service`
- [ ] Understand the role of the `Budget Tracker`
- [ ] Understand what a microservice is
- [ ] Understand why systems are split into multiple services
- [ ] Understand service-to-service communication
- [ ] Understand request/response flow between services
- [ ] Draw a very simple system diagram by hand
- [ ] Be able to explain in your own words:
  - [ ] what request comes into the system
  - [ ] what data must be read
  - [ ] what decision must be made
  - [ ] what response must be returned
- [ ] Write a one-page summary of how MiniRTB should work

### Deliverables
- [ ] `notes/rtb.md` contains a beginner explanation of RTB
- [ ] `docs/architecture/system_overview.md` has a simple system flow
- [ ] You can explain the full pipeline without looking at notes

---

# Phase 2 — C++ Foundations Before Writing Real Project Code
## Core syntax and language basics
- [ ] Learn variables and basic types
- [ ] Learn references
- [ ] Learn pointers
- [ ] Learn `const`
- [ ] Learn stack vs heap
- [ ] Learn functions
- [ ] Learn function overloading
- [ ] Learn namespaces
- [ ] Learn header/source file separation
- [ ] Learn compilation model in C++

## OOP basics
- [ ] Learn classes
- [ ] Learn structs
- [ ] Learn constructors
- [ ] Learn destructors
- [ ] Learn member functions
- [ ] Learn access modifiers
- [ ] Learn composition
- [ ] Learn inheritance
- [ ] Learn virtual functions
- [ ] Learn interfaces through abstract classes

## Modern C++
- [ ] Learn `std::string`
- [ ] Learn `std::vector`
- [ ] Learn `std::unordered_map`
- [ ] Learn `std::optional`
- [ ] Learn `std::variant` at a basic level
- [ ] Learn enums and enum classes
- [ ] Learn RAII
- [ ] Learn smart pointers:
  - [ ] `std::unique_ptr`
  - [ ] `std::shared_ptr`
  - [ ] when not to use smart pointers
- [ ] Learn move semantics conceptually
- [ ] Learn `= delete`
- [ ] Learn `= default`

## Error handling
- [ ] Learn exceptions
- [ ] Learn when to avoid exceptions in low-latency code
- [ ] Learn error code style design
- [ ] Learn status/result object patterns

### Practice tasks
- [ ] Write a small `UserProfile` class
- [ ] Write a small `Campaign` class
- [ ] Write a `Money` type
- [ ] Write an `Ad` class
- [ ] Separate headers and sources correctly
- [ ] Compile everything manually once
- [ ] Compile everything with CMake once

### Deliverables
- [ ] `notes/cpp_basics.md`
- [ ] `notes/oop.md`
- [ ] `notes/memory.md`
- [ ] small practice files compile successfully

---

# Phase 3 — Learn CMake Before Scaling the Project
- [ ] Understand what CMake is
- [ ] Understand what `CMakeLists.txt` does
- [ ] Learn how to define an executable
- [ ] Learn how to define a library
- [ ] Learn include directories
- [ ] Learn target linking
- [ ] Learn compile features
- [ ] Learn compile options
- [ ] Learn presets at a basic level
- [ ] Learn out-of-source builds
- [ ] Learn Debug vs Release builds

### Practice tasks
- [ ] Create a tiny hello-world CMake project
- [ ] Split it into `src/` and `include/`
- [ ] Add one static library
- [ ] Link the library into an executable
- [ ] Add one test target
- [ ] Build project in Debug
- [ ] Build project in Release

### Deliverables
- [ ] `notes/cmake.md`
- [ ] working minimal CMake project before touching MiniRTB main structure

---

# Phase 4 — Learn Basic Networking Theory
- [ ] Learn what a client is
- [ ] Learn what a server is
- [ ] Learn what TCP is
- [ ] Learn what HTTP is
- [ ] Learn difference between TCP and HTTP
- [ ] Learn what sockets are
- [ ] Learn IP address basics
- [ ] Learn port basics
- [ ] Learn connection lifecycle
- [ ] Learn request/response messaging
- [ ] Learn framing problem in TCP
- [ ] Learn why TCP is a byte stream, not a message queue
- [ ] Learn what serialization means
- [ ] Learn JSON serialization basics
- [ ] Learn binary protocol basics
- [ ] Learn timeout basics
- [ ] Learn reconnect basics
- [ ] Learn why partial reads/writes happen

### Practice tasks
- [ ] Write a tiny TCP echo server
- [ ] Write a tiny TCP echo client
- [ ] Send a string from client to server
- [ ] Return the same string back
- [ ] Add simple message delimiter such as newline
- [ ] Observe how reading from socket works
- [ ] Add logging for every connection

### Deliverables
- [ ] `notes/networking.md`
- [ ] a tiny standalone server/client example
- [ ] you understand why `message_framing.hpp` will be needed later

---

# Phase 5 — Learn Concurrency and Multithreading Basics
- [ ] Learn what a thread is
- [ ] Learn why servers use multiple threads
- [ ] Learn race condition concept
- [ ] Learn mutex basics
- [ ] Learn lock guard basics
- [ ] Learn condition variable basics
- [ ] Learn blocking queue concept
- [ ] Learn thread pool concept
- [ ] Learn atomic basics
- [ ] Learn memory ordering at a beginner level
- [ ] Learn spinlock concept
- [ ] Learn why spinlocks can be dangerous
- [ ] Learn contention concept
- [ ] Learn producer/consumer pattern
- [ ] Learn read-heavy vs write-heavy workloads

### Practice tasks
- [ ] Write a counter with multiple threads
- [ ] Break it intentionally with no synchronization
- [ ] Fix it with `std::mutex`
- [ ] Write a blocking queue
- [ ] Write a small thread pool
- [ ] Submit tasks into the pool
- [ ] Measure basic timing

### Deliverables
- [ ] `notes/concurrency.md`
- [ ] working `blocking_queue` practice
- [ ] working `thread_pool` practice

---

# Phase 6 — Learn Testing Early
- [ ] Learn what unit tests are
- [ ] Learn what integration tests are
- [ ] Learn what end-to-end tests are
- [ ] Learn what a fixture is
- [ ] Learn why tests matter in systems code
- [ ] Learn GoogleTest basics
- [ ] Learn assertions
- [ ] Learn test naming style
- [ ] Learn test isolation
- [ ] Learn deterministic testing basics

### Practice tasks
- [ ] Add GoogleTest to a small project
- [ ] Test `Money`
- [ ] Test `Campaign`
- [ ] Test `UserProfile`
- [ ] Test a small hash table operation
- [ ] Test serialization roundtrip

### Deliverables
- [ ] `notes/testing.md`
- [ ] minimal test target runs successfully

---

# Phase 7 — Learn Performance and Low-Latency Thinking
- [ ] Understand latency vs throughput
- [ ] Understand p50 / p95 / p99
- [ ] Understand why averages can be misleading
- [ ] Understand heap allocation cost
- [ ] Understand cache locality at a high level
- [ ] Understand why copying large objects is expensive
- [ ] Understand lock contention cost
- [ ] Understand why logging can hurt performance
- [ ] Understand warmup vs cold start
- [ ] Understand microbenchmark limitations
- [ ] Understand realistic benchmark limitations

### Practice tasks
- [ ] Benchmark vector vs list for simple access
- [ ] Benchmark mutex-protected queue
- [ ] Benchmark serialization of small objects
- [ ] Measure how long hash lookups take
- [ ] Write down observations

### Deliverables
- [ ] `notes/performance.md` or add section into `notes/system_design.md`

---

# Phase 8 — Define the MVP Very Clearly
- [ ] Write down the absolute MVP scope
- [ ] Confirm the system has exactly 3 services:
  - [ ] Bidder
  - [ ] Profile Service
  - [ ] Budget Tracker
- [ ] Decide communication style for MVP:
  - [ ] TCP custom protocol or
  - [ ] simple HTTP-like protocol
- [ ] Choose one format for MVP:
  - [ ] JSON first for simplicity
- [ ] Decide what can stay in memory only
- [ ] Decide what can be fake/mock for MVP
- [ ] Decide what does not need to be production-grade yet

### MVP requirements
- [ ] Bid request enters Bidder
- [ ] Bidder asks Profile Service for user profile
- [ ] Bidder selects a matching campaign
- [ ] Bidder asks Budget Tracker to reserve money
- [ ] If budget succeeds, return winning ad
- [ ] If budget fails, return no-bid
- [ ] Record simple metrics
- [ ] Support simple load test

### Deliverables
- [ ] `README.md` contains MVP scope
- [ ] `docs/architecture/system_overview.md` contains exact request flow
- [ ] every future coding decision is checked against MVP scope

---

# Phase 9 — Create the Real Project Skeleton
- [ ] Create root project structure
- [ ] Create `src/`
- [ ] Create `tests/`
- [ ] Create `benchmarks/`
- [ ] Create `docs/`
- [ ] Create `configs/`
- [ ] Create `data/`
- [ ] Create `scripts/`
- [ ] Create `tools/`
- [ ] Create `third_party/`
- [ ] Create `cmake/`

### Build system
- [ ] Create root `CMakeLists.txt`
- [ ] Add subdirectories gradually
- [ ] Make the empty project configure successfully
- [ ] Make the empty project build successfully

### Deliverables
- [ ] empty structure exists
- [ ] project configures with CMake
- [ ] project builds without source logic yet

---

# Phase 10 — Design the Domain Layer First
## Theory
- [ ] Understand what domain model means
- [ ] Understand that domain objects should represent business concepts
- [ ] Keep domain independent from transport layer as much as possible

## Implement domain classes
- [ ] Implement `UserProfile`
- [ ] Implement `Campaign`
- [ ] Implement `Ad`
- [ ] Implement `Money`
- [ ] Implement `Targeting`

## Decide fields for each domain object
- [ ] `UserProfile` fields defined
- [ ] `Campaign` fields defined
- [ ] `Ad` fields defined
- [ ] `Money` rules defined
- [ ] `Targeting` rules defined

## Write tests first or immediately after implementation
- [ ] Test `Money`
- [ ] Test `Targeting`
- [ ] Test `Campaign`

### Deliverables
- [ ] `src/domain/include/minirtb/domain/...`
- [ ] `src/domain/src/...`
- [ ] `tests/unit/domain/...`

---

# Phase 11 — Build the Common Layer
## Core types
- [ ] Implement `types.hpp`
- [ ] Implement `status.hpp`
- [ ] Implement `error.hpp`
- [ ] Implement `ids.hpp`

## Utils
- [ ] Implement `timer.hpp`
- [ ] Implement config loader interface
- [ ] Implement logger interface
- [ ] Implement basic serialization utilities

## Metrics
- [ ] Implement counter
- [ ] Implement histogram
- [ ] Implement metrics registry

### Theory while doing this
- [ ] Learn reusable library design
- [ ] Learn why common code must stay generic
- [ ] Learn why common code should avoid business-specific logic

### Deliverables
- [ ] common library compiles separately
- [ ] common tests pass where needed

---

# Phase 12 — Implement Serialization and Protocol Objects
## Theory
- [ ] Understand DTO vs domain object
- [ ] Understand transport message design
- [ ] Understand request/response versioning basics

## Implement protocol models
- [ ] `bid_request.hpp`
- [ ] `bid_response.hpp`
- [ ] `profile_messages.hpp`
- [ ] `budget_messages.hpp`

## Implement serialization
- [ ] JSON encode request
- [ ] JSON decode request
- [ ] JSON encode response
- [ ] JSON decode response
- [ ] Add validation for missing fields
- [ ] Add tests for malformed messages
- [ ] Add roundtrip tests

### Deliverables
- [ ] Bid request can be serialized/deserialized
- [ ] Bid response can be serialized/deserialized
- [ ] Profile and budget messages work correctly

---

# Phase 13 — Implement Basic Networking Layer
## Implement network abstractions
- [ ] `endpoint.hpp`
- [ ] `message_framing.hpp`
- [ ] `tcp_server.hpp`
- [ ] `tcp_client.hpp`

## Implementation tasks
- [ ] Support accepting TCP connections
- [ ] Support reading full framed messages
- [ ] Support writing full framed messages
- [ ] Support handling client disconnects
- [ ] Support timeout handling
- [ ] Add error reporting
- [ ] Add basic logs

## Tests / demos
- [ ] Server and client exchange one message
- [ ] Send multiple messages on one connection
- [ ] Handle invalid message format
- [ ] Handle closed connection gracefully

### Deliverables
- [ ] working reusable network layer
- [ ] small demo proves it works before real services are built

---

# Phase 14 — Implement In-Memory Storage Primitives
## Theory
- [ ] Understand hash table basics
- [ ] Understand load factor concept
- [ ] Understand collision concept
- [ ] Understand open addressing vs chaining
- [ ] Understand object pool concept
- [ ] Understand ring buffer concept

## Practice choice
- [ ] Decide whether MVP uses STL first
- [ ] Decide whether custom hash table is now or later
- [ ] For learning, maybe implement simple custom hash table separately first

## Implement
- [ ] `hash_table.hpp`
- [ ] `object_pool.hpp`
- [ ] `ring_buffer.hpp`

## Tests
- [ ] hash insert/find/delete
- [ ] collision behavior
- [ ] pool acquire/release
- [ ] ring buffer push/pop

### Deliverables
- [ ] storage components tested
- [ ] decision made whether services use custom storage in MVP or later phase

---

# Phase 15 — Implement Profile Service First
## Why first
- [ ] It is the easiest service
- [ ] It teaches networking + storage without budget consistency yet
- [ ] It gives Bidder something real to call

## Theory
- [ ] Understand request handler design
- [ ] Understand in-memory read path
- [ ] Understand loading sample data from JSON

## Implement pieces
- [ ] `profile_repository.hpp`
- [ ] `profile_store.hpp`
- [ ] `profile_service.hpp`
- [ ] config loading
- [ ] profile loading from sample file
- [ ] lookup by user ID
- [ ] return profile response through TCP

## Service binary
- [ ] implement `main.cpp`
- [ ] read config
- [ ] start TCP server
- [ ] preload profiles
- [ ] handle shutdown cleanly

## Tests
- [ ] unit tests for store
- [ ] unit tests for repository
- [ ] integration test for network lookup

### Deliverables
- [ ] Profile Service runs independently
- [ ] client can request a profile and receive a valid response

---

# Phase 16 — Implement Budget Tracker Second
## Why second
- [ ] It introduces correctness and concurrency concerns
- [ ] It is simpler than full Bidder logic
- [ ] It is required before Bidder can finalize decisions

## Theory
- [ ] Understand reservation concept
- [ ] Understand atomicity concept
- [ ] Understand overspending problem
- [ ] Understand ledger concept
- [ ] Understand idempotency concept at a simple level

## Implement pieces
- [ ] `budget_store.hpp`
- [ ] `reservation_engine.hpp`
- [ ] `ledger.hpp`
- [ ] `budget_service.hpp`

## Rules to define
- [ ] how campaign budgets are stored
- [ ] how reservation request looks
- [ ] what happens if budget is insufficient
- [ ] whether reservation and debit are one step for MVP
- [ ] how responses communicate success/failure

## Service binary
- [ ] implement `main.cpp`
- [ ] load campaign budgets
- [ ] start server
- [ ] process reservation requests safely

## Tests
- [ ] single-thread successful reservation
- [ ] insufficient funds case
- [ ] concurrent reservation test
- [ ] no negative budget test

### Deliverables
- [ ] Budget Tracker runs independently
- [ ] reservation logic is safe for MVP

---

# Phase 17 — Implement Bidder Third
## Why third
- [ ] It depends on the other two services
- [ ] It combines business logic, networking, deadlines, and decision making

## Theory
- [ ] Understand orchestration service design
- [ ] Understand deadline-aware request handling
- [ ] Understand fallback/no-bid decisions
- [ ] Understand campaign scoring basics

## Implement pieces
- [ ] `campaign_selector.hpp`
- [ ] `scoring_engine.hpp`
- [ ] `deadline_budget.hpp`
- [ ] `bidder_service.hpp`

## Define bidder pipeline exactly
- [ ] receive bid request
- [ ] validate request
- [ ] fetch user profile from Profile Service
- [ ] load candidate campaigns
- [ ] check targeting match
- [ ] compute score
- [ ] choose best candidate
- [ ] ask Budget Tracker to reserve budget
- [ ] if budget success → return winning ad
- [ ] if budget fails → try fallback or return no-bid
- [ ] record latency and result metrics

## Service binary
- [ ] implement `main.cpp`
- [ ] load configs
- [ ] connect to other services
- [ ] listen for bid requests
- [ ] process end-to-end request flow

## Tests
- [ ] unit test scoring
- [ ] unit test campaign selection
- [ ] integration test with mocked dependencies
- [ ] full flow test with real services

### Deliverables
- [ ] Bidder runs and returns actual bid decisions

---

# Phase 18 — Add Config Files and Sample Data
- [ ] Define config structure for each service
- [ ] Create bidder config
- [ ] Create profile_service config
- [ ] Create budget_tracker config
- [ ] Create campaigns config
- [ ] Create sample profiles
- [ ] Create sample campaigns
- [ ] Create sample bid requests

## Validate configs
- [ ] Handle missing config file
- [ ] Handle invalid JSON
- [ ] Handle missing required fields
- [ ] Use reasonable defaults where appropriate

### Deliverables
- [ ] project can be launched entirely from config files

---

# Phase 19 — Add Logging and Metrics
## Logging
- [ ] Define log format
- [ ] Add startup logs
- [ ] Add shutdown logs
- [ ] Add request logs
- [ ] Add error logs
- [ ] Avoid excessive noisy logs in hot path

## Metrics
- [ ] total bid requests
- [ ] successful bids
- [ ] no-bids
- [ ] profile lookup latency
- [ ] budget reservation latency
- [ ] total bidder latency
- [ ] error counts

## Tests / validation
- [ ] verify metrics are updated
- [ ] verify logs are readable
- [ ] verify logging does not break flow

### Deliverables
- [ ] system exposes enough observability for debugging

---

# Phase 20 — End-to-End Integration
- [ ] Run Profile Service
- [ ] Run Budget Tracker
- [ ] Run Bidder
- [ ] Send one sample request manually
- [ ] Verify correct response
- [ ] Verify budget changes
- [ ] Verify logs
- [ ] Verify metrics
- [ ] Send invalid request
- [ ] Verify graceful error handling
- [ ] Send request for unknown profile
- [ ] Verify fallback behavior
- [ ] Send request when budget is exhausted
- [ ] Verify no-bid behavior

### Deliverables
- [ ] first true end-to-end MVP demo works

---

# Phase 21 — Testing Expansion
## Unit tests
- [ ] common layer tests
- [ ] domain layer tests
- [ ] service logic tests

## Integration tests
- [ ] bid flow test
- [ ] profile lookup test
- [ ] budget reservation test

## E2E tests
- [ ] full pipeline test
- [ ] timeout behavior test

## Negative tests
- [ ] malformed JSON
- [ ] missing profile
- [ ] empty campaigns
- [ ] no budget left
- [ ] service unavailable case

### Deliverables
- [ ] test suite gives confidence that the system is stable

---

# Phase 22 — Benchmarking
## Theory
- [ ] Understand what to benchmark
- [ ] Understand benchmark isolation
- [ ] Understand why synthetic benchmarks are limited

## Implement benchmarks
- [ ] hash table benchmark
- [ ] serializer benchmark
- [ ] thread pool benchmark
- [ ] profile lookup benchmark
- [ ] budget reservation benchmark
- [ ] bidder pipeline benchmark

## Record results
- [ ] collect latency numbers
- [ ] compare Debug vs Release
- [ ] identify obvious slow spots
- [ ] write simple report

### Deliverables
- [ ] `docs/benchmarks/results.md`
- [ ] `benchmarks/reports/...`

---

# Phase 23 — Refactoring Pass
- [ ] Remove duplicated code
- [ ] Rename unclear classes/functions
- [ ] Simplify overly complicated code
- [ ] Split large source files
- [ ] Improve header hygiene
- [ ] Reduce unnecessary includes
- [ ] Improve const-correctness
- [ ] Reduce unnecessary copying
- [ ] review ownership rules
- [ ] review threading rules

### Deliverables
- [ ] code becomes cleaner after first working version exists

---

# Phase 24 — Documentation Pass
- [ ] Write project overview in `README.md`
- [ ] Write how to build
- [ ] Write how to run each service
- [ ] Write how to run tests
- [ ] Write how to run benchmarks
- [ ] Write config explanation
- [ ] Write protocol explanation
- [ ] Write architecture explanation
- [ ] Add diagrams
- [ ] Add limitations of current MVP
- [ ] Add future improvements

### Deliverables
- [ ] another student can clone and run the project

---

# Phase 25 — Optional Advanced Improvements After MVP
- [ ] Replace JSON with binary protocol
- [ ] Add async I/O improvements
- [ ] Add better connection pooling
- [ ] Add retry logic carefully
- [ ] Add campaign caching strategy
- [ ] Add profile cache optimization
- [ ] Add idempotency keys for reservations
- [ ] Add better deadline propagation
- [ ] Add admin endpoints
- [ ] Add metrics export format
- [ ] Add Docker support
- [ ] Add fault injection tests
- [ ] Add more realistic load testing
- [ ] Add campaign pacing logic
- [ ] Add budget refill logic
- [ ] Add sharding ideas for profiles
- [ ] Add persistence layer later if desired

---

# Weekly Study Routine Checklist
## Every week
- [ ] Read theory before coding
- [ ] Write small isolated practice code before real project code
- [ ] Implement one small piece only
- [ ] Test that piece
- [ ] Write notes for what you learned
- [ ] Write questions for what is still unclear
- [ ] Refactor only after code works
- [ ] Commit to git with meaningful message

## For every new concept
- [ ] Define it in simple words
- [ ] Explain why it exists
- [ ] Write a tiny example
- [ ] Break it intentionally if possible
- [ ] Fix it
- [ ] Connect it back to MiniRTB

---

# Rule: For Every File You Implement
- [ ] I know why this file exists
- [ ] I know who uses this file
- [ ] I know what problem it solves
- [ ] I know how to test it
- [ ] I know whether it belongs to domain/common/service/tool/tests

---

# Final Success Criteria
- [ ] Project builds successfully
- [ ] All 3 services run
- [ ] One request completes end-to-end
- [ ] Profile lookup works
- [ ] Budget reservation works
- [ ] Bid selection works
- [ ] Tests pass
- [ ] Benchmarks run
- [ ] Docs explain the project clearly
- [ ] I can explain the architecture without looking at the code
- [ ] I can explain each service responsibility
- [ ] I can explain the request flow step by step
- [ ] I can explain the main C++ concepts used in the project
