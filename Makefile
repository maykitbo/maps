# Number of parallel jobs for make
MAKE_FLAGS=-j4

# Database library build settings
DB_LIB_BUILD_PATH=build/db_lib
DB_LIB_PATH=src/data
DB_TEST_EXEC=test_database_lib

# Desktop application build settings
DESKTOP_BUILD_PATH=build/desktop
DESKTOP_CMAKE_DIR=src/ui/desktop
DESKTOP_EXEC=maykitbo_maps

# Target to build and run database library tests
data_manager_test:
	@echo "Building and running database library tests..."
	cmake -S $(DB_LIB_PATH) -B $(DB_LIB_BUILD_PATH) -DDBUILD_TESTS=ON
	$(MAKE) -C $(DB_LIB_BUILD_PATH) $(MAKE_FLAGS)
	./$(DB_LIB_BUILD_PATH)/$(DB_TEST_EXEC)

# Target to build and run the desktop application
desktop:
	@echo "Building and running the desktop application..."
	cmake -S $(DESKTOP_CMAKE_DIR) -B $(DESKTOP_BUILD_PATH) -DDB_LIB_PATH=$(DB_LIB_PATH)
	$(MAKE) -C $(DESKTOP_BUILD_PATH) $(MAKE_FLAGS)
	./$(DESKTOP_BUILD_PATH)/$(DESKTOP_EXEC)

# Target to clean all build directories
clean:
	@echo "Cleaning build directories..."
	rm -rf build/*

# Target to display help information
help:
	@echo "Available targets:"
	@echo "  data_manager_test  - Build and run database library tests"
	@echo "  desktop            - Build and run the desktop application"
	@echo "  clean              - Clean all build directories"
