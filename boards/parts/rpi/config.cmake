find_package(PkgConfig REQUIRED) 
pkg_check_modules(DBUS_CXX REQUIRED IMPORTED_TARGET dbus-c++-1)
target_link_libraries(otto_src PUBLIC PkgConfig::DBUS_CXX)
