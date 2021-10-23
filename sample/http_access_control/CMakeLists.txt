file(GLOB_RECURSE SOURCE_FILES "*.h" "*.cpp")

set(PROJECT_NAME imonitor_sample_http_access_control)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"")
