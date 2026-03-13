# MiniRTB TODO

## Root
- [ ] CMakeLists.txt
- [ ] CMakePresets.json
- [ ] README.md
- [ ] .gitignore
- [ ] .clang-format
- [ ] .clang-tidy
- [ ] LICENSE

---

## cmake
- [ ] cmake/CompilerWarnings.cmake
- [ ] cmake/Sanitizers.cmake
- [ ] cmake/StaticAnalyzers.cmake
- [ ] cmake/Options.cmake
- [ ] cmake/Dependencies.cmake

---

## third_party
- [ ] third_party/README.md
- [ ] third_party/googletest
- [ ] third_party/benchmark
- [ ] third_party/nlohmann_json
- [ ] third_party/spdlog
- [ ] third_party/asio

---

## external
- [ ] external/install

---

## docs

### architecture
- [ ] docs/architecture/system_overview.md
- [ ] docs/architecture/bidder.md
- [ ] docs/architecture/profile_service.md
- [ ] docs/architecture/budget_tracker.md

### protocols
- [ ] docs/protocols/request_response.md
- [ ] docs/protocols/binary_protocol.md

### benchmarks
- [ ] docs/benchmarks/results.md

### diagrams
- [ ] docs/diagrams/architecture.png
- [ ] docs/diagrams/sequence_bid_flow.png

---

## configs

### bidder
- [ ] configs/bidder/config.json

### profile_service
- [ ] configs/profile_service/config.json

### budget_tracker
- [ ] configs/budget_tracker/config.json

### campaigns
- [ ] configs/campaigns/campaigns.json

---

## data

### profiles
- [ ] data/profiles/sample_profiles.json

### campaigns
- [ ] data/campaigns/sample_campaigns.json

### requests
- [ ] data/requests/sample_bid_requests.json

### logs
- [ ] data/logs

---

## scripts
- [ ] scripts/build.sh
- [ ] scripts/build.ps1
- [ ] scripts/run_all.sh
- [ ] scripts/run_all.ps1
- [ ] scripts/benchmark.sh
- [ ] scripts/benchmark.ps1
- [ ] scripts/format.sh

---

# Tools

### request_generator
- [ ] tools/request_generator/CMakeLists.txt
- [ ] tools/request_generator/src/main.cpp

### load_tester
- [ ] tools/load_tester/CMakeLists.txt
- [ ] tools/load_tester/src/main.cpp

### profile_loader
- [ ] tools/profile_loader/CMakeLists.txt
- [ ] tools/profile_loader/src/main.cpp

---

# src

## common

### core
- [ ] types.hpp
- [ ] status.hpp
- [ ] error.hpp
- [ ] ids.hpp

### net
- [ ] tcp_server.hpp
- [ ] tcp_client.hpp
- [ ] endpoint.hpp
- [ ] message_framing.hpp

### protocol
- [ ] bid_request.hpp
- [ ] bid_response.hpp
- [ ] profile_messages.hpp
- [ ] budget_messages.hpp

### storage
- [ ] hash_table.hpp
- [ ] object_pool.hpp
- [ ] ring_buffer.hpp

### concurrency
- [ ] thread_pool.hpp
- [ ] blocking_queue.hpp
- [ ] spinlock.hpp

### utils
- [ ] timer.hpp
- [ ] config.hpp
- [ ] logger.hpp
- [ ] serialization.hpp

### metrics
- [ ] histogram.hpp
- [ ] counter.hpp
- [ ] metrics_registry.hpp

### src
- [ ] tcp_server.cpp
- [ ] tcp_client.cpp
- [ ] logger.cpp
- [ ] config.cpp
- [ ] serialization.cpp

---

# services

## bidder
- [ ] bidder_service.hpp
- [ ] campaign_selector.hpp
- [ ] scoring_engine.hpp
- [ ] deadline_budget.hpp

### src
- [ ] bidder_service.cpp
- [ ] campaign_selector.cpp
- [ ] scoring_engine.cpp
- [ ] main.cpp

### tests
- [ ] bidder_unit.cpp

---

## profile_service
- [ ] profile_service.hpp
- [ ] profile_store.hpp
- [ ] profile_repository.hpp

### src
- [ ] profile_service.cpp
- [ ] profile_store.cpp
- [ ] profile_repository.cpp
- [ ] main.cpp

### tests
- [ ] profile_service_unit.cpp

---

## budget_tracker
- [ ] budget_service.hpp
- [ ] budget_store.hpp
- [ ] reservation_engine.hpp
- [ ] ledger.hpp

### src
- [ ] budget_service.cpp
- [ ] budget_store.cpp
- [ ] reservation_engine.cpp
- [ ] ledger.cpp
- [ ] main.cpp

### tests
- [ ] budget_tracker_unit.cpp

---

# domain

### headers
- [ ] user_profile.hpp
- [ ] campaign.hpp
- [ ] ad.hpp
- [ ] money.hpp
- [ ] targeting.hpp

### src
- [ ] campaign.cpp
- [ ] targeting.cpp

---

# tests

## unit

### common
- [ ] hash_table_test.cpp
- [ ] thread_pool_test.cpp
- [ ] serialization_test.cpp

### domain
- [ ] campaign_test.cpp
- [ ] targeting_test.cpp

### services
- [ ] bidder_test.cpp
- [ ] profile_service_test.cpp
- [ ] budget_tracker_test.cpp

---

## integration
- [ ] bid_flow_test.cpp
- [ ] profile_lookup_test.cpp
- [ ] budget_reservation_test.cpp

---

## e2e
- [ ] full_pipeline_test.cpp
- [ ] timeout_behavior_test.cpp

---

## fixtures
- [ ] profiles_fixture.json
- [ ] campaigns_fixture.json
- [ ] requests_fixture.json

---

# benchmarks

## common
- [ ] hash_table_bench.cpp
- [ ] serializer_bench.cpp
- [ ] thread_pool_bench.cpp

## services
- [ ] profile_lookup_bench.cpp
- [ ] budget_reservation_bench.cpp
- [ ] bidder_pipeline_bench.cpp

## reports
- [ ] reports/.gitkeep

---

# build
- [ ] build/