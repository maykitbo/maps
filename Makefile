# Number of parallel jobs for make
MAKE_FLAGS=#-j4

# Database library build settings
DB_LIB_BUILD_PATH=build/db_lib
DB_LIB_PATH=src/data
# Database tests
DB_TEST_EXEC=data_test
DATA_WKB_TEST=WKB_TEST
DATA_TEMP_TEST=TEMP_TEST

# Tune database
TUNE_DB_CMAKE_FLAG=TUNE_DATABASE
TUNE_DB_EXEC=tune_database


# Core library build settings
CORE_LIB_PATH=src/core

# Desktop application build settings
DESKTOP_BUILD_PATH=build/desktop
DESKTOP_CMAKE_DIR=src/ui/desktop
DESKTOP_EXEC=maykitbo_maps


# Generic test target
define RUN_TEST
	rm -rf $(DB_LIB_BUILD_PATH)
	cmake -S $(DB_LIB_PATH) -B $(DB_LIB_BUILD_PATH) -DTEST_FLAG=$1
	$(MAKE) -C $(DB_LIB_BUILD_PATH) $(MAKE_FLAGS)
	./$(DB_LIB_BUILD_PATH)/$(DB_TEST_EXEC)
endef


data_wkb_test:
	$(call RUN_TEST,$(DATA_WKB_TEST))

data_temp_test:
	$(call RUN_TEST,$(DATA_TEMP_TEST))

# Target to build and run database tune
tune_database:
	@echo "Building and running database tune..."
	cmake -S $(DB_LIB_PATH) -B $(DB_LIB_BUILD_PATH) -D$(TUNE_DB_CMAKE_FLAG)=ON
	$(MAKE) -C $(DB_LIB_BUILD_PATH) $(MAKE_FLAGS)
	./$(DB_LIB_BUILD_PATH)/$(TUNE_DB_EXEC)


# Target to build and run the desktop application
desktop:
	@echo "Building and running the desktop application..."
	cmake -S $(DESKTOP_CMAKE_DIR) -B $(DESKTOP_BUILD_PATH) -DDB_LIB_PATH=$(DB_LIB_PATH) -DCORE_LIB_PATH=$(CORE_LIB_PATH)
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
