#include <gtest/gtest.h>
#include "../src/loader/loader.h"
#include <yaml-cpp/yaml.h>
#include <filesystem>
#include <fstream>

TEST(LoaderTest, ParsesSimpleCommand) {
  YAML::Node node = YAML::Load(R"(
    name: Test Command
    argument: test
    exec: echo 'hello'
  )");

  Command cmd = parseCommandNode(node);

  EXPECT_EQ(cmd.name, "Test Command");
  EXPECT_EQ(cmd.argument, "test");
  ASSERT_TRUE(cmd.exec.has_value());
  EXPECT_EQ(cmd.exec.value(), "echo 'hello'");
}

TEST(LoaderTest, ParsesCommandWithSubcommands) {
  YAML::Node node = YAML::Load(R"(
    name: Parent
    argument: p
    commands:
      - name: Child
        argument: c
        exec: echo 'child'
  )");

  Command cmd = parseCommandNode(node);
  ASSERT_TRUE(cmd.subcommands.has_value());
  ASSERT_EQ(cmd.subcommands->size(), 1);
  EXPECT_EQ(cmd.subcommands->at(0).name, "Child");
  EXPECT_EQ(cmd.subcommands->at(0).exec.value(), "echo 'child'");
}

// Optional: requires a real YAML file placed in testdata/loader.yaml
TEST(LoaderTest, LoadsCommandTreeFromFile) {
  std::filesystem::create_directories("testdata");
  std::ofstream out("testdata/loader.yaml");
  out << R"(
commands:
  - name: FileCmd
    argument: f
    exec: echo 'file'
)";
  out.close();

  auto commands = loadCommandTree("testdata/loader.yaml");

  ASSERT_EQ(commands.size(), 1);
  EXPECT_EQ(commands[0].name, "FileCmd");
  EXPECT_EQ(commands[0].exec.value(), "echo 'file'");
}
// Error handling tests for malformed YAML
TEST(LoaderTest, ThrowsOnMissingRequiredNameField) {
  YAML::Node node = YAML::Load(R"(
    argument: test
    exec: echo 'oops'
  )");
  EXPECT_THROW({
    parseCommandNode(node);
  }, std::exception);
}

TEST(LoaderTest, ThrowsOnIncorrectCommandsType) {
  YAML::Node node = YAML::Load(R"(
    name: Root
    argument: r
    commands: not_a_list
  )");
  EXPECT_THROW({
    parseCommandNode(node);
  }, std::exception);
}

TEST(LoaderTest, ThrowsOnInvalidYamlSyntaxInFile) {
  // Write invalid YAML to a file
  std::ofstream out("testdata/invalid.yaml");
  out << R"(
commands:
  - name: Bad
    argument: x
    exec: echo 'bad'
  - name: MissingIndent
  argument: y
    exec: echo 'bad2'
)";
  out.close();
  EXPECT_THROW({
    loadCommandTree("testdata/invalid.yaml");
  }, std::exception);
}
