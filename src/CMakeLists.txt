project(XenonApp2D)

include(${CMK_DIR}/include_xev.cmake)

file(GLOB_RECURSE SOURCES
        ${SRC_DIR}/*.cpp
        ${SRC_DIR}/*.cxx
        ${SRC_DIR}/*.c
)

add_executable(${PROJECT_NAME}
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
