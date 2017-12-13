bin_PROGRAMS = sensor_logger
sensor_logger_LDADD =  -lsqlite3 -lboost_system -lboost_filesystem #-lstdc++fs
sensor_logger_CXXFLAGS = -std=c++14
sensor_logger_SOURCES = \
	main.cc\
	sensor_logger_info.cc\
	configuration.cc \
	sensor.cc \
	sourvay.cc \
	filesystem/filesystem.cc\
	filesystem/boost_filesystem.cc\
	logger/sourvay_logger.cc \
	logger/sqlite_logger.cc
