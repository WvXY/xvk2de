project(UnitTest)

include(${CMK_DIR}/include_xev.cmake)

add_executable(${PROJECT_NAME}
        ${XEV_SRC_FILES}
        unittest_main.cpp
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

## ==========================================
#add_executable(TestBB
#        ${XEV_SRC_FILES}
#        bb_test.cpp
#)
#
#target_include_directories(TestBB
#        PRIVATE ${XEV_INCLUDE_DIR}
#)

#add_dependencies(TestGeometry CompileShaders)