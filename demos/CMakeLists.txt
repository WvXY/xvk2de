project(Demo-ballistic)

include(${CMK_DIR}/include_xev.cmake)

file(GLOB_RECURSE SOURCES
        ${PROJECT_SOURCE_DIR}/*.cpp
        ${PROJECT_SOURCE_DIR}/*.hpp
)

add_executable(${PROJECT_NAME}
        ${XEV_SRC_FILES}
        ${SOURCES}
)

if(UNIX)
    target_link_libraries(${PROJECT_NAME}
            PRIVATE glfw
            PRIVATE Vulkan::Vulkan
    )
else()
    target_link_libraries(${PROJECT_NAME}
            PRIVATE glm::glm
            PRIVATE glfw
            PRIVATE Vulkan::Vulkan
    )
endif()

target_include_directories(${PROJECT_NAME}
        PRIVATE ${XEV_INCLUDE_DIR}
)

add_dependencies(${PROJECT_NAME} CompileShaders)
