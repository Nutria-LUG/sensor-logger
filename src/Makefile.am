bin_PROGRAMS = logger
logger_LDADD =  -lsqlite3 -lboost_system -lboost_filesystem #-lstdc++fs
#logger_CXXFLAGS = -std=c++14
logger_SOURCES = \
	main.cc\
	sensor_logger_info.cc\
	configuration.cc \
	sensor.cc \
	sourvay.cc \
	filesystem/filesystem.cc\
	filesystem/boost_filesystem.cc\
	loggers/sourvay_logger.cc \
	loggers/sqlite_logger.cc
