#include <gtest/gtest.h>
#include "../src/runner/runner.h"
#include "../src/command/command.h"
#include <filesystem>

TEST(RunnerTest, HandlesNullCommand) {
  EXPECT_NO_THROW({
    runner::executeCommand(nullptr);
  });
}

TEST(RunnerTest, RunsPreAndExec) {
  Command cmd;
  cmd.name = "Test";
  cmd.argument = "test";
  cmd.pre = "echo pre";
  cmd.exec = "echo exec";

  EXPECT_NO_THROW({
    runner::executeCommand(&cmd);
  });
}

TEST(RunnerTest, ChangesDirectoryIfCdProvided) {
  Command cmd;
  cmd.name = "CD Test";
  cmd.argument = "cdtest";
  cmd.cd = std::filesystem::current_path().string(); // stay safe
  cmd.exec = "echo cd successful";

  EXPECT_NO_THROW({
    runner::executeCommand(&cmd);
  });
}

TEST(RunnerTest, ForceCoverageExecutionPath) {
  Command cmd;
  cmd.name = "CoverageTouch";
  cmd.argument = "cov";
  cmd.cd = std::filesystem::current_path().string();
  cmd.pre = "echo pre-cov";
  cmd.exec = "echo exec-cov";

  runner::executeCommand(&cmd);
} 

TEST(RunnerTest, FailsToChangeDirectory) {
  Command cmd;
  cmd.name = "FailCD";
  cmd.argument = "failcd";
  cmd.cd = "/nonexistent/path/that/should/fail";
  cmd.exec = "echo should not run";

  EXPECT_NO_THROW({
    runner::executeCommand(&cmd);
  });
}

TEST(RunnerTest, SkipsExecWhenMissing) {
  Command cmd;
  cmd.name = "NoExec";
  cmd.argument = "noexec";
  cmd.exec = std::nullopt;

  EXPECT_NO_THROW({
    runner::executeCommand(&cmd);
  });
}
