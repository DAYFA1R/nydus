#include <gtest/gtest.h>
#include "../src/utils/path.h"
#include <cstdlib>
#include <filesystem>

namespace {
  TEST(UtilsTest, ExpandTildeResolvesHome) {
    std::string fakeHome = "/tmp/fakehome";
    setenv("HOME", fakeHome.c_str(), 1);
  
    auto result = utils::expandTilde("~/projects");
    EXPECT_EQ(result, std::filesystem::path("/tmp/fakehome/projects"));
  }
  
  TEST(UtilsTest, NoTildeReturnsOriginalPath) {
    std::string path = "/absolute/path";
    auto result = utils::expandTilde(path);
    EXPECT_EQ(result, std::filesystem::path(path));
  }

  TEST(UtilsTest, ThrowsWhenHomeNotSet) {
    const char* originalHome = std::getenv("HOME");
    unsetenv("HOME");

    EXPECT_THROW({
      utils::expandTilde("~/missing-home");
    }, std::runtime_error);

    if (originalHome) {
      setenv("HOME", originalHome, 1);
    }
  }
}
