bin_PROGRAMS = sensor-logger
sensor_logger_LDADD =  -lsqlite3 -lopenair
sensor_logger_CXXFLAGS = -std=c++14
sensor_logger_SOURCES = \
	main.cc\
	sqlite_logger.hh\
	sqlite_logger.cc\
	sensor_logger_info.hh\
	sensor_logger_info.cc
