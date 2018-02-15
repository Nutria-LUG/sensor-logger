bin_PROGRAMS = sensor-logger
sensor_logger_LDADD =  -lsqlite3
sensor_logger_CXXFLAGS = -std=c++14
sensor_logger_SOURCES = \
	main.cc\
	sensor_logger_info.cc\
	configuration.cc \
	sensor.cc \
	sourvay.cc \
	loggers/sourvay_logger.cc \
	loggers/sqlite_logger.cc
