#include <gtest/gtest.h>
#include "../src/command/command.h"

TEST(CommandTest, MatchesTopLevelCommand) {
  std::vector<Command> commands = {
    {.name = "Alpha", .argument = "a", .exec = "run alpha"}
  };

  std::vector<std::string> args = {"a"};
  const Command* result = resolveCommand(commands, args);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->name, "Alpha");
}

TEST(CommandTest, MatchesNestedSubcommand) {
  Command sub = {.name = "Beta", .argument = "b", .exec = "run beta"};
  Command parent = {.name = "Alpha", .argument = "a", .exec = "run alpha", .subcommands = std::vector<Command>{sub}};
  std::vector<Command> commands = {parent};

  std::vector<std::string> args = {"a", "b"};
  const Command* result = resolveCommand(commands, args);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->name, "Beta");
}

TEST(CommandTest, ReturnsNullOnNoMatch) {
  std::vector<Command> commands = {
    {.name = "Alpha", .argument = "a", .exec = "run alpha"}
  };

  std::vector<std::string> args = {"nonexistent"};
  const Command* result = resolveCommand(commands, args);

  EXPECT_EQ(result, nullptr);
}

TEST(CommandTest, ReturnsNullOnSubcommandMismatch) {
  Command parent = {.name = "Alpha", .argument = "a", .exec = "run alpha", .subcommands = std::vector<Command>{}};
  std::vector<Command> commands = {parent};

  std::vector<std::string> args = {"a", "nope"};
  const Command* result = resolveCommand(commands, args);

  EXPECT_EQ(result, nullptr);
}