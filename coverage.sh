cd build/Debug
lcov --capture --directory . --output-file coverage.info --ignore-errors inconsistent,unsupported,format
lcov --remove coverage.info '/usr/*' '*/tests/*' '*/.conan2/*' --output-file coverage_filtered.info
genhtml coverage_filtered.info --output-directory out
open out/index.html
cd ../../