#include <gtest/gtest.h>
#include "../src/app/app.h"
#include "../src/command/command.h"
#include <sstream>
#include <iostream>
#include <filesystem>
#include <fstream>

namespace {
  class MockRunner {
  public:
    static inline std::vector<std::string> calledCommands;

    static void Execute(const Command* command) {
      if (command && command->exec.has_value()) {
        calledCommands.push_back(*command->exec);
      }
    }

    static void Reset() {
      calledCommands.clear();
    }
  };

  class StreamRedirect {
    std::streambuf* oldOut;
    std::streambuf* oldErr;
  public:
    std::ostringstream outBuffer, errBuffer;
    StreamRedirect() {
      oldOut = std::cout.rdbuf(outBuffer.rdbuf());
      oldErr = std::cerr.rdbuf(errBuffer.rdbuf());
    }
    ~StreamRedirect() {
      std::cout.rdbuf(oldOut);
      std::cerr.rdbuf(oldErr);
    }
  };

  TEST(AppTest, ReturnsErrorOnNoArgsAndLogsUsage) {
    MockRunner::Reset();
    StreamRedirect redirect;

    int result = app::run_nyd({}, "testdata/commands.yaml");
    std::cerr << std::flush;

    EXPECT_EQ(result, 1);
    EXPECT_NE(redirect.errBuffer.str().find("Usage:"), std::string::npos);
  }

  TEST(AppTest, ReturnsErrorOnUnmatchedCommandAndLogsError) {
    std::filesystem::create_directories("testdata");
    std::ofstream out("testdata/commands.yaml");
    out << R"(
commands:
  - name: Valid Command
    argument: validcommand
    exec: echo "valid top-level command"
    commands:
      - name: Sub
        argument: subcommand
        exec: echo "valid subcommand"
)";
    out.close();

    MockRunner::Reset();
    StreamRedirect redirect;

    int result = app::run_nyd({"bad"}, "testdata/commands.yaml");
    std::cerr << std::flush;

    EXPECT_EQ(result, 1);
    EXPECT_NE(redirect.errBuffer.str().find("Exiting, no command input match"), std::string::npos);
    EXPECT_TRUE(MockRunner::calledCommands.empty()) << "Command was unexpectedly executed";
  }

  TEST(AppTest, MatchesCommandAndLogsExecutionFlow) {
    std::filesystem::create_directories("testdata");
    std::ofstream out("testdata/commands.yaml");
    out << R"(
commands:
  - name: Valid Command
    argument: validcommand
    exec: echo "valid top-level command"
    commands:
      - name: Sub
        argument: subcommand
        exec: echo "valid subcommand"
)";
    out.close();

    MockRunner::Reset();
    StreamRedirect redirect;

    int result = app::run_nyd({"validcommand", "subcommand"}, "testdata/commands.yaml");

    EXPECT_EQ(result, 0);
    std::string output = redirect.outBuffer.str();
    EXPECT_NE(output.find("spawned"), std::string::npos);
  }
}

namespace runner {
  void executeCommand(const Command* command) {
    if (!command) return; // prevent segfault
    MockRunner::Execute(command);
  }
}
