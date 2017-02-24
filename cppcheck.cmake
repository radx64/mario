# additional target to perform cppcheck run, requires cppcheck

set(PROJECT_TRDPARTY_DIR "build")

file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h)
foreach (SOURCE_FILE ${ALL_SOURCE_FILES})
    string(FIND ${SOURCE_FILE} ${PROJECT_TRDPARTY_DIR} PROJECT_TRDPARTY_DIR_FOUND)
    if (NOT ${PROJECT_TRDPARTY_DIR_FOUND} EQUAL -1)
        list(REMOVE_ITEM ALL_SOURCE_FILES ${SOURCE_FILE})
    endif ()
endforeach ()

add_custom_target(
        cppcheck
        COMMAND /usr/bin/cppcheck
        --enable=warning,performance,portability,information
        --suppress=useInitializationList
        --suppress=missingInclude
        --std=c++11
        --template="[{severity}][{id}] {message} {callstack} \(On {file}:{line}\)"
        --quiet
        ${ALL_SOURCE_FILES}
)