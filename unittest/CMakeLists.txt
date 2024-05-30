project(UnitTest)

#add_executable(TestGeometry geo_test.cpp)

include(${CMK_DIR}/include_xev.cmake)

#file(GLOB_RECURSE SOURCES
#        ${PROJECT_SOURCE_DIR}/*.cpp
#        ${PROJECT_SOURCE_DIR}/*.hpp
#)

add_executable(TestGeometry
        ${XEV_SRC_FILES}
        geo_test.cpp
)

if(UNIX)
    target_link_libraries(TestGeometry
            PRIVATE glfw
            PRIVATE Vulkan::Vulkan
    )
else()
    target_link_libraries(TestGeometry
            PRIVATE glm::glm
            PRIVATE glfw
            PRIVATE Vulkan::Vulkan
    )
endif()

target_include_directories(TestGeometry
        PRIVATE ${XEV_INCLUDE_DIR}
)

#add_dependencies(TestGeometry CompileShaders)